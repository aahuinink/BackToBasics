# Check-in Log

Newest first. Written by the mentor during `/checkin` and `/submit`.

---

## 2026-11-14 · Kickoff

**Decisions**
- Target: Nucleo-F446RE (Cortex-M4F, 180 MHz, 512 KB flash, 128 KB SRAM). The ESP32-S3 is parked for Phase 6, because zig doesn't target Xtensa and its boot path is opaque.
- Language: C11 (`-std=c11`), freestanding. Compiler-provided headers (`stdint.h`, `stddef.h`, `stdbool.h`) are allowed. No libc.
- Build: zig cc + GNU Make. Keep `CC` swappable so the code is also checked against arm-none-eabi-gcc.
- Flash/debug: OpenOCD + GDB from the command line. No custom flasher or bootloader in Phase 1. Those come together in Phase 3.
- Dev environment: WSL2. The ST-LINK has to be passed through with usbipd-win.
- Budget: 5–10 h/week, no fixed schedule. Tickets are ≤ 4 h each.

**Assigned:** BTB-001 (assessment). BTB-002 and BTB-003 are queued.

**Next check-in due:** 2026-11-21
