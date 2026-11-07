---
ts: 2026-11-06T20:11:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ujs9A2jEdY4OPqx4KA1u
---
So func_80180254 is at line 11144 and is followed by only these three loops. But its insns are numbered 60-149, 223-249, 459-493? That means insn UIDs are not contiguous per function — the dump file is per-function and UIDs restart? No...

Wait — maybe the function order in the dump is not source order and UIDs are assigned as the function is expanded. Actually, RTL insn UIDs are assigned by `get_insns` counter that resets per function? In gcc, `insn_uid` is a global counter that increments per insn across the whole compilation, but `cur_insn_uid` resets? There is `INSN_UID` global `cur_insn_uid` reset in `init_rtl`? I believe UIDs restart at 1 for each function (cur_insn_uid = 1 in `rest_of_compilation`). Yes! `init_rtl` / `rest_of_compilation` sets `cur_insn_uid = 1`. So each function's insns are numbered from ~1.

Then our function has three loops: 459-493 (9 insns), 223-249 (7), 60-149 (28). But wait, in the vA dump the 28-insn loop section showed "Insn 96: regno 90 (life 1) moved to 529" and "Insn 136: regno 97 (life 1) not desirable", and bivs initialized at insn 55/58/52 — those are the case-2 loop (p, off, i). And the -1024? It's not listed. Hmm, but 28 real insns matches the loop body.

And the "9 real insns" loop 459-493 is the final `for (i=0;i<5;i++)` loop. The "7 real insns" 223-249 is case 5's do-while.

But wait, insn numbers 459-493 > 223-249 > 60-149, and the loops are listed in descending order — the .loop dump prints loops in the order `loop_optimize` processes them, which is reverse order of the function's insn list (loops found from the end backwards). OK.

So the case-2 loop is 60-149 (28 real insns) and the -1024 constant... insn 96 is "moved to 529" with regno 90. Let me verify insn 96 is the -1024 store. In vA's final code, the -1024 was hoisted, so yes, some constant was hoisted: "Insn 96: regno 90 (life 1), move-insn savings 1 moved to 529". That's likely the -1024 (or the -146?). Insn 136 was "regno 97 const=-146, not desirable". So insn 96 = -1024 constant (reg 90). Confirmed: it was moved.

insn_count = 28 real insns. threshold*(savings=1)*(lifetime=1) = threshold. So hoist iff threshold >= 28.

threshold = (loop_has_call ? 1 : 2) * (1 + n_non_fixed_regs).

Without pin: hoist happened → threshold >= 28. With pin: no hoist → threshold < 28. Since difference is 1, n_non_fixed_regs without pin = 27 and with pin = 26 (so threshold 28 vs 27). So n_non_fixed_regs = 27 lever-free.

Now in vD, I added a dead store; the dump shows the loop still has 28 real insns (same!), meaning the dead store was deleted before loop.c. Let me check vD's loop section insn count: the 28-insn loop for vD? Let me grep. If still 28, cse1 deleted the dead store.

So to raise insn_count I need an insn that survives cse1 but is deleted after loop.c. What does cse1 delete? `delete_trivially_dead_insns`? Let me check cse.c.
