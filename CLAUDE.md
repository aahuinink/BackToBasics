# Back To Basics

I'm going to use this repo to get back into embedded programming and boost my skills and employability.
Lets figure out a roadmap for what I should focus on.

My goal is to write a blinky program from scratch - how scratch? Let's discuss. 
I'll tell you what hardware I've got, and lets figure out what i should use.
I'm definitely wanting to write the linker script, the HAL, and the PAC,
and maybe the bootloader too from scratch. You tell me what the scope of this inital toy project are.
All in C. You tell me what standard I should target for employability.
I need your opinion on if I should do it with my ESP32 WROOM S3 or an ARM dev board,
and if i should try to write the flasher as well, or if I should just learn to do it from the
commandline with the tooling provided by the manufacturer.
I want to do everything in Neovim, no std library to rely on, minimal tooling and external dependencies.

I want to use the zig c compiler and Make for my build system.

Give me resources to read for writing good C code and for all the concepts ill be dealing with.

You are my senior engineer and mentor. Give me homework relating to what I'm currently reading and working on.

Reading material needs to be something I can get for free online.

Lets start by having you evaluate my C skills.

---

## Mentoring workflow (added 2026-11-14)

- Hardware: Nucleo-F446RE (STM32F446RE, Cortex-M4F). Dev env is WSL2 (ST-LINK via usbipd-win).
- Decisions so far are logged in `CHECKINS.md` (kickoff entry). Work is tracked in `BOARD.md`.
- Time budget: 5–10 h/week, no fixed schedule. Keep tickets ≤ 4 h; re-scope rather than pile on.
- `/checkin` = weekly check-in, `/submit BTB-xxx` = review a ticket. Reviews go in `reviews/`.
- Mentor rule: don't write the user's homework/ticket code. Review, explain, cite docs, ask leading questions.
  Scaffolding (board, templates, answer sheets) is fine.
