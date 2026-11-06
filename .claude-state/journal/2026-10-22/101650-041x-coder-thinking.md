---
ts: 2026-10-22T16:16:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1mY4gZeacfYy3na9gDHm
---
The RTL at cse2:
- insn 29: `(if_then_else (eq:SI (reg 72) (reg 73)))` — reg72 = p, reg73 = it. So the EQ is (p, it) — the opposite of the C's `it == p`! GCC expanded the comparison with the operands swapped.

Interesting: the C is `if (it == p)`. The RTL shows (eq p it). So the expander swapped. Why? In GCC 2.7.2's do_jump for EQ:
```
case EQ:
  ...
  /* If we are comparing a register to zero... */
```
Hmm. Or `fold` canonicalized the tree? Let me look at the .rtl (before passes) to see the original EQ order.

Actually, at insn 29 the EQ is (reg72, reg73) = (p, it). The C tree is (eq it p) = (73, 72). So it was swapped somewhere: maybe `expand_expr` swaps to put the operand with the *lower* reg? Or the `branch_equality` pattern in mips.md has `(match_operand 0 "cmp_op" "")` and the expansion uses `swap_operands` if... 

Let me look at .rtl for the function to see if the swap is there from the start.

If the swap is inherent to the expander (it puts the "first" operand as the one that is NOT a REG_EQUAL/constant?), then to get (it, p) I need the C to be `p == it`? But q14 (p == it) also scored 1 — maybe it produced the same (p, it)? Let me check q14's RTL... or simply test whether the score changes if the comparison operands are in the other order — q14 gave 1, so probably the same. Hmm, but maybe q14 produced (eq it p) and still beq a0,v1? Let me check q14's .s directly: run sc/dt diff on q14.

Actually the diff for q14 (score 1) might be a *different* instruction. Let me check.
