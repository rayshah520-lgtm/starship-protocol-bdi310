# Backend and Data Specification

## Backend
The ESP32 is the local server. Use the Arduino framework's WiFi and WebServer facilities; do not add a remote backend.

## Routes
GET /: return the complete console HTML with CSS and JavaScript, status 200, text/html.
GET /state: return JSON containing pressed (boolean) and count (nonnegative integer), status 200, application/json. Send Cache-Control: no-store.
Unknown paths: return a plain-text 404 response.

Example response: {"pressed":true,"count":3}

## Input rules
Configure GPIO23 as INPUT_PULLUP: LOW means pressed, HIGH means released. Accept a changed raw value only after it remains stable for 35ms. On an accepted transition to pressed, increment count by one. Set GPIO18 to match the accepted state. Never count again until a release followed by another press.

## State and persistence
Initial accepted state is released; LED is off; count is zero. Count and button state exist only in ESP32 RAM. A restart clears the session; there is no database and no personal data collection. Offline simulation keeps its own count in browser memory and resets when the page is reloaded.

## Response handling
The browser accepts pressed only as a boolean and count only as a nonnegative safe integer. Network, timeout, HTTP, JSON, or schema failure changes the interface to the disconnected state. A later valid response restores normal operation. Requests must not accumulate or overwrite newer state with an older result.

## Startup failure
Check that the local Wi-Fi access point starts. If it fails, report a clear serial-monitor message rather than printing a working-address claim. Hardware startup and reconnect behavior must be verified on the actual kit.
