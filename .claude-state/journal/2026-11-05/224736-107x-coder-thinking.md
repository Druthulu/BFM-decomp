---
ts: 2026-11-06T05:47:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_k9zNDpUqL01i9RMDfGHO
---
The target case 0:
```
81f8 jal func_800291B4
81fc li a0,214
8200 andi a1,v0,0xff      ← c = call & 0xFF  (c in a1)
8204 beqz a1, 8224        ← if (c != 0)
8208 andi v0,a1,0x1       ← (c & 1) — reads a1
820c lui s1 ...
...
8224 addiu a1,a1,1        ← c++  (a1)
8228 andi v0,a1,0xff      ← (c & 0xFF)
```
So c lives in a1 across the case. The call result is v0.

Without the launder, cse folds `c = (raw & 0xFF)` and `(c & 1)` into `andi v0,v0,1` reading the raw result (v0). So c never gets its own register.

So we need c to be a distinct pseudo from the call result. Plain C: `c = func() & 0xFF;` — the AND result is a new pseudo anyway (reg). But cse knows c == raw & 0xFF and substitutes `raw` into `(c & 1)` → `(raw & 0xFF) & 1` → `raw & 1`. So the AND is folded.

How to prevent? The mask must be "opaque". A real C 2nd set of c: e.g., `c = c;`? deleted.

Hmm, what if c is `u8`? Then the AND result is truncated to QI — a real conversion. `c & 1` on a QI variable: zero_extend(c) & 1. gcc would emit `andi v0,a1,0xff` (zero-extend) then `andi v0,v0,1`? Or fold: since c is QI, zero_extend(c) & 1 = c & 1 (the QI value in a register is 0..255, and the register holds the zero-extended value... hmm, if the register holds the QI value, the upper bits are undefined? No — for a QI variable in a register, gcc's RTL uses subreg; the register's upper bits may be garbage. To use it as SI, gcc must zero-extend (andi 0xff). But if gcc knows the value came from an AND 0xFF, it knows the upper bits are 0.

Hmm, tricky.

Let me look at what the pinned version's RTL looks like (the orig) to see the launder's effect, then think.

Actually, maybe a simpler lever: make `c` a *different type* like `s16` or `u16`, so the RTL has an HImode set that escapes cse.

Let me just try a batch of width variants on n3 (pin kept, launders removed):
- c as u8
- c as s16
- c as u16
- c as s32 with `c = (u8)c;` after
- c as s32 with `c &= 0xFF;` after

Let me test them and see which fixes the andi without breaking anything.

Note: `c` is used as `c++`, `c & 0xFF`, `c % 3` (case 1), etc. Changing c's width affects the magic division in case 1 (the comment says: "signed magic 0x55555556 => the modulo operand is a plain (signed) s32; a u8 c would let c-typeck's shorten do it unsigned (multu/0xAAAAAAAB)").

So c must stay s32 for case 1's modulo. Hmm, unless we use separate variables per case.

Actually, maybe the cleanest: keep c s32 but add a real 2nd set. What real 2nd set is value-preserving and not folded?

Idea: `c = (s32)(u8)c;` — a cast to u8 then back to s32. If gcc knows c ∈ [0,255] (from the & 0xFF), it folds to c. Hmm.

Idea: use a *separate* variable for the masked value: 
```c
s32 raw = func(...);
c = raw & 0xFF;
```
Doesn't help; cse still knows c = raw & 0xFF.

Idea: `c = raw; c &= 0xFF;` — a compound assign (2nd set). cse: c = raw, then c &= 0xFF → c = raw & 0xFF. Same knowledge. But the *first* set (c = raw) is a plain copy; combine may merge. Hmm.

Idea: `c = func(...); c = c & 0xFF;` — c is assigned the raw result, then masked. Then `c & 1` — cse knows c = raw & 0xFF, so it can substitute raw into (c & 1) → raw & 1. Same.

Hmm. The launder makes c an *opaque* value.

Real C opaque operations: memory (store/load), function call, volatile, asm. We can't add instructions.

Hmm, but maybe the QI/HI width trick works: if c is u8, then `c & 1` requires zero-extending c. gcc's RTL: (and:SI (zero_extend:SI (reg:QI c)) 1). cse can't fold the AND with the original `raw & 0xFF` because c is QI. It would emit... let me think: if c's register holds the QI value (from `andi a1,v0,0xff`), then zero_extend(c) is known to be the register value (since the AND cleared the upper bits — gcc knows from the set). So `andi v0,a1,1` — exactly the target!

And `c & 0xFF` in `func_800291A0(0xD6, c & 0xFF)` — for a u8 c, that's zero_extend(c) → no instruction if known. And `c++` on u8 → addiu + andi 0xff (the target has `addiu a1,a1,1; andi v0,a1,0xff` — wait, the target's `c & 0xFF` emits `andi v0,a1,0xff`). Hmm, so the target does have the andi for the c & 0xFF argument.

Let me look: `8224 addiu a1,a1,1; 8228 andi v0,a1,0xff`. So c++ then `c & 0xFF` → andi. With u8 c, `c & 0xFF` would be a zero-extend of a u8 — gcc might skip the andi if it knows the QI value... but the target HAS the andi. So c is s32 in the target.

Hmm. So c must stay s32 and the mask must survive.

OK, so what plain-C operation makes `c = raw & 0xFF` opaque to cse? 

The launder is a zero-byte asm. The catalog (moves.md) has several MATCHes replacing such launders with real 2nd sets. E.g., line 199: "dead copy vol2=vol + a 2nd def vol=vol|0x3000 (both dead in the RTL) give vol 2 defs". 

For our case: `c = func() & 0xFF;` — what if we do `c = func(); c = c & 0xFF;`? Hmm.

What about making the *function call result* go to a variable and the mask to c:
```c
s32 raw = func_800291B4(0xD6);
c = raw & 0xFF;
if ((c & 1) != 0) ...
```
cse still knows.

What if the AND is written differently: `c = raw % 256;`? For a signed raw, `% 256` is NOT the same as `& 0xFF` for negatives! The target has `andi` (unsigned mask). So `raw % 256` would emit a different sequence. No.

What if `c = raw & 0xFF;` then `c = c & 0xFF;`? The second is a real set but cse folds both into raw & 0xFF.

Hmm, what about `c = (raw & 0xFF) | 0;`? folds.

OK, the QI idea: what if we introduce a separate `u8` variable for the mask, then copy back to s32 c:
```c
u8 m = raw & 0xFF;
c = m;
if ((c & 1) != 0) ...
```
The RTL: m(QI) = subreg(raw & 0xFF) → `andi a1,v0,0xff`; c = zero_extend(m) → a copy from a1 to c's reg. If gcc coalesces c with m, then c is in a1 → `andi v0,a1,1` ✓ and `c & 1` reads a1.

Hmm, but c is s32 and m is u8; the copy c = m is a zero-extend which gcc folds to a copy (it knows m's upper bits are 0? Actually the RTL for m = (u8)(raw & 0xFF) would be (subreg:QI (and:SI raw 0xFF)) — and c = zero_extend(m) → combine may see c = and(raw,0xFF) again and fold... 

Ugh.

Let me just TEST a bunch of variants empirically. That's faster than reasoning.

Batch for the launder (on n3, pin kept):
c1: declare `u8 c;` (but case 1's c%3...)
c2: `s16 c;`
c3: `u16 c;`
c4: `c = (u8)c;` after each mask
c5: `c = (s16)c;` after each mask
c6: introduce `u8 m; m = ...; c = m;`
c7: `c &= 0xFF;` after

Let me test c4/c5 first (small changes, 3 sites).

Actually the mask sites are: case 0: `c = func_800291B4(0xD6) & 0xFF;`; case 1: `c = func_800291B4(0xD7) & 0xFF;`; case 2: `c = func_800291B4(0xD9) & 0xFF;`; default: `c = func_800291B4(0xD8) & 0xFF;`. But the launders are only in cases 0, 2, default (3 sites), not case 1.

So I need the anti-cse at those 3 sites.

Let me test:
d1: replace the 3 removed-launder sites with `c = (u8)c;`
d2: `c = (s16)c;`
d3: `c = c & 0xFF;`
d4: `c = (c & 0xFF) | 0;` (folds)
d5: `c = (u8)(c & 0xFF);`

Let me generate from n3 (launders removed, pin kept) by inserting after each `c = func_800291B4(0xXX) & 0xFF;` that originally had a launder.

Hmm, n3 has all 4 sites without launders. I'll insert at the 3 sites (D6, D9, D8).

Let me do it.
