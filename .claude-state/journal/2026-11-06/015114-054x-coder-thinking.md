---
ts: 2026-11-06T08:51:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Hg5CN3DZ4QxkiBeGFdFt
---
Key: `find_free_reg` builds `used` from `regs_live_at[ins]` for ins in [birth, death), plus call_used_reg_set if the qty crosses calls. Then it picks the first free register in `reg_class_contents[class]` order (i.e., lowest hard reg number first, but class order). For GR_REGS on mips, the order is v0,v1,a0,a1,a2,a3,t0..t7,s0..s7? Actually reg_class_contents for GR_REGS is a bitmask; `find_free_reg` iterates `i` from 0 to FIRST_PSEUDO_REGISTER and checks `TEST_HARD_REG_BIT(used, i)` and class membership. So the order is ascending hard reg number: v0(2), v1(3), a0(4), a1(5), a2(6), a3(7), t0(8)...

So allocation by priority; first free ascending. Confirmed.

Now, `used` includes regs_live_at for insns [birth, death). Note: `dead_index` exclusive! So a pseudo dying at insn D conflicts with regs live at insns birth..D-1. If t4 is born at insn 56 and r84 dies at 56, then r84 is not live at insn 56 for t4's check? `regs_live_at[56]` — r84 is live at the start of insn 56? The flow computes regs_live_at per insn; a reg dying in insn 56 is live at 56 (it's used by 56) → yes, r84 would be in regs_live_at[56]. But the loop goes ins < dead_index where dead_index is t4's death (59), born 56: checks 56,57,58. regs_live_at[56] includes r84 if it's live at 56. In w1, r84 is live at insn 56 (used by the load) → so t4 should conflict with v0! Yet w1's t4 got v0. Contradiction... unless regs_live_at excludes the insn where r84 dies? Let's check flow.c's regs_live_at computation: it's built in `life_analysis` scanning backward; `regs_live_at[insn]` might be the set live *before* the insn or after. If it's live after the insn, then r84 dying at 56 isn't in regs_live_at[56]... Hmm, but then in the off-keepalive variant, r84 lives past 56 so it's in regs_live_at[56..], blocking v0 for t4.

In w1, r84's last use is insn 56 (the t4 load). If regs_live_at[56] = live after 56, r84 is dead → no conflict → t4 gets v0. That matches! And in the keepalive variant, r84 is live after 56 (the asm at 61) → conflict → t4 gets v1. 

So for real C, we need r84 live after the t4 load's insn (i.e., used by a later insn) — impossible without a later instruction using it.

Hmm, wait. Alternatively t4's birth could be BEFORE r84's death if the fifth load's address computation is emitted such that r84 is used at insn 56 and t4 is born at 55? No.

Alternatively, give t4 a *copy suggestion* for v1! `find_free_reg` in the first pass uses `qty_min_class` with just_try_suggested=0, so no suggestions. Suggestions are used elsewhere (in global-alloc). Hmm, in this 2.7.2 local-alloc there's a suggestion mechanism? `qty_phys_copy_sugg` appears. Let me look at where it's used — maybe before the main loop there's a pass that tries suggested regs. Let me search.
