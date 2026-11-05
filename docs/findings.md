# First-build findings - Starship Protocol
Recorded 5 November 2026, before implementation fixes.
Numbered list: one finding per line. [ ] open; [x] verified fix.

1. [x] HTTP preview: serving offline_preview.html makes it request /state and show DISCONNECTED; it should offer PREVIEW ONLY with a working virtual button (A1-A2).
2. [x] Preview wording: pointer down says "Transmitting from the ESP32" and release says "Hold the physical button"; simulation must describe a virtual signal (A2).
3. [x] Keyboard: the preview registers no keydown/keyup handlers; Space/Enter cannot perform the planned hold interaction (A4).
4. [x] Lost link: the catch handler calls showState(false), presenting STANDBY despite an unknown reading; show SIGNAL UNKNOWN and explain that the last count is stale (A11).
5. [x] Response handling: update() has no timeout, schema validation or request-in-flight guard; reject malformed state, time out at 2000ms and serialize polls (A17).
6. [ ] Hardware verification: no physical ESP32 is attached; firmware upload, button/LED behavior and real Wi-Fi recovery still require kit checks (A8-A15).

Review method: cloud-browser HTTP launch and Node VM event-handler review.
No personal hardware test is claimed. Fixes will be recorded after this list is committed.

Verification: findings 1-5 passed browser/Node checks after sequential fixes; finding 6 remains open. See test-results.md for methods and limits.
