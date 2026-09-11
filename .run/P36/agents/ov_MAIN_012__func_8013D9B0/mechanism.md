# func_8013D9B0 (ov_MAIN_012 + 6 sibling copies): T7 agent c56, PORT of c47's minimum-lever body (P36 S103)

**Result: score 0 on all 7 copies with 2 marked levers** (the tree has 34 per copy). The source is c47's P1 body from
ov_SC04_011 (`../ov_SC04_011__func_8013D9B0/body.c`; its mechanism is in that pack's `mechanism.md`). The two GTE
`__asm__` lines are unchanged, byte for byte, with their `// !FAKE: … (P36 S103 c47 minimum-lever)` marks. There is no
register pin and nothing else is unmarked. The per-copy texts differ only in the four globals' names. Each body declares
them with body-local `extern`s, the same way the tree's levered bodies do in every one of these TUs.

Global map (per-overlay base; offsets +0 table, +8 cmd list, +0x18 any-flag, +0x20 set to -1):

| copy | TU | +0 (`void *`) | +8 (`s16 *`) | +0x18 (`s32`) | +0x20 (`s32`) | text | score |
|---|---|---|---|---|---|---|---|
| ov_MAIN_012 | src/ov_MAIN_012/ov_MAIN_012_jr_8013C98C.c | D_801841A4 | D_801841AC | D_801841BC | D_801841C4 | `body.c` (= `scratch/port_ov_MAIN_012.c`) | **0** |
| ov_SC02_037 | src/ov_SC02_037/ov_SC02_037_jr_8013C98C.c | D_801C849C | D_801C84A4 | D_801C84B4 | D_801C84BC | `scratch/port_ov_SC02_037.c` | **0** |
| ov_SC03_107 | src/ov_SC03_107/ov_SC03_107_jr_8013C98C.c | D_8019A7FC | D_8019A804 | D_8019A814 | D_8019A81C | `scratch/port_ov_SC03_107.c` | **0** |
| ov_SC07_006 | src/ov_SC07_006/ov_SC07_006_jr_8013C98C.c | D_801F4E4C | D_801F4E54 | D_801F4E64 | D_801F4E6C | `scratch/port_ov_SC07_006.c` | **0** |
| ov_SC07_007 | src/ov_SC07_007/ov_SC07_007_jr_8013C98C.c | D_801C65B4 | D_801C65BC | D_801C65CC | D_801C65D4 | `scratch/port_ov_SC07_007.c` | **0** |
| ov_SC07_010 | src/ov_SC07_010/ov_SC07_010_o2b.c | D_801A6AAC | D_801A6AB4 | D_801A6AC4 | D_801A6ACC | `scratch/port_ov_SC07_010.c` | **0** |
| ov_SC07_011 | src/ov_SC07_011/ov_SC07_011_jr_8013C98C.c | D_8018F144 | D_8018F14C | D_8018F15C | D_8018F164 | `scratch/port_ov_SC07_011.c` | **0** |

All 7 report `score 0 (OTHER; mine 141 ins, target 141) — MATCH`. The raw outputs are `scratch/port_<alias>.res`.
Each result echoes its own TU and function name. I took the global map from each copy's own tree body (the extern lines
and their uses at `p = …`, `gte[0] = …[param_1]`, `= -1` and `= any`), not from address arithmetic alone.

Negative control (the instrument scores the text, not the tree): `scratch/negctl_SC07_010.c` is the ov_SC07_010 port
with the stORGB asm put back to the header `gte_stORGB(&gte[2])`. It scores **13** (COUNT, 140 vs 141). That matches
c47's single-lever `s2_ldasm` row (13), so the port behaves as c47 measured.

(a)–(e): nothing new. The residual, the pass reading (`sched.c:1957` volatile-asm barrier, `loop.c:1631` hoist
threshold, `sched.c:2490`/`2539-2544` birthing priority) and the alternatives (P3 `$2` pin, P2c volatile launder) are
c47's and apply unchanged to these copies. c47 proved P3 and P2c only on ov_SC04_011 and ov_MAIN_012; I did not re-run
them on the other five.

(f) Method note: the pack brief's `git grep -l func_8013D9B0 -- src | xargs grep -l '!FAKE'` returns ~400 files,
because every file that CALLS the function also matches. Grepping for the definition `^void func_8013D9B0(` in the named
overlays gives exactly the 7 TUs (ov_SC07_010's copy is in `ov_SC07_010_o2b.c`, not a `_jr_8013C98C.c`). Three more
copies (ov_SC03_126, ov_SC04_021, ov_SC05_019) instantiate the shared `src/shared/ov/func_8013D9B0__4b66f7ea.h`. They
are out of this pack's scope and I did not touch them.

Scratch: `scratch/copies.txt` (alias → TU), `scratch/port_*.c/.res`, `scratch/negctl_SC07_010.c`.
