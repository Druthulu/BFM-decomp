# func_8017EF88 (src/ov_SC05_001/ov_SC05_001_jr_8017BEBC.c) — d10, P36 S104

**RESULT: score 0 in plain C, zero levers** (before: 3 pins `$8/$7/$3` + 2 keepalives + `do { } while (0)` + dead
`s32 pad[2]`; after: none of them). The sibling **func_8017F040 (same TU) closes by the same move at score 0**
(`scratch/f040_body.c`). Both verified with `tools/delever_search.py --try … --body`.

## (a) The residual
REG only, 46 = 46 instructions. Target: the three packed arguments sit in `$t0/$a3/$v1` (arg0/arg1/arg2) and EVERY
other global — the cx load temp, the ax/bx/cx/cy s16 copies — avoids those three registers (`$t1..$t4`). The free
body gave the packs `$v0/$v1/$a3` (local-alloc, block 8 only) and let the globals use `$v1/$a3/$t0`. The frame
(vars=56) matched only because of the dead `pad[2]`.

## (b) Mechanism (proved on bytes and in the dumps, `scratch/dumps_win/`)
The original builds each NCLIP argument as a **register union** (`union { struct { s16 x, y; } v; s32 sxy; }`)
by storing its two fields, then passes the word.
1. A 4-byte union with an `s32` member has SImode, so it lives in a pseudo. A field store into a REG goes through
   `store_bit_field`; MIPS `insv` FAILs for a non-MEM operand (`config/mips/mips.md:2901-2921`), so
   `store_fixed_bit_field` emits read-modify-write `u = (u & mask) | value` (`expmed.c:689-697` and, ior below it).
2. The first field store READS the uninitialised union, so flow marks all three union pseudos live at the
   function entry and at the start of every block down to the call (`.flow`: "Registers live at start: 4 5 6 29 30
   75 76 77", blocks 0 through 8).
3. combine folds each insert pair into `andi`/`sll`/`or`, so the read vanishes from the insns. But global.c seeds
   each block's conflict scan from flow's **pre-combine** `basic_block_live_at_start` (`global.c:640-660`), so the
   three unions still conflict with every pseudo in the function (`.greg`: 75/76/77 conflict with 72-85, 95).
   They are allocated as globals in priority order 77 (c) → `$v1`, 76 (b) → `$a3`, 75 (a) → `$t0`. `$v0` is
   skipped because the block-local `slt`/load temps hold it, and `$a0-$a2` because the parameters conflict. Every
   later global then skips `$v1/$a3/$t0`. That is exactly what the `$8/$7/$3` pins plus the "live from entry"
   keepalive were faking. The second keepalive (ax/bx/cx live past the masks) was faking the same conflicts.
4. The frame: the 7th "ST_REGS or none" pseudo (flow counts it, combine eliminates it, reload gives it an 8-byte slot)
   is reg 106 = the shared `0xFFFF0000` clear mask of the three x-inserts. That is what `s32 pad[2]` was faking. The
   other six are the `ashift` halves of the s16 sign extensions (the free body had those six too, hence vars=48+8).

## (c) The move (one line)
Replace the three `la/lb/lc = (u16)x` masks + `x | ((u16)y << 16)` packs (and the pins, both keepalives, the
`do/while(0)` and `pad[2]`) with three body-local unions `a, b, c` whose `.v.x/.v.y` are assigned from the s16
locals just before the call, passing `a.sxy, b.sxy, c.sxy`. Readability extras, both byte-neutral:
`return func_800495EC(...) >= 0;` replaces `r = …; return ~r >> 31;` (emit_store_flag gives the same `nor; srl`),
and the `do { } while (0)` is simply dropped.
Also verified at 0: `union { DVECTOR2 v; s32 sxy; }` with `.v.vx/.v.vy` (`DVECTOR2` is in src/shared/engine_types.h:759)
(`scratch/dv.c`). body.c keeps the self-contained anonymous struct so the four shared copies need no header.

## (d) Generator proposal
When a body pins N values that are packed as `(u16)lo | (hi << 16)` (or any byte/half insert into a word) AND has a
keepalive `__asm__("" :: "r"(v))` reading those pinned variables BEFORE they are assigned (live-from-entry), rewrite
each packed word as a register union `{ struct { s16 lo, hi; } v; s32 w; }` (or `{ u8 b[4]; s32 w; }` for byte packs)
whose fields are assigned where the pack was, and pass `.w`. More generally, **a keepalive on a not-yet-assigned
variable near the entry means "live at entry" in the original. In plain C that is an aggregate kept in a register
and built by field stores** (store_fixed_bit_field's read-modify-write of the uninitialised word).

## (e) What did not work (bytes)
- body_free.c: 14. Free sweep's best (free_004, swap-stmts): 12. Neither can reach 0, because no statement-order or
  width move makes a local-alloc'd mask conflict with block-0 globals.
- Inlining the packs into the call (`(u16)ax | ((u16)ay << 16)` as arguments): 16/20 (COUNT, the order changes).
- `u16 la/lb/lc`: 18/20. Compare-operand flips (16 permutations): 18-24 (lose 1-2 insns).
- `y << 16` without the `(u16)` cast or `x & 0xFFFF`: 45 insns and one zombie fewer (vars=40).
- Field-only unions (loads straight into `a.v.x`, compares on the fields, no s16 locals): 57 (56 insns).
- An early-return tail `if (ay < cy) return 1; <pack; call>` instead of `if (ay >= cy) { …call… } return 1;`: 5
  (47 insns). The if-block tail is load-bearing (`scratch/early.c`).
- The union WITHOUT the `s32` member (2-aligned struct only, passed as `*(s32 *)&a`): 25, vars=72 (BLKmode, so it
  lives on the stack; `scratch/bare.c`). The s32 member is what makes the aggregate a register.
- R71 check: no lever-free same-name variant in src/ (SC05_003/SC03_029/SC05_018's func_8017EF88 are other
  functions). All copies of this text (shared headers func_8017D5F4__014cbc20.h / func_8017D6AC__703b5fd0.h,
  ov_SC03_112 / ov_SC05_005 jr_*) carry the same levers and should take the same rewrite (D5F4 = EF88's shape,
  D6AC = F040's).

## (f) Where the method fell short / what found it
The allocation table and residual pointed at "why do globals avoid three registers that local-alloc hands out
later". No statement-level move could explain a block-0 temp conflicting with block-8 values. The clue was the
FRAME. `pad[2]` was fake: the free body's vars=48 were six stale pseudos (each "ST_REGS or none", flow-counted,
combine-eliminated) and the target needed one more. That said the original had an extra eliminated temp. Together
with the keepalive's "live from entry" reading, that led to field stores into a register aggregate, and the first
`--try` of that closed. Method addition: **a dead `pad[N]` lever is evidence — count the ST_REGS/no-hard-reg pseudos
in `.lreg` (8 frame bytes each) before accepting a dead local. The missing ones name the missing construct.**

## (g) Structs question — YES, and this is the proof case
The lever existed only because the packed arguments were written as integer arithmetic instead of the aggregate the
original used. The struct/union type moves the decision in flow → global (live-at-entry from the read-modify-write
field insert, `expmed.c:689-697`, and pre-combine live sets feeding `global.c:640-660`), not the expr.c/sched
aggregate-alias channel. The struct is a 4-byte SImode union `{ struct { s16 x, y; } v; s32 sxy; }` (PsyQ DVECTOR
overlaid with a long, i.e. an SXY GTE register value), one per NCLIP argument. It must contain a 32-bit-aligned
member so the aggregate is SImode (a bare `DVECTOR` is 2-aligned, BLKmode under STRICT_ALIGNMENT, and would go to the stack).
Tested on bytes with a body-local declaration: score 0.
