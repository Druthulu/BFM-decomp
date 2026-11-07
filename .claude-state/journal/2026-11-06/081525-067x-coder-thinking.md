---
ts: 2026-11-06T15:15:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_p68ZrbDGRQm39LPx1SYv
---
In the sched2 dump (pre-reorg): order is 476, 478 (andi), 486, 485, 488, then jump_insn 492. So the andi (478) is before the branch (492) — in the same block. So reorg DID move it from before the branch into the delay slot. My resource analysis must be wrong.

Let me look at reorg's actual behavior: maybe the delay slot was filled by `fill_slots_from_thread` using the fall-through thread, and the andi was moved into the *end of the block* by sched2's "reorder" of the block... no.

Wait: `fill_slots_from_thread` also tries insns from *before* the branch when `thread` is the fall-through: it scans the thread insns forward, but there's also `own_thread_p`. Hmm.

Let me look at the .dbr dump around the decision. Search for "478" in .dbr.
