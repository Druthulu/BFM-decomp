---
ts: 2026-11-06T16:30:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ono5gD6FY6Z6MtkmqGCj
---
So without the pin, `v0r = 1` lands in t0 instead of v0. That's the keepalive use (asm operand reads v0r, so v0r is live). Global-alloc gives it t0 because... v0 is reserved? With the pin, v0. Lever-free we need v0r in $2 naturally.

But without the keepalive, v0r is dead and flow deletes. With keepalive (asm use), v0r is live at that asm and local/global-alloc picks t0 (not v0) because... $2 is caller-saved and free? Hmm, global-alloc should prefer v0? It gave t0.

Note the target: li v0,1 at 0x55c. If it's a return value, expand puts it in $2. So the whole thing (v0 register + presence) strongly indicates a real return. That's the expand-void-return wall.

So item 1 is very likely WALL expand-void-return. But we must try 30 candidates. Let's think of plausible real-C moves to keep the value and put it in v0 without asm:

Idea: `v0r = 1;` and then make it live via a *real use that costs zero bytes and is optimized away after local-alloc*. What uses cost zero bytes? 
- A condition that folds to constant: `if (v0r) goto ret;` where ret is the next label — jump1 might delete it. But the use in the RTL exists at the point local-alloc runs? local-alloc runs after jump1? Order: jump1 (jump_optimize) runs after cse/loop, before local-alloc. If jump1 folds `if (1)` and removes the test, the use disappears before local-alloc → v0r dead → flow deletes. Order: flow1, combine, sched1, local-alloc, global-alloc, flow2... Actually local-alloc is after jump1? GCC 2.7.2 pass order: ... cse, loop, cse2, jump, flow, combine, sched, local-alloc, global-alloc, ... jump2 later. So jump1 would kill it.

- A use in a `&&` that folds? Same.

- `(void)v0r;`? A cast-to-void use. Does gcc keep the value? `(void)v0r;` — expand may generate nothing, and the VAR_DECL might be marked used? In gcc, a cast-to-void of a variable — expand_expr with ignore target... Actually `(void)x;` is an expression statement; expand_expr(..., const0_rtx, ...) — it may not emit code but might mark the variable as used. Let me test! This is a real C construct (no lever, not an asm). It could keep v0r live through to local-alloc. But if it generates no insn, the use doesn't reach RTL liveness? In gcc 2.7.2, `(void)x` for a scalar variable: expand_expr on a VAR_DECL returns the pseudo reg, and since target is const0 and it's a register... it just returns; the pseudo might never appear in RTL → dead.

Hmm, what about `if (v0r == 1) { }`? fold → constant.

What about `i = v0r;` then `i` used in `for`? no.

Another angle: the value 1 might come from the function's *last call argument*. `func_80059658(1)` sets a0=1. The `li v0,1` is separate.

Actually! What if the source's last statement is `return func_80010A98(), 1;`? Comma expression with a cast to void function... `return` not allowed in void.

Hmm, what if v0r is a `volatile`? Then `v0r = 1` would store to stack — extra insn, not matching.

OK here's another thought: what if the real source is:
```
if (0) v0r = 1;  // no
```

What if `v0r` is used as the loop's... no.

Given the strong evidence, WALL expand-void-return is right. But the shard wants us to actually try ≥30. Let's design a systematic set of ~30 real-C moves for the three residuals and score them. The item has three levers; a WALL's "best = lowest score of a lever-free body". So we need to find the best lever-free body (all three gone) and its lowest score. Currently w1 = 20. Maybe we can get lower, e.g. 10 by fixing the pin and keepalive partially.

Wait — for a WALL, best is the lowest score of a lever-free body (all kinds gone). If we can't fix the keepalive (missing li v0,1 = 1 ins) but we can fix the barrier's 19 via real C, we could get to score ~2-3. That's a meaningful "best" and a better evidence.

Let's focus on the barrier (19). The merge of the two identical call blocks. Real C ways to stop cross-jump while keeping bytes:

Cross-jump merges blocks if identical. To make them non-identical at the RTL level but identical in emitted bytes... The classic: one block's `func_800D2AA0(0)` argument 0 vs a different zero-valued spelling: e.g. `func_800D2AA0(NULL)` — same bytes (move a0,zero), same RTL (const 0). No.

What if one block uses `func_800D2AA0(0)` and the other `func_800D2AA0(0)` but with an intervening label used by a goto? Labels that are jump targets prevent... Actually cross-jump merges the *common suffix* of two blocks; a label in between doesn't prevent it because labels aren't insns. Hmm, but `CODE_LABEL` nodes are in the insn chain; cross-jump's `rtx_renumbered_equal_p` might treat LABEL_REF/CODE_LABEL as non-equal! In gcc 2.7.2 jump.c, cross_jump uses `rtx_renumbered_equal_p` and there's special handling: it does not merge if a label reference differs. But a plain CODE_LABEL between insns — the comparison walks insns; labels are skipped? Let me look at jump.c cross-jump.

Let me grep the reference source.
