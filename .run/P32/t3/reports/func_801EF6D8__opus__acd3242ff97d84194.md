# md_SC03_054:func_801EF6D8 — arm opus — model claude-opus-5
agent acd3242ff97d84194 · start 2026-09-05T06:53:39.372Z · end 2026-09-05T07:11:45.510Z · transcript /home/musashi/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-acd3242ff97d84194.jsonl

## Task prompt (first 600 chars)

Byte-match ONE function for the Brave Fencer Musashi matching decomp. Repo: /home/musashi/bfm-decomp (run every command from there). Target: func_801EF6D8 in binary md_SC03_054 (663 instructions, a jump-table dispatcher; a switch is expected — its table pads are derived at build time by the module rule, so just write the C). Arm: opus. READ FIRST, in order: .run/P32/t3/BRIEF.md (tools + output contract), .run/P32/t3/SYS.md (the laws), .run/P32/t3/packs/func_801EF6D8.md (your pack: the TU's authoritative declarations, a matched neighbour, journal history). Target asm (read IN FULL): asm/md_SC03

## Final report (verbatim)

Both gates are green. Cleaning up nothing under `src/` or `config/` — untouched.

**Result: `func_801EF6D8` byte-matches (604 ins), leaf and real-TU.**

What it is: a 12-arm dispatcher on `*(u16 *)(a0 + 0x34)`, with a 7-arm sub-state-machine on the global `D_801F1480` duplicated verbatim in outer cases 6–11 (six separate jump tables), plus a `cond ? 0x10 : 0` chain emitted as `sltu $v0,$zero,$v0 / sll $s0,$v0,4`.

Two non-obvious levers closed the 44-instruction gap — both worth adding to the cookbook:

1. **`2($sN)` off a `lui/addiu`-materialized base means a POINTER LOCAL in the source, not array/struct indexing on the extern.** Writing `D_801F1480` + `(&D_801F1480)[1]` (or a struct member) makes gcc-2.7.2 emit the absolute 2-insn `lui %hi(G+2) / sh %lo(G+2)($at)` form for *every* access — confirmed by the already-banked neighbour `func_801EF558`, which does exactly that for `D_801F1482`. Only `p = &D_801F1480;` followed by `p[0]`/`p[1]` produces the single hoisted `$s0` base with `0($s0)`/`2($s0)`. This was 7 extra instructions × 6 copies = 42 of the 44. Corollary tell: the sub-switch *selector* still reads the global absolutely (`lui $v1 / lh %lo`) and the scheduler slots the `lui/addiu $s0` pair into that load's delay — so `p = &G;` sits *before* `switch (G)` in the source even though the address computation appears *after* the load in the output.

2. **A constant-arm ternary chain whose value is consumed immediately as a call argument lays out differently from one stored to a variable.** `func_800D0F4C(c1?0xD:c2?0xE:c3?0xF:c4?0x10:0)` (and `t = <chain>; func_800D0F4C(t)` — identical) puts the *third* arm's value in its own block after the last arm plus a `j` (+2 ins). The `if / else if` **statement** chain assigning the same constants reproduces the target's "value insn before the inverted branch" layout. Note the identical chain in outer cases 0/1 matched as a ternary, because there the value lives across a later call and lands in `$s0` — the ternary-vs-if-statement distinction only bites when the result is coalesced into `$a0`.

Symbol audit per law 1c: extracted the 85 relocation targets from the target `.s` in address order and compared against `objdump -dr` on my object (internal `.text` branch relocs filtered) — 85/85 identical in name and order, including the six `jtbl_*`.

Also note the destination TU changed on disk mid-task (another agent banked `func_801EF558`); my externs for `func_8002D4C8`, `func_80178CBC`, `func_80029514`, `func_80029124`, `func_800D0F4C` and `D_801F1480` match its new file-scope declarations exactly, and `rtu_match` was run against that current version.

{"fn": "func_801EF6D8", "binary": "md_SC03_054", "arm": "opus", "status": "MATCH", "closeness": 0, "compiles": true, "draft_path": ".run/P32/t3/opus/func_801EF6D8.c", "note": "MATCH leaf+rtu (604 ins), 85/85 relocation symbols verified in order. Two new idioms: (1) a `2($sN)` offset off a lui/addiu-materialized base = a POINTER LOCAL (`p=&G;` then `p[0]`/`p[1]`) in the source -- array/struct access on the extern emits the absolute `lui %hi(G+2)/sh %lo(G+2)` form instead (proven by same-TU neighbour func_801EF558); worth 7 ins x 6 duplicated sub-switches = 42 of the 44-ins gap. (2) A constant-arm ternary chain consumed directly as a call ARGUMENT lays the 3rd arm's value block after the last arm (+2 ins); the equivalent if/else-if STATEMENT chain reproduces the target -- the same ternary matched in cases 0/1 where the value lives across a later call and gets $s0."}
