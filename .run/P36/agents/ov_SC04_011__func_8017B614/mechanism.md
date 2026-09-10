# func_8017B614 (ov_SC04_011) — T7 residue exemplar

Levers in the tree body: `register u8 *src __asm__("$16")` (pin), an `__asm__ __volatile__("" : "=r"(src) : "0"(...))`
(launder) and a bare `__asm__ __volatile__("")` (scheduling barrier). All three NEEDED by the byte oracle.
Lever-free start: **score 13**; mechanical search best **7**. This agent: **score 6** (see `body.c`), lever-free.

## (a) The residual in one sentence

Two independent residuals: (1) the lever-free body keeps `param_2` in `$s0` and compares `$s0` (target compares `$a1`
and copies `$a1 -> $s0` *after* the branch), and (2) sched1 hoists the first `li const; sh const,SYM` pair above the run
of six `lh` loads that the target emits first.

## (b) The passes and the decisions read (source, `file:line`)

### Residual 1 — `s0 -> a1` on `param_2` (PROVEN on bytes)

* `config/mips/mips.md:3587` `movstrsi_internal` declares **four `(clobber (match_scratch:SI "=&d"))`** early-clobber
  scratches. `config/mips/mips.c:2331 expand_block_move` -> `copy_addr_to_reg` puts the source address in a pseudo, but
  `cse.c` `canon_reg`/`make_regs_eqv` (`cse.c:826-858`) folds that copy back onto `param_2`'s own pseudo, so
  `param_2` is the address operand and is **live across both block moves**.
* `local-alloc.c` allocates those scratches first and hands them `$v0,$v1,$a0,$a1` (verified in the `.lreg` dump:
  `(clobber (reg:SI 5 a1))` on both `movstrsi_internal` insns).
* `global.c` then records `;; 73 conflicts: 72 73 2 3 4 5 29` for `param_2` — it conflicts with `$a1` — so the
  copy preference from the prologue `(set reg73 (reg a1))` is masked out (`find_reg` `global.c:1000-1031`) and the
  *plain* preference `16` wins. That preference comes from `set_preference` (`global.c:1534-1600`): the shift
  `(set off (ashift param_2 4))` has a dest that local-alloc renumbered to `$s0`, and `set_preference` strips the
  expression (`GET_RTX_FORMAT(...)[0]=='e'` -> `src = XEXP(src,0)`), so `param_2` inherits a preference for `$s0`.
  Dump evidence: tree `;; 73 preferences: 5 16` -> `73 in 5`; lever-free `;; 73 preferences: 16` -> `73 in 16`.
* Fix: `param_2` must **die before the first `movstrsi`**, i.e. a real copy insn must survive cse, and the copy's
  destination must land in `$s0`. Both are achieved by ONE source move (see (c)).

### Residual 2 — the `li 1; sh D_801F1638` hoist (PROVEN on bytes)

* Attribution control: recompiling the same TU with `-fno-schedule-insns` puts the tail back in source order and
  reproduces the target's tail exactly. So it is **sched1**, not sched2, not the assembler.
* `sched.c:395-437 init_alias_analysis` records `reg_known_value[regno]` for every pseudo with ONE set carrying a
  `REG_EQUAL`/`REG_EQUIV` note. `p794 = &D_801EECD4` gets `reg_known_value = (symbol_ref D_801EECD4)`, so the oracle
  disambiguates `(mem:HI (reg p794))` from `(mem:HI (symbol_ref D_801F1638))` and sched1 is free to move the store
  across the loads. It moves exactly ONE `li const; sh` pair (whichever comes first — swapping the two statements
  moves `li 30` instead, byte-proven).
* Fix: a `do { ... } while (0)` around the `D_8012694C = 0;` + the six loads. LOOP notes survive to sched1, which
  treats a mid-block LOOP_BEG/END as a total barrier (`sched.c:2058-2074`), so the store cannot be hoisted into the
  load run and the load run cannot be hoisted above the `sb`. This is `residual_moves.md` rank 7 (R7), applied to a
  *block* rather than to a single statement — a single-statement wrap (`do { D_801F1638 = 1; } while (0);`) fixes the
  `sh` but lets the `sb zero,D_8012694C` sink below the loads (score 10); two separate wraps score 8; the one wrap
  around the `sb` **plus** the loads scores 6.

## (c) The source moves that closed them

1. **One `s32 src` for the source address in BOTH arms of the `if`** (declared at function scope):
   * then-arm `src = param_2;` — a copy cse cannot fold away, because `src` is now a multi-block pseudo whose class
     is not `param_2`'s; `param_2` dies at that copy, loses the `$a1` conflict and takes `$a1` (copy preference).
   * else-arm `src = ((u32)param_2) * 0x10;` then `src = (s32)&D_80193D6C[src + 8];` — `src` also carries the
     offset and the second call's address, so it crosses the first `jal`, is a call-crossing global allocno and
     first-fits `$s0`, which is exactly the register the target uses in both arms.
   This move alone takes 13 -> 12 and makes **every register in the function correct**.
2. **`do { D_8012694C = 0; <the six loads> } while (0);`** in the tail — the sched1 barrier above. 12 -> 6.

Remaining 6 points: the else arm's schedule. Target `move a0,s1 / sll / la / addu a1 / addiu a2,sp,16 / addiu v0,v0,8
/ jal / addu s0,s0,v0(delay)`; mine `sll / la / addu a1 / addiu v0,v0,8 / addu s0,s0,v0 / move a0,s1 / jal /
addiu a2,sp,16(delay)`. Cause read from the `.sched` dump: reusing `src` as its own destination adds
`(insn_list:REG_DEP_ANTI 47)` on the second address insn (a WAR that the two-variable spelling does not have), which
lifts that insn's rank and pushes the two call-argument set-ups to the end of the block.

## (d) GENERATOR PROPOSAL

**R19 "one variable for the whole live chain":** when the residual is `register pairs: sN -> aM` on a *parameter*
whose only conflict with `$aM` comes from a `movstrsi_internal`/library-clobber insn, rewrite the body so that the
value the clobbering insn addresses is a **single named local that is also assigned in the sibling arm of the same
`if`** (so it becomes a multi-block, call-crossing allocno) — i.e. merge the per-arm temporaries of the two arms into
one variable. Mechanically: for each `if/else` where arm A holds a pointer temp and arm B holds an address temp of
the same width, emit the candidate that uses one declaration for both.

**R20 "barrier the load run":** when the residual is `delete <li const; store SYM>` early + `insert` the same three
instructions late, wrap the *statement run that must stay put* (the preceding side-effect store plus every load) in
`do { ... } while (0)`. The existing R7 wraps ONE statement; the measurement here says the wrap must cover the whole
run — one statement scores 10, two separate wraps 8, the run-wrap 6.

## (e) What did NOT work (byte evidence)

* `u8 *src` local to the then-arm, with or without `param_2 = 0;` to break the cse class: the copy survives
  (`move v0,a1`) but `src` is a **block-local** qty, so `find_free_reg` first-fits `$v0` — score 23, register
  rotation `v0->s0, v1->v0, a0->v1`.
* Merging `src` with the tail's `p78C` (score 37) or `p794` (61): the global allocno is allocated *after* local-alloc
  has given the block-3 local `$s0`, so `src` lands in `$s1`.
* `src` merged with the else-arm offset only (`K1`): `$a3` — a non-call-crossing global first-fits past the four
  scratch clobbers to `$a3`.
* `do { src = (u8*)param_2; } while (0);` — the LOOP notes do NOT stop cse folding the copy here (score 13,
  unchanged); only a genuine second pseudo does.
* Routing the two constant stores through a pointer (`s16 *pf = &D_801F1638; *pf = 1;`) to blind
  `reg_known_value`: cse folds the address back into the `(mem (symbol_ref))`, no change (12).
* Giving the tail loads register addresses (`p794[0..2]`, `p78C[0..2]`): 28. Dropping the pointers entirely
  (`D_80126990 = D_801EECD4;`): 25 and +2 instructions.
* Reordering `D_801F1638 = 1;` / `D_801EEC5C = 0x1E;` (before the loads, after the loads, after the six stores,
  swapped): all 12 — sched1 always hoists whichever pair comes first. Source order is not the knob.
* `do { D_801F1638 = 1; D_801EEC5C = 0x1E; } while (0);` with no other wrap: 10 (the `sb` sinks).
* Else-arm respellings that keep two variables (`a1addr`/`a2addr`) lose `$s0` for the offset — the offset only gets
  `$s0` by `combine_regs` tying it to the call-crossing second address, and that tie needs BOTH to be local qtys.

### Extra negatives on the remaining else-arm ORDER residual (all still 6, byte-measured)

`do { ... } while (0)` around the three address statements / around the shift alone / around each call; hoisting
`(s32)&buf[0]`/`(s32)&buf[8]` or `param_1` into locals; writing the addresses as `(s32)D_80193D6C + src` instead of
`&D_80193D6C[src]`; and four spellings that push the `src` update into a call argument with the comma operator
(`func(p1, a1addr, (src = ..., (s32)&buf[0]))` and three variants) — every one reproduces the same schedule. The
residual is not reachable from the source side while `src` is both read and written in that block: `combine.c`
`can_combine_p` refuses to fold `a1addr = src + base` into `(set (reg a1) a1addr)` because `src` is modified between
them, so the arg set-up stays a separate insn and sched1 ranks it after the address chain. The two-variable spelling
(`a1addr`/`a2addr`, no `src`) does get the fold and the target's order, but then the offset loses `$s0` (it only gets
`$s0` by `combine_regs` tying it to the call-crossing second address, `local-alloc.c:1287-1295`, and that tie needs
both pseudos to be block-local quantities). Keeping the else arm untouched and giving `src` `$s0` some other way was
also refuted: a non-call-crossing global allocno first-fits in regno order and stops at `$a3` (`global.c:957-985`,
no `REG_ALLOC_ORDER` on MIPS), and every hard-reg preference `set_preference` could give it is masked by a conflict.

## (f) Where the method fell short

* `sites.txt` says which levers are NEEDED but not what each one *does*; the pin and the launder here are one
  mechanism (split a live range) and the barrier is a different one. Reading the `.greg` `;; N conflicts` /
  `;; N preferences` lines for the levered vs lever-free build (two `cc1 -dg` runs, ~5 s) answered residual 1
  immediately and should be step 0 of the playbook for any `REG` residual class.
* `-fno-schedule-insns` as an attribution control for an ORDER residual is cheap and decisive; it is not in the brief.
* The pack's `history.txt` reports the mechanical best (7) and its path but not the residual *after* that path, so the
  agent cannot tell which half of the score the mechanical move already closed. Printing the post-path residual (the
  `--explain --path` output) in the pack would save a compile-and-read cycle.
