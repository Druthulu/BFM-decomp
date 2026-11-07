---
ts: 2026-11-06T11:10:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F76IgeAsylJ3cHgL0DcN
---
Items 1 and 2 have no asm at all (2 !FAKE do-whiles each). Items 3 and 4 have only symbol-name asm-label aliases.

Now let me write the results rows. I'll rewrite results.tsv with all four MATCH rows.

Tries counts (scored candidates):
- item 1: orig, nopin, nobar, win0, v_param, v_cast, v_dw, v_dw2, v_dw4, v_or, v_ptr, v_ref3, v_ref4, v_bar, v_bar2, v_addr, v_addr3, v_addr4, v_addr5, v_dw5, v_dw6 (21) + 36 generated (p_all, p_or, 6 p_, 12 d_, 12 e_ = 32... let me count: p_all, p_or = 2; 6 p_; 12 d_; 12 e_ = 32) + n1,n2,n3 = 3 → 56.
- item 2: orig, base, w_dw, w_dw6, w_bar, w_v1late, w_v1dw, w_split, w_split2, w_lit (10) + 36 generated (q_all, q_or, 6 q_, 12 r_, 12 s_ = 32) + m1 = 43.
- item 3: orig, base, v_sa (3) + x_dwbody, x_dwcall, x_dwafter, x_for, x_while, x_nfirst, x_ntern, x_nvar, x_ndw, x_ns16 (10) + y_else, y_not, y_cont, y_preinc, y_hcall (5) + z_ifiw, z_ifwi, z_iifw, z_iwif, z_nocnt, z_whileif, z_wifi, z_wiif, z_i32 (9) + z_nu16, z_bound, z_m, z_m2 (4) + x_dwbody/x_dwcall/x_dwafter rescored (3) + v_win, v_direct, v_win2 (3) = ~37.
- item 4: orig, base, v_sa (3) + 16 x_/z_ = 19 + win = 20.

Let me write the rows. The evidence for MATCH rows: the moves.

Format: `dir file func kinds result best tries wall evidence` with wall = "-".

Evidence strings:
- item 1: "param-direct a0 (pin gone); do-while around the unkC4 load + empty do-while after the unk58 store (sched1 keeps sw 88 before the RMW); barrier dropped".
- item 2: "same as func_8018966C plus v1 = 0x4000 moved after the RMW (lreg gives v1 $3 not $4)".
- item 3: "n s16 (cross-jump copy survives), empty do-while after the call (reorg fills beqz slot from target), D_801151D0 as 1-field struct alias (MEM_IN_STRUCT store not hoisted)".
- item 4: "same as func_80187EA0: n s16, empty do-while after the call, D_801151D0 struct alias".

Let me rewrite results.tsv.
