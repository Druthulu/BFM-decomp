---
ts: 2026-11-06T18:20:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OAPgrpr8QmtFFnuAX0Co
---
At insn 32: REG_DEAD notes first (none for 72 at 32), then mark_reg_store(76) → records conflict with currently live. 72 is live (from block start? 72's live range spans blocks; at block A's start 72 is live). So 76 should conflict with 72. But dump says no.

Unless 72 is NOT live at block A's start — hmm, block A is the `if (v0<a2)` true arm. 72 (a0 copy) is live at block A start (used at insn 32). Yes.

Wait, maybe I misread the conflict list. ";; 72 conflicts: 72 74 75 2 5 6 29" and ";; 76 conflicts: 75 76 29". Hmm, 76's conflicts don't include 72 nor hard regs 2,5,6. But 76 is born in block A where 72, 74, 75... are live.

Unless the dump's conflict lines are printed per allocno i and CONFLICTP(i,j) is asymmetric... they print both directions.

Hmm, is 76 maybe a different allocno? Let's check: maybe allocno 76 is the QI temp r77's... no.

Wait, maybe block A doesn't start with 72 live: block A = insn 29-34. 72 is used at insn 32. It's live-in. Hmm.

Unless flow (before global-alloc) found 72 dead in block A because... no, it's used.

Let me just look at the .lreg dump (after local-alloc) and the final .s. Actually, maybe I should stop the deep analysis: the empirical score is 3 and the mechanism is clear enough (preference for a0 via expand_preferences from the param copy). 

Practical lever candidates to remove the a0 preference:
1. Make the loads use a hard reg directly (no param copy 72): If the param a0 is used exactly once, expand uses the hard reg directly. But a0 is used 3 times. What if the source loads the pointer into a local FIRST and then uses that? e.g., `void *p = a0;` → that's exactly the copy 72. Hmm.

What if we make the source reference `a0` only ONCE by loading unkCC once before the branches? Then a0 used once, no copy; but structure changes (one load, not three) → wrong.

2. Make 72 not preferred for $4: if 72 conflicts with something in $4... 

3. Change the ORDER: if 76 were allocated BEFORE 72 (higher priority), then 76 would take $3 (lowest free) and 72 would get $4. Order is 75 76 72 74 — 76 is already before 72! And 76 has preference 4 → takes $4. If we remove the preference, 76 takes... find_reg for 76 with no pref: it tries call-clobbered regs in order $2,$3,... $2 is taken by 75, so $3 → MATCH. And 72 then takes $4. 

So the ONLY thing to change: kill 76's preference for 4 (which comes from 72's preference via expand_preferences at insn 32: dest 76, REG_DEAD 72).

expand_preferences fires only when the REG_DEAD at that insn is a *different allocno* and no conflict. Note: `if (XEXP (link, 0) == SET_SRC (set))` merge copy prefs; always merge normal prefs.

To stop it: make 76 and 72 conflict. How? Make 72 live *after* 76 is born such that they overlap... they already overlap. Unless the conflict isn't recorded because at insn 32 the REG_DEAD of 72 is present! Is there a REG_DEAD for 72 at insn 32? 72 is used at insns 32, 40, 53. It dies at 53. So no.

Hmm, wait. Let me recheck: maybe 72's *last* use is insn 32 in the RTL because jump2/cse... no, the .rtl dump clearly shows insn 40 and 53 using 72.

I wonder if the conflict list is right: maybe 72 and 76 DO conflict but the dump line for 76 omits 72 because... CONFLICTP(i,j) uses allocno_row_words and bit index. Hmm.

Let me look at the .greg dump again fully (the top part) and the .lreg, to see. Actually, let me look at the .lreg dump: local-alloc's own table might show what happened. But since 76 is global, local-alloc doesn't touch it.

Hmm, actually let me reconsider: maybe 76's "preferences: 4" comes from a different source: prune_preferences? No, it only removes.

Let me test the hypothesis directly: make the load base a different variable such that 72 doesn't exist... 

Alternative plan: change `a0`'s C type/usage so that the param copy goes to a *different* pseudo that isn't a global allocno... 

Hmm, what if we use the param a0 directly in the loads but with different types, e.g., `((Unkstruct_80184B70 *)a0)->unkCC` — that's what we have.

What if we add `void *p = a0;` at the top and use p? Then the RTL is the same (72 is the param copy; p is the same copy).

What if instead we do `s32 p = (s32)a0;`? Same copy.

OK here's another idea: **make the value loaded into 76 be used in a way that makes 72 and 76 conflict**. If 76's live range were extended to cover an earlier use of 72... e.g., if 76 were live-in to block A (used before being set)? No.

**Idea: use `v1` as the base of a later load before the store**, i.e., reload through v1: `v1 = a0->unkCC; ... *(s32*)(v1+0xB0) = v0`. If in a block we use v1 before it's set — no.

**Idea: two variables.** Give the three loads different destination variables, then merge: e.g., in each branch `v1 = a0->unkCC;` where v1 is one variable → same pseudo (GCC merges uses of the same variable across blocks into one pseudo? Actually no! Each assignment to the same variable in different blocks is the SAME pseudo-register in GCC — yes, a variable maps to one pseudo).

Hmm, what if we declare a separate variable per branch and then use a single one? The store needs one variable; we'd need a phi-like merge → gcc would need a copy at the join (extra move).

**Idea: make the store use a0-derived pointer instead of v1.** What if the final store is `*(s32 *)(v1 + 0xB0) = v0` — target. Fine.

**Idea: exploit prune_preferences' `reg_preferred_class`.** Not C-controllable.

**Idea: change the param copy so it prefers a different reg?** The copy `(set 72 (reg 4 a0))` always prefers $4.

**Idea: make 76's allocno priority higher/lower so it's allocated before/after?** It's already before 72 and takes $4 due to pref.

**Idea: make $4 unavailable for 76 by making a0 live in 76's range.** a0 (hard reg 4) dies at insn 4 (the param copy). If the source used a0 directly (no copy), a0 would be live until the last load, and hard reg 4 would conflict with 76 → pref 4 pruned → 76 takes $3. How to avoid the param copy? In GCC 2.7.2's function.c, the copy is made when the parameter is used more than once? Let me check assign_parms.

Actually I recall in GCC 2.7.2 function.c:
```
      /* If the parameter is passed in a register and is used more than once, copy it to a pseudo.  */
      if (reg_parm_stack_space ... )
```
Let me grep.
