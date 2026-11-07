---
ts: 2026-11-06T17:26:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XOvWSOsgx0DE45HWHdd3
---
nopin = 7, same length 254. Residual: v0/v1 swap around the sh16 computation:
```
173 addu v0,v0,v1 | addu v1,v1,v0
174 sra v0,v0,1    | sra v1,v1,1
175 sh v0,242(s0)  | sh v1,242(s0)
```
Only 3 instructions differ! Very close.

The source:
```
p[0x79] = (u16)(((sh16 >> 16) + (s32)((u32)sh16 >> 31)) >> 1);
```
Target: v1 = result; mine: v0. The pin was $2 (v0) — so with the pin sh16 is in v0 and the result stays v0. Without, sh16 might be in v1 and the result in v0 (mine), while the target has the result in v1.

Wait: target line 173 `addu v1,v1,v0` and `sra v1,v1,1; sh v1,242(s0)`. Mine `addu v0,v0,v1; sra v0,v0,1; sh v0,242(s0)`.

So the target's sh16 is in v1 (the addu's first operand v1 = sh16>>16? and v0 = sh16>>>31). Hmm.

Let me see the full context. Get the diff with more lines.
