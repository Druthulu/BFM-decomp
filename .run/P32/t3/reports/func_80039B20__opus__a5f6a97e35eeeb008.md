# main:func_80039B20 — arm opus — model claude-opus-5
agent a5f6a97e35eeeb008 · start 2026-09-05T06:54:59.677Z · end 2026-09-05T07:01:15.933Z · transcript /home/musashi/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-a5f6a97e35eeeb008.jsonl

## Task prompt (first 600 chars)

Byte-match ONE function for the Brave Fencer Musashi matching decomp. Repo: /home/musashi/bfm-decomp (run every command from there). Target: func_80039B20 in binary main (79 instructions, class D-NEAR, best closeness 7 — seed .run/S79w/sonnet/func_80039B20.c; the residual is a 7-entry rotation around a redundant D_80073140[i] re-read that the target schedules right after the D_800C7D20 load; four restructurings were inert and the permuter confirmed the plateau). Arm: opus. READ FIRST, in order: .run/P32/t3/BRIEF.md, .run/P32/t3/SYS.md, .run/P32/t3/packs/func_80039B20.md. Target asm (read IN FU

## Final report (verbatim)

**MATCH** — leaf `match_one` and real-TU `rtu_match` (fresh work dir) both report `MATCH (79 ins)`. Symbol audit is exact: the 7 relocation symbols in the target `.s` are exactly the 7 in the draft, no extras.

**What closed it.** The 7-entry rotation was never a scheduler tie-break — it was a `true_dependence` edge I was creating myself, and the cookbook already owned the lever (§30 / §30a#1 / §3-F / §351 / §379), just never applied to this function.

The four prior attempts all spelled the re-read as `*(s32 *)(base1 + i * 4)`. Per `expr.c:4570-4576` (verified in `tools/reference/gcc-2.7.2/expr.c`), the `/s` (`MEM_IN_STRUCT_P`) grant requires `TREE_CODE(TREE_OPERAND(exp,0)) == PLUS_EXPR` — and an integer add wrapped in a pointer cast puts a `NOP_EXPR` on top of the PLUS, so `/s` is **denied**. Without `/s`, `true_dependence` (`sched.c:817-841`) keeps the edge between the load and the fixed-address `D_800C7D20` store, pinning the re-read below it — exactly the observed idx55→idx61 sink.

Rewriting the identical address as a bare-typed subscript — `((s32 *)base1)[i]` instead of `*(s32 *)(base1 + i * 4)` — makes the INDIRECT_REF operand a top-level `PLUS_EXPR`, grants `/s`, and satisfies the drop clause's exact shape (load: `/s` + varying reg address + SImode; store: non-`/s` + fixed `SYMBOL_REF` address). The edge vanishes and the re-read hoists into the `D_800C7D20` load-delay slot. **One-character-class change, zero instruction-count drift, first compile.**

**Two things I measured that stay load-bearing** (both regress hard, so keep them in the banked body):
- the `$6`/`$7` register pins on `i`/`off` — removing them → 23 mismatched
- the `__asm__ __volatile__("" : "=r"(base1) : "0"(base1))` launder on the `D_80073140` base (defeats `move_movables` hoisting) — removing it → 39 mismatched

Note the two levers are in tension by construction and that is the reason this one hid for four attempts: the launder that stops LICM forces the base into an *integer* local, and an integer local is precisely what pushes the deref into the cast-wrapped-PLUS shape that loses `/s`. The subscript spelling keeps the launder and recovers `/s` at the same time. **Cookbook-worthy addendum to §30a#1** (for the coordinator's harvest step): *when a `/s` grant is blocked by an integer launder introduced for an unrelated LICM reason, re-index rather than re-cast — `((T *)n)[i]` restores `/s` while leaving `n` an integer.* Also worth re-probing: the residual class "redundant re-read scheduled at point-of-use instead of into a preceding load-delay slot" should be routed to §30 as a first move, not to the permuter — the permuter cannot reach an alias flag from C, which is why S80's ILS plateaued at 7 from a seed of 7.

`.run/P32/t3/opus/func_80039B20.c` is the draft; nothing under `src/` or `config/` was touched.

{"fn": "func_80039B20", "binary": "main", "arm": "opus", "status": "MATCH", "closeness": 0, "compiles": true, "draft_path": ".run/P32/t3/opus/func_80039B20.c", "note": "Closed by granting MEM_IN_STRUCT_P (/s) to the redundant D_80073140[i] re-read: rewrote *(s32*)(base1 + i*4) as ((s32*)base1)[i]. Per expr.c:4570-4576 a cast-wrapped PLUS is denied /s (cookbook §30a#1), so true_dependence (sched.c:817-841) kept the edge to the fixed-address D_800C7D20 store and pinned the re-read below it; the bare-typed subscript makes the INDIRECT_REF operand a top-level PLUS_EXPR, drops the edge, and the load hoists into the D_800C7D20 load-delay slot. Not a permuter class -- the search cannot reach an alias flag from C, which is why S80 ILS plateaued at 7 from a seed of 7. Measured LOAD-BEARING (keep): $6/$7 register pins on i/off (removal -> 23 mismatched) and the volatile launder on the D_80073140 base that defeats move_movables (removal -> 39 mismatched). rtu_match MATCH against src/800_c.c on a fresh work dir; 7/7 symbols audited against the target's own relocation lines."}
