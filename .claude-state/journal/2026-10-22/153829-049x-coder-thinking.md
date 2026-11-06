---
ts: 2026-10-22T21:38:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bB6BYoLsgnWJQQw3qexs
---
Both still put `move a0,v0` (testval) first. This is sched1's birth-order: the $4 copy is scheduled before the $3 copy regardless of source order.

Why? Because the $4 value (testval) feeds the beqz (branch at 13) → longer path → higher priority. The $3 value feeds the sb at 25 → longer path actually... Hmm, sched1's priority is the length of the longest path from this insn to the end of the block. The sll v1 chain (19,20) then sb (25) is longer than the beqz path. So the $3 copy should have higher priority... but sched1 schedules by "ready at earliest cycle" and picks by priority; both are ready at cycle 1.

Hmm, the target has v1 first, mine a0 first. Both are the same 2 insns in a different order. It's a tie-break: sched1 uses `INSN_PRIORITY` and then the insn's `uid`? Actually sched1's ready list is sorted by priority, ties broken by... let me think: `ready_add` inserts by priority; for equal priority, insertion order (queue order). The queue order is the birth order (RTL order). So the source order should decide... unless cse/combine reordered the insns before sched1.

The $4 copy is created by combine/local-alloc? These copies come from the hard-reg pins: byteval($3) = src($2) and testval($4) = src($2). RTL order: byteval copy first (source order). Then sched1 puts them... 

Hmm, but u8_swap (testval first in source) gives the same output as u8. That means the order is NOT decided by source order — something normalizes it. Possibly because byteval is u8 (a subreg copy) while testval is a plain copy: the u8 copy is `(subreg:QI (reg $3) 0) = (subreg:QI (reg $2) 0)` — hmm.

Wait, maybe the pins make $3/$4 hard regs and the copies get different priorities via REG_DEP_OUTPUT/live lengths. 

Let me try: give byteval's copy a shorter/longer life... 

Alternative: use a different register for byteval? No — pins must stay as they are (they're not row kinds, but I may not change them? "levers of other kinds the def already had (pins under other causes) may stay, never added" — it doesn't forbid changing them, but changing a pin is adding/altering a lever. Better keep them.)

Alternative approach: make the *testval* copy come later by making its value not equal src at birth — e.g. `testval = src;` where testval is used only in the branch. If testval's copy were scheduled after the beq... no, it must be before the beqz.

Hmm, what if the beq/beqz order... 

Let me think about sched1's priority for the two copies. Both have one successor path. In sched1, INSN_PRIORITY is computed as the length of the longest path from the insn to the end of the block. Copy to $4 (testval) → beqz (13) → then the fallthrough block? sched1 works within a basic block: the block ends at the beqz? Actually beq at 11 is a branch; the basic block ends there. So the block is insns 0..11 (up to the beq, with the delay slot). Then the second block starts at 13.

Hmm, so the beq at 11 ends block 1, and the delay slot insn (sll a1) is in block 1. So both copies are in block 1, whose end is the beq. Priority = distance to the block end (the beq). testval ($4) feeds the beqz at 13 (in the NEXT block) — hmm, but the beqz at 13 is the start of the fallthrough block.

sched1 priority = length of longest path to the end of the block. The $4 copy's use (beqz at 13) is not in the block, so it contributes nothing → priority low. The $3 copy's use is at 19-25, also not in the block. Both priorities similar.

Then sched1 schedules by priority and ready-time. Both are ready at the top. The order within equal priority: the ready list is a queue sorted by priority; for equal priorities, the insertion order is preserved... which is RTL order (birth order). Source order: byteval first.

But we saw that source order doesn't matter! Both u8 and u8_swap give `move a0,v0` first. So RTL order isn't the source order → the copies were reordered by an earlier pass, or the priority differs.

The u8 case: `byteval = src` is a QImode subreg copy; maybe it becomes a different insn pattern. And testval's copy is SImode. Hmm.

Maybe the difference: for u8 byteval, the copy is `move v1,v0` where v1=$3. And testval `move a0,v0` where a0=$4.

Let me try other spellings to flip the order:
- make testval u8 too? That changes the branch compare (beqz on a QI reg → it'd add andi). Hmm, maybe not: `testval != 0` with testval u8 → beqz on the subreg, no andi (since src is known <16). Actually it might still work. Test.
- make byteval's assignment later than testval's but with a dependency...

Alternatively, maybe the target's order comes from the *pins* themselves being different: in the target, $3's copy is born first because $3 is also used... hmm.

Wait. Maybe I should reconsider: the target's `move v1,v0` at 7 and `move a0,v0` at 8: v1=$3 (byteval), a0=$4 (testval). Mine: a0 then v1.

What if the u8 subreg copy is what makes it "movable", and the natural SImode copy is placed by a different rule. Let me test the reverse: make byteval a plain u32 (SImode) and testval a u8 (QI). Then maybe the SImode copy (byteval) goes first. But testval u8 might alter the beqz.

Also try: declare testval as u8 and byteval as u8.

Let me run a batch: (t_u8: testval u8), (both_u8), (byteval s16 + testval u8), etc.

Another idea: reorder the declarations (decl order) — byteval declared after testval? The declaration order in the block: src, byteval, testval. Try src, testval, byteval.

Let me batch these.
