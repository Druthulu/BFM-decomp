# md_MAIN_009:func_800CD674 — arm opus — model claude-opus-5
agent a89cf5f2cae287adc · start 2026-09-05T06:54:45.664Z · end 2026-09-05T07:53:25.172Z · transcript /home/musashi/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-a89cf5f2cae287adc.jsonl

## Task prompt (first 600 chars)

Byte-match ONE function for the Brave Fencer Musashi matching decomp. Repo: /home/musashi/bfm-decomp (run every command from there). Target: func_800CD674 in binary md_MAIN_009 (174 instructions, never drafted before). Arm: opus. READ FIRST, in order: .run/P32/t3/BRIEF.md, .run/P32/t3/SYS.md, .run/P32/t3/packs/func_800CD674.md. Target asm (read IN FULL): asm/md_MAIN_009/nonmatchings/md_MAIN_009/func_800CD674.s. Destination TU: src/md_MAIN_009/md_MAIN_009.c. sub = md_MAIN_009. Write your best draft to .run/P32/t3/opus/func_800CD674.c. Check with `.venv/bin/python tools/match_one.py func_800CD67

## Final report (verbatim)

Draft is in place and verified.

## What the function is

`func_800CD674(x, y, colour)` builds **four 0x18-byte "SPRT-with-its-own-tpage" primitives** (a 2×2 grid of 0xA0×0x100 tiles, `len = 5` words, code `0x64`, clut `0x7800`, tpages `0xE1000086/87/96/97`) at the `D_800A71D0` prim-buffer cursor, open-codes the PSY-Q `addPrim()` P_TAG 24-bit RMW pair onto OT word [0] of `D_800ABA24 + D_800BAE22 * 0x4000`, and republishes the advanced cursor. Same family as boot's `func_8001212C` (-O0) and `src/800.c:func_80016450` (-O2).

## Result

**174/174 instructions, 2 mismatched** (98.9%), identical under `match_one` and `rtu_match` — the real TU accepts the draft with no declaration conflicts. All 24 relocations (4× `D_800A71D0`, 4× `D_800ABA24`, 16× `D_800BAE22`) hand-checked one-to-one against the target `.s`, same order and counts (§174 law 1c).

Residual: `and $a3,$v0,$t1` / `or $v1,$v1,$a3` should be `$t1` — prim 3's masked-`p` wants `$a3` and prim 4's wants `$t1` (`m24`'s dying register). One shared local can only be one of them; splitting into two locals is +1 pseudo, which displaces `ori $s4,$s4,0x96` and the `0xE1000097 lui $s1` in **every** spelling measured (31 mismatched). Class `REGALLOC-PERM [permuter]`.

## The generalizable find (worth banking in the cookbook)

**The field stores must be NON-STRUCT lvalues.** gcc-2.7.2 `true_dependence` drops the store→load edge when the store is `MEM_IN_STRUCT_P` with a varying address **and mode != QImode**. With a `Sprt24 *p` struct, the five `sh` stores (clut/x0/y0/w/h) sink past the `lhu D_800BAE22` while the `sb`/`sw` ones stay — a store block split exactly on instruction width, unreachable by any statement order (verified: source order is preserved *within* each mode group and the split point never moves). Writing every field as `*(T *)(p + off)` restores the false edge for all 13 and the block lands byte-exact. This is a mode-keyed instance of cookbook §340. **102 mismatched → 6.**

Two more measured levers: `y + 0x100` inline for prims 3/4 rather than `y += 0x100` (the accumulate form lengthens `$a1`'s chain and sched2 hoists `addiu $a1,-0x78` to the head of the prologue — 16 → 7); and `otv = *ot;` splitting the half-2 RMW so the OT read precedes the `D_800A71D0 = p` publish and the OT write follows it, which is what puts `lui $at / sw $v0,%lo(D_800A71D0)` in the last `lw`'s shadow (7 → 2).

Measured **inert**: statement order for x/y/tpr/pm (36 positions), zero-byte fences at all 70 statement slots, re-ties on p/y/c/tpr/m24/mff, `pm2` declared plain/register/pinned `$4/$6/$7/$9`, `ot` pinned to 13 different registers, arg types s16/s32/u8, `p = p + 0x18` vs `p += 0x18`, explicit x2/y2 temps, `D_800A71D0` published as `p + 0x18` or before the last OT store, and `-fno-schedule-insns[2]` attribution (neither pass alone reproduces the target).

Nothing under `src/` or `config/` was edited. (Note: `src/.masked_diff_probe.*.c` files keep appearing — those are per-PID temp probes from ~35 concurrent `match_one` processes in this wave, not mine; I stopped removing them once I realized they belong to other agents' live runs.)

{"fn": "func_800CD674", "binary": "md_MAIN_009", "arm": "opus", "status": "NEAR", "closeness": 2, "compiles": true, "draft_path": ".run/P32/t3/opus/func_800CD674.c", "note": "174/174 ins, 2 mismatched in both match_one and rtu_match; relocs hand-verified. Residual class REGALLOC-PERM [permuter] sig=$a3>$t1: prim3's masked-p wants $a3, prim4's wants $t1 (m24's dying reg); one shared local can only be one, and splitting into two locals is +1 pseudo that displaces `ori $s4,$s4,0x96` and the 0xE1000097 `lui $s1` (31 mismatched) in every spelling. KEY FIND (cookbook-worthy, extends 340): the primitive's field stores must be NON-STRUCT lvalues `*(T *)(p+off)` -- gcc-2.7.2 true_dependence drops the store->load edge for MEM_IN_STRUCT_P varying-address stores with mode != QImode, so a struct `p` sinks all five `sh` stores past the `lhu D_800BAE22` while the `sb`/`sw` ones stay (102 -> 6). Also: `y + 0x100` inline beats `y += 0x100` (16 -> 7), and an `otv = *ot` temp splitting the half-2 RMW puts the D_800A71D0 publish in the last lw's shadow (7 -> 2). INERT: statement order (36 perms), fences at all 70 slots, re-ties on p/y/c/tpr/m24/mff, pm2 decl variants, ot pinned to 13 regs, arg types, p+=0x18 spellings, -fno-schedule-insns[1,2]."}
