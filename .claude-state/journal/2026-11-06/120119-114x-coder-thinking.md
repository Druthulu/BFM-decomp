---
ts: 2026-11-06T19:01:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GXNMGugQyvvd0pErH4ap
---
This is the ELSE block (the stores), not the loop-increment block. The sched's "basic block 2 from 56 to 103" is the else block (the 7 stores), and block 3 (50..112) is the increment block.

Block 3 (50..112): insns 37, 40, 43, 46, 111, 112. Hmm, those are the increments (4 of them) + the branch. The trace: 
- T-2: ready list 37, 40, 46, 111 → picked 111 (7f000001 = the current insn's launch priority).
- T-3: 46, 40, 37, 43 → picked 46.
- T-4: 43, 40, 37 → 43.
- T-5: 40, 37 → 40.
- T-6: 37 → 37.

The final order = reverse: 37, 40, 43, 46, 111? Hmm, the order of scheduling: T-1=112 (the branch), T-2=111, T-3=46, T-4=43, T-5=40, T-6=37. The final order is built by prepending: the last scheduled (37) is first. So the final order: 37, 40, 43, 46, 111 (the branch/delay).

Wait, that doesn't look right either: 111 is the branch? Let me look at the RTL for insns 37-46, 111.

The increments: 4 insns (a7+=0x68, v1+=0x68, a6++, a5+=0x68). The block 3 insns: 37, 40, 43, 46, 111, 112.

Let me look at them.
