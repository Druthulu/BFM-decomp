---
ts: 2026-10-22T20:35:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kJfEBk1mNULZVEG3ywZu
---
Wall it. Time is over budget for this item.

Wait — before walling, let me reconsider whether w1's 2 could be fixed by making the *second and third* call args differ in a way reload must rematerialize: e.g., if the address were not in a1 but the value had to be loaded... 

Actually, one more thought: the target's 3 addiu means the address pseudo was spilled and rematerialized. In w1, the address is in a hard reg. What if I use the pinned src for the source copy (giving the a1 base) and then *never* use src again, with the calls using `(void *)m`? That's w4 → 19 (dest pseudo). The dest pseudo r69/r80 is the blocker.

What if the movstr is generated with a dest that is *not* r69 but the hard reg, while the calls use the constant:
```
src = (int *)m;
*(Mat32 *)src = D_800AE620;
src = (int *)m;   (unused, removed)
RotMatrixX(..., (void *)m);
```
The dest is a1 → stores at 0(a1)... but the calls use the constant fp+16 → addiu per call. The stores differ from the target (a1-based vs sp-based). 8 diffs. Score maybe 16. Worse than 2.

Hmm, but would reload turn `sw v0,0(a1)` into `sw v0,16(sp)`? No.

Wall. Best = 2, tag `reload-hardreg-call-live`.

Hmm, actually let me name the tag more precisely: the target rematerializes the constant address in each call's delay slot; w1 keeps the pinned $5 (=a1) value live across the calls, so calls 2-3 get `nop`. Tag: `reload-fixedreg-across-call`. Or reuse `sched1-argcopy-hoist`? No. It's a reload/flow mechanism: the register-asm variable's hard reg is assumed preserved across calls. Let me call it `reload-hardreg-across-call`. New tag, lowercase, defined in the evidence.

Evidence (≤140 chars): "pinned $5(=a1) holds sp+16 across the 3 RotMatrix calls; reload never re-emits the const -> calls 2-3 delay slots nop (target addiu a1,sp,16); no $5 pin -> cse reuses movstr dest pseudo s1 (19); best 2".

Let me now write notes.md and the results row, then move to func_8012C750.

Actually, hold on. Let me reconsider one thing: the target's calls 2,3 have `addiu a1,sp,16` — reload rematerializing. If the address pseudo were *spilled*, reload would emit the addiu at each use. In w1 the hard reg isn't spilled. In c_struct the pseudo got s1 (local-alloc).

What if I make the address pseudo *multi-set and high-live* so global spills it? In score-0 the address was folded. In w8 it got s1.

Let me check the alloc table of w8 to see if I could push it below self's priority... In w8: 86 ins, s1 = address, s2 = self. The address pseudo (multi-set, 3 calls, live ~30?) beat self. If self's refs were higher, it'd win. Self's refs come from the C uses of `self` (param_1) — currently 9 refs. I could add refs to self by using it more... but that changes code.

Alternatively, reduce the address's live length: if the address pseudo were set right before each call and died at each call (3 separate pseudos), each would be local-alloc'd to a1 (no callee-saved). That's what the target does (3 addiu). But cse merges the 3 sets into one pseudo when the value is the same. In w8, the 3 sets became ONE multi-set pseudo? The alloc table would tell. If cse merged them into one multi-set pseudo live across calls → s1.

What if each set uses a *different* expression that cse can't equate? E.g., `mp = m;` for the first, `mp = &m[0];` for the second, `mp = (int *)m;` for the third — all identity spellings (disallowed) and cse folds them anyway.

OK, truly walling.

Now let me also think: is it legitimate to keep the $5 pin in the WALL body? The kinds row is `launder`; pins may stay. Yes.

Write notes.md and append the results row. Then move to func_8012C750.

Current time check needed. Let me get the date and write the files.
