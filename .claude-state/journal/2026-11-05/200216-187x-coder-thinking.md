---
ts: 2026-11-06T03:02:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NtdI9ryVHlIe3WxiFocU
---
s1 = arg0 (the parameter). s0 = the table pointer. So both unk1C accesses use arg0 (s1). Fine.

Hmm. So the original C used arg0 for both. And cse forwarded in our build.

Wait — maybe the original had the two statements separated by a *label* that is the target of the `bnez` at 205c! Look: the bnez at 205c targets 20ac (the final store). Not between.

What about the `beq` at 206c targeting 2094 (the store) — the store is the label's target.

Hmm, what if the original C's `if (unk6 != 0xFF)` loop guard and the store were arranged so the store is at the label (2094) and the load after — same as now.

Let me reconsider the possibility that cse's forwarding was prevented by the store being in a different EBB due to a label at 2094. Wait: the EBB boundary is at 2094 (a label and a branch target). cse processes each EBB separately; the store and load are both in the EBB starting at 2094. Forwarding within an EBB is exactly what cse does. Hmm.

Unless the EBB is split by a NOTE_INSN_LOOP_END at 2094? Notes don't split EBBs.

Hmm, let me look at the actual cse code to see when it forwards a store to a load. In cse.c, the memory table records the store's value with the address; a later load with the same address is replaced. But there's a condition: `cse_insn` for a load checks the table entry's `REG_EQUAL`? Actually, cse's store-to-load forwarding happens via `find_best_addr`? Hmm.

Let me look at whether the forwarding might be done by `flow`'s "store motion"? No.

Given the time (item 3 ~35 min), and that i2 got score 1 with a real move (dead-reset cse-breaker), maybe I can refine it to remove the extra store. Ideas:
1. Make the dead-reset store a `sh` to a u16 local that is later... still an insn.
2. Put the dead-reset store in a place where it gets combined with another store: e.g., reset `flag` and then the *existing* code stores to flag? No.
3. Use a store to a *pseudo* that is memory-resident... no.
4. Use a store to a stack slot that is dead AND flow deletes it. Let me check whether flow deletes dead stores to stack slots: the first store in nopin (to unk1C, a struct member) was deleted by some pass. Which pass? If it's cse's store-to-store (dead store to the same address overwritten later), then flow doesn't delete memory stores. Let me check which pass deleted insn 178 in nopin: the .cse dump has it, .cse2 has it, .combine doesn't. Between cse2 and combine there's a jump pass and loop? Let me check the toplev order: after cse2 → jump_optimize → loop? → combine. Hmm, actually the order is: cse1 (2859-2870), loop (2900), cse2 (2923-2929), then "jump threading" (2937), then... let me look at what's between cse2 and combine in toplev.

If the pass is `combine` (store-to-store), then combine deleted the first store because the second store overwrites it. Our `flag = 0` store isn't overwritten, so it survives.

Could we make the flag store overwritten by a store that is *already in the target*? The target's stores are to unk1C (28) and the stack (sp10 via GTE, flag via gte_stflg — before). After our region, func_801820E4 is called (a call clobbers memory, but that's after).

What if we place the dead-reset store to `flag` and then the *decrement's store* to unk1C... different address.

Hmm, what if the dead reset is a store to `sp10[0]` and later the *same* store appears? no.

5. Use a store whose address cse considers aliasing unk1C but which is deleted because it's a *store of a value already in memory* (redundant store): e.g., `flag = flag;` — cse might delete it (store of the same value). But j8 (flag = flag) didn't break cse (105). So cse deleted the redundant store before it could invalidate? Or it didn't invalidate because the value is unchanged? Actually, cse processes the store: it may first delete it as redundant (same value) and thus not invalidate. Hmm.

What about `flag = (s32)flag;`? same.

6. Use `sp10[0] = flag;` (a store of a value loaded from another memory location)? It would survive.

7. Make the dead store be to a *local that is later read by the existing code*, so it's not dead: e.g., store to flag, and flag is read... the condition uses flag before. Not after.

8. What if we insert the cse-breaker *before* the first store instead of between? A memory store before `unk1C = unkDC` wouldn't prevent the forwarding between the store and the load. ✗

9. What if the cse-breaker is the *load* of a different address that aliases? Loads don't invalidate.

Hmm. Let me look at what pass deletes the dead store and see if there's a way. Let me check the toplev order quickly.
