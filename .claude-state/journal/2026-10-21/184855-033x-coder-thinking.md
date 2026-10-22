---
ts: 2026-10-22T00:48:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_SdDJ1cIUwx3j5EJKNy2Y
---
Huge improvement: score 29 → 7. Remaining differences:

1. Branch targets (j/bltz/beqz) differ — these are just address differences because the function size differs by 1 instruction (mine 110 vs target 111). The j target offsets differ because of the missing instruction. So those 4 diffs are consequences.

2. mine[79:81] vs target[79:81]:
   - mine[79] = bne a2,v0,988 | target[79] = bne a2,v0,98c
   - mine[80] = ori a1,a1,0x3000 | target[80] = sll a2,a2,0x8
   - insert: mine[84] -- | target[84] = ori a1,a1,0x3000

So in mine, the `ori a1,a1,0x3000` is at position 80 (right after the bne, i.e. in the delay slot of the branch), while in the target it's at position 84 (later). And the target has `sll a2,a2,0x8` at 80 (mine has that at 81 presumably).

So the target's order is: bne (80), sll a2 (80?) hmm.

Let me reconstruct. Target:
79: bne a2,v0,98c
80: sll a2,a2,0x8
81: li a2,15  (?)
82: sll a2,a2,0x8
83: ?
84: ori a1,a1,0x3000
85: or a1,a1,a2

Mine:
79: bne a2,v0,988
80: ori a1,a1,0x3000
81: sll a2,a2,0x8
82: li a2,15
83: sll a2,a2,0x8
84: (something)
85: or a1,a1,a2

Hmm, the diff said "replace mine[79:81] target[79:81]" (2 mine, 2 target) then "insert mine[84:84] target[84:85]" (1 target inserted). So the target has one MORE insn in this region: total 111 vs 110.

The target's region: 79 bne, 80 sll, 81 li, 82 sll, 83 ?, 84 ori a1,a1,0x3000, 85 or a1,a1,a2. That's 7 insns (79-85). Mine: 79 bne, 80 ori, 81 sll, 82 li, 83 sll, 84 or a1,a1,a2? and mine[84:85] vs target[85:86] earlier showed "84 or a1,a1,a3 | or a1,a1,a2".

So in mine the `ori a1,a1,0x3000` comes right after the bne (in the delay slot), and in the target it comes later (at 84, right before the final or).

Why? Because in the target, the `ori a1,a1,0x3000` (which is my `vol | 0x3000`) is NOT part of the vol chain — in the target the vol|0x3000 happens later, after the x<<8 chain.

Hmm! Interesting. So in the target (with the launder), the ordering is: the vol chain ends, then the x chain (sll/li/sll), then the ori 0x3000, then the final or.

In mine (with `vol = vol | 0x3000` placed early), the ori is scheduled early (in the bne's delay slot) because it's ready earlier.

So the difference: in the target, the vol|0x3000 op is ordered AFTER the x<<8 chain. That suggests the launder's 2nd set is NOT at the position of the asm but later...

Hmm, wait. Actually maybe in the target, `vol | flg` is a separate computation that got scheduled late, whereas my `vol = vol | 0x3000` creates a dependency chain: vol → ori → later or. Both are chains. But the scheduling differs because in the target the asm (pri 1) sits between, and the ori (vol|flg) is a separate insn with a later LUID?

Alternatively, maybe in the target, the vol|flg is computed as part of the *final* expression: `((vol | flg) | x) & 0xFFFF` — the target's final sequence would be: ori a1,a1,0x3000 (a1 = vol), then or a1,a1,a2 (x). So the target computes vol|0x3000 then |x.

In mine, I merged flg into vol early, so the chain is vol → ori → (later) or with x. The ori can be computed as soon as vol is ready, hence earlier.

To reproduce the target's order, the `| 0x3000` should be applied at the END, i.e. keep `((vol | flg) | x) & 0xFFFF` as in the original but with a 2nd set of vol created earlier. Hmm — but then the 2nd set must be a separate op that doesn't change the value...

Wait. Let's reconsider: maybe the launder's role isn't a "2nd set of vol" but something else entirely. Let me look at the target's region again:

Target:
```
79 bne a2,v0,98c
80 sll a2,a2,0x8
81 li a2,15      (probably)
82 sll a2,a2,0x8
83 ? 
84 ori a1,a1,0x3000
85 or a1,a1,a2
```
Hmm, mine[84:85] ↔ target[85:86]: mine[84] = or a1,a1,a3; target[85] = or a1,a1,a2. So target[85] = or a1,a1,a2 — matches "final or". So target[84] = ori a1,a1,0x3000 and target[83] = ? (some insn equal to mine's?).

Let's figure out mine's full list 79-85:
mine[79] bne a2,v0,988
mine[80] ori a1,a1,0x3000
mine[81] sll a2,a2,0x8
mine[82] li a2,15
mine[83] sll a2,a2,0x8
mine[84] or a1,a1,a3
mine[85]? = andi a1,a1,0xFFFF presumably (target[86])

And target:
79 bne
80 sll a2,a2,0x8
81 li a2,15
82 sll a2,a2,0x8
83 andi? no...
84 ori a1,a1,0x3000
85 or a1,a1,a2
86 andi a1,a1,0xFFFF

So the target has one extra insn vs mine in this region. The extra is at target[83]. And in mine, `ori a1,a1,0x3000` is at 80 and there's nothing at 83.

Hmm, so the target has an extra instruction between the sll chain and the ori. What could it be? Maybe `andi a1,a1,0xFFFF` BEFORE the ori? I.e. the target computes: a1 = vol & 0xFFFF; a1 |= 0x3000; a1 |= x. Hmm, but the final andi...

Actually maybe the target's order is:
83: andi a1,a1,0xFFFF   (vol & 0xFFFF)
84: ori a1,a1,0x3000
85: or a1,a1,a2
and no final andi? Since (vol|0x3000|x)&0xFFFF = ((vol&0xFFFF)|0x3000)|x (as x's low bits... hmm, x = x<<8 so x's low 8 bits are 0; 0x3000 has bits within 0xFFFF). ((vol|0x3000)|x)&0xFFFF = (vol&0xFFFF)|0x3000|(x&0xFFFF). So gcc could compute andi first then ors. That works if gcc reassociates.

So the target's structure could be: `andi a1,a1,0xFFFF` then `ori a1,a1,0x3000` then `or a1,a1,a2`.

And in mine: `ori a1,a1,0x3000` (early) ... `or a1,a1,a3` then `andi a1,a1,0xFFFF` at the end. So mine has the andi at the end (1 andi total) and the target has the andi before the oris (1 andi total) — but the target has one MORE insn in this region (111 vs 110 total).

Hmm, so where does the target's extra instruction come from? Let me count: target region 79-85 = 7 insns; mine 79-84 = 6 insns (bne, ori, sll, li, sll, or) + andi = 7. Hmm, so if mine[85] = andi and target[86] = andi, then the difference is elsewhere.

Wait, the diff said the replace block mine[79:81] ↔ target[79:81] then insert mine[84:84] target[84:85], then earlier replace mine[84:85] target[85:86]. These are separate opcodes but difflib's opcodes are ordered and non-overlapping: replace(79:81), then equal(81:84 ↔ 81:84), then insert(84:84 ↔ 84:85), then replace(84:85 ↔ 85:86)? That can't be — insert at mine[84:84] and replace mine[84:85] overlap in mine. Actually difflib opcodes: 'insert' means i1==i2 (empty in mine), so insert mine[84:84] target[84:85] inserts one target insn before mine[84]. Then replace mine[84:85] target[85:86].

So: equal region mine[81:84] ↔ target[81:84]; then target[84] inserted; then mine[84] ↔ target[85].

So mine[81],[82],[83] = target[81],[82],[83] (equal, not shown): sll a2,a2,0x8 / li a2,15 / sll a2,a2,0x8 presumably.
target[84] = ori a1,a1,0x3000 (inserted).
mine[84] = or a1,a1,a3 ↔ target[85] = or a1,a1,a2.

And mine[80] = ori a1,a1,0x3000 ↔ target[80] = sll a2,a2,0x8 (the replace block mine[79:81] ↔ target[79:81]: mine[79] bne ↔ target[79] bne; mine[80] ori ↔ target[80] sll).

So: mine has the ori at 80, target has it at 84. Both have the same total except the target has ONE MORE insn somewhere (111 vs 110). The insert at target[84] IS that extra insn? No — the insert means target[84] is an extra insn not in mine at that position; but mine[80] = ori = target[84] in content. difflib doesn't match them because of position.

So both have one ori. Then where's the extra insn? Total: mine 110, target 111. The diff blocks: replace(79:81 → 79:81) [same size], insert(84:84 → 84:85) [+1 target], replace(84:85 → 85:86) [same size]. Plus the 4 branch-target replaces (same size). So the target has 1 extra insn: at position 84. And mine has an ori at 80 while target has an sll at 80.

Hmm, so the target's insn list 79-86:
79 bne
80 sll a2,a2,0x8
81 li a2,15
82 sll a2,a2,0x8
83 = mine[83] (equal) — what is mine[83]? If mine[83] = sll a2,a2,0x8 then target has 2 sll's and a li.

Let me reconstruct mine:
79 bne a2,v0,988
80 ori a1,a1,0x3000
81 = target[81] (equal)
82 = target[82]
83 = target[83]
84 or a1,a1,a3

Since mine[80] is the ori and mine[81..83] equal target[81..83], and mine[79] = bne. Target[80] = sll a2,a2,0x8.

So the sequence of "sll/li/sll" is at target 81,82,83 (3 insns: sll, li, sll) and mine at 81,82,83 as well. And target[80] = sll a2,a2,0x8 is an EXTRA sll in the target?! Hmm no: target[80] = sll a2,a2,0x8 and mine[80] = ori. The "extra" insn in the target is at 84 (the ori). So target = [bne, sll, sll?, li, sll, ori, or] hmm, that has an extra sll.

Let me re-examine: maybe the equal region mine[81:84] ↔ target[81:84] is [sll, li, sll] in mine and in the target [sll, li, sll]. And target[80] = sll a2,a2,0x8 is a 4th insn of that family?

The x computation: x = (x+0xA0)/0x14; if (x==0x10) x = 0xF; x = x << 8; then | x.

The asm: `sll a2,a2,0x8` then `li a2,15` then `sll a2,a2,0x8` — that's the "x == 0x10 → x = 0xF" then x<<8. Actually: x<<8 (sll a2,a2,8) then if x==0x10 → x=0xF (li a2,15) then sll a2,a2,8 again. Hmm.

So the target has: sll(8), li 15, sll(8) — 3 insns (81,82,83), and target[80] = sll a2,a2,0x8 is a FOURTH? That can't be.

Unless mine[80]=ori ↔ target[80]=sll is a mis-pairing, and the true picture is:
mine: [79 bne][80 ori][81 sll][82 li][83 sll][84 or]...
target: [79 bne][80 sll][81 ???][82 li][83 sll][84 ori][85 or]

with target[81] = sll (equal to mine[81]). So the target has an extra sll at 80. Total target = 111 = mine 110 + 1. ✓.

So the target has an EXTRA `sll a2,a2,0x8` compared to mine. Hmm! Why?

Because in the target, `x = x << 8;` appears... hmm. Wait: in the source, `x = x << 8;` — and the asm's `sll a2,a2,8` — maybe in the target, the `x = 0xF` branch has `li a2,15; sll a2,a2,8` and there's an additional sll from `x = x << 8` outside the if. So target: x<<8 (sll), then in the if-branch: li 15, sll 8. That's 3 total, not 4.

Unless the target's x<<8 happens twice: hmm.

OK, since both mine and target come from nearly the same source (only the vol 2nd-set differs), an extra sll in the target is strange. Unless the diff alignment is off by one somewhere earlier, i.e. there's an extra insn earlier in the target that I attributed differently.

Ugh, the diff blocks before this region: the 4 branch-target replaces (j, bltz, beqz, beqz) are the same size. So no extra insn before 79.

Hmm, so between 55 and 79 both have the same count. At 56-78 the big replace block: mine[56:64] ↔ target[56:62] (8 vs 6 = -2 for target), delete mine[66:67] target[64:64] (-1), replace mine[69:73] ↔ target[66:71] (4 vs 5 = +1), replace mine[74:77] ↔ target[72:78] (3 vs 6 = +3). Net: -2-1+1+3 = +1 → target has 1 more insn in 56..78. ✓ consistent with the total difference (111 vs 110).

So the target's chain region has one extra instruction compared to mine. And in the 79-85 region: target has one extra (the sll at 80) and mine has the ori at 80 vs target at 84.

Hmm, so where's the extra in the chain? Let me carefully reconstruct both chains:

MINE (from diff):
56 sra a3,v0,0x10
57 bgez a3,930
58 move a1,a3
59 negu a1,a3
60 lui a2,0x6666
61 ori a2,a2,0x6667
62 addiu a0,a3,160
63 mult a0,a2
64 = equal (target[62]) = ?
65 = equal (target[63]) = ?
66 mfhi a3 (deleted)
67 = equal target[64] = ?
68 = equal target[65] = ?
69 mult v1,a2
70 sra a0,a0,0x1f
71 sra v0,a3,0x3
72 subu a3,v0,a0
73 (--)
74 mfhi t1
75 sra v0,t1,0x6
76 subu a1,v0,v1
77 (--)
78 bne a3,v0,988

TARGET:
56 sra a2,v0,0x10
57 bgez a2,930
58 move a1,a2
59 negu a2? no: "negu a1,a2"
60 lui a0,0x6666
61 ori a0,a0,0x6667
62 = mine[64]
63 = mine[65]
64 = mine[67]
65 = mine[68]
66 mult v1,a0
67 mfhi t1
68 addiu v0,a2,160
69 nop
70 mult v0,a0
71 sra a0,t1,0x6
72 subu a1,a0,v1
73 sra v0,v0,0x1f
74 mfhi a2
75 sra v1,a2,0x3
76 subu a2,v1,v0
77 bne a2,v0,98c

Hmm interesting. Now compare the two chains semantically:

MINE:
```
mult a0,a2       ; a0 = (160-ax) [computed at 62], a2 = M → a0 = (160-ax)*M
[64] mflo a0     ; probably
[65] ???
mfhi a3          ; 66
[67] sra?
[68] ?
mult v1,a2       ; v1 = 127? * M
sra a0,a0,0x1f   ; sign of the lo part
sra v0,a3,0x3    ; hi >> 3
subu a3,v0,a0    ; correction
[73] ?
mfhi t1          ; 74
sra v0,t1,0x6
subu a1,v0,v1
```
TARGET:
```
[62] = mine[64]
[63] = mine[65]
[64] = mine[67]
[65] = mine[68]
mult v1,a0       ; v1 * M
mfhi t1
addiu v0,a2,160  ; v0 = 160-ax
nop
mult v0,a0
sra a0,t1,0x6
subu a1,a0,v1
sra v0,v0,0x1f
mfhi a2
sra v1,a2,0x3
subu a2,v1,v0
```

Interesting: the target's chain has `sra a0,t1,0x6; subu a1,a0,v1` where t1 = mfhi(v1*M) and v1 = 127?? and a1 = (hi(127*M)>>6) - 127. hi(127*0x66666667) = 50; 50>>6 = 0; so a1 = -127.

And the target's `mfhi a2; sra v1,a2,0x3; subu a2,v1,v0` where v0 = 160-ax: hi((160-ax)*M) >> 3?? Hmm, >>3 not >>6.

Hmm, that's a /20 division (shift 5?) no...

Wait, maybe I've got the wrong pairing. Let me reconsider: maybe the target's `mult v1,a0` where v1 = 0x7F=127 computes 127*M; then `mfhi t1`; `sra a0,t1,0x6`; `subu a1,a0,v1` → a1 = ((hi(127*M))>>6) - 127.

For a division of the form (n*127)/160 where the numerator is 160-ax: hmm.

Alternatively, this is the DIVISION BY 160 of the value 127*(160-ax)?? Let's compute differently: maybe gcc rewrote ((0xA0-ax)*0x7F)/0xA0 as (0x7F*0xA0 - 0x7F*ax)/0xA0 = 0x7F - (0x7F*ax)/0xA0. Then q = (127*ax)/160.

For that, gcc computes n = 127*ax (a mult by 127!) then magic-divide by 160.

The observed target: `addiu v0,a2,160` = 160-ax — hmm, that's not ax.

You know what? Let me instead consider that mine and target both compute the SAME thing but with different instruction scheduling, and the extra instruction in the target is a `nop` (target[69] = nop!). Yes! target[69] = nop. That's the extra instruction!

So the target's chain = mine's chain + 1 nop, reordered.

So: the target's chain:
```
62 mult v1,a0? ...
```
Hmm, let's redo with the nop:
target[66] mult v1,a0; 67 mfhi t1; 68 addiu v0,a2,160; 69 nop; 70 mult v0,a0; 71 sra a0,t1,0x6; 72 subu a1,a0,v1; 73 sra v0,v0,0x1f; 74 mfhi a2; 75 sra v1,a2,0x3; 76 subu a2,v1,v0; 77 bne a2,v0.

And mine:
62 addiu a0,a3,160; 63 mult a0,a2; 64 ?; 65 ?; 66 mfhi a3; 67 ?; 68 ?; 69 mult v1,a2; 70 sra a0,a0,0x1f; 71 sra v0,a3,0x3; 72 subu a3,v0,a0; 73 ?; 74 mfhi t1; 75 sra v0,t1,0x6; 76 subu a1,v0,v1; 77 ?; 78 bne a3,v0.

Both have the same instruction multiset except mine has an extra... hmm. Mine: mult, mfhi, mfhi, sra, sra, subu, mult, sra, subu — and target: mult(v1,a0), mfhi, addiu, mult(v0,a0), sra, subu, sra, mfhi, sra, subu. Both have 2 mults, 2 mfhis, etc. Plus the nop in the target.

So the target = same instructions in a different ORDER + a nop.

So mine needs: the mult of the CONSTANT (127) to come BEFORE the mult of the variable numerator, and a nop in the right place.

Hmm, the nop: gcc emits nops for delay-slot filling when the reordered instruction can't fill a delay slot (e.g. a `mult` can't be in a delay slot? Actually mult has a 5-cycle latency and gcc avoids putting it in a delay slot? No — gcc 2.7 can't put mult in a delay slot? It can.)

Hmm, the nop appears because sched2 couldn't fill a delay slot.

The key ordering difference: the target does `mult v1,a0` (constant * magic) FIRST, then `mfhi t1`, then `addiu v0,a2,160`, `nop`, `mult v0,a0`.

Mine does `addiu a0,a3,160` (numerator), `mult a0,a2` (numerator*magic) first, then later `mult v1,a2` (constant*magic).

So the difference is the order of the two mults. In the target, the constant mult is first. This is the "birth boost": the constant 127's multiply is a single-set pseudo → boosted → scheduled early.

In mine, the numerator's mult came first. Why? Because in mine, the numerator chain (addiu + mult + mfhi) has a higher priority?

The launder's effect: with the launder, vol has 2 sets → the division's *result* has 2 sets → the chain's "birth" priority changes.

Hmm, but in my cand02, vol also has 2 sets (division, then |0x3000). Yet the order still differs. But wait — in cand02 the residual is only 7 and the chain order... let me check cand02's diff: the diff showed only the branch targets and the region 79-85. So cand02's chain (56-78) MATCHES the target! Only the tail region differs (the ori position) plus the size difference.

So cand02 already fixed the chain order! The remaining issue: the extra `ori` position and the extra sll in the target at 80.

So now the residual is:
- target[80] = sll a2,a2,0x8 (an extra sll), target[84] = ori a1,a1,0x3000
- mine[80] = ori a1,a1,0x3000, mine[81..83] = sll,li,sll, mine[84] = or a1,a1,a3

Hmm, so the target has FOUR insns in the sll family? Let's see: target[80] = sll a2,a2,0x8, target[81],[82],[83] = mine[81],[82],[83] = sll?, li 15, sll? Hmm — mine[81],[82],[83] are equal to target[81..83] but I don't know what they are. From the earlier cand01 diff, mine[79] = sll a3,a3,0x8; mine[80] = li a3,15; mine[81] = sll a3,a3,0x8 — but that was cand01's indices (different numbering). In cand02, the region shifted.

Let me get cand02's diff with more context — the diff only prints changed blocks. I need to see the insns around 79-85 in both. Since equal regions aren't printed, let me reason:

cand02's mine list (guessing):
79 bne a2,v0,988
80 ori a1,a1,0x3000
81 sll a2,a2,0x8
82 li a2,15
83 sll a2,a2,0x8
84 or a1,a1,a3
85 andi a1,a1,0xFFFF (probably)
86 ...

target:
79 bne a2,v0,98c
80 sll a2,a2,0x8
81 sll a2,a2,0x8?
82 li a2,15
83 sll a2,a2,0x8
84 ori a1,a1,0x3000
85 or a1,a1,a2
86 andi?

Hmm, so the target has: sll, [sll?], li, sll, ori, or. Mine: ori, sll, li, sll, or.

Wait, mine[81],[82],[83] equal target[81],[82],[83]. If mine[81] = sll, [82] = li, [83] = sll, then target[80] = sll is an EXTRA sll in the target.

Hmm! An extra sll a2,a2,0x8. Where would that come from? `x = x << 8;` plus `x = x << 8` inside the if? Look at the source:

```
x = (x + 0xA0) / 0x14;
if (x == 0x10) {
    x = 0xF;
}
x = x << 8;
```
Only ONE x<<8. But the compiler might compute: t = x<<8; if (x==0x10) t = 15<<8; i.e. the shift is duplicated in both arms of the branch! Since x<<8 is computed in the common path, then the branch overrides with (0xF<<8). GCC might do: v = x<<8 (common), then if (x==0x10) v = 0xF00 → `li a2,15; sll a2,a2,8` in the branch arm, else v stays.

So the structure:
common: sll a2,a2,8 (x<<8)
branch (x==0x10): li a2,15; sll a2,a2,8
That's 3 sll-ish insns: sll, li, sll. Plus the target has an extra sll at 80 — hmm, so the target has 2 sll before the li?

Target: 80 sll a2,a2,8; 81 sll?; 82 li 15; 83 sll a2,a2,8.

Hmm, maybe target[81] = sll a2,a2,8 is the same as mine[81] = sll a2,a2,8. So target has sll at 80 AND 81. Two sll's in a row. That's odd unless one is x<<8 and the other... hmm, x<<8 and then (x==0x10 ? 15<<8 : x<<8)?

Hold on. Maybe the register differs: mine[81] might be `sll a2,a2,0x8` and target[81] the same. Fine.

Alternatively maybe I mis-assume and target[80] = "sll a2,a2,0x8" comes from the `x = x << 8` and mine[81] = sll a2,a2,0x8 is the SAME instruction but the diff alignment is shifted because of an extra insn earlier. Hmm, difflib's alignment is what it is.

Let's take a different approach: instead of guessing, let me use the `x` structure. The key question: how do I get the `ori a1,a1,0x3000` to be scheduled AFTER the sll chain (at position 84) rather than before it (position 80)?

In the target, the order is: sll, sll, li, sll, ori, or.
In mine: ori, sll, li, sll, or.

The `ori` (vol|0x3000) is delayed in the target. In the target, this ori is the `vol | flg` from the ORIGINAL source (which is inside the flg block: `((vol | flg) | x) & 0xFFFF`). In the original (launder) version, the order of `vol|flg` relative to the x chain is late.

In my cand02, I moved the |0x3000 to be right after the vol computation (early), and gcc scheduled the ori early.

So: keep the ORIGINAL expression `((vol | flg) | x) & 0xFFFF` (so the ori stays late), but still create a 2nd set of vol early to get the chain order right.

How to create a 2nd set of vol early without changing the value/order? Options:
- `vol = vol | 0;` → gcc folds `x|0` → x. Actually gcc's fold for `x | 0` → x (for integers, yes: (x|0) == x). It'd be folded at the tree level → no 2nd set.
- `vol = vol + 0;` → folded.
- `vol = vol ^ 0;` → folded.
- `vol &= 0xFFFFFFFF;` → gcc folds to vol (bitwise and with all ones) → folded.
- `vol = vol * 1;` → folded.
- `vol += 0;` → folded.

Hmm. What about using a different type to force a real 2nd set? E.g. `vol = (s16)vol;`?? changes value.

Alternatively: create the 2nd set on a DIFFERENT variable: e.g. `s32 v2 = vol;` — copy; flow/cse folds it (copy propagation) → probably no real 2nd set.

Hmm, but in the ORIGINAL (with launder), the asm output V is a new pseudo V = copy of vol, and the use `vol|flg` reads V. The copy is NOT folded because it's an asm.

In plain C, `s32 v2 = vol;` then use v2 — gcc's RTL: set v2, vol; then use v2. Copy propagation (flow) would replace v2 with vol → same as before. But if the copy is used ONCE and vol is used once, gcc's RTL "copy" might survive as a real insn? gcc usually eliminates it.

BUT: what if the copy's use is far away and the copy is a "real 2nd set"? The point of the launder was to make the vol chain's result have 2 sets, killing the birth boost of the chain.

Hmm, what about the "G11" trick applied here: `vol = vol | 0x3000` gives a real 2nd set but changes the value and the position of the or.

Alternatively: `vol = vol | 0x3000;` placed LATE (at the flg block, i.e. in the original position of `vol | flg`):
```
{
    s32 flg = 0x3000;
    vol = vol | flg;
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
}
```
This creates the 2nd set of vol at the LATE position (where the original `vol|flg` was) — but then does the chain order come out right? The chain order effect (which mult first) might depend on where the 2nd set is. In cand02 the 2nd set was early and the chain matched. Let me try the late version (cand03) — it's cheap.

Also try: keep `vol | flg` inline in the expression (as the original) AND add an early 2nd set that's value-neutral. Hmm.

Let me think about what makes the difference between "ori early" and "ori late". In the target, the ori is late. In cand02, the ori is early because it was in the source early. So the source position determines it (sched1 keeps source order mostly).

So for the target's order, the `|0x3000` must be at the late source position → cand03 (the flg-block version).

But will cand03 give the right chain order (the mults)? The launder was early (right after vol's computation). Hmm, in cand03 the 2nd set is late. Let's just test.

Actually — maybe better: what if the 2nd set is early but value-neutral in a way gcc keeps? Like `vol = vol & ~0;`? folded.

What about making the 2nd set through a variable that gcc can't fold: e.g.
```
s32 vol2;
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol2 = vol;       /* copy: gcc may keep it as a real insn? */
... later ...
func_8002D4C8(0x93E, ((vol2 | flg) | x) & 0xFFFF);
```
The copy `set vol2, vol` — gcc's RTL copy propagation in `flow` (pass_flow) would substitute vol2 → vol, killing the 2 sets. But maybe not if it changes the "birth" analysis... worth a try (cand04).

Let me try cand03 first (late compound assign).

Also I realize: maybe a cleverer approach — what if the 2nd set is created by an assignment to a DIFFERENT variable of a wider/narrower type? e.g. `s16 vol16 = vol;`? changes value (truncates) — but vol's range fits in s16? vol = ((0xA0-ax)*0x7F)/0xA0 ≤ 127. So s16 is fine. But then using vol16 in the expression would give the same value. The truncation creates a real 2nd set (slli/sra pair) → adds insns. No good.

Let me test cand03 and cand04.

cand03: keep `vol | flg` inline as the original but ALSO add an early real 2nd set? Can't have both easily.

Let me do:
cand03:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
x = (x + 0xA0) / 0x14;
if (x == 0x10) x = 0xF;
x = x << 8;
{
    s32 flg = 0x3000;
    vol = vol | flg;
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
}
```
cand04: early neutral copy:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol2 = vol;
x = ...
{ s32 flg = 0x3000; func_8002D4C8(0x93E, ((vol2 | flg) | x) & 0xFFFF); }
```

Let me write both and score both. I can run two --try calls in one Bash command? They're separate commands; I can chain with `&&`? The permission system denied `;` chains. Let me try running them in one command separated by newline (that's still multiple operations). Hmm, earlier a multi-op command was denied because of the pipe/`;`. Let me try two separate Bash tool calls in parallel in one block — that's allowed (independent calls).

Let me write both files then score both in parallel.
