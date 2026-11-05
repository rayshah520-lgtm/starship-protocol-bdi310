/*
  BDI310 — Starship Protocol
  Tested logic target: standard ESP32-WROOM-32 / ESP32 Dev Module.
  Use VS Code + PlatformIO IDE to build and upload this project.

  Wiring (ESP32 unplugged when connecting):
    GPIO 23 -> one side of push button
    GND     -> opposite side of push button
    GPIO 18 -> 220-ohm resistor -> LED long leg (+)
    GND     -> LED short leg (-)

  ESP32 hosts its own Wi-Fi network and web page.
*/
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const int BUTTON_PIN = 23;
const int LED_PIN = 18;
const unsigned long DEBOUNCE_MS = 35;
const char *AP_NAME = "BDI310-Starship";
const char *AP_PASSWORD = "Signal310";

WebServer server(80);
bool buttonPressed = false;
int lastRawButton = HIGH;
unsigned long lastChangeAt = 0;
unsigned long pressCount = 0;

// A single self-contained webpage: no internet is needed to display it.
const char PAGE[] PROGMEM = R"STARSHIP(
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Starship Protocol</title>
  <style>
    * { box-sizing: border-box; }
    :root { color-scheme: dark; }
    body { margin: 0; min-height: 100vh; font-family: system-ui, Arial, sans-serif;
      background: radial-gradient(circle at 50% 35%, #162b48 0%, #09131f 48%, #050b12 100%);
      color: #e2f7ff; display: grid; place-items: center; padding: 22px; }
    main { width: min(100%, 570px); border: 1px solid #2a5c79; border-radius: 16px;
      padding: clamp(20px, 5vw, 42px); text-align: center; background: #091726dc;
      box-shadow: 0 0 50px #008ee019, inset 0 0 30px #0077cc13; }
    .eyebrow { font-size: 11px; letter-spacing: .27em; color: #6fb3cb; }
    h1 { font-size: clamp(24px, 6vw, 34px); margin: 16px 0 10px; letter-spacing: .06em; }
    .radar { width: 180px; height: 180px; margin: 27px auto; border-radius: 50%;
      display:grid; place-items:center; position:relative; border: 1px solid #387c9a;
      background: repeating-radial-gradient(circle, #1178a51f 0 1px, transparent 2px 31px), #0b2237;
      box-shadow: inset 0 0 32px #0088cc22; }
    .radar:before, .radar:after { content:""; position:absolute; background:#347fa64d; }
    .radar:before { width:1px; height:100%; } .radar:after { width:100%; height:1px; }
    .core { width:45px; height:45px; border-radius:50%; background:#335c73; border:3px solid #7da9bd;
      box-shadow:0 0 13px #4d9db86b; z-index:1; transition: .18s; }
    .active .core { background:#72ecff; border-color:#d5fdff; box-shadow:0 0 30px #39d7ff, 0 0 80px #118fd0; }
    .active .radar { border-color:#73edff; box-shadow:0 0 32px #20c8fa35, inset 0 0 48px #008fdf35; }
    .active .radar:before, .active .radar:after { background:#4dbce66b; }
    .state { font-size: clamp(21px, 5vw, 29px); font-weight:800; letter-spacing:.15em; color:#a6b5c1; }
    .active .state { color:#80eaff; text-shadow:0 0 20px #33cfff8f; }
    .subtitle { margin:13px 0 24px; color:#9fbbcb; font-size:14px; }
    .details { display:flex; justify-content:space-between; gap:20px; border-top:1px solid #24445a;
      padding-top:17px; color:#a2c2d0; font-size:12px; }
    .details strong { color:#e2f8ff; font-size:15px; }
    .preview { display:none; margin:23px auto 0; padding:12px 17px; color:#041421;
      background:#90eaf8; border:0; border-radius:8px; font-weight:800; cursor:pointer; touch-action:none; }
    .preview:focus-visible { outline:3px solid #e2f7ff; outline-offset:5px; }
    .hint { padding-top:16px; color:#6f9bac; font-size:12px; line-height:1.5; }
  </style>
</head>
<body>
  <main id="console">
    <div class="eyebrow">BDI310 // ESP32 CONTROL SYSTEM</div>
    <h1>STARSHIP PROTOCOL</h1>
    <div class="radar" aria-hidden="true"><div class="core"></div></div>
    <div id="signal" class="state" aria-live="polite">STANDBY</div>
    <p id="description" class="subtitle">Hold the physical button to transmit.</p>
    <div class="details">
      <span>BUTTON PRESSES<br><strong id="count">0</strong></span>
      <span>LINK STATUS<br><strong id="connection">CONNECTING...</strong></span>
    </div>
    <button class="preview" id="virtual" type="button">Hold virtual button (offline preview)</button>
    <p class="hint" id="hint">Connect your laptop to the ESP32 Wi-Fi network to use this page.</p>
  </main>
  <script>
    const panel = document.getElementById('console');
    const signal = document.getElementById('signal');
    const description = document.getElementById('description');
    const count = document.getElementById('count');
    const connection = document.getElementById('connection');
    const virtual = document.getElementById('virtual');
    const hint = document.getElementById('hint');
    function showState(pressed, pressCount) {
      panel.classList.toggle('active', pressed);
      signal.textContent = pressed ? 'SIGNAL ACTIVE' : 'STANDBY';
      description.textContent = document.documentElement.dataset.mode === 'preview'
        ? (pressed ? 'Simulated transmission. Hardware is not connected.' : 'Hold the virtual button to simulate a signal.')
        : (pressed ? 'Transmitting from the ESP32...' : 'Hold the physical button to transmit.');
      count.textContent = pressCount;
    }
    const POLL_MS = 250;
    const REQUEST_TIMEOUT_MS = 2000;
    let requestInFlight = false;
    async function update() {
      if (requestInFlight) return;
      requestInFlight = true;
      const controller = new AbortController();
      const timeout = setTimeout(() => controller.abort(), REQUEST_TIMEOUT_MS);
      try {
        const response = await fetch('/state', { cache: 'no-store', signal: controller.signal });
        if (!response.ok) throw new Error('ESP32 response failed');
        const data = await response.json();
        if (typeof data !== 'object' || data === null ||
            typeof data.pressed !== 'boolean' ||
            !Number.isSafeInteger(data.count) || data.count < 0) {
          throw new Error('Invalid ESP32 state');
        }
        showState(data.pressed, data.count);
        connection.textContent = 'CONNECTED';
      } catch (err) {
        panel.classList.toggle('active', false);
        signal.textContent = 'SIGNAL UNKNOWN';
        description.textContent = 'Reconnect to the ESP32. Last count may be stale.';
        connection.textContent = 'DISCONNECTED';
      } finally {
        clearTimeout(timeout);
        requestInFlight = false;
      }
    }
    if (document.documentElement.dataset.mode === 'preview') {
      // The offline preview only imitates a button. No ESP32 is controlled.
      let previewCount = 0;
      let pressed = false;
      virtual.style.display = 'block';
      connection.textContent = 'PREVIEW ONLY';
      hint.textContent = 'Offline webpage preview: use the virtual button. The physical kit is not connected.';
      const down = (event) => {
        event.preventDefault();
        if (!pressed) { pressed = true; previewCount += 1; }
        showState(true, previewCount);
        if (event.pointerId != null) virtual.setPointerCapture(event.pointerId);
      };
      const up = () => { pressed = false; showState(false, previewCount); };
      showState(false, previewCount);
      virtual.addEventListener('pointerdown', down);
      virtual.addEventListener('pointerup', up);
      virtual.addEventListener('pointercancel', up);
      virtual.addEventListener('lostpointercapture', up);
      virtual.addEventListener('keydown', (event) => {
        if (event.key === ' ' || event.key === 'Enter') {
          event.preventDefault();
          if (!event.repeat) down(event);
        }
      });
      virtual.addEventListener('keyup', (event) => {
        if (event.key === ' ' || event.key === 'Enter') {
          event.preventDefault(); up();
        }
      });
      virtual.addEventListener('blur', up);
      window.addEventListener('blur', up);
    } else {
      signal.textContent = 'SIGNAL UNKNOWN';
      description.textContent = 'Waiting for the ESP32...';
      update();
      setInterval(update, POLL_MS);
    }
  </script>
</body>
</html>
)STARSHIP";

// Read the button and ignore tiny electrical bounces.
void updateButton() {
  int raw = digitalRead(BUTTON_PIN);
  if (raw != lastRawButton) {
    lastChangeAt = millis();
    lastRawButton = raw;
  }
  if (millis() - lastChangeAt >= DEBOUNCE_MS) {
    bool nowPressed = (raw == LOW); // INPUT_PULLUP: pressed means LOW
    if (nowPressed != buttonPressed) {
      buttonPressed = nowPressed;
      digitalWrite(LED_PIN, buttonPressed ? HIGH : LOW);
      if (buttonPressed) pressCount++;
    }
  }
}

// Send the current button state to the webpage as JSON.
void sendState() {
  String json = "{\"pressed\":";
  json += (buttonPressed ? "true" : "false");
  json += ",\"count\":";
  json += String(pressCount);
  json += "}";
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Internal pull-up; no 10k resistor needed
  lastRawButton = digitalRead(BUTTON_PIN);

  WiFi.mode(WIFI_AP);
  bool wifiOK = WiFi.softAP(AP_NAME, AP_PASSWORD);
  Serial.println();
  if (!wifiOK) {
    Serial.println("Could not start ESP32 Wi-Fi network.");
    return;
  }
  Serial.print("Join Wi-Fi network: ");
  Serial.println(AP_NAME);
  Serial.print("Wi-Fi password: ");
  Serial.println(AP_PASSWORD);
  Serial.print("Open webpage: http://");
  Serial.println(WiFi.softAPIP()); // Typically 192.168.4.1

  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", PAGE);
  });
  server.on("/state", HTTP_GET, sendState);
  server.onNotFound([]() {
    server.send(404, "text/plain", "Page not found");
  });
  server.begin();
}

void loop() {
  updateButton();
  server.handleClient();
  delay(2);
}
