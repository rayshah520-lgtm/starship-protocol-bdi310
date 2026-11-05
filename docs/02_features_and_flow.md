# Features and Visitor Flow

## Features
F1. Display a starship communications console with an immediately readable signal state.
F2. Read a momentary physical button on GPIO23 using the internal pull-up.
F3. Turn the LED on GPIO18 on while the debounced button is held, then off on release.
F4. Count one transmission per transition from released to pressed; holding does not repeatedly increment it.
F5. Show the current count and connection status on the browser page.
F6. Provide a clearly labelled offline simulation with a virtual hold button, without claiming to control hardware.
F7. Explain loss of connection and distinguish an unavailable reading from a confirmed released button.

## Main flow
1. Power the already-wired ESP32 and join its local Wi-Fi network.
2. Open the board's HTTP address shown in the serial monitor.
3. Read the instruction to hold the physical button.
4. Hold: LED on, SIGNAL ACTIVE, count increases once.
5. Release: LED off, STANDBY, count unchanged.
6. Repeat to start another transmission.

## Alternative and failure flows
Offline preview: open offline_preview.html directly, see PREVIEW ONLY and use the virtual button.
Lost connection: show DISCONNECTED and SIGNAL UNKNOWN; preserve the last count with a stale-data explanation. On a successful later response, restore live state.
Restart: count starts at zero because it is stored in memory only.

## Boundaries
The browser observes the physical button. It does not remotely switch the real LED. The virtual button changes simulation state only.
