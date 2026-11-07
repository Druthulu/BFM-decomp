---
ts: 2026-11-06T17:13:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Pbbt1zJrsVwAI4yjd6g1
---
"Register dispositions" without a "regs to allocate" line means the greg dump shows only local-alloc's dispositions (no global regs). So ALL allocation is local (one block). The mask 87 → 15 (t7), the constant 117 → 14 (t6).

So local-alloc's priority decided. Let me get the actual priority ordering: local-alloc sorts `qty_order` by qty_compare_1 = pri2 - pri1 where pri = floor_log2(n_refs)*n_refs*size/(death-birth). Let me compute for 87 and 117 using the lreg dump's insn numbers (UIDs):

- 87: birth 571, death = last and's insn ~1384. n_refs = 13. size 4.
  floor_log2(13) = 3. 3*13*4 = 156. 156/(1384-571=813) = 0.19.
- 117: birth 563, death 664. n_refs = 2. floor_log2(2)=1. 1*2*4=8. 8/101 = 0.079.

So 87 (0.19) > 117 (0.079) → 87 should be allocated FIRST and get the lowest free reg. Yet 87 got 15 and 117 got 14. That means when 87 was allocated, t6 (14) was already taken by a *live* qty (117 or another). But if 87 is allocated first (higher priority), 117 isn't allocated yet.

Unless the lreg dump's insn numbers are not the UIDs used (uid_cuid). The dump shows insn numbers (the `(insn N ...)`), and qty_birth/death use those.

Hmm, but the REG_DEAD of 117 is at insn 664, and 87's birth at 571 — 117 is live at 571 (563<571<664) → they conflict. With 87 allocated first, it takes the lowest free reg. At 87's allocation, the free regs depend on the conflict graph. 87 conflicts with a LOT (it's live 571-1384 and used across the tail); the other long-lived pointers occupy s-regs and t-regs. The lowest free might be 14 (t6) if it's free... but 117 will later need a reg that doesn't conflict with 87, so it'd take 15 (t7). That's the TARGET's outcome!

But the actual outcome is 87→15, 117→14. So 87 must have been allocated AFTER 117, i.e., pri(117) > pri(87).

My computed priors say otherwise. Maybe qty_n_refs for the mask is not 13. Let me get the exact stats: the lreg summary line for 87: "Register 87 used 13 times across 179 insns". "179 insns" is the span (death-birth) = 179! Not 813. So the lreg's span for 87 is 179 (from insn ~16 to 195). Hmm, but the RTL shows the ands at insns 1063-1384 — those are different numbering? The insn numbers in the dump are UIDs and they can be large (the function has ~1400 RTL insns pre-allocation; the final has 215 machine insns). The "across 179 insns" counts *machine* insns? Or the span in UIDs?

The lreg summary's "used N times across M insns" — M is likely `regno_last_uid - regno_first_uid` in UID units. For 87: birth UID ~571, death ~1384 → 813. But it says 179. So the mask's UIDs must be 571→750? Hmm.

Wait, maybe the mask's def at 571 is followed by the ands at 1063+... no, the ands I grepped are at lines 1063+ of the *dump file*, not insn numbers! I used grep -n on the dump output (line numbers in the file), not insn numbers. Oops. The actual insn numbers are inside the text.

Let me get the real insn numbers of the ands using the mask: search for "reg/v:SI 87" with the insn line.
