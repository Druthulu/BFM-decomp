---
ts: 2026-11-06T10:17:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cnMjtzIYWGPzVAVhDxft
---
d7 has 15 diffs:
1. At 27-28: mine has an extra `andi v1,s4,0xffff` (from u16 y truncation) where target has `nop`. So u16 y introduces an andi. That's the u16 truncation.
2. Register swaps in the block 27-39 (v1/v0/a0).
3. A reordering at 120: `sw v0,28(s2)` moved.

Hmm, d7 uses u16 y which adds `andi`. The target has no andi there. So u16 y is not right semantically for codegen.

Let me reconsider: d8 = r2 s16 + y u16 (same score 15). d1 = r2 s16 alone → 32. So adding y u16 improved to 15 but introduced the andi.

What about y as u32? or s32 with r2 s16 → d1=32. Hmm.

Let me look at d1's diff (32) to see if it's the s2 fix without the andi.

Actually, the best path might be: fix the pointer (s2) without changing y's type, then fix the register block. d1 (r2 s16) gives pointer s2? Let me check d1's diff.

Time: ~03:30. Item 2 started 03:13 → 17 min. I should wrap up soon. Tries so far: nopin + c1-c25 (25) + c26-c33 (8) + d1-d12 (12) = 46. Plenty.

Best = 15. Let me see if I can get lower quickly with a couple more variants, then record WALL.

Let me look at d1 diff and d7's structure. Actually, maybe the winning combination is r2 s16 + y s32 but with something that fixes the v0/v1 block. The block 27-39 is the `y = t2 + zr` region. In target:
27 lhu v1,44(s2)  (unk2C)
28 nop
29 andi v1,v1,0x7ff
30 and v0,v0,v1
31 subu v0,s4,v0
32 move s4,v0      (y = t2)
33 sll v0,v0,0x10
34 lui v1,0x0
35 lw v1,0(v1)     (D_8012718C)
36 sra v0,v0,0x10
37 addiu v1,v1,-2504
38 slt v0,v0,v1
39 beqz v0,...

Mine d7:
27 lhu a0,44(s2)
28 andi v1,s4,0xffff   (u16 y trunc)
29 andi a0,a0,0x7ff
30 and v0,v0,a0
31 subu v1,v1,v0
32 move s4,v1
33 sll v1,v1,0x10
34 lui v0,0x0
35 lw v0,0(v0)
36 sra v1,v1,0x10
37 addiu v0,v0,-2504
38 slt v1,v1,v0
39 beqz v1,...

So d7 is target with v0/v1 swapped (plus the andi). If I remove the andi (use s32 y), I get d1 (32). d1's diff would show the pointer fix but maybe s3? Let me check d1.

Let me just check d1's diff quickly.
