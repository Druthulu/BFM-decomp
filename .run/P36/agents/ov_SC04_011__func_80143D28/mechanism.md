# func_80143D28 (ov_SC04_011_jr_80140608.c) — score 0, MATCH, lever-free

Final text: `PACK/body.c` (also kept as `PACK/body_final.c`). Scored with
`.venv/bin/python tools/delever_search.py --try src/ov_SC04_011/ov_SC04_011_jr_80140608.c func_80143D28 PACK/body.c --body`
→ `score 0 (OTHER; mine 80 ins, target 80) — MATCH`. Nothing was written outside PACK.

## (a) The residual in one sentence

Pure callee-saved permutation with no count or order difference: `iVar3` (the `*(param_1+0x20)` pointer, 7 refs) took
`$s3` and `sVar4` (the 0x1000/shift value, 4 refs) took `$s2`, where the target has them the other way round — i.e. the
two allocnos are adjacent in the global bank and sorted the wrong way.

## (b) The pass and the decision, read from the compiler source

`global.c:587 allocno_compare` sorts the allocnos that `find_reg` then colours in order, lowest free callee-saved reg
first (`global.c:927/947-985`). The key is `global.c:591-597`:

```
  register int pri1
    = (((double) (floor_log2 (allocno_n_refs[*v1]) * allocno_n_refs[*v1])
        / allocno_live_length[*v1])
       * 10000 * allocno_size[*v1]);
```
truncated to `int`, ties broken by allocno number (= regno = declaration order) at `global.c:606`.

`tools/alloc_table.py` on the lever-free body (dumps via `tools/cc1_dumps_tu.sh`, `DUMP_ROOT` inside PACK) gives the two
contenders exactly, and the margin is the tightest one this arithmetic can produce:

| pseudo | var | refs | live | priority |
|---|---|---|---|---|
| r72 | param_1 | 14 | 53 | 7924 → `$s0` |
| r74 | iVar2   |  4 | 19 | 4210 → `$s1` |
| **r84** | **sVar4**  |  4 | 25 | **3200.0** → `$s2` |
| **r73** | **iVar3**  |  7 | 44 | **3181.8** → `$s3` |

`14/44 = 0.31818` vs `8/25 = 0.32000` — 0.57 % apart. Only two integer outcomes flip it: `live(iVar3) ≤ 43`
(`14/43 = 3255`) or `live(sVar4) ≥ 26` (`8/26 = 3076`).

`allocno_live_length` is `flow.c`'s `reg_live_length` (`flow.c:2073`), **overwritten by sched1** at `sched.c:4947`
(`reg_live_length[regno] = sched_reg_live_length[regno]`) — so the number the allocator sorts on is the count of insns
between the def and the last use **in sched1's output order**, and a source move only counts if sched1 keeps it. I
reproduced the 44 and the 25 by hand from the `.lreg` RTL (real insns only, labels and notes not counted, the defining
insn counted) before making any move; both matched exactly, so the model is the instrument.

Where sched1 puts `iVar3`'s `lw` is decided in `rank_for_schedule`, `sched.c:2385`. Both candidates are `birthing`
single-set defs, so `adjust_priority` (`sched.c:2507`, `birthing_insn_p` `:2469`, gated on `reg_n_sets[i] == 1`) raises
both to `max_priority` — the priority test at `sched.c:2395` ties, the last-scheduled-insn class test ties, and the
decision falls all the way through to the last line of the function:

```
sched.c:2428   return INSN_LUID (tmp) - INSN_LUID (tmp2);
```

**The original source order of the two insns is the whole tie-break.** In the `.sched` dump the ready list at T-18 is
`32 11`; insn 32 is the `p->f8` load, insn 11 is `iVar3`'s `lw`; 32 has the larger LUID, so 32 is chosen first in the
backward pass, is emitted one slot *earlier*, and `iVar3`'s `lw` sits at BB0 position 7 → live length 44.

## (c) The move that closed it

**Name `p->f8` as a temp and declare it BEFORE `iVar3`'s own declaration** (one new line; `iVar3`'s declaration slides
down one line, nothing else changes):

```c
    MatEntry *p = &D_80191D88[*(s16 *)(param_1 + 0x70)];
    u16 uVar5 = p->f8;                              /* NEW */
    s32 iVar3 = *(s32 *)(param_1 + 0x20);           /* was the first declaration */
    ...
    *(s16 *)(iVar3 + 0x14) = uVar5;                 /* was  = p->f8 */
```

That gives the `lhu p->f8` insn a **smaller** LUID than `iVar3`'s `lw`. `rank_for_schedule`'s LUID tie-break at
`sched.c:2428` now prefers the `lw`, sched1 emits it one slot later, and:

```
  r84(iVar3) pri=3255.8 refs=7 live=43   <- was 3181.8 / live 44
  r85(sVar4) pri=3200.0 refs=4 live=25   <- unchanged
```

`iVar3` overtakes `sVar4`, takes `$s2`, `sVar4` takes `$s3` → 80/80 instructions byte-identical, **score 0**. The
predicted live length (43) and the predicted flip both landed on the first try, so the reading is proven on bytes, not
inferred.

## (d) GENERATOR PROPOSAL — R19 `first_use_temps`

> When the residual is `REG-callee` with exactly two callee-saved contenders swapped and no count/order difference, read
> both priorities with `tools/alloc_table.py`; if they are within a few percent, take the contender that should have the
> **lower** `$s` number, find the **first statement that uses it**, and hoist the first sub-expression of that statement
> that does **not** mention the contender into a new named temp declared **immediately above the contender's own
> declaration** (moving that declaration down one line) — the temp's producing insn then precedes the contender's def in
> LUID order, sched1's `rank_for_schedule` tie-break emits the def one slot later, and the contender's `reg_live_length`
> falls by exactly one.

Mechanically checkable and cheap: the candidate set is (first-use statement) × (its sub-expressions independent of the
contender), typically 1–3 candidates per body, and the pre-filter is deterministic — compute `floor_log2(R)*R/L*10000`
for both contenders from the `.lreg` dump and emit the move only when `int(floor_log2(R1)*R1/(L1-1)*10000) > pri2`,
i.e. only when a **one-insn** shortening is enough. That predicate would have said YES here before any compile.

### How this differs from R18 `bystander_moves` (its nearest neighbour)

R18 permutes an **existing, textually independent** statement inside a brace block and aims at local-alloc's
`qty_compare`/`find_free_reg` race for block-local (caller-saved) quantities. This move is not reachable by R18:

1. R18 never introduces text. Here the thing that must move earlier is **not a statement at all** — it is a
   sub-expression (`p->f8`) inside `*(s16 *)(iVar3 + 0x14) = p->f8;`. The move *creates* the statement.
2. That statement **mentions `iVar3`**, so R18's conservative textual-independence test forbids moving it past `iVar3`'s
   declaration. The generator has to split the statement first, which is exactly what R18 does not do.
3. Different pass, different decision. R18's documented decision is `local-alloc.c:1579/2158`. This one is
   `sched.c:2428` (a LUID tie-break inside sched1) feeding `sched.c:4947` (live length rewritten) feeding
   `global.c:591-597` (the callee-saved bank order). It is a **global**-allocator move on values that cross a call, not a
   block-local colouring move.
4. R4 `decl-move` is the other neighbour and I proved it is a **no-op here** (see (e)) — moving the declaration alone
   changes the regno and nothing else. The new content is the *split*, not the move.

## (e) What did NOT work — byte evidence

| candidate | score | measured effect |
|---|---|---|
| `sVar4 = 0x1000;` hoisted to be the first statement | **11**, unchanged | priorities byte-for-byte identical (3200.0 / 3181.8): sched1 normalises the constant's position completely — its only successor is in BB11, so it is ready from the start of BB0's backward pass and lands at T-2 whatever the source says |
| `iVar3` declared last of the three (R4 decl-move) | **11**, unchanged | `iVar3` became r83 instead of r73, priorities identical (3200.0 / 3181.8). Confirms `global.c:606`'s declaration-order tie-break only bites on an **exact** integer priority tie (it does not apply here), and confirms that declaration order alone does not move sched1 — the `p->f8` load still has the larger LUID because it is generated by a *statement*, which always follows every declaration |
| the same temp `u16 uVar5 = p->f8;` declared **after** `iVar3` (control for the crack) | **11**, unchanged | live 44 / 25, priorities 3181.8 / 3200.0. **The temp is not what closes it — its LUID position relative to `iVar3`'s initializer is.** This is the control that names the mechanism |
| `sVar4 = 0x1000;` moved *after* the call | 10, class **COUNT**, 78 vs 80 ins | `sVar4` stopped crossing a call (`flow.c:1650` → `global.c:927`), left the callee-saved contest entirely and took `$a1`; the prologue lost the two `$s3` save/restore insns. `iVar3`'s registers *did* match in that build (residual reduced to `a1->s3 x4`), which independently confirms `iVar3` is the loser of a two-way race and not mis-ranked against anything else. Rejected: wrong bytes |

Two things I read but did not need to move (recorded so the next agent skips them): `sVar4`'s `li` gets **no**
`birthing_insn_p` boost because `reg_n_sets != 1` (three sets — `sched.c:2539`), and its BB0 slot is forced (it is the
only insn ready at T-2, between the post-call `lh` and the branch), so the `live(sVar4) ≥ 26` half of the flip window is
not reachable from the source without changing instructions. Only the `live(iVar3) ≤ 43` half was.

## (f) Where the method fell short

- **The pack's `residual.txt` does not carry the numbers that decide the case.** The whole crack was one arithmetic
  comparison (3181.8 vs 3200.0) that took ~4 minutes to produce and then made every subsequent step deterministic. The
  `.lreg` refs/live pair for the swapped contenders should be printed **into the pack** for every `REG-callee` residual;
  it is a single extra cc1 run per body and it turns a search into a calculation.
- **`tools/cc1_dumps_tu.sh` is awkward to point at a candidate body.** It wants a `<dir>/<fn>/t.c` layout and the TU's
  `#include "../shared/…"` lines force a `shared` symlink next to it. I wrote `PACK/dump.sh` (splice `body.c` into
  `tu_free.c`, dump, print the two priorities) — a `--dump` flag on `delever_search.py --try` doing exactly that would be
  worth more than another move family.
- **`tools/alloc_table.py` printed no rows** for this function: it filters on `Register N in M.` lines from the `.greg`
  dump, which this function's dump does not emit for the pseudos of interest, so the callee-saved table came out empty
  and the `unallocated` list was the only output. My PACK copy keys on `crosses N calls` instead and works. Worth fixing
  upstream — an instrument that silently prints an empty table is the "silently narrowed scope" defect class.
- The method's step 1 (read the residual, name the pass) was exactly right and cost 6 compiles total: 4 diagnostic
  candidates + the crack + one minimisation. No search was needed.
