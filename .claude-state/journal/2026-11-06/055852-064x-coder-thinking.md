---
ts: 2026-11-06T12:58:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RDZl6p3WOvnXZXfK2SOv
---
`if (minimum <= 0 && last1 != 0 && last1 != e1)`. minimum starts at 2 and is decremented per matching insn. So 2 matching insns needed normally; if a label is hit, minimum-- and break, so 1 matching insn + label suffices... no wait: hitting a label decrements minimum by 1 (to 1) and breaks; then `minimum <= 0` is false (1 > 0) → no merge. Hmm: the label decrement happens *before* the match, so if a label is hit, minimum goes 2→1 and break; then minimum(1) <= 0 is false → no cross-jump at all! Unless other decrements happened.

So: if the comparison encounters a CODE_LABEL, the merge only proceeds if enough insns already matched (each match decrements). With minimum=2, after 1 match minimum=1; then a label → minimum=0, break → merge of that 1 insn.

Hmm, so a label right before the beqz: sequence from e1 (the branch) backward: beqz (match, min 1), slti (match, min 0), then label → min -1, break → merge.

Actually the loop starts from e1 (the conditional jump insn itself)? `i1 = prev_nonnote_insn(e1)` — so e1 is the branch, and the scan starts at the insn before it. Hmm.

Let me reconsider what e1/e2 are: in jump_optimize, for each conditional jump insn `insn` with a target, `x` = the insn before the target's block end... Let me not go deeper.

The practical question: does a `do{}while(0)` in the then-arm change jump2's merge? The C0535 cookbook says do-while splits cse1 EBB. For jump2 we need a label to survive to jump2.

Given the empirical evidence in the moves list: "jump2-crossjump-arms — cross-jump merges byte-identical arms; only an asm insn between them blocks the merge" (func_80180D38, WALL, 33 lever-free bodies, best 10). That's a strong signal that this class is a wall.

But the brief's MOVES+ mentions C0535 and C0414. Let me try a few cheap things:
1. do{}while(0) around the then-arm's `break` (careful: break would bind to the do-while). Instead: `do { if (d >= 0x80) { <break-equivalent> } } while (0)` — the break inside would exit the do-while, not the switch. Wrong semantics.

Hmm. So we can't wrap the break.

2. What about restructuring so the then-arm's tail differs: e.g.
```
if (d >= 0) {
    if (d >= 0x80) break;
} else if (-d >= 0x80) {
    break;
}
```
That's a different CFG (else-if): the else arm's break is in a nested if. Might produce a different shape.

3. Another: swap the two arms' order:
```
if (d < 0) {
    if (-d >= 0x80) break;
} else {
    if (d >= 0x80) break;
}
```
Now the branch would be `bgez` to the then-arm. Target has `bltz`. So no.

4. What if the condition variable is computed differently so the two arms use different instructions? E.g., compute `d` and `-d` as separate variables before:
```
s32 d = ...; s32 nd = ...;
```
No.

5. What if the then-arm's break is written as `if (d >= 0x80) { s0->unk34 = ...; }`? no.

Let me think about what the target really is:
```
112 bltz v0,47c8      ; if d<0 goto else
113 slti v0,v0,128    ; delay: v0 = d<0x80
114 beqz v0,4aa8      ; if d>=0x80 break
115 nop
116 j 47d8            ; goto join
117 nop
118 47c8: subu v0,v1,a0
119 slti v0,v0,128
120 beqz v0,4aa8
121 nop
122 47d8: join
```

Mine:
```
112 bgez v0,47c0
113 slti v0,v0,128
114 subu v0,v1,a0
115 slti v0,v0,128
116 47c0: beqz v0,4a98
117 nop
118 47c8: join
```

Hmm, mine's cross-jump merged the `beqz` and made the then-arm's conditional a bgez to the else's slti. 

For a real-C fix, what if the two `break` statements went to *different* labels? They both go to the epilogue (the switch's end). They're the same target.

What if one of the arms did something else instead of break — e.g., the then-arm sets a flag and breaks? That changes the code.

OK, what if the source had the two arms share the condition differently... 

Alternatively: what if I make the *then-arm* end with a jump to the join while the else-arm falls through — that's what the target has! The target's then-arm has `j 47d8` and the else falls through. Why would the then-arm need an explicit jump in C? Because in source the then-arm is the "if (d>=0)" body and the else-arm is the else; the join follows. The then-arm's fall-through would be into the else-arm, so it needs a jump to the join. That's the normal structure.

Hmm, so the target's shape is the natural unmerged shape.

So the merge in mine happens because jump2 cross-jumps the two `slti;beqz` pairs.

To stop it lever-free: make the two pairs not byte-identical after renumbering. E.g., if the then-arm's `slti` used a different immediate... no.

What if the then-arm compares `d` and the else-arm compares `-d` but the *order* of the subu differs (mine has them in different places)? After cross-jump they're normalized.

What if the else-arm's comparison were `>= 0x80` on a *different variable* — e.g. the else-arm recomputes `((Unk*)b58)->unk6 - *(s16*)(s0+0x6)` in a different type (u16)? Then the code would differ (lhu vs lh). But the target's else-arm is `subu v0,v1,a0; slti v0,v0,128` — same as the then-arm's.

Hmm, what if the then-arm used a temp: `s32 d = *(s16*)(s0+6) - b58->unk6;` and the else `s32 e = b58->unk6 - *(s16*)(s0+6);`? The code is the same.

I think this is the documented wall `jump2-crossjump-arms`. Let me do a handful of real-C tries (10-15) and then record the wall, but I must satisfy ≥20 min and ≥30 tries. That's expensive for a wall. Hmm.

Alternatively — maybe there IS a crack. Let me think about the `nop` after `beqz` at 115 in the target: `beqz v0,4aa8; nop; j 47d8; nop`. Interesting: the target's then-arm ends with beqz+nop+j+nop. In mine: `beqz v0,4a98; nop` then the join.

What if the then-arm's break is written to make the compiler emit the j? It does.

Hmm, let me look at the *other* differences: mine[100] vs target[100] are just address shifts.

So the only real delta is this 4-insn region.

Let me try the do-while trick on the *break* target: what if instead of `break` I use a `goto` to a label at the end of the switch? In C:
```
if (d >= 0x80) goto L_end;
...
L_end:
```
Hmm, but then the label placement matters. Actually `break` already jumps to the epilogue.

What if I restructure the whole case-2 body's tail as:
```
if (func_80183A64(...) == 1) goto L_join;
if (d >= 0) {
    if (d >= 0x80) break;
} else {
    if (-d >= 0x80) break;
}
L_join:
if (...) ...
```
A `goto` adds a label; labels affect cross-jump (a CODE_LABEL stops the scan). Where would the label be? At L_join, which is after the if/else. Hmm, the label is after both arms — that doesn't separate the two beqz's.

What if I put a label between the slti and the beqz? Impossible.

OK, let me look at the other arm's structure once more:
- then-arm: `slti v0,v0,128; beqz v0,EPI`
- else-arm: `subu; slti; beqz`

The then-arm's slti is in the delay slot of the bltz. So in the RTL, the then-arm block is: [slti][beqz]. The else block: [subu][slti][beqz]. The merge takes the last 2 insns (slti, beqz) — minimum=2 → merge.

If a label were placed between the slti and the beqz in the then-arm, the merge would fail. Can't in C.

BUT: what if the then-arm had an extra insn between? E.g., make the then-arm's condition use a different temp so there's a `move` between slti and beqz? Hmm, that would add an insn to the target too.

What if the else-arm's tail is shifted by one insn: e.g. make the else-arm compute `-d` as `0 - d` (subu v0,zero,v0) instead of `v1 - a0`? That's an extra insn (target has 2: subu v0,v1,a0). If I write `if (b58unk6 - s0unk6 >= 0x80)` it's `subu v0,v1,a0`. 

What if the else-arm writes `if (-(*(s16*)(s0+6) - b58->unk6) >= 0x80)`? That would be `subu v0,a0,v1; subu v0,zero,v0` or `negu`. Extra insn → target doesn't have it.

I'm fairly convinced this is the documented jump2-crossjump-arms wall. But let me try a few cheap candidates anyway (they're fast, ~2s each):

c1: else-if form (`} else if (...) { break; }`).
c2: then-arm condition written as `if (!(d < 0x80)) break;`
c3: `if (d >= 0x80) { break; }` with explicit braces + a do-while(0) around the *then* arm body minus the break... 
c4: swap the arms' order (d<0 first).
c5: use a temp `s32 dd = d;` in the then-arm.
c6: compute `d` before the outer if.
c7: make the then-arm's comparison use `0x80 <= d`.
c8: use `if (d - 0x80 >= 0)`.

Let me run 8-10 of these. If none works, I'll need to spend the time for a wall (30 tries).

Actually — hold on. Let me reconsider the problem from the *other* direction: maybe I can make the cross-jump happen in a way that produces the target shape. The target has 4 MORE insns. What if the merge could be prevented by making the else-arm's `break` jump to a *different* epilogue entry point? E.g., if the then-arm's break went through a `goto` label placed before the epilogue code... that would add a label and change the jump targets. Actually: if I add a label at the start of the epilogue (`L_epi:`) and make one arm `goto L_epi`, the two jumps would have different targets → no cross-jump!

But `break` goes to the switch end. If I restructure:
```
switch (...) {
...
case 2:
   ...
   if (...) {
       if (d >= 0x80) goto L_epi;
   } else {
       if (-d >= 0x80) break;
   }
   ...
}
L_epi:
func_80183DA0(s0);
...
```
Then the then-arm jumps to L_epi (a label) while the else-arm breaks to the switch end — which is the same place, but jump_optimize would redirect `break` (a jump to the switch end label) to L_epi? Hmm, "Delete no-op jumps and optimize jumps to jumps": the break's jump target is the switch-end label; if that label is immediately followed by L_epi, jump_optimize would redirect the break to L_epi (jump to jump optimization). So both would target L_epi → merge again.

What if L_epi is placed *after* the epilogue? No.

Hmm. What if one arm's break goes through a different label that is NOT adjacent (e.g., in the middle of the epilogue)? Then the code differs.

OK — what about using a `do{}while(0)`+`break` inside a *switch*? Not applicable.

Let me try the empirical batch and see.

Actually, wait. Let me reconsider the C source: maybe the target's shape comes from a *different* C structure: the `if (func_80183A64(...) != 1) { ... }` guard. In the target, at 106 `beq v0,v1,47d8` — if the call returns 1, jump to the join (47d8). In mine: `beq v0,v1,47c8` (jump to the join at 47c8). Same.

Let me just run the batch.

Time check: item 3 started ~05:56. It's probably ~06:00 now.

Let me write the candidates.
