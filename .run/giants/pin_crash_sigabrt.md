# The cc1-2.7.2 "pin-crash" SIGABRT — characterized (Fable5 discovery, 2026-07-15)

**Verdict up front: the §42e "CC1-CRASH WALL" is a misdiagnosis. The SIGABRT is real and now
fully characterized (a gcc-2.7.2 sched1 REG_DEAD-note conservation bug), but it was triggered
by the PROPAGATION STAGING dropping file-scope `#define` dependencies — not by "ov077-TU-context
/ fixed-size allocator tables". All four backlogged pin families compile CLEAN in sibling TUs
when properly staged: func_80133AB0 133/133 (era AND today), func_8013D9B0 133/133 (today,
fleet-swept), func_8016DF5C + func_80156044 (era TU, spot-proven). The pin-×1 ceiling is a
staging-tool artifact. P31's pin-propagation route is OPEN.**

All artifacts referenced below live in `.run/giants/pincrash/`.

---

## 1. The abort site (exact)

**`gcc-2.7.2/sched.c:2725-2728`, in `create_reg_dead_note()`:**

```c
  /* The number of registers killed after scheduling must be the same as the
     number of registers killed before scheduling. ...
     We carefully remove REG_DEAD notes from the dead_notes list, so that
     there will be none left at the end.  If we run out early, then there
     is a bug somewhere in flow, combine and/or sched.  */
  if (dead_notes == 0)
    {
#if 1
      abort ();                      /* <-- the SIGABRT / make Error 134 */
```

`dead_notes` is a per-basic-block free list: `schedule_block` strips every REG_DEAD note off the
block's insns onto it (sched.c:3581-3582, reset at 3255), reschedules, then re-attaches death
notes from the recount (`attach_deaths_insn → attach_deaths → create_reg_dead_note`). The pool
runs DRY when the post-schedule recount needs more deaths in the block than flow ever noted
there. (The mirror-image surplus abort is sched.c:3967.)

**gdb backtrace (shipped i386 cc1, `tools/bin/gcc-2.7.2-psx/cc1`):**

```
#0  0x08049160 in abort ()
#1  0x08179ff1 in create_reg_dead_note ()
#2  0x0817a79b in attach_deaths ()
#3..#4          in attach_deaths ()          (recursive walk of the pattern)
#5  0x0817ac12 in attach_deaths_insn ()
#6  0x0817cd60 in schedule_block ()
#7  0x0817f2f7 in schedule_insns ()
#8  0x08073335 in rest_of_compilation ()
```

**Pass: sched1** (`reload_completed == 0` at the abort — the before-reload scheduler,
`-fschedule-insns`, on at -O2). Repro scripts: `abort.gdb`, `detail.gdb`, `min.gdb`.

At the abort on the real body (era staging of func_8013D9B0), the reg being killed was
`(reg/v:SI 11 t3)` — the `register u16 *puVar10 __asm__("$11")` pin — at a plain
`(zero_extend (mem:HI (reg 11)))` load. On the 12-line minimal repro it is `(reg/v:SI 4 a0)`
at the outer `if (a != b)` `jump_insn`.

## 2. The minimal repro (12 lines, `minimal_repro.c`, ddmin-reduced from the real crasher)

```c
typedef unsigned int u32;
typedef int s32;
extern void g();
void f(int param_1)
{
    register u32 a __asm__("$3");     /* caller-saved pin */
    register u32 b __asm__("$4");     /* caller-saved pin */
    g();                              /* a CALL the pins' values must cross */
    if (a != b) {                     /* use after the call ... */
        if ((s32)a < (s32)b) a = a + 1;   /* ... + branch-dependent partial update */
    }
}
```

`cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker minimal_repro.c` → SIGABRT
(exit 134; Python subprocess sees returncode -6).

**Why (visible in `minimal_repro.c.combine`, the RTL fed to sched1):** flow places the single
REG_DEAD note for each pinned reg at the last use on the FALL-THROUGH path (the inner `slt`
insn, a later basic block). The uses at the outer branch (same block as the call) carry NO
notes. sched1's per-block recount, walking the block that contains the CALL, sees the
call-clobber kill the caller-saved regs and therefore demands a REG_DEAD note for their
use-after-call inside THAT block — whose harvested pool is empty → abort. Flow's death
placement and sched's clobber-aware recount disagree exactly and only for this shape.
(sched.c's own comment names the class: "a bug somewhere in flow, combine and/or sched.")

## 3. The predicate — which pins are fatal vs safe (probe matrix, all byte-run)

| probe | shape | exit |
|---|---|---|
| minimal_repro | $3+$4 pins, call, nested-if partial update after | **134** |
| p1 | same, NO call | 0 |
| p2 | ONE pin ($3), call, nested-if | **134** |
| p3 | pins initialized before the call (live-across, not uninit) | **134** |
| p4 | same shape, callee-saved pins ($17/$18) | 0 |
| p5 | one-level `if (a!=b) a=a+1;` after call | 0 |
| p6 | non-arg caller-saved pins ($8/$9) | **134** |
| p7 | single `if ((s32)a<(s32)b) a=a+1;` after call | 0 |
| p8 | use-only after call (`if (a!=b) h();`) | 0 |
| minimal_repro `-fno-schedule-insns` (or -O1) | sched1 off | 0 |

**FATAL:** `register T x __asm__("$N")` where $N is CALL-CLOBBERED ($2–$15, $24, $25), the
value is used AFTER a CALL_INSN, and the post-call uses have a branch-dependent
use-then-conditionally-set (nested-condition) shape.
**SAFE:** callee-saved pins ($16–$23, $30) in any shape; caller-saved pins whose live range
never crosses a call; use-only or single-level-conditional shapes.
$0 (`zr`) pins: never observed to abort (fixed register; 133/133 clean, §5).

## 4. Why "compiles in ov077, dies in the sibling" — the REAL mechanism

`family_remap.extract_unit` carries a function's contiguous preceding `extern`/comment/
single-line-`typedef` lines — **it does NOT carry `#define` lines** (and, in the Phase-25-era
version, no typedef lines either; and its "definition" regex false-matches a one-line
`extern ...; int wrapper(){...}` construct). ov_SC01_077's TU supplies each body's file-scope
dependencies; the staged sibling body arrives WITHOUT them:

- **func_8013D9B0 (GTE 20-pin, THE one genuine crasher):** ov077 defines
  `#define gte_ldIR0z()/gte_ldrgb/gte_ldIRGB/gte_dpcl/gte_stORGB` as inline `__asm__ __volatile__`
  right above the body (ov_SC01_077.c:435-439, present in the era file too). The macro-less
  staged sibling body turns those five GTE ops into **implicit-declaration CALLS** — putting the
  caller-saved pins ($2,$3,$4,$6,$7,$8,$9,$10,$11,$13,$14) live across calls in the fatal shape
  → the sched1 abort → `make` Error 134. Era-exact replication: `era_d9b0.c` → **exit 134**
  (the historical crash, reproduced). With the macros carried: **exit 0 in the era TU and in
  ALL 133 sibling TUs today** (`d9b0_fleet.py`: clean 133/133; 4 SC07 overlays have no image =
  not siblings). In the REAL body no pin crosses a real call (the GTE ops are asm; the one true
  call, func_800599B8, is crossed only by callee-saved pins) — which is why ov077 banked it.
- **func_80133AB0 (zero-reg pin, "crashed 3/3"): NEVER crashed.** Era staging dropped its
  multi-line `typedef struct Map_80133AB0` (era extract_unit couldn't carry it) →
  `Map_80133AB0 undeclared` → **exit 33** (plain error), both era layouts tested (`histA/histB`).
  Properly staged (typedef + the sibling's `extern int func_80133AB0(int,s16,s16,int);` →
  s16-form decl flip): **exit 0 in 133/133 sibling TUs today** (`sweep.sh`) **and 133/133 at the
  era commit c84bcb35c** (`era_sweep.sh`). The Error-134 attribution: in the era one-big-split
  layout its stub shared `ov_SC01_XXX.c` — and therefore the (overlay,split) gate compile —
  with func_8013D9B0's stub; d9b0's genuine abort killed the shared TU compile and the 134 was
  blamed on every family staged there.
- **func_8016DF5C (GTE-pin):** era staging dropped its single-line
  `typedef struct { s32 w[8]; } Blk20_8016DF5C;` → **exit 33** (`era_df5c.c`). With the typedef
  (today's extract_unit carries it): **exit 0** against the era sibling TU (`era_df5c_td.c`).
  Its pins are $17 (callee-saved) + block-scoped $3 not crossing calls → safe class.
- **func_80156044 (trampoline):** extract_unit false-positive — the def-search regex matches the
  ONE-LINE `extern void func_80156044(int,int); int func_80155FF8(...) { __asm__(...); }`
  wrapper (the trailing `/* dedup */` comment defeats the era `;`-endswith guard), so the staged
  "body" was func_80155FF8's WRAPPER → `redefinition of func_80155FF8` → **exit 33**
  (`era_x6044.c`). The REAL body + the engine_core int→void flip: **exit 0** against the era
  sibling TU (`era_x6044_flip.i`). Its $2/$3 pins are used before the first call → safe class.

So: "the pins are ov077-TU-context-specific" is REFUTED. The pins were never the problem in 3 of
4 families, and in the 4th the problem was the staging deleting the asm macros around them. No
fixed-size-table, no register-pressure, no surrounding-function-set effect exists — decls-only
context reproduces every result (ddmin `mask_min.txt`: the masking "TU context" reduced to the
5 basic typedefs + 3 externs, i.e. to nothing).

## 5. Repro commands

```sh
# the genuine SIGABRT (minimal):
tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker \
    .run/giants/pincrash/minimal_repro.c -o /dev/null          # exit 134
# the historical crash, era-exact (staged macro-less GTE body in the c84bcb35c sibling TU):
tools/bin/gcc-2.7.2-psx/cc1 <same flags> .run/giants/pincrash/era_d9b0.i -o /dev/null   # exit 134
# the same body properly staged (macros carried) — clean:
tools/bin/gcc-2.7.2-psx/cc1 <same flags> .run/giants/pincrash/d9b0_000.tu3.i -o /dev/null  # exit 0
# gdb: gdb -batch -x .run/giants/pincrash/min.gdb tools/bin/gcc-2.7.2-psx/cc1
```

Fleet evidence: `sweep_results.txt` (80133AB0 today, 133×exit=0), `era_sweep_results.txt`
(80133AB0 at c84bcb35c, 133×exit=0), `d9b0_fleet.py` output (8013D9B0 today, 133×exit=0).

## 6. Implications for Phase 31 (the pin-×1 endgame)

1. **The ×1 ceiling is not a compiler wall — it is a fixable staging gap.** To propagate the four
   backlogged families, the per-sibling unit must carry: (a) file-scope `#define` blocks the body
   uses (extract_unit currently drops ALL `#define` lines — add `"#define"` to its prefix-walk,
   or stage macros like the single-line-typedef carry), (b) multi-line typedefs (route through
   the engine_types.h lift or flatten to single-line), (c) the per-sibling decl flips
   (`//@EDIT`-class: the s16-decl flip for 80133AB0, `(void)`→`()` + the hoisted
   `extern s16 *D_...;` for 8013D9B0, the engine_core int→void flip for 80156044), and (d) a fix
   for the extract_unit one-line-wrapper false-positive (require the def-line's brace-block, or
   reject lines starting `extern`). With (a)-(d), cc1 compiles all four in every sibling TU.
   Byte-identity per sibling remains for the whole-binary gate to decide — but the "cc1-crash"
   barrier does not exist.
2. **The fatal-pin predicate is checkable at draft time** (§3): flag any caller-saved
   `register __asm__` pin whose variable is referenced after a function call. Such drafts are the
   only ones that can ever hit this abort — and even they are fine if the "call" was really a
   macro/asm that staging must preserve.
3. **Diagnostic signature:** cc1 exit 134 + this backtrace (abort ← create_reg_dead_note ←
   attach_deaths) = this bug, ALWAYS. An exit-33 is ordinary decl/typedef plumbing — the R14
   lesson recursed: the era experiment's "SIGABRT, universal, 3/3" folded three distinct exit-33
   plumbing failures into one crash bucket because the shared-TU gate reported one code.
4. `-fno-schedule-insns` (or -O1) suppresses the abort — useless for matching (changes schedule),
   but confirms the sched1 locus and is a safe probe for "is this the dead-notes bug?".

## 7. What was NOT determined

- The exact flow.c line placing the fall-through REG_DEAD (the mechanism is proven from the
  combine dump + the abort state; the flow-side walk was not source-traced line-by-line).
- Whether the four families byte-MATCH their siblings once staged correctly (compile-clean is
  proven; matching is the byte-gate's question, out of scope for this characterization).
