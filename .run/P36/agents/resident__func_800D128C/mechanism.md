# func_800D128C — e34 (P36 T7 S104) — score 46 -> 0; levers 3 -> 0 asm (one METHOD-step-3 declaration alias left)

Files: `body.c` (0; the alias with an explanatory comment), `body_minlever.c` (0; the same text with the alias
line marked `// !FAKE: alias` — use it if the alias is ruled a lever: 3 -> 1), `body_leverfree_nearmiss.c`
(8; no alias, no asm).

## (a) Residual (counted on the whole objdump, scratch/target.txt vs scratch/free_dis.txt)
COUNT 238 vs 243, three independent defects:
1. switch-2 index copy `move v1,s1` missing (1 ins) — the tree's `sel` launder.
2. case 1's `[li a2,1][jal BB24][li s0,150][j]` tail cross-jumped into case 117's identical tail (3 ins).
3. case 16's `[label16][li s0,150][j]` cross-jumped into the same tail (1 ins) — the tree's second barrier.

## (b) Passes and decisions
1. Index copy. `switch (ret)` on an `s32 ret`: expand_end_case uses ret's pseudo as the index, no copy.
   On an `s16 ret` the index is `sign_extend:SI (reg:HI ret)` = an `ashift 16`/`ashiftrt 16` pair; combine's
   `simplify_shift_const` (`combine.c:7926-7942`) sees more than 16 sign-bit copies in ret (every set of ret is a
   small constant) and reduces the pair to `(set (reg:SI 96) (subreg:SI (reg:HI ret)))` — a real copy into a new
   single-block pseudo, which local-alloc puts in `$v1` (PROVEN: scratch/dumps_body/body.i.combine insn 653).
2+3. Cross-jump runs AFTER sched2 (`toplev.c:3142`, `jump_optimize (insns, 1, 1, 0)`), unconditional-jump arm
   `jump.c:1965-2000`: each `j L2` is compared with every other jump to L2 (jump_chain, reverse insn order) by
   `find_cross_jump` (`jump.c:2371-2527`, minimum 2 insns; 1 against the code before the label). A CODE_LABEL met on
   the moved stream lowers the minimum (`jump.c:2406-2410`), so case 16's `[label; s0=150; j]` merges into ANY other
   arm ending `[s0=150; j L2]`. sched2 cannot separate them: a hard-reg set after a call always depends on the call
   (`sched.c:1704`, the `call_used_regs[i]` test indexes the NREGS counter, i.e. `$0`, which is call-used).
   The target's bytes are reachable only if, at jump2 time, NO arm other than case 16 ends in `[s0=150; j L2]`:
   cases 1 and 117 end in `[call; j L16]` (a source goto to case 16's assignment, like the file's existing
   `goto lab1334` for case 3). reorg then rebuilds the target: the `j L16`'s slot cannot be filled from behind (the
   filled `jal` is a SEQUENCE, `reorg.c:675-700` stop_search_p), so it steals `li s0,150` from L16 and threads the
   jump on to L2 — `j 2c0; li s0,150`, byte-identical to a private tail. Case 5 -> 16 keeps its own block.
   But cases 1 and 117 now both jump to L16 after `[li a2,1][jal func_8014BB24]` — two equal insns, the minimum:
   they merge (scratch/c/g1.c: 41). They stay apart only if the two call insns are not `rtx_renumbered_equal_p`:
   SYMBOL_REF compares the name string BY POINTER (`jump.c:3991-3992`), and an `__asm__("func_8014BB24")` declaration gets its own
   `*`-prefixed, freshly allocated name string (`varasm.c:478-485`) — the METHOD step-3 declaration alias (g2/g3/body.c: 0).
   A return-type cast `((s32 (*)(s32, s32, s32))func_8014BB24)(obj, 0xC8, 1)` also works (call_value vs call
   pattern; scratch/c/k1.c: 0). Nothing in plain C makes two identical `(obj, K, 1)` calls to one declared void
   function differ in RTL.

## (c) The moves (all four in body.c)
1. `s16 ret = 3;` and `switch (ret)` — the `sel` variable and its launder deleted (1 lever).
2. case 1: `func_8014BB24(obj, 0x96, 1); goto set96;` and case 117: `...(obj, 0xC8, 1); goto set96;` with
   `set96:` on case 16's `val = 0x96;` — both asm barriers deleted (2 levers).
3. case 117's call through `func_8014BB24_alt` (body-local `extern void func_8014BB24_alt(s32, s32, s32)
   __asm__("func_8014BB24");`) — zero bytes, same relocation symbol, the .o is identical before linking.
(1) alone: 43 (u16 sel variant) -> the index copy fixed; (2) without (3): 41; (2)+(3): 0.

## (d) Generator proposals
- When a `switch (x)` target has an extra `move vN,sK` before `sltiu`, declare the switch variable `s16`
  (combine turns its sign extension into a surviving SUBREG copy) instead of adding a copy variable.
- When the target has N arms whose tails are byte-identical `[.. jal F][j L; li sK,C]` that the candidate
  cross-jumps, and one arm is a bare `[label][li sK,C][j]`: rewrite the other arms as `goto` to that arm's
  assignment; if two of the goto arms end in the same call, route one call through a body-local asm-named
  declaration of the same symbol. Detect by: target `j` delay slot holds an insn equal to the first insn at a
  label elsewhere (reorg's steal-from-target signature).

## (e) What did not work (bytes)
- `val = 0x96` before the call in case 1 or case 117 (x1/x2: 9/8): sched2 keeps it before the jal and reorg fills
  the `j` slot from L2's `move v1,s1` instead.
- one goto only (g4/g5: 43/41): the remaining `[s0=150; j L2]` tail swallows case 16 through the label rule.
- `switch ((u16)ret)`, `(ret & 0xFFFF)`, `u16 ret`, `u8 ret`, `(u8)ret`: 1 each (a zero-extend, `andi`).
  `switch ((s16)ret)` with `s32 ret`: 0 too — the declaration spelling reads better.

## (f) Where the method fell short
Steps 12-16 list "goto chains -> structured C"; this is the INVERSE: the target needed MORE gotos (two arms
jumping into a third arm's tail, reorg's steal-from-target rebuilding the private-looking tail). The residual
shows it as "arms merged that the target keeps apart", which reads like "add a barrier"; the tree's header had
concluded exactly that. The reorg signature (a `j` slot equal to another arm's first insn) should be a residual
class of its own.

## (g) Structs
No. The deciding facts are jump2's insn equality and reorg's slot filling; `obj` (`&D_80126B58`) as a struct
pointer would not change either. The remaining alias is a symbol-identity question, not an aggregate access.
