# The method that closed 14 of 22 in S102 (S103 addendum to PROMPT.md — read it after PROMPT.md, it takes precedence)

0. Read `PACK/neighbours.txt` first. One agent closed on its FIRST `--try` because a sibling's header spelled the crack out
   in English. **A `@stuck:` note is a CLAIM: two were refuted on bytes last session.**
1. Dump the target function WHOLE off the BASELINE SNAPSHOT (`mipsel-linux-gnu-objdump -drz .run/P36/delever/baseline/src/<tu>.o`
   — byte-identical to the original; NOT `build/`, which the coordinator's fleet gate deletes and rebuilds mid-run, S103 c15), not the residual's hunks — the hunk view scrambles moves into branch delay
   slots and hides a repeated shape. Dump your candidate's object the same way from your `PACK/scratch/` compile.
2. **COUNT FIRST.** The residual text cannot tell you whether an instruction is MISSING or the registers are WRONG; one
   agent chased a register theory for hours when cse had forwarded a just-stored value and deleted a load.
3. If instructions are missing (or extra), ask what emits them. The answers last session:
   - a dropped call argument (the call declaration was narrower than the callee — pass the argument the target passes);
   - a copy cse deleted because the producer sat immediately before it (move the producer away / reorder, generator R21);
   - a copy deleted because two locals shared a WIDTH (give one local the width the bytes prove, generator R20);
   - a block merged by cross-jump, whose equality test compares symbol names BY POINTER, so a body-local
     `extern T alias __asm__("SYM");` keeps the blocks apart at zero byte cost (this is a DECLARATION alias, allowed);
   - a call-result copy folded by combine into its single use (`combine.c:914-917`, no SMALL_REGISTER_CLASSES on MIPS).
   - (S103 c2) an EXTRA instruction per loop iteration + an extra callee-saved register = a second walked pointer
     (`q = p + k`, both stepped): loop.c strength reduction keeps both bivs. Delete `q`, write `q[i]` as `p[i+k]`; the
     field read that is textually LAST becomes the base giv (`record_giv` prepends, loop.c:4421; `combine_givs` :5494).
     Add `-dL` to the dump flags for any count gap inside a loop — its "Cannot eliminate biv" lines name the defect.
   - (S103 c4) MISSING `move`s / second `andi 0xffff` on a value used masked or cast to 16 bits: re-declare the copy's
     destination (or a post-decremented counter) as `u16`/`s16`, splitting it out of any comma declaration list. No
     PROMOTE_MODE on MIPS gcc 2.7.2, so a u16 local is a HImode pseudo: a same-mode SI copy is folded by cse's
     `(set REG0 REG1)` case (`cse.c:7440-7474`, gate `:7455` wants a REG source), a copy into HImode is a SUBREG move and
     survives; a u16 `cnt--` takes `copy_to_reg` (`expr.c:8645`). Several joint width moves may be needed at once.
   - (S103 c3/c12) a MISSING `move sK,$aN` whose source has no visible reader, but `$aN` reaches a `jal`/`jalr` (a
     dispatch-table handler) unwritten on another path: the handler READS it implicitly. Pass the value as that call's
     argument N-4 (widen the table's declaration in the body: `extern s32 (*D_x[])(void *, s32);`) AND reuse the source
     variable later as the LATER operand of a sum, so its last mention comes after the copy's (`make_regs_eqv`,
     `cse.c:846-862`; the swap `cse.c:7454`). Neither move helps alone. A consumer count that ignores calls reading
     `$a0-$a3` will call this "unreachable" — it was wrong twice.
   - (S103 c6/c10) MISSING instructions + `j` stubs into the MIDDLE of a common sequence in the target = post-reload
     CROSS-JUMP (`toplev.c:3142`, `find_cross_jump` `jump.c:2371`). Two opposite uses: (c6) a shared `goto do_call` tail
     rewritten as one call per site raises the allocator's ref count for the call's arguments, and cross-jump re-merges
     the calls AFTER allocation, so the bytes keep one; (c10) two identical tails merged that the target keeps apart —
     make their SHAPES differ (a loop's exits falling to the function's single final `return`).
   - (S103 c10) a parameter-vs-local callee-saved swap: pass the parameters through to a callee at its REAL arity (one
     more ref each for `allocno_compare`, zero bytes — jump2 deletes the self-copies, `jump.c:425-462`).
   - (S103 c5) a WHOLE missing test (a second null check): compile once with `-fno-thread-jumps`; if that reproduces the
     target, it is jump threading (`jump.c:4161`) — re-read the value from memory before the second test.
   - (S103 c7) a callee-saved swap where the loser is short on refs: duplicate a join-point statement (a pointer/counter
     step) into both arms of the if/else inside the loop — loop uses count double (`flow.c:2067`); check
     `floor_log2(refs)·refs/live` beats the rival first.
   - (S103 c1/c8) a register permutation among pointers/temps: a local REUSED across statement groups dies more than once
     and is refused by local-alloc (`local-alloc.c:472`) — split it into one name per value (generator R23 does this).
     `tools/alloc_table.py` prints the GLOBAL priority; local-alloc ranks by `qty_compare_1` (`local-alloc.c:1598`) —
     `tools/localalloc_sim.py <.lreg> <fn> <uid>` simulates it per block (0 mismatches over 150 validated blocks).
   - (S103 c11) the target keeps a global's address in a callee-saved register but yours rematerialises `lui`/absolute
     loads (a "launder" lever): write the late field reads relative to a DERIVED pointer the body already has
     (`*(T *)(arr + (D - K))`, not `*(T *)(base - K)`) — fold_rtx re-associates before folding (`cse.c:5580-5667`) and
     `find_best_addr` (`cse.c:2622`) folds base-relative reads to absolute; the FIRST cse pass must not reach them (a
     two-insn clamp arm stops it at the join label, `cse.c:8039`); the second pass (`.cse2`, dump flag `-dt`) re-associates.
     **Third condition (S103 c28, func_8013F350):** the second pass must scan the access's block EXACTLY ONCE — a block on
     two `.cse2` "Processing block from S to E" paths is re-associated on one and folded on the other
     (`cse.c:8098-8124`); then the lever is irreducible in plain C.
   - (S103 c11) a value tied into the wrong register by local-alloc (`local-alloc.c:1722`, refused when the destination is
     not local, `:1774`): REUSE one temp across blocks so flow makes it block-global (`flow.c:1204/1428`) and global.c's
     preference scan (`:1535`, `:1037-1071`) picks the argument register.
   - (S103 c11) a table load hoisted over a store (a `"memory"` barrier lever): `p[i]` is an aggregate access
     (`expr.c:4568-4575`) that `true_dependence` (`sched.c:817`) treats as independent of a scalar store; a cast-wrapped
     byte-offset read (`*(u8 **)((u8 *)tbl + i * 4)`) is not marked and stays after the store.
   - (S103 c18) the INVERSE of the split: when the target keeps ONE register for one role across several blocks (the same
     `$aN`/`$sN` loaded from the same expression in each), MERGE the per-block locals into one function-scope variable —
     one pseudo with the combined refs picks up the conflicts that put it in the target's register (`find_reg`,
     `global.c:945-990`). Read the whole objdump block by block for "same register, same role" — the hunk view hides it.
     Also: two flags the target keeps in ONE `$sN` → reuse one variable for both.
   - (S103 c18) a copy the target keeps after a `short` flag test (`move $v1,$sN`): combine reduces a sign extension of a
     0/1 value to a plain copy (`combine.c:7932-7942`, sign-bit copies `:718`) and the extension's second user keeps it —
     the tree's `c = chg` launder was faking exactly that copy; declare the flag `s16`, test it in a nested `||` if.
   - (S103 c35) a FRAME-ONLY residual (same instructions, a bigger stack frame, a slot no insn touches): a self-referencing
     local (`p = &D; p += r;`) whose uses all fold into one address keeps refs but no insns after combine
     (`combine.c:2306`) and reload gives it a slot (`reload1.c:2331-2352`) — write it as ONE assignment. `.greg` lists a
     pseudo with no disposition; `.lreg` says it "dies in 0 places".
   - (S103 c35) a call through a CAST that asserts fewer arguments than the callee takes, even when the declaration is
     right: pass the argument the caller already holds (0 bytes; jump2 deletes the no-op copy, `jump.c:437/462`). R19 now
     generates this.
   - Dumps: `DUMP_ROOT=PACK/scratch tools/cc1_dumps_tu.sh PACK/scratch/<your spliced TU>.c <tag>` (also `.dbr`, reorg) — it takes a .c file,
     resolves `../shared/…` includes, and writes `.cse2` (`-dt`) and `.jump2` (`-dJ`) too. No private dump.sh needed.
   - (S103 c10/c2/c4) READ LEVER-FREE BODIES that share your callees, globals or shapes ANYWHERE in the overlay, not only
     `neighbours.txt`: the answer to c10's function was in a different file (`func_80135888`), c4's was a sibling spelled
     lever-free under a stale `@stuck:` note. `grep -rln '<callee or global>' src/ov_SC04_011/`.
   - (S103 c2) grep the TU for the other functions that touch the same global/struct and READ THEIR BODIES, not only the
     headers in `neighbours.txt` — a sibling walking the same list gave the shape and the struct type.
4. Only then the allocation table (`tools/alloc_table.py`). Declaration-order moves are PROVABLY DEAD on a register
   residual whose allocnos have distinct priorities — `global.c:604-610` compares priority first and ties only by allocno
   number. Priority and live length are arithmetic: one body closed by moving a priority 6524 past 6666, another by
   shortening a live length from 44 to 43.
5. Many real closes are JOINT edits whose every single step scores worse than the start — do not abandon a move because it
   scored worse alone; try the combination the reading predicts.
6. Two REFUSALS: an invented identically-zero term (`x + 0*y`, `x - x`, a dummy dependency) is a compiler-forcing construct
   in C clothing and is NOT a close — the phase's rule is *ban the silence, not the lever*; and a body whose improvements
   are compensating errors is reported, not claimed. A plain `volatile` that the body did not already carry is also a lever.
7. `--try … --keep` keeps the candidate object and prints its path as the LAST line of the output. Write `PACK/body.c` and `PACK/mechanism.md` EARLY and keep them current. All scratch under `PACK/scratch/`.

## S104 additions (Drew's rulings of 2026-09-10 — they bind every agent from S104 on)
8. **`do { … } while (0)` and a dead initialiser** stay allowed as ordinary C (sotn-decomp keeps them the same way), but a new one
   carries `// !FAKE: do-while — <the pass it steers, file:line>` on its line (sotn's `docs/STYLE.md` rule). Prefer a body without.
   The identically-zero-term refusal (step 6) is unchanged.
9. **If the bytes will not close in plain C, deliver the MINIMUM-LEVER body**: the best honest plain-C text plus only the one or two
   levers it cannot do without, each marked `// !FAKE: <kind> <where> — <pass, file:line> (P36 S104 <agent id> minimum-lever)`, and
   `--try` it to 0. That banks now; the marked levers go to the STRUCTS phase. Report the count before → after.
10. **Structs question (Drew: "struct work is likely the missing piece to getting the C shape right without pins").** In
    `mechanism.md` add (g): would giving a pointer/global a STRUCT type (field accesses instead of `*(T *)(p + K)` casts) plausibly
    change the pass decision that keeps your lever? Say which struct, which fields, and why (`expr.c:4568-4577` aggregate accesses vs
    scalar stores in `sched.c`/`cse.c` is the known channel). If you can test it on bytes with a body-local struct declaration, do.
11. The free sweep already ran every generator family (R2–R26) on your class: its best candidate is named in your brief (the path
    under `.run/P36/regen/s104_all/`) — start from whichever of it and `body_free.c` scores lower.
12. **S104's landings — all at 0, eight of nine with ZERO levers (read these before the allocation table):**
    - (d2, d6) **a lever-free SAME-NAME variant in another binary is the answer half the time**: grep the WHOLE `src/` for the
      function's other definitions (not only `related.txt`, which searches one overlay). Port it: rename the per-overlay `D_`
      symbols (pair the two objects' relocations, or the extern lists), take the return type from the target TU's own later
      `extern`, add body-local `extern`s for symbols the donor TU declared at file scope.
    - (d3, d9) **a goto chain → STRUCTURED if/else (or a `||`)** — every generator mutates the goto text, so the sweep cannot
      reach it. A label between a condjump and a constant store blocks jump.c's if-conversion (`jump.c:805`, `:1019`); one
      constant store per arm keeps cross-jump from re-merging (`jump.c:2371`).
    - (d1) `x = a; if (c) x = f(a);` → `if (!c) x = a; else x = f(a);` — the NON-simple value in the ELSE arm (jump1
      re-merges an if/else whose else value is a reg/const, `jump.c:739-741`); never a ternary.
    - (d3) **reorder an independent test before a value's definition** to flip a scheduler tie-break (`sched.c:2428`) → the
      live lengths `allocno_compare` ranks on.
    - (d5) a hoisted temp `v = *(T*)(b+K); … x = x + v;` → `x += *(T*)(b+K)`: local-alloc's THREE-quantity order is by BIRTH,
      not a sort (`local-alloc.c:1486-1507`). `tools/localalloc_sim.py` sorts fully and mispredicts this — the fix is in
      `.run/P36/agents/ov_SC05_018__func_801837E8/scratch/lsim3.py`.
    - (d7) **declare a function-scope local INSIDE each switch case / if-arm** when it is used only there: a per-arm local
      crossing a call takes `$s0` in local-alloc (`local-alloc.c:2101-2106`) before global runs; `combine_regs` can then tie
      it (`:1722`, refused at `:1773` for a shared one). The inverse of S103 c18's merge.
    - (d8) **the WIDTH of an incremented local** decides sched1's birth priority: `(*(u16 *)(p + 2))++` or a `u16` counter
      (a SUBREG destination fails `birthing_insn_p`, `sched.c:2477-2490`); `+= 1` folds back to SImode and fails.
    - (d2) `home = (short)t;` re-extending an already-short value, with `t` given a second use (`combine.c:7926-7942`).
    - (d4) a marked `do { store; } while (0)` as a LOOP-note scheduling barrier (`sched.c:2058-2074`) — allowed, marked.
    - The `.sched` ready-list trace (`blocking insn N for 1 cycles`, the uid picked next) and `.lreg`'s `Register N in 16.`
      lines settled three of these where the allocation table misled.
13. **S104's second wave (d10–d15), all at 0 with ZERO levers:**
    - (d10) pins + a keepalive that reads variables BEFORE they are set + a dead `pad[N]` = a **register UNION**
      `union { struct { s16 x, y; } v; s32 w; } a;` assigned field-wise and passed as `.w` (the field insert makes flow mark it
      live from entry; `global.c:640-660`). Count the dead pseudos in `.lreg` against the target frame before accepting a pad.
    - (d12) **two differently-named locals pinned to the SAME register are ONE original variable** the decompiler split — merge
      them (rename the later to the earlier, delete its declaration), all pairs at once; a `$0` pin feeding `x = y + zr` means
      delete the temp and use `y`.
    - (d15) a temp reused for several values, each stored once (`.lreg`: "dies in N places", refused by `local-alloc.c:472`)
      → store each value directly (`*m = E;`, `*m |= K;`). A PROLOGUE copy-order residual → a parameter's WIDTH: an `s16`
      parameter's narrowing is emitted after all parameter copies (`function.c:3664-3676`); if a file-scope prototype fixes
      the type, a first-declared `s16 v = aN;` local does the same.
    - (d11) a sign-split range test (`if (v >= 0) { if (v >= K) goto L; } else { if (-v >= K) goto L; }`) → one condition with
      a ternary per axis `(v >= 0 ? v < K : -v < K) && …` (cross-jump finds no match, `jump.c:2412`; cookbook §396(a), §314b);
      never `abs()` — gcc's `abssi2` pattern differs.
    - (d13) `lhu; sll 16; sra 16` vs the target's `lh` + one wrong shift → cast ONE operand at the shift: `(s16)t >> 6`
      (`c-typeck.c:2418-2450` short_shift re-extends; cse folds that pair instead, `cse.c:5577-5667`); never the declaration.
    - Copies of your class under OTHER names in other TUs close with the same text almost always — find them by grepping a
      distinctive line and `--try` each (d7, d9, d11, d12, d13, d15 all did).
14. **S104's third wave (d14, d16–d19), all at 0 with ZERO levers — and a pattern across the session:**
    - **FOUR of nineteen closes were a goto chain rewritten as STRUCTURED C** (d3 if/else, d9 `||`, d11 ternary condition,
      d17 `switch` + a `for` with `continue`). The tree's bodies are decompiler goto text; no generator reaches a structured
      shape. If your body has `goto`/labels, try the structured spelling EARLY.
    - (d17) a do-while's return path `bnez …,<epilogue>; move v0,<ret>` vs the target's `beqz …; <increment in slot>` →
      write the loop as `for (…; …; count++, p += K)` with `continue`: a rotated for/while emits `NOTE_INSN_LOOP_VTOP`
      (`jump.c:2306`), which flips reorg's `mostly_true_jump` (`reorg.c:1364-1372`). A hoisted copy of a parameter living past
      the parameter's last use makes cse re-route reads through it (`cse.c:846-862`) — delete the copy.
    - (d14) a register residual in a LATE block where the target keeps late values in the same registers as unrelated
      EARLY variables → the original REUSED those variables: rename each late local to an earlier-dead one (enumerate;
      `combine_regs` refuses a pseudo that dies in several places, `local-alloc.c:1845`). (d19) a walked pointer vs counter
      `$s0/$s1` swap → make other loops' index the losing counter (raises its `allocno_compare` priority, `global.c:595-599`).
    - (d16, d18) a walked destination/secondary pointer (`dst`, `s1 = p + K` stepped alongside `p`) → index the array by the
      loop counter / write the accesses as `p + K + off`: all addresses become givs of one biv and combine into one register
      (`record_giv` `loop.c:4341`, `combine_givs` `:5494`). A `$0` pin on `y = x + zr` → declare `y` at the proven width.
    - Enumerating cheap spellings (d14: 365 bodies in ~3 min through `--try`) beats reasoning when the residual is a
      register permutation; `alloc_table.py` explains afterwards.
15. **S104's fourth wave (d21–d29), all at 0 with ZERO levers:**
    - (d27) a pinned RESULT local `r = 0; if (A) r = (B); return r;` → **return constants** `if (A && B) return 1; return 0;`:
      jump1's store-flag works on the hard `$v0` (`jump.c:1140-1210`), which pins the order after the call-result copy.
    - (d26) `v = *p; v -= 1; *p = v; if (v == 0)` → `if (--*p == 0)` (fewer refs for `qty_compare`, `local-alloc.c:1579`) and an
      independent sibling store moved BEFORE it (`sched.c:2425-2428` tie-break).
    - (d21) per-case call-result temps of one type → ONE function-scope variable (many refs over a short live length outrank
      the self pointer, `global.c:594-607`); a block with exactly 3 quantities is allocated in BIRTH order — add or remove a
      quantity (`local-alloc.c:1486-1500`).
    - (d22) a variable set in two switch cases → one variable per case (flow marks the shared one global, `flow.c:2058-2061`).
    - (d23) arms ending in the same store: the store BEFORE the counter (cross-jump keeps them apart); a list walk that reuses a
      long-lived variable as its `next` → a loop-local `next`.
    - (d24) `T x = argN;` at the top → delete, use `argN`. (d25) a FRAME-only residual (frame 8 bytes larger) → a local set twice
      (`p = &D; p += x;`) written as one expression (`combine.c:2305-2337`, `reload1.c:2327-2352`).
    - (d29) a `void` function whose last statement is a keepalive of `v0` RETURNS it — `s32` + `return X;` + the TU's `extern`
      prototype changed: a SIGNATURE change, parked for the STRUCTS phase (Drew S104 (d)); report it, do not expect it banked.
16. **S104's TU batches (e1–e9), and tool news:**
    - **`tools/localalloc_sim.py` now models the three-quantity switch** (both passes) — use it, not d5's `scratch/lsim3.py`.
    - `related.txt` now covers MAIN (`src/800*.c`); in main the answer is often a same-TU sibling that shares a global.
    - Recurring closes: every temp holds ONE value (a multi-death local is refused, `local-alloc.c:472`) — substitute in place or
      split, all at once; REUSE a temp across blocks to make it global; split a load from its update (`T = LOAD; … P = T + X;`);
      `return ++i;` for a counter's refs; a narrow load needed twice → `+=` on the field and re-read it at each test (combine's
      SUBREG copy survives, `local-alloc.c:1003-1007`); a hand-rolled `if (v < 0) v += 2^k-1; v >>= k;` is `v / 2^k`.
    - A `(void)` function whose first act reads a pinned `$a0`–`$a3` TAKES A PARAMETER; a narrow parameter the bytes use as s32
      IS s32; a store through another symbol of the same address is identical only after LINKING — all three are parked.
17. **S105's landings (f1 `src/800.c`, f2 `src/800_c.c` — 8 of 8 at 0: 5 plain C, 3 minimum-lever):**
    - (f2) **the LOOP FAMILY decides most COUNT residuals; the target says which biv it is:** the walked pointer's step emitted BEFORE
      the counter's `i++` = a counter-derived giv → `p = (T *)base + i * K;` at the loop top (**generator R44**; e21's law); AFTER
      `i++` = the pointer is its own biv, a RECORD base with no offset-0 access → `rec = SYM - OFF; rec[OFF ± k]` with OFF the
      textually LAST access's offset (`record_giv` prepends, `loop.c:4421`; the biv is eliminated, `loop.c:4035`). A lone address giv
      is never worth reducing (`-dL` benefit 2 per op, `add_cost` 2), a combined pair always is. A second derived pointer from the
      same base (`a1 = arg0 + 0x1B` beside `a3 = arg0 + 0x1A`) merges as `a3[c + 1]` (**R22 extended**).
    - (f1) read the target's PREHEADER giv init: it reads the parameter register while the copy lives elsewhere → walk the
      PARAMETER itself; it reads the register the pointer lives in → walk a LOCAL COPY (`record_initial` `loop.c:6327`,
      `valid_initial_value_p` `:4120`: a biv whose initial value is the hard `$a0` gets its giv init off `$a0`).
    - (f1) an OT-link `(A & 0xFF000000) | (B & 0xFFFFFF)` addPrim pair (in main: three witnesses in one TU; 256 files carry the
      mask pair) is the libgpu **P_TAG BITFIELD** store — body-local `typedef struct { u32 addr : 24; u32 len : 8; } PTag;` and
      `p->addr = ot[k].addr; ot[k].addr = (u32)p;` with the slot expression repeated in both halves as the macro does:
      `store_fixed_bit_field` (`expmed.c:556-706`) gives one set-once pseudo per value where the hand mask spelling reuses a temp
      that dies 4× (`local-alloc.c:472`) and goes global. Not a regex generator — a whole-body respelling; try it FIRST in main.
    - (f1) a `$aN` pin feeding a call whose delay slot the target leaves `nop`: read the CALLEE's body — if it never reads `$aN`,
      call it `(void)` through a body-local cast; when the pin IS the function's own parameter (`assign_parms`, `function.c:3679`),
      it is a SIGNATURE change → minimum-lever bank with the patch in `scratch/`, parked.
    - (f2) a `$a0`↔`$aK` permutation between a pointer parameter and an entry-block byte value used across a `switch` (`move aK,a0`
      at entry, `move a0,aK` before calls): the switch value is a NARROW `s16` local (its HImode block-local load takes `$4` in
      local-alloc; the SImode subreg copy survives cse `cse.c:7440-7460`; the parameter loses its `$a0` preference in
      `prune_preferences` `global.c:845-860`) — `u16`/`u8` do NOT work; pair with the per-case split of a multi-case temp (d7).
    - (f2) a narrow `s16` parameter the target treats as `s32` (PROMOTE_PROTOTYPES narrowing at entry, `function.c:3664-3676`) is a
      signature change: minimum-lever bank with ONE marked `$4` pin, patch in `scratch/`.
    - (f1) a local-alloc PRIORITY contest (`qty_compare`, `local-alloc.c:1579`; `tools/localalloc_sim.py`) where the losing temp
      already has every ref its instructions allow and cannot be born later (a multi-set temp's load is priority 1 and sched1's
      hazard tie-break lifts it above every store, `sched.c:2620-2690`; a set-once one sinks into the load-latency gap) → bank the
      minimum-lever body with that ONE pin marked; two `$sN` pins on narrow parameter copies stored after a call with a too-small
      frame → move the copies ABOVE the call (`global.c:925-990`: the copies cross the call, take `$s`, the parameters spill).
    - The `addu %0,$zero,$zero` instruction is `x = 0;` (the table knows it now); every remaining UNSTRIPPABLE pack is a one-off
      instruction (`mult` with no output, a 3-word block copy, `nop; addiu`) — strip it by hand from `body_tree.c`.
18. **S105 f3 (`md_SC07_004`, 5 of 5 at 0: 4 plain C, 1 minimum-lever PROVEN at its 5 levers):**
    - **The multi-set chain:** a MULTI-SET pseudo loses sched1's birthing boost (`sched.c:2477-2490`) → its load rises to the block
      top → a longer life → a LOWER `qty_compare_1` rank (`local-alloc.c:1598`) → it takes the later register. So a load-once /
      use-once read-modify-write value (an addPrim half, a masked field update) is spelled as COMPOUND UPDATES ON ONE VARIABLE
      (`tag = *p; tag &= 0xFF000000; tag |= x & 0xFFFFFF; *p = tag;`), declared in the INNERMOST block (a function-scope one goes
      global, `flow.c:2058-2061`, score 31 vs 0); the mask constants inlined. Closed two of five here and explains a third's ceiling
      (d8 covers only the width side of `birthing_insn_p`). In a MODULE TU the P_TAG bitfield spelling (step 17) scores 41 — an
      in-struct store sets only `writes->nonscalar` (`cse.c:7564-7577`) and the `lhu` reloads vanish; f1's main-side success needed
      the varying-address read. Try both; the bytes choose.
    - A 16-bit field value copied through a `$0` pin, tested, stored back with a byte of the sum → `if (F != G) { F += (u16)S;
      D[i] = F >> 7; }` on the FIELD (combine's HImode subreg copy is invisible to `optimize_reg_copy_1`, `local-alloc.c:1004-1006`);
      the frame's extra words are combine-orphan shift temps with stack slots (`.lreg` "ST_REGS or none", `reload1.c:2331-2352`),
      never a `pad[N]` — count the orphans against the target frame before accepting a pad (e8/e27/f3: three bodies in one TU).
    - ORDER residual where the target's loop inits (`move sN,zero` / `addiu sN,base,K`) sit AFTER a preceding call's argument setup:
      move the inits after the call (sched1's LUID tie-break, `sched.c:2384-2428`; the init pseudos cross the loop's call so
      `sched.c:1732` adds no anti-dependence) — R18 moves only within a block; a generator "move a loop-init across the preceding call"
      would reach it.
    - A constant-holder permutation whose `li`s sit one store-group EARLIER than their first use = REUSED temporaries in the
      original (multi-death holders → global, `global.c:945-990`) that keep the store order only with barriers: unreachable set-once
      (every 4-subset of five levers scored 2, every 3-subset ≥ 4, ~470 bodies) → bank minimum-lever with the markers carrying the
      pass. Structs lead: 4-byte `(x, y)` locals would make those constants SUBREG stores (no boost).
    - `tools/localalloc_sim.py` raises IndexError when the uid is not inside the block — feed it an insn uid from the block.
19. **S105 f4 (`ov_SC04_011_jr_8017D494`, 5 of 5 plain C) and f5 (`ov_SC02_005_jr_8018EA04`, 7 of 7 plain C):**
    - (f4) **`lh` + `move vX,vY` in the target = combine's narrow-load + sign-extend PARALLEL split** (`combine.c:1893-1918`, "we
      need both registers … split into a load followed by a register-register copy"), reached only when the `s16` local is loaded
      DIRECTLY from memory and set ONCE (a multi-set local is refused, `combine.c:1905-1911`, `reg_nonzero_bits` under LOAD_EXTEND_OP;
      a `u = t` copy hits cse's paradoxical-SUBREG fold `cse.c:4836-4870`). One single-set `s16` per axis. Three of five packs; and
      the tree's `frame_pad[N]` / "§333 aggregate" fillers were the dead shift temps' slots (8 bytes per site, `combine.c:2306` +
      `reload1.c:2331`) — DELETE the pad whenever this rule applies. A `$0` pin faking the copy (`v1 = v0 + zr`) is the same shape.
    - (f4) a `u16` counter TIED in `qty_compare_1` with a symbol (two tied pseudos HI+SI, 7 refs) wins by qty number where the
      target's symbol takes `v0` → re-declare the counter `s32` (one pseudo, 5 refs); `localalloc_sim.py` shows the tie.
    - (f4) a `$aN` pin on a global loaded right before an UNPROTOTYPED call = a missing call argument: read the callee's definition
      (`grep -n 'fn(' src -r`) and pass it through a body-local cast (R19); the tail `j; li v0,1` vs `move v0,zero` residual follows
      from it (reorg fills the slot from the fall-through's `lw a0`, `reorg.c:3320-3420`). A barrier between a store fed by an if/else
      and its reload → one store per arm (the reload lands in a new cse block; cross-jump re-merges the two `sh` in jump2).
    - (f4) a `$4–$7` "pre-copy" pin on a parameter used early and copied late → `s16` copies of the parameters at the top and the
      early result computed on the copy (cse's paradoxical-SUBREG fold routes `-y` to the parameter pseudo, which then keeps `a1`;
      the `s16` result is a SUBREG destination `birthing_insn_p` rejects, so the neg lands in the `bnez` slot).
    - (f5) **derived-pointer store (generator R45):** `s0[K] = 0` with `s0 = &SYM` known to cse → `lui $at; sw $zero,K($at)` — cse
      pass 1 FOLDS `(plus s0 K)` to the constant first (`find_best_addr`, `cse.c:2622-2740`, `:2653`); the pointer the function
      already passes to the call, `p = &s0[K]`, born BEFORE the store and stored through: zero instructions added; the `$s0/$s1` swaps
      beside the count hunks are the base's ref count (`alloc_table` 5 refs / 1785 → 7 / 2413, `global.c:594-610`) and vanish with it.
    - (f5) **set-once chain (generator R46):** `v &= 0x1F; v -= K; DST = v;` sets ONE pseudo several times → no `birthing_insn_p`
      boost → the chain is emitted at the block TOP ahead of the boosted `la`/`li`; `DST = (v & 0x1F) - K;` gives every temp one set
      and the LUID tie-break (`sched.c:2428`) puts it after the independent setups. The exact INVERSE of step 18's multi-set trick:
      the `.sched` priority column (`7f000001` vs `1`) says which direction a body needs.
    - (f5) a `$2` pin on a result local assigned a ternary/if-else of constants → two `return <const>;` statements
      (`expand_value_return` `stmt.c:2505-2528` writes the hard `$v0`; the taken arm's constant is the delay slot — try both orders).
    - (f5) `neighbours.txt` empty ≠ no neighbour: read the TU around the function — a lever-free sibling of the same byte shape
      (func_8018FAE0, func_8018FC38 which even spells the record as a struct) closed packs 4–7 on the first `--try` each.
    - The strip must not leave a READ of the pinned variable (`-a1v` after `register a1v __asm__("$5")` is gone): the free body's
      score is garbage until the argument is restored (f4 pack 5's "best 13" was measured on an uninitialised local).
20. **S105 f7 (`ov_SC01_077_jr_8017AE2C`, 6 of 6 at 0: 5 plain C, 1 minimum-lever):**
    - **STEP 0 — ablate each lever SEPARATELY** (`--try` the tree body minus one lever at a time) before any reading: dead
      keepalives and barriers exist in the tree (func_8017EF50's keepalive scored 0 without it).
    - **A pin unreachable by priority:** `find_free_reg` (`local-alloc.c:2073-2160`) takes the LOWEST register free over the
      quantity's [birth, death); when the pinned register lies ABOVE the block's first free register with nothing occupying the lower
      ones in the pre-alloc range, no priority order reaches it — decide from `.lreg` (~650 enumerated bodies said the same), bank
      the minimum-lever body with the pass on the marker.
    - **The giv-base law:** an offset-0 access is never a giv (`find_mem_givs`, `loop.c:4193-4196`), so a secondary pointer `q = p + K`
      with a `q[0]` read becomes a THIRD stepped register; write every access as `*(T *)(p + K ± c)` off the real biv (R22 does it now
      — it had refused every body with a `*(T *)q = v` store or a base sibling that does not itself step).
    - **The per-arm store / per-arm call** (c6's mechanism, two bodies here): duplicate the single consumer of an if/else-assigned
      local into both arms — jump1's `x = b; if (…) x = a;` merge (`jump.c:698-760`) needs one common pseudo, post-reload cross-jump
      (`jump.c:2371`) re-merges the tails; detect by a `li <else-const>` in the branch delay slot, or a pseudo "set in 2 blocks" whose
      join temp took its register (`global.c:945-990`). As a call ARGUMENT the `ior`/`and` temps are block-local and copy-suggested
      (`combine_regs`, `local-alloc.c:1722`); a function-scope result puts the `and` into a global pseudo and the tie is refused (`:1774`).
    - `x = E % K; … y += x` expands the quotient AND the remainder into `x`'s pseudo (`expand_divmod`, `expmed.c:2787-2790`,
      `:3653-3667`; dies twice → global) — write `c = E; y += c % K;` with no target variable; two statements keep fold's
      re-association (`fold-const.c:3685-3760`) from merging `(lhu - 320) + rem`.
    - The ORDER of a block's independent constant stores sets a birthing load's LIFE (`schedule_select`, `sched.c:2614-2660`: the
      load is "blocked for 1 cycle" behind every store issued the cycle before) and so its `qty_compare_1` rank — permute the stores;
      the sched1 trace, not the allocation table, is the instrument (36 of 120 orders close, exactly those with the 0xdc store first).
21. **S105 f6 (`ov_SC07_007_jr_8017BEBC`, 6 of 6 at 0: 1 plain C, 2 zero-pin with a marked do-while, 3 minimum-lever):**
    - A local assigned a CONSTANT in ≥2 blocks that outranks a parameter copy: `update_equiv_regs` (`local-alloc.c:1049-1064`)
      DOUBLES the live length of a set-once REG_EQUIV-constant pseudo — split it into one set-once local per block at the original
      statement position (never inline the constant: loop hoisting reorders the `lui/addiu`).
    - The do-while ref-weight tell: the loser needs EXACTLY +1 flow-time ref (`flow.c:2067`) on a statement that does not mention
      the winner (two parameters with 2 refs each → 5000 vs 3333 → +1 → a tie the lower allocno wins); a real callee argument does the
      same when one exists — never a fake argument (`func_801812BC` is really `(void)`).
    - A `$4–$7` pin copied once before the first call while all the callers cast to a WIDER arity = the function's own parameter N
      (`assign_parms`, `function.c:3620-3679`): signature patch parked, minimum-lever body passing it to the callees that take it.
    - `qty_compare_1` contests whose births/deaths are FIXED by sched1's backward LUID tie-breaks (`sched.c:3160-3260`) and refs by the
      bytes (14/226 = 1858 vs 13/222 = 1756) are "unreachable by priority": print both knobs from `localalloc_sim.py`; a loop-weight
      lever only works after the point where the target sinks its frame adjust, else it costs a `nop`.
    - P_TAG bitfield READS (not only the stores, step 17): the 0xFFFFFF mask pseudo gets 7 refs (`expmed.c:556-706`) and takes the
      target's register; and a pointer used for all-but-the-first access of a symbol → use it for the first too (combine folds the
      constant into `(mem (plus reg symbol))` and orphans the plus pseudo → the target's extra 8-byte slot, `reload1.c:2331`: the pad
      shrinks by two words).
    - A parameter reused as a later pointer + a `$sN` ROTATION among block-local temps: split the roles (parameter used directly,
      the pointer a block-local record base) — local-alloc allocates block-local quantities BEFORE the global parameter (allocation
      ORDER, not priority; the alloc table wants a "local vs global" column). A base with MIXED `sw K($sN)` / `lui $at` stores is a
      cse-opaque base beside own-symbol scalars — `find_best_addr` folds `(plus p K)` via `equiv_constant` before any cost compare
      whenever `p ≡ symbol` and the block has no ebb boundary: unreachable in plain C, mark the `la`. A tail `addiu s0,s0,32; move
      a1,s0` needs a CALL_INSN between the add and the arg copy or combine folds them (`combine.c:929`).
22. **S105 f8 (`ov_SC02_005_jr_80185E80`, 5 of 5 plain C, zero levers):**
    - A goto-form BOTTOM-TEST loop with a caller-saved swap between the counter's reload and its increment → a structured `while`:
      jump.c's `duplicate_loop_exit_test` copies the test to the loop end so the sum feeds it in one block, `combine_regs` ties the
      reload into the sum's quantity, and the post-reload cross-jump merges the two test copies into the target's `j` with the `sh` in
      its slot; the goto form can never reach it (the counter crosses the join label). Try STRUCTURED FIRST for any goto loop.
    - The target RELOADS a global between consecutive pointer stores (a barrier lever): cse's `note_mem_written` → `invalidate_memory`
      (`cse.c:7539-7580`, `:1701-1720`) — a pointer store sets only `nonscalar`, and an ARRAY-element load of the global is `/s` and dies
      at the first store; declare the global as a one-element array (a body-local alias when the file-scope extern disagrees), read
      `sym[0]`, and group the stores sharing one load as a chained assignment `outer = inner = v;`. `volatile` scores 12 (wrong
      registers); a bare-register store address folds back to PLUS by `find_best_addr`.
    - A `$4–$7` pin on a parameter copy + a global assigned INTO the parameter later → a fresh local for the global (jump2 deletes
      the parameter's `$4` copy tie otherwise); R71's sibling port found it on the first `--try`.
    - A `$5` pin whose value is loaded right before a call the TU declares NARROWER than `src/800.c` defines = a dropped call argument
      (R19; grep the definition and count parameters); the neighbouring v0/v1 swap vanished with it — the block dropped to exactly
      THREE local quantities and `block_alloc`'s unrolled 3-qty sort (`local-alloc.c:1486-1500`) allocates in BIRTH order.
    - **Copy-first:** a `$2` pin on a call result copied to a callee-saved local → make the copy the FIRST statement after the call
      (cse's `(set REG0 REG1)` swap, `cse.c:7440-7474`: `move s1,v0; bnez v0; sw v0`; with the store first `optimize_reg_copy_1` folds
      the copy). **Store-straddle:** a constant holder in `v0` (mine) vs `$aN` (target) with a load hoisted over the stores → move one of
      the identical constant stores ABOVE the nearest preceding two-register-value store (`la|lui|or`) so the holder's live range
      overlaps v0/v1 and `find_free_reg` gives it `a1` (sched1 keeps equal-priority constant stores in source order); 240 adjacent
      permutations all scored 6 — R9/R18 are inert here, the straddle closed in every try.
