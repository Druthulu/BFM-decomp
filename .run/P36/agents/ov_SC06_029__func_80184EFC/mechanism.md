# func_80184EFC (ov_SC06_029) — agent e22, P36 S104

**Result: score 0, ZERO levers (both pins, $16 and $2, gone). Levers 2 -> 0.** Plain C: no asm, no volatile, no alias,
no signature change.

## (a) The residual
Lever-free: score 35 (COUNT, 66 vs 63): an extra callee-saved register (`move s1,s0`, 32-byte frame) and a
v0/v1/a0 rotation through the flags/tag block (`sub` v0 vs v1, flags temp a0 vs v0, tag accumulator a0 vs v0,
0x40000000 v1 vs a0, the `lh 112` test v0 vs v1).

## (b) The passes and decisions
1. `s32 s0; s0 = a0;` — the parameter pseudo and its copy survive as TWO callee-saved pseudos (the copy is live past
   calls on two paths); deleting the copy and using `a0` (step 15 d24) removes the `$16` pin's job: 35 -> 16 alone.
2. `tmp` reused for the flags update AND the tag accumulator dies twice (at the `sh 44` and at the `sw 88`), so
   local-alloc refuses it (`reg_n_deaths == 1`, local-alloc.c:472) and global-alloc sees v0 already taken by the
   locals `sub` and the `lh 112` test value -> tmp lands in a0 (localalloc_sim: `sub` q0 -> v0, r83 -> v1, 0 mismatches).
   The target's assignment (tag in v0 first, `sub` v1, 0x40000000 a0, test value v1) is what local-alloc gives when
   the tag is a LOCAL quantity of high priority.
3. Splitting the temp naively (one `tag` variable, `tag |= C` three times) makes tag single-death but lets sched1 hoist
   the whole tag chain above the flags load/store (21): the chain's insns have priority 1 (`priority()` sched.c:1425,
   latency-1 chain), the flags store priority 3, and a 4-set `tag` gets no birthing boost (`birthing_insn_p`
   sched.c:2469 needs `reg_n_sets == 1`), so the backward scheduler picks the store first = places it last.
4. Written as ONE expression, `(s32)&D_80190A08 | 0x10000000 | 0x20000000 | 0x40000000` (fold cannot associate the
   constants onto a SYMBOL address, so the three `or`s survive), every step is a fresh single-set pseudo: each gets
   the birthing boost (adjust_priority, sched.c:2507-2544) the moment its consumer is scheduled, so the chain is placed
   right before the `sw 88` — after the flags store — and the tag quantity is local, ranks first, takes v0.
   Proven on bytes: a2 (one 4-set tag var) 21 vs a6 (four single-set vars g1..g4) 0 vs a8 (one expression) 0.

## (c) The moves
1. delete `s0 = a0`, use the parameter (`$16` pin gone).
2. flags update as `*(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;` (no shared temp).
3. tag as one expression `(s32)&D_80190A08 | 0x10000000 | 0x20000000 | 0x40000000` (the `$2` pin gone).
   (cosmetic, all 0: the cast on func_8012C1B8 dropped — the TU's prototype already returns s32; the `val`/`sub2`/`nib`
   temps folded into one statement with `D_80190810[nib * 6]`; `+= 1` on the u16 counter.)
   Six other lever-free TUs spell the same tag the same way (e.g. ov_SC06_022 `(s32)&D_80190F8C | 0x10000000 |
   0x40000000`, ov_SC02_011:686), which corroborates the idiom.

## (d) Generator proposal
When a register residual sits on a temp that is assigned a chain `t = X; t = t | C1; t = t | C2; ...; *M = t;`
(or a temp reused for two unrelated chains), rewrite the chain as ONE expression stored directly (`*M = X | C1 | C2`)
and any read-modify-write through the temp as `*P |= K;` — the single-set pseudos restore sched1's birthing boost and
local-alloc eligibility at once.

## (e) Tried and failed (bytes)
- a1 (only the `s0` copy removed) 16; a2/a3/a4 (shared temp split into flags var + ONE 4-set tag var) 21 — the
  chain hoists above the flags store (the tree header's warning, confirmed, and why the old author kept one shared
  pseudo plus a $2 pin); a5 (flags temp as u16 `nib`) 12.
- s104_all regen best 11 (R10 param-alias + R6 inline tmp): the generators inline one `tmp` step at a time and never
  produce the whole chain as one expression.

## (f) Where the method fell short
Nothing in steps 12-16 names "a multi-set temp kills the birthing boost" as a SCHEDULING fact (step 12's d8 covers
width, the 80185D44 header covers a 2-set s16); the `.sched` ready list (`(3)` vs `(7f000001)`) made it visible.

## (g) Structs
Not needed here and would not change the closing decision (register-only chain; the flags/tag stores are to
different objects). An object struct for `a0` (0x1C/0x20/0x2C/0x34/0x58/0x64/0x70) would read better but is
cosmetic; untested on bytes.
