---
ts: 2026-11-06T11:44:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Jt5pZvpCdHg5XpLvkaLX
---
d1 (barrier removed, launder kept): 1 load (`lhu a0,174(s0)`) reused. So the barrier is the reload cause. Confirmed.

Now, the target's second load is the reload after the barrier. Real C can't do it without a memory clobber.

Hmm, but wait — what about the launder being an asm that cse treats specially? The launder is `asm("" : "=r"(tmp) : "0"(tmp))` — an ASM_OPERANDS with a register output. Does cse's hash of an ASM_OPERANDS set do_not_record? Line 1967/1973. Let me look at hash_rtx's ASM_OPERANDS case.

If cse treats the asm as "do_not_record", it wouldn't invalidate memory either.

OK. Let me step back and consider the actual semantics of the original C: why would the original author write the barrier? Because without it, the compiler merges the loads and the match fails. So the original function's *true* C (pre-lever) must have had something that produced 2 loads naturally — maybe the original C read the value through a *different expression* that the author simplified.

Look at the two reads: the first is `bb = *(u16 *)(p + 0xAE)`, the second `*(u16 *)(p + 0xAE)` inside ratan2 args. If the original C had, say, a struct member for the first and a plain deref for the second, gcc 2.7.2 cse might not equate them if the MEM_IN_STRUCT flags differ... but cse's hash is on the address, and `lookup` uses rtx_equal_p on the full MEM expression. Does rtx_equal_p compare MEM_IN_STRUCT_P? In rtl.c/rtx_equal_p: for MEM, it compares... let me check. In gcc 2.7.2, `rtx_equal_p` for MEM: it compares XEXP(x,0) and the mode, and possibly `MEM_IN_STRUCT_P`? Let me look at rtl.c or rtlanal.c.

Actually `exp_equiv_p` in cse.c handles MEM specially. Let me look.
