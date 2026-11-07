---
ts: 2026-11-06T12:26:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QiGeYOThxlqPiEbNQeP6
---
The condition for our beqz: `get_branch_condition` returns the condition under which the insn branches to target — for `if (x != 0) call;` the beqz branches when x==0, i.e. condition is EQ → prediction 0 (rare_fallthrough==rare_dest probably, both inside loop) → prediction 0 → else branch → fall-through first (own_fallthrough) → fills `move a0,s0`.

If we could make the condition NE (prediction 1), reorg would try the target thread first. The branch at 221c is `beqz v0` = EQ condition. To get NE, the source would be `if (x == 0) { } else call;` → same beqz.

Hmm. What about the loop test `bnez v0` (NE → prediction 1): reorg tries target first there, and indeed target and mine both have `addiu s3,s3,32` in the bnez delay (from the taken thread = loop top? no, the fall-through is exit). Fine.

So for the if: we need the fall-through ineligible or the target chosen. In fill_slots_from_thread, there's `own_fallthrough = own_thread_p(NEXT_INSN(insn), NULL_RTX, 1)` — if the fall-through thread isn't "owned" (i.e., it's reachable from elsewhere, shared), reorg won't take from it. own_thread_p checks that the thread (the fall-through region up to the label) isn't entered elsewhere. If another branch jumps INTO the middle of the then-arm, the thread isn't owned → the fall-through can't be used → reorg tries the taken thread.

In target, is the call arm shared? The note said "the preceding beq then has to steal a second copy from the join at .L8017E028" — hmm.

Alternative: make the then-arm's first instruction ineligible via an intervening label target — e.g. an if/else structure where the arm is a join target from elsewhere.

Alternatively: get the increment copy in the delay slot from a different mechanism — cross-jumping? The `move a0,s0` is in the delay slot of the beqz in mine; the target has it before the jal (as part of the call setup) and the increment in the beqz delay.

Wait: in target, `move a0,s0` at 2224 and `jal` at 2228 with delay `move a1,s3`. In mine: `move a0,s0` in beqz delay at 2220, then jal at 2224 with delay move a1,s3. So mine has 1 fewer insn overall (the missing second addiu).

Approach: restructure the source so the increment is computed BEFORE the if in the taken path... Actually what if I write:

```
do {
    s32 nx = i + 1;
    if (...) { call; }
    i = nx;
    panel += 0x20;
} while ((s32)i < lim);
```
Then nx computed at loop top before the lh — no, that changes order (nx before load).

What about writing the increment inside the then-arm as well? No.

Better: exploit `own_thread_p`. If the fall-through thread has a label in the middle reachable by a branch, own_thread_p returns 0 → fall-through not used → target thread used. Can we make the call arm a branch target? E.g.:

```
if (x != 0) {
  if (1) { call; }   // no
}
```

Hmm. What about `goto`? Real C, no lever: 
```
do {
    if (x == 0) goto next;
    call;
next:
    i = i + 1;
    ...
}
```
Would that create a label at the increment, making the increment the branch target — and the then-arm fall-through... reorg: branch `bnez v0, .Lnext`? With `if (x == 0) goto next;` the branch goes to the increment when x==0, fall-through = call. That's a `bnez`? condition EQ (branch on x==0) → EQ → prediction 0 → fall-through first = call head `move a0,s0` eligible → same as now.

Hmm, so the key difference: target's fall-through head must be ineligible.

What makes an insn ineligible for a delay slot? Let's read fill_slots_from_thread and the eligibility checks: `eligible_for_delay`, `stop_search_p`, `slot_occupied`... `eligible_for_delay(insn, ...)` calls `eligible_for_delay` in the MD file (mips.md) which checks: insn is not a jump, not a call, not a label... and for a branch delay slot maybe only allows insns that don't reference the branch's condition register etc.

The head is `move a0,s0` — a simple move, eligible.

Idea: make the fall-through head a `jal` — calls can't fill a delay slot in MIPS md? Actually jal has its own delay slot. If the then-arm were `ot = f(ot,...)` without any argument setup (args already in place), the head would be the jal... not the case.

Another idea: make the then-arm head set a register that is used by the branch target (`i`'s increment path) — no, a0 isn't used at 2238.

Another: make the arm start with an insn that sets v0 (the branch condition reg)? At the branch target, v0 IS used (move s1,v0). So an insn at the fall-through head that writes v0 would be ineligible! In the target, the increment copy writes v0 = i+1... but that's the stolen one.

So: if the then-arm's first instruction writes v0, the fall-through is ineligible and reorg takes from the taken thread. In our C, the then-arm is `ot = xf8017E1D4(ot, panel, (s32)i);` — the first insn is `move a0,s0`. If instead the call were `ot = xf(panel, (s32)i, ot)`? That changes arg order → no.

Hmm, but wait: what if we could get the increment computed as part of the then-arm? Like `if (cond) { i = i + 1; ot = call(...); i = i - 1; }` — absurd.

Alternative approach: accept the structure and change the loop so the increment is placed differently: what if we hoist `i = i + 1` to the TOP of the loop body? Then the code would be:
```
i = 0;
do {
    i = i + 1;   /* or i++ at top */
    if (x) call with (s32)(i-1)?
```
No.

Let me reconsider: maybe there's another lever-free route: since only 1 insn and branch offsets differ, maybe using a different loop construct (for loop) changes reorg's decision. The `for (i = 0; i < lim; i++)` shape might put the increment at the bottom and the condition at the top... but the target has the increment copy after the call, i.e., the loop is a do-while with the test at the bottom (already so).

What about `while` loop with the test at top? Then the test is at the top and the increment at the bottom; the branch would be different. Target's shape is clearly a do-while.

Another thought: the empty asm barrier's effect could be replicated by making the fall-through head ineligible via a volatile access? No, volatile is a barrier-ish lever (kind "barrier" includes volatile-asm barrier; a volatile *load* would add insns).

Let me look at what fill_slots_from_thread does and whether "own_thread_p" for the target thread matters. In our case, prediction=0 → else branch: 
```
if (own_fallthrough) delay_list = fill_slots_from_thread(fallthrough...)
if (delay_list == 0) delay_list = fill_slots_from_thread(insn_at_target, ...)
```
So if own_fallthrough is 0, it goes to the target thread directly! own_fallthrough = own_thread_p(NEXT_INSN(insn), NULL_RTX, 1).

Let me read own_thread_p.
