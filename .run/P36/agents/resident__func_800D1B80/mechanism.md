# func_800D1B80 — e34 (P36 T7 S104) — score 1 -> 0, levers 1 -> 0 (plain C, no pin/asm/volatile)

Twin: func_800D1984 (aF800D1984) — same text with func_800D19DC for DsMix, same close (its own pack).

## (a) Residual
One register: the `sb v0,20(..)` base is `$s0` in mine, `$a0` in the target (22 = 22 ins). Nothing missing;
the load reads `$s0`, the store reads `$a0` — the copy `a0 = arg0` was placed BEFORE the store in the target.

## (b) Pass and decision (PROVEN on the .sched/.lreg dumps, scratch/dumps_{good,free})
1. sched1, `adjust_priority` (`sched.c:2507-2545`) boosts an insn with no deaths to `max_priority` when
   `birthing_insn_p` (`sched.c:2469-2491`) says it births its destination: `bb_live_regs & bit` AND
   `reg_n_sets[REGNO] == 1` (`sched.c:2488-2489`). In the lever-free body the ONLY set of hard `$a0` in the
   function is DsMix's argument copy (insn 32), so it is a "birthing" insn: priority 7f000001, scheduled first in
   the backward list (T-3), i.e. LAST in forward order, after the store (free .sched: `ready list at T-3: 29 (2) 32
   (7f000001), now 32 29`).
2. With the copy after the store, arg0's pseudo dies in the copy and the store keeps it (`$s0`).
   When the copy precedes the store, `update_equiv_regs` calls `optimize_reg_copy_1` (`local-alloc.c:1003-1007`,
   body `:700-800`) on `a0 = r72` (r72 not dead there): r72 dies in the store a few insns later, so the store's
   base is rewritten to `$a0` (good .lreg: `insn 30 (set (mem/s:QI (plus:SI (reg:SI 4 a0) ...`).
3. The extra `a0 = s0` before the `jalr` costs 0 bytes: after reload it is `s0 = a0; ...; a0 = s0` with neither
   changed, and jump2's no-op-move deletion removes it (`jump.c:425-462`, the S103 c10/c35 channel).

## (c) The move that closed it
Call the method pointer WITH ITS OBJECT — `fp(arg0)` with `fp` typed `s32 (*)(u8 *)` — i.e. at the handler's real
arity (it is `obj->fn(obj)`). That adds a second set of `$a0` (`reg_n_sets[4] == 2`), `birthing_insn_p` fails for
DsMix's argument copy, its priority stays 1, the store (priority 2) is emitted after it, and
`optimize_reg_copy_1` re-bases the store on `$a0`. `arg0[0x14]++` and `arg0[0x14] = arg0[0x14] + 1` both score 0;
the delivered body uses `++`.

## (d) Generator proposal
When the only residual is a store/load base `$sN -> $aK` right before a `jal` whose argument K is that same value,
and the function makes an earlier indirect call through a field of that pointer (`*(fn **)(p + K)`), re-type the
call as `fn(p)` (pass the object to the method) — generally: add the value the caller already holds in `$aK` as an
extra argument to an EARLIER call (it raises `reg_n_sets[$aK]` and kills sched1's birth boost for the later copy);
this is R19's "pass the argument the caller already holds" applied to the first call instead of the last.

## (e) What did not work (bytes)
- `v = arg0[0x14] + 1; p = arg0; p[0x14] = v; return DsMix(p);` -> 1 (cse re-canonicalises p to arg0).
- `arg0[0x14]++; return DsMix(arg0);` with `fp()` (no argument) -> 1.
- `p = arg0; p[0x14] = arg0[0x14] + 1;` with the call inlined in the `if` -> 1.
The tree header's theory (a second pointer pseudo `p` that cse must not merge, the `$0`-add opaque copy) was a
correct description of the final RTL but the wrong source: the `$a0` store is a local-alloc copy optimisation fed
by a sched1 order, not a surviving user variable.

## (f) Where the method fell short
Nothing in steps 8-16 names this channel: `birthing_insn_p`'s `reg_n_sets == 1` test on a HARD argument register.
It is the same arity family as S103 c3/c12/c35 (R19), but it acts through sched1 + `optimize_reg_copy_1`, so a
reader of `alloc_table.py` would never see it. Worth a cookbook line: "a store base `$aN` = the copy for the next
call scheduled before the store; count the sets of `$aN` in the function".

## (g) Structs
No. The deciding count is `reg_n_sets` of hard `$a0`; a struct type for arg0 (`f0C` method pointer, `u8 f14`)
would make the text nicer (`arg0->fn(arg0); arg0->f14++;`) but does not change sched1's birth test or
`optimize_reg_copy_1`. The close is a call-arity fact, not an aggregate-access one.
