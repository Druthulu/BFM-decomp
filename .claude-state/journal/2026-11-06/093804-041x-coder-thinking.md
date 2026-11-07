---
ts: 2026-11-06T16:38:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tyDDPblbXjksAHakES9Q
---
Key: LABEL_REF comparison: "Two label-refs are equivalent if they point at labels in the same position in the instruction stream": `next_real_insn(LABEL(x)) == next_real_insn(LABEL(y))`. Both branch to the same skip label → equal.

Also REG comparison after reload: reg_renumber maps pseudo to hard reg. Both branch on v0 → equal. But note: if one arm's branch is on a different hard register, not equal. So if I can make the else arm's comparison result land in v1 (or the branch test a different reg), the merge fails while the emitted instruction would be... `beqz v1` instead of `beqz v0` — different from target (target uses v0). Hmm, but wait: could the register differ but the instruction still print `v0`? No.

Alternatively: if the two arms' branches point at *different labels* that are at the same instruction position (next_real_insn equal), they're equal. So different labels in the same position are equivalent.

OK so what if one arm's branch uses the SAME v0 but the label target differs and is at a different instruction position? Then the insn differs → no merge, but the emitted branch would target a different address → the diff would show a different jump target. But maybe the target itself has different targets? Target's two branches both go to 2bc8 (skip). So no.

Hmm, what if the then arm's branch target is the same instruction but through a different label that has a `nop`... no.

Different approach: can we break the merge by making the then arm's jump target not the join label but something whose "code before" differs? The unconditional-jump cross-jump uses find_cross_jump(insn, JUMP_LABEL(insn), 1). e1 = the jump insn, e2 = the label. It compares the code before the jump (then arm) with the code before the label (else arm). The match happens on the branch. What if the then arm's jump targets the call label but the call is placed such that the code before it is not the else arm's branch? E.g. if the call block is not immediately after the else arm, but somewhere else... In the target, the call is after the else arm.

Alternatively, what if the then arm has no unconditional jump (falls through to the join) — that happens if the join is placed right after the then arm. Then no cross-jump of unconditional jump. But the layout would differ from target (call before else arm). Unless the else arm is laid out elsewhere.

Wait — target layout: then arm; j call; else arm; call. What if instead we produce: then arm; call; ... no.

Hmm, let's revisit: maybe the merge can be broken by making the else arm's *last insn before the label* different. The else arm's last insn is its branch 431. If the else arm ended with something else, e.g. an extra instruction that doesn't appear in the target... no.

Let's reconsider the problem from the target's side: the target's then arm ends with `beqz v0,skip` then `j call`. The else arm ends with `beqz v0,skip` then falls to call. The cross-jump merge compares then-arm code before its `j call` with else-arm code before the call label: [branch] vs [branch] — identical → merge. So GCC would ALWAYS merge this... unless the branches differ. In the target they ARE identical. So how did the target avoid the merge?

Because the asm was there — the asm sat between the branch and the jump in the then arm, making the last insn before the jump an asm, not the branch. That's the barrier. And with the barrier, the emitted insn sequence has no asm, so target = branch, j.

So to reproduce without asm we need SOME insn-level difference in the then arm that survives to jump2 as an RTL insn but emits nothing. Candidates in GCC 2.7.2:
- `(use ...)` / `(clobber ...)` insns — can be produced by...? A `volatile` asm is the usual. 
- A NOTE — notes are skipped by prev_nonnote_insn? i1 = prev_nonnote_insn(i1) skips notes. So a note won't help.
- A CODE_LABEL — prev_nonnote_insn stops at labels? Let's check: `prev_nonnote_insn` skips notes but not labels. In find_cross_jump, i1 = prev_nonnote_insn(i1); then `if (GET_CODE(i1) == CODE_LABEL) { --minimum; break; }`. So a CODE_LABEL between the branch and the jump breaks the match (minimum 1→0, last1==0 → no merge). 

So: get a real CODE_LABEL in the then arm between the branch and the end. How? A label that's a goto target. E.g.:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
lbl:
    goto docall;
} else {
    if (d >= 0x201) goto skip;
}
```
with `goto lbl` somewhere that's reachable... If nothing jumps to lbl, it's deleted. But a label can be "used" by being the target of a jump that is later optimized away? Hmm.

What if the else arm jumps to lbl? We saw that changes control flow. Actually, consider:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
lbl:
    goto docall;
} else {
    if (d >= 0x201) goto skip;
}
```
No one jumps to lbl. GCC's jump pass removes unused labels.

What about making lbl the target of the skip goto of the *then* arm? i.e.:
```
if (d >= 0x51) goto lbl;
lbl: ...
```
That's an identity goto — not allowed as a launder.

Alternatively a `switch` inside the then arm creates labels. Hmm.

What about a loop: `for (;;) { ... break; }` — creates a loop note/label? do{}while(0) creates a label? C0535 mentions do-while(0) splits cse1 EBB. A do-while(0) might leave a CODE_LABEL at its end. Let's test: wrap the then arm body in `do { if (d >= 0x51) goto skip; } while (0);` — this may create a label after the body (the do-while's end label), which could land between the branch and the jump. That's a real C construct and the constraint says do{}while(0) only with `// !FAKE: do-while` comment — implying it's allowed with that marker! Let's try.

Actually the `// !FAKE: do-while` marker is for when we use do-while(0) as a crack. Great, that's a documented allowed move.

Let me try wrapping the then arm in do{}while(0).

Actually, careful: the do-while(0) would be around the if. Let's write:

```
if (unk70 == 0) {
    do {
        if (d >= 0x51) {
            goto skip;
        }
    } while (0);
} else {
    if (d >= 0x201) {
        goto skip;
    }
}
call;
```

Test.
