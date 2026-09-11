# func_80014DEC (main, src/800.c) — T7 agent e10 (S104)

**Result: score 0, lever-free** (no pin, no asm, no volatile, no do-while). Levers 1 -> 0. Signature unchanged
(`u8 func_80014DEC(s32 a0, s32 a1)`).

```c
u8 func_80014DEC(s32 a0, s32 a1) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078D98;
    a1 &= 0xFF;
    offset = offset + a1;
    return *(u8 *)(offset + 0x32);
}
```

## (a) Residual
A pure `$v0 <-> $v1` swap: the `*76` shift/add chain sat in `$v1` and the `&D_80078D98` lui/addiu pair in `$v0`;
the target has the chain in `$v0`, the symbol in `$v1`. Count 14 = 14.

## (b) Pass and decision (PROVEN on dumps, `scratch/dumps_free`, `scratch/dumps_fix`)
The decompiler text writes the `*76` as an explicit chain assigning ONE user variable `v0` five times. `.lreg`:
`Register 74 used 10 times across 9 insns in block 0; dies in 2 places` — local-alloc refuses any pseudo that dies more
than once (`local-alloc.c:472`, `reg_n_deaths[i] == 1`), so it goes to global, AFTER local-alloc already gave the
block-local address pseudo (77) `$2`; global then takes `$3` for the chain. Written as `a0 * 76`, `expand_mult`'s
synth_mult emits a chain of set-once pseudos (74, 76..80), each dying once: local-alloc allocates them all in the
block, chain first -> `$2`, the symbol pointer 81 -> `$3` (`;; Register 81 in 3.`).

## (c) Move
The multiply written as `a0 * 76` (the same-TU sibling **func_80014CF8**, src/800.c:2114, is byte-identical to this
function except for its name — its text ported unchanged, parameters kept `s32`).

## (d) Generator proposal
When a body writes a constant multiply as a `v = (a<<2)+a; v = (v<<2)-a; v <<= 2;` chain into ONE variable, rewrite
it as `v = a * K` (K recovered by evaluating the chain) — the explicit chain makes a multi-death pseudo that
local-alloc refuses (`local-alloc.c:472`); and before any search, diff the target's bytes against every same-TU
sibling's (identical bodies under two names are common here: CF8/DEC, and D30 is the same with 0x42).

## (e) What did not work
The sweep's best (width `v0` s32 -> u16/u8) reached 1 [COUNT], an extra/missing mask — width moves add an `andi`, they
cannot shorten the pseudo's death count.

## (f) Where the method fell short
Nothing: `related.txt` listed func_80014CF8; objdump of the three siblings side by side showed CF8 == DEC byte for byte.
Step 12's "grep for another definition" should include "diff the target bytes against every sibling in the TU" —
an identical twin under a different NAME is not found by a name grep.

## (g) Structs
No. There is no struct access to change: the element size 76 and field 0x32 would become `D_80078D98[a0].f[a1]`
(`struct { u8 pad[0x32]; u8 f[...]; ... } [ ]` of size 0x4C) — that would produce the same `a0 * 76` multiply via
the array index and would equally close it, but the decision was the multi-death user variable, not an aggregate
access channel.
