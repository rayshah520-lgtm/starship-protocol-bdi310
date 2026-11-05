# Technical and Hardware Specification

## Approved implementation stack
- ESP32-WROOM-32 Dev Module, Arduino framework, C++ firmware.
- VS Code with PlatformIO IDE for compilation, upload, and serial monitoring.
- ESP32 Arduino core libraries: Arduino, WiFi, WebServer.
- Plain HTML, CSS and JavaScript in the browser; no frontend framework or CDN.
- Git and GitHub for source history and submission evidence.

No cloud hosting, external API, account system, database, or additional runtime library is required. First-time PlatformIO installation needs internet access; the loaded console runs locally afterward.

## Components and wiring
Disconnect USB power before wiring. Use the board's printed GPIO labels.

| Part | Connection |
| --- | --- |
| Momentary button | GPIO23 to one electrical side, GND to the opposite electrical side |
| LED | GPIO18 through a 220-ohm resistor to the anode; cathode to GND |
| Board power | USB data cable connected to the laptop |

Place a four-leg button across the breadboard gap so the chosen electrical sides are separate. Use the resistor in series with the LED. Check wiring before powering the kit.

## Named constants
BUTTON_PIN = 23; LED_PIN = 18; DEBOUNCE_MS = 35; POLL_MS = 250; REQUEST_TIMEOUT_MS = 2000; SERIAL_BAUD = 115200.
Access point name: BDI310-Starship. Configure its local demonstration password in firmware. Do not commit personal Wi-Fi credentials. Display the actual board address in the serial monitor; the starter uses http://192.168.4.1.

## Intended folder structure
README.md — how to open, run, and test.
docs/ — these seven planning documents, then actual findings and journal.
platformio.ini — board and build configuration.
src/main.cpp — firmware, HTTP routes, and embedded console page.
offline_preview.html — standalone simulated interface.
wiring_diagram.svg — wiring reference.
.gitignore — exclude PlatformIO build output and editor-generated temporary files.

## Constraints
No actual ESP32 is attached to this workspace. Compilation, firmware upload, wiring behavior, and LED behavior must be verified on the student's equipment before being reported as passed.
