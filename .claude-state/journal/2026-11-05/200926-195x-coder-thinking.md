---
ts: 2026-11-06T03:09:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_to9jclYSsfhCUTdfV2jz
---
Mine's merged shape:
```
4be0: bgez v0,4bf0     ; if d >= 0 goto shared
4be4: slti v0,v0,513   ; delay slot (first arm's test)
4be8: subu v0,v1,a0    ; else arm's d
4bec: slti v0,v0,513
4bf0: beqz v0,TAIL     ; shared test
4bf4: nop
4bf8: rest
```
So the compiler inverted the first arm's `if (d >= 0)` to `bgez → shared test`, putting the first arm's slti in the delay slot, then the else's subu/slti, then the shared beqz.

Target:
```
4be0: bltz v0,4bf8     ; if d < 0 goto else
4be4: slti v0,v0,513   ; delay slot
4be8: beqz v0,TAIL
4bec: nop
4bf0: j 4c08           ; first arm's jump to the rest
4bf4: nop
4bf8: else: subu; slti; beqz TAIL; nop
4c08: rest
```

So the target keeps the two tests separate and the first arm ends with `j 4c08`.

The target's structure: the first arm's `if (d > 0x200) goto TAIL;` followed by a `j 4c08` (the arm's end). The else arm's test falls through to 4c08.

For the compiler to produce the target, the two `if (d > 0x200) goto TAIL` must not merge. The barrier did that by splitting the RTL.

Real-C: maybe make the first arm's tail not identical by using a different form for the goto. E.g., the first arm's `if (d > 0x200) goto TAIL;` and then the arm ends (falls to the code after the if). In the target, the first arm ends with `j 4c08` (the jump over the else). The else is physically after the first arm. So the first arm's fallthrough is the else, hence the `j 4c08` to skip it.

The cross-jump merges the two `slti;beqz` tails. To prevent, make the first arm's tail differ: e.g., invert the first arm's test: `if (d <= 0x200) goto REST;` — then the first arm's tail is `slti; bnez REST; j TAIL`? That changes the code.

What if the first arm's test is written as `if (d >= 0 && d <= 0x200) goto REST;`? Hmm.

Let me think about the target's actual C. The target's first arm:
- `bltz v0, else` (from `if (d >= 0)`)
- `slti v0,v0,513` in the delay slot (the d>0x200 test)
- `beqz v0,TAIL`
- `j 4c08` (the end of the if arm)

The compiler chose `bltz` (not `bgez`) — meaning the source had `if (d >= 0) { ... } else { ... }` and the else block is the target of bltz (the fallthrough is the if-body). Mine has `bgez` because the compiler reordered/inverted due to the cross-jump.

What if we write the condition inverted: `if (d < 0) { else } else { if }`? That would put the else arm first physically. ✗

Hmm. What if we make the first arm's `d > 0x200` test use a *different variable* or expression so the slti insns differ? E.g., first arm: `if (d > 0x200) goto TAIL;` and else arm: `d = buf1 - unkA; if (0x200 < d) goto TAIL;` — same RTL.

What if the else arm uses `if ((u32)d > 0x200)`? The slti would differ (sltiu vs slti)! The target shows `slti` (0x2842). Hmm.

What if the first arm's test is `if (d > 0x200)` and the else arm's is `if (d > 0x1FF)`? Different constant → slti 512 vs 513. Target shows both 513. ✗

What if the *else arm's* d computation is folded differently so the slti's operand differs? Target: both `slti v0,v0,513`. Same.

So the insns are identical; the only way to prevent the merge is a CFG/label difference. The barrier provided an insn. Real-C options:
- A `goto` that creates a label between the test and the tail? 
- Make the first arm's tail not fall through to the same label.

Let me look at the cross-jump mechanics here: the two blocks both end with `beqz v0,TAIL`. The first arm's block: subu; slti; beqz; j REST. The else block: subu; slti; beqz; (falls to REST). find_cross_jump for the first arm's `j REST` (simplejump) compares its block's tail with REST's predecessor... Hmm, actually the merge in mine happened at the `bgez` inversion, suggesting a different transform.

Mine's shape: the compiler inverted `if (d >= 0)` to `bgez shared` because the first arm's body ends with `j REST` and the else follows; the "conditional jump over an unconditional jump" transform (jump.c 1733) fired: `if (d>=0) { ... j REST } else { ... }` → invert to `bgez REST; else-body; REST:`. That's the standard if-else inversion when the if-body ends with a jump. So the compiler naturally produces `bgez`.

In the target, the inversion did NOT happen: `bltz else` then the if-body then `j REST`. Why? Because the else-body's tail (slti;beqz TAIL) was NOT identical to the if-body's tail? Hmm, the inversion condition (line 1733) requires: condjump over an unconditional jump; it inverts the condjump and deletes the unconditional jump. The condition also requires `no_labels_between_p (insn, reallabelprev)` and `simplejump_p(reallabelprev)` and `prev_active_insn(reallabelprev) == insn`. Hmm.

Actually the merge of the two slti/beqz tails is a separate cross-jump. In mine, the first arm's slti/beqz was merged with the else's: the `bgez` delay slot holds the first slti, and the else's slti, then a shared beqz. So the merge happened across the two arms.

In the target, no merge. The barrier prevented it.

Real-C: maybe make the two `if (d > 0x200)` tests use different *comparison forms* that generate the same slti but with different RTL, so the cross-jump's insn comparison fails. Cross-jump compares INSNs after reload (jump2), so RTL differences that vanish at codegen are irrelevant. Both are slti;beqz — identical insns.

Unless the delay slots differ at jump2! The cross-jump's minimum is 1 (one side falls through). The matched suffix at jump2: the beqz? Let me think: at jump2, the blocks are:
- if-body: subu; slti; beqz TAIL; j REST.
- else: subu; slti; beqz TAIL; (falls to REST).
find_cross_jump(insn=beqz? no...). The merge in mine merged the tails.

Hmm, what if the first arm's `goto TAIL` is written so that the branch's delay slot differs? E.g., in the first arm, put the `d` computation such that the delay slot after the beqz has a different insn? The target has nop in the delay slot for both.

I think the polarity trick from the cookbook might apply: write one arm as `if (d > 0x200) goto TAIL;` and the other as `if (d <= 0x200) goto REST2;` where REST2 is the code after... Hmm, that would change the target.

Let me look at the cookbook's exact §162/§5a polarity example: "Both arms must be written `if (x <= 0) E00(a0,6); else C78(a0);` — the SAME polarity in BOTH sites." That was for merging call bodies.

For our case, the target's two tests ARE the same polarity (slti/beqz). So the original C likely had the same polarity and the compiler didn't merge due to something else.

Wait — maybe the original's two arms were NOT both `goto TAIL`. Maybe the first arm's test was `if (d > 0x200) goto TAIL;` and the else's was `if (d > 0x200) goto TAIL;` — same. The target shows both as `slti;beqz TAIL`. Identical. So the original compiler did NOT merge them. Why?

Maybe because the two blocks are not "cross-jumpable" due to the *first* insn before the test: the merge requires the matched suffix to be preceded by different insns; that's fine (minimum 1). Hmm.

Unless the target's first arm's beqz block is followed by a `j` (the arm's jump), so the block ends with `beqz; nop; j; nop` and the else's ends with `beqz; nop` falling into REST. find_cross_jump for the else's fall-through: the label REST's predecessor is the else's beqz/nop. The if-body's tail... 

Honestly, the empirical approach is better. Let me try C variants:
n1: swap the arms' order: `if (d < 0) { else } else { if }`.
n2: write the first test as `if (d > 0x200) goto TAIL;` and the else as `if (d > 0x200) goto TAIL;` (current).
n3: use a shared temp for the absolute difference.
n4: write the else arm as `d = -d; if (d > 0x200) goto TAIL;`? The target's else uses `subu v0,v1,a0` (buf1 - unkA), which is -d. If the source were `d = -d; if (d > 0x200)`, the codegen would be `subu v0,zero,v0` (neg) then slti — different. ✗
n5: `if (d >= 0) { if (d > 0x200) goto TAIL; } else { ... }` — current.
n6: Use `else if`: `if (d >= 0) { if (d > 0x200) goto TAIL; } else if ((d = buf1-unkA) > 0x200) goto TAIL;` — same.
n7: The two tests could differ if one uses a `s16` temp: `s16 e = d; if (e > 0x200)`.
n8: Make the first arm's test a `>` on a different var: `if (d - 0x200 > 0)`? codegen differs.

Let me look at what the target's `j 4c08` implies: the if-body ends with a jump to REST. If the source were `if (d >= 0) { if (d > 0x200) goto TAIL; } else { ... }`, the if-body's fallthrough after the inner if is the end of the outer if → the code after the else, i.e., REST. So the compiler emits `j REST` at the end of the if-body (to skip the else). Yes.

In mine, the compiler inverted the outer if to avoid that jump, merging the tails. The inversion is the "conditional jump over an unconditional jump" transform. To prevent the inversion, the else-body's first/last... The transform at jump.c 1733:
```
else if ((this_is_condjump || ...) && !this_is_simplejump
         && reallabelprev != 0
         && GET_CODE (reallabelprev) == JUMP_INSN
         && prev_active_insn (reallabelprev) == insn
         && no_labels_between_p (insn, reallabelprev)
         && simplejump_p (reallabelprev))
  { invert_jump(insn, JUMP_LABEL(reallabelprev)); ... delete_insn(reallabelprev); }
```
This requires the unconditional jump (`j REST`) to be the *immediately following* insn after the conditional jump's target label... i.e., the else-body must be empty or the jump right before the label. Hmm.

Actually, in mine the inversion happened: `bgez REST` — the conditional was inverted to jump to the if-body? Let me not go deeper.

Given the complexity and time (item 4 at ~15 min), let me try a batch of variants.

n1: invert the outer condition and swap the arms:
```
if (d < 0) {
    d = buf1 - unkA;
    if (d > 0x200) goto TAIL;
} else {
    if (d > 0x200) goto TAIL;
}
```
This puts the else arm first. The target layout has the d>=0 arm first (bltz to the else). Hmm, with the inverted condition, the compiler emits `bgez else`? Let me just test.

n2: write the outer as `if (d >= 0) { ... } if (d < 0) { ... }` (two ifs instead of if-else).
n3: use a single computed test: `if (d < 0) d = -d; if (d > 0x200) goto TAIL;` — codegen: subu/negu... different.
n4: add `else` with the inner if as `if (d > 0x200) { goto TAIL; }` braces.
n5: make the first arm's inner if body a `return`? no.
n6: `if (d >= 0) { if (d > 0x200) goto TAIL; else goto REST; }`? explicit goto REST.
n7: `if (d >= 0) { if (d > 0x200) goto TAIL; goto REST; } else { ... }` — an explicit goto REST at the end of the if-body; the compiler may not invert.
n8: `if (d >= 0) { if (d <= 0x200) goto REST; goto TAIL; } else {...}`.

Let me test n1, n2, n4, n6, n7, n8.
