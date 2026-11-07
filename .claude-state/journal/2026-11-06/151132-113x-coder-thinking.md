---
ts: 2026-11-06T22:11:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bxATKBaxzpH663VjQBnZ
---
That was a wasted call. Let me write a proper generator for the do-while variants using Python (multi-line replacement), since sed across two lines is awkward.

Let me write gen5.py in item 1:
- i1: wrap the packet store in do{}while(0).
- i2: wrap the otp block.
- i3: wrap both.
- i4: init-at-decl for oidx: `s32 oidx = g.otz << 2;` and remove the assignment line.
- i5: move oidx assignment before the `pkt[0xC]` line.
- i6: `u32 *pp = (u32 *)pkt;` for the first store (already a3-ish).

Let me write it.
