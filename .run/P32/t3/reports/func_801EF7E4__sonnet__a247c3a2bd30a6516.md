# md_SC03_053:func_801EF7E4 — arm sonnet — model claude-sonnet-5
agent a247c3a2bd30a6516 · start 2026-09-05T06:55:30.378Z · end 2026-09-05T07:06:30.635Z · transcript /home/musashi/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-a247c3a2bd30a6516.jsonl

## Task prompt (first 600 chars)

Byte-match ONE function for the Brave Fencer Musashi matching decomp. Repo: /home/musashi/bfm-decomp (run every command from there). Target: func_801EF7E4 in binary md_SC03_053 (72 instructions, never drafted; the TU already holds several sibling script-module functions banked this session — read them for house style, e.g. how func_8012E544 and the actor-field stores are spelled). Arm: sonnet. READ FIRST, in order: .run/P32/t3/BRIEF.md, .run/P32/t3/SYS.md, .run/P32/t3/packs/func_801EF7E4.md. Target asm (read IN FULL): asm/md_SC03_053/nonmatchings/md_SC03_053/func_801EF7E4.s. Destination TU: sr

## Final report (verbatim)

MATCH confirmed in both the standalone check and the real-TU splice. The key structural insight: the asm's redundant "unreachable default" test (`bnez`/`beqz`/`j` triplet) was the switch-statement tell from cookbook §339, but a plain switch with separately-duplicated `case 0:` / `case 3:` bodies placed the merged body in the wrong physical position (relying on cross-jump, which put it last, adjacent to the epilogue). Writing the shared body under **combined case labels** (`case 0: case 3: { ... }`) — a single case node with two entry values rather than two duplicated bodies needing post-hoc cross-jump merging — placed the case0/3 body first, exactly matching the target's block layout, and gave a byte-identical match on the first such attempt.

The only real-TU friction was `func_801789AC`: the TU (updated mid-session by sibling banks) already declares it `extern s32 func_801789AC(s32 a0)` (by value, not pointer as I'd assumed from other overlays) — adopted that spelling and cast at the call site, per the standard `conflicting types` fix.

Files:
- Draft: `/home/musashi/bfm-decomp/.run/P32/t3/sonnet/func_801EF7E4.c`
- Target asm: `/home/musashi/bfm-decomp/asm/md_SC03_053/nonmatchings/md_SC03_053/func_801EF7E4.s`
- Destination TU (not edited): `/home/musashi/bfm-decomp/src/md_SC03_053/md_SC03_053.c`

{"fn": "func_801EF7E4", "binary": "md_SC03_053", "arm": "sonnet", "status": "MATCH", "closeness": 0, "compiles": true, "draft_path": ".run/P32/t3/sonnet/func_801EF7E4.c", "note": "72/72 MATCH in both match_one and rtu_match. Structural fix: combined `case 0: case 3: { ... }` labels (one shared case node) instead of two textually-duplicated bodies relying on cross-jump merge — the duplicate-body approach cross-jump-merged into the WRONG physical position (last, next to epilogue) regardless of source case order; combined labels placed it first, matching target layout. Confirms/extends cookbook §339 (redundant default test = switch tell) with a §5a-adjacent lesson: prefer combined case labels over duplicated-body-plus-cross-jump when you control body placement order, since cross-jump target placement is not steerable from C source. Real-TU friction: func_801789AC's TU-local decl is `s32 func_801789AC(s32 a0)` (by value), not the `(s32*)` pointer form used in a sibling overlay TU — adopted the TU's exact decl and cast at call site."}
