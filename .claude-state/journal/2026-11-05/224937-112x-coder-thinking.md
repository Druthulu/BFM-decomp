---
ts: 2026-11-06T05:49:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xgGM0IOL8G4CQeiXk4WA
---
Global alloc: regs 72 (a0) in 16, 73 in 2, 74 in 2, 75 in 17, 76 in 4, 77 in 5, 98 in 64, 104 in 2, 113 in 16.

Interesting: 73 and 74 are in $2 with "preferences: 2". 76 in $4.

So which is v? Let me look at the RTL to identify. reg76 in $4 = a0 — that's likely v (the early-return pointer). It conflicts with 72 (arg a0), 2, 3, 29.

Hmm, and 73/74 in $2 are... the return pseudo(s)? "73 preferences: 2" means reg73 prefers $2 (the return value).

So the RETURN pseudo (73) is in $2, and v (76) in $4. The return pseudo has preferences for $2 (from the function return).

In the target (pinned), v is $2, so the return copy is free.

Without the pin, v is $4 and the return pseudo is $2 → `move v0,a0`.

Why does v get $4? global_alloc assigns by priority. v (76) conflicts with 72 (a0), 2, 3, 29. Its priority vs others...

Hmm. Note "73 in 2, 74 in 2" — two allocnos in $2? They must not conflict (73 and 74 conflict list: 73 conflicts 72,73,29; 74 conflicts 72,74,29 — so 73 and 74 don't conflict with each other → both in $2). Those are probably the two return-value pseudos (early return and final return).

So the structure: the early return's value pseudo (73) is in v0, the final return's (74) in v0, and v (76) in a0.

The target wants v in v0 directly (so the early return's value IS v).

Hmm, how does gcc create a separate return pseudo? For `return v;`, the RTL is `(set (reg:SI 73) (reg:SI 76))` then `(use (reg:SI 73))`. Wait, in gcc 2.7.2, the return statement does `(set (reg:SI <return>) (reg:SI v))`. If v and the return pseudo are coalesced (same reg), the move disappears.

So the question: why isn't v coalesced with the return pseudo (73)? global_alloc's `qty_phys_copy_sugg`/preferences: 73 prefers $2. v (76) could take $2 too if it doesn't conflict with 73... but they DO conflict? The conflict lists show 76 conflicts with 2, 3, 4, 29, 72 — not with 73. Hmm, 76's conflicts: "72 76 2 3 29". So 76 conflicts with 72 (the arg), $2, $3, $29. But 73 is in $2 and 76 conflicts with $2 (hard reg 2) — that means 76 conflicts with the *hard reg* 2, i.e., with any allocno in $2? No — the conflict list includes hard regs that the allocno conflicts with: 76 conflicts with hard regs 2 and 3 (because 76 is live across a call? no...). Hmm, hard regs 2,3 are caller-saved; an allocno conflicts with a hard reg if it's live across a call (the call clobbers $2/$3).

76 conflicts with 2 and 3 → it's live across a call! So v is live across a call → cannot be in $2/$3. That's why it goes to $4.

Wait, but the target has v in $2 across... hmm, the target's v is only live in the early-out (no calls after the pointers are set). Let me check: v is set after the cond computation (which has calls). So v shouldn't be live across a call.

Unless the *merge* of the two return paths makes v's live range extend across the switch calls? No, v is only on the early-out path.

Hmm, but global_alloc is conservative: if v is live across a basic block boundary and any call... no, liveness is precise.

Hmm, the conflict with hard regs 2/3 could come from a different reason: REG_ALLOC_ORDER or the function's call clobbers. Actually, in gcc, every allocno that is live across a call conflicts with the call-clobbered hard regs. If v isn't live across a call, no conflict.

Let me look at the RTL to understand. Let me find the v-related insns.

Actually, let me look at this from a different angle: maybe I can restructure the source so that the early return doesn't create a separate return pseudo — e.g., by making the early-out the LAST thing (fall-through return) or by using a single return at the end.

Alternatively, make v's qty prefer $2 via a copy hint: e.g., `v = (s32)&D_801922A0;` — the address materialization... 

Hmm, what about `return (s32)v;`? Same.

What if v is the *function's return value directly* via a different code shape: put the early return's value into `result` and use a single return at the end:
```c
result = ...;  // switch
...
return result;
```
and for the early-out: `result = ptr; ...; return result;`? That merges the returns into one variable. Hmm, but the target's early-out returns directly.

Let me look at the RTL first. Let me dump the .rtl around the early-out and identify the pseudo numbers.

Let me find "D_801922A0" in the rtl.
