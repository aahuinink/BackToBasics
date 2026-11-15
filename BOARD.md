# Board

Budget: **5–10 h/week, no fixed schedule.** Tickets are sized to fit one or two
sittings (≤ 4 h). Anything bigger gets split.

## Rules

1. **WIP limit: 1 build ticket + 1 reading ticket in Doing.** Finish before you start.
2. To move a ticket, cut and paste it into the right section. `Review` means "done
   from my side, waiting for the mentor".
3. **Log your hours** on the ticket (`Log:` line). This is how we tune estimates and pace.
4. Stuck for more than 45 minutes on one thing? Write down what you tried, then ask.
   Being stuck is data, not failure.
5. Commit at the end of every session, even if it's broken. Use a WIP commit message.

## Cadence

| What | When | How |
|---|---|---|
| **Check-in** | Every 7 days, or every ~5 logged hours, whichever comes first | Run `/checkin` in Claude Code |
| **Review** | When a ticket moves to `Review` | Run `/submit BTB-xxx` |
| **Milestone review** | End of each phase | `/submit` on the milestone ticket. Deeper code review, plus a retro |

Next check-in due: **2026-11-21**

---

## Doing

### BTB-001 · C assessment · est 3–5 h
- **Do:** Fill in `00-assessment/answers.md`. Write the Part C code in `00-assessment/`.
- **Done when:** Every question has an answer ("don't know" counts). The Part C files compile with `-Wall -Wextra -Wpedantic` and no warnings.
- **Read:** nothing. This measures where you are now.
- **Log:**

## Up Next

### BTB-002 · Toolchain + probe bring-up (WSL2) · est 2–3 h
- **Do:**
  - Install `zig`, `openocd`, and `gdb-multiarch` (or `arm-none-eabi-gdb`) in WSL.
  - You're on **WSL2**, so the Nucleo's ST-LINK is not visible by default. Install `usbipd-win` on the Windows side, then `usbipd bind` and `usbipd attach --wsl` the ST-LINK. You'll also need a udev rule or permissions fix so OpenOCD can open it without root.
  - Set up clangd in Neovim (you'll generate `compile_commands.json` later).
- **Done when:** `openocd -f board/st_nucleo_f4.cfg` connects and reports the Cortex-M4. `gdb` attaches through OpenOCD's port 3333. You can run `monitor reset halt` and `info registers` and paste the PC/SP values into the log. (The factory demo firmware is still on the chip, so that's what you'll see.)
- **Read:** OpenOCD User Guide chapters "OpenOCD Project Setup" and "Running". The `usbipd-win` README.
- **Log:**

### BTB-003 · Build your doc shelf · est 1–2 h
- **Do:** Download these into `docs/` (gitignore the PDFs):
  - RM0390: STM32F446 reference manual
  - DS10693: STM32F446 datasheet
  - PM0214: STM32 Cortex-M4 programming manual
  - UM1724: Nucleo-64 user manual
  - ES0298: STM32F446 errata
  - The Nucleo-F446RE schematic
- **Done when:** You can answer these from the docs alone, with page or section citations, in `docs/NOTES.md`:
  1. Which MCU pin drives user LED LD2, and which solder bridge could change that?
  2. What are the base addresses of RCC and of that GPIO port?
  3. Which RCC register and bit enables the clock for that GPIO port?
  4. Where do flash and SRAM start, and how big is each?
  5. After reset, what clock source is the core running from, and at what frequency?
- **Read:** Skim the RM0390 memory map chapter, the RCC chapter intro, and the GPIO chapter. Interrupt blog: *From Zero to main(): Bare metal C*.
- **Log:**

## Backlog: Phase 1, Blinky from scratch

### BTB-010 · Makefile + zig cc skeleton · est 2–3 h
- **Done when:** `make` builds `build/blinky.elf`, `.bin`, `.map` and a `.lst` disassembly for `thumb-freestanding-eabihf` / `cortex_m4`. `make clean` works. `CC` can be overridden (for example `make CC=arm-none-eabi-gcc` should at least try). Strict warnings are on, using `-Werror`. `compile_commands.json` is generated for clangd.

### BTB-011 · Linker script + vector table + infinite loop · est 3–4 h
- **Done when:** You flash with OpenOCD from a `make flash` target. After reset, GDB shows the PC in your `Reset_Handler` and the SP equals the top of SRAM. You can explain every line of the linker script without notes.

### BTB-012 · Ugly blinky · est 2 h
- **Done when:** LD2 blinks using raw addresses and a busy-wait loop, all in one file. Then answer: why does your delay loop change speed between `-O0` and `-O2`, or disappear entirely?

### BTB-013 · .data / .bss init + your memcpy/memset · est 2–3 h
- **Done when:** An initialised global and a zeroed global both hold the right values, verified in GDB before and after `Reset_Handler` runs. You've found in the `.map` file whatever zig links implicitly (compiler-rt?) and written it down.

### BTB-014 · Hand-written PAC: RCC, GPIO · est 3 h
- **Done when:** You have register structs with `_Static_assert` offset checks against RM0390 and named bit-field macros. Blinky has no magic numbers left.

### BTB-015 · Thin HAL: rcc + gpio · est 3 h
- **Done when:** `gpio_init`, `gpio_write` and `gpio_toggle` exist. The API knows nothing about register layout. The PAC knows nothing about the API.

### BTB-016 · SysTick interrupt + delay_ms · est 3 h
- **Done when:** You have an accurate 1 ms tick driven by the interrupt, and `delay_ms(500)` blinks at a measured 1 Hz. FPU enable (CPACR) is in startup, and you can explain why it has to be there.

### BTB-017 · Fault handler · est 2 h
- **Done when:** You deliberately cause a HardFault and catch it in your handler. In GDB you decode CFSR/HFSR and the stacked PC to find the faulting line.

### BTB-018 · ⭐ Milestone 1 review · est 2 h
- **Done when:** You've written a README covering the build, the flash steps and the memory layout, and done a retro (what was hard, what you'd change). Then run `/submit BTB-018` for a full code review.

### BTB-019 · (Stretch) 180 MHz via PLL · est 3–4 h
- **Done when:** The core runs from HSE/PLL at 180 MHz with over-drive enabled and the correct flash wait states, and SysTick is still accurate. Explain what breaks if you get the order wrong.

## Later (epics, broken into tickets as we get close)

- **Phase 2:** UART driver, interrupts, SPSC ring buffer, your own `printf`-lite
- **Phase 3:** Bootloader, plus a host-side flasher in C (image header, CRC, VTOR, jump)
- **Phase 4:** Host-side unit tests for the HAL, and CI
- **Phase 5:** Tiny preemptive scheduler (PendSV context switch)
- **Phase 6:** ESP32-S3 with ESP-IDF + FreeRTOS

## Done

_(nothing yet)_
