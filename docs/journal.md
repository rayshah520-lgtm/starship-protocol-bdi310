# M7 Journal - Starship Protocol
Rayyan Shah | BDI310 | 5 November 2026

## What I asked for
I asked the AI agent to use my Starship Protocol concept, create the planning documents and repository, then complete the build, findings and submission evidence. The interaction is a physical button connected to an ESP32: holding it lights an LED and changes the browser console to SIGNAL ACTIVE. A separate preview simulates this without hardware.

## What came back
The agent wrote seven planning documents and adapted the earlier Starship Signal Console starter into the first M7 draft. It kept the ESP32 firmware in src/main.cpp, the standalone preview in offline_preview.html and the board settings in platformio.ini. The planning documents were created after that earlier starter existed, so this was an adaptation rather than an entirely new concept built from scratch.

The first draft loaded, but the HTTP preview showed DISCONNECTED because it assumed only a file:// page could be a simulation. Reviewing the code and running its event handlers also exposed misleading simulation wording, missing keyboard input, a lost-link state that incorrectly looked like standby, and missing validation and request timeout handling.

## Findings before fixes
The first browser draft was committed as 76ad4de; the complete ESP32 source followed as 5251591. The findings were saved in docs/findings.md and committed as 30fead5 before implementation changes. This preserves the original problems in the repository history.

## What had to be corrected
The agent handled five software findings sequentially. It made the preview mode explicit so it works through HTTP as well as a local file. It changed the text to describe simulated transmissions, added Space/Enter hold and release controls, showed SIGNAL UNKNOWN when a reading is unavailable, and added response validation, a 2000ms timeout and a single-request guard.

Each finding was checked before the next local commit. Local commit identifiers are recorded in test-results.md; the verified final files were then synchronized to GitHub. The fixes were handled in one continuous assistant session, rather than separate chat threads as suggested in the class workflow.

## Verification and limits
The agent ran browser checks for keyboard input, a three-second pointer hold, and layouts at 375px and 1280px. It also ran a Node VM harness against the actual page script for key repeat, release, blur, malformed data, timeout, recovery and valid state changes. These automated and agent-operated checks are not claimed as tests I personally performed on my kit.

The ESP32 firmware compiled successfully in PlatformIO with telemetry disabled. Physical firmware upload, wiring, LED behavior and real ESP32 Wi-Fi recovery remain unverified because the kit is not connected to the agent's environment. Finding 6 remains open. The running-app screenshot therefore shows PREVIEW ONLY. The build does not need to be fully polished for M7, but the physical checks are the next step before demonstrating it in class.
