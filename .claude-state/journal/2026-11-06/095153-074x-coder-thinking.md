---
ts: 2026-11-06T16:51:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_otiiOlYi1zNV3bugSAmn
---
All 10. The sll placement doesn't change (sched decides).

Time check: ~09:52. Item 3 started ~09:44 → 8 min. I have ~12 more min minimum for a WALL, but maybe I can crack it.

Let me think about the target's branch block again. The key difference: the sign-extension `sll v1,v1,0x10` is scheduled early in the target and its dest is v1. In mine it's late with a temp dest.

The dest register difference (self vs temp) is an allocation issue: in the target, local-alloc tied the sll temp to v1 (copy suggestion?). The sra `sra v1,temp` — temp dies, v1 is set. local-alloc's copy suggestion: when an insn sets REG_A and uses REG_B which dies, and REG_A... hmm, for `sra v1,temp`, v1 is set and temp dies → local-alloc suggests v1 and temp share? That's `qty_phys_copy_sugg` — yes! In local-alloc, when an insn copies (set reg1 reg2) and reg2 dies, it suggests reg1's register for reg2. But `sra` is not a copy.

Hmm. Actually, the tie in the target might be because the *sll* is `sll v1,v1,16` — same source and dest. That happens when the compiler emits `(set (reg v1) (ashift (reg v1) 16))` directly, i.e., the source's `v1 = (s16)v1` was compiled as a self-set. gcc's `convert_to_mode`/`expand_expr` for a narrowing cast of a variable: it may use the same reg as the target if the operand is a REG and the mode change is a SUBREG... The MIPS backend's sign_extend from HImode subreg uses a temp when the source is a SImode reg.

But if v1 were declared `s16`, `v1 = (s16)v1` is a no-op and the extension would be implicit at each use. r01 (v1 s16) gave 65 ins — the code changed (the sra disappeared and other things changed). Not good.

What if the source uses a `s16` temporary for the comparison only: `if (v0 >= (s16)v1)` — same temp.

Hmm. Let me look at the target's exact instruction `sra v1,v1,0x10` at 339c: that's `v1 = (s16)v1` computed late, with sll early. Weird: sll at 3388 and sra at 339c — the dependency chain is split across the block. So the target's RTL is `sll v1,v1,16` early and `sra v1,v1,16` late. That means the compiler split the sign-extension into two insns scheduled apart. Mine also has them apart (sll 339c, sra 33a0) but both late.

The scheduler placed the sll early in the target because... the sll's source (v1) is ready early. In mine, the sll is late because its *dest* is a temp that... hmm.

Wait, maybe in mine the sll is late because the sign-extension is attached to the *comparison* (`slt v0,v0,v1`), whereas in the target it's attached to the *store*? No.

Let me try a different tack: maybe the whole branch can be written to avoid the sign-extension temp by reordering the comparison:
`if (v0 >= v1)` where v1 is u16 and v0 is s32... the comparison is signed.

Alternatively, keep v1 as s32 and do the sign-extension at the point of the *load*: `v1 = (s16)v1;` right after `v1 = v1 + v0;`? That's in the first block, not the branches. The target's first block doesn't have the sra. So no.

OK, let me try to attack the allocation directly: the sign-extension temp steals $v0 from the branch's v0. If I make the branch's v0 shorter-lived (e.g., split the index part), maybe the loaded value gets $v0 and the temp gets something else.

In the target branch, v0 is used for: unk70 (lh), *2, then the loaded value, then a0r=move a0,v0, then v0-0x30, slt. So v0's live range covers the whole branch. The temp's range is 2 insns. The temp wins.

Unless... the temp is eliminated. What if we write the sign-extension as a *separate statement using v1 itself* in a way gcc compiles to a self-set? e.g.:
```
v1 = (s16)v1;
```
→ temp. 
```
v1 <<= 16; v1 >>= 16;
```
→ two self-sets? `v1 <<= 16` is `v1 = v1 << 16` (self-set), `v1 >>= 16` arithmetic (v1 is s32) → self-set. That might compile to `sll v1,v1,16; sra v1,v1,16` with no temp! And the scheduler would place them as separate insns. Let me try!

r03 tried `v1 = (v1 << 16) >> 16;` which is a single expression → temp. But two statements might work.

Let me test:
- t01: `v1 <<= 16; v1 >>= 16;` in both branches.
- t02: `v1 = v1 << 16; v1 = v1 >> 16;`

Also, the `(s16)v1` in the else branch's comparison.

Let me test.
