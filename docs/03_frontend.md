# Frontend Specification

## Layout
One centered console panel, maximum width 570px, on a dark navy background. Use a system font, cyan highlights, a radar-style circular indicator, and clear text labels. Use the product name STARSHIP PROTOCOL with a small signal-console descriptor.

Reading order: project identifier; title; visual signal indicator; signal status; short instruction; transmission count and link status; preview control when applicable; connection guidance.

## States
| Mode | Signal | Link | Instruction |
| --- | --- | --- | --- |
| Initial live request | SIGNAL UNKNOWN | CONNECTING | Waiting for the ESP32 |
| Connected, released | STANDBY | CONNECTED | Hold the physical button to transmit |
| Connected, held | SIGNAL ACTIVE | CONNECTED | Transmitting from the ESP32 |
| Request failure | SIGNAL UNKNOWN | DISCONNECTED | Reconnect to the board; last count may be stale |
| Offline, released | STANDBY | PREVIEW ONLY | Hold the virtual button to simulate a signal |
| Offline, held | SIGNAL ACTIVE | PREVIEW ONLY | Simulated transmission; hardware is not connected |

## Interaction and accessibility
Signal information must use words as well as color. Use a native button with a visible focus outline for the offline control. Support mouse/touch hold and keyboard Space/Enter hold; ignore key-repeat when counting. Release on pointer cancellation, window blur, or keyboard release. Put status changes in a polite live region. Mark decorative radar graphics as hidden from assistive technology.

## Responsive behavior
Use a viewport meta tag, border-box sizing, 20–22px outer padding and a panel width that fits the viewport. At 375px and 1280px, all text and controls should fit without horizontal page scrolling. Allow detail labels to wrap when needed.

## Timing
Request state approximately every 250ms while connected. Keep no more than one request in flight and time out each request after 2000ms. A failed request must not leave a previous active indicator looking live.
