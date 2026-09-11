# func_80183884 (ov_SC06_010_jr_8017A4AC.c) — T7 d30, P36 S104

**Score 0, ZERO levers** (pin-free start 45, the same as the regen best free_012 = 45). Tree levers: 1 pin -> 0.
The same text closes **all seven** copies of the class at 0 (7 pins -> 0), see the table at the end.

The move (one, in case 3 only):
```
-        s32 d = ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88);
+        s32 ret = ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88);
         if (func_80182F4C(a0, 0x48) == 0) {
-            if (d > 0x40000) {
-                s32 r = func_8012B608(...);
-                if (r >= -0xFF && r <= 0xFF) {
+            if (ret > 0x40000) {
+                ret = func_8012B608(...);
+                if (ret >= -0xFF && ret <= 0xFF) {
```
plus `register s32 tbl __asm__("$16");` -> `s32 tbl;` and the in-body comment rewritten to say why.

## (a) The residual
Instruction count equal (163/163); a pure 2-register permutation: the a0 copy took $s0 and `tbl` / case 3's `d` took
$s1 (s0->s1 x35, s1->s0 x3), plus the prologue order that follows from it. Target: a0 copy $s1, `tbl` $s0, `d` $s0,
`p88` $s2.

## (b) The pass and decision
global.c `allocno_compare` (:595-607) + `find_reg` pass 0 (`regs_used_so_far`, :945-953). Pin-free `.greg` order
`121 72 144 119 149 151 74 124 123 73`: r72 (a0 copy, 37 refs / 137 live, pri 13503.6) is the first GR allocno and
takes $16 in pass 1; `d` (r124, 2 refs / 5 live, pri 4000) and `tbl` (r73, pri 394.7) follow and get $17.
With ONE `ret` for both case-3 call results, r124 has 4 refs / live 5 -> floor_log2(4)*4/5*10000 = **16000 > 13503.6**:
`.greg` order becomes `121 124 72 …` (scratch/dumps_m4, alloc_table). `ret` takes $16 first; r72 conflicts with it
(r72 is live across case 3's F4C call) and takes $17; `p88` conflicts with both -> $18; `tbl` does not conflict with
`ret` (tbl is dead after case 0's B1B4 call, `ret` lives only in case 3) -> $16 in pass 0. The B608-result piece never
shows in the bytes (the target tests `addiu v0,v0,255` straight off $v0): combine folds `(set ret v0)` into its single
use (combine.c:914-917, no SMALL_REGISTER_CLASSES on MIPS), but flow counted its 2 refs before combine and its live
length adds 0 — so it is pure priority. **Proven on bytes and dumps** (alloc_table r124 pri 16000 refs 4 live 5).
This is exactly d21's func_8018179C mechanism in the same TU (same a0 copy priority class, same fix).

## (c) The move that closed it
Reuse case 3's first call-result local for its second call result (`d`,`r` -> one `ret`). Also 0: the same `ret` at
function scope (m2), and additionally merging case 2's B608 result into it (m1, m3). m4 (case-scope, 2 pieces) is the
smallest change and is body.c.

## (d) GENERATOR PROPOSAL
**R-merge-callret (d21's, now twice confirmed)**: when the residual is a callee-saved permutation where the high-ref
self pointer (`a0` copy) sits one register too LOW, compute for every set S of same-typed call-result temps whose
live ranges do not overlap the variable that should share the winner's register (`tbl` here) the merged priority
floor_log2(Σrefs)·Σrefs/Σlive and emit the merge (rename all of S to the first member, delete the other
declarations) for each S that beats the self pointer's priority — include pairs INSIDE one case/arm (`d`+`r`), not
only across cases.

## (e) What did not work / was not needed
- The pin-free tree body: 45 (the permutation). Regen best free_012 (R8 hoist tmp0): also 45 — no family merges
  two call-result locals, so the sweep could not reach it.
- Nothing else was tried: the first reading (d21's note + the alloc table) predicted the move and m1–m4 all scored 0.

## (f) Where the method fell short
- **The pack was empty except `residual.txt`** — "UNSTRIPPABLE: token mismatch at …:8375: expected `register`". Line
  8375 is the `switch`, not the pin (the pin is at 8366): the pack builder used line numbers from BEFORE d21's bank
  (4833a380d) shifted this TU. A pack built for a TU that another agent banked into this session must re-read the
  line map (or build from the function name). I rebuilt what I needed from the tree text directly.
- The brief says "4 copies"; the distinctive-line grep finds 7 (the header already said "family of 7"). The copy
  count in the brief comes from a hash that the per-overlay `D_` names split.
- The fastest route was METHOD step 15 (d21) + `tools/alloc_table.py` on the free body: one table, one arithmetic
  check (need Σrefs/Σlive such that the product beats 13503.6), four candidates, all 0.

## (g) Structs question
No. The lever decided a global-alloc PRIORITY race between the a0 copy (37 refs) and a short-lived call result; typing
`a0` as an actor struct pointer turns `*(T *)(a0 + K)` into `a0->field` — the same number of references to the same
pseudo, the same live length — so r72's priority and the conflict graph are unchanged, and the permutation would
stay at 45. The `expr.c:4568-4577` aggregate/scalar channel concerns scheduling/cse ordering of memory accesses,
which play no part in this residual. Not tested on bytes (the plain-C close made it moot).

## Header note for the coordinator
The TU header above the function (item 4, "REGALLOC-PERM -> the $16 pin (see below)") now describes a lever that is
gone; it should read "REGALLOC-PERM -> case 3's two call results share one `ret` (see below)". I changed only the
comment inside the definition. The same header sits over each of the other six copies.

## Copies (same text, only the per-overlay `D_801A71A4` equivalent differs) — all `--try` score 0
| function | TU | file |
|---|---|---|
| func_801813D0 | src/ov_SC06_008/ov_SC06_008_jr_8017C294.c | scratch/copies/ov_SC06_008__func_801813D0.c |
| func_80183884 | src/ov_SC06_010/ov_SC06_010_jr_8017A4AC.c | scratch/copies/ov_SC06_010__func_80183884.c (= body.c) |
| func_801811DC | src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c | scratch/copies/ov_SC06_018__func_801811DC.c |
| func_8018908C | src/ov_SC06_022/ov_SC06_022_jr_80184A28.c | scratch/copies/ov_SC06_022__func_8018908C.c |
| func_8018B564 | src/ov_SC06_024/ov_SC06_024_jr_80186F00.c | scratch/copies/ov_SC06_024__func_8018B564.c |
| func_80188F1C | src/ov_SC06_032/ov_SC06_032_jr_80182890.c | scratch/copies/ov_SC06_032__func_80188F1C.c |
| func_8017FC64 | src/ov_SC06_033/ov_SC06_033_jr_8017C24C.c | scratch/copies/ov_SC06_033__func_8017FC64.c |

Generated by `scratch/copies/mk.py` (extract each definition from the tree, apply the pin removal + the `ret` merge)
and `scratch/copies/fixcomment.py` (the in-body comment). Each file is a whole definition for `--try … --body`.
