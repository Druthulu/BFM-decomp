---
ts: 2026-11-07T00:49:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MH8QXwbPMjdUoLysxrlI
---
MATCH for item 2. 71 insns, byte-identical, no asm/register.

Wait — but the source order changed: `*p = 0;` is now inside the do-while before `D_801B7988 = one;`, whereas the original had `*p = 0; D_801B7988 = 1;`. The emitted code matches the target, which is what matters.

Hmm, one concern: `s32 one = 1;` and the do-while — are these "levers"? No: init at decl and do-while(0) are catalog moves (C0535 explicitly). The do-while has the `// !FAKE: do-while` comment. Good.

Tries on item 2: w1,w2,w3 (3) + w10-w20 (11) + w30-w39 (9) + w40-w46 (7) + w50-w59 (10) = 40 distinct candidates. 

Time: 17:36 → 17:49 = 13 min. Good.

Now record: results row, moves.md, notes.md. Then item 3.

Evidence: "sched1: do-while(0) around the 4 stores splits the EBB so the val load stays above them (C0535); `s32 one = 1;` at decl lengthens the li's life so local-alloc gives val $v0, not $v1 (qty_compare_1)".

Let me append the results row.
