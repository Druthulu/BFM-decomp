---
ts: 2026-11-06T04:46:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pTpPiguGr604VpjhV4Ps
---
b1 diff is small: mine computes `lui v1,0xffff` then something then `ori v1,0xfff` at position 5, target does ori at position 3. And the a3 (D_800C7C60 address) setup moved. Let me dump b1 asm vs target.

Actually diff says: target insn 3 = ori v1,v1,0xfff (right after lui v1,0xffff), while mine has something at 3-4 (probably lui v0 currentLocationId / lh) before the ori. And mine has a3 setup at 15-16 whereas target at 6-7. Let's dump.
