---
ts: 2026-11-06T20:51:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_S7uFBZkhnyYupGYt4PX7
---
Not relevant.

Let me take a totally different approach to find the deleter: use `--try --keep` and check the .combine dump vs the .cse2 dump of the same body — we already know cse2 has it and combine doesn't. So it's combine.

Hmm, wait — maybe it IS combine's normal `try_combine` with i2=92, i3=101, and `added_sets_2 = !dead_or_set_p(i3, i2dest)`. If `dead_or_set_p` returns TRUE (87 dies in i3), then added_sets_2=0 and the copy is deleted after substitution. Why would 87 "die" in i3? `dead_or_set_p` checks `find_reg_note (insn, REG_DEAD, reg)` — but the RTL after cse2 has REG_DEAD notes only for the last use. The last use of 87 is... near the end (`func_80188650((void*)ent)` uses it). So 87 dies there, not at 101.

Unless combine processed i3 = the LAST use first (combine iterates forward, but `combine_instructions` may go backwards for the last insn?). Actually, `combine_instructions` iterates `for (insn = f; insn; insn = NEXT_INSN (insn))` and for each insn tries `try_combine (insn, prev, prevprev)`. So i3=101 first, i2=92. At that point, 87 is used later, so added_sets_2=1 and the merged insn should set 87.

But the merged insn 101 in the dump doesn't set 87... 

Hmm, unless combine's `subst` with `added_sets_2` creates a PARALLEL and then `recog` fails, and combine undoes... no, the copy is deleted.

Hold on — maybe the copy deletion happened at i3 = the LAST use (the call `func_80188650(ent)`), where 87 IS dead (after the call). Combine merges the copy into the call arg? The call uses a0 = 87. Combine could merge `87 = 72` into the call's arg setup (`a0 = 87`) — that's the insn before the call. Hmm, but then the other uses would still use 87.

Wait — unless the ORDER is: combine processes i3 = the last use first because... no.

I'm going too deep. Let me instead test empirically: if I make `ent` used in a way that its LAST use is before other uses... no.

Alternative empirical test: what if `ent` is used only ONCE (e.g., only the final call)? Then combine would merge it (score same?). Not helpful.

Let me try: make `ent` used in the first store AND make the copy's source a0 *modified* after the copy (so combine can't substitute). But a0 can't be modified without changing semantics... Actually, we CAN modify the parameter variable a0 in C! The parameter is a local copy. If we write `a0 = (void *)((s32)a0);` — a self-assignment, folded. If we write `a0 = (void *)0;` after the copy, the code changes.

Hmm, what if we use a *different* source variable: e.g., 
```
void *aa = a0;      // copy 1
...
ent = (s32)aa;      // copy 2
```
combine would propagate aa too.

OK. Let me try one specific thing: does combine merge the copy because `ent`'s uses are memory addresses (combinable patterns)? What if ent is used in a non-combinable context, e.g., passed to a function? The last use IS a call arg.

Let me try a completely different structure: use `ent` only in the stores, and the final call uses `a0` directly:
```
func_80188650(a0);
```
Then ent's last use is the last store; the call uses the parameter (s0). The target's call uses a0 (=ent). Hmm, but if ent is propagated to a0's pseudo (s0), the call would need a move. That's the baseline.

OK. I'll stop here — the wall stands. But let me use the remaining time to try 3-4 more variants that might exploit the combine condition:

1. Make `ent` a *volatile*? no.
2. Make the copy's source not a register but a memory ref: `ent = (s32)(*(void **)&a0);`? stack.
3. Make `ent` REG_USERVAR_P false? It's a user var, so REG_USERVAR_P is set — that might actually PREVENT some merges.

Hmm, actually: `REG_USERVAR_P (i2dest)` — for `ent`, a user variable, the pseudo has REG_USERVAR_P set. In the condition at 1561/1764/1830, `! REG_USERVAR_P` is required for the mode-change case. Not our case.

Let me look at line 2306: `if (! added_sets_2 && newi2pat == 0 && ! i2dest_in_i2src)` — hmm.

I'll accept the wall. Let me now check the time and write the final artifacts.

Time check: ~13:50. Need 13:58. Let me do a couple more scored variants (genuinely different), then finish.

Actually, let me reconsider: maybe I can make the copy survive by making `ent`'s uses NOT all combinable. Combine merges the copy into i3 only if it can substitute. If the FIRST use is a call argument (not a plain set), combine can't merge. In the target, the first use is a store (mem). Hmm.

What if we reorder the statements so the first use of ent is the final call? No, the call is last.

OK, let me just do 2-3 more variants for time and then wrap up.

Actually, a thought: what if we make `ent` used in a *conditional* first (e.g., `if (ent)`) — adds a branch.

Let me try:
vAQ: `s32 ent = (s32)a0;` and the first use is a scalar compare? adds a branch.
vAR: `ent` assigned from a0 inside the existing do-while's first statement, with the rest after.

Let me instead spend the time verifying everything and writing the final log. The 20-min mark will arrive soon.

Let me check the time and the results.tsv state, then append item 4's row at ~13:58.

Actually, I can write the results row now (13:50) and then continue a bit; the row's timing isn't checked. But honesty: the notes say end 13:58. Let me do a few more tries until ~13:58.

Let me try 4 more variants now.
