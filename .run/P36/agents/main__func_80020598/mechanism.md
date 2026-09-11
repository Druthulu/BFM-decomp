# func_80020598 (main, src/800.c) — T7 agent e10 (S104)

**Result: score 0, lever-free** (no pin, no asm, no volatile, no do-while, no pad). Levers 1 -> 0. Signature
unchanged. Whole-object check on the `--try --keep` object: `.text`, `.data`, `.rodata` byte-equal to
`.run/P36/delever/baseline/src/800.o`. The `MH` wrapper structs, the `m3` variable and the dead `s32 pad[4]` are all
gone; `a2`/`a3` are used directly by the gte macros.

## (a) Residual
`lw v1,64(sp)` + 8 loads through `$v1` where the target uses `$t0` — the SECOND of the two per-iteration re-loads of
a matrix pointer from its stack home (the first, from 56(sp), was already `$t0`). Count 292 = 292.

## (b) Pass and decision (PROVEN on dumps `scratch/dumps_c2/` + bytes)
* The target's `$t0` is not a global-alloc choice: it is RELOAD's register. With `a2`/`a3` written straight into
  `gte_SetRotMatrix(a2)` / `gte_SetRotMatrix(a3)` / `gte_SetTransMatrix(a3)`, both parameters' pseudos (74, 75) live
  across the whole loop and 7 calls, all nine `$s` registers are taken by higher-priority pseudos, so global leaves
  them unallocated (`.greg` "Register dispositions" lists neither) and reload gives each an 8-byte-aligned stack slot
  (`reload1.c:2331-2352`, `assign_stack_local(..., -1)` -> `BIGGEST_ALIGNMENT` rounding, `function.c:681-685`) and
  reloads the asm's `"r"` input into a spill register: `Spilling reg 8.` — `$8` is the first call-clobbered register
  never live in the function (`$2-$7` are all used). That is exactly the target's `lw t0,56(sp)` / `lw t0,64(sp)`.
  The tree faked the homes with two `MH` 8-byte structs + a pinned `m3`; unpinned, `m3 = h3.p` is an ordinary pseudo
  and gets `$v1`.
* That spelling (scratch/c1.c) left score 4: the homes at 72/80 vs 56/64 — the tree's `pad[4]` sat BEFORE them.
  Without the pad (c2.c) the homes are right but the frame is 120 vs 136: 16 bytes of reload slots missing ABOVE the
  homes. `.lreg` shows where such slots come from: `Register 140 used 4 times across 1 insns … ST_REGS or none` — the
  default arm's `(w >> 8) & 0xFF`, narrowed by combine into `lbu 1(base)` while the word load stays live, is a
  3-insn combine that SPLITS (combine.c:1994-2020); with `newi2pat != 0` the dead i2 pseudo's counts are not zeroed
  (`combine.c:2306`), so it keeps `reg_n_refs > 0`, gets no hard register and a phantom 8-byte slot
  (`reload1.c:2331-2334`) — the same mechanism as S103 c34 (ov_SC02_031 func_8017ECEC). The target has THREE such
  phantoms: arms 0 and 1 spelled the byte the same way.

## (c) Moves (joint; neither alone closes)
1. Delete `MH h2, h3`, `m3`, `h2.p = a2; h3.p = a3;` — pass `a2`/`a3` to the macros (the same-TU sibling
   func_80020248 does exactly this): score 9 -> 4.
2. Delete `s32 pad[4];` -> 22 (frame 16 short), and spell arms 0 and 1's middle byte like the default arm:
   `local[1] = ((w >> 8) & 0xFF) | ((w & 0xF) << 8);` (was `a1[3].b1 | …`) -> **0**. Combine still narrows it to the
   target's `lbu 20(s0)` off the word load's own address.

## (d) Generator proposal
When the tree carries a pinned pointer reloaded from a stack "home" that a struct/union wrapper fakes (`h.p = aN;
m = h.p;`), try the parameter itself at every use (reload's spill register reproduces the pinned `$t0`), then fix a
frame-only residual by counting phantom slots: each `(w >> K) & 0xFF` / `(s16)w` narrowing of a still-live word is one
8-byte reload slot (`.lreg` "ST_REGS or none"), so replace byte-deref spellings of the same word with the shift-mask
form until the `.frame` matches — and delete any `pad[]` that was compensating.

## (e) What did not work
The sweep's R4/R6/R7/R10/R12 moves (all 9): none touches the wrapper structs; `m3` inlined as `h3.p` still loads a
plain pseudo that global puts in `$v1`. c1 (params direct, pad kept) = 4 (homes shifted 16 by the pad); c2 (no pad) =
22 (frame 16 short).

## (f) Where the method fell short
The header comment's own claim — "a3 home must be read once into $t0 … Unpinned, gcc picks $v1" — was true of the
wrapper spelling only; the "homes" were reload slots, which the allocation table would not show (neither pseudo gets a
hard register). Useful addition to step 3: "a register that is the first never-live call-clobbered one (`$t0` when
`$v0-$a3` are used) on a load from sp = a reload register: make the value a spilled pseudo, do not pin it".

## (g) Structs
The fix REMOVED a struct (the `MH` 8-byte home wrapper) rather than adding one. The OBJ598 entry struct is already
used; its `b1` field access was the wrong spelling for arms 0/1 (a byte field read is a separate QImode MEM and never
creates the combine-split phantom), so here a struct field was the MISSING-piece's opposite: the bytes want the word
read and shifted.
