---
ts: 2026-10-22T10:41:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IR3ghP0H5qRTaPVUzb1Y
---
Now let me:
1. Copy the best bodies to best.c per item.
2. Append to each item's notes.md.
3. Append to moves.md.
4. Write the log file.
5. Delete the dump dirs.

Let me do the best.c copies and the notes.md appends.

For notes.md, I'll append a section with my findings. Let me write them per item:

**func_80184828** (append):
```
## RM2 retry (2026-10-22): WALL, best 1 — 55 scored tries, ~37 min
New evidence (gcc 2.7.2 source, tools/reference/gcc-2.7.2/):
- combine.c `simplify_rtx` (the first thing it does): "If this is a commutative
  operation, put a constant last and a complex expression first" — with
  XEXP(x,0)=SYMBOL_REF (CONSTANT_P) and XEXP(x,1)=REG it SWAPS the plus.
  So the address tree (sym, idx) becomes (idx, sym) -> `addu v0,v0,a1`.
- The target's tree must have had the pointer in a REG at combine time; the
  launder's `=r` output makes p a hard-reg pseudo, and that is the only thing
  that keeps the pointer first.
Tried (all 1): pointer types u8/u16/u32/s32/char/void; `&D_80195AF6[0]`;
  casts through s32/u32; the struct-member spelling `p[idx].f4` and
  `((D_80195AF6_t *)((u8 *)p + off))->f4`; the address computed through a temp
  pointer (`pa = (u8 *)p + off`); the +4 folded into `off`; the index written
  as `<< 3`; u32/u16 index; the pointer used twice (newval through p); decl
  order; the assignment before/after the call; the load through the symbol.
Evidence: the .rtl/.cse dumps show the address as
  `(plus (symbol_ref D_80195AF6) (reg 118))` and the .combine dump as
  `(plus (reg 118) (symbol_ref))` — the swap is combine's.
Wall tag `combine-commutative-swap` (defined here).
```

**func_8018483C**:
```
## RM2 retry (2026-10-22): WALL, best 5 — 34 scored tries, ~20 min
New evidence: the .rtl dump of the lever-free body (`pb` temp + `p = pb`)
  shows ONE set insn for the address:
  `(set (reg/v:SI 81) (symbol_ref D_800B99DC))` — the copy `p = pb` is already
  gone at expand time, so cse never sees it. The copy the target keeps
  (`lui v0; addiu v0; move s0,v0`) needs TWO pseudos: a short-lived one for
  the constant and the call-crossing one in $s0.
  Per cookbook §195-I any SECOND set of the pseudo kills the fold — but the
  only second sets available are identity statements (`p = p`), which the
  brief rules out as launders.
Tried (all >= 5): the address used twice (the direct load, 115 insns); the
  pointer through u8/u16/u32/s32; `&D_800B99DC[0]`; a `pb` temp in a block;
  the pointer assigned before the early return; the loop as for/while/do-while;
  the `for` init carrying the pointer; the assignment order q/p/r; the
  `D_801E86C0` read order; `*p += c0`; the call args; the frame order.
Wall tag `cse-const-addr-copy` (defined here).
```

**func_8017D81C**:
```
## RM2 retry (2026-10-22): WALL, best 12 — 104 scored tries, ~15 min
Mechanism confirmed: the three constants are materialised where they are
BORN.  With the launder, the asm READS x/y/z at the assignment, so the
pseudos are born there (insns 19-21 in $v1/$a1/$a0).  Without it, cse
forwards the constant into every use and the pseudo is born at the FIRST
USE, so the `li` lands just before the first store that needs it.
Diagnostic: moving the x-store to the front (var/w17_store_first.c) puts the
`li v1,-1664` at insn 18 (the target's slot) and drops the residual from 20
to 12 — the li's really do follow the first use, and the target's store
order forbids that.  So the target's li's can only come from the launder's
birth-at-assignment.
Tried (all 20 unless noted): the constants' spellings (hex/decimal/0-minus/
cast); the assignment order x/y/z, z/y/x, y/x/z; the assignment before the
call; the declaration order; the store order (every early-store permutation);
the do-while as for/while; the loop body's order; the store types (s32/u32/
pointer casts); the pin on z kept (it stays a0 in both).
Best 12 = var/w17_store_first.c (a different residual class: the li's early
but the store order moved).
Wall tag `cse-const-holder` (defined here).
```

**func_8018389C**:
```
## RM2 retry (2026-10-22): WALL, best 14 — 125 scored tries, ~15 min
Mechanism confirmed with the dumps: the .rtl dump has TWO constant sets for
the shared magic 1717986919 (0x66666667) — one per division — and cse keeps
one.  In the .sched dump our magic's set sits immediately before its first
mult (insn 357 -> the mults at 300/312); the target materialises it at the
TAIL TOP in $a0 (insns 120-121) and both multiplies use that one register.
The launder's asm (priority 1) is what keeps the materialisation from
sinking to its use.
Tried (all 14 unless noted): the compound division split into two statements
(the best), the numerator in a named temp, the x-division split/two-step,
  the two divisions swapped, the divisor spelled 160/20/0xA0/0x14, unsigned
  division, the widths u32/u16/s16 for x/ax/vol, the ax computation as
  if/else, the && folds and their operand order, the condition's constants,
  the flg temp inlined, the call argument spellings, the L.v[] assignment
  order, the ternary for `x == 0x10`.
Wall tag `sched1-birth-boost` (in walls.txt).
```

**func_8017DA30**:
```
## RM2 retry (2026-10-22): WALL, best 4 — 42 scored tries, ~22 min
Mechanism confirmed from both asm listings: the target's else arm is
  move a0,s1 / addiu a1,s0,36 / lui a2 / addiu a2 / li v0,51 / jal /
  sb v0,39(a0)      <- the store in the delay slot
while every lever-free spelling ends
  move a0,s1 / lui a2 / addiu a2 / jal / addiu a1,s0,36 (delay slot) /
  li v0,51 / sb v0,39(a0)
The a1 setup (ent+0x24) is sunk into the delay slot because it is born at
the call; the target has it at the arm top, i.e. the value was computed
early — which is exactly what the launder's asm (priority 1) forces.
Tried (all 4 unless noted): the store before/after the call; the assignment
  order q/p/e, p/q/e, q/e/p, e/p/q; the store's spellings (struct member,
  u8 cast, byte offset); the call's args as expressions; the call's first
  arg = sub instead of q (5); the pin on q removed (5, the store's base
  changes); hw before/after the call (12/8); the store's value through a
  temp; the arg order swapped (8).
Wall tag `sched1-argcopy-hoist` (in walls.txt).
```

Now the moves.md lines (append one per item):
"launder | func_80184828 | WALL combine-commutative-swap — combine simplify_rtx puts the constant last in a commutative plus; the pointer must be a REG (launder hard-reg pseudo) to stay first (RM2)"

Let me write all this with a Python script (heredocs are error-prone with backticks).

Then the log file.

Let me write the notes appends + moves.md now.
