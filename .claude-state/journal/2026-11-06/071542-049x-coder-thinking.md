---
ts: 2026-11-06T14:15:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DYsHN61vsGiDLtFIOD9i
---
Now let me create a batch of variants and score them all.

v1: `dst = src + n;` -> `dst = src + (n + i);`? Hmm, `src + n + i` where i=0. Let me use `dst = src + n + i;`. Pointer arithmetic: src + n + i = src + (n+i). Since i=0, same. 

v2: `dst++;` -> `dst += 1;`
v3: `dst++;` -> `dst = dst + 1;`
v4: reorder increments: `dst++;\n                            i++;\n                            src++;` -> `i++;\n                            dst++;\n                            src++;`
v5: `i++;` -> `i = i + 1;`
v6: combine the two increments: `dst++;\n i++;\n src++;` -> `dst++, i++, src++;`  (comma expression)
v7: move i++ before the body: no.

Let me also try the array-index version:
v8: replace `px = *src;` ... `*dst = out;` with `px = src[i - i];`? no.

Let me first batch v1-v6.

Actually, let me reconsider v1 more carefully. `dst = src + n + i;` — the addition order: (src + n) + i. The target has `sll $2,$12,1; addu $11,$9,$2` = src + n*2. If combine folds i=0, we get the same. But does combine know i is 0? At the point of `dst = src+n+i`, i was just set to 0 in the same block. combine works on insns; the REG_EQUAL note on i's set says i == 0. combine's `try_combine` can use `reg_last_set_value`? Hmm, actually combine only combines within a 3-insn window and uses `subst` from the SET_SRC of a previous insn. There's a function `try_combine` that calls `subst` on known values. Also `combine_instructions` uses `reg_last_set_value`? I recall `combine.c` has `reg_last_set_value` in `combine_instructions`? Hmm, that's in cse.

Actually, `combine` does do "known value" substitution via `reg_last_set_value` and `reg_last_set_table_tick`? Let me grep combine.c.

Actually, jump.c's `no-op move`/`delete_noop`? There's also `cse` after loop but before flow. Hmm, the flow is after cse2. So cse2 runs before flow; cse2 could propagate i=0 and fold. Wait, if cse2 folds `src+n+i` to `src+n`, then flow wouldn't see the i ref. Order: jump, cse, loop, cse2, flow. So cse2 runs BEFORE flow. Damn. So cse2 would constant-propagate i=0 and eliminate the i ref before flow counts it.

Unless cse doesn't propagate because i is in a loop / the value is set outside. Hmm. cse does track constants. `i = 0` then `src + n + i` — cse would replace i with 0 and fold. So flow sees no i ref. Bad.

OK so any redundant use of i that cse can fold won't help, because cse runs before flow.

But a use of i that cse CANNOT fold (because i's value isn't a known constant) would remain and add an instruction. Unless combine removes it later (combine runs after flow). So: we need a use of i that cse2 can't fold but combine can eliminate. That's a narrow window.

Hmm, alternatively, the extra ref could come from a use that doesn't generate an instruction at all — e.g., an addressing mode or an existing operand.

Wait — what about `i` used in the loop condition twice in one insn? Like `while (i < n && i >= 0)`? cse/fold might simplify `i>=0` (unknown). It'd emit an extra compare.

What about using i in the store: `dst[i - i] = out`? cse folds.

Hmm.

New angle: reduce dst's refs. If dst has 10 refs, i wins. How to reduce dst by one without changing code?

dst's RTL: 
- insn 318 `(set reg162 (plus reg161 reg170))` — in block 13 (depth 1)
- insn 391 `(set (mem:HI (reg162)) ...)` — block 17
- insn 394 `(set reg162 (plus reg162 2))` — block 17 (increment, extra ref)

If I can eliminate the increment's REG_INC extra ref, dst loses loop_depth refs. `dst++` vs `dst += 1`: both are increments recognized by flow? The REG_INC note is set by... let me check where REG_INC is set. In flow.c, the code at 2300 is in a function that optimizes `x = x + 1` patterns? Let me look at the function name around 2280.

Actually line 2300 is inside `mark_used_regs`? Let me look at the enclosing function.
