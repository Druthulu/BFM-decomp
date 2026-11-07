---
ts: 2026-11-06T21:54:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wPrXSgPoxbcVSVpxyAgi
---
This is the banked body. The `tmp = 6;` at L801921F8 is followed by a shared label L801921FC where tmp is used. The SCAN_1919A0 macro presumably does `tmp = ...; goto L801921FC;`? Let me look at the macro and the surrounding code. The missing `li a3,6` suggests that in the target, the path that falls into L801921FC has tmp=6 AND another value. Hmm.

Actually target at 306-312: 
```
306 bnez v1,85c
307 li v0,6        (delay slot: tmp=6?)
...
312 li a3,6
```
Mine:
```
306 bnez v1,858
307 li a3,6       (delay slot)
...
(no second li)
```
So target: `tmp`(v0)=6 in the delay slot, then later `a3`=6. Mine: a3=6 in the delay slot, no v0. This is a register/scheduling difference: target's delay-slot insn is `li v0,6` (v0 = $2 = tmp pin) and later `li a3,6`. Two different destinations with the same constant.

Hmm, where does `li a3,6` come from? Probably `((Unkstruct...)->unk34 = 6)` or `unk1C = 6`? Let me look at the macro SCAN_1919A0 and the case-8 region. Let me find the macro definition.
