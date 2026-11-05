# Verification record - 5 November 2026

## Software checks observed by the agent
- Browser HTTP preview: PREVIEW ONLY and virtual button displayed after finding 1 fix.
- Browser Space followed by Enter: count reached 2; each release returned to STANDBY.
- Browser pointer held for 3000ms: count increased once to 1; release returned to STANDBY.
- Browser responsive iframe: 375px viewport / 375px content; 1280px viewport / 1280px content. No horizontal document overflow.
- Node VM: pointer down/up, keyboard repeat ignored, keyboard release and window blur reset active state.
- Node VM: network failure showed SIGNAL UNKNOWN, DISCONNECTED and stale-count explanation.
- Node VM: six invalid JSON-state fixtures were rejected (null, empty object, string boolean, negative count, fractional count, unsafe integer).
- Node VM: valid responses updated signal and count; a later valid response recovered from failure.
- Node VM: concurrent poll was ignored while a request was pending; abort timer was 2000ms.
- Browser log inspection found extension-origin metadata errors; no app-origin JavaScript error was observed in the inspected entries.

## Local sequential fix commits
1. 6f68aaf - explicit HTTP preview mode.
2. 834f0e7 - accurate simulation wording.
3. 1073f6d - keyboard hold/release.
4. b4fd253 - unknown signal on disconnect.
5. b8b1e92 - bounded and validated requests.

These are local work commits, not GitHub commit hashes. The GitHub first-build and findings commits are recorded in journal.md. Final files are synchronized by browser uploads, grouped by directory.

## Physical checks pending
No ESP32 is attached. Firmware upload, real button/LED response, physical debounce, board restart, routes and actual Wi-Fi reconnection have not been verified on hardware. Browser/VM tests do not replace these checks.
