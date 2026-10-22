---
ts: 2026-10-22T00:06:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_fdW6Mu79stoVPnVvXewC
---
Excellent — very informative! The launder-free variant differs mainly by:
- register: a3 vs a2 (the PAN multiply chain lands in a3 instead of a2) and the order of the two multiply chains swapped.
- mine 236 vs target 237 ins (one instruction fewer — the "mfhi a3" / reordering).

Target sequence:
```
sra a2,v0,0x10
bgez a2
move a1,a2
negu a1,a2
lui a0,0x6666
ori a0,a0,0x6667
addiu v0,a2,160
nop
mult v0,a0
mfhi t1
addiu v0,a2,160
nop
mult v0,a0
sra a0,t1,0x6
subu a1,a0,v1
sra v0,v0,0x1f
mfhi a2
sra v1,a2,0x3
subu a2,v1,v0
bne a2,v0
sll a2,a2,0x8
li a2,15
```
Wait, that shows the target has two `addiu v0,a2,160` and two mult v0,a0 — that's the VOL multiply and the PAN multiply. And mine has:
```
sra a3,v0,0x10
bgez a3
move a1,a3
negu a1,a3
lui a2,0x6666
ori a2,a2,0x6667
addiu a0,a3,160
mult a0,a2
mfhi a3
sra a0,a0,0x1f
sra v0,a3,0x3
subu a3,v0,a0
mfhi t1
sra v0,t1,0x6
subu a1,v0,v1
```
So in mine, the PAN multiply (with 0x6666 magic = /20 → wait 0x6667 is magic for /20) comes first, then VOL (/160 uses magic 0x6667? hmm). Anyway: mine order = PAN first, target order = VOL first. Also register a2 vs a3: the PAN chain destination register differs: target a2, mine a3.

So the launder is what keeps the VOL multiply first AND puts PAN in a2.

The VOL multiply: (0xA0 - av)*0x7F/0xA0 → /160. The PAN: (sx+0xA0)/0x14 → /20.

The target's chain: after negu a1,a2 (av in a1), `lui a0,0x6666; ori a0,0x6667` → magic for /160? Let's compute: 0x6667 = 26215. For division by 160: magic. Hmm. Then `addiu v0,a2,160` (a2 = 0xA0 - av), `mult v0,a0`, `mfhi t1`, `addiu v0,a2,160` again?? Interesting — the target has addiu v0,a2,160 twice and mult v0,a0 twice. That's the two chains both computing with the same base? Wait:

Chain A (VOL): v0 = a2 + 160 where a2 = 0xA0-av? Hmm, "addiu v0,a2,160" — a2 is the register holding sx (0xA0 - av). Hmm.

Actually the two chains:
- VOL: ((0xA0 - av) * 0x7F) / 0xA0 = (0xA0-av)*127/160. gcc computes: t = 0xA0-av (a2?), then t*127 → mult with 127, then /160.
- PAN: (sx + 0xA0)/0x14 = (sx+160)/20.

Target order: magic 0x6667 loaded into a0, then `addiu v0,a2,160; nop; mult v0,a0` — this is the PAN chain: (sx + 0xA0) with magic for /20 = 0x6667? Let's check: for /20, magic = 0x6667 (26215): x/20 = (x*0x6667)>>32 ... yes 0x66666667 is the classic magic for /20 (with add). And it needs the add of 160: gcc adds 0xA0? no, for signed division by 20, gcc adds 0xA0? Hmm, the standard: for d=20, magic=0x66666667, add=0xA0 (160/... ) hmm, actually for signed div by 20: M=0x66666667, and the sequence is: mult, mfhi, sra 6, subu with sign. The "addiu v0,a2,160" could be the "add the dividend bias" step? For signed division gcc does `addiu` of (d-1)? no.

Look at the target more carefully:
```
sra a2,v0,0x10        ; sx = (s16)(u16)&sxy  (sign extend of low half)
bgez a2
move a1,a2
negu a1,a2            ; av = |sx|
lui a0,0x6666
ori a0,a0,0x6667      ; magic 0x66666667
addiu v0,a2,160       ; ? v0 = a2 + 160   (a2 = sx)
nop
mult v0,a0            ; 
mfhi t1
addiu v0,a2,160       ; again?
nop
mult v0,a0
sra a0,t1,0x6
subu a1,a0,v1
sra v0,v0,0x1f
mfhi a2
sra v1,a2,0x3
subu a2,v1,v0
```
Hmm, wait: the "addiu v0,a2,160" appears twice with nop between mult. That's the classic gcc-2.7 signed division by constant: 
```
mult
mfhi t1
sra t1,t1,6
subu a0,a0,t1
```
Hmm not exactly.

Actually gcc 2.7 for signed division by constant c uses:
```
div: mult $m, $d ; mfhi $hi ; sra $hi,$hi,s ; subu $r,$d,$hi
```
where s = ceil(log2(c)) and the correction. But 0x6667 magic with 32-bit high multiply and shift 6 is the *unsigned* magic-number division. For signed, gcc 2.7 uses the "add then unsigned" trick: for d=20: M = 0x66666667, add = 0xA0? Hmm: the standard algorithm: n = 0xA0? no.

Let me not over-analyze. The key observation: the target computes the same magic constant (0x66666667) for BOTH divisions? Both /160 and /20? The magic for /160: 0x66666667? Let's check: unsigned division by 160: M = 0x66666667? Hmm, for /20 unsigned: M=0xCCCCCCCC (32-bit) with shift 32. 0x66666667 is for /20? Let's compute: 2^32/20 = 214748364.8 → M = 0x0CCCCCCD. And 0x66666667 = 1717986919 ≈ 2^32/2.5. Hmm, 0x66666667 is the classic magic for /10? For /10: 0xCCCCCCCC. For /5: 0xCCCCCCCD. Hmm 0x66666667 = magic for division by 3? no, /3 = 0xAAAAAAAB.

0x66666667 = 1717986919. 2^33/10 = 858993459. 2^34/20 = 858993459. Hmm 0x66666667*20 = 34359738340 = 8*2^32 - 20 ≈ ... So 0x66666667 = (2^32 - 1)/... let's compute 0x66666667 = 1717986919; times 160 = 274877907040; 2^38 = 274877906944. Close: 274877907040 - 274877906944 = 96. So M ≈ 2^38/160 with error 96. So this magic is for /160 with shift 38-32=6. Yes! `sra a0,t1,0x6` — shift 6 → total 38 bits. So 0x66666667 with shift 6 is the magic for /160.

So both chains in the target use 0x66666667?? The second chain `mult v0,a0; mfhi a2; sra v1,a2,0x3` → shift 3 → total 35 bits: 0x66666667 * 20 = 34359738340 vs 2^35 = 34359738368 → yes! diff -28. So the same magic constant serves /160 (shift 6) and /20 (shift 3). Cute — gcc reuses the constant because both are related? Hmm, 0x66666667 as magic for /20: 0x66666667*20 ≈ 2^35, so shift 3. Yes both.

Wait, but PAN is (sx + 0xA0)/0x14 = (sx+160)/20 — with an "addiu v0,a2,160" bias? For signed division by 20, gcc 2.7's algorithm: M=0x66666667, add 0xA0?? Hmm, "addiu v0,a2,160" adds 160 to sx... but the source says (sx + 0xA0)/0x14. So the addiu is literally the source's +0xA0! And then the division by 20 is done with the unsigned magic trick after adding... hmm, for signed division gcc does: if x<0 handle separately. 

Look: `sra a2,v0,0x10; bgez a2` — the branch bgez a2 is a runtime check for negative (the "if (sx<0) av=-sx" branch). After bgez, the fall-through computes vol = (0xA0-av)*127/160? But the target shows addiu v0,a2,160 using a2 (=sx?) hmm, a2 was sx (sra a2,v0,0x10) and after the negu a1,a2, a2 still = sx. But vol uses av (a1) not sx. Hmm.

Wait: maybe the target's `addiu v0,a2,160` is part of the *PAN* chain (sx+0xA0)/20 and the VOL chain is the one with `mult v0,a0; mfhi t1; sra a0,t1,0x6` — the shift 6 one = /160. But then which operand? "mult v0,a0" where v0 = a2+160 = sx+160. That's the PAN dividend (sx+0xA0) and 0x66666667 shift 6?? that would be /160 not /20.

Hmm, I'm misreading. Let me look at the actual target disassembly around there instead of guessing. Use the tools: `tools/delever_search.py --explain TU FN` prints the target's instructions? It prints mine vs target diff only. Maybe `tools/masked_scorer.py` can dump. Or cc1 dumps.

Better: let me get the target assembly directly. Where's the target baseline object? oracle.baseline_path(rec["obj"]). Perhaps simpler: the asm source in asm/nonmatchings/. Let me find the target .s file for this function: asm/nonmatchings/ov_SC02_026/... Let me search.

Actually, a faster approach: the diff output above gives me both. Let me get the full target instruction list around the tail. I can use --explain on the current src body (score 0) — it prints nothing if identical. Hmm.

Alternative: use tools/masked_scorer.py? Let me check what tools/asm-differ or masked_scorer offer. Or simply read the target .s file: asm/nonmatchings/ov_SC02_026_jr_8017C180.s maybe.

Let me find it.
