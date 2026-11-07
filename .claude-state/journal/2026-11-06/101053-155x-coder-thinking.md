---
ts: 2026-11-06T17:10:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WifGqyQdDERT8rJbPrK6
---
In the lreg dump, insn 564 is `(set (reg:SI 117) (ior (reg:SI 117) 142))` — pseudo 117 is the constant, still a pseudo (not yet allocated to a hard reg) in the lreg dump?! But the greg dump showed `(reg:SI 14 t6)`.

Hmm, the lreg dump shows reg 117 (not hard) because... local-alloc assigned it? The lreg dump's insns show pseudo regs (they're renamed at reload?). Actually local-alloc replaces block-local pseudos with hard regs in the RTL. If it shows 117, then 117 was NOT allocated by local-alloc (maybe it's global or was left).

Wait, the dispositions "Register 117 in 14" appeared in the *greg* dump (global-alloc), not lreg. I mislabeled: the list I printed at line 207+ came from the lreg dump's disposition comments — but those `;; Register X in Y` lines in the lreg dump are the *local* allocation results. Let me recheck: I ran `sed -n '/Function func_801817D0/,/^;; Function/p' $D/n3.i.lreg | grep ";; Register .* in "` — yes, from the lreg dump. And it says "117 in 14" there. But the RTL shows 117 as a pseudo still...

Confusing: maybe the dump prints the dispositions first and then the RTL with pseudo regs for those not allocated... Actually gcc's dump_local_alloc prints `;; Register %d in %d.` for each pseudo with a hard reg, then prints the insns with `regno` replaced. If the RTL shows 117, then 117 was not replaced, contradiction.

Unless the insn 564 shown is from a different function? No.

Hmm, wait: the lreg dump lists "Register 117 in 14" and the RTL at insn 564 shows `(reg:SI 117)`. In gcc 2.7.2's dump_local_alloc, the RTL is printed after `alter_reg`? The insns are printed with `print_rtl` where regs allocated by local-alloc have been renamed to hard regs via `reg_renumber`? Actually local-alloc modifies the insns directly (replacing pseudos with hard regs) only when the pseudo is local; for qty members, it calls `alter_reg` at reload. Hmm, in 2.7.2 local-alloc sets `reg_renumber[regno]` and the RTL keeps pseudos until reload? No — `local_alloc` calls `update_equiv_regs`? Let me not chase.

The key fact: the *final* assembly shows the constant in t6 and the mask in t7. And the target is the reverse.

Let me try more C variants:
- a4: split the mask into two variables.
- Make the constants not hoistable: e.g., write them as `*q2 = 0xE100008E;` (already). The hoisting is sched1's.
- Change the *order* of the packet blocks so the 0x8E constant is materialized at a different time.
- Make the mask's live range longer (assign earlier) — a2/a3 gave 23 (worse but the constant/mask may have swapped?). Let me check a2's diff: 23 vs 21 — maybe it fixed some and broke others.

Let me look at a2's diff.
