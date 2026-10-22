---
ts: 2026-10-21T23:48:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YfEuXoF7sqRMv5gHlfPN
---
The regex is generic. So "jr $ra" would be captured.

So why did my probe compile to 2 instructions? Maybe the probe compiled to:
```
move v0,zero
jr $ra
```
with the delay slot filled by... `nop` would be a 3rd. Actually gcc for `return 0` at -O2 emits:
```
move v0,zero
jr $ra
nop
```
3 instructions. Unless the function's last instruction is `jr $ra` with the delay slot being the `move v0,zero`? No, the delay slot follows jr.

Hmm! Unless the tool's extraction for my probe returned 2 because the object's function label didn't match and it fell back to the whole .text section?? No, that'd be more.

Wait — maybe my probe's compile FAILED and it used a different fallback? "mine 2 ins" hmm.

Whatever. Let me look at the actual comparison from the earlier nopin diff: it showed target[34:35] = "j 6abc" and mine[36:37] = "j 6ac4" — a `j` to a local label. If the epilogue (`jr $ra`) were included, both would show it.

Conclusion: the extracted function text seems to lack the `jr $ra` — probably because these ov "tail" objects are fragments: the function's code is split and the epilogue lives in the next fragment (the objects are named tail.data.o, tail2.data.o, ... suggesting the TU's .text is split into chunks with the epilogue in a later chunk). Hmm, but then the extraction of "the function" from the object containing the label would only include the part in that object.

Hmm, but that would make the baseline and candidate equally partial. Fine.

So the ROM function as scored = 39 ins without the epilogue. My job: match those 39.

Given that, the "target" tail:
```
30 nop
31 lw v0,376(a0)
32 nop
33 xor v0,v0,a1
34 j +0x94
35 sltu v0,zero,v0
36 move v0,zero
37 ?
38 nop
```
And +0x94 = ins 37.

Since ins 37 is unknown (it was "equal" to my probe's ins 0 — my probe's first ins = "move v0,zero"), so target[37] = "move v0,zero"?? and target[38]="nop" vs mine[1]="move v0,zero"...

Hmm, that gives target[36]="move v0,zero" AND target[37]="move v0,zero"? My probe's 2 ins = ["move v0,zero", "jr $ra"]? Then mine[0]="move v0,zero" == target[37] → target[37]="move v0,zero"; mine[1]="jr $ra" vs target[38]="nop" → but the printed line said mine[1]="move v0,zero" | target[38]="nop". Contradiction.

Unless the printed line's mine column was mine[1]... Let me re-read the printed output:

```
  replace mine[1:2] target[38:39]
        1  move	v0,zero                       | nop
```
Format: f"{i1+k:4d}  {m_:34s} | {t_}" → "    1" is i1+k = 1 → mine[1]; m_ = mine[1] = "move v0,zero"; t_ = target[38] = "nop".

So mine[1] = "move v0,zero" and mine[0] == target[37].

So my probe compiled to [X, "move v0,zero"] where X == target[37]. If X = "jr $ra"?? then my probe = "jr $ra; move v0,zero" — that's not a valid order for `return 0` (gcc: move v0,zero; jr $ra; nop).

UNLESS the tool's off/word extraction is fine but the ORDER of the insns list is by objdump order... yes it is.

Hmm, alternatively: mine[0] = "nop" (the delay slot) and target[37] = "nop" too! And mine[1] = "move v0,zero"?? For that, my probe's asm order would be [nop, move v0,zero] — no.

OK here's another possibility: the probe's body `return 0;` in a function that gcc compiled as:
```
jr $ra
move v0,zero    <- delay slot of jr!
```
That's what gcc does for a leaf function returning a constant?? No: gcc puts `move v0,zero` BEFORE `jr $ra` normally, with `nop` in the delay slot. But with -O2 and reorder, gcc may emit `jr $ra` with the delay slot being the move! Actually yes! Modern gcc does: `jr $ra; move v0,zero` (the move in the delay slot). For gcc 2.7.2 (this old MIPS target), the epilogue is often:
```
jr $ra
move v0,v0
```
Hmm.

If my probe = ["jr $ra", "move v0,zero"], then mine[0]="jr $ra" == target[37] → target[37] = "jr $ra" ✓✓ and mine[1]="move v0,zero" vs target[38]="nop" ✓ (target's delay slot after jr $ra is a nop!).

So the ROM's tail is:
```
36 move v0,zero     ; return-0 path
37 jr $ra
38 nop              ; delay slot
```
And +0x94 = ins 37 = "jr $ra" → the branches to +0x94 are RETURN branches (returning v0 as-is).

So now the semantics: branch at 22 (arg2==9) → jr $ra with v0 = 0 (the `and` result) → returns 0! And branches 25,27,29 → v0=1 → returns 1. And the branch at 10/20 → +0x90 = ins 36 `move v0,zero` → returns 0. And ins 34 `j +0x94` + delay `sltu v0,zero,v0` → returns (v0 != 0).

Great, now the picture is complete:

```
 0 lhu v0,0(a1)
 1 nop
 2 beqz v0,RET(0x94)      ; delay: move v0,zero → returns 0
 3 move v0,zero
 4 lw v0,88(a1)
 5 nop
 6 beqz v0,RET
 7 move v0,zero
 8 lhu v0,94(a1)
 9 nop
10 beq v0,a2,0x90         ; *(&0x5E) == arg2 → skip block → return 0
11 li v1,0x8000
12 lw v0,92(a1)
13 nop
14 andi v0,v0,0xc100
15 bne v0,v1,RET          ; → return 0 (v0 != 0x8000)
16 move v0,zero
17 lh v0,174(a1)
18 andi v1,a3,0xffff
19 and v0,v0,v1
20 bnez v0,0x90           ; mask != 0 → return 0
21 li v1,9
22 beq a2,v1,RET          ; arg2 == 9 → return v0 (=0!)
23 li v0,1                ; v0 = 1  (only reached when arg2 != 9)
24 li v1,17
25 beq a2,v1,RET          ; → return 1
26 li v1,41
27 beq a2,v1,RET
28 li v1,10
29 beq a2,v1,RET
30 nop
31 lw v0,376(a0)
32 nop
33 xor v0,v0,a1
34 j RET
35 sltu v0,zero,v0
36 move v0,zero
37 jr $ra
38 nop
```

So the ROM's `v0 = 1` is sunk to ins 23 (after the first compare). This is exactly gcc's behavior when the assignment `v0 = 1` is *not* the first statement but the compares use v1.

Hmm wait, in the source, `v0 = 1;` IS the first statement of the innermost block, and `v1 = 9; if (arg2 == v1) return v0;` follows. gcc's scheduler (sched1) sank the `li v0,1` past the `li v1,9` and the `beq`?? That's a "birth boost" thing: sched1 boosts the birthing instruction of a pseudo... Per moves.md: "sched1-birth-boost — sched1 boosts the single-set la s3 (birthing) past the jal". So sched1 can reorder a set relative to branches.

Hmm, but semantically the `beq` at 22 branches to RET which returns v0 — with the `li v0,1` sunk past it, the RET path would return v0=0 rather than 1. gcc wouldn't do that if it changes semantics! Unless... the RET block at +0x94 is `jr $ra` and the branch at 22 → jr $ra with v0 = whatever. If gcc sank the li v0,1 past the beq, the beq path returns 0 instead of 1 — a semantic change gcc wouldn't make.

Unless the source's semantics really are: the first compare `if (arg2 == v1) return v0;` — with v0 uninitialized?? No, v0=1 comes first.

Hmm, unless the ROM's `beq a2,v1,+0x94` at 22 is NOT the first compare! Let me re-map: maybe ins 21 `li v1,9` + ins 22 `beq a2,v1,RET` is the compare for 9, and `li v0,1` at 23 is the v0=1 assignment sunk... but the branch at 22 goes to RET which needs v0=1.

Unless RET is not `jr $ra` but a block that sets v0=1? But we determined +0x94 = ins 37 = "jr $ra" (equal to my probe's ins 0 = "jr $ra"). Hmm, but that equality is with masked_word comparison — masked_word masks relocations; "jr $ra" vs "jr $ra" ✓.

So the beq at 22 → jr $ra → returns v0 = 0 (the `and` result). Semantically the ROM returns 0 for arg2==9 — a ROM quirk. And gcc's compilation of the pinned C reproduces it — meaning gcc DOES sink the `li v0,1` past the beq, changing semantics?! That can't be; gcc wouldn't.

...Unless the pinned C's `v0 = 1;` is NOT the first statement of the block. Let me re-read the src:

```c
if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
    v0 = 1;
    v1 = 9;
    if (arg2 == v1) return v0;
    ...
```
Yes, v0=1 is first.

Hmm, so how does gcc produce `li v0,1` AFTER the beq? OH WAIT. Maybe the `beq a2,v1,RET` is not "arg2 == v1 → return". Let me reconsider: maybe the branch polarity: `beq a2,v1,RET` = if (a2 == v1) goto RET. And the fallthrough continues to `li v0,1`. So the RET path (arg2==9) returns v0 — and v0 must be 1 there.

For that, the `li v0,1` must dominate the RET path. It doesn't (it's after). Unless the compiler knows v0=1 on that path...

Hmm, unless the ROM's RET block is NOT `jr $ra` but something like `jr $ra` with v0 set elsewhere.

You know what? There's another possibility: the function's *first* `beqz v0,RET` at ins 2 has delay slot `move v0,zero` (ins 3) → returns 0. So RET is shared between "return 0" (with v0 already 0) and "return v0" paths. So RET = jr $ra, and the callers set v0 appropriately. For the arg2==9 path, v0 = 0 (the and result) — hmm.

So the ROM has a quirk. But the pinned C compiles to exactly these bytes and is deemed "correct" (score 0). So gcc 2.7.2 did sink `li v0,1` past the beq. That's possible if gcc treats `v0` as... hmm, `v0` is pinned to $2 via `register s32 v0 __asm__("$2")`. With the pin, the pseudo is a HARD REG pseudo (reg $2). Maybe with the hard-reg pseudo, gcc's RTL treats the assignment differently (e.g. it can't reorder a set of a hard reg across a branch? or the "birth boost" for hard regs differs).

Wait, actually! Maybe with the pin, gcc produced the li v0,1 at ins 23 because the scheduling differs. And the ROM (the original game) was compiled by a different compiler (PsyQ) with the same quirk.

Anyway: the ROM semantics quirk doesn't matter. What matters: reproduce the bytes.

KEY INSIGHT: maybe the quirk IS the pin's doing, and without the pin we can't reproduce it. But the task says find a lever-free body that scores 0.

Hmm OK. Now let me think about what the "1"-value pseudo is in the target. In the target, `li v0,1` at ins 23 = the set of the pseudo holding 1 (allocated $2 = v0). And the branches at 25,27,29 → RET return that pseudo. The branch at 22 → RET returns the same pseudo but it hasn't been set yet (it's set at 23, after) → in the ROM the value there is whatever v0 held (0 from the `and`).

Hmm, so gcc emitted the set AFTER a branch that uses the value — a real bug in the ROM. But gcc wouldn't do that... unless gcc's scheduler reordered a set of a *hard-reg* pseudo across a branch (the pinned v0!). That's plausible: with `register ... $2`, the pseudo IS the hard register, and gcc's "birth boost" in sched1 might move the `li $2,1` (a hard-reg set) later since hard-reg sets can be sunk (the value is "dead" before?).

Interesting: so the quirk comes FROM the pin. Without the pin, gcc keeps the set before the branch (semantically correct) → different bytes (mine has 41 ins).

Hmm! That means the ROM's oddity is pin-induced. But the ROM is the ROM: the original game code has this behavior. And the pinned C reproduces it. So the pinned C is "wrong" semantically but byte-correct. Fine — the target bytes are what they are.

Now, can a lever-free body produce the same bytes? We need gcc to (a) sink the `li v0,1` past the first beq, and (b) allocate the "1" pseudo to $2 and the const temp to $3, and (c) produce 39 ins with the same block layout.

In mine (nopin): the `li v0,1` ended up as the delay slot of a `j` (mine[31] j, mine[32] li v0,1) and there's an extra `move v0,zero`... wait no, mine[21] `move v0,zero` (delay slot of the bnez at 20) and mine[30] = nop, mine[31] `j`, mine[32] `li v0,1`.

So in mine, the "1"-pseudo is set in the block that jumps to RET (the "return 1" block), i.e. after the last compare falls through. And the const-chain's last compare is `bne` (jump if != to the continue block).

So mine's structure differs in block layout: mine has an extra block ("return 1" block with j+li) and inverted last compare.

The difference is essentially: in the target, the four "return v0" arms are all branches to the shared RET (with the value set once at ins 23 — even for the first arm, which is a ROM quirk); in mine, gcc created a separate block for "return 1" reached by fallthrough from the last compare.

Hmm, mine's structure: after `bne a2,v0,6aac` (if arg2 != 10 → goto continue at 6aac), the fallthrough is the "return 1" block (j RET; li v0,1 in the delay slot). And the earlier compares `beq a2,v0,6aa4` → 6aa4 = the "return 1" block too.

So in mine, the first three compares branch to the return-1 block (6aa4) and the last compare branches-if-not-equal to the continuation. In the target, all four compares branch to RET directly.

So the target's "return v0" is a direct branch to the shared epilogue (jr $ra) — meaning gcc had NO separate return block, i.e., the `return v0` statements compiled to a direct `beq → jr $ra`?? That means v0's value was already correct at the branch. And the value was set at ins 23 — after the first branch.

OK whatever, semantics aside, the structural difference: the target has 39 ins, no separate "return 1" block, and the last compare is `beq` (branch to RET) with fallthrough to the continuation.

To match, gcc must not create the extra return-1 block and must place `li v0,1` at ins 23.

This smells like the "flow"/sched1 behavior with the pinned hard reg. Without the pin, gcc's block structure differs fundamentally.

Hmm, but wait: mine has 41 ins = 39 + 2 (the extra `j` + `li v0,1`... plus a nop somewhere?). Actually the difference: target has `li v0,1` (1 ins) where mine has `j` + `li v0,1` (2 ins) → +1; and the last compare polarity → same count; and mine has an extra `move v0,zero`? Let me recount from the diff:

diff (nopin vs target):
- equal: mine[0:20] == target[0:20]
- replace mine[20:30] vs target[20:30] (10 vs 10) — same count
- equal: mine[30:31] == target[30:31]? (the diff printed "delete mine[31:33] target[31:31]" right after, so mine[30] == target[30] as an equal opcode)
- delete mine[31:33] (2 ins: j, li v0,1) vs target nothing
- equal mine[33:36] == target[31:34]
- replace mine[36:37] vs target[34:35] (j)
- equal mine[37:41] == target[35:39]

Total: mine = 41, target = 39. The extra 2 = the deleted `j` + `li v0,1`.

Hmm, so in mine the "return 1" block is: `j 6ac4` (mine[31]) + `li v0,1` (mine[32]) — and target has just `li v0,1` at 23 and the branches go directly to RET (jr $ra).

Wait, but if mine[31] is `j 6ac4` and the RET (jr $ra) is at 6ac4 → mine's return-1 block is `j RET` with the delay slot `li v0,1`. And the target's return-1 arms branch directly to RET with v0 already = 1.

So the target's `li v0,1` at ins 23 serves the three later arms; the first arm (arg2==9) returns v0=0 (quirk).

So the structural difference in mine: gcc created a block for "return 1" (because v0's set must dominate the RET branch, and gcc placed the set at the block start = the fall-through block after the last compare). In the target, the set is at ins 23 (in the middle of the chain, after the first compare) — i.e., the set was sunk into the middle of the block (not at the block start!).

So in the target, the "1"-pseudo's set is INSIDE the basic block (after the first compare) — that's a scheduling artifact of the pinned hard reg (sched1 sinking a hard-reg set).

Conclusion: this quirk is likely pin-induced, i.e., the byte-exact ROM behavior for this function may require the pin. But the task expects lever-free cracks to be possible (other shards found many). Let me think about what lever-free C could produce `li v0,1` in the middle of a block.

Actually! Here's a thought: what if the "1" is not a variable but the constant 1 used in the returns — then each return would need its own `li v0,1`... no.

What if the source is:
```c
v0 = 1;
v1 = 9;
if (arg2 == v1) return v0;
```
and gcc's sched1 sank the `li v0,1` past the beq because... with the pin, v0 is a hard reg and gcc's "hard reg set" can be sunk into the delay slot or past a branch if the value is "not needed"? That would be a bug.

Hmm, alternatively the *ROM* was compiled with the value 1 in a different place and the "quirk" is that the ROM's original source was:
```c
if (arg2 == 9) return 0;   /* ... */
```
Hmm no.

Wait wait. Let me reconsider the ROM: maybe `li v0,1` at ins 23 is NOT the "1" value but something else, and the "1" value is set elsewhere. What if the source were:

```c
v0 = 1;
```
compiled with the pin: the set `li v0,1` appears once. ✓ consistent.

And the four `return v0` → each needs v0 = 1 on that path. The set at ins 23 dominates the branches at 25,27,29 but NOT the branch at 22. So the ROM has a bug for the arg2==9 case → returns 0.

Since the pinned C reproduces it byte-exactly, gcc 2.7.2 with the pin does sink the set past the branch. gcc 2.7.2 was buggy; that's plausible (old compilers did reorder hard-reg sets across branches when the pseudo was a hard reg, since "the value is dead" analysis for hard regs is weaker).

So: to reproduce without the pin, I need gcc to sink the set of a *pseudo* (not hard reg) past a branch — unlikely, since for a pseudo gcc must respect the SSA-ish value flow.

Hmm, unless the pseudo's set is sunk because the pseudo is *reassigned* later! Think: if the "1" pseudo is set to 1 (ins 23) and later set to something else (e.g. the final `xor` result), then... no.

Alternative: what if the value returned is not from a pseudo but the return is `return 1;`?? Then each of the 4 returns has its own `li v0,1` (4 sets). No.

Hmm, but what about `return v0;` where v0 is a pseudo set to 1 — gcc creates the pseudo set once (if it can prove a single set dominates all uses) — but here the first use (branch at 22) is NOT dominated → gcc would need to split the set (two sets: one before the branch, one after) → that's what gcc did? No — in mine, there's exactly ONE `li v0,1` (in the return-1 block at the end).

Hmm, in mine: where is the "1" set? mine[32] `li v0,1` in the "return 1" block (j RET + delay li). And the first three compares branch to that block (6aa4). So the set dominates all 4 uses ✓ (semantically correct). gcc created a separate block for "return 1" (reachable from 3 branches + fallthrough from the last compare).

In the target, the set is at ins 23 (mid-block) and the branch at 22 does NOT have it → the target is semantically buggy. Reproducing that without a hard-reg pin seems hard.

BUT: maybe there's another C spelling that produces the same bytes! E.g., what if the source has the "1" set inside the block AFTER the first compare, and the first compare's return is `return 0` (not v0)?? That is, a source that matches the ROM's semantics exactly:

```c
v1 = 9;
if (arg2 == v1) return 0;     /* hmm, but then the branch at 22 → RET with v0 = 0 (already 0 from the `and`) */
v0 = 1;
v1 = 0x11;
if (arg2 == v1) return v0;
...
```
Would that compile to the same bytes? The `return 0` at the first compare: gcc would emit `beq a2,v1,RET` with v0 = 0 already? The `and` result v0 = 0 there, so `return 0` needs no set... but gcc might emit `move v0,zero`. Hmm! In the target, at ins 22 the branch goes to RET and there's no `move v0,zero` — because v0 is already 0 (the `and` result). gcc would know v0 == 0 there? The `and` result is 0 only on that path (the condition `(x & y) == 0` → the block is entered when the result is 0 → gcc knows v0 == 0 in this block! Yes! Because the branch condition `(s16 & (u16)arg3) == 0` implies the AND result is 0 → gcc propagates that (the pseudo is 0). So `return 0` in that block → no instruction needed (v0 already 0). ✓✓

So the C spelling:
```c
if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
    v1 = 9;
    if (arg2 == v1) return 0;      /* v0 is already 0 here */
    v0 = 1;
    v1 = 0x11;
    if (arg2 == v1) return v0;
    v1 = 0x29;
    if (arg2 == v1) return v0;
    v1 = 0xA;
    if (arg2 == v1) return v0;
    return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
}
```
Hmm, but `return 0` — the return value 0 → gcc sets v0=0 (already 0, so nothing) ✓. But careful: with `return 0`, gcc might emit `move v0,zero` anyway (it doesn't know v0==0 unless it propagates). Since the block is entered when the AND == 0, and the AND result is in v0 → gcc knows v0 == 0 (the pseudo is the same). Probably.

But this changes the C semantics vs the current src (arg2==9 now returns 0 — but that MATCHES the ROM's actual behavior!). Since the ROM returns 0 there, this C is MORE faithful. But the brief says "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)" — changing `return v0` to `return 0` is a statement-level change... it's not exactly in the catalog but it's a "statement order"/"temps" change? Hmm, it changes the returned value. It's a decomp-fidelity question: the ROM returns 0 for arg2==9, so `return 0` is the faithful decomp. But wait — is the ROM really returning 0 there? Let me double check the branch at 22 → 6abc = +0x94 = ins 37 = "jr $ra" (per my inference that mine[0]="jr $ra"). Hmm, mine[0] for the probe = the probe's first instruction. If the probe compiled to ["move v0,zero", "jr $ra"], then mine[0]="move v0,zero" == target[37] → target[37] = "move v0,zero" and target[38]="nop" vs mine[1]="jr $ra" → they'd differ → the replace line would print mine[1]="jr $ra" | target[38]="nop". But the printed line says mine[1]="move v0,zero". So mine[1]="move v0,zero" → the probe's 2nd ins is "move v0,zero" → the probe's 1st ins (mine[0]) == target[37] and the probe = [X, "move v0,zero"].

For `s32 f(){return 0;}`: gcc 2.7.2 MIPS might emit:
```
jr $ra
move v0,zero
```
? Hmm, that's unusual but possible: gcc's MIPS epilogue with the "move" in the delay slot of jr? Actually yes! Old gcc MIPS commonly emits:
```
jr $ra
move v0,v0    (or the value move in the delay slot)
```
Hmm, but then "move v0,zero" in the delay slot is exactly the return value ✓. So mine = ["jr $ra", "move v0,zero"] → mine[0]="jr $ra" == target[37] → target[37] = "jr $ra" ✓ and target[38]="nop" vs mine[1]="move v0,zero" → replace ✓ (matches the printed output).

Great: so target[37] = "jr $ra", target[38] = "nop" (delay slot), and the probe's asm = ["jr $ra", "move v0,zero"] — wait, that ordering is weird: the delay slot executes AFTER the jump, so `jr $ra; move v0,zero` sets v0=0 then returns ✓ correct.

So target[36] = "move v0,zero" (at +0x90) — the "return 0" block for the branches at 10 and 20 (which jump to +0x90, i.e. ins 36). ✓ consistent.

So the ROM's return-0 block is at +0x90 (ins 36) and the shared epilogue at +0x94 (ins 37-38).

Now, the branch at 22 (arg2==9) → +0x94 = jr $ra directly, with v0 = 0 (the `and` result) → returns 0 ✓ (the ROM quirk confirmed).

And the branches at 25,27,29 → jr $ra with v0 = 1 (set at ins 23) ✓.

So the faithful C is:
```c
v1 = 9;
if (arg2 == v1) return 0;   /* v0 already 0 */
v0 = 1;
v1 = 0x11;
if (arg2 == v1) return v0;
...
```
Hmm, but hold on: is `return 0` even needed? What if the first compare's return is `return v0;` where v0 is unassigned? Not valid C (well, it is valid C but reads an uninitialized var — bad decomp).

Alternatively: the first compare returns 0 and v0 is declared but assigned later.

But hmm: with `return 0` in the first arm, gcc must set v0 = 0 on that path. If gcc knows v0==0 (from the AND), it emits nothing ✓. If not, it emits `move v0,zero` → mismatch (the target has nothing there). Risky but let's test.

Also: the "1" pseudo (v0) is now set at ins 23 (after the first compare) — exactly the target's position ✓ — and it's only used by the three later arms, so gcc can sink/place it there naturally ✓.

And the register allocation: v0 (the "1") needs $2; the const temp needs $3. Now the "1" pseudo has 1 set + 3 uses = 4 refs; the const temp has 4 sets + 4 uses = 8 refs → const temp still wins $2?! Hmm. But maybe now the structure differs: the const temp's live range vs the "1"'s.

Hmm, but the target has "1" in $2 and const in $3 — with the pin, the "1" is $2 by force. Without the pin, will the const temp still take $2? Possibly. Let's test — the structural change might alter the allocation (e.g. the const temp now has 4 sets but the first one dies earlier).

Let me write this variant and test. Also a variant where the first arm returns 0 via an explicit `return 0;`.

Also worth testing: keep `return v0` in the first arm but declare v0 = 0 initially? e.g.
```c
v0 = 0;   /* hmm, that adds an ins */
```
No.

Let me write:
vE_first0.c: as above with `return 0` in the first arm and v0 = 1 after it.

Wait, careful about ordering: the target has `li v0,1` at ins 23, i.e., AFTER the first compare (ins 21-22) and BEFORE `li v1,17` (ins 24). So the source order should be:
```c
v1 = 9;
if (arg2 == v1) return 0;
v0 = 1;
v1 = 0x11;
if (arg2 == v1) return v0;
v1 = 0x29;
if (arg2 == v1) return v0;
v1 = 0xA;
if (arg2 == v1) return v0;
return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
```
Hmm, but the current src has `v0 = 1;` FIRST (before v1 = 9). Changing to `return 0` in the first arm + moving v0=1 after is a semantic change to match the ROM — justified as "the ROM returns 0 there". Hmm, but is this "a real C move" per the catalog? It's a statement-order change + the returned value. The brief's constraint: "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". "statement order" ✓ — moving `v0 = 1` after the first compare is a statement-order move. But changing `return v0` → `return 0` alters the value returned... which is exactly what the ROM does (the ROM's behavior). I'd call it a faithful decomp improvement.

Hmm, but risky: the graders may check "no semantic change"? The task is byte-matching the ROM. The ROM returns 0 there. So `return 0` is correct.

But hmm, wait. Is it possible that the ROM's branch at 22 doesn't return 0 because v0 was set to 1 earlier by the `li v0,1`... no, the li is at 23.

Hmm, but hold on: what if the ROM's `li v0,1` at ins 23 is actually the *set* of the pseudo for the FIRST compare's return and the compares are in a different order? Like the source was:
```c
v0 = 1;
v1 = 9;
if (arg2 == v1) return v0;
```
where gcc (in the original PsyQ build) scheduled the li v0,1 into the delay slot of the beq? No, the delay slot of ins 22 is ins 23 = "li v0,1"!!! Wait — ins 22 is `beq a2,v1,6abc` and ins 23 is `li v0,1` — IS ins 23 the delay slot of the beq at ins 22?! NO — in MIPS, the branch's delay slot is the instruction IMMEDIATELY AFTER (address-wise). ins 22 is at +0x58, ins 23 at +0x5C → so ins 23 IS the delay slot of the branch at ins 22!!

I made an indexing error earlier! Let me redo the address mapping: ins n is at +0x4n. So:
- ins 22 (beq) at +0x58, its delay slot = ins 23 at +0x5C = "li v0,1" ✓✓✓
- ins 20 (bnez) at +0x50, delay slot = ins 21 (+0x54) = "li v1,9" ✓
- ins 2 (beqz) at +0x08, delay slot = ins 3 (+0x0c) = "move v0,zero" ✓
- ins 34 (j) at +0x88, delay slot = ins 35 (+0x8c) = "sltu v0,zero,v0" ✓

So the branch at 22 (arg2==9 → RET) has the delay slot `li v0,1` → v0 = 1 on BOTH paths ✓✓✓. No quirk! The semantics are correct: arg2==9 → v0=1 → return 1.

So the `li v0,1` is in the delay slot of the first compare's branch. That's the classic MIPS delay-slot filling: the scheduler put the "v0=1" set into the branch's delay slot (since the branch is "not taken" → the set is needed on the fallthrough path... wait, the delay slot executes on both paths).

So the target: `beq a2,v1,RET` with delay slot `li v0,1` → v0=1 always after ins 22 ✓. Then ins 24 `li v1,17`, ins 25 `beq a2,v1,RET` (delay slot = ins 26 = `li v1,41`)...

WAIT. Then ins 26 `li v1,41` is the delay slot of the beq at 25 — so the `li v1,41` executes before the branch → breaking the comparison? No: the delay slot of ins 25 is ins 26 (`li v1,41`), which overwrites v1 AFTER the comparison was made ✓ fine.

So the structure is a chain:
```
21 li v1,9          ; delay slot of the bnez at 20
22 beq a2,v1,RET    ; if arg2==9 → RET (v0=1 set in the delay slot)
23 li v0,1          ; delay slot of the beq at 22
24 li v1,17         ; delay slot of the beq at 22?? no...
```
Hmm, delay slots: each branch's delay slot is the next instruction. Branches: ins 2 (delay 3), 6 (delay 7), 10 (delay 11), 15 (delay 16), 20 (delay 21), 22 (delay 23), 25 (delay 26), 27 (delay 28), 29 (delay 30), 34 (delay 35).

So:
- ins 20 bnez v0,+0x90, delay ins 21 = "li v1,9" ✓
- ins 22 beq a2,v1,RET, delay ins 23 = "li v0,1" ✓ (v0=1 always)
- ins 25 beq a2,v1,RET, delay ins 26 = "li v1,41" (overwrites v1 after the compare ✓)
- ins 27 beq a2,v1,RET, delay ins 28 = "li v1,10" ✓
- ins 29 beq a2,v1,RET, delay ins 30 = "nop" (the last compare's delay slot is a nop; nothing to fill)
- ins 31 lw v0,376(a0) — wait, ins 30 is the delay slot (nop) and ins 31 is the next insn. But ins 31 is "lw v0,376(a0)" and ins 32 "nop" — a load with a nop delay slot (load delay) ✓.

So the whole chain works: each `li v1,X` fills the previous branch's delay slot, and the compares use v1 before it's overwritten.

So the semantics are correct, and the "1" (v0=$2) is set once at ins 23.

Now MY compile (nopin) has the same structure but with the const temp in $2 and the "1" in $3:
```
20 bnez v0,6ac4, delay 21 = "move v0,zero"?? 
```
Hmm, mine[21] = "move v0,zero" — that's the delay slot of the bnez at 20. In the target, the delay slot of the bnez at 20 is "li v1,9" (a different fill!). Because in the target, the "li v1,9" was available to fill the delay slot; in mine, gcc filled it with "move v0,zero" (the return-0 setup) — because in mine, the bnez at 20 goes to a block that returns 0 and needs v0=0, so gcc sank the "move v0,zero" into the delay slot.

Hmm, why the difference? In the target, the bnez at 20 branches to +0x90 (ins 36: "move v0,zero") — the return-0 block — and v0 is set there. In mine, the bnez at 20 branches to 6ac4 (also a return-0 block) but with "move v0,zero" in the delay slot.

Both are valid; the difference is scheduling/optimization. Ugh.

Wait, actually, maybe the difference is that in mine, the branch at 20 is NOT the "return 0" branch. Let me re-read mine's structure:
```
20 bnez v0,6ac4      ; if (mask&arg3) != 0 → 6ac4
21 move v0,zero      ; delay slot
22 li v0,9           ; (v0 = const temp!)
23 beq a2,v0,6aa4    ; if arg2 == 9 → 6aa4 (the return-1 block)
24 li v0,17
25 beq a2,v0,6aa4
26 li v0,41
27 beq a2,v0,6aa4
28 li v0,10
29 bne a2,v0,6aac    ; if arg2 != 10 → 6aac (continue)
30 nop
31 j 6ac4            ; the return-1 block: j 6ac4 (RET)
32 li v0,1           ; delay slot: v0 = 1
33 nop? ...
```
Hmm, mine[33:36] == target[31:34] = nop, lw v0,376(a0), nop → mine[33]=nop? and mine[31]=j, mine[32]=li v0,1, mine[33]=nop?? then mine[34]=lw? Hmm the equal region was mine[33:36] vs target[31:34] (3 insns each): target[31]=nop, target[32]=lw v0,376(a0), target[33]=nop.

So mine[33]=nop, mine[34]=lw v0,376(a0), mine[35]=nop, mine[36]=j 6ac4 (replaced vs target[34]=j 6abc), mine[37:41]==target[35:39] = sltu, move v0,zero, jr $ra, nop.

Wait, that doesn't work: mine[36] = "j 6ac4" and mine[37] = "sltu v0,zero,v0" — so the j's delay slot is the sltu ✓. And where's the "li v0,1"? mine[32]. And mine[31] = "j 6ac4"?? The diff said "delete mine[31:33]" = mine[31], mine[32] → deleted. So mine[31] = "j 6ac4" and mine[32] = "li v0,1". Then mine[33] = nop (equal to target[31]).

Hmm, but then what is the block structure? mine[31] j + mine[32] li v0,1 (delay slot) → jumps to 6ac4 = the return-1 block? and mine[33] nop, mine[34] lw v0,376(a0)...

Hmm, so mine[31:33] is a block: "j 6ac4" + delay "li v0,1" — that's the return-1 path. And it's placed BEFORE the continuation code (mine[33:36]). But the branches at 23,25,27 (beq a2,v0,6aa4) → 6aa4 = that block? 6aa4 < 6aac < 6ac4 hmm. So the branch targets: 6aa4 (return-1 block), 6aac (continuation), 6ac4 (RET). Mine's addresses are larger overall (41 ins vs 39).

OK so in mine:
- The return-1 block = "j RET; li v0,1" — the "1" is set in the delay slot of the jump.
- The first compare's branch (23) → the return-1 block; the delay slot of ins 23 is ins 24 = "li v0,17" ✓.
- The last compare uses "bne" (jump-if-not-equal to the continuation) — the fallthrough is the return-1 block.

In the target:
- The "1" is set in the delay slot of the first compare's branch (ins 23).
- All four compares branch to RET directly (no separate return-1 block).
- The last compare is "beq → RET" with a nop delay slot, and the continuation follows.

So the target's structure is: the "1"-pseudo's set is sunk into the first branch's delay slot, and the return-1 arms are direct branches to the epilogue (no extra block) because v0 is already 1.

In mine, gcc needed a separate block because the "1"-pseudo (in $3) was set only in the return-1 block.

Hmm! Actually, in mine, why couldn't gcc have set the "1" in the delay slot of the first compare (like the target)? Because in mine, the "1"-pseudo is in $3 = v1 and the const temp is in $2 = v0 — and the const temp's set (`li v0,9`) is at ins 22 (delay of the bnez at 20). If the "1" (v1=$3) were set at ins 23 (delay of the beq at 22)... hmm, that would be possible in principle. But gcc chose a different structure because the "1"-pseudo's live range starts at the return-1 block.

The root difference is the register allocation: in the target, "1" is in $2 (the return register) so `return v0` is a direct "jr $ra" (no move needed) and gcc can merge the returns into the epilogue; in mine, "1" is in $3, so `return v0` requires a MOVE to $2 → gcc creates a block "move $2,$3; jr $ra" — and to save the move it puts the set in the delay slot.

So EVERYTHING hinges on getting the "1"-pseudo into $2.

OK so back to the allocation problem: how to make gcc put the "1"-value in $2 (v0) rather than the const temp?

In the target (pinned): v0 ($2) = "1", v1 ($3) = const temp.
Without the pin: const temp → $2, "1" → $3.

Local-alloc assigns registers to pseudos within a block. The order is by qty (number of refs) descending? If so, "1" has 1 set + 4 uses = 5 refs (in the original C) and the const temp has 4 sets + 4 uses = 8 → const wins ✓ consistent with observation.

To flip, I need the "1" pseudo to have MORE refs than the const temp, or the const temp fewer.

Idea: make the const temp have fewer refs! What if the four compares don't use a temp but the constants directly? Tried (variant A) — same result, because gcc coalesced them into one pseudo (combine). Hmm, did it? The score was identical (17, 41 ins) — so yes, gcc produced the same code.

Idea: make the "1"-pseudo have more refs. What if the returns use v0 more times? E.g. restructure so that v0 is used in the final expression too:
```c
return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
```
Hmm, that returns a bool.

What if we write:
```c
v0 = 1;
...
if (arg2 == v1) return v0;
...
v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;   /* reuse v0 */
return v0;
```
That adds a set of v0 (refs: 2 sets + 5 uses = 7) and removes the const temp's? The const temp still has 8. Hmm, and it changes the codegen of the final expression (v0 = xor; sltu) → the target has `xor v0,v0,a1; sltu v0,zero,v0` → in the target the result is computed INTO v0 ($2) — interesting: the target's final expression uses $2 for the xor and the sltu! So in the target, the final expression's pseudo is ALSO $2 (v0). Hmm, but that pseudo is a different one (the xor result).

Hmm OK. Let me think about local-alloc's actual rule in gcc 2.7.2 (final.c, local_alloc):

In final.c, `local_alloc` → for each basic block, it computes the "live" pseudos and allocates hard registers to them. The order of allocation within a block is by `qty` (the number of references) — actually in final.c: `local_alloc` uses `qsort (reg, ...)`? Let me recall the code:

```c
static void
local_alloc (insn, block, reg, regset, i, pseudos, n_pseudos, live, n_live, need, n_need)
```
and there's:
```c
  /* Sort the pseudos by their quantity of references */
  qsort (pseudos, n_pseudos, sizeof (pseudo_reg), pseudo_reg_qty_cmp);
```
Hmm, in GCC 2.7 final.c, there's a function `find_reg` and the allocation order is determined by `qty` and `reg` (the "preferred register" ordering). Actually I recall: `local_alloc` iterates over the pseudos in the block, and for each pseudo, it tries to allocate a hard reg, preferring `reg` (the pseudo's preferred reg) then others.

The "reg" preference for a pseudo is set by global-alloc (for globals) or by the "hard reg" copy preferences. For local pseudos, `reg` is usually 0.

Hmm, in gcc 2.7's final.c local_alloc:
```
  /* Now allocate the hard registers among the pseudos... */
  for (i = 0; i < n_pseudos; i++) { ... }
```
and the ordering comes from `qsort (pseudos, n_pseudos, ..., pseudo_reg_forced_p)`.

I recall that in local-alloc, the pseudos are processed in order of DECREASING qty? Actually `pseudo_reg_qty_cmp` sorts by qty ascending? Hmm.

Rather than theorize: EXPERIMENT. The key question: how do I make the "1"-pseudo win $2 over the const temp?

Experiment set:
E1: Make the "1"-pseudo's value used more: e.g. `v0 = 1; if (arg2 == v1) return v0;` ×4 (already) — try adding `v0 = v0;`? no.

E2: Reduce the const temp's refs by using each constant once but with SEPARATE variables (not reused):
```c
s32 v1, v2, v3, v4;
v1 = 9; if (arg2 == v1) return v0;
v2 = 0x11; if (arg2 == v2) return v0;
v3 = 0x29; if (arg2 == v3) return v0;
v4 = 0xA; if (arg2 == v4) return v0;
```
Each temp: 1 set + 1 use = 2 refs (4 temps = 8 total, but each is short-lived). gcc might allocate them all $3 (not live simultaneously) and the "1" pseudo $2? Hmm, but they're in the same block, and local-alloc's per-block allocation with 5 pseudos (v0, v1..v4) competing for $2/$3/$4... Since v1..v4 die quickly, gcc's local-alloc can reuse $3 for all of them. And v0 (live across the block) gets $2? Plausible! But the target has all four `li v1,X` in $3 — matching "one pseudo reused" but also matching "four pseudos sharing $3".

Wait, but with 4 separate temps, gcc might assign $3,$4,$5,$6 (if it doesn't reuse). Hmm, local-alloc does reuse registers for pseudos that don't conflict (it processes them in order and reuses freed regs). Since each temp dies right after its use, they'd all get the same reg.

But: the delay-slot structure requires the `li v1,X` to be in the delay slot of the previous branch — that's sched1's doing, independent of the C spelling.

E3: Give the "1" a higher qty by making the compiler see more uses: e.g. write the returns as `return v0;` but ALSO use v0 in the final expression:
```c
v0 = 1;
...
v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
return v0;
```
Then v0 has 2 sets + 5 uses = 7 refs vs const temp 8. Close. And the target's final expression: `lw v0,376(a0); xor v0,v0,a1; sltu v0,zero,v0` → the result is in $2 ✓ consistent with v0 being the pseudo for the final value! And in the target, the xor result is in $2 = v0 → suggesting the final value IS in the same pseudo as the "1"?! No — different pseudos can share $2 if not live simultaneously. But it does suggest that the final-expression pseudo got $2.

Hmm! That's a hint: in the target, TWO different pseudos got $2: the "1"-pseudo and the xor-result pseudo (not live simultaneously). And the const temp got $3 throughout.

If in the target the xor-result pseudo is a separate pseudo that got $2 — then the "1"-pseudo also got $2 — meaning $2 was available for 2 pseudos.

In mine, the xor result also went to $2 (mine[31..33]: lw v0,376(a0) etc. — yes mine's final expression uses $2 = v0). So in mine, $2 goes to: the const temp (live across the chain) and later the xor result. So in mine, the const temp won $2 because it's live at the block start.

To flip, the const temp must lose $2 to the "1"-pseudo.

Let me now think about *why* gcc gives $2 to the const temp: at the block start (ins 20-21), the live pseudos are: the "1"-pseudo (v0, set later... hmm, actually in the source v0=1 is the FIRST statement of the block, so at the block start both the "1"-pseudo and the const temp are live) and the const temp.

In gcc's local_alloc, for each block, the pseudos are sorted and allocated. The "1"-pseudo: qty 5; const temp: qty 8. If sorted by decreasing qty, the const temp gets $2 first ✓ (matches observation).

So to flip: increase the "1"-pseudo's qty above 8, or reduce the const temp's qty below 5.

Reduce const temp's qty: if each constant gets its own temp (E2), each has qty 2 → the "1" (qty 5) wins $2 ✓. And the four temps share $3 (they die quickly) — plausible.

Let me try E2! Also try E2b: same but with the temps declared in a way that they're not simultaneously live.

Also, the "1"-pseudo's qty could be increased by using it in the final expression (E3) → qty 7, still < 8.

Combination E2+E3 might be needed if E2 fails.

Let me write E2 and E3 and score them.

E2 (four temps):
```c
s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v3;
    s32 v4;
    ...
            v0 = 1;
            v1 = 9;
            if (arg2 == v1) return v0;
            v2 = 0x11;
            if (arg2 == v2) return v0;
            v3 = 0x29;
            if (arg2 == v3) return v0;
            v4 = 0xA;
            if (arg2 == v4) return v0;
```
E3 (reuse v0 for the final value):
```c
            v0 = 1;
            v1 = 9;
            if (arg2 == v1) return v0;
            v1 = 0x11;
            if (arg2 == v1) return v0;
            v1 = 0x29;
            if (arg2 == v1) return v0;
            v1 = 0xA;
            if (arg2 == v1) return v0;
            v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
            return v0;
```
Hmm, this changes the final expression's codegen: `v0 = (load != arg1)` → gcc computes xor + sltu into v0 → then `return v0` → since v0 is $2, no move ✓. In the target, the final expression is `lw v0,376(a0); xor v0,v0,a1; sltu v0,zero,v0` — the sltu result in $2 ✓. So E3 could produce exactly that.

Let me also try E4: both (four temps + v0 reuse).

Let me write these 3 and score them in parallel.
