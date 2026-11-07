---
ts: 2026-11-06T15:16:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_f5IfyU6l6u5AopX8WBmS
---
Target prologue: a0→s0 (idx), a1→s1 (a1 param). So a1 is in s1, not v0! At 6d8, `sra s0,v0,0x10` — v0 must hold a1 at that point? Let me look: case 5 at 6d4-6d8. Before that, at 6d0 `li v0,2`? Let me look at 6c8-6dc.

Actually at 6cc: `j 858`, 6d0: `li v0,2` (delay). Hmm. Let me look at the case-5 entry: the switch jumps here. At 6d4? Let me print 6d0-6e0 again:
```
6d8: sra s0,v0,0x10
6dc: bnez s0,6f4
```
So v0 holds a1 before 6d8. Where does v0 get a1? `move v0,s1` somewhere. Let me look at 6d0-6d8.
