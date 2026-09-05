# md_MAIN_007:func_800CEE2C — arm sonnet — model claude-sonnet-5
agent ad629fbb5409d94d5 · start 2026-09-05T06:55:36.540Z · end 2026-09-05T07:04:42.066Z · transcript /home/musashi/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-ad629fbb5409d94d5.jsonl

## Task prompt (first 600 chars)

Byte-match ONE function for the Brave Fencer Musashi matching decomp. Repo: /home/musashi/bfm-decomp (run every command from there). Target: func_800CEE2C in binary md_MAIN_007 (52 instructions, the module's first function, never drafted). Arm: sonnet. READ FIRST, in order: .run/P32/t3/BRIEF.md, .run/P32/t3/SYS.md, .run/P32/t3/packs/func_800CEE2C.md. Target asm (read IN FULL): asm/md_MAIN_007/nonmatchings/md_MAIN_007/func_800CEE2C.s. Destination TU: src/md_MAIN_007/md_MAIN_007.c (a boot-slot module TU that stacks only config/symbols.us.txt). sub = md_MAIN_007. Write your best draft to .run/P32

## Final report (verbatim)

All symbols (D_800B99E4, D_800CFABF, D_800CFAC4, D_800CFAD4, D_800CFADC, D_800D1364, D_800AF630, func_8001534C) are confirmed against the target .s's own relocation lines — cross-checked earlier via `asm/md_MAIN_007/data/tail.data.s` and `func_8001534C`'s canonical definition in `src/800.c`. No invented/seed symbols. Both the leaf check (`match_one`) and the real-TU check (`rtu_match`) report MATCH at 52 instructions, byte-identical.

Key lever: the target holds `&D_800AF630` live across two `func_8001534C` calls in the callee-saved `$s0`, and reads a nearby global (`D_800B99E4`, same address as `D_800AF630+0xA3B4`) via raw base+offset arithmetic with **no relocation** on that access — so the C had to route through a `u8 *base = D_800AF630;` declared early (forcing the cross-call register allocation) and dereference `*(u16 *)(base + 0xA3B4)` rather than the named symbol. Separately, `&D_800CFABF` had to be captured once into an explicit pointer local (`p`) and reused for both the `p - 0xB` argument and the `*p = v1` store, otherwise gcc re-derived the address twice with different registers.

Draft: `/home/musashi/bfm-decomp/.run/P32/t3/sonnet/func_800CEE2C.c`

{"fn": "func_800CEE2C", "binary": "md_MAIN_007", "arm": "sonnet", "status": "MATCH", "closeness": 0, "compiles": true, "draft_path": ".run/P32/t3/sonnet/func_800CEE2C.c", "note": "s0 cross-call liveness: needed an early `u8 *base = D_800AF630;` local (live across both func_8001534C calls) to force callee-saved $s0 allocation, then `*(u16*)(base+0xA3B4)` (no relocation, matches D_800B99E4's address by raw offset) instead of the named symbol. Also had to capture &D_800CFABF once into an explicit pointer local reused for both the (p-0xB) arg and the *p=v1 store — writing two separate &D_800CFABF expressions produced 3 independent address computations instead of 1 shared register."}
