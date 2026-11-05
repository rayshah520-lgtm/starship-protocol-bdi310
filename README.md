# Starship Protocol | BDI310 M7
Rayyan Shah

An ESP32 communications console: hold a physical button to light an LED and show SIGNAL ACTIVE. Release for STANDBY. Separate presses increase the transmission counter.

## Open the browser preview
Extract this project and double-click offline_preview.html. The virtual button simulates input; PREVIEW ONLY means no hardware is controlled. The final preview works directly from a file or through VS Code Live Server; it explicitly stays in simulation mode.

## Run on the kit
Open this folder in VS Code with PlatformIO IDE installed. Disconnect USB before wiring. Connect GPIO23 through the button to GND; connect GPIO18 through a 220-ohm resistor to the LED anode, and its cathode to GND. See wiring_diagram.svg. Reconnect USB with a data cable. Build, then Upload using PlatformIO. Open Serial Monitor at 115200 baud. Join BDI310-Starship with the demonstration password Signal310. Open the HTTP address printed in Serial Monitor (normally http://192.168.4.1).

## Source map
- src/main.cpp: debounced button input, LED output, counter, local Wi-Fi and HTTP server, and embedded page.
- offline_preview.html: standalone browser simulation.
- platformio.ini: ESP32-WROOM-32 / Arduino build configuration.
- docs/01 through 07: planning specifications and acceptance checks.
- docs/findings.md and docs/journal.md: review and work record, added after the first build.

## Provenance and verification
This M7 build adapts the earlier AI-assisted Starship Signal Console starter. The planning documents were written later; the draft is not presented as entirely new code created before the starter. Physical ESP32 upload and LED behavior require the actual kit and are not claimed as tested here.
