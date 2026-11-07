---
ts: 2026-11-07T01:15:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aNonHpuJUaCHxzcyXlCw
---
All 1. 49 tries now (30 + 13 + 6). Time 18:15:39, item 2 started 18:09 → ~7 min.

I need until ~18:29. Let me think if there's any crack left.

Insight attempt: the substitution is by local-alloc's update_equiv_regs / optimize_reg_copy. Let me look at what exactly did it. Let me diff the .sched RTL and .lreg RTL for insn 43:
- .sched: `(set (mem (plus (reg/v 72) 516)) (reg/v 74))`, REG_DEAD (reg/v 72).
- .lreg: `(set (mem (plus (reg:SI 4 a0) 516)) (reg/v 74))`, REG_DEAD (reg/v 74).

And insn 46 in .sched: `(set (reg:SI 4 a0) (reg/v 72))` with REG_DEAD (reg/v 72).
In .lreg: insn 46 `(set (reg:SI 4 a0) (reg/v 72))` — and where did r72's death go? The .lreg insn 46 probably still has REG_DEAD 72.

So the store's base was replaced with a0 (the dest of insn 46), and the store's REG_DEAD for r72 was dropped (since r72 is no longer referenced there).

This looks like `optimize_reg_copy_1` (called for a reg-reg copy where SRC is not dead). But SRC (r72) IS dead at insn 46... unless the REG_DEAD note wasn't present at that point. Hmm, in .sched it shows REG_DEAD (reg/v:SI 72)? Let me verify insn 46's notes in the .sched dump.

Actually the .lreg dump's insn 46 has `(expr_list:REG_DEAD (reg/v:SI 72) ...)`? Let me check. Earlier I saw insn 46 in lreg: `(insn 46 40 43 (set (reg:SI 4 a0) (reg/v:SI 72)) 159 {movsi_internal2} (insn_list:REG_DEP_ANTI 28 (nil)) (nil))` — hmm, no REG_DEAD note shown in the earlier print? Let me look again at the lreg output I captured:

```
(insn 46 40 43 (set (reg:SI 4 a0)
        (reg/v:SI 72)) 159 {movsi_internal2} (insn_list:REG_DEP_ANTI 28 (nil))
    (expr_list:REG_DEAD (reg/v:SI 72)
        (nil)))
```
Yes, REG_DEAD (reg/v:SI 72) is there.

So the copy has SRC dead → the `optimize_reg_copy_1` branch is skipped; `optimize_reg_copy_2` requires DEST to be a pseudo (a0 is hard) → skipped.

Then how did the store's base change? Let me look at `optimize_reg_copy_3` or the code after the scan: "Now scan all regs killed in an insn to see if any of them are registers only used that once. If so, see if we can replace the reference with the equivalent from."

That's the REG_EQUIV replacement: for each insn, for each REG_DEAD note, if the dead reg is mentioned in the pattern, and the reg has reg_equiv_replacement set... r72 would need reg_n_refs==2 and reg_basic_block<0 and rtx_equal_p(note, SET_SRC).

Hmm, r72 has 4 refs.

Let me look at the rest of the function (after line 1100) for the replacement logic. Actually, let me look at `optimize_reg_copy_1` — it's called when SRC is not dead. In our case SRC is dead. Hmm.

Wait — maybe the RTL at local-alloc time differs from the .sched dump. The .sched dump is after sched1; local-alloc runs after. The REG_DEAD notes are recomputed by flow? 

Hmm, alternatively the change could be from **flow** (the pass after sched1? no).

Let me just look at the .lreg dump's insn 43 vs .sched's, and check whether there's an intermediate dump. The dump list: cse, cse2, combine, flow, sched, lreg, greg, sched2, dbr, jump2. So .flow is after combine (before sched). 

OK, whatever the pass name, the mechanism is clear. The practical lever: prevent the copy from being before the store.

Idea: make the store's base a *different* pseudo that is not r72 — by having the store use `new_var` where new_var is set from r72 *after* the store... circular.

Idea: make the copy `a0 = r72` not exist at all — impossible since the call needs the pointer.

Idea: make the call argument a *different* register value: e.g., pass `(u8 *)s0` where s0 is a `char *` — same.

Hmm, what if we make the call arg `(u8 *)new_var` AND the store base `s0`, with new_var being a *different* pseudo that cse can't merge because it's set from a different expression... e.g.:

```
  char *new_var;
  s0 = a0;
  call1(a0);
  new_var = (char *) s0;
  v0 = 8; store1 (base s0);
  v0 = 0x100000; store2 (base new_var);
  func_80171990((u8 *) s0);
```
That's the base body (w00): the call arg is s0, the store base is new_var. cse merged new_var into r72. So the copy `a0 = r72` is the source for both.

If instead the call arg were `(u8 *)new_var`, the copy source would be the same merged pseudo.

What if new_var is assigned from a *function of* s0 that the compiler keeps as a separate pseudo: e.g., `new_var = (char *)s0;` — merged.

Fundamental: any pointer equal to s0 is cse-merged.

So the only way is to keep the *call arg* from being a copy of the store's base — impossible, since the target passes the same pointer.

=> WALL confirmed. The prior agent's conclusion (sched1-argcopy-hoist) matches.

Now: item 2 needs 20 min (until ~18:29) and 30 tries (have 49). I'll use the remaining time to:
1. Verify the score is 1 across all 3 includers (for the wall evidence).
2. Write notes + the row.
3. Clean the dumps.

Let me check the other two includers (k=1, k=2) with tryinc on w00.

Actually, MATCH requires score 0 on all includers; for a WALL, the best is the lowest lever-free score. Checking the other includers confirms the same score (1) — good evidence.

Let me run tryinc k=1 and k=2.
