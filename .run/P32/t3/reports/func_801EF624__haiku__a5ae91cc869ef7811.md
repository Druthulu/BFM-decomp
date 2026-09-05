# md_SC03_053:func_801EF624 — arm haiku — model claude-haiku-4-5-20251001
agent a5ae91cc869ef7811 · start 2026-09-05T07:01:19.860Z · end 2026-09-05T07:04:25.430Z · transcript /home/musashi/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-a5ae91cc869ef7811.jsonl

## Task prompt (first 600 chars)

Byte-match ONE function for the Brave Fencer Musashi matching decomp. Repo: /home/musashi/bfm-decomp (run every command from there). Target: func_801EF624 in binary md_SC03_053 (35 instructions, never drafted). Arm: haiku. READ FIRST, in order: .run/P32/t3/BRIEF.md, .run/P32/t3/SYS.md, .run/P32/t3/packs/func_801EF624.md. Target asm (read IN FULL): asm/md_SC03_053/nonmatchings/md_SC03_053/func_801EF624.s. Destination TU: src/md_SC03_053/md_SC03_053.c (read its banked siblings for house style). sub = md_SC03_053. Write your best draft to .run/P32/t3/haiku/func_801EF624.c. Check with `.venv/bin/p

## Final report (verbatim)

{"fn": "func_801EF624", "binary": "md_SC03_053", "arm": "haiku", "status": "MATCH", "closeness": null, "compiles": true, "draft_path": ".run/P32/t3/haiku/func_801EF624.c", "note": "Register pin __asm__(\"$16\") forced stable $s0 allocation across branches; the compiler was incorrectly using $s1 in the false-branch arm until the register was pinned (memory: dont-conclude-unsteerable-try-register-pins)"}
