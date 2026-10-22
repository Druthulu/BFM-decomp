---
ts: 2026-10-22T11:15:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_BK6mSCLOWwrSR6F6qkdQ
---
Now compare:

ORIG (with asm):
- insn 235: load → reg 167
- insn 237: asm (sets 167)
- insn 240: set a0 = 167
- insn 242: set a1 = 320
- insn 244: set a2 = 240
- 246: call

Note: NO `code_label` between the load and the call in the orig! There's a NOTE_INSN_BLOCK_BEG at 232 and the block continues. Hmm, so the asm did NOT split the block in the RTL? The asm insn 237 is in the same block.

Wait, but the final code has the load before li a1. Let me check the orig's .sched dump to see the scheduled order.

Actually hold on! In the orig, the load is `set 167 = mem` and then the asm `set 167 = asm_operands(...)`. The asm's output is 167, and the input is 167 (tied). So after the asm, 167 is "written by asm" — its value is the input value (same reg).

Then `set a0 = 167` — this copy can't be coalesced with the load because the asm intervenes (the value flows through the asm).

In the no-asm version:
- 235: set 167 = mem
- 238: set a0 = 167
- 240: a1=320
- 242: a2=240
- 244: call
Then coalesce merged 235+238 into one insn (the load became `set a0 = mem`), with uid 238.

Then sched1 reordered: li a1 (240) before the load (238).

In the orig: after the asm, `set a0 = 167` (uid 240) — the copy is separate from the load. The scheduler then... let me check the orig's sched dump order.

Let me look.
