# func_80036FB0 (src/800_c.c) — P36 S104 agent e3 — score 4 -> 0, ZERO levers (the keepalive + `f64 hole` removed)

## (a) The residual
FRAME-only + one delay slot: the target has an 8-byte frame (`addiu sp,sp,-8` / `+8`) that no instruction touches, and
its first `blez` carries `move a2,zero` (i = 0) in the delay slot where the lever-free do-while body has `nop`. Same 20
other instructions. The tree faked the frame with `f64 hole` + `asm volatile("" :: "m"(hole))` (the asm also stopped
reorg's backward delay-slot scan from pulling the prologue's `addiu sp` into the slot — `stop_search_p`, reorg.c).

## (b) The pass decisions (all read on the `-d` dumps of the closing body, `scratch/dumps_u1/`)
1. The original is a plain `for (i = 0; i < D_8006AEE8; i++)` loop, not an `if (D > 0) { count = D; do … while }`:
   - jump.c `duplicate_loop_exit_test` (jump.c:2131; new pseudos for the copied test at :2223) copies the exit test
     `t = i < D; if (t == 0) goto end` in front of the rotated loop.
   - combine then merges `i = 0` (i1) + `t = (lt i D)` (i2) + the branch (i3) into `blez` with `i = 0` KEPT as newi2pat.
     Because `newi2pat != 0`, combine.c:2306-2314 does NOT zero `reg_n_refs` of `t` (pseudo 87): `.flow` says
     "Register 87 used 2 times across 2 insns", `.greg` lists `87 conflicts:` EMPTY and no disposition -> `alter_reg`
     (reload1.c:2331-2352) gives it a stack slot -> the 8-byte frame that nothing references (the S103 c35 / §16Xy
     orphan-slot class, new source: a rotated loop's duplicated exit test).
   - The delay slot then comes out as the target's (`move a2,zero`, bytes). WHY reorg does not pull the prologue
     `addiu sp` into that slot here while it does for the `pad[2]` probe in (e) was NOT examined (`.dbr` not read) —
     most likely the `i = 0` insn kept by combine now sits between the load and the branch; unproven.
2. The loop bound `D_8006AEE8` is read in the loop condition and loop.c HOISTS it (`.loop`: "Insn 17: regno 75 … moved"):
   `invariant_p` (loop.c:2779) asks `true_dependence` (sched.c:817, the `MEM_IN_STRUCT_P && rtx_addr_varies_p` clauses at
   :834/:858) whether the store `(&D_80078F10)[i] = arg1` can alias the scalar `D_8006AEE8` — an ARRAY store at a varying
   address never conflicts with a fixed-address scalar, so the load moves to the loop preheader, and cse2 turns it into
   the copy `move a3,v0` of the pre-test load. That is why the target has `lw v0 … blez v0 … move a3,v0` (two pseudos)
   — the tree's `count = D_8006AEE8` local was the decompiler's reading of the hoisted invariant.
3. The walked pointer `$v1` is loop.c's strength-reduced giv of `(&D_80078F10)[i]` (`giv at 47 reduced to (reg:SI 89)`).

Proven on bytes: `--try` score 0 (21/21). Proven on dumps: the orphan pseudo 87 (.flow/.greg), the hoist (.loop).

## (c) The move that closed it
The whole do-while + `count` + walked `p` + `if` guard rewritten as the TU's own idiom (func_80036D24 at
src/800_c.c:1445 spells the same loop over the same two globals this way):

    for (i = 0; i < D_8006AEE8; i++) {
        if ((&D_80078F10)[i] == arg0) {
            (&D_80078F10)[i] = arg1;
        }
    }

`p = &D_80078F10; … p[i]` scores 0 too (u2). Walking `p++` in the for header does NOT (u3, 15: the pointer store is
scalar-to-scalar, no hoist).

## (d) GENERATOR PROPOSAL
When the residual is FRAME-only (+8, no slot referenced) on a guarded `if (G > 0) { count = G; … do { … } while (i < count); }`
loop, rewrite it as `for (i = 0; i < G; i++)` over an indexed array access (delete the guard, the `count` local and the
walked pointer): the rotated loop's duplicated exit test orphans one pseudo in combine (8 bytes of frame) and the
aggregate-vs-scalar alias rule hoists `G` into the `count` copy.

## (e) What did not work (bytes)
- `count = G; if (count > 0) { for … }` / `if (G > 0) { count = G; for … }` (w1-w5, v1, v3): 7-8 — the frame appears but
  cse cannot fold the duplicated `0 < count` test against the guard (`fold_rtx` only checks dominance when arg0 is a REG,
  cse.c:5411-5431; here arg0 is the constant 0), so a second `blez` survives.
- `count = G; for (…; i < count; …)` without a guard (v4, w6, w7): 14 — `count` IS the load, no copy, order differs.
- Unused `s32 pad[2]` on the free body: 3 — the frame appears but reorg pulls the prologue `addiu sp` into the `blez` slot.

## (f) Where the method fell short
neighbours.txt and related.txt were empty; the answer was a sibling in the same TU (func_80036D24, same globals) — the
"grep the TU for the other functions that touch the same global" step (S103 c2) found it. The generator families never
propose deleting a guard + a local together (a structural rewrite: guarded do-while -> for).

## (g) Structs question
No struct needed; the channel IS the aggregate rule, but it is reached with an array access (`(&D_80078F10)[i]`), which
is already `MEM_IN_STRUCT_P` (expr.c:4568-4577). Declaring `D_80078F10` as `s32 D_80078F10[]` would read better and
should give the same bytes (same aggregate flag) — not tested because the file-scope `extern s32 D_80078F10;` is shared
with other functions in the TU (a structs-phase cleanup).
