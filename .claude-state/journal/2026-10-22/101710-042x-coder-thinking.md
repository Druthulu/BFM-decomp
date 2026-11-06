---
ts: 2026-10-22T16:17:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Py2UC6AT8ExnFRlRiwLM
---
Hmm, the .rtl grep shows an `ne` at line 38 but not the eq. Let me print the rtl region fully. The `eq` might be there but my grep pattern missed due to line wrapping. Let me print the rtl body.

Wait, the .rtl shows `(if_then_else (ne:SI (reg 73) (reg 72)))` for the second compare (`it != p`) — order (it, p), matching the C. So the RTL preserves source order for `ne`. For the first compare (`it == p`), cse2 shows `(eq (72) (73))` = (p, it) — swapped. That suggests the swap happened during expansion of the EQ (not NE). In GCC 2.7.2's do_jump:
```
case EQ:
  ...
  if (GET_CODE (op1) == CONST_INT ...)
```
Hmm, but maybe there's a `swap_operands` call in `expand_cond`? Or in `do_jump` for EQ:
```
    case EQ:
      ...
      /* Put the constant on the right? */
```
Both are regs.

Wait — maybe the tree got canonicalized: `if (it == p)` where `it` and `p` are locals — fold-const might canonicalize `(eq a b)` to put the *cheaper* operand first? Hmm.

Let me check the .rtl for the first compare. Print lines n..n+60 fully.
