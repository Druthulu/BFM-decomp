---
ts: 2026-10-22T01:01:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_LFlwdrqGpvyaO2m4m7eM
---
The pattern: "cast" at site 1 (v1) is needed; at site 2 (e) we need "dowcast" (which truncates the pointer — semantically wrong) or "dow" (score 2).

Since the cast on `e` truncates a pointer (semantically wrong), the faithful best is "cast-dow" = 2.

Hmm! What if the *cast* at site 2 could be value-preserving? e is a pointer (s32). A cast that preserves it: none (s16 truncates).

Hmm, what if the *e* site's replacement were a "real 2nd set" of e — e.g. `e = e;`? identity (forbidden, and folded).

What about a different *real* second set for e: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` (a re-load)? That's a real 2nd set (re-reading the field) — value-preserving at runtime (the field isn't modified in between) but the compiler may fold it (the same load) → hmm, but with the do-while in between... CSE would fold the re-load (the same address, no intervening store) → the same value → hmm.

Hmm, but maybe: the re-load + the do-while → GCC keeps the re-load? No, CSE folds it.

What about `e = e + 0;`? folded.

Hmm. So the e site needs the "dowcast" (truncating) to reach 1, which is semantically wrong.

Hmm, wait. Let me reconsider: is the (s16) cast on e *really* wrong? The value of e is a pointer (unk20). (s16)e truncates it to 16 bits. Then `*(s32 *)(e + 4)` uses the truncated pointer → a different address → WRONG. Yes, semantically wrong. So pg018/pg020 are not acceptable as cracks (even though they score 1).

Hmm, unless... the *target* itself has the `lh` load! I.e. maybe the original game code had a truncated pointer?! Hmm, no: the target's asm has `lw` (a word load) for e.

So: for this item, the faithful best is 2 (an ORDER difference of one instruction).

Let me try a couple more things for the ORDER difference:
- The `do-while` at the e site could be placed *after* the `argmode = 3;` line (statement order!).
- The cast at the v1 site could be placed elsewhere (e.g. right after `v1 = mode;` — that's where it is).

Hmm, the ORDER difference is about `li a0,409` (callarg0 = 0x199) placement. In the target it's at index 44 and in mine at 45.

Let me look at the target's asm around 40-50 to understand. Let me dump the target for D96C.

Actually, let me think about the *cause*: the delay-slot scheduling of `li a0,409`. The scheduler (sched2) places the `li` in a delay slot. The difference between mine and the target could come from the *number of instructions* in the block (the do-while adds a block).

Hmm! What if the do-while isn't needed at the e site? The combos with "none" at site 2: "cast-none" = 6. So the do-while at site 2 helps (6 → 2).

Hmm, what if the e site's replacement were a *different* kind of statement that adds a block without changing the value: e.g. a `do { } while (0);` vs an `if (0) { }`? Hmm, `if (0) {}` is folded at parse time. What about `if (e == e) { }`? Hmm, that's a real statement (a compare) but folded.

What about a `while (0) { }`? Folded? Hmm, `while(0)` is a loop with a constant condition → GCC removes it (but maybe not at gimplify time!).

Let me try a few alternatives for the e site: `while (0) { }`, `for (;0;) { }`, `do { e = e; } while (0);` hmm (identity), `if (1) { }` (folded).

Hmm, the empty do-while is the standard "block barrier" idiom. Let me try `while (0) { }` and `do { } while (0);` variants with different placements.

Let me also reconsider: maybe the ORDER difference is fixed by using the do-while at the e site *and* moving the `e = ...` assignment after it:
```
case1:
    func_8001C810(...);
    callarg0 = 0x199;
    do { } while (0);
    e = ((Unkstruct_800B5CB8 *)s0)->unk20;
    argmode = 3;
```
Hmm, that changes the order of the e assignment vs the do-while.

Let me generate a few such variants and score them. Let me do a focused sweep: variants of the case0/case1 blocks with the do-while in different positions relative to the assignments, plus the cast at the v1 site.

Let me write it.
