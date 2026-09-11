# func_8017E764 (ov_SC06_010_jr_8017A4AC.c) — T7 e26, P36 S104

**Score 0 with ONE marked lever** (minimum-lever, METHOD step 9): levers 2 -> 1. The `$3` pin on `vp` is gone; the
`*(volatile u16 *)` cast (present in body_free.c, so the brief's rule lets it stay; sites.txt calls it NEEDED) is kept
and now marked `// !FAKE: volatile cast …`. Free start 6 = regen best 6. No copies (`0x14D10`, `D_8018A5A2` occur only
here).

The two moves (both needed; each alone scores worse — METHOD step 5):
```
     ent = D_801202A0;
+    i = 0;
     pos[0] = *(u16 *)(param_1 + 6);
     {
-        register u16 *vp __asm__("$3");
-        u16 t;
-        vp = (u16 *)&D_80126B66;
-        t = *(volatile u16 *)vp;
+        u16 tt;
+        val = (s32)&D_80126B66;              /* the loop's `val` temp, reused */
+        tt = *(volatile u16 *)val;           /* !FAKE: volatile cast (kept) */
         pos[1] = *(u16 *)(param_1 + 0xA);
-        pos[2] = t + 8;
+        pos[2] = tt + 8;
     }
-    i = 0;
     np = (u16 *)D_801152A8;
```

## (a) The residual
Same 438 instructions; the `pos[2] = camZ + 8` load: the target has `move s4,zero; lhu v0,6(s3); la v1,D_80126B66;
sh v0,24(sp); lhu v0,0(v1)` — the address in `$v1`, set ABOVE the pos[0] store. Pin-free: `la v0` after the store,
`lhu v0,0(v0)`, and `move s4,zero` in the load-delay slot.

## (b) The passes and decisions (dumps: scratch/dumps_free, dumps_vB, dumps_tree, dumps_w1, dumps_w4)
1. **Why the address is in a register at all — the volatile.** expand forces the constant address into a pseudo
   (`(set r130 (symbol_ref))`, `.rtl`); combine folds that set into its single use `(mem r130)` for every non-volatile
   spelling (vA/vB/vC/w5: 437 ins, `lui v0; lhu v0,%lo(v0)`). With a volatile MEM the combined insn cannot be
   recognised: combine runs under `init_recog_no_volatile` (combine.c:491) and `general_operand` refuses volatile MEMs
   (recog.c:807). No other can_combine_p/try_combine refusal applies to a constant-address load in one block, and the
   bytes show no block boundary between the `la` and the load. So the volatile stays (the marked lever).
2. **Why `$v0` without the pin — sched1's birthing boost.** The address set births a pseudo set once
   (`birthing_insn_p`, sched.c:2469-2545: `reg_n_sets == 1`), so `adjust_priority` raises it to the block maximum and the
   reverse list scheduler places it immediately before the load, AFTER the pos[0] store (free `.sched` T-33: 213 at
   `7f000001` over 208). local-alloc then finds `$v0` free (the pos[0] temp died at the store).
3. **Reusing `val`** (the table-value temp of the entity loop, `val = (&D_8018A5A0)[j * 0x20]`, which the target keeps in
   `$v1` — `lhu v1,0(at)` at 0x45b4): `reg_n_sets` = 2, no birthing boost (w4 `.sched`: priority 1), and `val` is now
   ONE global allocno spanning the loop: `.greg` "83 conflicts: … 2 29" — it conflicts with `$v0`, so global-alloc gives
   it `$v1`. Alone (w1) this leaves an ORDER residual of 4: the unboosted set sinks to the TOP of the block in sched1
   (lowest LUID), and sched2's LUID tie-break (`rank_for_schedule`, sched.c:2425-2428) keeps `la v1` above
   `lhu v0,6(s3)` and `move s4,zero`.
4. **`i = 0;` written before `pos[0]`** gives that insn (231) a LUID below the address set's, so both schedulers break
   the priority-1 tie the target's way: `move s4,zero; lhu; la; sh` (w4 = 0). `i = 0` alone (w6): 6.
Proven on bytes (w1 4, w6 6, w4 0, w5 = w4 without the volatile 10) and on dumps (w4 `.sched` priority, `.greg`
conflicts).

## (c) The moves
- Reuse the function-scope `val` for the address (`val = (s32)&D_80126B66; tt = *(volatile u16 *)val;`), deleting `vp`
  and its `$3` pin (d14's rule: the target keeps both values in the same register -> one original variable).
- Move `i = 0;` above `pos[0] = …` (statement order = LUID tie-break).
- Kept, marked: the `volatile u16 *` cast (structs phase).

## (d) GENERATOR PROPOSAL
**R-reuse-late-temp**: when a register residual puts an early short-lived pseudo in `$vN` too LOW (e.g. `$v0` where the
target has `$v1`) and the target's `$v1` also holds a function-scope temp later in the body (same register, disjoint
live ranges), rename the early temp to that later variable (cast as needed) — the second set removes sched1's birthing
boost (sched.c:2489-2490) and makes the pair one global allocno whose conflicts pick the target register; then
enumerate the position of each independent constant statement in the block (`i = 0;`, `ent = …`) for the LUID
tie-break. Enumerate: every function-scope local the target keeps in the wanted register.

## (e) What did not work (bytes)
- body_free (volatile, no pin): 6. Statement orders with a block-local `vp` (o1–o4): 6 each — sched1 re-sinks the
  boosted set regardless of source order.
- No volatile: vA/vB (plain or pointer local) 10, vC 17 (437 ins, address folded).
- Reusing `j` instead of `val` (w2): 5 (`j` is `$s1`). Inline `pos[2] = *(volatile u16 *)val + 8` with `i = 0` early (w3): 4.
- A 400-order enumeration of the region was started and stopped once w4 was found by reading the sched2 tie.

## (f) Where the method fell short / what helped
- The residual looked like a pure register choice (a pin), but half of it is COUNT-in-disguise: the volatile is what
  creates the `la`; METHOD should say "a `la`+`lw/lhu 0(reg)` pair on a global the target reads elsewhere with `%lo` =
  a combine refusal; only a volatile MEM (or a block boundary) produces it at -O2".
- METHOD 12 (d3)/14 (d14) were the right families: variable reuse + a statement-order tie-break. The `.sched` ready-list
  priorities (`7f000001` = birthing) located both decisions in one reading.

## (g) Structs
No, not for this lever. The kept lever decides combine's RECOG of a volatile MEM; a struct type on the camera vector
(`D_80126B5C` as `{ s32 vx, vy, vz; }`, reading the upper half of `vz`) would still be a non-volatile MEM that combine
folds (and it would relocate against `D_80126B5C+10`, identical only after LINKING). The `expr.c:4568-4577` aggregate
channel concerns scheduling/cse memory ordering, not combine's operand predicate. Plausibly the original declared this
global (or a macro over it) volatile — if the structs phase types the D_80126B5C block, try `volatile` on that single
member and drop the cast (not tested: other accesses to D_80126B66 in this body fold, so a volatile member would have to
be accessed through a separate declaration there).
