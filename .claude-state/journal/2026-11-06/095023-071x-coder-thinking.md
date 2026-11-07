---
ts: 2026-11-06T16:50:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FmvJYwKpyqglkGmNpnBa
---
q01/q03 = 29 with 65 ins (2 fewer than target) — worse than p02 (10). Splitting the branches hurt.

p02 is the best so far (10). p02: v0 (block1+branches), v0b (JOIN/K). Let me refine: maybe split differently — v0 for block1, v0b for branches, v0c for JOIN/K was worse. What about v0 (block1), v0b (branches+JOIN/K)? That's p01 (33). Hmm.

p02's residual: the branches' temp got $a0 instead of $v0, and the `sll v1,v1,0x10` / `sra` ordering differs.

Wait, p02 diff:
- mine[17] nop vs target sll v1,v1,0x10 — a scheduling difference
- mine[21] `lh a0,0(at)` vs `lh v0,0(at)`; `sll v0,v1,0x10` vs `sra v1,v1,0x10`; `sra v1,v0,0x10` vs `move a0,v0`; `addiu v0,a0,-48` vs `addiu v0,v0,-48`.

So in the branches, the loaded value is in $a0 (mine) vs $v0 (target). This is the branch's v0 (same source var as block1's, since p02 keeps v0 for block1+branches). It got $a0 because... the JOIN's v0b took $v0.

So: v0b (JOIN/K) got $v0, and v0 (block1+branches) got $a0. If instead v0 got $v0 and v0b got $a0, we'd match. The priority: v0b (short, JOIN+K) beats v0 (long). To flip, make v0b less attractive or v0 more.

Hmm, but the target uses $v0 for both. The allocator gives $v0 to only one.

What if we split so that the branch region's temp is a separate variable with a very short live range that outranks everything? Let's think: target branch block:
```
3384 lh v0,112(s0)
3388 sll v1,v1,0x10
338c sll v0,v0,0x1
3390 lui at
3394 addu at,at,v0
3398 lh v0,0(at)
339c sra v1,v1,0x10
33a0 move a0,v0
33a4 addiu v0,v0,-48
33a8 slt v0,v0,v1
33ac bnez v0
33b0 nop
33b4 j
33b8 sh a0,48(a1)
```
v0 is used for unk70*2, then reloaded, then a0r = v0 (move a0,v0), then v0 = v0-0x30, then slt. So v0's branch live range is from lh to slt (~8 insns). a0r = $a0, v1 = $v1.

Mine (p02):
```
17 nop (target: sll v1,v1,0x10)
21 lh a0,0(at)      ; v0 -> $a0
22 sll v0,v1,0x10   ; the test shift -> $v0
23 sra v1,v0,0x10
24 addiu v0,a0,-48
```
So mine has an extra temp: `sll v0,v1,0x10` — that's the `v1 = (s16)v1` sign extension, which in the target is `sll v1,v1,0x10; sra v1,v1,0x10` (two insns, both in v1). In mine, the sll result is in $v0 and the sra in $v1. So the `(s16)v1` cast creates a temp in $v0.

Hmm, this is the `v1 = (s16)v1;` statement. In the target, `sll v1,v1,0x10; sra v1,v1,0x10` — the sll dest is v1 (self). In mine, the sll dest is a temp ($v0) and the sra dest is v1. So the temp stole $v0 from the branch's v0!

Fix: make the `(s16)v1` cast reuse v1. `v1 = (s16)v1;` — the cast to s16 then back to s32 should be a sign-extension: sll+sra. If the source is `v1 = (s16)v1;`, gcc emits the sign-extension into v1. But mine emits the sll into a temp. Hmm.

Wait, in p02 the `v1 = (s16)v1;` is in both branches. Maybe the source's `(s16)v1` is in a different context. Let me look at the actual source lines:
```
    if ((s32)(v0 << 16) < 0) {
        ...
        v0 = *(s16 *)at;
        a0r = v0;
        v0 = v0 - 0x30;
        if (v0 >= v1) {
```
Wait, where's `v1 = (s16)v1;`? In the else branch:
```
    } else {
        v1 = (s16)v1;
        v0 = ...
```
And in the if branch? Let me re-read the orig:
```
    if ((s32)(v0 << 16) < 0) {
        v0 = ((Unkstruct_800B5CB8 *)s0)->unk70;
        v1 = (s16)v1;
        v0 = v0 * 2;
        ...
```
Yes, both branches have `v1 = (s16)v1;`.

Hmm, in the target, the `sll v1,v1,0x10` is at 0x3388 and `sra v1,v1,0x10` at 0x339c. In mine, `sll v0,v1,0x10` at 22 and `sra v1,v0,0x10` at 23. So mine's sll temp is $v0 and the sra dest is $v1. That means `v1 = (s16)v1` produced: temp = v1 << 16; v1 = temp >> 16. The temp is a separate pseudo. In the target, both use v1 (the sll overwrites v1 then the sra).

So the fix: make the sll reuse v1. `v1 = (s16)v1;` should do that... unless gcc's expand creates a temp for the conversion and cse doesn't merge.

Hmm, actually gcc emits `(set (reg v1) (sign_extend:SI (subreg:HI (reg v1) 0)))` which becomes sll+sra with the same reg. But mine shows a temp. Maybe because `v1` is also used as a u16 elsewhere and the type is u16? Let me look at the declarations: `s32 v1;`. `v1 = (s16)v1;` — sign-extend. Should be self.

Wait, maybe the temp is from `(s16)v1` where v1's mode is SImode and the cast is to s16 then implicitly back to s32. gcc: `v1 = (s16)v1` → `(set (reg:SI v1) (sign_extend:SI (subreg:HI (reg:SI v1) 0)))`. The MIPS expander for sign_extend from a subreg might use a temp: `sll temp,v1,16; sra v1,temp,16`. Yes! The MIPS backend's sign-extension pattern uses a temp for the shift. In the target, local-alloc tied the temp to v1 (copy preference? the temp dies into v1). Since `sra v1,temp` — the temp dies at the sra, so local-alloc's tie should make temp = v1. But mine gave the temp $v0.

Why? Because the temp is a block-local qty competing with the branch's v0. Priority: the temp's live range is 1 insn (sll→sra), refs 2, pri = log2(2)*2*4/1 = 1*8=8. The branch's v0 has a longer life → lower priority. So the temp gets $v0.

In the target, the pin forces v0=$2, so the temp can't have it, and local-alloc ties it to v1 ($3).

Lever-free: we need the temp to tie to v1 or v0 to win. Hmm.

What if we write the cast differently: `v1 = (s32)(s16)v1;`? Same. `v1 = (v1 << 16) >> 16;`? That's an arithmetic shift right — gcc may emit sll+sra with a temp too.

What about making v1 an `s16` variable? Then no cast needed: `v1 = ...` but v1 holds u16 sums; the target uses sra. If v1 were s16, the store `sh v1` and the comparisons would still work, but other uses (v1 = v1 + v0) might change.

Hmm, what if we remove the `v1 = (s16)v1;` line? Is it needed? In the target, the sra exists. It's needed for the signed comparison `v0 >= v1`.

What if we use `v1 = (s16)v1;` in only one branch? It's in both.

Alternatively, make the branch's v0 a *shorter* live range so the temp doesn't compete? The temp and v0 are in the same block; both want $2. The temp's pri is higher.

What if we eliminate the sign-extension temp by making the comparison signed differently: `if (v0 >= (s16)v1)`? That's a compare of s32 v0 with sign-extended v1 — the backend would still need the sign extension, maybe as a temp.

Hmm, what if v1 is declared `s16`? Let me test that on top of p02.

Actually, let's reconsider: p02 = 10. The remaining issues: (a) the sign-extension temp in the branches steals $v0; (b) a scheduling difference (nop vs sll). If we fix (a), maybe it becomes 0 or near.

Let me try variants on p02:
- r01: v1 declared `s16` (drop the casts `(s16)v1` → maybe keep; if v1 is s16, `(s16)v1` is a no-op).
- r02: replace `v1 = (s16)v1;` with `v1 = (s32)(s16)v1;`
- r03: replace with `v1 = (v1 << 16) >> 16;`
- r04: replace with `v1 = (s16)(v1 & 0xFFFF);`
- r05: v1 as s16 and remove the casts.
- r06: use `CAST_SIGN` macro? Maybe the codebase has one.

Let me look at what the target's sll/sra are: `sll v1,v1,0x10; sra v1,v1,0x10` — self. So we want the sign-extension to reuse v1. If v1 is `s16`, the load into v1 would be lhu? and the sra? Hmm.

Let me test r01-r05.
