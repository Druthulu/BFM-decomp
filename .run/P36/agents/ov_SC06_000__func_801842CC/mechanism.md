# func_801842CC (ov_SC06_000_jr_8017AE2C.c) — e28, P36 T7 S104

**Score: 24 free (sweep best 5) -> 0 with ZERO pins/asm and ONE marked `do { … } while (0)`** (step 8's allowed-but-marked
construct). Tree: 3 levers (pin v1 + pin a0 + launder) -> 0 levers + 1 marked do-while. NOT a strict plain-C close: every
do-while-free spelling I found stays at >= 21 (see (e)).

The same text closes the class's two other copies (`--try` 0 each; rename + the copy's own constants):
ov_SC03_024 `func_80182108` (identical) and ov_SC03_014 `func_801889B4` (`z -= 0x28`, `0xFFFD0000`) —
scratch/copy_80182108_dw.c, scratch/copy_801889B4_dw.c.

Alternative at 0 (kept for the coordinator's choice): the tree's shape with ONE pin, `register s32 v0 __asm__("v0")` on
the reused variable, launder and the v1/a0 pins deleted — scratch/body_onepin.c (also 0 on both copies:
scratch/copy_80182108.c, copy_801889B4.c). And two pins (v1, a0) + no launder: scratch/t4.c.

## (a) Residual
COUNT-equal register rotation in the loop body: free text x/(x&4) in `a0`, d in `v0`, the +E value in `v1`; the target has
x in `v0`, d in `v1`, +E in `a0`, and (consequence) `sh v0,52(a1)` sinks below the `lui v0` constants. Plus
`addu v0,v0,s0` vs the target's `addu v1,s0,v1`.

## (b) Passes and decisions (PROVEN on dumps: scratch/dumps_free, dumps_c1, dumps_c2, dumps_e2, dumps_h1; localalloc_sim)
1. **local-alloc** (eligibility local-alloc.c:472 = one block AND one death; qty order :1486-1507; find_free_reg lowest
   free). In the free text ONE variable `v0` holds x, x&4, the +6 value, the +A value and the sign-extended result: it
   dies in 4 places -> global. Block 2 then has two local qtys, d (33846) and +E (15000): d takes `$2`, +E `$3`, global
   gives v0 `$4`. The target needs a `$2` holder that local-alloc SEES.
2. Giving x its own variable `t` makes THREE local qtys, t=q0, +E=q1, d=q2; the three-qty switch (it compares qty
   NUMBERS 0/1/2 while swapping POSITIONS, :1489-1500) orders them [t, d, +E] -> `$2/$3/$4`, the target's
   (localalloc_sim on dumps_h1: q0 37500 v0, q2 33846 v1, q1 20625 a0, 0 mismatches).
3. **sched1** then breaks it. `priority()` (sched.c:1425) = max over LOG_LINKS of pred priority + cost - 1. With x in the
   same pseudo as the +6 load, that load carried REG_DEP_ANTI links to the x uses (priority 2) and stayed after the d
   chain; with `t` split it has no predecessor, priority 1, and is hoisted above the d chain (dumps_c2 trace T-11:
   "58 (2) 62 (1)" -> 58), overlapping t, so global cannot give the reused `v` `$2`; the subu then gets 2, the `sll d,16`
   ties the +E store at 2 and the store wins the potential-hazard tie (schedule_select sched.c:2616-2686, "insn 68 has a
   greater potential hazard"). Needs 1-2 (x its own single-death local) and 3 (x sharing the +6 load's pseudo) contradict
   in plain C.
4. **The do-while**: its NOTE_INSN_LOOP_BEG/END are sched1 barriers (sched.c:2053-2080: the insn after a loop note gets a
   dependence on every earlier set/use, `reg_pending_sets_all`, `flush_pending_lists`). LOOP_BEG makes the +6 load depend
   on the d chain (stays after it); LOOP_END makes the +E store the barrier, so the sign extension and everything after
   it must follow the store. dumps_h1's block-2 trace is serialised to single-element ready lists. One note is not enough:
   a lone barrier before the +6 load (scratch/e1-e5.c) scores 2 — the barrier insn is then the LOAD, every later insn
   inherits its latency (+40 gets priority 3) and the +E store again ties the `sll` and wins by potential hazard.
5. `addu v1,s0,v1`: expand_binop swaps a commutative op whose target equals op1 (optabs.c:409-418), so `v1 = s0 + v1`
   became `(plus v1 s0)`; one expression `d = i + t * 3 - 0x2A` keeps the counter first. The launder's only job was to keep
   combine from turning `(v0<<1) + v0` (disjoint bits of `x & 4`) into `or` (score 1 without it, scratch/t1.c); `t * 3`
   in one expression keeps `addu` — proven on bytes; which combine test declines the ior was NOT dumped.

## (c) Moves (body.c)
- x split into its own `t = *(u16 *)(arg0 + 0x84) & 4;` (the rest of the reused variable is `v`);
- `v1 = v0 * 2; launder; v1 = v1 + v0; v1 = s0 + v1; v1 = v1 - 0x2A;` -> `d = i + t * 3 - 0x2A;`;
- the +6 load and the +E update wrapped in a marked `do { v = *(u16 *)(e + 6); z += 0x28; *(u16 *)(e + 0xE) = z; } while (0);`
- readability: `if (e != 0) { … }` instead of `continue`, `v = (s16)d;` instead of `<< 16`/`>> 16`, `v = -(v << 7);`,
  `*(u16 *)(e + 0x34) = v + 0x1000;` — each proven neutral on bytes (scratch/g3, g4, g8, g9, g10 -> h1 = body.c).
- Not neutral (keep as written): `*(u16 *)(e + 6) = v - d;` (21), `*(u16 *)(e + 0xE) = z + 0x28;` inside the do (21),
  `*(u16 *)(e + 0xA) -= 0x20;` (30).

## (d) Generator proposal
When a register residual needs a variable SPLIT for local-alloc (a multi-death local, :472) but the split lets sched1
hoist a load that the shared variable used to pin with anti-dependences, wrap [that load .. the next statement group the
hazard tie reorders] in a marked `do { … } while (0)` — and try the two pins -> one pin on the reused variable as the
lever-count fallback.

## (e) What did not work (bytes)
- 2160-body plain-C sweep (scratch/gen.py -> gen_results.txt): x split / fused, three d spellings, three +E spellings,
  +6 and +A updates inline / via temp, both sign-extension spellings, all 6 field-update orders, +E load before/after
  the x load: best 21. s16 `d` (d1-d5.c): 21-27. Single pin on v1 or a0 (t7/t8.c): 21.
- do-while around the d chain only, empty do-while, do-while around the +6 load only (e1-e5.c): 2.
- do-while around only the +40 with the +6 load before it (f3.c): 21.

## (f) Method
Counting first said "no missing instruction"; alloc_table.py was the wrong tool (the decider is local-alloc) —
`tools/localalloc_sim.py` + the `.sched` trace settled it. The method has no row for "a variable reuse that the
SCHEDULER needs (anti-dependences) but LOCAL-ALLOC forbids (multi-death)"; that contradiction is what the tree's pins,
the one-pin fallback and the do-while each resolve.

## (g) Structs
Plausibly NO for this decision: typing `e` as an entity struct (`e->x -= d; e->y -= 0x20; e->z += 0x28; …`) produces the
fresh-temp form (the sweep's inline `*(u16 *)(e + K) -= …` spellings: 21+). The aggregate channel (expr.c:4568-4577) only
changes MEMORY dependences; here every load/store pair is already disambiguated by base+offset (memrefs_conflict_p) and
the deciding links are a REGISTER anti-dependence and sched1's loop-note barrier. Not tested with a body-local struct.
