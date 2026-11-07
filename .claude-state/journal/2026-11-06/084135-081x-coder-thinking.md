---
ts: 2026-11-06T15:41:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1wTKmK1GGlJBEW89wvur
---
Interesting: same insn count (311) but the order differs: mine loads `D_80126950` into v1 and adds 500, then `mult a2,v1`; target loads into v0, adds 500, then `mult a2,v0`. Wait, the diff says mine[104:108] is deleted and target[107:112] inserted — it's an ordering difference with the mult moved.

Actually it looks like: mine has `lui v1; lw v1; nop; addiu v1,v1,500` at 104-107, then something, then `mult a2,v1` at 111. Target has at 107: `lui v0; lw v0; nop; addiu v0,v0,500; mult a2,v0`. So the register differs (v1 vs v0) and the position differs by a few.

Hmm, the `n` variable is pinned to $6 (a2? no, $6 = a2). Wait $6 is a2. And `mult a2,v1` — n is in a2 ($6, pinned). The launder's second set of n...

Let me look at the target assembly around there and mine.

The line 3115: `d = n * (D_80126950 + 0x1F4) / (ret * 4);`

With the launder, n is a 2nd set. Without, maybe cse folds something.

Let me look at more context of the diff — only 2 hunks, score 9. The register allocation of the constant's temp differs (v1 vs v0).

What does the launder do here? It redefines n ($6) opaquely. n = q + 8 (q pinned $2). Without the launder, cse may substitute n's value (q+8) into the multiply: `(q+8) * (D+500)`. That could change the allocation/order.

Let me look at the target asm.
