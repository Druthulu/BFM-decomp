# func_80186440 (ov_SC03_091_jr_8018326C.c) — P36 S104 agent d8

**Result: score 0 in plain C, zero levers** (was 1 NEEDED lever: `register s32 cnt __asm__("$4")`). Levers 1 → 0.
Best body: `PACK/body.c` — the `cnt` local is deleted and the tail's `cnt = *(u16 *)(param_1 + 2) + 1; ... *(u16 *)(param_1 + 2) = cnt;`
becomes a single `(*(u16 *)(param_1 + 2))++;` after the `|= 0x50000000` store. Verified by `--try`: score 0, 231/231 ins, MATCH.

Equivalent closes, also byte-proven (score 0): keep the local but declare it `u16 cnt;` (or `s16 cnt;`) with the original
statement order; `++*(u16 *)(param_1 + 2);`; a body-local struct with `((struct T *)param_1)->f2++;`.

## (a) The residual
Same 231 instructions; in the final block the `lhu a0,2(s2)` of the +2 counter must sit ahead of the three `sb` 0x80 stores
(right after `li v0,128`) with the counter in `$a0` and the `0x50000000` in `$v1`; the lever-free s32 body put the `lhu` down
against its `addiu`/`sh` and swapped `$a0`/`$v1`. Counted first: no instruction missing — an ORDER residual that drags a
local-alloc register swap with it.

## (b) The pass and the decision (read in the dumps, proven on bytes)
sched1 (before local-alloc). The lever-free trace (`scratch/dumps_free/fn.sched`, block ending at insn 579):
`T-2: ... 553 (7f000001)` — the `addiu` (insn 553, `(set (reg:SI 80) (plus (reg:SI 179) 1))`) was raised to
LAUNCH_PRIORITY the moment the `sh` was scheduled, because `adjust_priority` (sched.c:2537-2545) finds
`birthing_insn_p` true: SET_DEST is a REG (sched.c:2477-2478), live below, and `reg_n_sets == 1` (sched.c:2490). It is then
scheduled right above the store, and its `lhu` (insn 551) in turn (also birthing), so both land after `lw 256` — the
sched1 order `sb sb sb lui lw lhu or sw addiu sh`. Local-alloc then numbers the qtys in that order and the constant takes
`$a0`, the counter `$v1`; sched2 keeps it.

With the u16 spelling the RTL is `(set (reg:HI 178) (mem:HI +2))`, `(set (reg:SI 179) (plus (subreg:SI (reg:HI 178)) 1))`,
`(set (reg:HI 80) (subreg:HI (reg:SI 179)))` — the HImode add has no insn on MIPS and is widened (expand_increment →
expand_binop OPTAB_LIB_WIDEN, expr.c:8662; the same widening for a u16 local's `= x + 1`). combine's simplify_set
(combine.c:4376-4402) rewrites the merged insn as `(set (subreg:SI (reg:HI 80) 0) (plus:SI ...))` — a SUBREG destination,
so `birthing_insn_p` returns 0 at sched.c:2478, the `addiu` keeps priority 2 (`T-2: ... 554 (2)`), the `sw` is taken first,
and the `lhu` floats to the top of the block (`scratch/dumps_u16/fn.sched`, trace identical to the pinned tree's
`scratch/dumps_tree/fn.sched`). Local-alloc then gives lhu/addiu `$a0` and the constant `$v1` exactly as the pin did.
In the `++` body the increment is even textually AFTER the byte stores and sched1 still hoists the `lhu` above them
(`scratch/dumps_pA/fn.sched`) — there is no alias barrier (same base `s2`, disjoint offsets); the placement is pure priority.

The `+= 1` and `x = x + 1` spellings (both scored 6) are folded by the C front end to `(u16)((int)x + 1)`: the add's
destination is an SImode REG again → birthing → the s32 residual.

## (c) The move that closed it
`s32 cnt` → `u16 cnt` (width of the counter local = width of the field it copies), or equivalently drop the local and write
the field update as a u16 `++`. One statement / one declaration; no reordering needed.

## (d) Generator proposal
When the residual is an ORDER/COUNT diff where a 16-bit field's `lhu`→`addiu`→`sh` chain is scheduled against its store in
mine but its `lhu` sits early in the target, re-declare the local that carries `field ± k` to the field's 16-bit width
(R12 must enumerate EVERY local stored to a 16-bit lvalue, not just the loop temps — here it only ever tried `w`), and
also try rewriting `x = F + 1; …; F = x;` / `F += 1` as `F++` at the store's position: both make the add's SET_DEST a
SUBREG, which switches off sched1's birthing boost (sched.c:2477-2545).

## (e) What did not work (byte evidence)
- `*(u16 *)(param_1 + 2) += 1;` at the end, `= *(u16 *)(param_1 + 2) + 1` at the end, and the s32 local loaded first then
  `cnt + 1` stored: all 6, identical residual (SImode REG destination → birthing).
- Reusing `w` for the counter (74) or `q` (38): the multi-set pseudo defeats birthing but becomes a global allocno that
  perturbs the `rand() % 8` blocks' registers.
- The history's single moves (R6 inline cnt, R8 temp, R9 swap, R7 block, R12 width on `w`, R18) all stayed at 6 — none
  touched the width of `cnt` itself.

## (f) Where the method fell short
Nothing structural: residual → count (none missing) → sched1 trace in `.sched` → `rank_for_schedule`/`adjust_priority` →
the one bit (REG vs SUBREG destination) that differs between the pinned and free bodies. The `LAUNCH_PRIORITY`
(0x7f000001) marker on a just-readied insn in the `.sched` trace is the tell; worth a row in `residual_moves.md`
("7f000001 on an arithmetic insn that feeds a store = birthing boost; make its dest a SUBREG via a 16-bit local/`++`").
The tree's own comment attributed the effect to register choice and a pin; the real lever was the local's mode.
The generator gap is R12's candidate set (see (d)).

## (g) Structs question
Neutral here. Tested on bytes with a body-local `struct T { u8 pad0[2]; u16 f2; u8 pad4[0xF8]; u8 c[3]; u8 pad; u32 flags; }`:
struct field accesses with the s32 local (`cnt = s->f2 + 1; … s->f2 = cnt;`) = 6 (unchanged); `s->f2++` = 0 and the u16 local
with struct accesses = 0 — i.e. the struct changes nothing, only the mode of the incremented value does. The known
struct channel (MEM_IN_STRUCT_P aggregate accesses vs scalar stores, expr.c:4568-4577 / sched.c true_dependence) is not
involved: sched1 already moves the `lhu` freely over the `sb`s (same base register, disjoint offsets). A struct type for
`param_1` (u16 +2 state counter, s16 +0xA, s32 +0x1C/+0x20, s16 array +0xDC..+0xF8, u8 rgb +0xFC..+0xFE, u32 flags +0x100)
would help readability and would make `p->state++` the natural spelling, but it is not what closes the bytes.
