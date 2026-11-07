---
ts: 2026-11-06T16:40:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_U1DCjnnHIHvtltBb7mZB
---
do_cross_jump: `get_label_before(newlpos)` creates label 523 before the else's branch 431 (newlpos = 431). Then redirects jump 421 to 523, and deletes insns from newjpos to insn (the then arm's matched range: from branch 413 to jump 421). So the then arm's branch 413 is deleted, and the jump now targets the else's branch. Exactly what we see.

So find_cross_jump(insn=421, JUMP_LABEL=440, minimum=1) returned f1=branch 413, f2=branch 431.

Backward scan: i1 = prev_nonnote_insn(421) = 413 (branch). i2 = PREV_INSN(440) skipping notes/labels → 431 (branch). Compare: equal → minimum 1→0, last1=413,last2=431. Loop: i1 = prev_nonnote(413) = 412 (slti 81); i2 = PREV(431) → 430 (slti 513). Compare: differ → break. minimum=0, last1 != e1 → merge.

To prevent, we need i1's first insn to not match i2's first insn, i.e., the then arm's insn before the jump must differ from the else arm's last insn.

Options:
(a) The then arm's jump is preceded by a non-branch insn (e.g. a second slti? no).
(b) The then arm's jump is preceded by nothing (i1 = CODE_LABEL → break, no merge). If the then arm's block starts with the jump (i.e., no branch before it) — e.g., if the then arm's body is just `goto docall;` with the condition tested before the block split. Hmm!

Consider this source:
```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;
}
```
The then arm block = [slti; branch skip; jump docall]. i1 before the jump = branch.

What if instead we write the then arm as:
```
if (unk70 == 0) {
    if (d >= 0x51) {
        goto skip;
    }
    else goto docall;   /* hmm */
}
```
Same.

(c) Make the else arm's last insn before the join not the branch but something else. If the else arm's block ends with, e.g., a jump (not a branch), then i2 = that jump, i1 = branch → differ → break, minimum=1, last1=0 → no merge. So if the else arm ends with an unconditional jump to the call, and the call is placed right after (so the jump is to the next insn and gets removed)... hmm, if it gets removed at jump1, at jump2 there's no jump.

But what if the else arm's jump targets a label that is NOT immediately next? E.g., put the call in a separate block that the else arm jumps to, with the skip code in between. Layout: then arm, else arm, skip code, call? Target has call before skip. no.

(d) Make the then arm's block have TWO insns before the jump where the first differs, and the matching one is only the second... no, the first comparison is what matters.

(e) Break the branch equality: make one branch's LABEL_REF point at a label whose next_real_insn differs. But both branches must go to the same skip instruction to match target's emitted code. If the then arm's branch goes to a label at a different position... the emitted branch target would differ. Unless the label is at the same instruction (different position in the RTL chain but next_real_insn equal) — then they're equal.

Hmm, wait: what about making the two branches differ in the *register* by having one use a pseudo that gets a different hard reg but the *instruction* still be beqz v0? Not possible.

(f) Make the then arm's branch a conditional branch with a different INSN_CODE but same assembly: e.g. `branch_zero` vs `branch_zero_inverted`? The MIPS machine description may have two patterns for branch if zero: one with the delay slot. Same.

Hmm. Let me look at the MIPS md for branch_zero patterns.
