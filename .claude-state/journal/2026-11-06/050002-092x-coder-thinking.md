---
ts: 2026-11-06T12:00:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oPdaPr3vQ2XRTtNMYUj5
---
v_two_s8: `li v1,2` at insn 3 (before sw ra,20). Target has it at insn 5 (after sw ra and lw v0,32). So the s8 li is hoisted too early.

Target: sw ra (3), lw v0 (4), li v1 (5). Mine: li v1 (3), sw ra (4), lw v0 (5). So the scheduler moved the li before sw ra and lw.

This is sched1 ordering. The li v1,2 is independent of sw ra and lw, so sched1 can move it. Target keeps it after the lw. 

Hmm. The barrier doesn't affect the prologue. The `two = 2` is in the first block. The s8 version made the li hoistable to before sw ra.

With s32 two (v_two), the li was at insn 5? Let me check: v_two had `li v0,2` at insn 5 (after lw v1,32). So s32 two kept the order but swapped regs. s8 two fixed regs but hoisted the li.

So there's a tension: s32 keeps order but wrong regs; s8 gets right regs but wrong order.

Let me try other types: u8 (v_two_u8 = 8, so it kept the swap?). Hmm, u8 gave 8 (swap not fixed). s8 fixed the swap. Interesting.

Let me try to fix the s8's li order. The li v1,2 is hoisted before sw ra. Maybe if I add a dependence between two and the prologue... 

Actually, the li v1,2 being at insn 3 vs 5 — sched1 placed it early because it's ready. To delay it, I could make it depend on the lw (p). E.g., `two = 2` after p is loaded. It already is (source order: p = ...; two = 2). But sched1 hoisted it. 

Hmm, the s32 version didn't hoist it (li v0 at 5). Why does s8 hoist? Maybe because the QImode li is cheaper/different.

Let me try `s8 two` but with the store order changed, or with `two` used differently.

Alternatively, try `s8 two` and see if the store position can be fixed. The store sink is still there (score 4 includes the store move). Let me focus: with s8, the remaining issues are (a) li order (1 mismatch) and (b) store position (1 mismatch) = 4 score.

If I can fix both, score 0.

Let me try:
- v_two_s8_store: s8 two + store reorder.
- v_two_s8_dw: s8 two + do-while around the store.
- v_two_s8_late: s8 two + make the li depend on p.

For the li order: maybe `two = (s8)2` after `p = ...` with p used in between. Or `two = 2; ` but insert the p load before. It's already after. sched hoists.

What if I make `two` depend on p? e.g., `two = (p != 0) + 1;`? That adds a compare/set. Hmm, but maybe it produces `sltu` etc. — extra insns.

What if `two = *(s8*)(&D_...)`? No.

Let me try wrapping the two assignment in a do-while (C0535 EBB split) to control sched1 birth order. v_two_s8 + do-while around `two = 2;`.

Let me also try s8 + the store in a do-while.

Let me generate.

Also, the store sink: target sw at 29, mine at 30. With s8, mine's store is at 30 (after li a0,2432). Let me try moving the store to a different position or adding a dependence.

Let me test a batch:
- v_s8_dw_two: s8 + do{two=2;}while(0)
- v_s8_store_dw: s8 + do{store 0x10}while(0)
- v_s8_both_dw
- v_s8_store_first: s8 + reorder store before the li? (can't control)
- v_s8_unk2_first: s8 + unk2 store before p load

Let me test.
