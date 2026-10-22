---
ts: 2026-10-22T09:44:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_j7J9dHA8dhCPZ8RxBM28
---
Pass order in gcc 2.7.2 toplev.c:
1. (line 2781-2867): flow analysis + CSE (cse_main) — the .cse dump is here (cse_main dumps to cse_dump_file).
2. loop (2893) — .loop
3. cse2 (2925) — .cse2
4. flow (2971, 2983)
5. combine (3004) — .combine
6. sched (3033) — .sched

And the RTL dump ('r')? Let me find where rtl_dump_file is printed — probably right after expand, before cse.

So the order is: rtl → cse → loop → cse2 → flow → combine → sched.

So .cse comes BEFORE .combine ✓ (as I assumed). Then:
- .rtl: (plus (symbol) (reg 118)) — symbol first
- .cse: (plus (symbol) (reg 118)) — symbol first
- .combine: (plus (reg 118) (symbol)) — index first (combine swapped it!)
- final asm: index first ✓ consistent.

So COMBINE swapped it. Good — combine.c is the place. Now let me find the code in combine.c that swaps a PLUS's operands.

The rule: combine has a "canonicalization" for commutative ops. Let me look at combine's `simplify_rtx` case PLUS. Let me find "case PLUS:" in simplify_rtx (around line 3100-3130?). We saw at 3120: `temp = simplify_binary_operation (code, mode, XEXP (x, 0), XEXP (x, 1));`.

Let me read simplify_rtx's beginning (around 2961-3130) to see the handling before that.

Actually, maybe the swap is in the `plus_constant`/`make_compound_operation` recursion: in make_compound_operation, the PLUS case might reorder (plus (symbol) (mult)) into (plus (mult) (symbol)) to build a "compound operation" (the scaled-index form). Let me look at the PLUS case of make_compound_operation (line 5856 area is the AND case...). Let me find the PLUS case within make_compound_operation (after line 5400).
