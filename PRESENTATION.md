Page 1 — Assignment & Scope

- Assignment list (requirements):
  - 2.4 Devices: Device base class + concrete types (Light, Camera, TV, Smoke & Gas Detector, MusicSystem). Implement polymorphism and factory creation.
  - 2.5 Modes: Implement `Mode` interface and 4 mode variants (Normal, Evening, Party, Cinema) using Strategy/State patterns.
  - 2.6 States: Implement system performance states (Normal, Sleep, HighPerformance) and state history/transition handling.
  - 2.7 Security: Security subsystem with motion/smoke/gas/intrusion detection, alarm activation, and escalation.
  - 2.8 Detection: Timed alarm sequences, user acknowledgment, and interruptible alarm flows.

---

Page 2 — Commit History (high-level)

- Notable commits (representative):
  - "Fix CMake typo and build configuration" — corrected cmake_minimum_required and build targets.
  - "Guard conio.h and add POSIX non-blocking input" — added termios/select `_kbhit()`/_getch() for Linux.
  - "Remove bilingual Arabic UI strings — convert to English" — made UI English-only.
  - "Add Test Alarm menu and auto-create test devices" — `testAlarmMenu()` creates temporary devices when missing.
  - "Add --auto-test mode and deterministic self-test" — `runAutoTest()` for automated validation.
  - "Device API improvements and prevent powering off detectors" — added device active/inactive API and detector protections.
  - "Fix smoke simulation ID handling and security registration" — corrected simulateSmokeEvent and SecuritySystem registration.
  - "Update TEAM_SUMMARY and COMPLETION_REPORT" — documentation updates.

- View full history: `git log --oneline --decorate --graph` (recommended during presentation)

---

Page 3 — Integration Plan & Branching

- Branching model (recommended / used):
  - `main` — stable production-ready code.
  - feature/* — each feature or subsystem (e.g., `feature/mode-subsystem`, `feature/devices`).
  - fix/* — hotfix branches for CI/build breakages.
  - `integration` (optional) — for cross-team merges and integration testing before `main`.

- Integration workflow:
  1. Developer creates `feature/<name>` branch.
  2. Work, local tests, and commit messages following Conventional Commits.
  3. Open Pull Request to `integration` or `main` (depending on policy).
  4. Code review by at least one other subsystem owner, CI runs unit/build checks.
  5. Merge only after approvals and passing CI.

- CI suggestions: run `cmake --build`, static analysis (cppcheck), and unit tests (if added). Use `buildkite`/`github actions` for automation.

---

Page 4 — Roadmap, Challenges & Scoring

- Roadmap (next steps):
  - Add unit tests and integration tests (GTest) for devices, modes, and detection flows.
  - Implement a PTY/expect-based test harness for interactive flows.
  - Add CI pipeline with static analysis and artifacts.
  - Extend device family variants (e.g., `SamsungTV`/`LGTV`) if strict product-family classes required.
  - Improve UX: better menu, config file support via `ConfigManager`.

- Development challenges encountered:
  - CMake configuration typos and mixed target signatures — required careful CMake fixes.
  - Non-portable input handling (`conio.h`) — solved with POSIX `termios` and `select`.
  - Multiple API mismatches across subsystems (Logger, AlarmSystem, SecuritySystem) — required iterative refactors and forward declarations.
  - Interactive test automation — piped stdin mismatched prompts; solved by adding `--auto-test` and auto-device creation.
  - Ensuring detectors cannot be turned off and are registered with security subsystem.

- VCS / Integration screenshots & scoring:
  - If integration screenshots (branch graph, PR approvals, CI green) are available, award base score to each team member before individual presentation.
  - To capture screenshots: `git log --oneline --graph --decorate --all` and GH PR pages.

- Presentation tips (10 minutes each):
  - 1–2 minutes: Assignment & what you implemented.
  - 3–4 minutes: Demonstration (run `./MSHSystem` or `./MSHSystem --auto-test`).
  - 2–3 minutes: Integration notes, commits, and challenges.
  - 1 minute: Q&A and next steps.

---

Files added/updated during the project (quick reference):
- `MSHSystem.h`, `MSHSystem.cpp`, `main.cpp`
- `modules/devices/*` (Light, Camera, TV, SmokeGasDetector, MusicSystem, DeviceManager)
- `alarmsystem.*`, `securitysystem.*`, `DetectionSystem.*`
- `Logger.h`, `COMPLETION_REPORT.md`, `TEAM_SUMMARY.txt`, `PRESENTATION.md`


Prepared by: Team MSH — ready for 10-minute presentations.
