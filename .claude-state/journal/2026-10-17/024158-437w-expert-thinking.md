---
ts: 2026-10-17T08:41:58.604Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
The counts have shifted from the original plan now that T7 reduced things: 2269 rows total, with 543 left by the author and 198 not judged (157 asm-macro-def, 3 gte, 18 singleton, 20 head-class) — different from the plan's earlier 808/205 figures, which were pre-T5/T7.

There's a sub-part to work through: re-judging the 543 plus the 41 non-macro not-judged rows via delever removal. I need to pin down what "left by the author" actually means in the ledger — probably that the delever verdict was manually set by the author — so I should grep the lever census writer for that instrument text to confirm.
