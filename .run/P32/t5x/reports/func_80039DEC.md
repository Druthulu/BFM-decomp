# func_80039DEC (main / src/800_c.c, 74 ins) — Fable T5x report, 2026-09-05

**Verdict: MATCH** — `match_one` 74/74 and `rtu_match` MATCH in the real TU (`src/800_c.c`, decl `extern void func_80039DEC();`).
Draft: `.run/P32/t5x/fable/func_80039DEC.c` (identical to `.run/P32/t5x/work/func_80039DEC/sw2.c`). No pins, no
fences, no launders, no `do{}while(0)`. The `.s` carries no relocation lines (no jal/HI16/LO16), so there is no symbol
identity to cross-check (SYS law 1c) — every immediate was spelled from the target.

## What closed it — the mechanism, read from the compiler

The residual (sonnet-9: 9 ins; permuter: 2 ins) was a clean swap of the two K&R raw-preserve parameter copies:
target puts a2-raw in `$a3` and a1-raw in `$t0`, every draft did the reverse. Both copies are `reg/v:HI` parm pseudos
(73 = a1, 75 = a2; lreg dump insns 8/12) with NO satisfiable hard-reg preference (their sources 74/76 keep `$a1`/`$a2`
and overlap them), so both fall through `find_reg`'s pass 0 (candidates = `regs_used_so_far` only, `global.c:948-951`,
"we never allocate a register for the first time in pass 0") into pass 1, which hands out the LOWEST free register by
number (`global.c:960-985`; MIPS has no `REG_ALLOC_ORDER`). Hence: **whichever of the two is allocated FIRST gets `$7`
(`$a3`), the other `$8` (`$t0`).** The order is `allocno_compare` (`global.c:587-608`):

    pri = floor_log2(n_refs) * n_refs * size / live_length

with `n_refs` from `flow.c:2067` (`reg_n_refs[regno] += loop_depth`) and `live_length` the insn count where the reg is live.

Measured (lreg dumps, `.run/c294/dumps_t5x_9DEC_{s9,sw2}/*.i.lreg`):

| draft | a1-raw (73) | a2-raw (75) | pri(73) | pri(75) | allocated first | greg dispositions |
|---|---|---|---|---|---|---|
| sonnet-9 (`L_merge` + `kind`) | 3 refs / 26 | **3 refs / 45** | 1·3/26 = 1153 | 1·3/45 = 666 | 73 | `73 in 7  75 in 8` (wrong) |
| sw2 (duplicated case tails) | 3 refs / 26 | **4 refs / 41, dies in 3 places** | 1153 | 2·4/41 = **1951** | 75 | `73 in 8  75 in 7` (target) |

The target's dispatch (`beq 0x1E` → `slti 0x1F`/`beqz` → `beq 0x14` | `beq 0x28`) is gcc's `emit_case_nodes` balanced
tree for a 3-case `switch` (`stmt.c:4907`, `:5580-5651`; count < 5 → tree, no jump table), relocated in front of the case
bodies by `reorder_insns` at `stmt.c:5055` — which is why the bodies sit in SOURCE order (0x14, 0x1E, 0x28, default) after
the tree. The shared `.L80039ECC` tail (`sb $a3; sb $a0; ori 3; sb $v1`, entered by `j` from L_14 with `addiu $a0,0x18` in
the delay slot and by fall-through from L_28 after `addiu $a0,0x1A`) is jump.c's post-reload CROSS-JUMP (`jump.c:1923`,
`find_cross_jump`/`do_cross_jump`) of two textually identical case tails. So at flow/global-alloc time the
original had THREE `sb <a2-raw>` uses (case 0x14, case 0x28, default) — a2-raw's fourth ref, `floor_log2(4) = 2`, and the
higher priority. Every prior draft merged the two tails at the C level (`goto L_merge` + a `kind` variable pinned to `$4`),
which deleted one `sb` use: 3 refs, `floor_log2(3) = 1`, and a1-raw won `$a3`. Attempt 1's `do{}while(0)` "ref-count
boost" worked by the same arithmetic (`loop_depth` 2 doubles the refs inside the pseudo-loop) — a less natural spelling of
the same lever, and it dragged a1-raw's `ori` inside too in the permuter lineage.

**The `config/wave_exclude.txt` claim "fixed by ARGUMENT POSITION … 2nd param → $a3, 3rd → $t0" is refuted:** sw2 puts the
3rd parameter's copy in `$a3` and the 2nd's in `$t0`, exactly the target. And the T4b NOTES' hypothesis (`local_reg_n_refs`
skipping in pass 0) is not what the code does: `local_reg_n_refs` is consulted only in the kick-out retry when
`best_reg < 0` (`global.c:1108-1160`), which never fires here.

## Variants measured (all natural `switch`, same 0x1E block as sonnet-9)

* **sw1** — one function-scope `u8 *p` assigned in all three cases: FAIL (structural, ~40 mismatched from idx 24). `p` is
  then used in several blocks → `REG_BLOCK_GLOBAL` → one global allocno for all three address temps, which must be ONE
  hard reg; the target has the entry pointer in `$v0` in L_14/L_28 but `$v1` in default (its `$v0` is taken by the
  sign-extended a1 born in the `j` delay slot). Block-local temps are required.
* **sw2** — `case N: { u8 *p = …; … }` block-scope per case: **MATCH 74/74**, rtu MATCH.
* **sw3** — no temp, `((u8 *)a0 + a1 * 26)[k]` written out three times: 3 mismatches, all the final `addu`:
  `addu $v0,$v0,$a0` vs target `addu $v0,$a0,$v0`. cse merges the three address expressions but the canonical form puts
  the shift chain first; the named pointer local `p = (u8 *)a0 + a1 * 26` keeps `a0` as the first operand. Side-lesson:
  when a base+scaled-index `addu` has its operands swapped, name the pointer as a local.

## The permuter "closeness 2" was unsound (R63)

`.run/S79w/permuter/func_80039DEC.c` stores `tmp` in the default path (`pd[0x1F] = tmp`) but assigns it only in
`L_merge` — uninitialized on that path. Its idx-65 `sb $a3` "matched" because the `tmp` pseudo (81, `reg/v:SI`, 5 refs/24)
out-prioritised both parm copies and took `$7` (`.run/c294/dumps_t5x_9DEC_perm2/*.i.greg`: `81 in 7`). The sound
ancestor's real residual was 9, not 2.

## Cookbook harvest (for the coordinator)

* **K&R raw-copy register choice is `allocno_compare` order, not argument position.** Two narrow K&R parms' HI copies have
  no preference and take `$7`, `$8`, … in PRIORITY order (`floor_log2(n)·n/live_length`). To move one to `$a3`, give it
  the ref count the original had — usually by NOT merging duplicated case tails at the C level (write the `switch` as
  the author did; let cross-jump merge them post-reload). A `goto L_merge` + `kind` refactor deletes a ref and can flip
  `floor_log2` (3→1 vs 4→2). Tell: exact-length draft, a pure `$a3<->$t0` swap of `addu $aN,$aM,$zero` copies, target
  tails that look cross-jumped (`j` into a shared tail with a constant load in the delay slot).
* `switch` cases that share an address temp must declare it BLOCK-SCOPE per case (`case N: { T *p = …; }`) when the
  target holds it in different registers per block; a function-scope temp becomes one global allocno.
