# Homework 0: C Assessment

**Rules:** Parts A and B: from memory, no compiler, no search. "I don't know" or
"I think X because Y" is a perfectly good answer. Guesses are useful, so label
them as guesses. Part C: compile with `zig cc` as much as you like.

Time spent (rough): ___ h

---

## Background

- Years writing C: 3
- Last time you wrote C seriously, and what it was: A few months ago, it was a budget app that I started but never finished because I got hung up on implementing basic algorithms and data structures like hashmaps and arena allocators.
- Other languages you use day to day: C++ (but not day to day, I don't write code at my day job but I just miss doing it and I don't want to get rusty)
- Embedded experience (MCUs, RTOSes, tools, what you shipped): ESP32, ARM, FreeRTOS
- What you think your weakest area is: Just inexperience probably, I don't know if I know enough to know what I suck at.

---

## Part A: Concepts

### A1. `const int *p` vs `int *const p` vs `const int *const p`

>   1. A pointer to a constant int. The pointer can change as the int is copied around in memory, but you aren't allowed to modify the underlying int.
>   2. A constant pointer to an int. The address of the int can't change, but you are free to modify the underlying int.
>   3. A constant pointer to a constant int. Can't modify the pointer or the underlying int.

### A2. What does `volatile` guarantee, and what *doesn't* it? Is it enough for a variable shared between an ISR and `main`?

>   I think volatile guarantees that reads to a variable will not be discarded by the compiler during optimization.
>   It does not guarantee atomicity though, so its not good enough for a shared variable between main and an ISR.

### A3. The three meanings of `static`

>   1. A variable that has a single declaration/spot in memory (e.g. a global variable)
>   2. A function that only has one call site. 

I think I'm doing a bad job of explaining this though. I don't know the third.

### A4. Declaration vs definition. What does `extern` do?

>   A declaration is the symbol by the compiler and linker, often provided in the header file.
    The definition is the code or value for that symbol, for example a function prototype is declared in a header file,
    but the funciton is defined in the source file somewhere else. The linker puts the definition with the declaration.
    Extern means that the definition for that symbol comes from a source file not related to the current header i think?
    It basically means that some variable or function is defined elsewhere and there's only one definiton for it, so the linker
    needs to look elsewhere for it.

### A5. Which section does each end up in (`.text` / `.rodata` / `.data` / `.bss` / stack)?

I don't know 

| Code | Section | Why |
|---|---|---|
| `int a;` (file scope) |  |  |
| `int b = 5;` (file scope) | | |
| `const char *s = "hi";` (file scope): the pointer `s` | | |
| `const char *s = "hi";` (file scope): the string `"hi"` | | |
| `static int c;` (inside a function) | | |
| `int d;` (inside a function) | | |

### A6. What is undefined behavior? Three examples. Why does the optimizer make it worse?

>   Undefined behaviour is behaviour that the language provides no guarantees about. It could be a crash, it could be fine, who knows.
    Examples are dereferencing a null pointer, using a memory address after its been freed, and overflowing/underflowing a buffer by reading or writing outside its bounds.
    I don't know why the optimizer makes it worse, although i do remember reading an article about it at one point, someone was complaining to GNU about their undefined behaviour resulting from very reasonable code due to optimizations.

### A7. `uint16_t x = 0xFFFF; uint32_t y = x * x;` with 32-bit `int`: what's the problem?

>   I think this is undefined behaviour because you are storing the result of an operation with one type in another type with a different size.

### A8. `sizeof(struct { char a; int b; char c; })` on Cortex-M: what is it, why, and how would you shrink it?

>   I think the cortex m uses 32 bit integers, so sizeof is 12 bytes (3x4), I would shrink it to 8 by writing struct { int b; char a; char c;}

### A9. Everything you know about what happens between power-on and `main()`

>   Clocks are initialized, PC goes to reset handler, starts executing. That's all i know...

---

## Part B: Find the bugs

For each one, say what's wrong, what actually happens, and how you'd fix it.

### B1
```c
#define SQUARE(x) x * x
int r = SQUARE(a + 1);  // results in 2a + 1, expands to a + 1 * a + 1
```

>   I'd fix SQUARE by writing 

```c
#define SQUARE(x) (x) * (x)
```

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

>   You make the MSB of whatever is at address 0x40020014 1. Maybe you want this though if its a register... If you wanted this OR assignment operation to be applied to the integer 0x40020014, then I'd write

```c
uint32_t some_int = 0x40020014;
uint32_t *odr = &some_int;
*odr |= 1 << 31;
```

### B4
```c
for (uint8_t i = 0; i < 300; i++) { do_thing(i); }
```

> This loops forever since i is a byte, which will overflow to 0.  I'd write it as 

```c
for (uint16_t i = 0; i < 300; i++) { do_thing(i); }
```

### B5
```c
int len = -1;
if (len < sizeof(buf)) { copy(buf, len); }
```

>   I think this does some crazy copy because len is negative, but I'm not sure without looking up the copy function...

### B6 (`tick_count` is incremented in an ISR)
```c
volatile uint32_t tick_count;
void SysTick_Handler(void) { tick_count++; }
void main_loop(void) { if (tick_count >= 1000) { tick_count -= 1000; blink(); } }
```

>   I don't know

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

>   Static inline is prefered to macros, not sure why though

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

>   Can't do this

### C4 (stretch). Lock-free SPSC byte ring buffer: ISR writes, `main` reads (files: `ring.h` / `ring.c`)

Why is it safe without locks? When would it stop being safe?

>   I don't know how to do this without locks
