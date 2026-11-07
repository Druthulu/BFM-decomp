---
ts: 2026-11-06T12:06:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TZaaJgmRRidINxwN6qgq
---
v_tail_p1 = 2 (same). Others worse. So the source tail order is best (p1 swaps unk14 and 0x18, still 2).

The store sink is unfixable. It's 05:06. Item 4 started ~04:56. 10 min. I need ~20 min → 05:16.

Let me continue with a few more genuine attempts. Let me try to influence the sched2 priority via a different mechanism. 

Idea: sched2 uses REG_DEAD notes and register pressure. If I add a fake use of v0 after the store... no.

Idea: the li a0 is needed by the jal. sched2 schedules the jal's args. If I could make the jal's a0 setup depend on the store... 

What if the final call's first arg is read from memory that the store wrote? No, it's 0x980.

Hmm. Let me try a few more:
- v_call_ptr: call through a cast `((void(*)(s32,s32))func_8002D4C8)(0x980, 0);` — might change scheduling.
- v_call_2stmts: `func_8002D4C8(0x980, 0);` split into two calls? No.

Let me test v_call_ptr.

Also, let me reconsider: maybe the li a0 is hoisted by sched1 (before reload), not sched2. If I add an insn between the store and the call that's a barrier... 

Actually, let me look at whether the wall is really unavoidable. The sibling's notes say "only the memory clobber works". So yes.

Let me do 2-3 more tries and then write up. Let me test v_call_ptr and a couple of others.

Actually, let me reconsider the whole thing: the score is 2, which is very close. Is it possible that a slightly different v-computation changes the sched such that the store stays? For example, if v's last computation (lui 0xfffd) were scheduled differently. 

Let me try the v if/else with different branch structure (e.g., ternaries). 

Let me test:
- v_tern: `v = (v < 0) ? (unk70 ? 0x40000 : 0x30000) : (unk70 ? -0x40000 : -0x30000);` — a ternary tree. This might change the branch structure but the target has branches. Hmm, gcc might generate the same.

Let me test v_call_ptr and v_tern.

Let me generate.
