# md_SC03_053:func_801EF734 — arm sonnet — model claude-sonnet-5
agent a2f0d5509a90e778f · start 2026-09-05T07:07:14.533Z · end 2026-09-05T07:11:31.843Z · transcript /home/musashi/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-a2f0d5509a90e778f.jsonl

## Task prompt (first 600 chars)

Byte-match ONE function for the Brave Fencer Musashi matching decomp. Repo: /home/musashi/bfm-decomp (run every command from there). Target: func_801EF734 in binary md_SC03_053 (44 instructions). ESCALATION: a Haiku drafter plateaued at 47 instructions with its draft at .run/P32/t3/haiku/func_801EF734.c — its three if-arms each emit their OWN `jal` where the target CONVERGES on one shared tail call (44 ins). That is a C structure question, not a compiler wall: make the arms only compute/assign the arguments and FALL THROUGH (or `goto` one shared label) to a SINGLE call site so gcc emits one ja

## Final report (verbatim)

MATCH confirmed at both levels — leaf (`match_one`) and real-TU (`rtu_match`), both reporting `MATCH (44 ins)`.

Root cause and fix: the haiku draft's structural problem wasn't literally "3 separate `jal`s" per se — it actually did get gcc's `cross_jump` pass to merge the three textually-duplicated `func_80178CBC` calls into one shared `jal` site. But its mixed shape (an early-`return` first `if`, followed by a separate nested `if`/`else`) caused gcc's register allocator to fail to coalesce the pointer value into a single callee-saved register — it allocated `$s0` **and** `$s1` for the same value across the two control-flow regions, adding a spurious `move s1,s0`, an extra `sw`/`lw s1`, and a bigger frame (32 vs 24 bytes) — 3 instructions too many (47 vs 44).

Fix: register-pin the pointer (`register s32 s0 __asm__("$16")`, matching sibling `func_801EF624` in the same TU) and write the function as one uniform `if / else if / else` chain — no early `return`, no nested nesting — with the literal `func_80178CBC(s0, &D_xxx)` call duplicated in each of the three arms. This is exactly cookbook §224's documented lever ("write the duplicate, and read a shared delay slot as the merge signature" / "duplicate the whole call per arm; cross_jump merges only the common jal+tail, landing `move a0,s0` in the branch's delay slot"). gcc's `cross_jump` then merged the three identical `jal func_80178CBC` + epilogue tails into one shared block reached by `j` from arm 1 and arm 2 and fall-through from arm 3 — reproducing the target's redundant per-arm `addu $a0,$s0,$zero` and the single 44-instruction body exactly.

Final draft: `/home/musashi/bfm-decomp/.run/P32/t3/sonnet/func_801EF734.c`

Symbols verified against the target's own relocation lines (`func_8012E8E0`, `func_8012E88C`, `func_80187344`, `func_80029178`, `func_80178CBC`, `D_801F0900`, `D_801F0A6C`, `D_801F0A9C`, `D_801F0934`) — all match. No files under `src/` or `config/` were touched.

{"fn": "func_801EF734", "binary": "md_SC03_053", "arm": "sonnet", "status": "MATCH", "closeness": null, "compiles": true, "draft_path": ".run/P32/t3/sonnet/func_801EF734.c", "note": "cookbook §224 lever: register-pin s0 + write the func_80178CBC call literally in each of 3 nested if/else-if/else arms (no early return, no nesting-shape mismatch) so gcc's cross_jump merges the 3 identical jal+epilogue tails into one shared call site, redundantly emitting move a0,s0 per arm exactly like the target; haiku's plateau at 47 ins was a register-coalescing failure (spurious $s1) from mixing an early-return if with a separate nested if/else, not a missing merge."}
