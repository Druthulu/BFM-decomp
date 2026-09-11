# func_8018486C (ov_SC03_091_jr_8018326C.c) — d35, P36 T7 S104

**Result: score 0 with ZERO levers** (3 `$N` pins → 0; the dead `s32 pad[2]` from `body_free.c` stays — the frame
needs its 8 bytes, see (e)). It closed on the FIRST `--try` (`scratch/s1.c` = `body.c`). The same text, with only
the callee names swapped, closes all three other copies at 0 (table at the end).

## (a) The residual
A pure register permutation (117 vs 117 ins; mine→target s4→s2, s5→s6, s7→s5, s2→s7, s6→s4). The decompiler's goto
text keeps the compare constant in ONE explicit local `cmp = 1` (and compares against `flag` in the third loop). That
pseudo ranks 5th in `allocno_compare` and takes `$s2`, which pushes best1/val1/val2/best2 one register along.

## (b) Pass and decision
Two effects, both from the loops being REAL loops (the `for` gives NOTE_INSN_LOOP_BEG/END, `stmt.c:2171`) rather
than backward gotos:
1. **loop.c invariant hoisting** (`scan_loop`, `loop.c:702` `invariant_p (src)` → `move_movables` `loop.c:1529`): with
   a literal `== 1` in each loop, each loop gets its OWN hoisted constant pseudo (r85, r88, r91 in `scratch/dumps_st`),
   each short-lived with few refs → priorities 1875/1875/682, allocated LAST: r85 and r88 get the left-over `$s7`
   (the target's `li s7,1` in loops 1 and 2), r91 gets `$s3` (flag is dead in loop 3 — the target's `bne v0,s3`).
   The goto text has no loop notes, so nothing is hoisted and the decompiler faked the hoist with `cmp`/`flag`.
2. **flow.c loop-depth weighting** (`flow.c:1400-1403` raise `loop_depth` at the notes; `flow.c:2067`
   `reg_n_refs[regno] += loop_depth`): refs inside the loops count double. cur 17→29 refs, i 12→21. With
   `allocno_compare` (`global.c:594-607`, floor_log2(refs)·refs/live) the order becomes
   `74 77 73 81 78 80 76 75 79 85 88 91` → cur s0, i s1, best1 s2, flag s3, val2 s4, val1 s5, best2 s6, consts s7/s7/s3
   = the target exactly (`.greg` Register dispositions, `scratch/dumps_st/*.greg`; goto: `scratch/dumps_gt/`).

Proven on bytes: both moves are needed — structured loops but keeping the `cmp` local: 18 (`scratch/s3_cmpvar.c`,
113 ins, the hoist disappears because cmp is a variable); goto text with literal `== 1`: 63 (`scratch/s4_goto_lit.c`,
no hoist, `li` per test). The pass attribution (hoist + ref doubling) is read from the dumps' allocation tables
(`tools/alloc_table.py st|gt func_8018486C scratch`), not separately bisected.

## (c) The move
The decompiler goto chain → STRUCTURED C: three `for (; i < 0x60; i++, cur += 0x10C)` loops, the found-arm as
`{ ...; flag = 1; break; }` (loops 1 and 2), `if (!flag) { ...; return; }` between them, the `t == 0` goto as an
if/else, every compare against the literal `1` (the `cmp` local deleted). Note the game bug the bytes preserve: after
loop 1 breaks, loop 2 starts at the SAME `cur` (no step), so best2 always = best1 when found in loop 2.

## (d) Generator proposal
When a body has backward-goto loops of the shape `L: if (f(p) == c) goto X; i++; p += K; if (i < N) goto L;` with `c`
a local assigned a constant just before the loop, rewrite each as `for (; i < N; i++, p += K) { if (f(p) == CONST) {
<X's block without its goto>; break; } }` and substitute the constant for `c` (delete `c`) — loop notes give loop.c a
per-loop hoisted invariant and flow.c's doubled in-loop refs, which the goto text can only fake with a pinned local.

## (e) What did not work / notes
- `scratch/s2.c` (s1 without `s32 pad[2]`): 20, frame 56 vs 64. The 8 dead frame bytes stay as the project's
  accepted dead-local idiom (cookbook idiom 6; d8's func_80186440 in this same TU banked with `s32 unused[2]`). I did
  not find what the original's 8 bytes were.
- The regen families (R2–R37, best 18–21) all mutate the goto text; none produces a `for` with `break`.

## (f) Where the method fell short
Nothing — step 14's "a goto chain → structured C, try it EARLY" closed this on the first compile. The fifth such close
this session; the goto→structured rewrite deserves to be a generator (every one so far was an agent's hand rewrite).

## (g) Structs
Neutral here, tested on bytes: a body-local `struct Ent { u8 raw[0x10C]; }; extern struct Ent D_801202A0[];` with
`struct Ent *cur/best1/best2` and `cur++` also scores 0 (`scratch/s5_struct.c`). D_801202A0 is the 0x60-entry,
0x10C-byte entity table (func_8012A908, func_801787D4 walk it the same way); a real `Entity` struct would make this
body readable but the lever here was control-flow shape, not an aggregate-vs-scalar access.

## Copies (all `--try` 0 with this text, callee names swapped)
| function | TU | file |
|---|---|---|
| func_8018486C | src/ov_SC03_091/ov_SC03_091_jr_8018326C.c | PACK/body.c |
| func_80183CE8 | src/ov_SC03_089/ov_SC03_089_jr_8017CA80.c | PACK/scratch/copy_SC03_089_func_80183CE8.c (no body-local D_801202A0 extern: file scope has it) |
| func_801839C4 | src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c | PACK/scratch/copy_SC03_090_func_801839C4.c |
| func_80181858 | src/ov_SC03_104/ov_SC03_104_jr_8017CA80.c | PACK/scratch/copy_SC03_104_func_80181858.c |

Callee map (test / select / first call): 091 80184A40/80184A98/80184AE4; 089 80183EBC/80183F14/80183F60;
090 80183B98/80183BF0/80183C3C; 104 80181A2C/80181A84/80181AD0.
