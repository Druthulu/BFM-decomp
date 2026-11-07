---
ts: 2026-11-06T16:54:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y7COA5Kw3wkAQhsmZYJs
---
Score 12: n is in v1 instead of s0 ($16). The target wants n in s0. Both computations use n; in mine n got v1 (a caller-saved scratch), target s0 (callee-saved $16).

Why does the target keep n in s0? Because n's live range crosses a call? Look at the code:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
m = (q - n) << 16;
if ((rand() & 1) == 0) m = -m;
```
n is used before the second rand() call; it dies at `m = (q-n)<<16`. So n's live range doesn't cross a call. Yet the target has it in s0 ($16) — a callee-saved register. That's odd unless n is *not* dying and the register is reused later... but s0 is used for the second computation too.

In the target, n = s0 in both computations (14 uses). So the target allocated n (or the common temp) to s0. Without the pin, local-alloc gives v1 (a scratch, since n dies within the block).

Hmm. But if n is a single variable used twice (both computations), its live range spans from the first computation to the second (with a call in between: rand()). Actually the variable n is assigned in computation 1, then reassigned in computation 2. If the compiler treats it as one variable live across the whole span (from first def to last use), it would cross the call and go to a callee-saved register (s0). But local-alloc/global-alloc might split it.

In the current source, n is declared at function scope and used in both computations. The compiler's variable n has a live range covering both. Yet without the pin it got v1, meaning the allocator treated the two uses as separate (dead between). Hmm, why? Because the two computations are in different basic blocks? No, straight-line.

Wait, maybe the issue: after the first computation, `m` and the second `rand()` call. n's value from computation 1 is dead after `m = (q-n)<<16`. Then n is redefined in computation 2. The variable's live range is split by the redefinition (it's dead between). local-alloc assigns per-block; if n dies and is reborn in the same block, local-alloc may reuse the same register (v1) for both.

The target keeps n in s0, meaning in the target's RTL, n is ONE pseudo live across the call (from the first def to the last use) — no redefinition in between? Or the target's n is the same pseudo and local-alloc/global-alloc... 

Actually, the pin forced n to $16 for BOTH computations. So the target's n is a single pseudo covering both computations (live across the rand() call). If the compiler splits the live range at the redefinition, each part could take a scratch. But local-alloc's `local_alloc` handles pseudos per block: a pseudo that is set twice in the same block with a dead gap... The pseudo's life is computed by `reg_live_length` and it's one allocno; local-alloc assigns one register for the whole block if it fits, else splits? In GCC 2.7.2 local-alloc can split a pseudo's live range (`local-alloc.c` "We can split the register if..."). Hmm.

The target's n in s0: this is what happens when the pseudo is live across a call — it must be callee-saved. In mine, n got v1, so the allocator decided it doesn't cross the call.

So we need the real C to make n one value live across the rand() call. How? If the source had:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
m = (q - n) << 16;
```
n is dead after the last use. The second computation redefines n. So there IS a dead gap. Unless the original source used the *same* n without redefining (impossible, different value).

Wait, maybe the target's original had n as a variable that's *not* redefined: e.g. the second computation uses a different variable, and the pin applied to one of them? The pin is on n only; the target shows s0 for both computations (14 uses). The pin forced n to $16; the second computation also uses n (same variable) — so the compiler kept n in s0 across both.

If we remove the pin, the compiler can split n into two ranges (v1 each). To prevent the split, we could make n live across the call: e.g. keep n's value alive after the first computation (use it later)? That changes code.

Alternatively, the real C might have declared n inside... hmm.

Let's think about what the original source likely was: maybe n wasn't a single variable; maybe the decompiler's source used one variable and the original used a different structure. The pin was introduced by a previous coder to force s0.

What real C move makes local-alloc keep n in s0? The wall tags include "lreg-qty-priority", "lreg-v0-local-first", "lreg-copy-pref-dying-base", etc.

Let me look at the target's full instruction stream to understand the register roles. Target uses s0 for n and v0 for q. Let me read target.s.
