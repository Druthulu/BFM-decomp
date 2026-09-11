# func_80181864 (ov_SC03_113) — d23, P36 S104 — score 25 → 0, ZERO levers (3 levers → 0; 7 copies close, 21 → 0)

## (a) The residual
Two defects, both counted before touching the source (237 vs 240 instructions):
1. **Free-list loop** (was the `launder` lever): target `move a0,s0; beqz a0,END; nop; j L; nop` — the exit test reads the
   COPY (a0); mine tested the source `s0` and reorg put the copy in the branch delay slot (`beqz s0,END; move a0,s0`).
   Same count, different test register → one delay slot unfilled in the target.
2. **Two cross-jumped stores** (were the two `barrier` levers): target ends BOTH arms of each `if (call) … else if (call) …`
   pair with its own `sh v0,18(s0)` / `sh v0,26(s0)` (the first arm's in its `j`'s delay slot); mine had ONE store, the
   first arm jumping into the middle of the second arm's tail (`j <sh>; addiu v0,v0,-4`) — 2 missing instructions.

## (b) Passes and decisions (read, and proved on dumps)
1. cse `make_regs_eqv`, **`cse.c:846-857`**: on `arg0 = e`, the NEW register becomes the class's canonical (first) reg only
   if it lives beyond the cse block AND its last use is later than the old one's (`regno_last_uid[new] > …[firstr]`).
   The decompiler text reused `e` (the function's entity pointer, used to the function's END) as the loop's "next" temp,
   so `e` always stayed canonical and the test `arg0 == 0` was rewritten to `e == 0` (`canon_reg`). A loop-local `next`
   dies at `p = next`, `p` outlives it (the loop test), so `p` becomes canonical and the test stays on the copy.
   (Proved on bytes: this move alone 25 → 21, the loop hunk vanishes.)
2. post-reload jump pass with cross-jumping, **`toplev.c:3142`** → `find_cross_jump` **`jump.c:2371`**, equality by
   `rtx_renumbered_equal_p` (`jump.c:3899`), minimum 1 insn (`jump.c:1978`). Source order `n = 1; store;` makes the store the
   LAST insn before both the `j L` and the fall-through into `L` → equal → merged (`do_cross_jump`). Dump proof
   (`scratch/dumps_a1` vs `scratch/dumps_sw15`, pass order greg → sched2 → jump2 → dbr): with the old order the stores to
   e+0x12/e+0x1A are insns 259/312/392/445 in `.sched2` and only 312/445 in `.jump2`; with `store; n = 1;` the last insns
   before the jump/label are `(set s1 (const_int 1))` vs `(set s1 (const_int 2))` (and `s1+4` vs `s1+8`) — unequal at the
   first compare, no merge; all four stores survive `.jump2`, and reorg (`.dbr`) later hoists `li s1,N` into the `jal rand`
   delay slot and copies the store into the `j`'s slot (new uids 766/769) — exactly the target's layout.

## (c) The moves that closed it (all plain C)
1. `for(;;){ e = p->next; f(p); p = e; if (!p) return; }` → `while (p != 0) { s32 next = *(s32 *)(p + 0x6C); f(p); p = next; }`
   (a fresh loop-local `next` instead of reusing `e`; the structured `while` is byte-identical to the `for(;;)`/`if` form,
   and so are `for (p = e; p != 0; p = next)` and the `if (e) do … while` form — tested).
2. In each of the four arms: `n = K; *(s16 *)(e + 0x12) = …;` → `*(s16 *)(e + 0x12) = …; n = K;` (store first, then the
   counter). Either one arm of each pair suffices (masks 5/6/9/10… of 16 all score 0); all four swapped is the consistent text.
3. Readability only (0 bytes): parameter named `e` directly, one walker `p` for all three list walks (the count loop, the
   free loop, the 0x2000-arm loop — the inner `s32 p;` shadow deleted). Scores 0 with each step.
Single-move scores: move 1 alone 21, move 2 alone 18, both 0 (the 25 start).

## (d) GENERATOR PROPOSALS
- **R-xjump-order**: when the residual shows a `j` into the MIDDLE of another arm's tail with the target duplicating that
  tail's last store (a cross-jump stub; tree lever = `__asm__ __volatile__("")` "5a cross-jump barrier"), move the arm's
  last side-effect-free REGISTER assignment (`n = K`, `n += K`, a flag) to AFTER the arm's final store, in every arm that
  ends `…; store;` before a join label — the arms then end with unequal insns and `find_cross_jump` stops at the first
  compare. This is the lever-free replacement for every "cookbook 5a" barrier whose arms set distinct constants.
- **R-fresh-next**: when a list-walk `x = p->next; f(p); p = x; if (p == 0)` reuses a LONG-LIVED variable as `x` and the
  residual is the loop's test register (test on the source vs the copy), replace `x` with a loop-local `next`
  (cse canonical-reg choice, `cse.c:846-857`). Tree lever = a `"=r"/"0"` launder on the copy.

## (e) What did not work / notes
- Struct typing does NOT steer the cross-jump: a body-local `struct Ent { …; s16 v12; …; s16 v1A; }` for the four stores
  scores 21 with the old statement order (`scratch/st_a1.c`) and 0 with the new (`scratch/st_sw15.c`) —
  `rtx_renumbered_equal_p` compares codes/modes/operands, never `MEM_IN_STRUCT_P` (a flag, not a format field).
- No lever-free donor existed: all 6 other definitions of the class carry the same 3 levers.
- The sweep's generators could not reach either move: R9 swap-stmts was applied at one site only (`@5537`), and neither
  defect alone moves the score much from its start (21/18) while the other remains — a JOINT edit (method step 5).

## (f) Where the method fell short
- Nothing blocking; step 1 (whole-function dump diff with addresses stripped) located both defects in one read, and the
  `.sched2`/`.jump2` store-uid census proved the cross-jump in one command. A cheap enumerator over "statement pair
  swaps inside arms that end at a shared label" (16 bodies here, ~5 s) would have found move 2 mechanically.

## (g) Structs answer
No for this class — neither remaining decision reads struct information: cse's canonical-register choice is lifetime
arithmetic on pseudos, and cross-jump's equality ignores MEM flags (tested on bytes, above). A struct for `e` would still
be the right READABILITY step for the structs phase: `0x02 s16 state`, `0x06/0x0A/0x0E u16 pos x/y/z`, `0x12/0x16/0x1A s16
vel x/y/z`, `0x20 ptr → sub-object (0x12 s16 dir, 0x14 s16 angle)`, `0x34 s16`, `0x6C next` (linked list), `0x70 s16`,
`0x88/0x8A/0x8C s16 home x/y/z`, `0xFC s16 timer` — all byte-neutral per the struct test.

## Proved vs not proved
Proved on bytes: both moves (score 0, reloc-level objdump identical, `scratch/final.s` vs `scratch/target.s`), the
cross-jump attribution (uid census across `.sched2`/`.jump2`), the struct null. Read but not traced in a dump: the exact
`make_regs_eqv` branch taken for `p = next` (inferred from the loop hunk disappearing under move 1 alone).
