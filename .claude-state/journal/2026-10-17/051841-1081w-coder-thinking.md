---
ts: 2026-10-17T11:18:41.960Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm trying to trace label 57's use count through the CSE pass, following the jump paths from BB0 through BB1 to figure out whether LABEL_NUSES actually drops to 1 during that scan.

Actually, I suspect cse1 is threading jump 21 directly to 73 during its own pass via jump-redirection logic in cse_insn, which would make label 57 followable afterward on rescan. That means I need a store block cse1 genuinely can't merge or thread — one that's only decidable in cse2, so I should look at how cse.c handles redirect_jump and LABEL_NUSES inside cse_insn.
