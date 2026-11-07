---
ts: 2026-11-06T21:47:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_a1eGfA9iHzZcriTDS670
---
Line 17: "launder | func_8018C2D8 | MATCH — reuse m for next ptr (m = s1+0xD0; dv = m) and m1 for col: reassignment kills the cse sym class (W02)". Mechanism: reassignment kills the cse sym class.

Line 44: "launder: p = *abase; p += 0x2D (self-reassign stales cse ...)" — a self-reassignment stales cse's equivalence.

So a promising trick: make iv2c reassigned so cse's symbol class for it changes. E.g.:

```
iv2c = iVar2;
iv2c = iv2c;      // self-assign — that's a no-op launder, not allowed
```

Better: a real second set that is semantically needed. Hmm. What real second set does iv2c have? None.

Alternative from line 31: "launder->pv=*p; pv&=mask split" — split a compound expression into two real sets so the value isn't a copy.

Our launder's role: force a copy. Hmm.

What about making iv2c a *different variable that gets reassigned*: e.g. reuse an existing variable for the compare. Look: `one` is assigned 1 and compared. What if we write the compare differently using a real second set:

```
iv2c = iVar2;
iv2c = iv2c + 1;   // no, changes value
```

Hmm.

Think about cse's copy propagation more precisely in GCC 2.7.2. cse.c: it records `(src, dest)` in the "reg_eqv" table only if `REGNO(dest) != REGNO(src)` and dest is a REG. Then uses of dest get rewritten to src *within the block, if the value is still valid* — actually cse's copy propagation in 2.7.2: in `cse_insn`, for `SET (reg, reg)`, it records an equivalence `dest = src` and sets `reg_eqv_table`. Later insns using dest... Hmm, cse in 2.7.2 does not rewrite uses of dest to src generally; it's cse_insn's `src_eqv` used for comparisons. Hmm, but observed: the move is gone and `beq a0,v0` uses a0.

Maybe it's combine: `iv2c = iVar2` then `if (iv2c != one)` — combine merges the copy into the compare (register copy propagation). Combine runs after cse2? In GCC 2.7.2, combine_instructions is called from rest_of_compilation right after cse pass 2? Let me check toplev.c order in tools/reference/gcc-2.7.2. That would tell me which pass to defeat.

Let me grep the pass order.
