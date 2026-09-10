# func_80136334 (`src/ov_SC04_011/ov_SC04_011_jr_80135D20.c`) — de-lever, T7 agent

**RESULT: score 0 — MATCH, 161/161 instructions, byte-identical.** All four NEEDED lever sites removed
(pin `$12` @943, launder @953, barrier @988, keepalive @994). Best text: `PACK/body.c`.
(Lever-free start 24; the mechanical search's best was 2 and needed a `do { } while (0)`.)

---

## (a) The residual in one sentence

Three independent residuals sat on top of each other: the lever-free body was **three instructions SHORT**
because `jump_optimize`'s cross-jump merged the two `if (a1v & 1)` arms' trailing `sh v0,4(v1)` (the arms had
become register-identical after `sched2` hoisted `D_801152AC = ±0xFFF` over the `D_801909C4[2] = a2v ± 2`
store), and the two parameter copies read the **copy** instead of the incoming argument register
(`andi v0,t4,0x1` / `sll v0,t3,0x10` where the target has `andi a1,a1,0x1` / `sll v0,a2,0x10`), because
`cse` had merged each `xNv = argN` pair into one quantity.

## (b) The passes and the decisions, with `file:line`

Three separate decisions, each read in `tools/reference/gcc-2.7.2/` and each then proven on bytes.

**1. `output_dependence`, `sched.c:868-882` — why the two stores were free to swap (the *count*, and the `barrier` lever).**
```c
  return ((MEM_VOLATILE_P (x) && MEM_VOLATILE_P (mem))
      || (memrefs_conflict_p (...)
          && ! (MEM_IN_STRUCT_P (mem) && rtx_addr_varies_p (mem) && GET_MODE (mem) != QImode
                && ! MEM_IN_STRUCT_P (x) && ! rtx_addr_varies_p (x))       /* sched.c:876-878 */
          && ! (MEM_IN_STRUCT_P (x) && rtx_addr_varies_p (x) && ...)));
```
`D_801909C4[2] = …` expands to `(mem/s:HI (plus (reg 171) (const_int 4)))` — `MEM_IN_STRUCT_P` **set** and the
address **varies**. `D_801152AC = …` on a plain scalar `extern s16` expands to `(mem:HI (symbol_ref))` —
`MEM_IN_STRUCT_P` **clear** and the address does **not** vary. That is exactly the first exclusion clause, so
gcc declares the two stores independent, `sched_analyze_1` records no `REG_DEP_OUTPUT`, and `sched2` is free to
hoist the cheap `li 4095` chain into the `lw`'s load-delay slot. Doing so makes both arms end in the identical
`sh v0,4(v1)`, and `jump_optimize (…, cross_jump = 1)` (`toplev.c:3142`) then merges that tail — **-3 insns**.
The tree's `__asm__ __volatile__("")` barrier existed only to stop that hoist.

*Proof, `PACK/scratch/dumps_n3/n3.i.lreg`*: after the rewrite the same store prints as
`(insn 265 … (set (mem/s:HI (symbol_ref:SI ("D_801152AC"))) (reg:HI 175)) … (insn_list:REG_DEP_OUTPUT 258 …))`
— `mem/s` now set on both sides, and the **`REG_DEP_OUTPUT` on insn 258** (the `D_801909C4[2]` store) is the
dependence that pins them in source order in both arms. No note, no barrier, no displaced instruction.

**2. `make_regs_eqv` / `canon_reg`, `cse.c` — why `arg1`/`arg2` were read through the copy (the `launder` and `$12` levers).**
`a1v = arg1;` is `(set (reg Q) (reg P))`; cse enters Q into P's quantity and, because Q outlives the cse basic
block and dies later than P, makes **Q canonical**, so the *first* use `arg1 & 1` is rewritten to read Q. Q is
live to the end of the function, so it cannot be the incoming hard register: local-alloc gives it `$t3`/`$t4` and
emits `andi v0,t4,1`. In the target the two are **distinct quantities**: P stays tied to `$a1` by
`combine_regs` through the entry copy, dies at the `andi`, and the `andi`'s destination ties to it —
`andi a1,a1,0x1`. MIPS has **no `PROMOTE_MODE`** (`config/mips/mips.h:2622` is only a comment), so declaring the
local `u16`/`s16` makes it a genuine HImode pseudo; the copy is still one `move`, but the modes differ, cse never
equates them, and the parameter keeps its own quantity. `(s16) arg2` behaves identically (`sll v0,a2,0x10` from
the parameter, not from the copy).

**3. `qty_compare` / `allocno_compare` — the two knock-on effects I had to avoid, not create.**
`local-alloc.c:1579-1596` (`pri = floor_log2(n_refs) * n_refs * size / (death - birth) * 10000`) decides which of
the two block-local quantities in an arm — the reloaded `D_801909C4` pointer and the `a2v ± 2` value — takes `$v0`;
`global.c` `allocno_compare` decides whether `a1v` or `a2v` takes `$t3`. Both are why the mechanical search's
`do { … } while (0)` stalled at 2: a `do`-while's `NOTE_INSN_LOOP_BEG` is both a sched barrier **and** a
`loop_depth` bump, and `flow.c` weights `reg_n_refs` by `loop_depth` (`flow.c:2067/2315/2501`), so wrapping the
`a2v` store inflated `a2v`'s refs from 3 to 4 and flipped `$t3`/`$t4` (measured: the `.greg` line
`;; 12 regs to allocate: … 80 76 75` with `75 in 12  76 in 11`). Making the dependence real instead of noting a
loop leaves every counter alone, so neither knock-on happens.

## (c) The moves that closed it

Three moves, all inside the function definition (the `extern` declarations are block-scope, so the bank stays BODY-ONLY):

1. `extern s16 D_801152AC;` → `extern s16 D_801152AC[];`, and both writes → `D_801152AC[0] = ±0xFFF;` — sets
   `MEM_IN_STRUCT_P` on the scalar store so `output_dependence` (`sched.c:876`) pins it behind the
   `D_801909C4[2]` store; replaces the **barrier** and the **keepalive**.
2. `s32 a1v;` → `u16 a1v;` — splits `a1v` from the `arg1` parameter quantity in cse; replaces the **launder**.
3. `s32 a2v;` → `s16 a2v;` — the same split for `arg2`; replaces the **`$12` pin**. Because `a2v` is now exactly
   `(s16) arg2`, the two `(s16) arg2` casts and the `arg1 & 1` test are written as `a2v` and `a1v & 1`, which is
   also the more readable text (each parameter is now read exactly once).

All three are load-bearing; `u16`/`s16` are interchangeable on both locals (all four combinations score 0), and
`*D_801152AC` scores 0 as well as `D_801152AC[0]`.

## (d) GENERATOR PROPOSAL — R19, "the in-struct re-spelling" (new; not R15/R16/R17/R18)

> **When the residual is COUNT with *mine* shorter than the target, and the function contains an `if`/`else` whose
> arms write the same two memory locations in opposite order — one through a pointer/array (`p[k] = …`) and one a
> plain scalar global — re-spell that global's block-scope `extern T X;` as `extern T X[];` and its writes as
> `X[0] = …`, so `MEM_IN_STRUCT_P` matches on both and `output_dependence` (`sched.c:868-882`) pins the pair in
> source order.**

It is a one-line declaration rewrite with a mechanical trigger (a scalar `extern` written in the same brace block
as a `p[k] =` store), it costs zero instructions, and it is the **readable** replacement for the whole
`barrier` / `keepalive` lever family — those levers exist to stop exactly this reorder. Two natural extensions the
same rule covers: the inverse (a spurious dependence that should be *broken*, by dropping an array spelling to a
scalar) and applying it to `true_dependence`/`anti_dependence` (`sched.c:831/855`, the identical clause) for a
load hoisted over a store. It should be tried **before** `R7 do-while`, which reaches the same barrier through
`NOTE_INSN_LOOP_BEG` but always disturbs `loop_depth` → `reg_n_refs` → the allocation as well (this body is the
proof: `R7` capped at 2, the dependence at 0).

## (e) What did NOT work, with byte evidence

| attempt | score | why |
|---|---|---|
| lever-free start | 24 (COUNT, 158/161) | the baseline |
| `do { D_801909C4[2] = a2v+2; } while (0)` + `u16 a2v` (the search's best) | 2 | count fixed, but `andi v0,t3,1` ≠ `andi a1,a1,1` |
| the same with `u16 a1v` too | 7 | head fixed, but `loop_depth` inflated `a2v`'s refs → `$t3`/`$t4` swapped on 7 insns |
| `do`-while around `D_801152AC = 0xFFF` instead + both locals narrowed | **4** | count and `$t3`/`$t4` both right; only the then-arm `$v0`/`$v1` roles wrong (`qty_compare`, `local-alloc.c:1579`) |
| `do`-while around the else arm / the whole `if` / `D_801152AA` / `D_801152A8` | 20, 25, 17, 17 | the barrier must sit between *those two* stores |
| plain `{ … }` block instead of `do`-while | 14 | braces emit no note, so no barrier at all |
| `{ s32 t = a2v + 2; D_801909C4[2] = t; }` (and the pointer/both-temp forms) | 5, 5, 5 | the extra SI temp defeats the extend-into-`addiu` combine: `andi v0,t4,0xffff` + `addiu v0,v0,2` |
| declaration order `a2v` before `a1v` | no change (7) | the `$t3`/`$t4` race is `allocno_compare` priority, not the regno tie-break |
| `a1v = arg1;` moved below the `if`/`else` | 2 | the parameter must then live across the branch, so it cannot stay in `$a1` |
| `extern u8 D_801152AC[];` + `(*(s16 *)D_801152AC) = …` | 14 | a cast-deref of an array **does not** set `MEM_IN_STRUCT_P` — only the `[]`/`*` deref of a typed pointer does |
| dropping `s32 frame_pad[2]; (void)&frame_pad;` | 4 (COUNT, 159) | still needed for the 8-byte frame; it is a pre-existing class C/D site, not one of this body's levers |

## (f) Where the method fell short

- **The residual was three stacked residuals and the score is a scalar.** Every single move made one of them worse
  while making another better, which is why a beam search that only keeps improving children stalled at 2. What
  unstuck it was reading the *diff shape* per region (head / then-arm / count) and holding each region's fix fixed
  while sweeping the others — a 3×3 width grid × 8 barrier placements, 60 compiles at 0.8 s. **Suggestion: score
  per diff hunk, not per body**, so the search can hill-climb on one region without regressing another.
- **`--try` prints only the diff.** Reading the target's *whole* 161-instruction stream is what revealed that the
  target's then-arm keeps a `nop` in the load-delay slot — i.e. that `$v0` was doing double duty and the reorder
  was blocked by a register conflict, not by a barrier. I had to build my own `objdump` dump
  (`PACK/scratch/dump.py`). **Suggestion: a `--try --full` that prints both streams side by side.**
- **The pass-dump route was not turnkey for an agent.** `tools/cc1_dumps_tu.sh` wants an `rtu_match --work`
  directory and defaults `DUMP_ROOT` to `.run/P32/t4e`; it also drops the `-I<tu dir>` that this TU's relative
  includes need. I rewrote it as `PACK/scratch/dumps.sh` (splice the body → cpp with `-Isrc/ov_SC04_011` → cc1
  `-dl -dg -df …`). **Suggestion: a `delever_search --dumps TU FN FILE --body` mode**; the `.lreg` `REG_DEP_OUTPUT`
  line is what proved this crack and it took ~15 minutes of plumbing to see it.
- **The scratchpad is shared between concurrent agents.** `$SCRATCHPAD/t.sh` was silently overwritten by another
  T7 agent's helper of the same name mid-run, and one probe batch reported another function's compile errors under
  my variant names. Caught only because the TU in the output line was wrong. **All my scratch lives in
  `PACK/scratch/` instead — the brief should say so.**
- **`sites.txt` said all four levers were NEEDED and that reads as "four independent problems".** It was two:
  one memory-dependence decision (barrier + keepalive) and one cse-quantity decision applied twice (launder + pin).
  A lever census counts *sites*, not *mechanisms*.
