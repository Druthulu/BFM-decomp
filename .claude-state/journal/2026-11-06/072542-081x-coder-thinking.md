---
ts: 2026-11-06T14:25:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZFw0dB4KT2ThEbUvEpPz
---
It IS reg_live_length. So why is it the same 39?

Let me look at how reg_live_length is computed more carefully. In propagate_block, `reg_live_length[p->offset*...]++` for regs that were live in the previous insn (old) and are still in maxlive. It counts the number of insns where the reg is live. But there's also line 2073: `reg_live_length[regno]++` in mark_used_regs when the reg is set (to include the setting insn).

Hmm, maybe the live_length is computed on a per-block basis and summed. For i: block 13 (from i=0 to end), block 14 (whole body, since i is live from the back edge at the start to... wait, is i live at the start of block 14? Block 14 is the loop body; i is used in block 17 (latch), so at the start of block 14, i is NOT yet live (it's live in the latch). Actually i is live at the END of block 14 (flowing into block 17). So in block 14, i is live only after... hmm, i is not used in block 14, so i is live throughout block 14 only if it's live at the end. Yes: i is live at the end of block 14 (needed by block 17), so it's live for ALL of block 14. Similarly, in block 13, i is live from i=0 to the end (block 13 ends with the blez). In block 17, i is live from the start to the slt.

If i=0 moves later within block 13, i is live for fewer insns in block 13. So live_length should decrease. But it didn't.

Unless... the live_length is computed with `basic_block_live_at_start` and the backward propagation. In the first pass (final=0), it computes liveness. In the final pass (final=1), it counts live_length. Hmm.

Wait, maybe i's birth is in block 13 but flow counts i as live at the start of block 13 because block 13 is inside a loop and i is live at the loop back edge? No, block 13 is before the do-while.

Hmm, let me look at the actual block structure. Maybe the setup block is block 13, and i=0 at insn 307/316. The live_length counts from the insn where i is born. If i=0 is at insn 316, and the block ends at insn 321, then i is live for insns 316-321 (6 insns) in block 13. In c1, i=0 at 307, block ends 323 (the blez) -> ~17 insns. That's a difference of 11. But live_length is the same 39.

Something's off. Let me actually look at the live_length computation. Maybe it's not what I think. Let me look at the `sometimes` mechanism: `regs_sometimes_live` tracks regs that were live at some point in the block; for each insn, if the reg was live in the PREVIOUS insn (old), increment. This counts insns where the reg is live. Hmm.

Actually wait — maybe the live_length printed is from a DIFFERENT flow pass. The .lreg dump prints flow info. But maybe `dump_local_alloc` calls `dump_flow_info` which prints the CURRENT reg_live_length, which might have been updated by local-alloc? No, local-alloc doesn't change it.

Hmm, let me look at c1's live for i again: 39. And dst: 36. Let me compute dst's: dst born at insn 316 (c1) in block13, block ends ~323. Then live in block 14 and 17 until dst++ at 393. So dst live ~36. OK.

For i: born at 307, live until slt at ~398. If the loop body is ~40 insns and the latch ~20, plus setup ~17, that's ~77. But it says 39. So maybe the loop body isn't counted fully... 

Hmm, maybe reg_live_length counts only the insns in the block where the reg is live, and blocks are counted once, but the setup block 13 is counted. Let me count: block13 insns 296-321 = 26 insns; block14 325-379 = 55; block17 388-407 = 20. If i were live throughout, that's ~100. But it says 39. So i is NOT live throughout block 14.

Wait, is i live in block 14? i is used in block 17 (i++ and slt). Block 14 flows into block 17. So i must be live at the end of block 14 (to be used in block 17). So i is live throughout block 14... unless block 14 doesn't flow to block 17 (maybe block 14 ends with a branch to block 17 and i is dead there? No, i is used in 17).

Hmm, but the "sometimes" counting: regs_sometimes_live tracks regs that were live at some point. For each insn, it increments live_length if the reg was live in the PREVIOUS (old) set. Let me re-read:

```
for each insn (backwards):
  ...
  diff = live & ~maxlive  -> add to sometimes list
  maxlive |= diff
  for each sometimes reg p:
     if (old[p] & bit)  // was live in the previous (later) insn
        reg_live_length[p]++
```

Hmm, `old` is the live set before the current insn? In a backward scan, `old` is the live set after the insn (from the previous iteration). So it increments for each insn where the reg is live. So the count should be the total live span.

Let me just directly check: maybe I'm misreading which register is i. Let me verify with the .cse2 dump: insn 393 sets reg160 (i++), and reg160 is the i. Yes.

Actually, maybe reg 160 in b2 is a DIFFERENT pseudo than in c1 due to renumbering. In b2, the order is src(161), dst(162), i(160)? That's odd: src=161, dst=162, i=160. In c1: i=160, src=161, dst=162. So the pseudo numbers differ based on declaration order? The declarations are `s32 n; s32 i; u16 *src; u16 *dst;`. n=159, i=160, src=161, dst=162. In b2, the assignments are reordered but the declarations are the same. So i=160 still. Good.

Hmm, so b2's i is born at insn 316 and c1's at 307. Yet both live_length 39. Let me actually dump b2's flow info again... it said 39. Weird.

Wait, maybe the .lreg dump's flow info is printed AFTER local-alloc, and local-alloc modifies reg_live_length? No.

Let me look at the actual flow dump (.flow) which is dumped right after flow_analysis. Let me grep b2's .flow for reg 160.

Actually, the .flow dump might not exist in the dump list: the dumps were cpp.err, .combine, .cse, .cse2, .dbr, .flow, .greg, .jump, .jump2, .loop, .lreg, .rtl, .sched, .sched2, .s. Yes, .flow exists. Let me grep b2's .flow.
