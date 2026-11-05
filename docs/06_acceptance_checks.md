# Acceptance Checks
These are planned checks, not test results. Record actual observations after the first build and before making fixes.

| ID | Action | Expected result | Equipment |
| --- | --- | --- | --- |
| A1 | Open offline_preview.html directly | Console loads; PREVIEW ONLY is visible | Browser |
| A2 | Hold virtual button, then release | Active while held, standby after release, count +1 | Browser |
| A3 | Hold virtual button for 3 seconds | Count increases once only | Browser |
| A4 | Tab to virtual button; hold/release Space, then Enter | Same behavior as pointer; visible focus | Browser |
| A5 | Lose window focus during a simulated hold | Signal releases; no stuck active state | Browser |
| A6 | Inspect at 375px and 1280px widths | No horizontal overflow; labels remain readable | Browser |
| A7 | Build the firmware in PlatformIO | Build succeeds for configured ESP32 board | Laptop/toolchain |
| A8 | Upload, power on, join board Wi-Fi, open displayed HTTP address | Console reports CONNECTED and correct state | ESP32 kit |
| A9 | Hold/release physical button | LED and page match button state | ESP32 kit |
| A10 | Hold physical button for 3 seconds, then press 3 separate times | +1 for hold, then +3 for separate presses | ESP32 kit |
| A11 | Disconnect board network during active signal | SIGNAL UNKNOWN and DISCONNECTED within request timeout plus polling interval; count marked stale | ESP32 kit |
| A12 | Reconnect to board network | Next valid response restores live status | ESP32 kit |
| A13 | Request /state | Correct JSON types; no-store response | ESP32 kit/browser |
| A14 | Open unknown route | Plain-text 404 | ESP32 kit/browser |
| A15 | Restart board, reload console | Count returns to zero | ESP32 kit |
| A16 | Inspect browser console while using the page | No uncaught JavaScript errors | Browser |
| A17 | Supply malformed or incorrectly typed state response in a controlled test | Disconnected state; invalid data not presented as live | Browser test harness |

## Evidence rules
Record environment, action, observed result, and pass/fail/pending. Use real screenshots and actual commit history. A browser simulation does not demonstrate a working physical LED or successful firmware upload.
