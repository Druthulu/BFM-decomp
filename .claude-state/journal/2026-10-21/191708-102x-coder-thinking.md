---
ts: 2026-10-22T01:17:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YEsoNcAIK7ghzo20uY4M
---
Now item 2's notes.md (append the handoff). I have the original content (read earlier). Let me write it with the handoff section.

Item 2 handoff content:
- best candidate path: .run/P40/T11/G08b/func_8014FD54__func_8014FD54/vP1_ret.c (also vP2_ret2.c) — score 6, 39 ins vs 40.
- spellings tried: nopin (9), decl order, hoist before/after the call, u32 ret, byte var, res var, &&-fold, direct returns, early return, mask var, ret copy, swapped tests, etc. (scores 6–14).
- current hypothesis: the ROM needs $2 reserved for the whole function (the pin's hard-reg `result`), so the call result is copied to $3 (`move v1,v0`); lever-free, the call-result pseudo (pri 10000, refs 2, live 2, blk 1, prefers v0) always wins $2 and the RESULT_DECL's short live range leaves $2 free at the call. The alloc table (cc1 dumps, deleted) showed: lever-free r73 (RESULT_DECL) pri 10000 refs 3 live 3 prefers v0; pinned r73 pri 7500 refs 3 live 4 conflicts v0 prefers v1, and the pinned hard reg $2 reserves $2 for the whole function.
- next tries: (a) give the RESULT_DECL a set before the call (an early `return` — needs an instruction-neutral spelling); (b) raise the RESULT_DECL's priority above the call-result pseudo (refs/live) without changing the instruction count: more `return` statements that gcc merges, or a shorter RESULT_DECL live range; (c) a local live across [call..mask test] with pri > 10000 (refs 3, live 2) to take $2 and push the call result to $3; (d) try the `result`-variable shape with the local declared before `ret` (allocno order = the tie-break).

Let me write notes.md for item 2.

Also write win.c for item 2 = the best body (vP1_ret.c) — consistent with the G08 convention. Let me do that.

Then moves.md and the shard log.
