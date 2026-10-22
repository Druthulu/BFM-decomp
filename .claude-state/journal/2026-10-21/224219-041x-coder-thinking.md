---
ts: 2026-10-22T04:42:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_CxBE5VaaUDW7EkxC2gvW
---
x1 = 9 (same as nopin) — the short temp didn't produce the copy either (probably the truncation cost insns but the score stayed 9).

x5 = 10 with 42 ins (the s16 temp used for both tests → extra extension insns).

Let me look at x1's diff to see what the short temp did. Actually, time is limited (22:55; started 22:23 → 32 min). I need to wrap up this item soon: the rule is 20-30 min per item, ≥20 min and ≥30 scored tries for a WALL.

Tries so far in this session: 8 (w1-w8) + 6 (x1-x6, one failed compile) + nopin + win.c = ~15 new. Plus the 34 earlier tries = 49 total ≥ 30 ✓. Wall time ≥ 20 min ✓ (32 min).

But before declaring a WALL, let me try a couple more high-value ideas, because a MATCH is the goal:

Idea A: The `move v1,v0` copy is the copy of the call result into the pseudo. In the target, the call-result pseudo is in v1. What if the call result is used in a context that requires a 64-bit comparison? no.

Idea B: What if the call's result is consumed by a call argument? e.g. pass `ret` to another function → the arg setup would move it to a0 (a copy). But that changes the code (an extra call).

Idea C: What if the value returned by the call is assigned to a variable and the variable's address is compared? no.

Idea D (promising): make the call result pseudo conflict with v0 by making ANOTHER pseudo live in v0 at that time — specifically the RESULT_DECL! If the RESULT_DECL is live across the call... it's the returned value, live from its def. If we define the RESULT_DECL before the call — e.g. by an early `return`:

```
int func_8014FD54(int param_1)
{
    ...
    if (param_1 == 0) return 0;   /* changes semantics! no */
```
Not allowed semantically.

Hmm, but what about a `goto`/label structure? Hmm.

Idea E: what if the call result is assigned to a variable that is live across the call but whose value is not needed after the call → then it's dead → no.

Idea F: reconsider — maybe the copy isn't of the call result but the RESULT_DECL's copy! Look at the target again: ins 24 `move v1,v0` right after the call. What if the original source was:

```
ret = func_80133784(1, buf1, (int)buf2);
result = ret;        /* result is the pinned $2 pseudo?? no, result is assigned 0 later */
```
Hmm, `result` is assigned 0 in the branches, so `result = ret` would be dead.

What if the original had:
```
v = func_80133784(...);
if (v != 0) { ... }
```
where `v` is a variable that ALSO gets the result of the boolean? no.

Idea G: What if the call result is compared with a CONSTANT using a different instruction, requiring the value in a specific reg? no.

Idea H: Look at the moves file for similar MATCHes: "pin | func_8017EEB0 | MATCH — the first call's result moves to its own var w (2 uses); the stored value keeps the short live range and wins $2, the pin is gone (G06)". Here the goal was the opposite (the value wins $2).

"pin | func_8017CE7C | MATCH — do-while(0) around the tail gives the byte temp a loop-shaped live range, so local-alloc ranks it above the ret0 copy and it wins $2".

So the general mechanism to win $2: make the pseudo's live range SHORTER (higher pri = refs*2^floor(log2 refs)/live).

For us, the pseudo that must win $2 is the local `result` (r74, pri 11428, refs 4, live 7). But r74 conflicts with v0 because the call result (r84) holds the hard reg v0 in [24..26].

So the call result's HARD REG is the problem: local allocnos with hard regs are assigned first, and global allocnos avoid them.

Can we make the call result NOT have the hard reg v0? In gcc, the call's return value pseudo is a "call result" pseudo; local allocation gives it the hard reg because of the call's output constraint. The pseudo is the "call" insn's output... Actually in gcc 2.7.2, the call insn's output is a pseudo with a hard reg preference (v0) — call it r84. It's live [24..26] (the call's output is the pseudo; the hard reg v0 is the "return reg" of the call).

Hmm, actually in gcc 2.7.2 the call insn is `(call (reg 0 v0) ...)`, i.e. the output is hard reg 0 (v0) directly! Then the pseudo r84 (the copy of the call result) is a separate pseudo that copies v0 → r84. But the table shows r84 with hard reg v0 — meaning r84 IS the call's output pseudo with the hard reg v0.

So the call's result pseudo r84 = hard reg v0, live [24..26] (2 insns: the call at 22-23 and the use at 26? live 2).

Since r84 has a hard reg, it's assigned in local allocation and can't be displaced... unless global allocation can spill it? In gcc's IRA-less global/local allocation, local allocnos with hard regs are fixed.

Hmm! But wait: the target has the call result in v1 with the copy `move v1,v0`. So in the target, the call's output pseudo is v1?! That means gcc 2.7.2's call insn output can be a non-hard-reg pseudo when the hard reg is unavailable (i.e. when the call's return value must be moved). Actually in gcc, `expand_call` creates the call with output = a pseudo, and the "call" pattern requires the output to be in a register; the RTL for a call is `(call (reg 0 v0) ...)`. If v0 is occupied/conflicting, gcc copies.

In the target, the copy `move v1,v0` is exactly the pattern of "the call's return value must be moved out of v0 because v0 is reserved". In the pinned version, v0 was reserved by the pinned `result`.

So the question stands: how to reserve v0 ($2) lever-free.

Since the RESULT_DECL prefers v0 (it's the return reg) — in the direct-return form (win.c) the RESULT_DECL gets v0 but only from ins 27. The call result (r84) has the hard reg v0 from the call.

Hmm, so the RESULT_DECL and the call result coexist in v0 at different times ✓ (that's win.c, score 6).

To make the call result get a copy, the RESULT_DECL must be live AT the call. The RESULT_DECL is live from its first def. Its first def is at a `return` statement. So we need a `return` statement BEFORE the call!

Semantically we can't return before the call... unless the early return is unreachable-ish but still semantically equivalent? E.g.:

```
if (param_1 == 0) return 0;   /* NOT equivalent */
```
No.

BUT: what about a return statement that is always false but the compiler doesn't know? E.g. `if (0) return 0;` — gcc folds it → no effect on the RTL. What about a condition gcc can't fold but that is always false at runtime? That changes semantics (though unreachable in practice, the compiler would emit the branch → extra insns).

Hmm, what about `if (buf1[0] != 0) return 0;`? buf1[0] is set to 0 → gcc knows it's 0 → folds.

Hmm, the RESULT_DECL live across the call → gcc would move it to a callee-saved reg → the prologue changes (sw s1) → mismatch. So even if we could, it'd break.

Hmm, unless the RESULT_DECL's live range across the call is short...

OK, let me think about the target's ACTUAL structure once more. In the target:
- $2 (v0) at ins 24: the raw call result (dead after the copy).
- $3 (v1): the call result pseudo (r84-like) — the tests use it.
- $2 (v0) from ins 28: the value (result).

The pinned `result` pseudo is in $2 and is live from ins 28 (its first def is `result = 0` in the then-branch at ins 28) — wait, in the target the `move v0,zero` at ins 28 IS the `result = 0` (then-branch) — hmm, no: ins 28 is in the delay slot of the mask-test branch, so it's the "mask==0 → result = 0" path.

Actually the pinned `result` pseudo's live range: [28..34]. And the call result's pseudo is live [24..26]. So they DON'T overlap! Yet the call result is in $3 and $2 was free at [24..26].

So why didn't the call result take $2 in the pinned version? Because in the pinned version, the pseudo `result` is HARD-REG v0 for its whole live range, but even so, the call result (live [24..26]) doesn't overlap with it ([28..34])...

Unless the pinned pseudo's live range is considered to start at the function entry! A `register int result __asm__("$2")` with a hard reg — gcc's local allocation assigns it reg 2, and the conflict graph marks reg 2 as unavailable to OTHER pseudos that are live at ANY point where the pinned pseudo is live. If the pinned pseudo's live range were [24..34] (starting earlier), the call result would conflict.

Hmm, or maybe: in gcc's local allocation, a hard-reg pseudo conflicts with ALL other pseudos that want that reg — i.e. the hard reg is reserved globally for that pseudo (not just in its live range). That's what the notes said: "the hard reg $2 is reserved for the whole function".

So the lever-free equivalent: we need a pseudo that is assigned the hard reg v0 and reserved for the whole function. Which pseudo could that be lever-free? A pseudo with a hard-reg preference that wins v0 and is "reserved" — the RESULT_DECL! The RESULT_DECL prefers v0. But the RESULT_DECL is only live [27..].

Hmm, but in gcc, the RESULT_DECL's preference for v0 doesn't reserve it globally.

Hmm, hmm. But WAIT: what if the local `result` variable in the source is the RESULT_DECL itself? I.e., what if the function's return value is assigned DIRECTLY without a copy — e.g. by using a construct where the variable IS the return slot?

In gcc, there's an optimization where the return value is computed directly into the RESULT_DECL. But our local `result` is a separate variable.

Hmm, what if the function is written to return the variable directly in a single return statement, and gcc 2.7.2's "return slot" (the local `result` IS the return slot)? gcc 2.7.2 doesn't have that.

Hmm, BUT: what if we make the local `result` the RESULT_DECL by declaring the function's return... no, the body is fixed as `int func_8014FD54(int param_1)`.

Hmm, hmm. What if the local variable is declared with the SAME name as... no.

OK: alternative approach — maybe the ROM's `move v1,v0` copy isn't a call-result copy at all but the copy of a variable assignment. Consider the source:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) { ... }
```
with `ret` being... hmm, what if the ORIGINAL source was:

```
v = func_80133784(1, buf1, (int)buf2);
if (v != 0) {
    if (v & 0x8000) { ... }
}
```
Same thing.

What if the original had TWO variables: `ret` (the call result) and `x` (copied from ret)? The copy `move v1,v0` = `x = ret` — but then cse would merge it (as we saw). Unless x's copy escapes cse via a width change... which costs insns.

Hmm, what if x is used in a way that requires the 32-bit value while ret is 16-bit?? E.g. `ret` is s16 and `x` is int:
```
short ret = func_80133784(...);   /* truncation */
int x = ret;                       /* sign-extension */
if (x != 0) ...
```
→ extra insns.

OK, let me consider that the answer may be: this item is a WALL. But before that, let me try two more cheap ideas:

Idea 1: `ret` declared as `unsigned int` and the mask test `(ret & 0x8000)`. Tried ("unsigned int ret" = 6).

Idea 2: What if the call result is compared using an unsigned test `if ((unsigned)ret != 0)`, changing the test to `sltiu`? The ROM uses `beqz` → signed/zero test.

Idea 3: What if the two tests are on the SAME expression so gcc computes `ret & 0x8000` once? Currently the andi is in the delay slot ✓ (matches the target's shape).

Idea 4 (NEW): what if `result` is declared as a REGISTER variable... no, that's the lever.

Idea 5 (NEW): What if the value is returned via a helper: `return result ? 1 : 0;`? Changes the code.

Idea 6 (NEW): the "loop shape" lever! From the moves: "do-while(0) around the tail gives the byte temp a loop-shaped live range, so local-alloc ranks it above the ret0 copy and it wins $2". Hmm — a do-while(0) around the tail could give the `result` pseudo a different live range. The brief allows `do{}while(0)` only with `// !FAKE: do-while`.

Interesting: the local-alloc (not global) ranks pseudos. In our case r74 (the local `result`) is a GLOBAL allocno (it's in the .greg order line) — because it's live across... hmm, r74 conflicts v0,sp and has pri 11428 — it's in the order line "74 73" → global allocation handles r74 and r73 (the local `result` and the RESULT_DECL), while r80/r82/r84 (the call results) are local allocnos with hard regs.

So the local `result` is a global allocno because it's live across a CALL? No — r77 (s0, param_1) crosses a call. r74 crosses... hmm, "crosses 1 call" is noted for r77 and r72. r74 doesn't cross a call. Why is r74 global? Because it conflicts with the hard regs? In gcc, a pseudo that conflicts with a hard-reg pseudo (or has a hard-reg conflict) is allocated globally. r74 conflicts v0 (the call result's hard reg) → so r74 must be in global allocation (to avoid v0) → global allocnos are allocated after local ones, and they avoid the hard regs.

So the KEY: r74 (the local result) conflicts v0 because the call result r84 holds v0 in [24..26] and r74 is live [25..33] → overlap at [25..26].

If r74's live range started AFTER ins 26 (i.e. after the call result dies), there'd be no conflict with v0 → r74 could get v0! But then the value would be in $2 from ins 27 on ✓ and the call result would still be in $2 (v0) at [24..26] with the tests on $2 → no copy → back to score 6.

ARGH. The copy requires the call result to be in $3.

Hmm, so: the copy `move v1,v0` requires the call result pseudo to be in v1 — i.e., the call's OUTPUT pseudo must not be the hard reg v0. In gcc 2.7.2, the call insn's output is always hard reg v0 (`call (reg 0 v0)`). But the ROM shows the call result in v1 with a copy — so the copy is from the call's hard-reg output v0 into a pseudo r84 (in v1).

In gcc's RTL after expand: the call insn is `(call (reg 0 v0) (mem ...))`. Then the pseudo r84 (the variable `ret`) is set from v0 via a copy: `(set (reg r84) (reg 0 v0))`. Then reload/alloc: r84 gets a register; if r84 is allocated v0, the copy is deleted (coalesced); if r84 gets v1, the copy `move v1,v0` remains.

In the table, r84 is listed with hard reg v0 — hmm, so r84 IS the hard-reg pseudo. And the other call results r80, r82 similarly.

Hmm, so which pseudo holds the call result in the target? In the target, the call's result is in v1 at ins 24-26. So the pseudo holding it is in v1 — that pseudo must be r84 (if r84 is the pseudo for `ret`) — but the table says r84's hard reg is v0.

Hmm, the table's "hard" column comes from the .greg "Register N in M." lines or the order line. The dump's lreg table gives "Register 84 used 2 times across 2 insns" etc.

The three v0-hard pseudos (r80, r82, r84) with refs 2, live 2: these are the three calls' results. But two of the calls (func_80149290) return void... their "result" pseudos are unused. Hmm, refs 2 live 2 for all three.

Wait, maybe r80/r82/r84 are the ARGUMENT setups? Hmm.

Let me look at the .lreg dump section for the function directly to see the pseudo list with their roles. Actually the alloc_table output is what it is.

Hmm, let me think about it differently: the call result pseudo for the third call has refs 2 (the def from the call + ...). Live 2 (ins 24-26).

In the target (pinned), the notes said the call-result pseudo had pri 11428 refs 4 live 7 — that's the PINNED dump. Hmm, refs 4 live 7 — that looks like the local `result` in my nopin dump (r74: refs 4, live 7, pri 11428). Coincidence? The notes' "call-result pseudo (refs 4, live 7 → pri 11428)" might actually be r74 = the local `result` (they mislabeled it). Hmm, but in the pinned version, r73 = pri 7500 refs 3 live 4 = the RESULT_DECL, and r74 = pri 11428 = the local `result` (which in the pinned version is the hard-reg pseudo...). Hmm, a hard-reg pseudo wouldn't be in the .greg order line.

OK whatever. Let me try the empirical route with the dump: dump the PINNED version (orig.c) and compare the allocation tables (pinned vs lever-free). That tells me exactly which pseudo holds $3 in the target and what its pri/refs/live are, and hence what to change.

That's the decisive experiment. Let me do it: dump orig.c (with the pin) and read the table.

Time: 23:00. This is worth it.
