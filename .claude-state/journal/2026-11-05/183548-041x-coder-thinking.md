---
ts: 2026-11-06T01:35:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WOnWEER8LLPHc6aSVFMs
---
Still 9, same as nopin. So `return;` at end of function didn't emit a jump (gcc knows it's the last statement and omits). Let me verify by checking gcc stmt.c expand_null_return_1.

Alternatively, force a jump: make zero not the physically last block? Or put the `return;` inside a construct that isn't recognized as the last statement, e.g., `if (1) return;`? That would emit a conditional? Actually `if (1)` folds.

Maybe `goto end;` with `end:` label after? That would create a label and jump; then reorg may delete jump-to-next... but the epilogue is compiler-generated at the end.

Wait — if zero is the last block and the epilogue follows, jump-to-next would delete the jump anyway. The question is whether the jump exists at jump2 time. If gcc's expander doesn't emit a jump for a terminal `return;`, we need another way to have a jump at the end of zero's block.

Alternative: reorder the blocks so zero is not the last. E.g., put zero block earlier and the epilogue... The epilogue is always at the end of the function. If zero is not the last block, then zero's `return;` emits a jump (since it's not terminal). We could move the zero block before dec? But the target layout order is: ... turn, dec, zero. The physical order matters: target has zero last. But we could write the C in a different order and rely on... no, block order follows source.

Hmm. But maybe: write zero's return as `if (1) return;`? gcc 2.7.2 folds `if (1)` at parse? It's a constant condition; expand might still emit unconditional jump. Let's test.

Alternatively, the real C might have the zero block written as `... ; return;` where the function body's last statement is the return but inside a block that's part of an if-else chain? Currently zero is reached by `goto zero`. The `zero:` label then statements, then end of function. The return label: gcc emits it at the end; a `return;` here may be recognized as the function's last statement and elided.

Check stmt.c expand_null_return_1 for the elision.
