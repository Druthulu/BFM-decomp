---
ts: 2026-11-06T16:41:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bZ8D5YP0p6UAQ9t7MGCJ
---
In o1, register 72 doesn't exist at all — only 73. So local-alloc merged 72 into 73 (or cse did). Actually cse1 would rewrite 72's uses to 73? Hmm: the copy is 73 = 72 + $0. Not a copy. So cse can't merge. Local-alloc then ties 73 to 72's qty (combine_regs with both pseudos, ureg=72 dies at insn 11) → same qty → one register. So the plus kept them distinct through cse but local-alloc tied them.

In w1, the copy `73 = 72` was handled by cse (73 → 72 in the EBB) and local-alloc tied differently.

So the key is: keep the arithmetic op (so cse doesn't merge) but make it fold to a move without a pin. The `+ zr` used the $0 pin. Alternatives that produce an arithmetic RTL but zero-cost after combine:

- `self = arg0 + 0;` → cse/expand might fold at expand time (expand_binop with const 0 may return the operand directly, producing a copy). Let me check what RTL s6 produced. Let me dump s6 rtl.

Actually, let's test which variants produce a `plus` in the initial RTL. Check s6, s7, s9 RTL.
