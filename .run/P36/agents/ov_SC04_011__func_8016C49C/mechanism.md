# func_8016C49C (ov_SC04_011_jr_8016AB6C.c:2700) — CLOSED, score 0

Final: **score 0 (MATCH, 172/172 instructions, byte-identical)** from a seed of 34.
Body: `PACK/body.c` — **one line changed** from `body_free.c`.

## (a) The residual in one sentence

Every one of the 34 differing words was a *pure two-way rename of two callee-saved registers*
(`s2->s1 x22, s1->s2 x11`, class MIXED, `mine 172 ins, target 172`, not one instruction added,
removed or moved): my build put `param_1` in `$s2` and the loop counter / `iVar5b` in `$s1`, the
target the other way round — i.e. `global.c` visited the two allocnos in the opposite order.

## (b) The pass and the decision, with `file:line`

Pass: **`global_alloc`** (`tools/reference/gcc-2.7.2/global.c`), fed by **`life_analysis`**
(`flow.c`). Both read from the pinned cc1's own dumps (`-dl -dg`), not from theory.

1. `global.c:546` — `qsort (allocno_order, max_allocno, sizeof (int), allocno_compare);`
2. `global.c:587` — `allocno_compare`'s priority is
   `(floor_log2 (n_refs) * n_refs / live_length) * 10000 * size`.
3. `global.c:904` — `find_reg` then colours in that order; MIPS declares no `REG_ALLOC_ORDER`, so
   it is plain first-fit over the regnos, and *whoever is compared first takes `$s1`*.

The `.greg` dump prints exactly that order on its `;; N regs to allocate:` line, so the reading is
checkable against a known-true case. Lever-free seed (`dumps_base`, my extended `alloc_table` view):

```
;; 8 regs to allocate: 81 76 80 73 74 140 75 84          <- the qsort order
  r81 psVar3   refs=11 live=14  pri=23571  -> $s0
  r76 sVar1    refs=3  live=4   pri=7500   -> $v0
  r80 iVar4    refs=5  live=15  pri=6666   -> $s1   <<< wins the race
  r73 param_1  refs=23 live=141 pri=6524   -> $s2   <<< loses it by 142/10000
  r74 iVar5    refs=8  live=67  pri=3582   -> $s3
  r140 iVar5b  refs=6  live=43  pri=2790   -> $s1  (no conflict with r80)
  r75 iVar6    refs=4  live=41  pri=1951   -> $s4
  r84 (0x30)   refs=3  live=26  pri=1153   -> $s5
```

Reproducing those eight priorities by hand from the formula gives the printed order exactly, so the
instrument is sound. **The whole 34-point residual is one `qsort` comparison, decided by 142 units
out of 6666 — 2%.**

The move therefore has to raise `reg_n_refs[73]` from 23 to 24 (`pri` 6524 -> 6808 > 6666) without
emitting an instruction. That is possible because **`reg_n_refs` is a LOOP-WEIGHTED count, and it is
computed before `combine` and before `sched1`** (`toplev.c:2983` `flow_analysis`, then `:3004`
`combine_instructions`, `:3033` `schedule_insns`, `:3052` `local_alloc`, `:3080` `global_alloc`):

* `flow.c:434` — `find_basic_blocks` starts its scan at **`depth = 1`**;
* `flow.c:440-443` — `depth++` on `NOTE_INSN_LOOP_BEG`, `depth--` on `NOTE_INSN_LOOP_END`;
  `:456`/`:471` store it per block, `:1385` reloads it per block for the backward scan;
* `flow.c:2067` (`mark_set_regs`) and `flow.c:2501`/`:2711` (`mark_used_regs`) —
  `reg_n_refs[regno] += loop_depth;`.

So **a reference that sits between a `NOTE_INSN_LOOP_BEG`/`_END` pair is counted twice.** The whole
seed table is arithmetic on that rule, which is how I checked it before spending a compile: r84 (the
loop-invariant `0x30`) has 1 def outside + 1 use inside = `1 + 2*1 = 3` refs; r81 (`psVar3`) has 1 def
outside + 5 occurrences inside = `1 + 2*5 = 11`; r80 (`iVar4`) `1 + 2*2 = 5`; r73 (`param_1`)
`21 + 2*1 = 23`. All four match the dump.

## (c) The move that closed it — one line

* Wrap the function's **last statement** in the canonical statement-macro idiom:
  `param_1[1] = sVar1;` -> **`do { param_1[1] = sVar1; } while (0);`** (line 2777).

`do {} while (0)` emits a `NOTE_INSN_LOOP_BEG`/`_END` pair around that store, so the `param_1`
reference in it is weighted 2 instead of 1; `reg_n_refs[73]` 23 -> 24, `pri` 6524 -> 6808, the
`qsort` order becomes `81 76 73 80 74 140 75 84`, `find_reg` hands `param_1` `$s1` and the counter
`$s2`, and every one of the 34 words falls into place. Proven on bytes:

```
win: order [81, 76, 73, 80, 74, 140, 75, 84]
  r73 refs=24 live=141 pri=6808     <- +1 ref, nothing else in the table moved
  r80 refs=5  live=15  pri=6666
-> score 0 (OTHER; mine 172 ins, target 172) — MATCH
```

**The control that proves it is the notes and not the scope:** the *plain block* at the same site,
`{ param_1[1] = sVar1; }`, leaves the table untouched (`r73` refs=23, order `81 76 80 73 …`) and
scores **34** — the seed's score, to the point. A brace block emits no loop notes; only `do/while`
does.

**Why the tail position is free.** `do/while` notes are also a `sched1` region barrier, which is why
R18's docstring records that R7 "always costs one displaced insn". Measured here across all 47
`do-while` sites in this body: 22 of them change the instruction *count*, and of the 25 that keep 172
instructions only the **last statement of the function** scores 0 — the next best terminal-ish sites
(`@2714`, `@2748`, `@2763`) score 2 with class ORDER, i.e. the barrier displaced a pair. At the final
statement there is nothing left to schedule across, so the barrier is free and only the ref weight
survives. **Position, not site count, is the discriminator.**

## (d) Generator proposal — one sentence

**R19 `loop_note_weights`: when the residual is a pure callee-saved rename (equal instruction counts,
`pairs` only) and the `.greg` priority table shows the two contending allocnos adjacent in
`allocno_order`, wrap in `do { … } while (0);` the LAST statement of the enclosing block that
references the under-weighted pseudo — one candidate, not 47 — because the loop notes double that
reference's `loop_depth` weight in `reg_n_refs` (`flow.c:2067/2501`) and flip `allocno_compare`
(`global.c:587`) at zero instruction cost only in tail position.**

Concretely the generator is R7's do-while spelling made *directed* by a computed quantity that no
current generator uses: read `;; N regs to allocate:` + `Register N used K times across M insns` from
a single `-dl -dg` compile, recompute `floor_log2(K)*K/M*10000`, and emit candidates only where the
smallest `+1 ref` (or `+1 live`) flips a specific adjacent pair — then rank those by *tail distance*
(last statement of a block first), the inverse of the engine's current NEEDED-site distance ranking.
The same table also says when to stop: if no single `+1 ref` / `+1 live_length` closes the gap, the
class is not reachable by a note move at all. It is new against R15 `sink_merges` (a `block_alloc`
quantity move), R16 `constant_holders` (deletes a quantity), R17 `constant_run_splits` (a
`find_free_reg` live-range overlap) and R18 `bystander_moves` (`reg_live_length` via statement
distance): those all move `local-alloc`'s block quantities, this one moves `global.c`'s *priority*,
and it is the only one that changes a ref *weight* rather than a ref *position*.

## (e) What did NOT work, with byte evidence

| Try | Score | Why |
|---|---|---|
| R15 `sink_merges` — `param_1[1] = sVar1` sunk into both arms (the tool's own candidate, byte-for-byte) | **40**, `mine 173` | duplicates the `sh` at the merge; the target has one. The `-> 1` in `history.txt` is **not reproducible from the lever-free seed** — I ran `dl.sink_merges` itself and scored its exact text. |
| Plain block `{ param_1[1] = sVar1; }` @2777 | **34** | the control above: no loop notes, table unchanged. |
| Swap the two loop-init declarations (`psVar3` before `iVar4`) | 35 | moves the *counter's* birth the wrong way: its `live` 15 -> 14 (pri 6666 -> 7142), `psVar3` 14 -> 15. Widens the gap. |
| `int iVar4` instead of `short` | 41, `mine 169` | drops the `sll/sra` truncation; three instructions gone. |
| Both loop locals declared at function top (`D`) | 34 | RTL identical; table identical. |
| R3 init-split of `param_1` (`u16 *param_1; param_1 = …;`) | 34 | ditto. |
| Parameter re-typed `u16 *param_1_arg` | 34 | ditto — and **unbankable anyway**, see below. |
| Nested `if`s instead of `&&` in the loop | 34 | ditto. |
| R14 `param-width param_1_arg s32->u16` (the move `history.txt` credits for `best 1`) | not pursued | **cannot be banked.** The bank is body-only, and this TU's definition is not the only declaration: `extern s32 func_8016C49C(s32 param_1_arg);` appears in 20+ sibling TUs (`ov_SC04_011_jr_8017AE2C.c:1846`, `…_jr_80171B4C.c:1863`, `ov_SC03_099_*`, `ov_SC06_008_*`, …) and the body is also instantiated through `src/shared/ov/func_8016C49C__0db10db0.h`. `delever.protos_outside_definition` only inspects the *current* TU, so R14 still offers this candidate here even though the width change would have to leave the definition. Not needed — the answer above needs no signature change. |

## (f) Where the method fell short — and the fix, with evidence

**The winning candidate was generated by the existing tooling in every one of the six runs and thrown
away unscored, every time.**

`delever.recipe_candidates` builds 439 candidates for this body and sorts them by *distance to the
nearest NEEDED site* (`delever.py:2520-2529`); the only NEEDED site is the pin on the declaration at
line 2707, and the answer is at line 2777 — the farthest statement in the body. Measured:

```
total candidates: 439
rank of "do-while @2777": 438      (cap = 48)
```

Dead last of 439, cut by `--cap 48` in g3, g5, s1, s2, s4 and s7 — together ~4,300 compiles that
could never have reached a one-move answer. Two concrete fixes:

1. **The NEEDED-site distance heuristic is exactly backwards for the register-order class.** A pin on
   a *declaration* says which VALUE is mis-coloured; it says nothing about which STATEMENT to weight,
   and for a `global.c` priority flip the cheapest statement is the one furthest from the declaration
   (the tail, where the `sched1` barrier is free). For residual class `MIXED`/`pairs`-only, rank by
   *tail position*, or simply never let `cap` drop the last statement of a block.
2. **The engine never reads the allocator's own answer.** One `-dl -dg` compile (0.3 s, the same cost
   as one scored candidate) prints `;; N regs to allocate:` and the refs/live of every pseudo; from
   those eight numbers the required move — "+1 ref on r73" — is arithmetic, and the search space
   collapses from 439 blind candidates to one. I spent ~15 compiles total, and the reading came
   first. `tools/alloc_table.py` already parses these dumps but prints only the callee-saved holders
   and drops the `;; N regs to allocate:` order line, which is the single most informative line in
   the `.greg` dump; it also missed 7 of the 8 allocnos here because its `Register N in M.` regex does
   not match this dump's `;; Register dispositions:` block. Both are small fixes and would make the
   instrument usable as the first step of every `regalloc-order` body.

**Claims proved on bytes:** the priority table and its arithmetic (reproduced by hand and matched
against the `.greg` order line, twice — seed and winner); the `+1 ref` from the loop notes; the
plain-block control; the free-only-in-tail-position result (47 measured sites); the R15 refutation.
**Claims NOT proved:** that `sched.c:2058-2074` is the specific barrier making the non-tail
do-while sites cost 2 (I measured the cost, I did not read the `.sched` dump for it); and that the
original source used a statement macro here — that is only the natural reading of why a
`do { … } while (0)` sits around this one store.
