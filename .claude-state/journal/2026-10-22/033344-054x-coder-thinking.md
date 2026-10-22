---
ts: 2026-10-22T09:33:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_lEahZTjjPZUS9Zq6Vadf
---
Reload.c has commutative-operand swapping (line 3273: "If insn is commutative (it's safe to exchange a certain pair of operands)"). This is the mechanism!

In reload, when an insn's operand needs a reload and the insn is commutative, reload may swap the operands so the reload happens in the other operand. Also, reload has the rule about "reload_in_progress" and the order of operands.

So the operand order in the final asm is decided by reload — and specifically by which operand needed reloading and the order in which reload processes operands.

In our case: the insn is `(set (reg 113) (mem/s:HI (plus (symbol_ref) (reg 118))))` — a MEM with an address PLUS. The address's operands: symbol_ref (needs reload into a reg: lui+addiu) and reg 118.

In reload, for a MEM address, the address is decomposed; the "plus" with a symbol becomes LO_SUM/HIGH... The tree (plus (symbol) (reg)) → reload turns the symbol into a register (a1) → (plus (reg a1) (reg 118)) → "addu v0,a1,v0"? But ours is "addu v0,v0,a1"!

Hmm. So in ours, the reload put the symbol in the SECOND position. Why? Because reload.c has a rule: for a commutative operation where one operand is a MEM/constant needing a reload, the operand order gets swapped so the reload is in the second operand (to preserve the "base + index" convention?).

Let me look at reload.c around line 3273 and the code that decides to swap.

Key question for cracking: how to get the symbol into the FIRST position?

In the target, the pointer was in a1 in the first position, and the pointer came from a REG (pseudo), not a symbol_ref! Because if it were a symbol_ref, reload would handle it as a constant address.

Hmm, in the target: "lui a1; addiu a1,a1,0" — a1 = the symbol, materialized by reload. Then "addu v0,a1,v0" — so the pointer is in the first operand as a REG.

In ours: "lui a1; addiu a1,a1,0" — also a1 = the symbol materialized by reload, but placed second: "addu v0,v0,a1".

Same materialization, different position! So the position is decided by the tree order after reload's processing, i.e. the ORIGINAL tree order: in ours the tree was (plus (symbol) (reg 118)) → symbol first → but the output has the symbol SECOND. So reload SWAPPED them. In the target, the tree must have been (plus (reg ptr) (reg 118)) where ptr is a pseudo — no swap needed (the pseudo is already a reg; reload assigned it to a1).

So the target's pointer was a pseudo reg at reload time.

Now — why is our symbol_ref swapped to second by reload? Let me read reload.c's commutative handling (line 3273+) and the code that swaps when an operand is a constant.

Let me read reload.c around 3200-3320.
