---
ts: 2026-11-06T16:38:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_90jQyI4qVaohs22EJcvg
---
Still 9. The do-while(0) probably got optimized away before jump2. Hmm.

Let me check where the merge happens precisely: at jump2 (post-reload). In v1, the merge happened at jump2 (post-reload). The do-while would need to survive reload as a label. Unlikely.

Alternative: produce a CODE_LABEL that survives by having an actual goto target. What about a real control-flow use: the then arm could `goto` a label at its own end, targeted by a condition that's never true but not folded? e.g.:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    if (param_1 == 0) goto endthen;   /* real branch, emits insns — no */
}
```
Adds insns.

Hmm, wait. Maybe a completely different approach: make the then arm's comparison *not* produce an identical branch to the else's by using a comparison that yields the same `slti v0,v1,81` instruction but a different RTL. The RTL for `slti` is `(set (reg v0) (lt (reg v1) (const_int 81)))` then a branch on v0. Both arms identical in shape.

Unless the *branch* pattern differs due to the LABEL_REF comparison: "Two label-refs are equivalent if they point at labels in the same position in the instruction stream": next_real_insn(label) equal. If the then arm's skip label were a DIFFERENT label that's immediately followed by the same instruction, they'd be equal → merge still.

What if one arm's branch target label is followed by a `barrier`/note then the same instruction? next_real_insn skips notes and barriers? `next_real_insn` returns the next non-NOTE, non-CODE_LABEL insn — barriers? Let's check. If a label is followed by a barrier then the skip insn, next_real_insn(label) = the skip insn; same as another label directly before the skip insn → equal.

OK, alternative: make the two branches differ in the *condition* pattern. What if the then arm's test result is used in a way that yields `(if_then_else (eq (reg) (const_int 0)) ...)` vs `(ne ...)`. For a conditional goto `if (cond) goto skip`, MIPS emits branch_zero with `(if_then_else (ne v0 0) (pc) (label_ref))` for branch-if-false. If instead we write `if (!cond) { } else goto skip;` — GCC might emit `(if_then_else (ne v0 0) (label_ref skip2) (pc))` = branch-if-true to skip? Hmm that would be a bnez to skip. But then the condition would be inverted: `if (!(d >= 0x51)) {} else goto skip` = branch when d>=0x51 to skip, i.e. bnez on v0=(d<81) to skip. The emitted insn would be `bnez v0,skip` instead of `beqz`. Target has beqz. Not matching.

Unless the comparison gets inverted too: `if (!(d < 0x51)) goto skip` → `slti v0,v1,81; beqz v0,skip`. Same as before.

Hmm.

What if we make the else arm's branch differ by having its comparison be on a different register through a real C temp that costs nothing: e.g. 

```
} else {
    s32 e = d >= 0x201;
    if (e) { ... }
}
```
The result still goes to v0.

OK here's another thought: the merge compares `branch` insns. What if the then arm's branch is a *conditional return* or a jump with a different insn code, e.g. branch with `(reg)` in a different mode? no.

Let me step back and consider that maybe the target's RTL is achieved by having the then arm's branch be in a different position: e.g. the then arm's comparison is a `slt` with the constant in a register... no.

Alternatively, maybe the crack is to restructure the control flow entirely so the shared block is not the call but something else, yielding the same 4 extra insns. E.g. make the skip path shared instead:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
} else {
    if (d >= 0x201) goto skip;
}
call; return;
skip: ...
```
The target's extra insns: then-arm `j call`, and the call placement. Alternative structure with the same insn count/layout? The diff shows mine misses 4 insns: at target[172:176] `beqz; nop; j; nop` — so target has an extra [beqz nop j nop] = the then arm's own branch+jump, while mine merged the branch into the shared one. Total: target then arm = slti + beqz + nop + j + nop = 5 insns; mine then arm = slti + (jump to shared) → then executes shared beqz: effectively slti + j + nop + beqz + nop = 5 too? Hmm mine has 197 vs 201 = 4 fewer, so the merge saved 4.

OK, let me look at the actual instruction streams side by side to see exactly.

Target (from 2b8c):
```
lh v0,112(s3)
nop
bnez v0,2bb0
slti v0,v1,513     <- delay slot
slti v0,v1,81
beqz v0,2bc8
nop
j 2bb8
nop
2bb0: beqz v0,2bc8
nop
2bb8: jal
move a0,s3
j 2bf4
nop
```
Mine (v1):
```
lh v0,112(s3)
nop
bnez v0,2ba0
slti v0,v1,513
slti v0,v1,81
2ba0: beqz v0,2bb8
nop
jal
move a0,s3
j 2be4
nop
2bb8: ...
```
So mine merged the then arm's beqz into a shared block at 2ba0 which the bnez jumps to. The else arm falls into it. Interesting: the merge moved the branch to a position reached by both arms.

So mine: unk70!=0 → jump to shared beqz; ==0 → slti 81 → fall into shared beqz. Clever cross-jump.

The target: ==0 arm does its own beqz+j; !=0 arm does beqz; both to skip.

To prevent the merge, the then arm's branch must not equal the else's. OR the then arm's jump to the join must not exist.

Idea: what if the call block is placed *before* the else arm by source order, i.e. the join block is between the arms? Not possible with if/else.

Idea: what if we make the then arm's jump target a label that is NOT the call but a separate label after the else arm, from which a jump goes to the call? That adds a jump.

Hmm, let's think about the register difference more concretely. If the else arm's comparison result is a different register, the branch would be `beqz v1` and target has beqz v0. But wait — which register does target use? Both branches in target use v0. So both arms must use v0.

What if we can make one arm's branch pattern differ in the LABEL_REF position while emitting the same address? The label ref equivalence uses next_real_insn(label). If the then arm's skip label is a distinct label placed just before a `barrier` then the skip code, next_real_insn skips barriers? Let's check next_real_insn: skips NOTE, CODE_LABEL, BARRIER? In GCC, next_real_insn skips NOTEs, CODE_LABELs, and BARRIERs. So a distinct label with a barrier before the skip code still compares equal. 

Hmm what about making the then arm's branch use a different *comparison constant* that is still 0x51? impossible.

Let's reconsider: maybe we don't need the branch insns to be non-identical; maybe we can make the then arm's jump not target the join. What if the then arm ends with `goto docall;` where docall is a label BEFORE the else arm? Can't in source order.

What if we restructure so the else arm is not adjacent to the call? E.g. put the skip code between the else arm and the call? That changes layout.

Alternatively: maybe accept a different but equivalent instruction stream with 201 insns and score 0? No — score 0 means byte-identical to target. So we must reproduce target's exact insns.

Let me look at the target's layout again and think about what source produces it. The then arm jumps over the else arm to the call. In GCC's block ordering, the then arm's fallthrough goes to the else arm (if/else layout: then block, else block). So the then block must end with a jump to the join. That's normal. The cross-jump optimization then merges the common tail. The asm blocked it.

Now, cross-jump of unconditional jumps: find_cross_jump(insn=jump_to_join, label=join, minimum=1). It compares backwards. The then arm's insns before the jump: branch. The code before the join label: the else arm's last insn: branch. Match → merge. minimum 1 → 0 → merge.

But note: the merge only happens if `last1 != e1` and minimum <= 0. One matched insn is enough. So any single identical insn immediately before the jump and before the label triggers it.

To break: the insn before the then arm's jump must differ from the insn before the join label. The then arm's insn before the jump is its branch (because the then body is just the if). Unless the then arm has more code between the branch and the jump. Real C: add a statement after the if that emits an insn... but that would add an instruction to the target stream (not allowed) — unless it's an insn that emits nothing (asm) or a label/note.

So we need a non-emitting RTL insn. Options in GCC 2.7.2 that survive to jump2 without emitting:
1. asm_input (barrier) — forbidden.
2. A `(use)` or `(clobber)` insn — can C produce one? `volatile` register? No. Some builtins? 
3. A CODE_LABEL — can survive if used.
4. A NOTE — skipped by prev_nonnote_insn.

So a CODE_LABEL is the promising one. How to get a used CODE_LABEL between the branch and the jump that survives to jump2? A goto from a *reachable* place to a label placed there. But that changes control flow / adds insns... unless the goto itself is optimized away by jump1 but the label remains? If the goto is removed by jump optimization (e.g. jump threading), the label may become unused and deleted.

What about a label at the end of the then arm that is the target of the skip goto from the then arm's inner if? I.e.:

```
if (d >= 0x51) goto lbl;
lbl: ;
```
This is an identity goto — the branch target is the very next insn. GCC's jump pass would turn the branch into a fallthrough and delete the label. Hmm.

What about a computed use: a `switch` with a case label placed after the branch? A switch statement creates labels for cases. E.g.:

```
switch (0) {
case 0:
    if (d >= 0x51) goto skip;
}
```
GCC folds switch(0) to the case body, deleting the label. Probably.

What about a `for` loop with a `break` label? e.g.
```
for (i = 0; i < 1; i++) { if (d >= 0x51) goto skip; }
```
adds insns.

Hmm. What about `do { if (d>=0x51) goto skip; } while (0)` — the loop end label. GCC's loop optimization might keep a CODE_LABEL for the loop end. It scored 9 though, so no.

Let me actually check v5's jump2 to see if a label appeared. Maybe the merge was prevented at jump2 but a different diff appeared? Score was still 9 with 197 ins. Let me disassemble v5 quickly.
