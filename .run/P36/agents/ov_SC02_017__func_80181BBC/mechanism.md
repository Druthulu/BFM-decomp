# func_80181BBC — e7 (P36 T7 S104) — score 9 (sweep best 4) -> 0, ZERO levers (was: 1 NEEDED `$4` pin)

(a) Residual: REG, a v1/a0 permutation in the single straight-line block between the two `func_8001D0E8` calls — the
target puts the first `*(s0+0x20)` pointer and the `lhu 0x36` value in `v1` and the second `*(s0+0x20)` pointer (the
`|= 0x8000` object) in `a0`; the lever-free text swaps them. Counts equal (39/39). The tree pinned `a0_2` to `$4`.

(b) Pass/decision (dump-verified, `scratch/dumps_c1` vs `scratch/dumps_c5`, `.lreg`): the decompiler text REUSES two
locals for several values — `v1` = pointer, then the u16, then the constant 1; `v0` = `*(s0+0x64)`, then the flag word,
then the `+0xA` halfword. Each reused local "dies in N places" (`.lreg`: r74 v0 "dies in 3 places", r75 v1 "dies in 2
places"), so local-alloc refuses it (`local-alloc.c:472`, `reg_n_deaths[i] == 1` required for a block-local quantity)
and it goes to global.c, which fills v0/v1 by priority AFTER local-alloc has already placed the single-death `a0_2` in
`v1` (c5 `.lreg`: ";; Register 76 in 3"). With one pseudo per value every temp is a block-local quantity
(c1 `.lreg`: eleven one-block registers, `a0_2`-equivalent r80 "in 4", the u16 r84 "in 3") and `qty_compare_1`'s
ranking (local-alloc.c:1598) reproduces the target.

(c) Move (one, joint over two variables): give every value its own temp — either inline them (`body.c`, the house
spelling: `*(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x8000;`, `*(u16 *)(a0 + 0xA) += 0x36;`, one `u16 uVar1` for the
`0x36` read, as sibling func_80181A98 TU:5063 spells it) or rename each value (scratch/c8.c, also 0). The `s0 = a0`
param copy is irrelevant (c3 without it: 9; c4 with it + inlined temps: 0); body.c drops it (d24).
Byte-proven: c1 (body.c) 0, c8 (all renamed) 0, c4 0.

(d) GENERATOR PROPOSAL: when the residual is a register permutation inside one basic block and `.lreg` shows two or
more body locals that "die in N>1 places", split ALL of them at once (one name per assignment, or inline each
single-use temp) — R23 splitting one variable at a time cannot reach it (c2 splitting only `v1`: 10; c5 only the
first pointer role: 7).

(e) Did not work: c2 (split v1 alone) 10; c5 (inline the first pointer only) 7; c6 (inline the `|= 0x8000` only) 9;
c7 (inline the `0x64` pointer only) 9; c3 (delete the `s0` copy only) 9. The sweep's R8/R12 moves reached 4 (COUNT).

(f) Method: METHOD S103 c1/c8 ("a local REUSED across statement groups dies more than once and is refused by
local-alloc — split it") is exactly this; the only extra fact is that BOTH reused locals had to be split together.
The natural rewrite (inline, as the sibling func_80181A98 reads) closed on the first `--try`.

(g) Structs: no. The decision is block-local quantity eligibility (death count) in local-alloc; a struct type for the
object (`+0x20` sub-object with `+0x04` flags / `+0x20` pointer, `+0x64` owner with `u16 +0x36`, `u8 +0x75`, `u16 +0xFE`)
would change the spelling, not the number of pseudos.
