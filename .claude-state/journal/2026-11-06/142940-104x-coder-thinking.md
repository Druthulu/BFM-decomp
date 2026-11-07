---
ts: 2026-11-06T21:29:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0oGmLGXvBeCmwAhvhers
---
Interesting! In target, s0 is used as a scratch for the rand() modulo sequences throughout the function (lines 30-36, 74-78, 90-94). So `n` is a single pseudo reused across all the modulo sequences, and it lives in s0 because... it's used across the whole function, spanning calls!

Look: the modulo sequences are at 77c (first rand), then 81c, 858, etc. `n` (s0) is used in each. But each sequence is separate; the variable n is reassigned. However, the C code declares `n` once at the top, and it's assigned multiple times. The compiler may treat it as one pseudo (same reg). Since it's used across the whole function (spanning calls), global-alloc assigns it a callee-saved reg (s0) because it's live across calls? But between uses, n is dead (reassigned). Actually n is dead after each modulo (m computed), then reassigned. So it shouldn't cross calls. But the compiler coalesced it into one pseudo.

Hmm, but the first modulo (line 29-36) is for the radius: `rand() % ((...*3)>>9)`? No wait, the first sequence at 77c is:
```
bgez v0; move s0,v0; addiu s0,v0,4095; sra s0,0xc; sll s0,0xc; subu s0,v0,s0
```
This is `rand() % 0x1000` (the first argument to func_8012B0B4). Actually `rand() % 0x1000`: q=rand(); n=q; if(q<0)n=q+0xFFF; n>>=12; n<<=12; result = q-n. Yes, that's the `rand() % 0x1000` in the source! But wait, the source writes `rand() % 0x1000` directly, not via n. The compiler expands `%` using the same pseudo as n? It reuses the register s0.

Actually, the C source has `rand() % 0x1000` (a compiler-generated modulo) AND the manual `n` modulo. The compiler may reuse the same pseudo/reg for both.

So in target, s0 is used for all modulo temps (compiler-generated and manual n). In mine, the compiler-generated modulo uses v1 (or v0) and the manual n uses v1 too. Hmm.

Wait, mine's diff showed v1 for the manual n sequences. What about the compiler-generated `% 0x1000`? Let me check mine's full asm. The diff only showed the manual n sequences differing (v1 vs s0). So mine uses v1 for n, target s0.

The pin forced n to s0, and apparently the compiler-generated modulo also used s0 (register pressure/allocation).

To crack: make n land in s0 without the pin. Since n is a global allocno (crosses blocks), its priority and the availability of caller-saved regs determine the choice. If caller-saved v0/v1 are busy, it goes to a callee-saved.

Idea: increase the live range of n so it crosses a call → forces callee-saved. But that changes code.

Idea: change the type of n to unsigned, so the `if (q<0)` sign-correction changes? No.

Idea: restructure the modulo to use `q % 4` directly? That changes the code (compiler uses magic or div).

Hmm. Actually, maybe the pin is REDUNDANT if we change how `n` is declared/used. The moves log line: "pin redundant" MATCHes exist. Let me search moves for "pin redundant" or similar on $16.

Line 15: "launder,pin | func_80180E40 | MATCH — pin redundant; u16 var_s4 + (u16)(var_s4 - 0x1000) < 0x11 keeps the andi (W02)". So pins can be redundant.

Let me try some real-C variants:
1. Declare n as the same type but move its declaration into a block? No, n is used across.
2. Make n `u32` — the `if (q<0)` with u32 changes (always false). No.
3. Compute the modulo differently: `m = (q % 4) << 16;` using the C % operator. That might generate the same sra/sll/subu but with a different temp. Let me test!
   `m = (q % 4) << 16;` — the compiler generates the modulo with its own temp. Target's sequence is exactly a modulo-by-4 (sra/sll/subu). So `q % 4` should produce the same instructions. And the temp might be s0.
4. Use `q & 3` instead of `% 4`? For negative q, & 3 differs from %4. But q = rand() which is non-negative? rand() returns 0..RAND_MAX, non-negative. But the code has `if (q < 0) n = q + 3;` suggesting q could be negative (rand() might return negative in this SDK?). Hmm, but target has the bgez check, so the compiler treats rand() as signed.
   If we write `q % 4`, the compiler generates the signed modulo (sra/sll/subu with the sign correction). That matches target! And no manual n variable. Let me test.

Let me try: replace the manual modulo sequences with `m = (q % 4) << 16;`. This removes the n variable entirely (removing the pin). Let me test both modulo sites.

Actually the source:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
m = (q - n) << 16;
```
This IS `m = (q % 4) << 16;` for signed q (C truncation toward zero: q - (q/4)*4). So replacing with `m = (q % 4) << 16;` is semantically identical. Let me test if it produces the target and gets s0.

Let me also consider the compiler-generated `rand() % 0x1000` already uses the same pattern. So using `%` for the 4s would be consistent.

Let me build win.c with `m = (q % 4) << 16;` and remove n. But careful: the source has TWO sites. Let me replace both.

Let me create win2.c.
