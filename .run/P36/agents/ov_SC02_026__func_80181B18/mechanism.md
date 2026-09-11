# func_80181B18 (ov_SC02_026_jr_8017C180.c) — agent d7, P36 S104

**STATUS: CLOSED in plain C. Score 0. Levers 3 -> 0** (pin $17, barrier, pin $3 all gone; no asm, no pin, no volatile, no
do-while). `PACK/body.c` has the text. The same text (with the name changed) also scores 0 on all five copies elsewhere:
func_801814FC (ov_SC03_098), func_80186F1C (ov_SC03_091), func_80180CF4 (ov_SC03_094), func_80186074 (ov_SC03_090),
func_8017F96C (ov_SC02_035). Each was checked with `--try` against its own TU. So 6 bodies and 18 levers.

The move, in one sentence: **declare `sub`, `v` and `cnt` inside the `case 2: { }` and `case 3: { }` blocks, and keep
`t` at function scope.**

## (a) The residual: two independent defects, counted first (108 vs 108 ins, no count gap)
1. **Callee-saved swap** (s0<->s1, 35 sites): the target keeps `ent` in $s1 and `state` and `sub` in $s0. The lever-free
   body gives `ent` $s0 (and a different prologue order, which follows from the swap).
2. **v0/v1 swap in case 3** (6 sites): the target has `sll v1,a0,12; sra v1,v1,12; li v0,8192; subu v0,v0,v1`. The
   lever-free body puts the shifted value in v0 and the 8192 constant in v1.

## (b) Pass and decision (all PROVEN on bytes and on the .lreg/.greg dumps)
1. **Swap 1 is decided by local-alloc, not by global's priority order.** The lever-free `.greg` order is `77 78 76 74 73 75`
   (global.c:587-610 `allocno_compare`). ent r74 = 4*23/83 = 11084, state r73 = 2*7/17 = 8235, sub r75 = 3*8/32 = 7500.
   ent is allocated first and takes $s0. The tree's `sub` was ONE variable shared by cases 2 and 3, so flow marked it
   REG_BLOCK_GLOBAL (flow.c:2061 / 2497) and it went to global allocation.
   With a per-case `sub`, each copy lives in ONE basic block (a CALL_INSN does not end a block in 2.7.2) and crosses one
   call (`func_8004787C`). local-alloc assigns it, and `find_free_reg` (local-alloc.c:2101-2106) excludes
   `call_used_reg_set` for a quantity with `qty_n_calls_crossed > 0`. So it gets the first call-saved register, **$s0**
   (`.lreg`: `;; Register 85 in 16.`, `;; Register 108 in 16.`). global.c then records that hard reg as a conflict of every
   allocno live across it (global.c:1256 `IOR_HARD_REG_SET (hard_reg_conflicts[ialloc], hard_regs_live)`). The `.greg`
   now lists ent r72 as `conflicts v0,v1,a0,a1,s0,sp`, so ent takes **$s1** and state, which never meets the sub copies,
   takes $s0. That is the target. The priorities did not change (ent is still 11084, state still 8235). The conflict
   decides it, not the order.
   One local `sub` is enough: `sub` per case in case 2 only, or in case 3 only, both score 0 (v/s3.c, v/s4.c).
2. **Swap 2: local-alloc `combine_regs`** (local-alloc.c:1722). The refusal at local-alloc.c:1773 is "Can't combine if
   SREG is not a register we can allocate", `reg_qty[sreg] == -1`. The destination `v` of `0x2000 - lo` was ONE variable
   set in two blocks, so it was not local and could not be tied to the dying constant pseudo. The two local quantities
   then race in `qty_compare` (local-alloc.c:1579). lo's tied quantity (r111+r110, 4 refs, span 3) scores 2*4/3 and
   beats the constant r112 (2 refs, span 1), which scores 2. So lo takes v0. With `v` local to case 3, block_alloc tries
   operand 1 first and ties v to the constant. qty(r112+v) has 5 refs over span 3 and scores 2*5/3, which beats 2*4/3.
   The constant/v quantity takes v0 and lo takes v1, as in the target. The byte check: shared `v` scores 4 and per-case
   `v` scores 0 (v/s2_vshared.c).
3. **`t` must stay shared** (v/s2_tcase.c: 106 ins, score 43). A per-case `t` becomes block-local, local-alloc ties it to
   the call's $v0, and the target's `move a0,v0` disappears (2 instructions short). Shared, `t` is a global allocno that
   global.c puts in $a0 by copy preference. The scoping has to be exactly as in body.c.

## (c) Moves (in body.c)
- `sub` declared per case (`case 2: {` / `case 3: {` blocks): replaces pin $17 and the barrier.
- `v` declared per case: replaces pin $3.
- `cnt` per case: neutral (it scores 0 either way), kept for symmetry. `lo` and `w` are inlined, which is neutral.
- `state` stays a function-scope local stored by case 1. Switching directly on `*(u16 *)(ent + 0x34)` and storing the
  constant 1 compiles identically, because cse's jump equivalence canonicalises the store to the index register. So
  `ent->timer = 1` is an equally valid spelling.

## (d) Generator proposal
**When a register residual is a callee-saved permutation (or a v0/v1 swap around `li K; op d,K,x`) and the body has a
function-scope local that is only assigned and used inside separate switch cases / if-arms, emit one candidate per
such local with the declaration moved into each arm's block. This works because a block-local pseudo that crosses a call
is placed in $s0 by local-alloc before global runs.** Try the locals one at a time and then together, and keep any
local whose per-arm split scores worse shared (`t` here). It is the inverse of S103 c18's MERGE move. A tool can predict
it without compiling. In the `.lreg` of the lever-free body, look for a pseudo with "dies in N>1 places; crosses K
calls" whose uses fall in disjoint blocks. If it is split, it becomes a `crosses 1 call` local, and that local claims
the first call-saved register.

## (e) Tried, did not work (byte evidence)
- The free sweep's `do { state = ...; } while (0)` plus the `v` split scores 0. It does so by doubling state's refs
  (flow.c:1401 loop_depth, :2067), giving state 14117 against ent 11566. That is a lever and is no longer needed.
- These all score 39, identical to the lever-free body: `u16 state`; `switch (state = ...)`; `switch ((s32)state)` with a
  u16 state; `++`/`+=` forms of the 0x34 increment; `++*(s32 *)(ent + 0x1C) < 9`; the parameter named `ent` with no
  copy; a `(u16)state` store.
- `switch ((u16)state)` and `switch (state & 0xFFFF)` score 44 (an extra andi). Loading state before `ent = a0` scores 47.
- Everything per case including `t` (v/cleanA.c, v/s2_tcase.c) scores 43, 106 ins (see b3).

## (f) Where the method fell short
- The allocation table printed global priorities and made the defect look like a priority race (state 8235 against ent
  11084). All my first hypotheses were ref/live arithmetic, and the two levers the sweep found (the do-while, and the
  tree's pin) both work on priority. The real channel is a **hard-register conflict injected by local-alloc**, and that
  is visible only in the `.lreg` `Register N in 16.` lines and in the `conflicts ... s0` column of the `.greg` table
  after the move. Suggestion for `tools/alloc_table.py`: on a callee-saved residual, print which callee-saved hard regs
  local-alloc already handed out (`Register N in 16..23` for pseudos with `crosses K calls` in one block) next to the
  global order. "s0 is already taken by a local" is the question to ask before any priority arithmetic.
- METHOD step 3 lists the c1/c8 split (a local reused across groups dies more than once) as a PERMUTATION fix for
  local-alloc (local-alloc.c:472). This case is the same split, but its effect runs through global's conflicts. Worth
  one line in the method: "a split local that crosses a call claims $s0 in local-alloc and pushes a global allocno to
  $s1".

## (g) Structs
**Not the missing piece here. PROVEN on bytes with body-local struct declarations.** I built two versions with
`struct Ent_80181B18` (`u16 mode @0x02`, `s32 timer @0x1C`, `struct Sub_80181B18 *sub @0x20`, `u16 state @0x34`) and
`struct Sub_80181B18` (`s16 sx @0x18, sy @0x1A, sz @0x1C`), with every access a field access:
- with the tree's scoping (`sub`/`v` shared by the two cases): score **43**, identical to the cast-based lever-free body
  (scratch/v/st_shared.c);
- with body.c's per-case scoping: score **0** (scratch/v/st.c).
The levers stood in for pass decisions made by variable **scope** (block-locality in flow.c, then local-alloc), not by
memory aliasing. The `expr.c:4568-4577` MEM_IN_STRUCT channel has nothing to act on: the residual has no load/store
order defect and no count gap. Struct typing is readability-neutral here. It is fine to adopt it in the structs phase
(these fields recur across the six copies), but it neither helps nor hurts the match.
