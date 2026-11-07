---
ts: 2026-11-06T13:07:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_E2nt5Yvitpp5CkGMMlQK
---
Target:
```
61 lbu s0,258(s1)     ; c = p[0x102]
62 nop
63 addiu s0,s0,1      ; c+1
64 sb s0,258(s1)      ; p[0x102] = c
65 jal rand
66 andi s0,s0,0xff    ; c & 0xff   (delay slot)
67 andi v0,v0,0x1
68 slt v0,v0,s0
69 beqz ...
```
So the target's delay slot of `jal rand` is `andi s0,s0,0xff`.

Mine (a1, no barrier): andi before sb. Let me dump mine.
