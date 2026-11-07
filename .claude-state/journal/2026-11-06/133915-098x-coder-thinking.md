---
ts: 2026-11-06T20:39:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kSk7NtUS3OtUSqTWMkX8
---
Baseline: score 7, 70 vs 69 insns. Residual:
1. `move a0,s0` missing at position 37 (mine has nop) — the target's copy at ed4c.
2. The stores use s0 instead of a0 (2 mismatches).
3. The `lhu a1,20(sp)` position: mine at 44, target at 43 (scheduling).
4. Mine has an extra `move a0,s0` at 45 (before the call) — the copy for the final call.

So: mine = 70 insns (extra move at the end), target = 69 (the move at ed4c is reused).

So the pin forced the copy early (ent=a0) and the compiler used a0 throughout, including for the final call (no extra move).

Real-C: make `ent` a separate pseudo that isn't coalesced with the parameter, so a copy is emitted at its definition and a0 is used as the base. Since the final call `func_80188650((void *)ent)` uses ent, if ent is in a0 the call needs no move (target: `jal; sh a1,14(a0)` with a0 already = ent).

The key: `ent` must be a distinct pseudo from a0's incoming value, and it must be allocated a0.

In the target, the copy `move a0,s0` happens at ed4c (right after the RotTransSV call), i.e., where `ent` is defined in the source. And a0 is used as the base for all subsequent stores.

Without the pin, `ent = (s32)a0` is copy-propagated: all uses of ent become a0 (the parameter, in s0). Then the final call needs `move a0,s0` in the delay slot (mine's extra move at 45).

To force a distinct pseudo: make the value assignment not a pure copy. E.g., `s32 ent = (s32)a0;` — pure copy. What about making `ent` a pointer: `u8 *ent = (u8 *)a0;` — still a copy.

What about `s32 ent = (s32)(a0);` with a cast — same.

What about using a union/bitfield? no.

What about `s32 ent = (s32)a0 + 0;`? folded.

Hmm. What about using `ent` in a way that makes it a distinct value: e.g., `ent = (s32)a0; ... ent += 0;`? folded.

What if we make `ent` an `unsigned` and do arithmetic? e.g. `u32 ent = (u32)a0;` — copy.

Hmm, the pin used `+ zr` where zr is a hard-register variable. Is there another way to get an opaque zero in plain C? 

- A function call returning 0: adds a call.
- A global variable that's 0: adds a load.
- `(s32)(a0 - a0)`? The compiler folds to 0 → copy.
- `(s32)a0 * 1`? folded.
- `(s32)((u32)a0 | 0)`? folded.

What about making the *value* not obviously a copy by using a different type size, e.g., `s32 ent = (s32)(s16)(s32)a0;`? Truncates → wrong value.

What about `ent = (s32)a0;` but declared `volatile`? Stack.

Hmm. What if we avoid `ent` entirely and force the compiler to use a0 by making the parameter itself dead after the entry? The parameter a0 is copied to s0 at the entry (move s0,a0) because a0 is used across calls. If the source used a0 directly (no copy), gcc still moves it to s0 because a0 is call-clobbered and used after calls.

The target's `move a0,s0` at ed4c exists because the source created a new variable ent that was allocated a0 (a call-clobbered reg, free at that point since no call intervenes until func_80188650).

Without the copy, the compiler could still allocate a *use* of ent to a0... but ent is copy-propagated away.

So the question: how to create a distinct pseudo from a0 without an addition? 

What if we make `ent` the result of a *function-like* expression? Hmm.

What about `s32 ent = (s32)a0;` followed by taking a different path? 

Wait — maybe we can use the do-while: if `ent` is defined INSIDE the do-while block, would that prevent copy propagation? cse1 sees the do-while as a separate EBB; ent's definition and uses might be in different EBBs, preventing copy propagation. But the definition must be before the uses. Let me try moving `s32 ent = (s32)a0;` inside the do-while:
```
do {
    s32 ent = (s32)a0;   // hmm, scope ends at the block
    ...
} while (0);
```
But ent is used after the do-while too.

What if we declare ent at the outer level and assign it inside the do-while?
```
s32 ent;
do {
    ent = (s32)a0;
    *(s16*)(ent+0xA) = v[1];
    t1 = *(u32*)(ent+0xC4);
} while (0);
...
```
Then the assignment `ent = a0` is inside the do-while block; copy propagation within cse1 might still replace uses. But the uses are also in the same block.

Alternatively, assign ent inside the do-while and use it after — then ent is live across the block boundary, and cse can't propagate it across blocks? cse1 works per extended basic block; if ent's def is in one EBB and its uses in another, copy propagation still works via the register (cse tracks values across blocks within an EBB). The do-while creates a loop structure that may block it.

Let me just try a few:
vA: `s32 ent = (s32)a0;` (baseline, 7)
vB: move the assignment into the do-while: `s32 ent;` + `do { ent = (s32)a0; ... } while (0);`
vC: `u8 *ent = (u8 *)a0;`
vD: `s32 ent = (s32)a0; ent = ent;`? no.
vE: `s32 ent = (s32)(a0 + 0);`
vF: `s32 ent; ent = (s32)a0;` as a separate statement before the do-while.

Let me also think about the third residual (lhu a1,20(sp) position): the target has `lhu a1,20(sp)` at ed64 (before the ori/sb), mine at 44 (after). The pin's effect on sched1? The do-while comment says "LOOP notes split sched1 so the li 1 / ori stay below the 0xC4 load". Hmm, the do-while is already there.

The target sequence:
```
ed54 lhu v0,18(sp)      ; v[1]
ed58 lw v1,196(a0)      ; t1 = *(u32*)(ent+0xC4)
ed5c sh v0,10(a0)       ; *(s16*)(ent+0xA) = v[1]
ed60 li v0,1            ; one = 1
ed64 lhu a1,20(sp)      ; v2 = v[2]? no, a1
ed68 ori v1,v1,0x2
ed6c sb v0,192(a0)
...
edb4 sh a1,14(a0)       ; *(s16*)(ent+0xE) = v2 (in the delay slot of the call!)
```
So a1 holds v[2] and is stored at the very end in the call's delay slot.

Mine: `lhu a1,20(sp)` comes after `ori v1,v1,0x2` (position 44 vs target 43). A scheduling difference of one slot.

Let me first fix the ent copy and see what remains.

Let me create the variants and score.
