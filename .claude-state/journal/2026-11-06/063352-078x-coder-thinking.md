---
ts: 2026-11-06T13:33:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UAfhGQWCU98DwEHMdT6X
---
The clobber is mem:BLK → `GET_CODE(ref)==MEM && !w->all` → invalidate(ref) — a memory invalidation, not registers.

So why did orig keep 291? Let me actually check whether cse2 deleted 291 in orig. Look at orig.i.sched for insn 291 in the function region.

Actually the sched dump is written AFTER sched1, but the .cse2 dump is written BEFORE cse2. There's no dump after cse2. Hmm. So I can't tell directly whether 291 survived cse2 in orig. But the final code tells us the addiu is early, so 291 survived (or an equivalent).

Let me think about what cse2 does with the no-op `a1 = a1` (insn 312, with REG_EQUAL fp+16). In cse_insn, for a set of a hard reg to itself, cse's `canon_reg` replaces the source with its known equivalent: a1's value in the table is fp+16 (from insn 291). So 312 becomes `a1 = fp+16`. Then `delete_dead_from_cse` isn't called for cse2. Then the final jump_optimize (noop_moves) would... 312 is not a no-op anymore.

Then who deletes 291 in nobar? Maybe cse2 itself: cse_insn processes insns; when it sees 291 setting a1, it records the value. Later, at 312, it substitutes. But 291 is still there. Unless cse's "dead code" removal (cse_insn deletes insns whose destination is set again before use?) — there's `delete_dead_from_cse` (only for cse1).

Hmm, the sched dump shows only 310 (the addiu) and no 291. Wait — maybe 291 IS the addiu and it's just numbered 310 in the sched dump because... the UIDs in the sched dump come from the same RTL, so no.

Hold on, let me re-check the nobar sched dump: the ready list had "insn[ 288]" and "insn[ 293]"... but no 291. Yet the cse2 dump had 291. So between the cse2 dump and sched1, 291 vanished. The only passes: cse2_main, jump_optimize(0,0,0) at 2929 if tem, then flow? Wait, where's flow? Between cse2 and sched1 there might be flow analysis. Let me check toplev 2929-3040: after cse2, jump_optimize if tem; then loop? no (loop was before cse2); then flow analysis? Let me read 2930-3040.

Actually the order was: cse, loop, [jump, cse2], then ... let me read.
