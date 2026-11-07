---
ts: 2026-11-06T13:37:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VXx71sSS9In6kO2o9del
---
Target at 0x1870: `mult v0,s2` where s2 = D_80192CC0 (loaded earlier as `lh s2,0(s2)` at 17cc), and v0 = t (the angle computation). The `d = cc * (D_80126950 + 500)` — hmm, in the source:
```
aa = t * m;      // m = D_80192CC0
bb = aa >> 12;
cc = bb + 8;
[barrier]
d = cc * (D_80126950 + 500);
d = d / (ret * 4);
```
So `D_80126950 + 500` is a load + addiu. In the target at 0x1870: `mult v0,s2` — hmm, s2 is D_80192CC0 (m). Wait, that's `t * m`? Let me map: the source has `m = D_80192CC0;` (loaded at 17cc into s2). Then t = ... Then aa = t*m → mult v0(t), s2(m) at 1870. Then mflo t0, sra v0,t0,0xc = bb. Then cc = bb+8.

So the target's mult at 1870 is aa = t*m, not d. The diff index 84-89 corresponds to this region. Mine hoisted the D_80126950 load above the mult (into the s2 load area?).

Let me see mine's listing around the same.
