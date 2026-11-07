---
ts: 2026-11-06T12:57:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OAQqkSmLUIym0MRmemIT
---
Now I see the target (first block) vs mine (second block).

Target:
```
106 beq v0,v1,47d8      (if func_80183A64 == 1 goto 47d8)
108 lh a0,6(s0)
109 lh v1,6(s1)
111 subu v0,a0,v1       (v0 = d)
112 bltz v0,47c8        (if d < 0 goto else)
113 slti v0,v0,128      (delay slot: v0 = d < 0x80)
114 beqz v0,4aa8        (if !(d<0x80) -> break)
115 nop
116 j 47d8             (goto join)
117 nop
118 47c8: subu v0,v1,a0  (else: v0 = -d)
119 slti v0,v0,128
120 beqz v0,4aa8        (break)
121 nop
122 47d8: (join) lh v0,6(s0)
```

Mine:
```
106 beq v0,v1,47c8
108 lh a0,6(s0)
109 lh v1,6(s1)
111 subu v0,a0,v1
112 bgez v0,47c0       (if d >= 0 goto then)
113 slti v0,v0,128     (delay)
114 subu v0,v1,a0      (else arm inlined here)
115 slti v0,v0,128
116 47c0: beqz v0,4a98  (shared break)
117 nop
118 47c8: join
```

So mine has cross-jumped: both arms' `slti; beqz` share the `beqz` at 116. Target has two separate beqz's and an extra `j` + nop.

The target's structure: then-arm ends with `beqz ...; nop; j join; nop` and else-arm ends with `beqz ...; nop`, falling into the join.

Note the target's join at 47d8 is reached from the `beq` at 106 too (the != 1 path skips the whole if).

So: target keeps the two arms separate. Real-C route: make them not cross-jumpable. find_cross_jump requires the two blocks to be identical after normalization. The two arms in target:
- then: slti v0,v0,128; beqz v0,EPI
- else: slti v0,v0,128; beqz v0,EPI
These ARE identical (after the subu which differs)! jump2's cross-jump merges the identical tails. Hmm, so why doesn't the target's jump2 merge them? Because of the barrier: the asm insn at the end of the then-arm prevents merging (the block isn't byte-identical).

Hmm wait, in the target the then-arm is: slti; beqz; nop; j; nop. That's the shape of a block that ends with a jump to the join. The else-arm: slti; beqz; nop then falls into the join.

Hmm, so the then-arm's `beqz v0,EPI` + `j join` and the else-arm's `beqz v0,EPI` — the identical part is just `slti; beqz`. Cross-jump would replace the then-arm's tail with a jump to the else-arm's tail. 

OK, so how did the target avoid it? The asm insn. In the target's then-arm, is the asm still present? Yes! The barrier is an empty asm — it emits no instructions but it's an insn in the RTL, so at jump2 time the two blocks differ (one has an extra insn) → no cross-jump. And the empty asm emits nothing.

So the target's 4 extra insns (j + nop + ... hmm, target has 319 vs mine 315) come from the non-merge.

To crack it lever-free: make the then-arm's RTL differ from the else-arm's without an asm. Options:
(a) A different C spelling of the then-arm's condition that produces the same target instructions: `if (d >= 0x80) break;` → target has `slti v0,v0,128; beqz`. That's exactly what `d >= 0x80` produces... yes, `d < 0x80` inverted.

Hmm. The two arms' *code* is identical; only the value differs (v0 vs v1-a0). Cross-jump normalizes registers so they look the same.

(b) Make the arms have different instruction counts: e.g., write the then-arm's test as `if (*(s16*)(s0+0x6) - b58->unk6 >= 0x80)` and the else-arm as `if (*(s16*)(s0+0x6) - b58->unk6 <= -0x80)`. The second form: `d <= -0x80` → slti v0,v0,-128; bnez? That would produce different instructions than the target (which has `subu v0,v1,a0; slti v0,v0,128`).

Target else-arm: `subu v0,v1,a0; slti v0,v0,128; beqz` → that's `-(d) < 0x80` → `if (-d >= 0x80) break` → exactly `b58->unk6 - s0unk6 >= 0x80`. So the source is as written.

(c) Use `do{}while(0)` in one arm to split the block for jump2. C0535 (do-while splits cse1 EBB) — maybe it also leaves a label that makes the arms differ for jump2? jump2 runs after cse... but jump_optimize also removes redundant labels. Hmm, but maybe not: a `do{}while(0)` with a break inside creates a label at the end which jump_optimize may keep if... hmm.

Actually, the existing moves list has a MATCH for a similar case: "barrier | func_8014F74C | MATCH: invert the `!= 0x1D` guard so the two `return ret` collapse into one return block; jump_optimize then picks bne-to-return + move delay slot as the target". So restructuring the conditionals is the route.

Here we need the OPPOSITE: prevent a merge (the target has the unmerged shape). 

Ideas:
(d) Move the barrier's role to a *different* statement placement: e.g., put the `break` of the then-arm into a `do{}while(0)`:
```
do { if (d >= 0x80) break; } while (0);
```
Hmm, `break` inside do-while(0) breaks the do-while, not the switch! That changes semantics.

(e) Write the then-arm as `if (d >= 0x80) { goto epi; }`... no label.

(f) Reorder the arms: put the else-arm first (i.e. `if (d < 0) { else } else { then }`). Then the cross-jump might merge in the other direction and produce a different shape. Let me think: target's shape has the `bltz` (branch on d<0) to the else-arm placed after. If I invert the outer if, the code would be `bgez v0, else` — different from target.

Hmm, but the target's outer test is `bltz v0,47c8` — branch to the else when d<0. That corresponds to source `if (d >= 0) { then } else { else }`. So the source is as written.

(g) Add a real difference in the then-arm: e.g., the then-arm could compute something extra. No.

(h) Change the then-arm's test to a form with the same target instructions but different RTL: e.g. `if (d >= 0x80) break;` vs `if (!(d < 0x80)) break;`. Both produce the same RTL after fold.

(i) What about making the two arms' *delayed branches* differ: e.g., in the then-arm, the `slti` is in the delay slot of the `bltz` (target insn 113 is in the delay slot of 112!). Look: target 112 `bltz v0,47c8` with delay 113 `slti v0,v0,128`. And mine 112 `bgez v0,47c0` with delay 113 `slti`.

(j) Make the else-arm's `break` target different? No.

Hmm. What about giving the then-arm a `goto` label so jump2 sees a label? Let me think about how cross-jump works: it compares the *tails* of two blocks that end with the same jump/branch. If the then-arm's tail has a label, does that stop it? jump2's find_cross_jump compares insns; a label (CODE_LABEL) is a barrier to the comparison? In jump.c's find_cross_jump, there's a check for `GET_CODE (i1) == CODE_LABEL`... let me check jump.c.

Actually, the target's structure: then-arm ends with `beqz EPI; nop; j JOIN; nop`. The `j JOIN` is a jump to the join block. The else-arm ends with `beqz EPI; nop` and falls through to JOIN. Cross-jump merges blocks that end with the same jump; here the then-arm ends with `j JOIN` and the else-arm... hmm.

Wait, actually maybe I have it backwards. Let me reconsider: in the target, the then-arm (d>=0) is:
```
slti v0,v0,128
beqz v0,4aa8      ; if d >= 0x80 -> break
nop
j 47d8            ; else goto join
nop
```
and the else-arm:
```
47c8: subu v0,v1,a0
slti v0,v0,128
beqz v0,4aa8
nop
47d8: (join)
```

In mine, the merge produced:
```
bgez v0,47c0
slti v0,v0,128
subu v0,v1,a0
slti v0,v0,128
47c0: beqz v0,4a98
nop
47c8: join
```
Hmm, that's odd: mine has BOTH slti's executed (one in the delay slot of bgez, one in the else path), then a shared beqz. Actually cross-jump moved the then-arm's `slti` into the branch delay slot and shared the `beqz`. Interesting.

So jump2 (cross-jump) in mine merged the `beqz v0,EPI` of both arms into one at 47c0, using the slti results from both paths.

To prevent: make the two `beqz` targets... they're the same (the epilogue). 

Real-C idea: make the then-arm's break go to a different place. E.g., restructure:

```
if (func_80183A64(...) != 1) {
    if (d >= 0) {
        if (d >= 0x80) break;
    } else {
        if (-d >= 0x80) break;
    }
}
```
Currently that's what we have.

What if instead:
```
if (func_80183A64(...) != 1) {
    if (d >= 0) {
        if (d >= 0x80) break;
        goto L;      // no
    }
}
```

Alternative real-C: compute the comparison once:
```
if (func_80183A64(...) != 1 && (d >= 0 ? d : -d) >= 0x80) break;
```
That would produce a conditional-expression → likely different code (and the target has two separate subu's).

Hmm. What does the target's shape correspond to in C? Two separate arms with identical tails. That IS the natural C. The only reason it doesn't merge is the asm.

So maybe the route is: make the arms differ by having different *values* in the comparison — e.g. the then-arm uses `>= 0x80` and the else-arm uses `> 0x7F`. That's the same RTL after folding? `x > 0x7F` → `x >= 0x80` after canonicalization. Same.

What if the else-arm uses `if (-d > 0x7F)` → fold → same.

What if I write the else arm as `if (d <= -0x80) break;` — different RTL: `slti v0,v0,-128; bnez`? Target has `subu v0,v1,a0; slti v0,v0,128; beqz`. With `d <= -0x80`: `slti v0,v0,-127`? Actually `d <= -0x80` → `!(d > -0x80)` → `!(d >= -0x7F)` → `slti v0,v0,-127; beqz`. Different. So no.

Hmm, what about making the then-arm's condition use a u16 cast: `if ((u16)d >= 0x80)`. Then the code would be different (andi). No.

OK, what about the `nop` after each beqz in the target? The target has `beqz; nop` — a branch-delay nop (reorg couldn't fill). In mine, `beqz v0,4a98; nop` also.

Let me consider: is there another way to make the two blocks differ for find_cross_jump — e.g., different *source* order of the loads `lh a0,6(s0); lh v1,6(s1)` vs `lh v1,6(s1); lh a0,6(s0)`? The loads are before the branch, shared in both.

What about the else-arm re-loading `b58->unk6` instead of using v1? Currently v1 = lh v1,6(s1) is loaded once and used by both arms. If the else-arm re-read `((Unk*)b58)->unk6` after the subu, cse would forward it anyway.

Hmm. What if the then-arm and else-arm used *different registers* so the normalization differs? Cross-jump normalizes.

Let me look at jump.c's find_cross_jump to see what stops it. In 2.7.2 jump.c there's `find_cross_jump` with a `min` parameter (jump2 uses min=1?). Let me grep.
