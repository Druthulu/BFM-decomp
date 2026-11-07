---
ts: 2026-11-06T16:41:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_E0biU4VG1LvtMnJnxw65
---
Interesting! In v3, the else arm's branch is `(if_then_else (eq v0 0) (label_ref 450) (pc))` — the EQ form (normal jump: bne? wait). And the then arm's branch was `(ne v0 0) (pc) (label 450)` — inverted. So in v3 the two branches ALREADY differ (EQ vs NE)! But the merge still happened (then arm's branch deleted, jump 421 -> 521 before the else branch 433).

Hmm wait, then how did find_cross_jump match? Because for EQ/NE, the code says:

```
if (code == EQ || code == NE || GET_RTX_CLASS (code) == 'c')
    return ((rtx_renumbered_equal_p (XEXP (x, 0), XEXP (y, 0))
	     && rtx_renumbered_equal_p (XEXP (x, 1), XEXP (y, 1)))
	    || (rtx_renumbered_equal_p (XEXP (x, 0), XEXP (y, 1))
		&& rtx_renumbered_equal_p (XEXP (x, 1), XEXP (y, 0))));
```

This is for the code EQ/NE at the top level of the rtx. The branch pattern is `(set (pc) (if_then_else ...))` — a SET. The SET case is handled by the generic '2' class comparison: compares XEXP(0) and XEXP(1) in order. XEXP(0) = pc both. XEXP(1) = the if_then_else with (eq ... (label) (pc)) vs (ne ... (pc) (label)). For if_then_else, the code is IF_THEN_ELSE (class '?') — the generic path compares operands in order: cond, then, else. cond: `(eq v0 0)` vs `(ne v0 0)` → code differs (EQ vs NE) → not equal. So the branches differ!

But the merge still happened! Because of the "register equivalence" branch: the matched suffix might not be the branch. Let me re-read: in v3.jump2, the then arm's branch is gone and jump 421 targets 521 which is right before the else's branch 433. So do_cross_jump deleted insns from newjpos to insn: newjpos must have been the then arm's branch 413. So find_cross_jump matched the branch despite EQ/NE?? 

Hmm wait, maybe the then arm's branch was not matched with the else's branch but with something else. Actually the label 521 is before branch 433, and the deleted range was [then-arm branch ... jump]. Hmm, so last1 was the then arm's branch.

Unless... the then arm's branch in v3 was also EQ? Let me look at v3.jump (pre-jump2) to see.

Actually, maybe at jump2 the RTL was regenerated after reload: the branch patterns get rebuilt from the machine description, and both become the same form? Post-reload, insns are recognized via recog; the branch pattern might be normalized. Indeed at jump2 (after reload), the branch insn is re-recognized: `(set (pc) (if_then_else (eq v0 0) (label) (pc)))` might be recognized by the same branch_zero pattern, and the RTL stays as-is. Hmm.

In v3.jump2, the else's branch is `(eq v0 0) (label 450) (pc)` = normal jump → "b%N0z" with NE... wait operand[0] is the operator = EQ; operands[2]=label (not pc) → normal jump → case EQ: "beq v0,0,label". So it's beqz. And the then arm's branch (in v1) was `(ne v0 0) (pc) (label)` = inverted → case NE: "beq v0,0,label" = beqz. Both emit beqz but different RTL!

And yet cross-jump merged them... how? Let me re-read rtx_renumbered_equal_p for IF_THEN_ELSE. IF_THEN_ELSE has class '?'. Not 'c', not '<', not '2', not '1' → falls to the generic loop comparing all operands. cond differs EQ vs NE → 0. So not equal.

But maybe the merge compared the then arm's branch with the else arm's branch only after... Hmm, let me look at v3.jump2 more carefully — maybe the deleted range was not the branch. Actually wait: maybe in v3, the then arm's branch was already EQ at jump2 (normalized by reload). Let me check the .jump (jump1) dump for v3 to see the branch forms.

Actually, hold on: maybe the merge in v3 happened at jump1 (pre-reload), where the branches were both `(ne ...)` inverted form. Then at jump2 the else branch shows EQ because... hmm no.

Let me check v3.jump1's tail.
