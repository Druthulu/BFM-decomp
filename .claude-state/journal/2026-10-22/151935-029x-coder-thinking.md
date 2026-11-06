---
ts: 2026-10-22T21:19:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_He6lrshDIl4JBt2uiFq6
---
Now arm3 in w2: 14b4 sh 32; 14b8 li 1536; 14bc sh 34; 14c0 li -80; then falls into the shared tail at 14c4. And arm1 jumps to 14c4. So the merge is of the last 3 insns.

To defeat this partial merge, the *last store* must differ. In w2 it doesn't differ because combine/cse2 folded the s32 k into a constant.

Wait, but the merge is of "sh zero,36; sh zero,46; sh v0,48" — the last store included. If the last store differed, the merge would be just 2 insns, still merging "sh zero,36; sh zero,46" and then arm1/arm3 would still jump to a shared block. Hmm — but the target has NO merge at all: arm1 ends with its own j at 1464.

Target arm1: 145c sh zero,36; 1460 sh zero,46; 1464 j 14fc; 1468 sh v0,48.
So the j and the delay-slot store are part of arm1.

For a full non-merge, the *first* differing insn must be at the start: sh v0,32 vs arm3's sh v0,32 — identical. Unless the register differs! In the target both use v0. Hmm.

But wait: cross-jump requires rtx_equiv_p with renaming — register differences are handled. So the only way is a structural difference in the first insn.

Hold on. What if the two blocks have different *number of insns* or different successors? Cross-jump merges the longest common suffix; the target has none. So the target's arm1 and arm3 blocks must differ in EVERY insn? No — cross-jump merges a common suffix; even a 1-insn common suffix would produce a jump. In the target, arm1 ends with j + delay store; arm3 ends with j + delay store. Identical! Yet no merge.

Therefore cross-jump in the ROM's build didn't merge these blocks at all. Why? Because the barrier asm is in arm3 — a `volatile asm` insn can't be matched. But in the target there IS no asm insn...

Oh wait! The ROM is the *target*: the real game binary. Its source (unknown to us) had no asm. So how did the real compiler not merge?

Possible: cross-jumping in gcc 2.7.2 (the ROM's compiler) requires more than identical suffixes — maybe `flag_cross_jumping` requires -f... or the ROM was built with -O2 but cross-jumping is disabled? But then our build (using the same compiler? tools/bin/gcc-2.7.2-psx) would behave the same.

Hmm! Wait. Our build uses gcc-2.7.2-psx — the same compiler. So cross-jump is part of it. Then the ROM's source must differ structurally.

Let me reconsider: maybe in the ROM's source, arm1 and arm3 blocks aren't both "then" blocks with the same successor. Look at the target's control flow:

1444: beqz v0,146c  (cond1 false → 146c: cond2 test)
1448: li v0,113 (delay)
144c-1468: arm1 body, j 14fc; sh v0,48

146c: cond2 test: lhu v0,16(sp); addiu; andi; sltiu; beqz v0,14ac
1488-14a0: ... wait target 1488: lhu v0,20(sp); 1490 addiu -1665; 1494 sltiu 1020; 1498 beqz v0,14ac; 149c li v0,682; 14a0 sh v0,32...

Hmm, target line 78-80 earlier: 1498: beqz v0,14ac; 149c: li v0,682; 14a0: sh v0,32. Then arm2 continues... then 14c0: sh v0,32?? Let me re-read the target fully around 14a0-14e0.

From the tgt.txt lines 80+: 14a0 sh v0,32; 14a4 li v0,1536; 14a8 sh v0,34; 14ac li v0,-80; 14b0 sh zero,36; 14b4 sh zero,46; 14b8 j 14fc; 14bc sh v0,48; 14c0 li v0,682; 14c4 sh v0,32; 14c8 li 1536; 14cc sh v0,34; 14d0 li -80; 14d4 sh zero,36; 14d8 sh zero,46; 14dc j 14fc; 14e0 sh v0,48? 

Wait that doesn't match. Let me re-read the earlier output: 

```
14c0: a6020020 sh v0,32(s0)
14c4: 24020600 li v0,1536
14c8: a6020022 sh v0,34(s0)
14cc: 2402ffb0 li v0,-80
14d0: a6000024 sh zero,36(s0)
14d4: a600002e sh zero,46(s0)
14d8: 0800053f j 14fc
14dc: a6020030 sh v0,48(s0)
14e0: 240202aa li v0,682
14e4: a6020020 sh v0,32(s0)
14e8: 24020600 li v0,1536
14ec: a6020022 sh v0,34(s0)
14f0: a6000024 sh zero,36(s0)
14f4: a600002e sh zero,46(s0)
14f8: a6000030 sh zero,48(s0)
14fc: a6000032 sh zero,50(s0)
```

Hmm so there are blocks at 14a0ish (arm2?), 14c0ish (arm3), 14e0ish (arm4).

Wait — 14a0's block: sh v0,32 with v0=682? No: 149c li v0,682; 14a0 sh v0,32; 14a4 li 1536; 14a8 sh v0,34; 14ac li -80; 14b0 sh zero,36; 14b4 sh zero,46; 14b8 j; 14bc sh v0,48.

Hmm, but arm2's body is unk20=0x2AA(682), unk22=0x800(2048), unk24=0, unk2E=0, unk30=0. That doesn't match: at 14a4 li 1536 = 0x600, not 0x800. And arm3's body is 0x71,0x600,0,0,k. But at 14a0 v0=682=0x2AA.

I'm confusing myself. The dump I read (sed 80,119) started at 14c0. The earlier sed 1,80 ended at 14a0 sh v0,32. Let me just read the full target disassembly again carefully, lines 70-100 of tgt.txt.

Let me print tgt.txt lines 60-100.
