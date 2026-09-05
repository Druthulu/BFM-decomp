# func_800CF3E8 (md_MAIN_003, 469 ins) — S83 bounded second look at the NEAR-27 row

Arm: opus. Prior best: `.run/P32/t3/opus/func_800CF3E8.c`, closeness **27** at 469/469, blocks 1–2
byte-exact (idx 0–361). Deliverable this session: `.run/P32/t3/opus/func_800CF3E8_s83.c` — **byte-identical
to the prior best** (nothing beat it). `match_one` 27/469, `rtu_match` in the real TU agrees (27, no decl
conflict).

## The prior report's root cause is CONFIRMED but MIS-ATTRIBUTED, and the named lever is REFUTED

Byte-verified from `-dr` (rtl-gen) and `-dS` (sched1) dumps of the actual draft:

* **The RTL fact is exactly as reported.** The p6 field stores are `(mem/s:QI (plus (reg/v:SI 3 v1) N))`
  while `*(u32*)p6` is `(mem:SI (reg:SI 429))` — pseudo 429 is the pre-copy address
  (`(set (reg 429) (plus …))`, `(set (reg/v:SI 3 v1) (reg 429))`). Different base rtx ⇒
  `memrefs_conflict_p` cannot compare offsets ⇒ the tag load true-depends on all ten field stores.
* **It is NOT `cse.c:canon_reg`.** `canon_reg` never touches the load: it returns hard regs unchanged, and
  the `-dr` dump shows the load is born as `(mem:SI (reg/v:SI 3 v1))` — the hard reg. The pseudo appears
  only after cse. The actual mechanism is **`cse.c:find_best_addr`**, reached from `fold_rtx`'s `case MEM`:
  it looks the whole address up in the hash table and swaps in the cheapest equivalent, and cse's
  `COST(X)` macro scores a pseudo with a valid qty **0** and a hard reg **1**. A whole-word access at
  offset 0 is a bare REG address, so it IS in the table and gets swapped; a field access is
  `(plus (reg 3) N)`, which is not a table value, so it keeps the hard reg. **That asymmetry is the whole
  bug**, and it explains why the report's "leading `u32 tag` struct reshape" was inert (a COMPONENT_REF at
  offset 0 has the same bare-REG address).
* **Why the pseudo copy exists at all and cannot be removed from C:** `expand_expr` contains
  *"If will do cse, generate all results into pseudo registers"* and drops any hard-reg target at -O2. So
  every assignment to a `register …asm()` local is `pseudo → hard reg`. Measured: `p6 = b_ + idx`
  (PLUS_EXPR instead of ADDR_EXPR), `p6 = (Sprt24*)((u8*)b_ + idx*24)`, `p6 = b_; p6 += idx;` — all still
  emit `(set (reg 429) …) (set (reg 3) (reg 429))`. All 27.
* **The task's named lever (an unpinned ALIAS for the load) is REFUTED — 5/5 inert at 27.** It cannot work
  by construction: cse puts the alias in the SAME quantity, so `find_best_addr` swaps the alias's address
  to the same pseudo 429 (or the alias's own pseudo) — either way the base is still ≠ the stores'
  `(reg 3)`. Variants measured: alias born from p6 right after birth (load only); alias used for the tag
  load AND store; alias born from the same `&b_[idx]` expression; alias declared last; alias born just
  before the ADDPRIM chain. **All 27.**

## What DOES unlock the hoist (new, and the real answer to §500 D-1's open lever)

**Launder the PINNED POINTER ITSELF, not an alias:** `__asm__("" : "=r"(p6) : "0"(p6));` right after p6's
birth. Zero bytes. It retires reg 3's cse quantity, so `find_best_addr` has no cheaper equivalent and the
load keeps `(mem:SI (reg/v:SI 3 v1))` — the SAME base rtx as the stores. Verified in `-dS`: the tag load's
LOG_LINKS collapse from eleven field stores to one (the launder). The load then hoists ~15 slots.

With the launder + `p6->w = 0x80;` moved back to its natural place (after `clut`), the p6 block goes from
"load last" to:

```
        mine (79 @ 470)                     target
  377   sb  a2,0x3(v1)                sb  $a2,0x3($v1)
  378   sw  t7,0x0(a1)                lui $a2,(0xFFFFFF>>16)
  379   lui t2,0xff                   sw  $t7,0x0($a1)
  380   ori t2,t2,0xffff              lw  $t2,0x0($v1)     <-- the hoisted tag load
  381   sb  t6,0xB(v1)                ori $a2,$a2,0xFFFF
  382   lui v0,%hi(D_800EC68C)        sb  $t6,0xB($v1)
  383   lbu v0,%lo(...)               lui $v0,%hi(D_800EC68C)
  384   lw  a2,0x0(v1)   <-- load     lbu $v0,%lo(...)
  385..399  BYTE-EXACT                BYTE-EXACT
  400   and a2,a2,t0                  lw  $v0,0x0($a1)
  401   lw  v0,0x0(a1)                and $t2,$t2,$t0
  402   nop  (load-use)               and $v0,$v0,$a2
```

So idx 0–377 and 385–399 are byte-exact; the residual is a **7-slot window (378–384) in which the load
lands 4 slots late** plus the resulting load-use `nop` (470 ins). Closeness reads 79 only because the +1
length shifts every later index. This is a *different, structurally much closer basin* than the banked 27,
but it does not close, and by the closeness metric it is worse.

## Searches run this session (all deterministic, all measured)

* alias family (5 variants) — **27, inert** (refuted above).
* address-form family: `b_ + idx`, `(Sprt24*)((u8*)b_+idx*24)`, `b_; += idx`, on p6 / p6+p5 / p6+p5+p3 —
  **27, inert** (the pseudo copy is forced by `expand_expr`).
* launder placement × `p6->w` placement, 2-D, 324 compiles — floor **27**.
* launder × `p6->w` × the p6-block `__asm__("")` fence, 3-D, 5,832 compiles — floor **27**.
* ior-operand form × launder × `p6->w`, 1,026 compiles — floor **27**.
* "fence immediately after an explicit `tag6 = *(u32*)p6;` + a named `m24 = 0xFFFFFF`" construction
  (the shape that would reproduce the target's window exactly), anchor × w × order × launder, 8,704
  compiles — floor **49**. Naming the tag and the mask as locals costs more than the window is worth.
* explicit `tag6` temp birth sweep (14 positions) — 79/126/117, never < 27.
* tail-mask pins: `register u32 t24 asm("$6")` (reuse c5's reg after its last `len` store), `mq2` reused
  for 0xFF000000, tag pinned `$10`, and both — **93/114/115/132, all worse**. The tail's `$a2`/`$t2` roles
  are a local-alloc consequence of WHERE the load lands, not something a pin can buy.
* `p5->x0`/`p5->y0` source swap for the 2-row 362/363 residual — **31, worse** (the current order is
  locally optimal; those two rows are paid for elsewhere).
* removing / moving `__asm__("" :: "r"(ot))`, fence-between-ADDPRIM-halves, naming `otv = *ot` — 39/45/143.

Harness: `.run/P32/t3/work/func_800CF3E8_s83/{gen,b1..b15,side,rtl}.py` — ~16k compiles at ~70/s with 14
processes (each variant gets its own `--work`, so `match_one` parallelises perfectly).

## Residual (unchanged): 27, class [permuter]/basin

Same single cause as the prior report, now correctly named: the target's tag load sits at idx 380 and
mine at 399, which flips local-alloc so 0xFFFFFF lands in `$t2` instead of `$a2` (the 22 `and` rows) and
shifts 378–399 by one. The blocker is no longer "unreachable" — the launder reaches it — but the freed
load lands 4 slots later than the target's and buys a load-use `nop`. Closing it needs the load pinned
BELOW the `len` store (offset 3, which genuinely overlaps the tag word) and ABOVE the `code` store, with
the 0xFFFFFF `lui` born pre-fence and its `ori` post-load; every C spelling of that I could construct
either re-fuses the constant (cse) or costs a named local that moves the whole tail.

**New cookbook material (proposed as an amendment to §500 D-1):**
1. The mechanism is `cse.c:find_best_addr` + the `COST` macro (pseudo 0 / hard reg 1), NOT `canon_reg`;
   and it fires ONLY on offset-0 (bare-REG) addresses, which is why a struct reshape does not help.
2. `expand_expr`'s "generate all results into pseudo registers" makes the pseudo copy unavoidable at -O2,
   so no address spelling can dodge it.
3. **The fix is a zero-byte launder on the PINNED variable itself** (`__asm__("" : "=r"(p) : "0"(p));`) —
   an unpinned alias is provably inert because cse unifies the quantity. Same family as §500-B
   `func_80015B6C`'s "barrier on the SOURCE variable, not on the copy".
