# func_8013DD68 (ov_SC04_011) — T7 agent c20 (re-draw)

**Final: 0** — 187 against 187, byte-identical (`--try … body.c --body` → `score 0 … MATCH`). No pin, no asm, no added
volatile, no `do { } while (0)`, no zero term. Around 10 compiles. The earlier agent's files are kept in
`scratch/prev_body.c`, `scratch/prev_mechanism.md` and `scratch/prev_body_altB.c` (that attempt reached 2 with
`do { } while (0)` wraps).

`body.c` is `body_free.c` with 3 lines changed:

```
-    ((P_TAG_8013DD68 *)p)->addr = OTE->addr;          (x3: before, inside and after the loop)
+    ((P_TAG_8013DD68 *)p)->addr = *(u32 *)OTE;
-            uVar2 = q[-7];
-            *(u16 *)((int)puVar10 + -6) = 0x7800;
-            *(u8 *)((int)puVar10 + -7) = (u8)uVar2;
+            *(u8 *)((int)puVar10 + -7) = (u8)q[-7];
+            *(u16 *)((int)puVar10 + -6) = 0x7800;
```

Only the addPrim inside the loop needs the `*(u32 *)` read (`scratch/c/v4.c`, which changes just that one, also
scores 0). I changed all three so the three addPrims read the same way. The ones before and after the loop are
byte-neutral: `v1` (loop only) and `v2` (all three) both score 10 before the scheduling move.

## (a) The residual in one sentence

The loop counter `iVar14` and the loop's hoisted `0x00ffffff` addPrim mask swap `$a3`/`$t0`. That is 9 instructions,
plus scheduler knock-on inside the loop. The cause: the mask's allocno sorts ahead of the counter because it carries
**two phantom references**. They come from a bit-field read feeding a bit-field store, which masks twice. Combine later
removes the second mask but never takes back the reference count.

## (b) The pass and the decision (read from source, proven on the dumps)

* `expmed.c:1456-1471` `extract_fixed_bit_field`: reading the unsigned 24-bit `addr` field of `OTE` ANDs the loaded
  word with `0xffffff`.
* `expmed.c:667-683` `store_fixed_bit_field`: `must_and`, storing a non-constant SImode value into a 24-bit field ANDs
  it with `0xffffff` again.
* loop.c hoists the invariant `0x00ffffff` into one pseudo, so both ANDs read the register and cse cannot fold them.
  At flow the mask has 3 uses inside the loop (`.flow`: insns 242, 247, 272). `flow.c:2067/2315` add `loop_depth`
  (2) for each: 1 set + 3×2 = **7 refs**.
* combine turns `(and (and x r148) r148)` into one AND (insn 247 in `.combine`), but **`reg_n_refs` is not adjusted**.
  `combine.c:55-57` says so in its own header: "reg_n_refs is not adjusted in the rare case when a register is no
  longer required in a computation".
* sched1 splits the constant into `lui`+`ori` (`sched.c:4830` `try_split`, mips.md:3208 `large_int` split). The
  pseudo then has two sets, so `update_equiv_regs` cannot give it a REG_EQUIV note. Its live length is not doubled
  (`local-alloc.c:1058-1064`), unlike the one-insn `0xff000000`, whose 56 becomes 112.
* `global.c:587-607` `allocno_compare`: `floor_log2(refs)·refs/live·10000`:

| pseudo | what | refs / live | pri | allocated |
|---|---|---|---|---|
| r148 (free) | loop mask, double-ANDed | 7 / 58 | **2413.8** | first → `$a3` (wrong) |
| r79 | `iVar14` | 7 / 81 | **1728.4** | second → `$t0` (wrong) |
| r144 (body.c) | loop mask, single AND | **5** / 58 | **1724.1** | second → `$t0` ✓ |

The `.greg` order line goes from `… 74 148 79 80 …` (free) to `… 74 79 144 80 …` (body.c). All three rows come from
`tools/alloc_table.py` run on `scratch/dumps_{free,v1,v5}`. The margin is 4.3 priority points, and the bytes confirm it.

Reading the OT entry as a plain word (`*(u32 *)OTE`) removes the extract's AND before combine ever sees it. The store
still masks once, and the final code does not change: combine had produced the same single `and` anyway.

**Proven on bytes.** Control `scratch/c/v6.c` has the scheduling move but not the u32 read: 7, pairs
`a3->t0 x5, t0->a3 x4`. `v1` has the u32 read in the loop and no scheduling move: 10, and the register pairs are GONE
(only the `li v0,100` / `lui a0,0xe100` / `andi` order hunk is left).

The second residual is the one the earlier agent already solved (its moves 1 and 2): with `uVar2 = q[-7]` inlined,
the store sits before the `0x7800` store, the `lhu` sits at its use, and sched1's LUID ties fall the target's way
(`sched.c:2428`). Inlining without the reorder (`v3`) is 8; inlining plus the reorder (`v4`/`v5`) is 0.

## (c) The moves, one line each

1. addPrim's OT read written as a word: `((P_TAG_8013DD68 *)p)->addr = *(u32 *)OTE;` (the loop one is load-bearing;
   the other two for consistency) → register swap gone (17 → 10).
2. `uVar2 = q[-7]` inlined into its store, and that store moved above `*(u16 *)(puVar10 - 6) = 0x7800;` → 0.

## (d) GENERATOR PROPOSAL

**When a REG residual swaps a loop-invariant constant's pseudo with another allocno, and the constant feeds a
bit-field store whose source is a bit-field READ of the same width (`a->f = b->f`, the PsyQ `setaddr(p, getaddr(ot))`
/ addPrim idiom), rewrite the source read as a whole-word read (`a->f = *(u32 *)b`).** It removes one phantom
depth-weighted reference, `2·loop_depth`, from the mask pseudo with zero byte cost, because combine would have merged
the double AND anyway (`combine.c:55-57`). More generally: for any register-priority residual, count refs in the
**`.flow`** dump, not only `.lreg`, and look for insns combine deleted; their refs persist into `allocno_compare`. The
opposite lever (spell a field read as a bit-field read to ADD refs) should work for a pseudo that needs to rise.

## (e) What did NOT work / what the earlier reading got wrong (R14)

* The earlier agent's claim "the only reachable move is one more weighted reference on `iVar14`" and "nothing in C
  chooses [the mask's refs]" is **refuted**. The mask's 7 refs are 3 from the two-insn constant (their count) plus
  **3 depth-2 uses, one of them phantom** (they read 2), and the phantom is chosen in C by how the OT field is read.
  Their arithmetic (priority, live lengths, `floor_log2` step) was correct and was the key; the error was counting
  the mask's uses from `.lreg` (after combine) and not `.flow`.
* v3: inlining `q[-7]` without the reorder is 8 (the `lhu v1,0(s1)` / `sb` ordering hunk).
* I did not need the METHOD_S103 moves (implicit handler args, cross-jump, width moves): the residual was a priority
  inversion, and the table settled it.

## (f) Where the method fell short

* `tools/alloc_table.py` prints `.lreg` refs, the value global.c uses, but not WHERE they come from. The decisive fact
  was the gap between flow-time uses (3 in the loop) and post-combine uses (2), and the table cannot show it. Suggest
  a column: "refs at flow vs mentions in the final RTL". A pseudo whose refs exceed its current mentions × depth is
  carrying phantom refs from combine, and the source construct that produced the deleted insn is the lever.
* `residual_moves.md` should get a row: "REG swap, winner is a hoisted constant fed by a bit-field copy →
  whole-word read of the source field."
* The pack worked: reading the earlier agent's arithmetic plus `.flow` got here in about 10 compiles.
