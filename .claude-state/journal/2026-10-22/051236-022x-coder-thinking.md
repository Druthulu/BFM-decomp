---
ts: 2026-10-22T11:12:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_g8URmIrxtrQC19ivp57c
---
Interesting! The .sched dump is AFTER scheduling (it's the final scheduled RTL). Note the order in the dump:
- insn 240: `set a1 = 320`
- insn 238: `set a0 = mem[73+32]` (the load!)
- insn 242: `set a2 = 240`
- insn 244: call

Note the insn numbers: 238 < 240 < 242 < 244. But the DUMP order shows 240 first, then 238, then 242, 244. In GCC's RTL dumps, instructions within a block are printed in the insn_list order (which is the actual order). The numbers in parens are the LUID-ish sequence numbers... Actually the format is `(insn <uid> <prev> <next> ...)`. Hmm, in GCC's RTL dump the first number is the insn's "sequence number" (uid), the second is the previous insn's uid, third is next.

So: insn 240 has prev=246, next=238. insn 238 has prev=240, next=242. So the actual order is 240, 238, 242, 244. Yes — the dump order is the real order.

So in the final RTL: a1=320 comes BEFORE the load. So the scheduler put the li first.

Interesting: the a0 load (insn 238) has uid 238, less than the a1 li (240). But the order is 240 then 238. So the scheduler chose the li first.

Now — in the TARGET, the order is load then li. So the target's load is not in the same block.

Let me look at the TARGET's sched dump... I don't have it. But I can generate it: compile the ORIGINAL (with asm) and dump.

Let me do that to confirm the block structure difference.

Let me run cc1_dumps_tu.sh on the orig TU. I need a spliced TU with the original body. The --keep scratch for orig.c... Actually I can create the scratch by running --try with orig.c --keep.

Let me do that.

Actually, more valuable: let me figure out how to force the load to be scheduled before the li in the same block.

sched1's priority: In GCC's sched1 (sched1.c), `rank_for_schedule` computes for each insn a "priority" = the number of insns in the block that it must wait for (its dependency depth), with a "birth" adjustment. The `li a1,320` has 0 deps → priority 0? Hmm, but then it should be first. And the load (a0) also 0 deps in-block. So both 0 → tie.

Then sched1 breaks ties... In GCC's sched1, when priorities are equal, it picks the insn with the highest "ratio" and then... Actually `sched1` sorts by priority descending, and for equal priority it uses `insn->priority` and then the order in the ready list.

Hmm, GCC 2.7's sched1 `schedule_insns` → uses `ready` list ordered by `priority` then by `order` (the LUID). It picks the highest priority; among equal, it picks the one with the highest `order`?? Hmm.

Actually GCC's sched1 has a special rule from the "birth boost": `rank_for_schedule` gives a bonus to insns with fewer predecessors. And there's the `sched1` option `no-sched-interblock`, `sched-pressure`...

Alternatively — the difference might come from the *delay slot* consideration: `sched1` tries to maximize the number of insns in the delay slot of the preceding branch.

Hmm. Let me look at the pre-sched RTL (cse2 dump) to see the order there.

Let me look at cse2 around line 18757.
