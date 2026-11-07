---
ts: 2026-11-06T12:48:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_45n0o6m55mWFUaRpQ0pZ
---
Compare:

Target:
```
1c5c: lh a0,112(s1)       ← hmm wait, target line 143?
```
Let me get the target's 1c5c region:
From earlier target lines 143-165:
```
1c5c: 86240070  lh a0,112(s1)   (probably)
1c60: lui at
1c64: sh zero,0(at)          ← D_801F32D0 = 0
1c68: lui at
1c6c: addu at,at,a0
1c70: lbu v0,0(at)           ← idx = D_801ED4B4[i70a]
1c74: nop
1c78: sll v0,v0,0x3          ← idx<<3 in v0
1c7c: lh v1,266(s1)          ← reload unk10A
1c80: lui at
1c84: addu at,at,v0
1c88: lw v0,0(at)            ← tmp1
1c8c: sll v1,v1,0x3
1c90: lui at
1c94: addu at,at,v1
1c98: lw v1,0(at)            ← tmp2
1c9c: lui at
1ca0: sw v0,0(at)            ← D_801F32DC = tmp1
1ca4: lui at
1ca8: sw v1,0(at)            ← D_801F32E0 = tmp2
1cac: lui at
1cb0: addu at,at,a0
1cb4: lbu a0,0(at)           ← D_80183A40[i70b]
```
So in the target, the `unk10A = idx` store (`sh v0,266(s1)`) does NOT appear here! Wait, mine has `sh v0,266(s1)` at 1c7c (the store of unk10A = idx). The target has `lh v1,266(s1)` at 1c7c instead — the target RELOADS unk10A but never stores it? Let me check: where's the store of unk10A in the target? Earlier in the target maybe (`sh` before). Let me grep the target asm for "266(s1)".
