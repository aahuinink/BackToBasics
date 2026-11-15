# Homework 0: C Assessment

**Rules:** Parts A and B: from memory, no compiler, no search. "I don't know" or
"I think X because Y" is a perfectly good answer. Guesses are useful, so label
them as guesses. Part C: compile with `zig cc` as much as you like.

Time spent (rough): ___ h

---

## Background

- Years writing C:
- Last time you wrote C seriously, and what it was:
- Other languages you use day to day:
- Embedded experience (MCUs, RTOSes, tools, what you shipped):
- What you think your weakest area is:

---

## Part A: Concepts

### A1. `const int *p` vs `int *const p` vs `const int *const p`

>

### A2. What does `volatile` guarantee, and what *doesn't* it? Is it enough for a variable shared between an ISR and `main`?

>

### A3. The three meanings of `static`

>

### A4. Declaration vs definition. What does `extern` do?

>

### A5. Which section does each end up in (`.text` / `.rodata` / `.data` / `.bss` / stack)?

| Code | Section | Why |
|---|---|---|
| `int a;` (file scope) | | |
| `int b = 5;` (file scope) | | |
| `const char *s = "hi";` (file scope): the pointer `s` | | |
| `const char *s = "hi";` (file scope): the string `"hi"` | | |
| `static int c;` (inside a function) | | |
| `int d;` (inside a function) | | |

### A6. What is undefined behavior? Three examples. Why does the optimizer make it worse?

>

### A7. `uint16_t x = 0xFFFF; uint32_t y = x * x;` with 32-bit `int`: what's the problem?

>

### A8. `sizeof(struct { char a; int b; char c; })` on Cortex-M: what is it, why, and how would you shrink it?

>

### A9. Everything you know about what happens between power-on and `main()`

>

---

## Part B: Find the bugs

For each one, say what's wrong, what actually happens, and how you'd fix it.

### B1
```c
#define SQUARE(x) x * x
int r = SQUARE(a + 1);
```

>

### B2
```c
char *get_name(void) { char buf[16] = "blinky"; return buf; }
```

>

### B3
```c
uint32_t *odr = 0x40020014;
*odr |= 1 << 31;
```

>

### B4
```c
for (uint8_t i = 0; i < 300; i++) { do_thing(i); }
```

>

### B5
```c
int len = -1;
if (len < sizeof(buf)) { copy(buf, len); }
```

>

### B6 (`tick_count` is incremented in an ISR)
```c
volatile uint32_t tick_count;
void SysTick_Handler(void) { tick_count++; }
void main_loop(void) { if (tick_count >= 1000) { tick_count -= 1000; blink(); } }
```

>

---

## Part C: Write code (freestanding, no libc)

Put the code in this directory. Suggested files are listed below; organise it
however you like. For each file, note how you compiled it. Something like
`zig cc -std=c11 -ffreestanding -Wall -Wextra -Wpedantic -c file.c` is enough.

### C1. `memcpy` and `memset` with their exact standard signatures (file: `mem.c`)

Notes or design decisions:

>

### C2. Bit set/clear/toggle/read on a 32-bit register, plus `reg_write_field(reg, pos, width, value)` (file: `bits.h`)

Notes: macros or `static inline` functions? Why?

>

### C3. Mini-PAC for the made-up GPIO at `0x48000000` (file: `gpio_pac.h`)

| Register | Offset | Access |
|---|---|---|
| MODER   | 0x00 | RW |
| OTYPER  | 0x04 | RW |
| OSPEEDR | 0x08 | RW |
| PUPDR   | 0x0C | RW |
| IDR     | 0x10 | RO |
| ODR     | 0x14 | RW |
| BSRR    | 0x18 | WO |

Requirements: a struct typedef, a `GPIOA` macro, a `_Static_assert` proving that
`BSRR` is at 0x18, and `IDR` marked read-only.

Notes:

>

### C4 (stretch). Lock-free SPSC byte ring buffer: ISR writes, `main` reads (files: `ring.h` / `ring.c`)

Why is it safe without locks? When would it stop being safe?

>
