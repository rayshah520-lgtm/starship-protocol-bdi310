# M7 Build and Submission Plan

## Starting point
These new plans refer to the earlier Starship Signal Console concept and starter. Preserve that distinction in the journal. Do not describe imported starter code as a new build generated after these plans.

## Work order
1. Commit and push these planning documents to a new Starship Protocol repository.
2. Ask the agent to read all seven documents and implement the complete app. Use only the specified stack.
3. Run the app and review the frontend specification section by section. Commit and push the first build.
4. Save actual problems as docs/findings.md: numbered list, one finding per line. Commit and push before editing implementation code.
5. Work on one finding per new conversation. Read affected files in full before changing them. Test each fix, mark its finding complete, update the journal, then commit and push.
6. Record hardware-dependent checks as pending until tested on the kit. It is acceptable to leave findings unfinished; the assignment says the build need not be polished.

## First-build instruction
Read every document in docs before changing code. Build Starship Protocol from these documents using only the listed technologies. Report the location of each feature and anything not implemented. Keep the offline simulation clearly separate from physical hardware operation. Do not claim hardware checks passed without observing them.

## Findings format
Use a numbered list such as “1. [ ]” followed by an actual observed problem, its reproduction steps, and expected behavior. Do not pre-fill imaginary defects. After testing a fix, change the box to [x] and record the test result.

## Journal content
Describe what was requested, what the agent returned, what actually failed or needed correction, what changed, and what was tested. Mention use of the earlier starter where applicable. Do not describe tests that have not happened or invent earlier work dates.

## Submission PDF
Filename: RayyanShah_BDI310_M7.pdf.
Put the real github.com repository URL at the top, then the journal entry, a genuine screenshot of docs/findings.md open in VS Code, a screenshot of the running app, and a screenshot of GitHub commit history showing the first build and findings commits before fixes.

## Current status
Planning documents created on 5 November 2026. Repository created and plans committed. See findings.md, journal.md and test-results.md for the subsequent implementation record and remaining hardware checks.
