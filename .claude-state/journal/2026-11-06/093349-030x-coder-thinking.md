---
ts: 2026-11-06T16:33:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NaGkuZgvhMIqi6L2TWjV
---
The with-asm version in jump2:
- then arm: slti 81; beqz skip (branch_zero, if ne -> pc else label 450); asm; jump 438 (join)
- else arm: slti 513; beqz skip; falls to 438 join.

So indeed the asm insn is between the branch and the join jump. Note the then arm already had a `jump 438` to the join! That jump existed because... the join label 438 is after the else arm. So in the RTL, the then arm ends with an unconditional jump to the join, and the asm is just before it. So the asm's role: it prevented cross-jump from matching [beqz] and merging. Because backward comparison: then arm's last insns are [asm, jump 438] — wait backward from the end of the then block: the block ends with jump 423? The then block is [slti 412, branch 413, asm 421, jump 423]. The else block ends [slti 429, branch 430]. Comparing backward: jump 423 vs branch 430 → different → no merge.

Without asm, the then block would be [slti, branch, jump 438]. Backward: jump 438 vs branch 430 differ → no merge either?? But mine merged. Hmm, in mine's dump (v1) the then block was [slti 412, jump 421] — the branch 413 was GONE! In v1, the then arm's `beqz skip` got eliminated/redirected: look at v1 dump: after 412 slti there's only `jump -> 523`. And 523 is right before the else's branch 431. So jump threading converted the then arm's branch into... hmm, actually the then arm's beqz skip and the else arm's beqz skip were merged by *cross-jump at jump (the first jump pass)*? The dump shown was jump2 but the merge may have happened at jump1 (the .jump dump). Let me check v1.i.jump for the region. In v1.jump2, the then arm's branch disappeared and it jumps to 523. That's after cross-jump merged [branch skip] into the else arm's branch, leaving the then arm with just the jump.

Wait no: in v1, B_then = [412 slti 81, 421 jump 523]; 523 label before 431 branch. So the then arm jumps into the middle of the else block to execute the else's branch using v0 from its own slti. That's a cross-jump merge of the branch. So the merge happened at the second jump pass (jump2) since jump2 is the post-reload pass and its dump shows the merged form.

So to prevent: make the then arm's branch pattern differ from the else's. Options:
- The branch pattern is identical for both because both are `slti; beqz`.
- If the then arm's comparison is expressed so the branch becomes a different insn, e.g. `bnez` vs `beqz` with swapped target. E.g. then arm: `if (d < 0x51) goto docall;` — that's the *inverted* form: `slti v0,v1,81; bnez v0,docall` and fall to skip. But target has beqz to skip. Different insns.
- Unless the inverted form gets canonicalized back.

Alternative approach: make the else arm's branch pattern differ by using a different compare insn that still emits `slti`: e.g. `if ((s32)(d & 0xFFFF) >= 0x201)`? no, d is small.

What about `if (d - 0x201 >= 0)`: addiu + bgez → 2 insns, target 1 slti. No.

Hmm, but wait: the target itself has `slti v0,v1,513` in the delay slot of the `bnez v0,2bb0`. In the target the else arm's slti sits in the delay slot of the unk70 branch. Fine.

Maybe the trick: make the two arms' branches use different label refs but otherwise equal? rtx_renumbered_equal_p might compare labels by identity; both branch to the same skip label, so equal. If one arm branches to a *different* label that jumps to skip, the patterns would differ and no merge... but that adds an insn? A `goto skip` from a different label... hmm.

What if we restructure the C so the two skip gotos target different labels? In C both `goto skip;` are the same label. If we split: `goto skip1;` / `goto skip2;` where skip1/skip2 are two consecutive labels both before the tail code — GCC merges them into one label at jump1. Maybe not if there's something between.

Alternatively, make one arm's "skip" path a `return`? No, skip code is shared.

Hmm, think differently. Maybe the intended crack for this item is not about the branch merge but a different C arrangement that yields target's layout naturally. Consider writing the code as the original probably was:

```
if (d <= 0) { ... }
else if ((...&1) == 0) {
    if (unk70 == 0) {
        if (d < 0x51) {
            func_801822A4(param_1);
            return;
        }
    } else if (d < 0x201) {
        func_801822A4(param_1);
        return;
    }
}
skip: ...
```
Here each arm's fall-through is the call; skip after. Cross-jump would merge the two call+return blocks → then arm jumps to merged call block after else. That's target's layout! Let me check: then arm [slti 81; bgez/branch to else?]... Hmm.

Actually let's simulate. Source:
```
if (unk70 == 0) {
    if (d < 0x51) { call; return; }
} else {
    if (d < 0x201) { call; return; }
}
/* fall to skip */
```
Then arm: slti (d<0x51); branch if true to call block A; else fall to... the else arm? Layout: then arm, else arm, then skip. Hmm the then arm's false path must jump to skip. And call block. This duplicates calls; cross-jump merges them.

Let's just try several variants quickly with sc.sh. Variants:
v3: call duplicated inside each arm with `if (d < ...) { call; return; }` and then fallthrough to skip.
v4: same but with goto.

Let me write v3:

```
        if (((Unkstruct_800B5CB8 *)param_1)->unk70 == 0) {
            if (d < 0x51) {
                func_801822A4((void *)param_1);
                return;
            }
        } else {
            if (d < 0x201) {
                func_801822A4((void *)param_1);
                return;
            }
        }
```
and no call after. But then the `skip:` label follows. Note the original had `else if ((...)&1)==0)` wrapper. Keep it.

Let's test v3.
