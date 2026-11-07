---
ts: 2026-11-06T14:18:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aPQYDLU8kvyiLziIerhb
---
b2/b3 still 6. b4 (src = arg0->data after dst, which is invalid anyway — dst uses src before assignment; b4 is wrong semantically, ignore).

Hmm, b2 and b3 still 6. Did the ref/live numbers change? Let me dump b2 and check the register table. Actually, maybe sched1 reordered so flow's live range is the same? No, flow is before sched1.

Wait, actually the C statement order affects the RTL order produced by expand. If `src = arg0->data; dst = src + n; i = 0;` then dst's birth is at the same relative place. The live_length for dst: from its birth insn to its last use. Moving i=0 after dst doesn't change dst's birth... wait, b2 reorders so dst is before i=0. dst's birth insn is now earlier in the RTL (before i=0). So dst live should be +1 or +2.

But score stayed 6 (REG-caller). Maybe the allocation still gives dst t2. Let me dump b2 and check refs/live.

Actually, let me reconsider: maybe it's not global-alloc at all! Let me verify by looking at the .greg dump for c1: which regs are assigned where. The .greg dump shows "Register N now in X" lines. Let me grep for regs 160 and 162 in c1's greg dump.
