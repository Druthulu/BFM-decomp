---
ts: 2026-11-06T16:40:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sAzeQSU3X5ZTTQz80Bjb
---
The branch_zero pattern has a match_operator, so the RTL of the branch encodes the comparison operator. For `if (d >= 0x51) goto skip`, the branch pattern could be:
`(if_then_else (ne (reg v0) (const_int 0)) (pc) (label_ref skip))` — NE operator with operands pc/label (inverted jump form). 

If instead we wrote `if (d < 0x51) {} else goto skip;`, the RTL might be `(if_then_else (eq (reg v0) (const_int 0)) (pc) (label_ref skip))`? No — the emitted insn would still be beqz. Actually the operator in the RTL would be different (EQ vs NE) but the same assembly! Let's think: for a branch-if-false to skip, the RTL is `(if_then_else (NE v0 0) (pc) (label skip))` — i.e., if v0 != 0 continue, else goto skip. For a branch-if-true to skip: `(if_then_else (NE v0 0) (label skip) (pc))` — if v0 != 0 goto skip. Different pattern structure but the same operator.

The emit code: operands[2]=pc for normal jump → "b%C0z" = bne for NE. For inverted jump (operands[2] != pc): "b%N0z" = beq for NE. So:
- `(if_then_else (NE v0 0) (pc) (label skip))` → inverted jump → "beq v0,0,skip" = beqz.
- `(if_then_else (NE v0 0) (label skip) (pc))` → normal → "bne v0,0,skip" = bnez.

So both are NE but the pc position differs. rtx_renumbered_equal_p compares the if_then_else structure: `(if_then_else cond (pc) (label))` vs `(if_then_else cond (label) (pc))` — different structure! But if both arms branch to skip, both would be inverted form (pc first) — identical.

Unless one arm branches to skip and the other... hmm.

What if the then arm's branch is the "normal jump" form branching to the *call* (bnez to call)? That emits `bnez v0,call` where v0=(d<81). But target's then arm has `beqz v0,skip; j call` — two insns. So no.

OK here's yet another thought: what if we make the then arm's comparison emit the branch in the normal form (branch-if-true to a *later* label), e.g.:

```
if (d >= 0x51) goto skip;
```
vs writing:
```
if (d < 0x51) goto docall;   /* bnez to docall */
goto skip;
```
The then arm: slti 81; bnez v0, docall; j skip. Target: slti; beqz skip; j docall. Different instruction order (bnez vs beqz). no.

Hmm.

Let's consider that maybe the merge can be blocked by making the then arm's jump to the join target a label whose preceding insn differs, by placing the call block differently. What if the call block is shared but positioned not right after the else arm — e.g., after the skip code? Layout would differ.

New idea: make the else arm end with a *different* insn than a branch by moving the else arm's test before the unk70 test? no.

Alternative: maybe we can make the *then* arm's last insn before the jump a `(use)` from a function call... 

Actually, here's a classic real-C RTL-only difference: an `if` condition involving a call? no.

Let me reconsider the problem statement: "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". None of these obviously produce a non-emitting insn. But maybe one of them changes the RTL tail differently: e.g., "&&/|| folds" — the then arm's condition could be written as `if (d >= 0x51 && ...)`. Hmm.

Wait. Maybe we're overcomplicating: perhaps the merge only happens because both arms' branches are `beqz v0` — but what if the two comparisons use different registers *and* the target's both show v0 because... let me re-read the target: 
```
2b94: bnez v0,2bb0
2b98: slti v0,v1,513
2b9c: slti v0,v1,81
2ba0: beqz v0,2bc8
```
Both use v0 and v1.

Hmm what if we use a *loop* for the whole if-else? "loop shape" is in the catalog. E.g., turn the if/else into a `while` loop that executes once. That changes the RTL tail (loop notes/labels) and may block cross-jump while emitting identical insns (loop notes don't emit). Interesting! A loop creates NOTE_INSN_LOOP_BEG etc. But notes are skipped by prev_nonnote_insn. A loop also has CODE_LABELs (the loop end label, and continue labels). Those labels are real CODE_LABELs and could sit between the branch and the jump!

E.g.:
```
while (1) {
    if (unk70 == 0) { if (d >= 0x51) goto skip; }
    else { if (d >= 0x201) goto skip; }
    break;
}
```
Hmm, loop.c might optimize.

Or `do { ... } while (0)` — we tried and it vanished. What about a `for` loop with a break that's not folded? e.g. `for (i = 0; i < 1; i++)` — adds insns.

Hmm, what about `do { ... } while (unk70 == 2)`? Changes semantics.

Let's think about the label idea again but with a *real* goto that doesn't add insns: the then arm's `goto docall` is a jump. If there's a label between the branch and that jump... The label must be a target of some branch. What if the else arm also jumps to that label? Then the label is used. E.g.:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
mid:
    goto docall;
} else {
    if (d >= 0x201) goto skip;
    goto mid;
}
docall: call;
```
The else arm's `goto mid` jumps backward into the then arm — that would re-execute... semantics: else arm with d < 0x201 jumps to mid → docall. Same result. But the layout/insns: else arm ends with `j mid` — an extra jump not in target. Unless the jump gets converted... no.

OK, let me look at this from a completely different angle: maybe I should check whether a *note* can block it. find_cross_jump's i1 = prev_nonnote_insn(i1) skips notes; i2 loop skips NOTE and CODE_LABEL. So notes never block.

What RTL insns emit no assembly? Let me grep the MIPS md for define_insn with empty or "nothing" templates... e.g. `define_insn "nop"` emits nop. `blockage`? `(define_insn "blockage" ... "" ...)` emits nothing! The scheduler uses `(insn (unspec_volatile [(const_int 0)] 0))` blockage insns. Can C produce a blockage? Not directly.

What about `(use)` insns from `__builtin_...`? 

Hmm, what about an unused `static` variable's initialization? no.

What about `__attribute__((unused))`? no.

OK, maybe the answer is different: maybe we can make the then arm's branch *not exist* as a separate branch by restructuring so that the target's beqz+j pair arises from a different construct, e.g. a `&&` fold. Look at target: then arm `slti 81; beqz skip; j call`. What if the then arm is:

```
if (unk70 == 0 && d >= 0x51) goto skip;
```
This folds to: test unk70; if 0 → test d. Hmm, `&&` short-circuit: `if (unk70 == 0 && d >= 0x51) goto skip;` compiles to: bnez unk70 → after; slti; beqz skip; after: ... The then arm's RTL tail: slti; beqz skip; jump after. That's the same.

What about `if (d >= 0x51 && unk70 == 0)`? order swapped.

Hmm what about the else arm as `else if` with `||`:
```
if (unk70 == 0) { if (d >= 0x51) goto skip; }
else if (d >= 0x201) goto skip;
```
same.

Let me try to find how other barrier items were cracked: "barrier | func_801564B0 | MATCH — ||-fold of the two return-0 tests" and "barrier | func_80180100 | MATCH — field-direct &= and -- on s0->unkAC (no temps), dead pad[2] dropped". Those are different kinds.

Maybe I should look at the C0505 catalog for the move list. Let me check cookbook C0505.
