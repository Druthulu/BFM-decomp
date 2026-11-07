---
ts: 2026-11-06T12:48:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mEQDCPEOoXtvgRPo0BYc
---
The target:
```
1c78: sll v0,v0,0x3        ← idx<<3
1c7c: lh v1,266(s1)        ← reload unk10A
1c80: lui at
1c84: addu at,at,v0
1c88: lw v0,0(at)          ← tmp1 = D_801ED5F0[idx*2]
1c8c: sll v1,v1,0x3        ← unk10A<<3
...
```
Mine (w4):
```
1c78: sll v1,v0,0x3        ← idx<<3 into v1
1c7c: ? 
```
So mine has idx in v0 and the shifted value in v1, target has the shifted value in v0. This is the priority issue: the reload pseudo took v0.

Wait, in mine: `lh a0,112(s1)` (i70a in a0), `lbu v0` (idx in v0), `sll v1,v0,0x3` (the shift result in v1) — then presumably `lw v1`... Let me see mine's next lines.

This is the exact §137 inversion described in the original comment: "All of {162,165,169,77,78} tied at pri 6666 ... so the tie fell to qty number and the reload won -> whole path inverted ($v0<->$v1, 11 insns off). idx (reg 156) sat at 6000 (refs 3 / len 5). Folding an "r"(idx) input INTO the existing memory barrier adds one ref ... -> pri 16000, so idx is allocated first, takes $v0".

Hmm, but in w4 mine has idx in v0 (good) and the *shift result* in v1 (bad). Target: idx in v0, shift result in v0 too (the shift overwrites idx after its last use). So the issue is which pseudo takes v0 after idx dies: the shift result vs the reload.

Actually in mine: `sll v1,v0,0x3` — the shift result is in v1; target `sll v0,v0,0x3` — in v0. Since idx is dead after the shift, the shift result could take v0 in local-alloc... but local-alloc assigned v1.

Hmm, this is a local-alloc qty priority thing. The original note says the fix was giving idx +1 ref so it's allocated FIRST (in global-alloc) and takes v0.

Wait, but idx already takes v0 in mine (lbu v0). So the difference is the shift result.

Let me look at mine's full region 143-165.
