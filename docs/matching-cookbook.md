# Matching Cookbook — reusable compiler idioms & C-writing techniques

> **Evolvable reference (docs/ layer). Created Phase 6, 2026-06-14.** Append an entry every
> time a reusable nuance is found — these recur across nearly every function, so capturing
> them once accelerates all future matching. Companion to `SETUP.md` §5 (the pinned triple)
> and §6.6 (the matching loop). **Consult this at session start before matching.**

**Pinned toolchain (the context all entries assume):** `tools/bin/gcc-2.7.2-psx/cc1`
`-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker` → `maspsx --aspsx-version=2.56
--expand-div` → `mipsel-as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0`. (See SETUP.md
§5.4. psx≈cdk and 2.56≈2.67 produce identical bytes on functions without the discriminating
idioms — they only diverge on `sltu`+`$at` / div-expansion specifics.)

---

## How to use this
1. Scaffold (`tools/decompile.py <fn>` or Ghidra MCP), then consult the entries below to shape
   the C toward the target idioms *before* iterating asm-differ — it saves rounds.
2. When you discover a new asm↔C correspondence or a "what makes gcc emit X" trick, **add it here.**
3. When a residual diff is pure instruction scheduling (provably-independent ops reordered),
   that's a **decomp-permuter** job, not a hand-iteration job — note it and move on.

---

## §1 Idiom catalog (asm pattern → C that produces it)

### I1 — Unsigned range check: `(x - lo) < (hi-lo)` → `addiu`+`sltiu`
Target: `addiu v0,v1,-0x51 ; sltiu v0,v0,0x5f` (true iff x in [0x51, 0xaf]).
C: `if ((u32)(x - 0x51) < 0x5f)`. The subtract-then-unsigned-compare is the canonical
single-branch range test. `sltiu` (immediate) is emitted for `< constant`.
Example: `func_80018F20`.

### I2 — Byte mask forces `andi` even after `lbu`
Target: a redundant-looking `andi v1,v1,0xff` on a value already loaded by `lbu`.
C: write `(x & 0xff)` explicitly on the *later* uses of a byte value (gcc 2.7.2 -O2 does
NOT prove the upper bits zero across pseudo-registers, so the `& 0xff` survives as `andi`).
If you omit it, you lose the `andi` and the diff won't close.
Example: `func_80018F20` (first compare uses raw `x`, the 2nd/3rd use `x & 0xff`).

### I3 — Division by a constant → magic multiply
Target: `lui a3,0xcccc ; ori a3,a3,0xcccd ; multu a1,a3 ; mfhi t0 ; srl a1,t0,3` = `a1 / 10`.
C: just write `x / 10` (constant divisor). gcc emits the reciprocal-multiply (`0xCCCCCCCD`,
shift 3 for ÷10). The magic constant is loop-invariant and gets hoisted to the preheader.
Example: `func_80015A74`.

### I4 — Runtime (variable) division → `divu` + zero-check `break` (NEEDS `--expand-div`)
Target: `divu zero,a0,a1 ; bnez a1,.+12 ; nop ; break 0x7 ; mflo <q> ; mfhi <r>`.
C: `x / y` and `x % y` on the *same operands* → one `divu`, `mflo`=quotient, `mfhi`=remainder.
**Critical:** maspsx must run with `--expand-div` or it emits a bare `divu` with no zero-check
and the function can never match. This is PINNED in the Makefile (`MASPSX_FLAGS`).
Example: `func_80015A74`.

---

## §2 Writing matching C (what makes gcc emit X)

### T1 — Loop pointer: top-of-body for `addu` induction, not constant-folded `addiu`
If you init a loop pointer *before* the loop from a constant index (`p = base + 2`), gcc
constant-folds it to `addiu p,base,2`. The original often recomputes it from the induction
variable, giving `addu p,base,i` at both entry and loop-back. **Fix:** compute the pointer at
the *top of the loop body* (`p = base + i;`) so gcc keeps the induction form.
Example: `func_80018F20` (365→0 hinged on this).

### T2 — Source statement order drives instruction scheduling
gcc 2.7.2's scheduler largely follows source order for independent setup/init statements.
When pre-loop inits are mis-ordered vs the target (e.g. a counter `li` landing before vs after
a hoisted loop-invariant), reordering the C statements moves them. When it *doesn't* (the op is
placed by the optimizer, e.g. a hoisted invariant), it becomes a **permuter** job — see §3.
Open example: `func_80015A74` residual (counter init vs hoisted magic constant).

### T3 — Types
`u8/u16/u32/s8/s16/s32` from `include/common.h`. A `u8*` deref → `lbu` (zero-extend); `s8*` →
`lb` (sign-extend). Pick the load width/sign that matches the asm, then layer `& 0xff` (I2) /
casts as needed.

### T4 — Branch polarity: invert the source condition to flip gcc's chosen branch
Two source forms can be logically identical but emit **opposite** branches:
`if (x & m) return A; return B;` vs `if ((x & m) == 0) return B; return A;`. gcc -O2 picks one
polarity (beqz vs bnez); it may be the opposite of the target. Symptom in asm-differ: the right
structure but a lone **beqz↔bnez flip with the two return constants swapped** between the branch
and its `j`/delay slot. Fix: rewrite the condition with the other polarity. Also: which arm of an
`if/else` becomes the fall-through follows source order — put the target's fall-through block in the
`if`, the branched-to block in the `else` (e.g. `if (a != b){…} else {…}` if the `==` block sits
last). Example: `CdQueueBusy` (1405 → 210 via if/else order, 210 → 0 via the 0x20 polarity flip).
Likewise multi-exit functions: write the **success/main return LAST** (it becomes the fall-through
into the shared epilogue) and error cases as **early `return`s** (they branch in). Reversing this —
`if (ok) { … return good; } return 0;` — makes `return 0` the fall-through and duplicates the
`j epilogue`/`move v0,zero` tail. Example: `CdReadRequest` (305 → 0 by flipping to `if (busy) return 0;
… return cdReq_result;`).

---

## §3 When a diff is pure scheduling → decomp-permuter (harness built, Phase 6)
A residual diff of provably-independent instructions reordered is a permuter job, not hand-iteration.
**As-built harness** (`tools/permuter/`, committed): `compile.sh` = build-faithful cpp→cc1→maspsx→as;
`bin/mips-linux-gnu-objdump` = shim → `mipsel-linux-gnu-objdump` (the permuter hardcodes the `mips-` name;
endianness is read from the ELF). **Per-function setup** (scratch dir `.run/permuter/<fn>/`, gitignored):
- `base.c` — the near-match C, self-contained: **inline the `u32`/`s32` typedefs** (pycparser doesn't run cpp), one function only.
- `target.o` — assemble the expected bytes: `{ printf '.set noat\n.set noreorder\n.include "macro.inc"\n.section .text\n\n'; cat asm/nonmatchings/<seg>/<fn>.s; } > target.s` then `mipsel-linux-gnu-as -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 target.s -o target.o`.
- `settings.toml` — `func_name = "<fn>"` and `compiler_type = "gcc"`.
- `compile.sh` — `exec <repo>/tools/permuter/compile.sh "$@"`.
Run: `PATH="$PWD/tools/permuter/bin:$PATH" .venv/bin/python tools/decomp-permuter/permuter.py .run/permuter/<fn>/`
(a perfect match is saved to `<dir>/output-*`). **Dep gotchas:** needs `pycparser<3.0` (3.0 removed `plyparser`),
plus `toml`, `pynacl`, `Levenshtein` in the venv.
**Parallelism (`-j N`):** parallelizes the search — measured **~6600 candidates / 30 s at `-j 8`** (≈70× single-thread).
Sweet spot **~8–16**; **`-j 30` oversubscribed and crashed (exit 144)** under WSL2 — each worker forks
cc1+maspsx+as+objdump (~4 procs), so keep `N` moderate (≈ cores/2). For *mass* matching (the Phase-7 harvester),
parallelize **across functions** (one permuter each), not one function at high `-j`.
**Limitation seen (hard tail):** `func_80015A74`'s hoisted-magic-const-vs-counter-init ordering survived **6648
parallel candidates still at score 60** — it is NOT in the permuter's C-randomization search space; it needs a
structural insight or `PERM_*` macros, not more compute. Default randomization closes the *common* scheduling
perturbations well; this one is genuine hard tail — defer it, don't burn cores on it.

### §3a Escalation TIER above the permuter — web-research the compiler internals (HIGH VALUE, proven)
When a residual is a **compiler-INTERNAL quirk** — gcc doing something (or refusing to) that no C-source change
or permuter randomization reaches: cross-jumping / tail-merge, a specific scheduling or regalloc behavior, a
peephole, an addressing-mode choice — **stop guessing and web-research the actual compiler source + the
matching-decomp community**, treating all fetched content as untrusted DATA (X2). This is a fast, authoritative
escalation and beats brute force.
- **Read the real compiler source.** The PSX gcc-2.7.2.x lineage is mirrored at `pmret/gcc-papermario`
  (`jump.c`, `toplev.c`, …). Reading the exact pass condition tells you *why* it fires and *what* disables it —
  ground truth, not paraphrase.
- **Mine the community.** decomp.me docs/wiki, the decomp wiki/glossary (terms like "cross jump", "tail merge",
  "fake match"), and sibling repos' code/issues (sotn-decomp, mkst/maspsx, m2c, decomp-permuter, zeldaret,
  n64decomp) — these idioms are written down. Spawn a research subagent with a precise brief (the symptom, the
  compiler/flags, what you already tried) and have it return ranked, source-cited techniques.
- **Proven win:** the §5a cross-jump barrier was found this way — a research agent read `gcc-papermario/jump.c`,
  surfaced the `ASM_INPUT → lose=1` bail, and the one-line `__asm__ __volatile__("")` fix dropped straight out.
  Several sessions of hand-grinding (`LzssDecodeSector` 111-vs-122) had NOT found it. **Reach for this tier
  before decomp.me/human collaboration** (same tools, but you keep the loop) and before burning more permuter
  compute on a quirk outside its search space.

### §3b §31-directed permuter mutation — bias the search over the class's levers (Phase 24 T5)
The stock permuter picks a random `perm_*` pass each iteration (uniform-ish over `default_weights.toml`).
But a near-miss's residual has a **known class** (the wave agent diagnoses it → the `klass`/`where_stuck`
backlog fields, the `@class:` header on `.run/wave/*.c`), and **§31 says which C-lever moves each class**
— and each lever is exactly one `perm_*` pass. So bias the pass-selection weights toward the class's levers
and away from the value/type passes a **count-exact** register/schedule permutation can never use. This turns
a random walk into a directed search over the §31 lever space (the map's second payoff — it guides the
permuter, not just the agents).
- **Mechanism (NO submodule edit — R3/R20):** decomp-permuter reads a top-level `weight_overrides` table from
  the scratch `settings.toml` (`src/main.py:336`), merges it over the compiler-type defaults **per-key**
  (`helpers.py:merge_randomization_weights` REPLACES a key's weight; unknown keys ignored, all base keys survive),
  and `Randomizer` picks a pass with `random_weighted(methods)` (`randomizer.py:2467`). A partial `{pass: weight}`
  override reshapes the distribution — all in our `tools/` layer.
- **The tool:** `tools/permuter_weights.py` — `classify(klass, where)` → `regalloc | schedule | cse | None`
  (the klass TAG is the primary bucket; a **cse residual overrides** — func_80148094 is tagged `regalloc-order`
  but its residual is a cse mult-order, so it wants the commutative-heavy profile; a generic WAVE/GIANT tag falls
  back to the `where` text). `render_settings_toml()` emits the `[weight_overrides]` block. `p16_permute.setup(fn,
  draft, asm_subdir, klass=…, where=…)` writes it; `grinder.py` auto-threads `klass`/`where_stuck` from the
  backlog record. **`klass=None` → no table → the plain gcc defaults (identical to the pre-T5 undirected search:
  a safe superset).**
- **The three profiles → §31 levers** (keys are the exact `perm_*` names): **regalloc** (RC-1/2/3, S7, S11
  register-permutation) up-weights `perm_reorder_decls`(40, RC-1 slot / RC-3 tie-order) · `perm_reorder_stmts`(40,
  RC-2 range / S11 LUID) · `perm_temp_for_expr`(60, S2 boost) · `perm_split_assignment`/`perm_duplicate_assignment`
  (set-count → RC-2 / defeat RC-7 equiv); **schedule** (S1–S5, D1–D4) leads with `perm_reorder_stmts`(60, LUID) +
  `perm_temp_for_expr`(60, S2) + `perm_ins_block`/`perm_empty_stmt` (S4 filler); **cse** leads with
  `perm_commutative`(40, operand order) + `perm_expand_expr`/`perm_split_assignment` (re-decompose). All three
  push the value/type noise (`perm_add_mask`/`xor_zero`/`mult_zero`/`randomize_*_type`/…) to ~0.1.
- **Validated:** on `func_8014E048` (S11 LUID⊗alloc, 143-ins, base masked-36) the regalloc profile found a
  better score in <30 s (36→34→33) where the undirected search had stalled — proof the biased distribution
  explores the class's territory. The whole-binary byte-gate (`harvest_verify`) stays the **sole arbiter** (G3/P9):
  a permuter `output-0-*` is a strong CANDIDATE to gate, never a bank.
- **The grinder's companion fix (T5):** the old idle path did a blind `tried.clear()` → re-permuted every
  floor-victim on every idle tick (churn, R14). Replaced with **input-changed gating** (`grinder.py draft_sig` =
  `(best_draft mtime, closeness)`): a fn is re-opened only when the worker actually improved its draft; the
  permuter is deterministic given `base.c`+`target.o`, so an unchanged input can never newly win.
- **Scope note:** the four flagship count-exact seeds (`func_8014E048` 35 · `func_80176D94` 52 · `func_80148094`
  72 · `func_801412A8` 110) are the project's **worst-case** intrinsic walls (RC-6/S11, "the C-space around the
  target is discontinuous" — §31 regalloc RC-6). Directed mutation is the right tool but the map's "two probes,
  don't grind" applies. The real payoff is the **broader** reach-134 near-miss tail (T8: ~30 schedule / ~84
  regalloc), most of which is far less extreme — there the directed profiles raise the per-batch close-rate.

---

## §4 Flag/toolchain gotchas
- `--expand-div` is **required** for any div/rem (§I4). Pinned globally in `MASPSX_FLAGS`.
- `-O2 -G0` (no `$gp`-relative). `-G0` confirmed (zero `%gp_rel` in the disassembly).
- psx-vs-cdk cc1 and aspsx 2.56-vs-2.67 are byte-equivalent on functions without the
  discriminating idioms — don't expect a probe to distinguish them unless it uses `sltu`+`$at`
  or div-expansion specifics. The evidence-based pin is **psx + 2.56** (PsyQ 4.0 stamps).
- Per-module mixing (§5.5) is expected: if a whole module's div is *bare* (no `--expand-div`)
  or flags differ, that's a per-file override — record it here and add the Makefile mechanism.

## §5 Known hard-residual classes (instruction-identical, one byte-exact blocker)
These are functions where every instruction matches but a final whole-function artifact blocks
score 0. They still *confirm the compiler* (instruction selection + regalloc match); defer them
as decomp-permuter candidates rather than hand-grinding.
- **Phantom empty stack frame** — gcc 2.7.2 -O2 sometimes wraps a frameless leaf in an unused
  16-byte frame (`addiu sp,sp,-0x10` / `+0x10`, no saves/spills); the target is frameless. The one
  extra instruction shifts the whole function → large score from a trivial cause. Structural
  variation / the permuter can flip frame allocation. Example: `func_80016714` (bzero).
- **Hoisted-invariant vs IV-init ordering** — a loop-invariant load scheduled before/after the
  counter init; not reachable by C-source changes (permuter stuck at base). Needs `PERM_*` or
  insight. Example: `func_80015A74` (uint→BCD). See §3.

### §5a Cross-jump tail-merge — gcc collapses two byte-identical blocks the original kept separate (FIX FOUND)
**Symptom:** your function is N instructions SHORTER than the target, because the original binary has two
(or more) byte-identical tail blocks (classically a "save K globals then `return c`" epilogue reached from
different states) but gcc **merges them into one**. asm-differ shows a big cascade; the instruction COUNT is
short by exactly one copy of the tail. Example: `LzssDecodeSector` — the original keeps `block_14` (the
state-3/4 save, ending `j epilogue`) SEPARATE from the state-2 reload save (which falls through to the
epilogue); gcc merged them → 111 vs the original 122 instructions.
**Root cause (ground-truthed against gcc-2.7.2.3 `jump.c`):** the `find_cross_jump`/`do_cross_jump` pass
walks two blocks backward and merges them while the instruction suffix is identical (`rtx_renumbered_equal_p`).
It is hardcoded ON at any `optimize > 0` (fires at -O1 too; **no `-fno-crossjumping` exists before gcc 3.3**),
and `do_cross_jump` explicitly rewrites `RETURN` insns — so identical save/return epilogues are exactly what
it targets. Shared-`goto`, explicit-epilogue, and three-inline-copy C forms all produce RTL-identical tails →
gcc re-merges every time. cdk cc1 merges too. The permuter's default randomization does NOT defeat it.
**THE FIX — a zero-byte volatile-asm barrier.** `find_cross_jump` sets `lose = 1` (bails) on ANY volatile asm
node (`ASM_INPUT`/`MEM_VOLATILE_P`). Put one empty volatile asm in ONE of the twin blocks (after the last
store, before the return):
```c
    /* ...the K stores... */
    __asm__ __volatile__("" ::: "memory");   /* zero-byte cross-jump barrier */
    return c;
```
It emits **no machine code** but makes the block's RTL non-identical to its twin, so gcc keeps BOTH copies →
correct instruction count. Document it as load-bearing (a future reader will "clean it up" and lose 11 bytes).
This is a standard decomp idiom (sotn writes duplicate funcs explicitly; the `"" ::: "memory"` clobber also
pins store ordering — drop the clobber to plain `__asm__ __volatile__("")` if it perturbs scheduling).
**Permuter caveat:** pycparser rejects `__asm__ __volatile__(... ::: ...)`. To still permute the residual
regalloc, put a placeholder call (`CJBARRIER();` + an `extern void CJBARRIER(void);`) in `base.c` and have the
per-function `compile.sh` `sed` it to the real asm before compiling. Note the asm-differ object-mode score then
floats on a cosmetic `.rodata`-vs-`jtbl_<addr>` symbol floor (the migrated jump table links identically), so
verify candidates with the **linked** `make check`, not the permuter score.
**The full close of this exact function** — the ~4 regalloc/scheduling slots this barrier leaves behind, and the
floor-free `.text` metric that finally measured them — is **§10** (LZSS matched byte-for-byte, Phase 7 session F).

---

## §6 Per-module optimization mixing — the -O0 boot module (Phase 7)
**Finding (2026-06-14):** the EXE mixes optimization levels per original translation unit (the
§5.5 Xenogears-style mixing, now concrete). The **boot/main/game-mode-dispatch module** — a clean
contiguous block at **vram 0x80010000–0x800123F0** (~50 funcs: `start`, `main`, `GameModeDispatch`,
`DebugMenuHandler`, the game-mode handlers) — was compiled at **-O0**. Everything from 0x800123F0
onward (every match so far + the file-loader cluster) is **-O2**. **Always opt-fingerprint a new
function before writing C** — the pinned `-O2` is NOT global.

### Detecting the opt level (do this first)
gcc 2.7.2 **-O0 keeps a frame pointer**: `addu $fp,$sp,$zero` (`21F0A003`) in the prologue +
`addu $sp,$fp,$zero` in the epilogue; **-O2 omits it**. Grep the target `.s`:
`grep -l 21F0A003 asm/nonmatchings/<seg>/<fn>.s` → hit = **-O0**, miss = -O2. Module scan: classify
every `.s` by that signature, sort by address; the contiguous -O0 run is the module (the boot block
is the one early -O0 run). Other -O0 tells: redundant `move`/`addu rd,rs,$zero` copies; a `nop` after
every load (no load-delay scheduling); single-use values parked in callee-saved `s0..`; large
constant member offsets left **unfolded** (`la $reg,sym` + `lhu off($reg)`), where -O2 folds
`sym+off` into one load.

### -O0 idiom — far struct member via a `register` base pointer
Target: `lui s0,%hi(BASE); addiu s0,s0,%lo(BASE); lui at,1; addu at,s0,at; lhu v0,-0x5c52(at)` =
load a u16 at `BASE + 0xA3AE`. The `lui 1 / addu / -0x5c52` is just `as` expanding a register-relative
load whose offset (0xA3AE) exceeds 0x7FFF (%hi=1, %lo=-0x5C52). C — a **`register`-qualified pointer**
to the base, then offset-deref:
```c
extern u8 BASE[];
register u8 *p = BASE;
... *(u16 *)(p + 0xA3AE) ...   /* base stays in a callee-saved reg; offset left unfolded */
```
`register` is **load-bearing**: drop it and -O0 spills the pointer (extra sw/lw, bigger frame); and
-O1/-O2 fold it all back to `lhu sym+off` (no base reg, no frame pointer). Plain `BASE[idx]` or
`((struct*)BASE)->m` also **fold** at -O0 → wrong. Example: `GameModeDispatch` (0x80010B40) =
`gameModeHandlerTable[*(u16*)(p+0xA3AE)]()` — byte-exact (asm-differ 0).

### -O0 idiom — a reserved (unstored) local sets the frame size
A named local the original declares but our toolchain wouldn't store (e.g. a call result the
original checks directly) still **reserves its 8-byte stack slot** at -O0, enlarging the frame.
If a near-match differs **only** by frame size + a uniform save-offset shift (every instruction
identical), add the missing local as a **declaration-only** `int x;` + `(void)x;` — no store, no
load, no `-Wall` noise, no code, just the slot. (Assigning the result to the local instead emits a
`sw`/`lw` pair the target lacks.) Example: `DebugMenuHandler` (0x80011144) — `if (CdReadRequest(...)
!= 0)` with a reserved `int iVar1;` → frame 0x20 (score 42 → 0).

### Build mechanism — per-file opt override (splat resegmentation)
One original .c = one opt level; you can't mix within a compile unit, and gcc 2.7.2 has no
per-function optimize pragma. **Split the module into its own splat c-subsegment** and give that
object its flags:
- `config/splat.us.exe.yaml`: split the text subseg at the module boundary (a function start; file
  off = vram − 0x8000F800). Boot module = `[0x800, c, boot] → src/boot.c`; the rest stays
  `[0x2BF0, c, 800] → src/800.c` (name kept to avoid migrating matched C).
- `Makefile`: target-specific override — `build/src/boot.o: CC1FLAGS := …-O0…` (the pattern recipe
  reads `$(CC1FLAGS)`, so this overrides just that object).
- **Regression gate:** the split must rebuild **byte-identical at 100% INCLUDE_ASM** before any -O0 C
  is added (opt level only affects matched C, not stubs). Verified for the boot split.
Reuse this hook for any future module whose flags differ (another opt level, bare `divu`, etc.).

---

## §7 PsyQ SDK types & symbols (the library-call prerequisite)
A function that calls PsyQ library routines needs both the SDK **types** and the library **symbols**:
- **Types:** pull the EXACT layout from Ghidra's imported `.gdt` (`mcp__ghidra__types get <Name>`,
  category e.g. `/LIBCD.H`) — never guess offsets (G1). Declare in `include/psyq/<lib>.h` (it
  `#include "common.h"` for u8/u32, guard-safe). Verify sizes with a compile-time assert:
  `typedef char a[sizeof(T)==N ? 1 : -1];`.
- **Symbols:** PsyQ fns are already named in the Ghidra DB but absent from our exported
  `config/symbols.us.txt`, so the build shows them as `func_<addr>`. Add `Name = 0xADDR; // func`
  to `symbols.us.txt` (R15) AND rename the matching `INCLUDE_ASM("…", func_<addr>)` stub(s) in
  `src/` to the canonical name (splat won't rewrite a committed `.c`). Re-extract →
  **byte-identical** (label-only change). No matched C may already reference the old name.
- Done Phase 7: `include/psyq/libcd.h` (CdlLOC 4B, CdlFILE 24B + CdSearchFile/CdPosToInt/CdIntToPos
  protos) + the 4 libcd/libetc symbols — unlocks the file-loader cluster. Same pattern for
  libgpu/libgte/libspu as they come up.

---

## §8 rodata island (compiler jump tables) — the `.data→.rodata→.data` sandwich (Phase 7)
GCC emits each `switch` jump table into `.rodata`; in this EXE all compiler rodata is ONE island at
0x80072A38–0x80074750, sitting BETWEEN the front `.data` (globals @0x800629DC) and the tail `.data`
(@0x80074750). No single splat `section_order` expresses data→rodata→data. Proven mechanism (session C):
- **Migrate, don't standalone.** A jtbl `.word`s reference function-internal `.L`/`jlabel` targets, so a
  separate rodata object can't link — the table MUST co-locate in its function's object. Use a **dotted
  `.rodata` subseg whose NAME matches the code subseg** (`[<off>, .rodata, 800]`): `extract=False`, spimdisasm
  migrates each single-ref jtbl/const into `asm/nonmatchings/<seg>/<fn>.s` as `.section .rodata`. The
  INCLUDE_ASM stub already `.include`s that `.s`, so it flows into the object for free. Multi-ref rodata can't
  migrate → splat emits `INCLUDE_RODATA(...)` lines (in a FRESH `.c`). **H5:** don't regen-fresh the curated
  `.c` (drops comments) — surgically INSERT just the INCLUDE_RODATA lines.
- **Place explicitly.** splat is section-major (floats all `.rodata` to the front). `tools/ld_interleave.py`
  (wired into `make extract`) rewrites the `.main {}` body to text → front-`.data` → `.rodata` → tail-`.data` →
  bss, splitting front/tail by object basename. Sizes then land byte-exact.
- **Carve data-in-text.** A trailing non-code table inside the text range (here 0x80062998–0x800629DC) must be
  its own `data` subseg, or jumptable analysis mis-extends the last function across it (the +24 `main_TEXT_END`
  overrun's first cause).
- **The `.align 3` file-split trap:** GCC 8-aligns jtbls; concatenating many functions into one object injects
  padding nops the original (separate TUs) lacked → image grows. spimdisasm PRINTS file-split suggestions at
  the misaligned jtbls. Fix = per-file split at those boundaries (sotn-style) — OR link the real library
  object (§9) when the owning function is SDK code.

## §8a rodata island in a flat OVERLAY — the tail sandwich, per matched jr-function (Phase 26 — PoC PROVEN)
The EXE's §8 was one central island. The **overlays** are different: gcc's switch jtbls sit in ONE contiguous
`.rodata` block at the **TAIL** of the flat blob — between the `.data` globals and a tiny `.data` remnant
(ov_SC01_077: island vram 0x801D7F9C..~0x801D9460, right after `.data` global D_801D7F94; layout = text →
data-globals → **rodata-jtbls** → data-tiny). While every jr-function is INCLUDE_ASM the jtbls emit as in-place
`.data` and the build is byte-fine. The moment you MATCH a jr-function, its C emits the jtbl into `.rodata`
(which the overlay `section_order:[.rodata,.text,.data,.bss]` floats to the FRONT @0x80128158) **and** the raw
copy is still in the data tail → duplicate + wrong address. The **proven fix (byte-identical on func_8012ACE0,
a 25-ins single-jtbl jr-function in ov_SC01_077):**
- **Carve per matched fn.** Split the `[…, data, tail]` subseg around that function's jtbl(s) into
  `[…, data, tail]` (globals + pre-carve jtbls, still raw `.data`) + `[<off>, .rodata, <code-subseg-name>]`
  (the fn's jtbl → migrates into its `asm/nonmatchings/<subseg>/<fn>.s` as `.section .rodata`; the name MUST
  match the code subseg the fn lives in, e.g. `ov_SC01_077_a`) + `[<off2>, data, tail2]` (post-carve jtbls +
  tail, raw). Other functions' jtbls STAY raw `.data` until they too are matched (per-fn carve, not whole-island).
- **Place via the parameterized `ld_interleave`** (Phase-26: added `--section .<binary>` → derives the
  `<binary>_TEXT/DATA/RODATA/DATA2/BSS` symbol prefix; default `.main` = the EXE, byte-identical): it rewrites
  the overlay's output section to text → data(tail, `--front tail.data.o`) → rodata → data(tail2+trailing,
  `--tail tail2.data.o --tail trailing.o`) → bss. Wired into `make extract` via a per-binary
  **`<bin>_JTBL_INTERLEAVE`** var in `config/overlays.mk` (holds the `--front/--tail` basenames) + an
  `ifneq ($(strip $(JTBL_INTERLEAVE)),)` branch. **GOTCHA:** put NO trailing `#comment` on the
  `JTBL_INTERLEAVE :=` line and `$(strip)` it — a trailing comment leaves whitespace → non-empty → the branch
  misfires on EVERY binary (ld_interleave then runs with EXE defaults → "front data object not found" on resident).
- **The C body needs `canon_sig_reconcile`** before it will compile in the real TU (the raw draft hits
  `conflicting types for <fn>` vs the TU's forward decl + `conflicting types for <typedef>` vs a sibling; reconcile
  rewrites the def sig to canonical + uniquifies the draft's typedefs + block-scopes externs). Placement is
  orthogonal — reconcile first, then the carved jtbl lands byte-exact.
- **Alignment:** gcc emits the jtbl `.rdata .align 3` (8-byte). If the original jtbl address is 8-aligned
  (`jtbl_801D8078`, 0x…078) there is no pad and it lands exact. A **4-aligned** original address (`jtbl_801D8AFC`)
  would force a 4-byte align pad → **HANDLED (Phase 29): the §8e `JTBL_PADS` pad-spec filter** (hit for real by
  `jtbl_801D8144` in the func_80131340 bank).
- **rtu_match is NOT a whole-binary gate for jr-functions** — it masks relocs AND excludes the §8 jtbl rodata, so
  it MATCHes a body whose switch is subtly wrong (e.g. func_80159C84's 2nd jtbl was 5 words vs the real 6 — a
  false-MATCH). Always confirm jr-function cracks with the whole-binary gate (which now works, via this carve).
- **×134 automation (NEXT):** each overlay sibling has the SAME jr-function at a per-overlay address with its own
  jtbl in its own tail → the carve config + the `<bin>_JTBL_INTERLEAVE` var must be generated per overlay from
  the sibling's jtbl address (a tool over `family_sweep`), then reconcile+template the body per sibling. The PoC
  proves the per-binary mechanism; the fleet rollout is the mechanical generator.

### §8a-pad — a trailing `.word 0x00000000` under a jtbl dlabel is `.align` PAD, not an entry (Phase 26 session 6, byte-proven)

> **⚠ CORRECTED by §8e (Phase 29):** the "maspsx drops all `.align`" rationale below is **FALSE** (that
> `continue` is in an inventory-only pass; the output path passes `.align` verbatim). The TRIM itself remains
> correct — the pad belongs to the NEXT table's `.align 3`, absent when that owner isn't compiled in the same
> object. Multi-table spans now reproduce interior pads via the §8e `JTBL_PADS` spec filter.

**This retroactively explains the §8a `func_80159C84` "5 words vs the real 6" false-MATCH.**

The raw `dlabel jtbl_XXXXXXXX` in `asm/<ov>/data/*.data.s` can span one word MORE than the switch has
cases. That last `.word 0x00000000` is the ORIGINAL TU's intra-rdata **`.align 3` padding** — emitted when a
jump table's entries end ≡4 mod 8 and another jtbl of the same TU follows. It cannot be a table entry:
`0x00000000` is not a jump target.

- **The true entry count is the function's `sltiu <n>` range check**, not the dlabel span. Byte-confirmed:
  `func_8015AE2C` → `sltiu $v0, $v1, 0x7` = **7** entries, yet its raw dlabel spans **8** words.
- **maspsx drops all `.align`** (maspsx.py:435), so a C-emitted jump table can NEVER reproduce the pad.
- **Therefore `jtbl_carve` must TRIM trailing zero words** from the carve range, leaving the pad in the raw
  post-carve `data` piece. Carving to the next dlabel reserves 8 words while the compiled object supplies
  only 7 → the `.rodata` piece under-fills by 4 bytes → **every later symbol shifts +4** (the same image
  corruption class as §41d: ~271k differing bytes from one missing word). Trimming is always safe.
- Existing carves are parsed from the CONFIG (their `end` = the next piece's offset), not re-derived from
  the data asm, so the trim only affects NEW carves — committed banks are unaffected.

## §8b MULTI-jtbl per overlay — the `ld_interleave --order` sandwich + the same-subseg cases (Phase 26 session 4)
Once ONE jr-function is banked in an overlay, banking a SECOND makes it multi-jtbl (§8a's single-carve breaks:
`jtbl_family_bank.revert()` restores the committed config = already has carve #1). The generalization:
- **`ld_interleave.py --order <leaf1,leaf2,…>`** — an explicit, ADDRESS-ORDERED list of the data-region pieces
  forming the sandwich (text → [these] → bss). A `*.data.o`/`trailing.o` leaf contributes its `.data`; any other
  (code) object leaf contributes its `.rodata` carve. Unlisted `.data`/`.rodata` lines must be empty code-object
  sections → parked byte-neutrally with `.text`. Generalises the 3-piece single sandwich to N pieces. Legacy
  `--front/--tail` path is byte-untouched (main EXE + single-carve siblings unaffected).
- **`jtbl_carve.py` is additive / regenerate-from-config** — parse the tail data-region + the existing `.rodata`
  carves, add the new fn's jtbl (split its containing data piece), re-emit the address-ordered pieces + the
  `--order` arg. Idempotent. **BOUND-FIX (subtle, cost a false "non-contiguous"):** a new jtbl's end is bounded by
  the next raw dlabel **OR the next EXISTING carve start** — an already-carved adjacent jtbl is GONE from the data
  asm, so the raw dlabels alone over-extend the new jtbl past it.
- **`jtbl_family_bank.bank()` must `make extract` BEFORE the carve** (the sibling asm must match the reverted
  committed config so the carve finds the new fn's RAW jtbl; the old error-string retry was fragile).
- **PROVEN cross-subseg (fleet-scale):** func_801734BC (34-ins PURE jr, clean shared-tail switch `case N:t=-N;break;
  default:goto after;`) in `ov_SC01_077_after` + func_8012ACE0 in `_a` = 2 carves / 2 subsegs → banked ×134, R22
  136/136 byte-identical.
- **A code object emits its jtbls CONTIGUOUS (gcc source order)**, so two matched jr-fns in ONE subseg are
  byte-correct only if their jtbls are ADJACENT in the island. Two flavors:
  - **(a) adjacent → MERGE** into one spanning `.rodata` carve (`jtbl_carve` does this; config-proven on
    func_80171B4C `801D8C48` + func_801734BC `801D8C68`). Byte-proof needs a matched adjacent pair.
  - **(b) non-adjacent (unmatched jtbl between) → ISOLATE** one fn into its own code subseg (whale `_o0b`
    precedent) so each object holds ONE contiguous rodata run. `jtbl_carve` derives the carve subseg from
    `func_subseg`; isolating F preserves carves BELOW F (trim keeps `<F`) → bank same-subseg families ASCENDING.
    **RESOLVED (session 6, byte-proven):** `tools/overlay_src_split.py` (overlay-`.c`-aware partition, 404/404
    round-trip) + `tools/jr_isolate_all.py` (multi-cut resegment) + the **declaration-environment reconstruction**
    of §8c. Full 54-jr isolate-all on ov_SC01_077 → `d19c9580` **byte-identical, R22 clean-fleet 136/136**.
    Applied **LAZILY** (isolate only the cores we actually bank — upfront-×134 would add ~7,200 region files):
    `jtbl_family_bank` catches `jtbl_carve`'s `NON-CONTIGUOUS` fail-loud → `jr_isolate_all --only <core>` →
    re-extract → re-carve. Proven on `func_80178D40` (the 890×134 heaviest core): carve blocked → isolated
    (byte-neutral `d19c9580`) → carve lands in its own subseg.

## §8c Splitting a TU means rebuilding its DECLARATION ENVIRONMENT, not moving text (Phase 26 session 6)

The §8b isolation wall. A mechanical source split is *not* mechanical: this C is written against gcc-2.7.2's
lenient scoping, and a cut silently strands declarations. **Four** file-scope decl sources must be carried
forward into each new region (regions are address-ordered and file order == address order, so ambient flows
strictly FORWARD — every carried decl already preceded every item of the receiving region in the original file):

1. **col-0 decls in the `.c`** — the obvious one (the only one the first attempt handled).
2. **`DEFINE_func_*` macro LEADING externs.** The macro expands *at file scope* to
   `extern <type> <sym>; … <definition>`, so its externs ARE part of the invoking TU's file-scope environment —
   but they live in `engine_core.h`, so **no col-0 text scan of the `.c` can ever see them** (1,377 macros /
   3,929 extern lines / 1,462 symbols). This stranded `func_801734BC` from `extern s16 D_80126B3E;`.
   *(Correcting the session-5 hypothesis: this is NOT a "block-scope extern persists to file scope" gcc quirk —
   the externs are genuinely file-scope, just textually invisible. The 148 externs INSIDE macro bodies are real
   block-scope shadows and must never be hoisted.)*
3. **A function DEFINITION is itself a declaration** for everything below it in its TU. Cut the definition into
   an earlier region and every later caller that took its address breaks (`func_8012B2CC undeclared`).
   Synthesize its prototype — and a **K&R** definition declares an *unprototyped* function, so it must render
   `extern T f();`, never `f(void)` or the K&R param names.
4. **File-local typedefs** used by a carried prototype (`extern s32 f(Vec3s *a0)` → `parse error before '*'`).
   Legal to re-emit because each region becomes its OWN TU. Emit types before decls.

**Why NOT "declare every used symbol from a global symbol→type map"** (the intuitive design): this codebase is
loosely typed, so a symbol legally carries contradictory decls — `func_80173544` is *defined* at file scope as
`s32 f(void *)` yet declared `extern void f(void);` **inside** `func_801734BC`'s body. Hoisting "every used
symbol" lifts that block-scope shadow to file scope, where it collides with the definition — so the design then
needs a heuristic "type-shadowed set" to dodge a problem it created. Carrying forward only what was *already*
file-scope is **conflict-free by construction**: every carried decl already coexisted with every definition in
the one original TU, and decl compatibility is order-symmetric. Shadows stay in bodies and travel with them.

- **Dedup by exact decl TEXT, not by symbol.** One symbol legitimately has several distinct file-scope decls
  (the baseline build emits **87** `type mismatch with previous external decl` warnings and is byte-identical).
  Collapsing to the first drops a decl the original had.
- **Baseline-parity is the warning oracle:** diff the isolated build's warnings against the baseline's. New
  *classes* mean you changed decl visibility; identical classes mean you reproduced it.
- **TRAP — `func_subseg` from the asm tree is stale-prone.** `make extract` does not prune stale subseg dirs, so
  after an isolation BOTH `nonmatchings/<ov>_after/<f>.s` and `nonmatchings/<ov>_jr_<A>/<f>.s` exist; an
  `os.listdir` scan returns the STALE owner and silently re-creates the very collision the isolation removed.
  **Derive the owning subseg from the CONFIG (address → containing code piece).**
- **TRAP — a sweep's revert must restore, not delete.** `overlays.mk` is SHARED by all 134 overlays and every
  one now has a *committed* `<ov>_JTBL_INTERLEAVE`; the old revert dropped the line unconditionally, destroying
  a banked carve on any failed sibling. Restore it to its **committed value** (`git show HEAD:`), splice
  per-overlay (never `git checkout` the shared file mid-sweep), and delete only the region files *this* attempt
  created. `jtbl_family_bank` now refuses to start on a dirty `config/`+`src/` (an uncommitted prior family
  would be silently reverted) — **commit each family before sweeping the next.**

## §8d Templating a body INTO a TU must not CHANGE its declaration environment — demote the carried data externs (Phase 26 session 8, byte-proven on `func_8015AE2C` ×133)

The mirror of §8c. There, *splitting* a TU meant **carrying its decl environment forward**. Here, *templating a
cracked body into* a sibling TU means **not disturbing the environment that is already there** — and the ×N
family sweep was doing exactly that, silently.

`family_remap.gather_externs` carries the exemplar's decl for every symbol the body references and prepends
them at **FILE scope**. For a per-location DATA symbol that the sibling declares only at **BLOCK** scope —
inside its *own* later functions, loosely typed — that carried decl **establishes a global declaration the TU
never had**, and every later block-scope `extern` of that symbol must now agree with it. In loosely-typed
engine code they never do. The whole-binary gate proved both halves:

```
BLOCK(int) -> BLOCK(struct Ent *) -> FILE(void *) ...      builds [ OK ]   (the region, stub state)
FILE(void *) -> BLOCK(int) -> ...                          conflicting types for `D_801812A4'   (ERROR)
```

`D_801812A4` (ov_SC01_000's entity dispatch table) is declared **four incompatible ways in one region** —
`(int)` and `(struct Ent_8015CD20 *)` at block scope inside `func_8015C128` / `func_8015CD20`, then `(void *)`
at file scope ×12. That compiles. Prepend the body's `extern void (*D_801812A4[])(void *);` above them and it
does not. It was the **only** hard error in the build; all 27 carried *function* externs were fine raw.

**THE FIX (`tools/scope_data_externs.py`, a pure draft-text transform):** emit a carried `D_` extern at
**block scope inside the function body** whenever the target TU has **no file-scope decl of that symbol above
the insertion point**. It then declares no global, nothing below it can conflict, and the TU's environment is
preserved exactly. **Byte-neutral** — an `extern` emits no code, and moving it changes neither the symbol nor
the declared type, so every access keeps its opcode. It also *restores fidelity*: the original source declares
these symbols at block scope in precisely this way (m2c/Ghidra emit per-function externs there).
Wired into `jtbl_family_bank` as the `scoped` stage (raw → **scoped** → recovered → reconciled) and used as
the base for the later recovery stages. **First sibling byte-identical; 562-ins core ×133.**

- **Never worse than raw**, which is why it can be applied unconditionally: a symbol that *does* have a
  file-scope decl above is left alone (an identical spelling is a legal duplicate; a differing one is the §41
  reconcile class and errors at file scope either way, so demoting could not have saved it).
- **`reconcile_decls` is the WRONG instrument for this class, twice over.** (a) Its oracle is *fleet-majority*
  (engine_core.h first-seen, else a plurality vote across all overlays) — but the question is not "what does
  the fleet call this symbol", it is "what can *this TU* see". (b) Its `DATA_DECL_LINE_RE` cannot even parse
  the **fn-ptr-array** form `extern void (*D_x[])(void *);`, so it silently skipped the very symbols that were
  failing. A tool that no-ops on the failing input reads exactly like a tool that had nothing to fix.
- **TRIAGE RULE (R17 boundary, Drew 2026-07-13).** "The compiler produced the wrong **BYTES**" → read the gcc
  source (regalloc / sched / cross-jump / CSE — things no C change reaches). "The compiler **refused to
  compile**" → read *our Python*. This was `conflicting types`: a C front-end diagnostic, gcc correctly
  rejecting plain C89. Reading `cse.c`/`global.c` would have taught nothing; the bug was ours.
- **Diagnostics gotcha:** gcc-2.7.2 does not prefix errors with `error:` — grepping a build log for `error`
  finds only make's `Error 33`. Grep for the diagnostic text (`conflicting types`, `undeclared`, `parse error`,
  `redefinition`) instead, and remember `warning: conflicting types for built-in function 'memcpy'` is benign.

## §8e The jtbl ALIGNMENT LAW + the pad-spec filter — multi-table .rodata spans (Phase 29, byte-proven; `.run/probe_jtbl/verdict.md`)

**Two prior cookbook claims are CORRECTED here** (both were instrument errors, R35):
- §8a-pad's "**maspsx drops all `.align`**" is **FALSE**. The `continue` at `maspsx/__init__.py:435` is in
  `preprocess_lines` — an *inventory-only* pass (sbss/bss/sdata dicts) whose skips produce no output; the real
  output path (`process_line`, L872-873 catch-all) re-emits `.align` **verbatim**. The §8a-pad *trim* is still
  right, for a different reason: the trailing pad word belongs to the NEXT table's `.align 3`, which is only
  emitted when that next owner is compiled in the same object.
- The Phase-29 session-2 "half-pin" ("cc1 AND maspsx emit the jtbl `.align 2`") was **inverted**, measured off
  VACUOUS probes (an empty `j $31` fn — no jtbl in them at all; the only `.align 2` was the function-entry
  `.text` align). Lesson: **a probe whose output contains no instance of the thing being probed pins nothing.**

**The law (each link byte-verified in `.run/probe_jtbl/`):**
1. cc1 (Sony gcc 2.7.2) emits `.rdata` + **`.align 3`** + label before **every** switch jump table
   (probe: 2 tables in one TU → 2× `.align 3`; the clean single-table object's `.rodata` sh_addralign=8).
2. maspsx passes `.align` through; `as` bakes the pad into the section **SECTION-RELATIVE** — the linker can
   never remove an intra-object pad. (`as` control: bare `.word` section → Al=4; with `.align 3` → Al=8.)
3. Link placement is always TIGHT: `SUBALIGN(2)` (splat `subalign: 2`, fleet-wide) + `ld_interleave`'s
   `. = ALIGN(., 4)` override input-section alignment — a 4-mod-8 carve start places exactly (the banked
   `0xb07dc` carve is the byte proof). So **only intra-object pads can diverge from the original.**
4. ORIGINAL layout semantics: originally-separate TUs pack **TIGHT** (PSX linker, 4-aligned placement:
   jtbl_801D8078's 51 entries end 0x801D8144 exactly where the next TU's table begins, %8==4); **intra-TU**
   consecutive tables carry a REAL zero-word pad wherever the previous table ends ≡4 mod 8
   (tail2.data.s: jtbl_801D8158/8170/8188/81A0 = 5 entries + one `.word 0` each).
5. ⇒ Merging originally-separate TUs into one decomp TU makes cc1's intra-TU `.align 3` fire where the
   original had a tight TU boundary: a non-first table at original vram ≡4 mod 8 gains a **+4 interior pad**
   → every downstream data symbol shifts → `%lo` relocs break image-wide (func_80131340: pad at rodata 0xCC,
   SHA1 fail from a clean build). Conversely a genuine intra-TU pad must be REPRODUCED.
6. **Isolation does NOT fix this in general**: `.align` is section-relative, so an isolated object whose
   first table starts at vram ≡4 mod 8 flips the parity of every INTERNAL align — a multi-table function
   with a 4-mod-8 first table would mis-pad inside its own object. Only explicit pad control is general.

**The mechanism (`tools/jtbl_rodata_pads.py` + `jtbl_carve` + Makefile `JTBL_PADS`):** for a multi-table
span, `jtbl_carve` derives each boundary's pad by **interval arithmetic** (`pad[K] = start[K] − end[K−1]`
∈ {0,4}; a 4-gap must be a verifiably-zero payload word, else NON-CONTIGUOUS→isolate) and writes a
per-object `build/src/<ov>/<sub>.o: JTBL_PADS := 0,4,…` target var into `config/overlays.mk`; the Makefile
pipes that object through the filter, which **REPLACES each rodata `.align` with the spec'd pad bytes**
(`.word 0` or nothing). Per-sibling self-adapting (each overlay's own addresses), fail-loud on drift
(spec count ≠ align count; non-`.align 3`; non-jtbl rodata content). Committed spec values are CARRIED,
never re-derived (a committed span's interior boundaries are unrecoverable from its interval).
Single-table carves get no var — their pipeline is byte-identical to pre-§8e (their lone `.align 3` at
section offset 0 pads nothing and SUBALIGN neutralizes the sh_addralign).
- **Object-layer proof before image-layer claims:** verbatim vs filtered objdump — 0xE4/pad-at-0xCC vs
  0xE0/tight — settled the mechanism before any carve landed. Cheap, decisive, reusable probe shape.

**§8e-2 — the spec-derivation law (learned banking the 4 giants, Phase 29):**
- **The ZERO-WORD rule is the whole derivation:** pad before table K ⟺ payload word at `start[K]−4`
  is `0x00000000` (a zero can never be a table ENTRY — the §8a-pad axiom). No entry counts, no interval
  bookkeeping. `spec_from_starts` needs only the span's TABLE STARTS + the payload.
- **Table starts are PERISHABLE — persist them.** `make extract` prunes a matched owner's stub `.s`, so a
  span's interior structure becomes unrecoverable (the `func_8013F350` lesson: the existing `0xb0740`
  carve was a Phase-26 **merged double** (8+5 tight) that the red-team's "all single-table" sample missed
  — R14; its structure had to be re-derived from the compiled stream + span length). The `JTBL_PADS` line
  now persists starts as span-relative offsets (`tables=+0x0,+0x20,…`); source priority per span:
  untouched+line → reuse verbatim · untouched+no-line → skip (its natural `.align 3`s are committed-green)
  · touched → union{new fn's `.s`, surviving stub `.s`, line `tables=` rebased, `--span-tables` override,
  `--like <exemplar>` role-transfer} → zero-word rule. Sibling sweeps get structure via `--like`
  (same family ⇒ same span shape; pads still derived from the LOCAL payload).
- **4-mod-8 FIRST tables are placement-only** (SUBALIGN packs them tight — `jtbl_801D836C`/`0xb07dc`
  proofs); only NON-first tables need the spec. A single-table carve never needs a line.
- **Splice-reconcile carry-overs** (the 59C84/F350 banks; all §56-class, byte-neutral): the draft's
  standalone scalar typedefs must be STRIPPED in-TU; a conflicting draft decl is replaced by the
  **macro-canonical redecl** (NOT just dropped — C89 rejects file-scope use-before-declaration, so the
  decl must exist above the use) + §18 width-preserving store casts (`*(u16 *)&D_x = …` under a canonical
  `u8`) + §17a-1 fn-ptr call casts where the canonical prototype differs from the matched call shape
  (`((s32 (*)(s32))func_801416D4)(…)` under a `(s16)` def; a prototyped `(void)` canon needs it too).
  §30#2 def-side widen (`extern void`→`s32` in every DISCARDING caller decl, incl. engine_core macros).
- **Crash-ordering gotcha:** `jtbl_carve.apply()` writes the splat yaml BEFORE the overlays.mk vars — a
  crash between the two leaves a half-applied config vs stale asm (symptom: phantom trim counts /
  shifted NON-CONTIGUOUS offsets). Recover: `git checkout` both configs + re-extract, then re-carve.
- **The CLEAN-DRAFT law (the 59C84 sweep lesson, 3/8→100%):** a family sweep's `--raw` draft must carry
  the exemplar's reconciles as **canonical-form decls + call casts IN THE DRAFT TEXT** (typedefs stripped;
  decls in the fleet-canonical spelling; §17a-1/§18 casts baked in). The per-sibling ladder absorbs *some*
  of a dirty draft on *some* siblings (3/8), which disguises the class as random — diagnose by re-running
  ONE failed sibling with the cleaned draft (BANKED ⇒ the class is the draft, not the siblings). Symbol
  names remap per sibling, so textual canonical fixes transfer.
- **Named deferral classes from the 4-giant campaign** (fail-loud, zero corruption, burn-down items):
  (i) the 4 SC07 `files=1` overlays compose a new span against a PRE-EXISTING `_o2b` carve whose object
  emits no tables at raw stage (the count-guard refuses — needs a per-overlay look); (ii) an **-O0 family
  member cannot bank until its overlay has the -O0 cluster carve** (`rollout_o0_cluster`, the Arm-A splat
  wall) — func_8013C414 banked ×1 (ov_SC01_077 has `_o0`) but its 137 siblings uniformly gate-fail at -O2;
  the family rides the -O0-rollout dependency, not a codegen wall.

## §9 Link real PsyQ library objects byte-exact (Phase 7 — GO proven)
~350 of BFM's functions are unmodified PsyQ 4.0 SDK code. They are **byte-identical to the real PsyQ library
objects**, so link them directly instead of hand-decompiling — and each library `.o` brings its own correct
alignment (dissolving the library-half of §8's `.align 3` problem). Validated: `CdPosToInt`/`CdIntToPos` EXACT
vs PsyQ libcd; `PRESET_OBJ_*` ∈ `LIBGS.LIB`. Workflow (the decomp-standard psyq-obj-parser path):
- **Tools** (gitignored `tools/psyq/`): `psyq-obj-parser` (decompme prebuilt — `.OBJ`→ELF; rejects `.LIB`),
  `lib40/*.LIB` = PsyQ **4.0 USA** libraries (DTL-S2002 R2.0 = BFM's version; extracted from the redump ISO via
  `tools/bfm_extract/iso9660.py`). Identify a function's library by searching the `.LIB` for a NON-relocated
  instruction run from its EXE bytes (relocated runs false-negative — use leaves or interior runs).
- **Integration:** split `.LIB` (LIB\x01 archive) → `.OBJ` → `psyq-obj-parser` → `ar` per lib → link the `.o`
  for each library function and drop its INCLUDE_ASM. BFM mixes 4.0+4.2 library stamps, so a few objects may
  need 4.2/4.3 libs — determine per-object by the byte test.
- **Proven full-object link recipe (SYS.o byte-identical to BFM, Phase 7):**
  1. **Placement** — `tools/psyq_identify.py <elf_dir>`: relocation-masked search finds each object's `.text`
     vram in the EXE. Per library the used objects are CONTIGUOUS in object order → place the first at the
     region base, link the rest in order.
  2. **Recover externals** — symbols the object references but doesn't define are usually absent from
     `symbols.us.txt`; read them straight out of the EXE's RESOLVED relocations: for each reloc, `R_MIPS_26` →
     `target = ((word&0x3FFFFFF)<<2)|(pc&0xF0000000)`; an `HI16`+`LO16` pair → `(hi<<16)+signext(lo)`. Feed as
     `ld --defsym NAME=0xADDR`.
  3. **Alignment** — psyq-obj-parser emits `.text/.rdata/.data` at align 2**3; the original is 4-aligned, so an
     8-align bumps the section +4 (the tell: every `LO16` to that section is off by +4). Fix:
     `objcopy --set-section-alignment '.rdata=4' --set-section-alignment '.data=4' obj.o obj_a.o` before linking.
  4. **Link + verify** — `ld -T <SECTIONS: . = <text vram>; .text:{*(.text)} . = <island>; .rdata:{*(.rodata)
     *(.rdata)} . = <data vram>; .data:{*(.data)}> --defsym … obj_a.o` → `objcopy -O binary --only-section
     .text` → byte-compare to the EXE. `.rdata`/`.data` vrams are found by searching the EXE for the section
     bytes (`objcopy --only-section`). Tools: `tools/psyq_lib_split.py`, `tools/psyq_build_libs.sh`,
     `tools/psyq_identify.py`.

### §9.1 Generalised per-object linker — `tools/psyq_link.py` (+ `psyq_link_lib.py`), 18/18 libcd byte-exact
Session-D generalised the SYS.o recipe into a tool that links **every** used object of a library byte-identical.
Two gotchas the one-object recipe didn't surface, both now handled:
- **psyq-obj-parser MISLABELS common-style globals.** Uninitialised globals (PSYLINK `.comm`) get packed into each
  object's `.bss` with *sequential* `st_value`s, but the original linker SCATTERED them (e.g. libcd CDROM's
  `StRingAddr`→`0x800c7c94` and `StRingSize`→`0x800c7f00` are 0x26c apart, the ELF claims 8). **Trust no
  `st_value`** for placement.
- **Robust model = recover-everything + selective override.** Place `.text` at its vram and the *real* initialised
  sections at their bases (byte-search; or, for `.bss`/reloc-bearing `.data`, the address the section symbol itself
  resolves to in the EXE). Resolve every symbol the `.text` references by the address read out of the EXE's already-
  linked relocations (`R_MIPS_26` jump field; `HI16`+`LO16` immediates; object addend subtracted, but PsyQ addends
  are 0). A symbol that is a *genuine* member of a placed section (recovered == base+st_value) is left to `ld`; a
  *mislabelled* one is **`--weaken-symbol`'d then `--defsym`'d** to its recovered address (a strong defsym beats the
  weak section def — `--strip-symbol` is refused on reloc-referenced symbols, weaken isn't). `.text` byte-compare is
  the check (G3).
- **Tells:** `ld: 'X' referenced … defined in discarded section` = you discarded a section whose section-symbol the
  `.text` needs → place it instead. A 1–4 word residual in `lui/lw/sw` immediates (`3c0480xx`) = a mislabelled
  `.bss` common → weaken+defsym it.
- **Externals split intra/extra-library.** Per-object "externals" (UND) include symbols defined in *sibling* objects
  (resolve internally in a whole-library link) vs truly external ones (other libs' funcs like `VSync`/`memcpy`, and
  module data globals like `St*`) — the latter feed `--defsym`/`symbols.us.txt` (R15). libcd: 82 union = 48 intra +
  34 extra. `tools/psyq_link_lib.py <elf_dir>` links all located objects, flags address conflicts, writes
  `.run/psyq_link.<lib>.json`. Same tooling will serve libgs/libspu/… (the +24 culprits).

### §9.2 Wire a library region into the build with NOLOAD — no data carving (`tools/psyq_link_region.py`)
To replace the asm stubs of a library's functions with the real objects in the byte-identical build WITHOUT
carving the flat `data` subsegment:
- **Place `.text` LOADED at each object's exact vram; place `.data`/`.rdata`/`.bss` as NOLOAD at their vrams.** A
  NOLOAD section contributes its symbol addresses but **zero bytes** to `objcopy -O binary`, so the build's existing
  flat data subsegment still emits those bytes (no double-emit, no carve) while the hundreds of section-relative
  `.text` refs resolve via the NOLOAD placement. Set `.data`/`.rdata`/`.bss` align=4 first or a 4-but-not-8-aligned
  vram bumps +4 (same tell as §9). Needs `ld --no-check-sections` (NOLOAD overlaps the loaded flat blob's VMA).
- **Weaken every `.bss`/`.sbss`-defined named symbol**, then `--defsym` it to its recovered address: the common-style
  globals are scattered (genuine `CD_*` and mislabelled `St*` alike, and a `.bss` symbol of object A may be referenced
  by object B), so a uniform strong-defsym-beats-weak-def resolves them all. Truly-undefined externals (other libs'
  funcs) surface from a probe link's `undefined reference` lines → defsym from the recovered map.
- **Place each object at its EXACT vram, not by concatenation** — a library's objects are *mostly* contiguous but a
  non-library function can sit between them (libcd: a 76-B gap of non-libcd code between C_003 and C_004), so naive
  `*(.text)` concatenation drifts past the gap. The gap stays an asm stub in the build (split the splat code subseg
  into [pre][lib block 1][gap stub][lib block 2][post]). `tools/psyq_link_region.py <elf_dir> --emit <p>` verifies the
  region byte-identical per-object and emits `<p>.ld` (text + NOLOAD lines) + `<p>.syms`. libcd: 18 objects byte-exact,
  36 externals.

### §9.3 Make it the build: resegment + swap + resolve (`tools/psyq_integrate.py`, libcd DONE)
Wiring a library region into `make build` byte-identical (libcd: 58 SDK funcs, full pipeline green):
- **Resegment the splat text subseg into [pre][block1][gap][block2…][post]** at the library blocks
  (one `c` subseg per block + per non-library gap; vram→file = −0x8000F800). `make extract` regenerates
  the gap/post stubs; **`tools/split_src_region.py trim`** rewrites the curated pre-file (keeps items
  <lo, preserving real C and `#ifdef NON_MATCHING` blocks by brace/`#endif` matching) — splat will NOT
  overwrite an existing `.c`, so a stale one mis-places everything. splat-auto-empties (`void f(void){}`)
  ≥hi regenerate identically — no move needed.
- **`psyq_integrate.py` (run in the `$(OUT)` recipe, after objects compile — the externals discovery
  trial-links the whole image):** (1) prep objects (align=4 + weaken every `.bss` symbol) → `build/psyq/<lib>/`;
  (2) rewrite the splat `.ld` — replace each `build/src/<stub>.o(.text);` with the block's real
  `<obj>.o(.text);` (concatenation places them at their vrams since the pre-file ends exactly at the block
  start) AND **delete the stub object's other `(.rodata/.data/.bss)` lines** (else its stub symbols
  multiply-define the real ones); add per-object **NOLOAD** data sections sorted by vram (unsorted →
  "dot moved backwards"); (3) resolve externals via a **full trial link** (symbols still defined elsewhere
  never appear, so no double-def — no blanket exclude needed).
- **External resolution, in order:** `func_<addr>` (external code/data calls a libcd fn by its splat
  address-name; the real object exports a PsyQ name) → that address; a `symbols.us.txt` name (jump-table /
  dispatch pointer in the flat `.data`, e.g. `BIOS_OBJ_3B8`) → its `symbols.us.txt` address; a recovered
  data/extern global (`St*`/`CD_*`) → recovered. **Always also defsym EVERY weakened `.bss` common** — the
  ones whose object's `.bss` is NOLOAD-placed resolve to that weak placement and never show as undefined
  (the 8-word `StMode` miss). Capture BOTH `undefined reference` AND `defined in discarded section` from the
  trial link.
- **Byte-identical with OR without the SDK objects** (the stubs reproduce the same bytes), so gate the
  whole thing on `[ -d <elf_dir> ]` — a fresh clone without `tools/psyq/` builds via stubs. Idempotent
  (`build/psyq/<lib>` in the `.ld` ⇒ re-derive syms only).

### §9.4 Integrating a SECOND library (libgs block 6 after libcd) — multi-library gotchas
Wiring a 2nd `psyq_integrate` call into the same build (libcd, then a libgs block) surfaced bugs the
single-library path never hit. All fixed in `tools/psyq_integrate.py`; reuse for libspu/libsnd/…:
- **Namespace the NOLOAD section names per library** (`.nl_<objdir-basename>_<i>`, e.g. `.nl_libgs6_0`).
  The idempotency guard was a global `if ".nl_0" not in ld` — so the 2nd integration saw `.nl_0` (from
  libcd) and SKIPPED adding its own NOLOAD lines, discarding that library's `.data/.rdata/.bss`
  (symptom: `'.bss'/'.rdata' referenced … defined in discarded section` for the 2nd lib's objects, §9.1 tell).
- **Globally re-sort ALL `.nl_*` NOLOAD lines by vram across libraries** at the end of each integrate.
  Two separately-sorted groups whose vram ranges interleave make ld's location counter jump back
  (`warning: dot moved backwards`) — harmless (NOLOAD emits no bytes) but noisy. Pure reordering.
- **Pass already-emitted sibling `*_externals.ld` to the trial link.** The 2nd library's trial link sees
  the FIRST library's real objects (already in the `.ld`) referencing symbols defined only in the first
  library's externals (e.g. libcd objects call `DMACallback`/`DeliverEvent`); without the sibling syms the
  trial reports them as spurious `!! UNRESOLVED`. Glob `build/psyq/*_externals.ld` minus the current one.
- **A resegment can shift spimdisasm's auto-detected function/data boundaries** in the UNCHANGED regions
  around the new subseg (shrinking 800b re-merged `func_80052FCC/053050` and re-typed the `D_80062998`
  data table as a `func_`). Two deterministic fixes, both from the real artifacts (G1): declare the
  affected REAL functions in `symbols.us.txt` (verify via the PsyQ object's symbol table — these were
  `GsMulCoord2/3` in MATRIX.o), and carve any trailing data-in-text table as its own `data` subseg (§8;
  here extend the front-data subseg back to the table start, update `ld_interleave` FRONT_DATA basename).
  Always regenerate the split `src/*.c` from the fresh extract so stubs match the generated `.s`.
- **Block selection is by EXE-placement + disambiguation, not the full library.** A library's objects span
  several non-contiguous blocks (libgs: 6 blocks + gaps incl. the GS_001 scattered-`.bss` gap, §9.1).
  `psyq_identify <full-lib-dir> <lo> <hi>` over ONE block's range reports the right objects PLUS byte-
  identical-`.text` aliases (GS_131≡RVWUNIT, PRESET2≡PRESET3, OBJT2≡OBJT3); keep the one that also
  matches `.data/.rdata` (`psyq_link_region --verify` confirms per-object). Hardcode the disambiguated
  object list in a committed regen script (`tools/make_libgs.sh`) — SDK-derived dir, gitignored.

### §9.5 Integrating a WHOLE multi-block library in one call (full libgs — Phase 7 session G)
Block 6 alone (§9.4) proved the pattern; the full library is then ONE `psyq_integrate` call over all of
its used objects — no separate integration per block. integrate auto-splits the elf dir's vram-ordered
objects into contiguous runs (`contiguous_blocks`) and maps the i-th run to the i-th stub: pass one
block stub per contiguous run, and a plain asm stub per non-library gap (gaps keep their own subseg).
- **Derive the block/gap structure empirically (G1), don't trust the notes.** `psyq_identify <used-dir>`
  prints each object's vram; a new block starts wherever the next object's vram ≠ the previous object's
  end (`vram + nins*4`). libgs = 6 blocks, gaps 80/48/1536/48/304 B (the 1536 is the excluded GS_001).
  Resegment the splat code subseg into `[game-pre][block1][gap1]…[blockN][gapN]…` (vram→file =
  −0x8000F800); block subsegs become the `libgsN` integrate stubs, gap subsegs stay `gsgapN` asm stubs
  (incl. the GS_001 gap). One `split_src_region.py trim` drops the old single-subseg's stubs from the
  pre-file — but verify FIRST that **no matched C lives in [lo,hi)** (trim drops that range
  unconditionally; here all matched fns were ≤0x8002Axxx, far below the 0x80051804 libgs base).
- **Short objects need the placement WINDOW (new `psyq_integrate <stubs> <lo> <hi>` arg).** An object
  whose `.text` is too short to anchor uniquely over the whole EXE — libgs **GS_106** (8 ins; its pattern
  recurs in game code) — is `ambiguous` in the default 0x80010000..0x800629DC scan, so it drops from the
  placement map, its block splits, and the block↔stub count breaks. Pass the library's text window
  (wired in the Makefile integrate call: `… libgs1,…,libgs6 0x80051804 0x80057928`); the object anchors
  uniquely there. `tools/make_libgs.sh --verify` (psyq_link_region over the same window) is the preflight.
- **Result + checks:** 31 libgs objects / 6 blocks linked byte-identical in one integrate (≈49 named SDK
  functions — count OBJECTS, not stubs: splat over-segments library code into ~5× more INCLUDE_ASM stubs
  than real functions). The finer resegmentation (10 new subsegs) was **split-deterministic** across two
  clean extracts (no new §9.4 boundary re-detection — the GsMulCoord2/3 declarations + the 53198 data
  carve from §9.4 already cover it) and **byte-identical WITH or WITHOUT** the SDK objects (stub
  fallback, fresh-clone-safe). The unified call cleanly supersedes the §9.4 block-6-only integration.

### §9.6 Scaling library linking to the whole EXE (Phase 8 — 8 libs linked, 20%→50% byte-identical)
Phase 8 linked the remaining footprint libraries (libetc/libgpu/libmcrd/libc2/libgte/libspu/libsnd/libapi/
libcard). New patterns + tools that make a fragmented, multi-library EXE tractable:
- **Survey first (`psyq_identify` over every built `.run/obj40/*`).** Produces the byte-confirmed footprint
  map (`docs/psyq-worklist.md`): which libs place, how many blocks, regions, aliases. 3 libs (libmath/libc/
  libsn) place 0 objects — BFM links libc2 not libc. Replaces guesswork (R14).
- **`tools/gen_lib_subsegs.py` automates the multi-block resegment.** A library scatters across a game-code
  region in many contiguous blocks (libgte = 22, libsnd/libspu combined = 9). The tool places the objects,
  groups blocks, and emits the splat subseg lines (`libN` blocks + game-code gap frags) + the integrate stub
  list. **Boundary gotcha (was a real bug):** a block's end = the last object's **`.text` SECTION size**
  (`readelf`, 8-aligned), NOT `psyq_identify`'s instruction count × 4 — the count omits trailing align pad
  (libc2 SETJMP.o: 30 ins = 0x78, but `.text` = 0x80). A too-low boundary overlaps the object's padded tail
  and the relink inserts +N padding, shifting the WHOLE downstream image (pervasive 1-byte reloc diffs + a
  grown file). The tool bakes the section-size rule in.
- **Pass the stub list via a make var** (`LIBGTE_STUBS := libgte1,…`) for the long ones; `progress.py`'s
  `linked_subsegs()` resolves `$(VAR)` from the Makefile's `:=` defs so LINKED still counts them.
- **Interleaved libraries → ONE combined region.** libspu+libsnd interleave object-by-object in 0x3A444..
  0x4239C, so two independent passes tangle (each lib's objects span the other's gaps). Instead build a
  combined curated dir (`tools/make_snd_used.py`): merge both libs' objects by vram, and for an aliased
  address (>1 object, same masked `.text`) pick the one whose linked `.text` **byte-matches** the EXE
  (`psyq_link.link_object`). libapi+libcard share the same trick (`make_apicard_used.py`, C112 dedup).
- **Scattered-`.bss` exclusion = the GS_001 class, now also cross-object.** An object whose `.bss` commons
  the original linker scattered (referenced as `.bss`+offset via one section symbol, but resolving to >1 base
  in the EXE) can't be reproduced by a single NOLOAD base → EXCLUDE it (stays a byte-identical stub). Detect:
  `psyq_link_region` shows N words differ in that object and `conflicts>0`. Exclude **by address** (the alias
  twin fails identically). Cases: libgpu SYS.o, sound S_R/S_GRMDT/VM_F; plus a false placement (S_IH @0x3D94C
  is inside libsnd SSSTART.o). Excluding a few objects banks the other 60.
- **CLEAN-REBUILD gotcha (verification).** `psyq_integrate` rewrites the `.ld` in place; after a *src* change
  an **incremental** `make build` can re-run integrate on an already-rewritten `.ld` and transiently
  mis-resolve a sibling library's externals (a harvest falsely diffed in libmcrd). The canonical verify is
  always `make clean && make extract && make build` — never trust an incremental build for a byte check.
- **Honest metric:** linked objects stay INCLUDE_ASM stubs in their `.c` (the fresh-clone fallback), so
  `progress.py` counts them in a distinct **LINKED** bucket (not REAL, not stub). REAL = hand-written C only.

---

### §9.7 Binary-agnostic toolchain refactor (Phase 9) — the reusable pattern for Gen2

Gen2 builds many binaries (resident blob, location overlays) with these same tools. The refactor
that got there, and the technique to land it safely without ever breaking the byte-locked EXE:

- **Required params, no defaults.** Every binary-specific value — `--vram-base` (the fileoff→vram
  delta), `--exe`, `--symbols` — is a REQUIRED argparse/function parameter. No module-level
  `EXE`/`VRAM_BASE` default an overlay could silently inherit; a miss fails loud (argparse error /
  NameError). The roadmap's #1 risk was a hidden EXE default surfacing as a wrong overlay address
  only at Phase 10 — required params make that impossible by construction.
- **`--vram-base` is a single scalar** (EXE `0x8000F800` = `0x80010000 − 0x800`), sufficient for any
  flat-loaded PS1 image. The text-scan window `[lo hi]` is a SEPARATE, orthogonal param
  (scan-narrowing only, for short/ambiguous objects) — never conflate the two.
- **Transitional-default technique (keeps every per-tool commit green despite in-process coupling).**
  `psyq_integrate`/`psyq_link_region` import `recover_sym_addrs`/`VRAM_BASE` from `psyq_link`
  IN-PROCESS, so deleting the global in one tool's commit breaks the build mid-sequence. Instead:
  each tool first gains the param DEFAULTING to the kept EXE global (build stays byte-identical as
  callers are updated one commit at a time); a FINAL commit removes the globals + all defaults →
  required, once every caller passes explicitly. Refactor **leaf-first** (`psyq_link` →
  `psyq_identify` → `psyq_link_region` → `psyq_integrate`) so a missed call site fails loud, not
  silently on a stale global that happens to hold the EXE value.
- **Negative control proves threading.** A pure no-op (`143dbb89…` unchanged) can pass for the wrong
  reason (param accepted-but-ignored). Always ALSO pass a deliberately wrong `--vram-base` and
  confirm the build/link DIVERGES (`cae22f7e…` ≠ target) — that proves the value is load-bearing.
  Per-tool: `psyq_link.py … --vram-base 0x8000F900` must FAIL where `0x8000F800` PASSes.
- **Makefile shape.** `BINARIES := main` (alias keys) + `main_*` vars + `$(BINARY)`-resolved aliases
  (`OUT`/`LD_SCRIPT`/`VRAM_BASE`/…). EXE artifact paths preserved verbatim (no rename churn against
  the oracle). EXE-only SDK-integration + `ld_interleave` blocks gated under `ifeq ($(BINARY),main)`.
  **Lockstep gotcha:** `progress.py` parses the Makefile's `psyq_integrate` calls for the LINKED
  subseg list, so when you add leading `--flag value` pairs to those calls, its stub-list regex must
  consume them (`psyq_integrate\.py(?:\s+--\S+\s+\S+)*\s+\S+\s+\S+\s+\S+\s+\S+\s+(\S+)`) — land the
  regex change in the SAME commit, gated on `make report` reproducing the LINKED count.

## §10 Closing the regalloc/scheduling hard tail by hand (LZSS, Phase 7 session F — the full close)
`LzssDecodeSector` (0x80018730) was the last-mile case the §5a barrier set up but did not finish: with the
cross-jump barrier the instruction COUNT was correct (122) but ~4 register-allocation / scheduling slots were
wrong. The decomp-permuter could NOT measure progress (its object score floats on the `.rodata`-vs-`jtbl`
floor — §5a caveat), and its random search diverged. **Hand-solving with the §3a research tier won** — every
fix below was ground-truthed against the pinned **gcc-2.7.2** source (`reorg.c`, `jump.c`, `local-alloc.c`).
These idioms are general; reach for them whenever a function is instruction-count-correct but off by a few
regalloc/schedule slots and the permuter can't score it.

### The clean object-level metric (use this, not the permuter score, for jtbl/rodata functions)
The permuter/asm-differ **object** score is polluted by the migrated-jtbl symbol name (`.rodata` vs
`jtbl_<addr>`), so it can't see real `.text` progress. Two floor-free checks (no link needed):
- **Normalized instruction diff** — `objdump -dr --no-show-raw-insn -j .text`, strip the `R_MIPS_*` lines,
  the `<sym>` operands and the branch-target hex, then `diff` candidate vs `target.o`. Shows ONLY real
  register/opcode/order differences. (`.run/permuter/LzssDecodeSector/try.sh` is the reference impl.)
- **Raw `.text` byte compare** — `objcopy -O binary --only-section=.text cand.o c.text` and `… target.o
  t.text`, then `cmp -l`. In a relocatable object the `%hi/%lo` immediates of an unresolved symbol are BOTH
  0 (the reloc fills them at link), so a migrated jtbl reference is byte-identical here and does NOT show —
  the only diffs that remain are genuine (e.g. a wrong *local* branch offset). This is the fast, authoritative
  iterate-on-`.text` oracle; finish with the linked `make check` (G3) for the whole-binary truth.

### Residual A — commutative `|`/`&`/`+` result lands in the wrong source-operand register
`local-alloc.c combine_regs` (≈line 1855) ties a commutative op's result to the **first RTL operand that
dies** at the insn (RTL operand order = source order; gcc 2.7.2 has NO `swap_commutative_operands`, so the
source order survives). Target `or $v0,$v0,$v1` ⇒ result tied to the `code&0xFF` operand ($v0).
- **Fix A1 — operand order:** write the operand whose register you want the result in FIRST:
  `code = (code & 0xFF) | (nh << 8);` (not `(nh<<8)|(code&0xFF)`).
- **Fix A1-companion — DECOUPLE shared inputs (load-bearing):** if a variable feeds *two* expressions
  (`nb` fed both the low- and high-byte ORs), reshaping one OR re-allocates that variable in BOTH paths
  (it jumped `$v1`→`$a0`). Give the second use its **own variable** (`nh`) so the operand-order change is
  local. This was the unlock — A1 alone "didn't work" only because of the coupling.

### Residual B — a `return <const>` materialised late / merged instead of distributed per-site
`reorg.c fill_simple_delay_slots` backward-scan (≈line 2907) pulls the common `li $v0,K` out of the
predecessors into the shared epilogue's branch-delay slot, and `redundant_insn` then collapses the other
copies — so one `li $v0,1` ends up in the `j <epilogue>` slot instead of one per return site. Three levers,
applied where each fits:
- **B-distribute (shared tail reached by ≥2 predecessors):** carry the value in a **plain local set in each
  PREDECESSOR block** (`result = 1; newState = N; goto save;` … `save: …stores…; return result;`). Because
  the value is live-in from two defs, gcc emits a distinct `li $v0,1` per predecessor and leaves the tail's
  delay slot `nop`. (A barrier is NOT needed for this half; the predecessor structure is.)
- **B-schedule-early (single-path block whose `li $v0,K`'s only use is the shared `jr ra`):** the sched
  list-scheduler gives an independent `li $v0,K` priority 0 (its use is in another block) and the tie-break
  drops it to just before `jr ra`; the target schedules it first. Force it with an **explicit `$v0` register
  local pinned by a read-only input-asm BEFORE the stores**:
  ```c
  register s32 r __asm__("$2");
  r = 1;
  __asm__ __volatile__("" : : "r"(r));   /* materialise li $v0,1 here, ahead of the stores */
  …stores…
  __asm__ __volatile__("" ::: "memory"); /* the §5a cross-jump barrier, still required */
  return r;
  ```
  A plain `result` local does NOT work here (gcc rematerialises the constant at the return); the `+r`/`"=r":"0"`
  read-write pins put it in `$v1`; only the explicit-`$2` local + early read-only input pin lands `li $v0,1`
  first, in `$v0`. (Scope `r` to the one block so `$v0` stays free as scratch elsewhere.)
- **B3-reuse-the-compare (a `return 0` whose 0 already sits in a reg):** a `switch(x){case…}` range check is
  `sltiu $v0,x,N; beqz $v0,<dft>`; on the out-of-range path `$v0==0` already equals the wanted `return 0`.
  Give gcc nothing else to do: **NO `default:` and NO statement after the switch** → the `beqz` threads
  straight to `jr ra`, reusing the `sltiu` result (target `beqz $v0,.epilogue`). An explicit
  `if(x>=N)return 0;`, a `default: return 0;`, or a trailing `return 0;` each forces a separate
  `move $v0,$zero` (+1 insn / wrong branch target). Falling off the end of the non-void function is
  deliberate here and matches the original (gcc warns under `-Wall`; harmless). Cross-refs cookbook §3 (T4
  branch-polarity / fall-through) — same family.

### Method note (reinforces §3a + R16)
The permuter is the wrong tool when (a) its score can't see the residual (rodata/jtbl floor) or (b) the
residual is a specific compiler-internal placement rather than a randomizable C perturbation. For those,
**web-research the exact pinned compiler source** (§3a) to name the pass and its bail/tie condition, then
express the lever in C. Here a research agent reading `reorg.c`/`jump.c`/`local-alloc.c` produced all four
levers directly; hand-iteration with the clean `.text` metric closed it in a few compiles. Pin every such
construct with a `LOAD-BEARING` comment naming the pass — a future reader WILL try to "simplify" them.

## §11 Cross-binary dedup & code-sharing (Phase 11 — "one match unlocks many")

BFM is overlay-heavy: 134 location overlays all load to the SAME vram `0x80128158` and run on the same engine,
so they share enormous amounts of code (a 770-instruction engine fn is byte-identical in **all 134**). Match a
shared fn ONCE, credit every binary it lives in. The pipeline (all Ghidra-free except the EXE/resident sigs):

**1. Sign every binary → `.run/sig.<bin>.jsonl`.** `make sig-refresh` (Ghidra, EXE/resident) + `make
sig-overlays` (the 134 `0.4.dec` via `tools/sig_image.py`, no Ghidra). Each fn gets `h_exact` (SHA1 of raw
instruction bytes), `h_norm` (structural), `h_seq`, `nins`, `calls`.

**2. Group across binaries → `docs/duplicates.cross.md`.** `tools/dup_report.py --cross` (run by `make report`,
gated `BINARY=main`) buckets ALL sigs by `h_exact` then `h_norm`, splits cross-binary (members in >1 binary —
the **Phase-12/13 work queue**) vs intra-binary, ranks by collapsible bytes `(count−1)×nins×4`, top-200 capped.

**3. Register a share → `config/dedup.us.yaml`.** `group → {id, tier, hash, source, func, members:[{binary,
vram, name}]}`. `tools/dedup_integrate.py --check` is the **byte-honesty gate** (fail-closed if a member's live
sig hash drifts from the recorded `hash`); wired into `make report` so a stale share fails the report (P9).

### The mechanism: game-code dedup is SOURCE-LEVEL, not an object swap (R-D1, the key lesson)
`psyq_integrate`'s stub-object swap works only for separate library **subsegments**. Game-code functions are
**interior to one compiled object per binary** (`build/src/800.o`, `build/resident/resident.o`, each overlay's
one object) — the linker can't excise interior bytes. So you share at the SOURCE level: author the matched body
ONCE as a macro in `src/shared/<fn>.h` and instantiate it at each member site in each binary's `.c`:

```c
// src/shared/clearTbl40.h
#define CLEAR_TBL40(name) void name(void) { s32 i; for (i=0x40; i>=0; i-=0x10) (&D_80076251)[i]=0; }
// src/800.c:   CLEAR_TBL40(func_80037004)   ...   CLEAR_TBL40(func_80037334)
```
Same bytes land at each vram. The **byte-gate is the existing per-binary `make check`** — the image is identical
or it is not. `h_exact` shares are risk-free; `h_norm` shares are CANDIDATES, accepted only if every claiming
binary stays byte-identical (a wrong `h_norm` group wastes a build, never poisons an image). A shared `.h` is
skipped by the `find src -name '*.c'` OBJS glob automatically (no exclusion needed). `progress.py` counts dedup
members as REAL via the registry (the macro form isn't a parseable function def).

### `sig_image.py` (Ghidra-free signer) — notes for reuse on overlays
- **`h_exact` is the workhorse**: SHA1 of raw bytes → format-independent → byte-matches the Ghidra dumper with
  no normalization. Validated 100% on the resident's contiguous/non-GTE functions. Use it as the cross-tool tier.
- **`h_norm` is self-consistent, NOT Ghidra-byte-exact** (R-D2): masks j/jal targets, lui highs, hi/lo-paired
  address-los (a consistent lui→reg tracker); keeps registers / true constants / PC-relative branch offsets.
  Uniform within the overlay fleet (catches different-offset structural dups); does not cross-compare with the
  Ghidra-signed EXE/resident `h_norm` (low value — overlays *call*, don't embed, the resident). Full normToken
  byte-match is a deferred refinement.
- **Boundary detection**: (a) seeded (pass `--seeds <sig.jsonl>` when boundaries are known, e.g. the resident);
  (b) `--bootstrap` for overlays = **linear partition** (split contiguous code at the first `jr $ra`(+delay)
  that lies at/after all forward branch targets — handles early-return + double-epilogue) bounded by
  `detect_code_end` (first run of ≥3 invalid instrs = the code→data transition; overlay code decodes ~100%
  valid). Call-graph BFS FAILS on overlays (they dispatch via function-pointer tables, not `jal`). Residual:
  jump-table-only fns + non-contiguous Ghidra bodies (D5) are missed — conservative, fixed when splat configs
  land (Phase 13).

### Per-binary toolchain provenance (R24)
Verify the toolchain per binary before linking its library code: the EXE is PsyQ 4.0, the **resident is 4.7**
(`tools/psyq/conv47/`, sha-recorded in `tools/psyq/CHECKSUMS.sha256`). Never assume one binary's SDK applies to
another — the 4.0 libs won't byte-match the resident's 4.7 objects.

## §12 Ultracode harvest — parallel-draft + byte-gate at scale (Phase 12, resident: 1.4%→71.7% in one session)

When a binary has **many independent small/medium functions** to hand-match (the resident: ~143 game-code fns,
the overlays later), fan the *drafting* out to a swarm of agents and let an **incorruptible byte-gate** filter —
a wrong match is structurally impossible to accept (G3/P9), so blind/semi-blind drafting is safe to mass-produce.
This drove REAL 1→102/145 (71.7% byte-identical) on the resident in one Ultracode session (5 passes). Reusable
verbatim for the Phase-13 overlays.

**The loop (each pass = a Workflow + a deterministic gate; loop-until-dry):**
1. **Draft (parallel, Workflow).** N agents (round-robin a size-sorted fn list into ~13–16 batches), each reads
   `asm/<bin>/nonmatchings/.../<fn>.s` + this cookbook + the already-matched fns (the style/extern conventions)
   and writes ONE self-contained `.c` per fn to `.run/drafts/<fn>.c` (externs + body) + a `.conf` (high/med/low).
   **No builds, no Ghidra** inside the draft pass (the asm IS the target; Ghidra contention flakes under fan-out).
   Distinct files per fn → no write races (no worktree isolation needed).
2. **Byte-gate (deterministic, `tools/harvest_verify.py`).** Substitutes each draft for its `INCLUDE_ASM` stub,
   `make build BINARY=<bin>`, keeps it ONLY if the image stays byte-identical, else reverts to the stub.
   Chunk-with-bisection (apply K, build; if the SHA holds keep all, else isolate one-at-a-time). The build is the
   sole arbiter — agent over-claims cost nothing. (`src/<bin>/*.c` is git-committed → always `git checkout`-able.)
3. **Loop (redraft passes).** Re-run the Workflow on the residual stubs, each agent seeded by its **prior failed
   draft(s)** + a **debugging checklist** (the high-yield miss-modes — see below). Gate again. Resident yield per
   pass: +62, +8, +9, +2.
4. **Iterate pass (the strongest — `tools/match_one.py`).** Gives each agent a *real per-function asm-differ loop*:
   compile ONE fn's C standalone (the pinned triple), mask relocations (jal/HI16/LO16, exactly `psyq_identify`'s
   mask), compare to the target bytes in its `.s` → `MATCH` or a per-instruction `idx | MINE | TARGET` diff. Fully
   isolated (own `.run/match/<fn>/` temp dir) → parallel-safe. Agents `write C → run match_one → read diff → fix`
   until MATCH. This cracks scheduling/regalloc near-misses blind drafting can't (resident +13 on the hard tail).

**Workflow resilience:** wrap the per-batch `agent()` in **retry waves** — a transient server 500/"rate limited"
returns null; re-run only the null batches up to 3× (`pending`/`okResults` pattern). One un-retried pass lost
10/14 agents to a server throttle; the retry-wave pass recovered all 13.

**Under a SUSTAINED server-side throttle, throttle the FAN-OUT, not just retry it — process in SEQUENTIAL
WAVES of ≤10 agents.** A big concurrent burst (40+ batches submitted at once) hammers the shared
`Server is temporarily limiting requests (not your usage limit)` rate limit, and even retry waves keep
failing because every wave re-bursts. Phase-15 T6 v3: a 48-batch burst harvest crawled at ~1 draft / 45 s
and finished with **33 dead batches**; re-run as `for (g of chunks(batches, 10)) await parallel(waveOf10)`
(with intra-wave retry), the SAME 375 targets drafted at **~42 drafts / 60 s, 0 dead batches**. Keeping
≤10 requests in flight stays under the per-window limit; sequential waves space the load so each window
resets between them. Pair with **leaf-first / easy-first ordering** so the early waves bank the high-yield
functions even if later waves get throttled. This is the rate-limit-gentle default for large harvests.

**MANDATORY GAP-FILL after every multi-agent run you expect to be complete (the retry-wave is NOT enough).**
Retry waves only re-run agents that returned `null`. But an `"API Error: Connection closed mid-response. The
response above may be incomplete."` failure returns a **truncated-but-non-null** result — the workflow reports
`dead_batches: 0` and a clean exit, yet that batch's agent silently wrote only SOME of its assigned drafts (or
none). The summary count looks fine; work is missing. So the gate alone would silently skip those functions
(a leftover stub is itself byte-identical — the byte-gate can't see an *un-attempted* target). **Always
reconcile the produced artifacts against the expected work-list before gating** (this generalizes to any
fan-out, not just harvests — diff produced-vs-expected whenever "expected complete"):
1. **Missing:** every manifest target with no draft file on disk.
2. **Truncated/malformed:** every present draft that is brace-imbalanced, has no function def, or doesn't close
   — a partial write. (These would fail the gate harmlessly, but re-drafting recovers them.)
3. **Re-draft the union** with a focused gap-fill agent (same prompt, the gap names), THEN gate the full set.
This is the byte-honest closure of "exhaustive" (P9/R14): the disk, not the workflow's success summary, is
ground truth. Phase-15 T6 v2: workflow reported 585 drafted / 0 dead after the retry-wave re-ran 2
connection-closed batches, but a produced-vs-manifest diff still found **6** un-drafted targets (individual
skips inside completed batches) — re-drafted before gating, none lost.

**Two TU-level gotchas (both bit, both have a fix):**
- **Inline scalar-typedef redefinition.** Agents told "self-contained" sometimes inline `typedef unsigned char
  u8;` — in a `.c` that already `#include`s `common.h`, gcc-2.7.2 (C89) errors on the dup → a *compile* fail, NOT
  a byte miss. `harvest_verify.py`/`match_one.py` STRIP `^\s*typedef\b.*\b(u8|u16|…|f64)\s*;` lines (common.h
  provides them). (Recovers false-failures: re-gate after the strip.)
- **`match_one` MATCH but whole-build FAIL = extern-type conflict.** `match_one` compiles standalone (one fn's
  externs); the real build is ONE TU (`resident.c`) where all fns coexist. A caller that declares a shared symbol
  to suit ITS call site (e.g. `extern s32 func_800D1714(void);` to drop an `andi v0,0xffff`) conflicts with that
  symbol's decl/def elsewhere (`u16`) → `conflicting types for …` → gate fails. Resident pass-4: 34 standalone
  MATCH → 13 whole-build (21 conflict casualties on ~25 shared symbols). **Fix: unify the extern types in the
  `.c`** — usually widen the *definition's* return type where byte-identical (`u16 f(){return u16g;}` ↔ `s32
  f(){…}` are the same `lhu;jr`), so all callers agree. NOT separate `.c` per fn: splat places the binary as ONE
  address-ordered object, so a second TU's `.o` isn't interleaved at the right vram.

**Honest tail (P9).** What survives the iterate pass is real compiler-internal residual — cross-jump tail-merge /
block-reorder / regalloc that no C-source shape steers (the agents document each in the draft header). Those go to
**decomp-permuter** (`tools/permuter/`) + the §3a/§5a/§10 research tier, or stay honest stubs — never forced.

**Idioms the swarm surfaced (fold the asm patterns into §1/§2/§10):**
- A "void-looking" dispatcher that ends in `jalr` with NO trailing `move v0,zero` but HAS `move v0,zero` in its
  early-return delay slots is actually **`s32`-returning with `return 0;` early-exits** and `return fp(...)` at the
  tail (the jalr's `v0` is the return) — declaring it `void` mis-schedules the constant.
- **Local = global** for a small fixed table: a `lw 0/4/8(base); sw …` prologue copying a 3-word global into a
  stack array is a **struct copy** (`Foo local = D_global;`), not element-wise assignment (forced when a runtime
  index makes gcc materialise the whole table on the stack).
- `*10` (and small-const multiplies) decompose as `(x<<1)+(x<<3)`, not `((x<<2)+x)<<1`; if a div/mul-by-const diffs
  by one shift/add arrangement, hand-write the explicit `x*2 + x*8` form.
- **Masked compare `andi` survives only if the value's range is unprovable.** `(a0 & 0xff) == k` keeps its `andi
  v1,a0,0xff` only when gcc can't prove `a0`'s range; a clean `u8` load lets gcc-2.7.2 prove `a0∈[0,255]` and DROP
  the andi (shifting the whole tail). An `(s8)`/`(u8)` cast on a wider load is the lever to restore-or-drop it.
- Callee **return type forces the cast at the call site**: `jal f; andi v0,0xffff` means `f` is declared returning
  a type WIDER than u16 (so the `(u16)` cast emits the `andi`); declaring `f` as `u16` lets gcc trust it and drop
  the andi.

## §13 Add a location overlay — the canonical runbook (Phase 13; the Phase-15 fleet recipe)

All ~134 location overlays are flat LZSS-decompressed `0.4.dec` payloads that stream into the SAME slot
**vram `0x80128158`** (position-locked, Phase 3) and chain into the resident engine. Each is its own build
binary `ov_<SCxx>_<nnn>`. The whole pipeline is one command + the §12 harvest; this is the reusable recipe.

### One-command onboarding — `tools/new_overlay.sh <SCxx> <FILE_nnn>`
Computes sha1 / size / `code_end` (from `sig_image.py --bootstrap`, the last function's end), instantiates
`config/splat.<ov>.yaml` from `config/splat.us.overlay.template.yaml`, writes `config/check.<ov>.sha` + an empty
`config/symbols.<ov>.txt`, appends the `<ov>_*` block to the **generated** `config/overlays.mk` (the Makefile
`-include`s it, so the hand-maintained Makefile body is NEVER edited) + the alias to `OVERLAY_BINARIES`,
sentinel-inserts the entry into the 4 report/diff dicts (`diff_settings.py`, `tools/{progress,difficulty,
dup_report}.py` — grep-guarded + `ast.parse` syntax-checked), then `make extract && make build` to byte-verify
at 100% INCLUDE_ASM. Idempotent (re-run = clean no-op). Proven on SC01/005, /006, SC03/001.

### The flat-blob overlay config (what the template encodes)
- No header, no `gp_value` (-G0), single `code` segment @ `vram 0x80128158`; `build_path: build`; per-binary
  nested `asm/<ov>` + `src/<ov>` + `build/<ov>`; `asset_path: assets/<ov>`; stacked symbols
  `[symbols.us.txt, symbols.resident.txt, symbols.<ov>.txt]` (overlays call the resident engine).
- **Overlays open with code at file 0x0** (a prologue), UNLIKE the resident's leading data word — first subseg
  `[0x0, c, <ov>]`, no leading-rodata trick. Subsegs: `[0x0, c]` + `[<code_end>, data, tail]`; `code_end` = the
  last sig_image function's end (file offset). Byte-match is robust to the exact split (splat round-trips bytes).

### THE NON-4-ALIGNED-OVERLAY GOTCHA (≈75% of the fleet; fixed in the template + Makefile, automatic)
A `0.4.dec` whose size isn't a multiple of 4 (SC01/077 = 0xB29D7, mod 4 = 3) loses its final 1–3 bytes three ways:
1. **spimdisasm drops the trailing partial word** (won't emit < 4 leftover bytes; a `data` carve of those emits
   *nothing*). → Carve them as a **`bin`** subseg `[<word_floor>, bin, trailing]` (raw `.incbin`). `new_overlay.sh`
   injects this when `size % 4 != 0`.
2. **splat's `bin` asset needs a build rule** — `.ld` references `build/assets/<ov>/trailing.o`. The Makefile
   `build/assets/%.o: assets/%.bin` rule assembles a one-line `.incbin` stub **+ `objcopy --set-section-alignment
   .data=1`** (else `as` defaults `.data` to 16-align → ld pads the image, adds a stray byte).
3. **splat's `.ld` does `. = ALIGN(., 4)` at the segment end** → up to 3 zero pad bytes. The Makefile objcopy
   step **TRIMs** it: shrink-only, capped at 3 bytes, gated on `size(build) > size($(EXE)) && delta ≤ 3` — can
   never hide a shortfall or touch the 4-aligned EXE/resident (which never hit any of this).

### The A→B→C per-overlay workflow
- **A. Onboard + all-asm byte-match** (`new_overlay.sh`) → `make check BINARY=<ov>` byte-identical. *The milestone
  bar* (splat round-trips bytes regardless of carve quality).
- **B. Seed boundaries + Ghidra import** (to draft harder fns): splat carves ~all functions itself (SC01/077:
  2504 cleanly), so seeding `symbols.<ov>.txt` only fixes conservative carves (§8/§11) + attaches names — the
  byte-match doesn't depend on it. Ghidra: `ghidra_import_raw.sh <0.4.dec> 0x80128158 <ov>` (MCP stopped, R23) +
  `DefineFunctions.java` over splat's func list (auto-analysis finds only the `jal`-reachable subset — overlays
  dispatch via fn-pointer tables; SC01/077: 1237 → 2661). The overlay Ghidra DB is **script-reproducible** →
  DB-commit optional (skip to avoid ~14 MB bloat unless doing manual RE). Restarting MCP to serve `<ov>` drops
  the client SSE → pause + ask Drew to run `/mcp` (memory `mcp-reconnect-after-restart`).
- **C. Dedup-credit FIRST, then the §12 harvest.** Credit the high-leverage shared engine functions (top
  `docs/duplicates.cross.md` groups — byte-identical at fixed vrams in all 134 overlays) so they leave the
  queue; then `difficulty.py --binary <ov>` ranks the unique remainder for the §12 parallel-draft + byte-gate.
  **Use Ultracode** (T7 evidence: xHigh agents = Max-agent yield on blind drafting — no reason to spend Max
  depth; see `docs/effort-map.md`). SC01/077: 704 matched (yield 92%→79%→54% as difficulty rose; the hard tail
  → permuter/§3a or honest stubs).

### Dedup-credit (§11) for overlays — two shapes
- **Per-function share (general/fleet shape):** a matched body lives once as a macro in `src/shared/<h>.h`,
  instantiated **in place** (preserve address order — overlays link functions in source order!) at each member
  site, registered in `config/dedup.us.yaml` (members in >1 binary), byte-gated by `dedup_integrate --check` (the
  recorded `h_exact` must equal each member's `sig_image` hash, keyed by addr-int — sig_image names lowercase,
  splat uppercase, validator case-moot). The nested overlay `.c` resolves quoted includes relative to ITS dir →
  use `#include "../shared/<h>.h"`. Proven: SC01/005 ≡ 006 share 3 accessors from `src/shared/ov_setters.h`
  (`SETTER`/`RETCONST`), both byte-identical from one source. `progress.py` credits shared members as REAL.
- **Whole-overlay collapse (special case for byte-identical pairs):** for two overlays with the SAME `0.4.dec`
  sha1, `src/ov_B/ov_B.c` can `#include "../ov_A/ov_A.c"` — B inherits ALL of A's matches from one source.
  Maximal but doesn't generalize to partial sharing, so the per-function share is the fleet default.

### Fleet build — `make build-all` / `make check-all`
Recursive `$(MAKE) BINARY=<b>` over `$(BINARIES)` (NOT `foreach` — the OBJS glob is parse-time per `$(BINARY)`),
one PASS/FAIL + per-binary `.run/check.<b>.log`. Serial across binaries (shared `build/asm|src/**` outputs make
binary-level `-j` racy). Day-to-day incremental; milestone fleet proof = a CLEAN run (R22): `make clean && for b
in $(BINARIES); do make extract BINARY=$$b; done && make check-all`.

## §14 Propagate a matched function across the fleet — `tools/dedup_propagate.py` (Phase 15)

**The economics that drives Phase 15.** Overlays are position-locked at `0x80128158`, so a shared engine
function has the SAME vaddr (hence the SAME `func_<ADDR>` symbol) and a BYTE-IDENTICAL body in every overlay
that contains it. Measured on the fleet: **577 of `ov_SC01_077`'s 785 matched functions are `h_exact`-identical
across ALL 134 overlays** (~2.19 MB collapsible) — already matched, just needing propagation. So the rule is
**match once → propagate, do NOT re-harvest each overlay.** (`tools/dedup_propagate.py --auto-from ov_SC01_077`
enumerates exactly this set: matched-as-an-inline-def in the source AND `h_exact`-shared across ≥`--min-reach`.)

**The tool.** `tools/dedup_propagate.py --addr 0x..[,..] --source-overlay <ov>` (or `--auto-from <ov>` for the
whole shared set; `--check-only` for a dry-run plan):
1. extract the matched body (preceding `extern`s + the def, brace-matched) from the source overlay's `.c`;
2. author it ONCE as a tool-generated `#define DEFINE_func_<ADDR>() \`-continued macro in `src/shared/engine_core.h`
   (idempotent; **refuses `//` line comments** — they break line-splicing; block `/* */` is fine);
3. at every onboarded overlay whose sig shows that `h_exact` (lead with `h_exact` — guaranteed byte-identity),
   replace that function's `INCLUDE_ASM` stub (or, in the source overlay, its inline def) **in place** with
   `DEFINE_func_<ADDR>()` — address order preserved; `#include "../shared/engine_core.h"` added once after
   `common.h`;
4. **byte-gate** each touched overlay (`make build BINARY=<ov>` == its `check.sha`); on ANY miss, restore EVERY
   file from an in-memory snapshot and abort (fail-closed; nothing wrong lands);
5. register the group in `config/dedup.us.yaml`, validated by `dedup_integrate --check`.

**Key gotchas (each cost a real bug or false pass during the Phase-15 proof):**
- **Key by addr-int, never the string.** `sig_image` writes lowercase hex (`0x80144b9c`); splat's symbol is
  uppercase (`func_80144B9C`). Compare `int(addr,16)`; render the symbol as `func_%08X`.
- **Accumulate edits from the on-disk text, not a snapshot cache.** When a batch propagates several functions into
  the same overlay, re-read the file before each edit (the snapshot dict holds the ORIGINAL for restore, not the
  running state) — else each function's edit clobbers the previous and only the last lands.
- **The byte-gate can't catch under-application.** A leftover `INCLUDE_ASM` stub is itself byte-identical (it just
  uses the asm), so `make check` passes even if a function wasn't actually converted. Add a STRUCTURAL self-check:
  after editing, assert each member's `.c` contains `DEFINE_func_<ADDR>()` and NO leftover stub line.
- **Header-dependency tracking is mandatory once shared headers are build inputs (R22).** The Makefile C rule
  originally made `build/src/%.o` depend only on the `.c`, so editing `engine_core.h`/`common.h` did NOT trigger a
  recompile → an incremental `make check` after a header-only edit was STALE (a wrong shared body falsely passed).
  Fixed: the `cpp` stage now emits a `.d` (`-MMD -MP -MT $@ -MF $(@:.o=.d)`) and the Makefile `-include`s
  `$(C_SRCS:%.c=build/%.d)`. Side-effect only — output bytes unchanged. With it, the negative test (corrupt a
  macro body → `make check` rebuilds via the `.d` → SHA mismatch → fail) behaves correctly.
- **Idempotent + resumable.** A propagated source function becomes a `DEFINE_…` macro (no longer an inline def), so
  `--auto-from` re-runs skip the done ones; `--addr` re-runs no-op (source is now a macro, plan is empty).
- **Scale note (deferred until it bites):** `dedup.us.yaml` members are listed verbose (`{binary,vram,name}`).
  For the full 134-overlay × hundreds-of-functions bulk, switch to a `vram + binaries:[...]` shorthand (expanded by
  `dedup_integrate`/`progress.py`) before it becomes a 5-figure-line file.

### §14a The fleet bulk run (Phase 15 — `--auto-from`, 947 REAL → 74,527; 3.82% → 22.14% in one pass)

A measured **577 of `ov_SC01_077`'s matches are h_exact across all 134 overlays**; `dedup_propagate --auto-from
ov_SC01_077` propagated **553** of them fleet-wide (each overlay byte-gated) in ~2 min. The 5 things that made
the bulk work (each cost a real failure first):
- **Only self-contained bodies are mechanically liftable.** A 077 match whose body names an overlay-LOCAL struct
  type (`SrcB964 *a0` — a harvest-invented type defined in 077.c, not common.h) compiles in 077 but FAILS in
  every other overlay (`parse error before '*'`, `a0 undeclared`). The first bulk attempt died on one and
  reverted all 134 (fail-closed, correct but wasteful). Fix: a **compile pre-filter** — `compiles_standalone(body)`
  builds the body with `common.h` only (cpp→cc1); skip if it fails. 9/562 were local-typed → skipped honestly (P9).
  These need their types shared too (a future enhancement); they are NOT a byte regression, just deferred.
- **The registry shorthand is mandatory at this scale.** 553 groups × ~134 members verbose ≈ 77k lines; the
  `vram + binaries:[...]` shorthand keeps `dedup.us.yaml` at ~4k. `group_members()` (in `dedup_integrate`) is the
  single expander used by `dedup_integrate --check` and `progress.py`.
- **Per-overlay apply, not per-(function,overlay).** Group targets by overlay → one read/write per file; stub
  lines replace 1:1 (no shift); the source overlay's inline defs splice by range in REVERSE line order. (Naive
  per-pair editing is 77k file-ops and minutes slower.)
- **Skip already-registered + gate-only-changed.** `--auto-from` excludes addrs already in the registry (additive,
  resumable, never collides with an existing SETTER/engine_core share); only overlays that actually changed are
  rebuilt. Re-running tops up as more overlays onboard.
- **`progress.py --fleet` parse cache.** `dedup_members` parsed the (now-large) registry once per binary (136×) —
  cache it once (`_DEDUP_CACHE`): fleet report 6m+ → ~7s.

### §14b Harvesting the UNMATCHED shared core — the match_one wall (Phase 15)

After the bulk (already-matched) propagation, the remaining shared functions are the **hard residual** the
original per-overlay harvest already failed on. A 25-agent Ultracode pass (§12) drafted + `match_one`-verified
300 of the smallest unmatched-shared functions (8–16 ins); the whole-binary byte-gate (`harvest_verify` in
`ov_SC01_077`) verified **only 49 (16%)** despite 292 agent-claimed "high". The gap is structural, not agent error:
- **`match_one` masks relocations (jal 26-bit, HI16/LO16), so it CANNOT verify call/data targets.** A draft that
  calls the wrong function — or the right function with the wrong extern signature — still prints `MATCH`. It is a
  true gate only for **leaf** functions (no calls, no global refs). The 49 that passed were essentially the leaves.
- **The real misses are the extern-type-conflict wall** (§12's gotcha, now the dominant failure): a wrapper
  `func_A` calls `func_B`; the draft declares `extern void func_B(s32)`, but `func_B` is already defined IN THE SAME
  TU (an `engine_core.h` macro from the bulk, or an inline def) with a different signature → `conflicting types` →
  compile fail → the byte-gate reverts it. `match_one` (standalone, no other defs) never sees the conflict.
- **Implications for future passes (the open-ended tail):** (1) **leaf-first** — filter targets to functions whose
  `.s` has no `jal`/`%hi`/`%lo` for a high-yield pass; (2) **callee-signature-aware drafting** — when a draft calls
  `func_X` that's already C-defined (grep `engine_core.h` / the overlay `.c`), it must reuse `func_X`'s EXACT
  signature; a STUB callee (still `INCLUDE_ASM`) takes any consistent extern (asm provides the symbol, no conflict);
  (3) a real per-function gate would need to **link** (resolve relocations), i.e. the whole-binary `harvest_verify`,
  not the masked `match_one`; (4) the call-heavy residual is genuine decomp-permuter / hand-iteration work — the
  open-ended Phase 15 continuation, not a milestone gate.

### §14c Callee-signature-aware harvest — breaking the extern-type-conflict wall (Phase 15, T6)

§14b named the wall; this is how it falls. The call-heavy shared residual fails the whole-binary
byte-gate (NOT `match_one`, which compiles standalone and masks `jal`) because a draft declares a
callee or data symbol with a type that **conflicts** with that symbol's canonical declaration
elsewhere in the single overlay TU (an `engine_core.h` DEFINE macro, another banked function's
inline extern). The fix is to stop letting agents guess: pre-resolve every callee's EXACT signature
deterministically and hand it to the agent to reuse verbatim.

**`tools/gen_harvest_targets.py`** builds the callee-sig-aware target manifest (`.run/t6_*.json`).
For each still-`INCLUDE_ASM` shared function it records `{name, addr, nins, reach, callees:[{sym,
status, signature}]}`, resolving each callee three ways (priority order):
1. **defined** — a body exists: `engine_core.h` `DEFINE_func_X` macro body, or an inline def in the
   overlay `.c`. The signature is authoritative; the draft MUST reuse it verbatim.
2. **declared** — no body, but the symbol is already `extern`-declared somewhere (another macro/draft).
   That extern is authoritative too (a stub callee with an established signature — reuse it).
3. **stub / extern** — undeclared (a bare overlay stub, or a resident/EXE symbol). The agent infers a
   minimal consistent extern from the `.s` arg-setup; resident/EXE callees are conflict-free (not
   defined in this TU).

Result on the small band (nins 8-30, 616 fns): **855/1019 callees resolved to exact sigs**, and the
whole-binary gate yield jumped **16% → 60-67%**. The agents draft callee-sig-aware C (reuse exact sigs
for defined/declared callees; infer for stubs), self-check with `match_one`, and the whole-binary
`harvest_verify` is the sole arbiter (`match_one` cannot see TU-level conflicts).

**The four conflict flavors (all real this phase):**
- (a) **defined-callee return/param mismatch** — draft guessed `s32`/wrong params; canonical body says
  otherwise. (`func_8012A100` is `void f(s8)`, not `(s32)`.) → reuse the resolved sig.
- (b) **declared-stub-callee** — a still-`INCLUDE_ASM` callee already extern-declared `int func_X(int,
  int,int)` by other macros; a draft declaring it `void` conflicts. (`func_80150BA4`→`func_80151184`.)
  → harvest the extern declarations too, reuse them.
- (c) **DATA-symbol type conflict** — the dominant residual after (a)/(b): `D_XXXX` globals declared
  with different types by different drafts (`u8 D[]` array vs `s32 D` scalar) → `conflicting types`.
  The manifest resolves FUNCTION sigs but not yet DATA-symbol types; this is the next yield-limiter.
  Structural fix for a future pass: a single canonical decls header (all data symbols as `extern u8
  D_X[];` byte-arrays, used via explicit casts) that the overlay `.c` includes and drafts never
  redeclare → zero possible conflict.
- (d) **narrow-return-widening** — a callee defined returning a NARROW type (`s8/s16/u8/u16`, body
  `return <load>`) forces a `sll/sra` (or `andi`) sign/zero-extension at EVERY call site; if the target
  asm lacks it, the original declared that function `int`/`s32`. Widen the DEFINITION's return type to
  `s32`/`u32` — byte-identical because the body's `lb/lbu/lh/lhu` already extends to 32 bits — and all
  call sites match. (`func_8017AE08`→`func_80174764`.)

**Operational gotcha (cost real work):** NEVER `git checkout src/<overlay>.c` during an active harvest.
It silently reverts banked matches while the propagation artifacts (`engine_core.h` macros, other
overlays' `DEFINE_func_X()` instantiations, `dedup.us.yaml` groups) survive — an inconsistent (though
byte-recoverable: the next gate re-verifies) state. Use a `.run/_bak.c` copy for diagnostic
substitute/build/revert, never `git checkout`.

**Resilient incremental loop (proven under server-side API rate limiting):** the draft Workflow is the
only rate-limited part. Gate whatever drafts have landed (`harvest_verify`), `dedup_propagate
--auto-from` (deterministic, immune to throttling), `make report`, repeat as more land. Quarantine
gate-failures to `.run/drafts-<x>-fail/` after each round so re-gates stay fast. Partial harvests bank
cleanly; the residual resumes next pass (loop-until-dry). T6 banked 123 fns / +4.6% fleet this way with
the Workflow only ~40% through its batches.

### §14d Deterministic recovery beats agent waves on the hard tail (Phase 15, the final-session finding)

Once the EASY shared core is banked, the residual is permuter-class and **agent harvesting is poor ROI**: a
50-agent Ultracode wave on 300 hard-tail stubs verified only **27 (~9%) for ~4.1M tokens (+0.36% fleet)**, while
a **deterministic recovery pass added +2.67% for ~0 agent tokens** the same session. **Reach for these BEFORE
mass-drafting the hard tail** (this is a cost rule, codified in `docs/effort-map.md`):

- **`tools/sig_unify.py` — unify the draft's OWN definition signature, not just callee externs.** The dominant
  hard-tail gate failure is a TU-level **signature conflict** on a draft whose body is already byte-correct
  (it passes `match_one`). A probe is the tell: substitute each gate-failing standalone-MATCH draft alone, build,
  and classify the error — **30/30 sampled were `conflicting types`, 0 false-positives (built-but-SHA-diff)** →
  they are byte-correct C blocked only by declaration unification. `canon_draft_decls` rewrites *callee* externs
  but never the **function's own def signature** (defined `void`/`s16` here, extern-declared `s32` by banked
  callers) — `sig_unify` adds that (canonical return + param types, draft's param names kept; arity-mismatch →
  return-only fallback). The byte-gate stays the arbiter. **191 conflict-blocked → 32 recovered** deterministically.
- **The silent-under-propagation class (`find_site` brace bug).** A GREEN byte-gate proves *what landed is
  correct*; it does NOT prove *everything that should have propagated did*. `dedup_propagate`'s inline-def
  detector required the opening brace **on the same line** as the signature, so every **next-line-brace** def
  (which `sig_unify`/permuter emit) was silently skipped from propagation — a whole session's matches capped
  invisibly. **Always sanity-check the OUTCOME metric** (`make report` fleet %, or `--auto-from --check-only`
  plan size), not just the gate. Fix: `find_site` accepts brace on the same OR the next non-blank line. (One fix
  unlocked a 61-function backlog.) Generalizes: any "match→register" detector must accept all draft formats.
- **`build_engine_types.py` must be ADDITIVE.** A 2nd `--strip` run regenerating the shared types header from the
  source's *current* inline defs DROPS the already-migrated types (they were stripped last run) → build breaks.
  Merge with the existing header; the header is the cumulative record.
- **Probe-before-investing.** Size every recovery lever on a ~20–30 sample (build-classify the failures) before
  building the full pass — it told us sig_unify was worth it (30/30 conflicts) AND that the *next* tier was a
  dead-end (below) before we spent on it.

### §14e Two hard-tail dead-ends (Phase 15 — documented so they aren't re-attempted)

- **`()` no-prototype externs DON'T resolve arity/param conflicts here.** The textbook PS1-decomp escape (declare
  inter-function externs param-less) FAILS under gcc-2.7.2: *"An argument type that has a default promotion can't
  match an empty parameter name list declaration"* — C forbids `()` matching a prototype with a default-promotion
  param (`s8/s16/u8/u16/float`), which these engine fns have. The remaining ~159 arity conflicts (def needs N
  params, callers declare M) have **no clean deterministic fix**.
- **m2c/Ghidra output is a scaffold, NOT byte-matching C — the struct is the wall.** On the remaining shared band,
  **20/20 sampled m2c outputs are struct-heavy** (`arg0->unkXXX` inferred field accesses) and **won't compile**
  without the engine struct defined, plus `?`-typed values. A decompiler gives structure + offsets for free; it
  does not give the struct definition or the byte-match. **The path forward (Phase 16):** infer the one engine
  **actor struct** layout from the union of m2c field-accesses (offsets + widths) → feed as m2c `--context` →
  compilable C → `sig_unify` → **decomp-permuter** brute-force (compute-bound, low-token — the "set-it-and-go"
  pipeline). Validate on a 10-fn medium sample before scaling.

## §15 Struct-heavy shared-core pipeline (Phase 16) — empirical determinations (S0)

Established by **running m2c on real `ov_SC01_077` stubs** (R14) — it corrects §14e's framing on two key points and the corrections are favorable.

**(1) m2c output COMPILES via `tools/m2c/m2c_macros.h` — the struct is NOT a hard compile prerequisite.**
`--valid-syntax` emits `M2C_FIELD(p, type, off)` ≡ `*(type)((s8 *)p + off)` (defined in `m2c_macros.h`) — a **byte-faithful cast** (same `lw/sw/lh/sh` as `p->field`). §14e's "won't compile without the struct" was *without m2c_macros.h*. **30/30 sampled m2c-targets use only byte-faithful macros** (`M2C_FIELD`/`M2C_BITWISE`/`M2C_UNK`) → they compile. The **non-faithful** macros — `M2C_ERROR/M2C_BREAK/MULT_HI/MULTU_HI/CLZ/GLUE_F64/BSWAP/M2C_TRAP` — emit `(0)` (discard the real op) → a function using any of them **cannot byte-match** (GTE/handwritten/special). **Their presence = "defer, not m2c-matchable."**

**(2) Compiling ≠ byte-matching; the residual is regalloc/scheduling → decomp-permuter is the byte-closer (essential, not optional).** Pure-leaf example `func_8012CB64`: macro-compiled output = 16/16 ins, identical control flow, only `v0↔v1` regalloc + a trailing `move`/`nop`. That is permuter-class. Some functions m2c gets *structurally* wrong (e.g. 8 vs 18 ins) → permuter cannot fix → struct types / hand / defer.

**The byte-match path:** `m2c --valid-syntax` (+ macros + context) → `sig_unify` → **decomp-permuter** (regalloc/schedule) → `harvest_verify` whole-binary byte-gate → `dedup_propagate`. **Struct types (`struct_infer`, S1) are an ENHANCER** — readability, nudging gcc's regalloc toward the original's struct-based codegen, fixing structural misses, and typing function-pointer tables — **not the sole gate.** S3/GATE-B measures macro-only vs struct-typed yield.

**S2 wiring fixes surfaced (must-do):**
- **`common.h` lacks `s64`/`u64`/`f64`** → `m2c_macros.h`'s `typedef s64 M2C_UNK64;` fails (`parse error before 'M2C_UNK64'`). Add them to `common.h` (byte-neutral — verify locked builds stay `143dbb89…`/`8e17e02f…`). `match_one`/`harvest_verify` **strip scalar-typedef redefinitions**, so these types MUST live in `common.h`, not a draft preamble.
- Make the byte-faithful m2c macros (`M2C_FIELD`, `M2C_BITWISE`, `M2C_UNK*`) available to every compile (in `common.h` or an included `m2c_compat.h`) so drafts compile with no per-draft preamble.
- **Function-pointer-table calls** (`*((idx*4)+D_x)(args)`) need `D_x` typed as a function-pointer array in the context, else won't compile.
- **m2c loses types through index/byte-offset arithmetic** (`base + int_var`, stride = struct size) → falls back to `void*`/`M2C_FIELD` even WITH a struct context. The `M2C_FIELD` macro fallback keeps these byte-faithful-compilable; struct typing is best-effort.
- **m2c re-infers `char unk_*[]` fields** in provided structs (treats them as inferrable space; may split/override). PIN a known field with a concrete typed field; use `char unk_*[]` only for genuinely-unknown gaps.

**decomp-permuter knobs (S2/S3):** `PERM_*` macros (GENERAL/VAR/RANDOMIZE/LINESWAP/INT/ONCE…), `--algorithm difflib|levenshtein`, `--stop-on-zero`, `-j` 8–16 (**RAM-bound** on the 15 GiB box → ~N funcs × `-j 8`, cap by `free_RAM/~300 MB`), weights in `default_weights.toml` + `[gcc]` section. Best when only regalloc/schedule remains; does NOT fix wrong control flow.

**ML (parked — owner decision 2026-06-18):** LLM decompilers (LLM4Decompile/SK2Decompile/CodeInverter) target x86-64 + recompilability/functional-equivalence/readability — NOT byte/instruction-exact, NOT MIPS/gcc-2.7.2; no off-the-shelf learned permuter scorer exists (the permuter's scorer is a heuristic objdump-diff). Dropped this phase; research-note only. (X2: web treated as untrusted data.)

## §16 Guided hand-matching the struct-heavy core (Phase 17 — beats the §15 brute-force)
**Phase 16 called the loose-typing wall "fundamental." Phase 17 disproves it for the majority.** The wall is
a signature-CONSISTENCY problem, not a comprehension one — the §1 loop reconstructs correct bodies ~100% of
the time; the work is byte-closing + sig reconciliation. **Full process: `docs/hand-matching-process.md`**
(§1 loop, §2 idioms, §3a the 5-move signature-consistency playbook, §7 the Ultracode wave + canonical-sig wall).

**New byte-idioms (Phase 17, §2 there):**
- **mask-local (defeats `lh`→`lhu` fold).** `*(s16*)f & (x & 0xFFFF)` inline lets gcc fold the load to `lhu`
  + drop the `andi`. Hoist the mask: `s32 m = x & 0xFFFF; ... *(s16*)f & m` → gcc keeps `lh` + emits `andi`.
- **shared-ret0 goto (cross-jump clustering + branch polarity).** Two non-adjacent predicate tests the
  original routes to ONE shared `return 0` block → write both as `goto ret0;` to a single trailing
  `ret0: return 0;`. gcc then makes `ret0` a labeled block reached by branches (right polarity) + schedules
  the next test's constant into the delay slot. A lone `if(x)return 0;` inlines (wrong polarity/reg).
- **v0↔v1 result/constant coalescing** + the §10 hoist-vs-remat / phantom-frame quirks = the residual hard
  tail — **NOT a dead-end: §17 (CORRECTED) shows the call-crossing register-ORDER class is matchable with
  `register __asm__` PINS + a scheduling barrier (byte-proven, func_8012B8E4), and array-decay cracks the
  hoist-vs-remat class.** Hand-tier, but matchable. (Permuter can't help — it rejects `register __asm__`.)

**Scaling = Ultracode wave (§12 pattern + §7):** Ghidra pre-pass (`DecompileFunctions.java`, headless batch,
no /mcp) → parallel draft agents (m2c+Ghidra-C+asm+actor-struct+§3a, self-validate `match_one`) → whole-binary
gate (`harvest_verify --chunk 1`) → `sig_unify` recover → `dedup_propagate --auto-from`. Calibration (top-30):
60% match_one MATCH, **33% whole-binary** (+0.47% fleet), 136/136.
**THE CANONICAL-SIG LAYER (built Phase-17 session-4; NOT the ~2× lever it first looked like).** The
match_one→whole-binary gap on the calibration's *top-30* was SIG CONFLICTS (parallel agents declare shared
callees inconsistently → `conflicting types` in the one-big-TU; 100% compile-errors, 0 codegen). Fix = a
SURGICAL per-callee canonical-sig layer: `tools/census_conflict_callees.py` (the conflict predicate:
undeclared-stub callee with `decl_sources = n_callers + is_target >= 2`) + `tools/derive_canonical_sigs.py`
(byte-neutral `s32 func_X(s32...)`, arity from Ghidra-C + asm read-before-write `$a0-$a3`) → a 20-extern
block at the TOP of `ov_SC01_077.c` (LOCAL, not engine_core.h — reach-1 names differ across overlays). *(Both `census_conflict_callees.py` and `derive_canonical_sigs.py` were **DELETED in Phase 26-A** — R33; the fleet-canonical-sig approach was superseded by `reconcile_tu`'s per-TU oracle. Historical record.)*
`gen_harvest_targets` + `sig_unify` auto-read it; **the gate pipeline is now draft → `sig_unify` (MANDATORY)
→ `harvest_verify --chunk 1`** (the accumulating baseline now carries the file-top block, so a raw draft's
guessed extern would clash without sig_unify). **SIZING CORRECTION (R14):** for the *remaining 270*, the
conflict wall is only **20 callees / 24 targets / 7% of wave reach** — the "~2×" was the top-30's in-flight
conflicts, since resolved by banking. **The real wall is the gcc-quirk tail, not sig conflicts** — the 4
highest-reach circular targets are ALL §10-hoist / regalloc / layout-bound (0 closed by hand or permuter).
The layer makes a wave *sig-clean*; it does NOT unlock the quirk tail. **→ The match-% lever is understanding
gcc-2.7.2 (R17 compiler-source research, Phase 18), not more brute waves.** Wave deferred; infra staged
(`.run/harvest_wave_s4.js`, 40 tractable reach-134 targets). See `docs/hand-matching-process.md` §8.
**§17 (CORRECTED) answers it: the call-crossing register-ORDER class IS matchable — with `register __asm__`
pins + a scheduling barrier (byte-proven). The "brute waves won't help" point stands; HAND levers (pins) do.**

## §17 The compiler-quirk wall — the matching TOOLKIT (Phase 18; gcc-2.7.2 source + byte-gated)
Phase 18 read the real gcc-2.7.2 source (`tools/reference/gcc-papermario`, SETUP §5.6) + mined Xenogears (our
EXACT compiler). **Verdict (CORRECTED — an earlier draft of this section wrongly called the register-order
class "unsteerable"; it is NOT): every quirk class met so far is matchable from C — the register-order tail
needs `register __asm__` PINS, which I'd skipped. The wall was a missing lever, not an impossibility.** Triage
each residual with `match_one` (the floor-free oracle — NEVER the permuter score on jtbl/rodata fns, §10), then
pick the tool. R14 caveat: don't conclude "unsteerable" until you've tried the PINS.

### Register-allocation ORDER (call-crossing $s0/$s1 swap) → FORCE it with register pins (byte-proven)
*Mechanism (why the swap happens):* two pseudos live across a call → both are **global** allocnos (NOT
local-alloc) competing for callee-saved $s0/$s1; `global.c:allocno_compare` sorts by density
`floor_log2(n_refs)*n_refs/live_length` so the short-lived value wins $s0 and the whole-function value gets $s1
— often the reverse of the original. Clean-C reshapes / flags / cc1-swaps do NOT flip it (all tested).
**The lever (DON'T skip this): pin each call-crossing value to the register the TARGET uses** —
```c
register s32 d     __asm__("$16");   /* $s0 */   register s32 s1ang __asm__("$17");   /* $s1 */
```
gcc honors the pin and forces the allocation. Read the target `.s`, map each call-surviving value → its
callee-saved reg ($s0=$16, $s1=$17, $s2=$18 …), pin it. Then the residue is usually small: fix it with the
**branch-polarity invert** (§3-T4), **explicit temps** for any reassociation (`t = u6+0x1000; iVar4 = u5-t;`),
and a **scheduling barrier** for a last stuck instruction (`__asm__ __volatile__("" : : "r"(u5));` emits zero
code, anchors `u5` ahead of the next op). **WORKED EXAMPLE — func_8012B8E4** (the flagship "unsteerable" fn):
21 → MATCH via pins + branch-polarity (24→21) + clamp temps (7→3) + the u5 barrier (3→MATCH); byte-gated +
propagated ×134. NOTE the permuter can't help here — pycparser rejects `register __asm__`/`__asm__` (§5a), so
this residue is a HAND lever, not a permuter job. Labor: ~5-10 min/fn, but each circular fn is reach-134 → ×134.
*(Xenogears ships this class as INCLUDE_ASM only because they hadn't found the pin lever — not because it's
impossible. We did.)*

### The STEERABLE idioms (byte-confirmed this phase)
- **array-decay forces rematerialization (NEW).** A stack buffer passed to a callee as `&struct` / `mtx.w` /
  `*(T*)arr` (any address-taken form) is HOISTED into a callee-saved reg (needs an extra callee-saved → bigger
  frame, more spills). Declare it a local **array** `T buf[N]` and pass it as `buf` (array-decay, never
  address-taken) → gcc **rematerializes** `addiu $reg,$sp,off` per call instead (matches the original, frees
  the reg). func_8012B4B8: 88→52 (the hard regalloc+remat half fixed). CAVEAT: an array can't take a struct
  block-copy (`arr = STRUCT` needs a struct; element-copy constant-folds each global addr to its own `lui`,
  +ins), so a fn that ALSO needs a load-base-once struct-copy has an unavoidable tension.
- **for-loop vs do-while controls delay-slot scheduling.** A counted scan as a `for` (init/cond/update) lets
  gcc schedule the branch-taken return value into the loop test's delay slot; a `do-while` with increments in
  the body fills that slot with an increment instead (+1 ins, wrong schedule). func_801399A8: do-while 7
  mismatch → for-loop 2 → MATCH.
- **statement order in the for-update = instruction order (§2-T2 extended).** Independent updates in
  `for(...; ...; A, B)` emit in source order; swap to match. (func_801399A8 final 2.)
- (existing, reconfirmed) **§3-T4 branch-polarity invert** (func_8012B8E4 24→21), **§16 mask-local**,
  **§16 shared-ret0 goto**.

### The pipeline gotcha — match_one ≠ the gate; `sig_unify` is MANDATORY
`match_one` masks relocations → it MATCHES even when the draft's own def-signature or a data-extern TYPE
conflicts with the canonical decl in `engine_core.h` (`u8 *func(void)` vs canonical `s32 func(void)`;
`extern u8 D_x` vs `extern s32 D_x`). The whole-binary gate then fails `conflicting types`. ALWAYS retype the
draft to the canonical set (return + data-extern types; use integer address arithmetic `(s32)&sym`,
codegen-neutral): **draft → `sig_unify`/canonical-retype → `harvest_verify`.**

### The LOOSE-TYPING wall is real for narrow params (Phase 16, reconfirmed)
Some STRUCTURAL_MISS fns are blocked by it: func_80146A6C needs an incoming arg as `lhu` (s16), but the shared
canonical sig declares it `s32` (→ `lw`); the byte-match needs s16, another call site needs s32, no single C
type satisfies both. No clean fix (the documented narrow-param dead-end). **Stub it.** *(Reconciles §16's
"Phase 17 disproves the loose-typing wall": disproven for pure-structure fns like func_801399A8; REAL for
narrow-param fns like func_80146A6C and inseparable from the regalloc tail.)*

### Strategic conclusion — the match-% lever post-research
The high-reach **circular regalloc-order tail IS matchable** — by register pins + barriers (above), labor-
intensive but ×134 per match. So the lever is BOTH: (a) the **non-walled STRUCTURAL_MISS fns** (clean
reconstruction + the structural idioms + mandatory sig_unify — proven on func_801399A8), the cheap bulk; and
(b) the **circular tail hand-matched with pins** (proven on func_8012B8E4), the high-value-per-fn work. Triage
each with `match_one`: pure structure → reconstruct; stack-buffer-to-callee → array-decay; call-crossing
register swap → PINS; last-instruction schedule → barrier. The ONLY genuine dead-end left is the **narrow-param
loose-typing conflict** (func_80146A6C: an arg that must be s16 here and s32 at another call site — no single C
type) → stub THAT and move on; everything else is matchable with enough hand effort.

### §17a The TOOLKIT at WAVE scale (Phase-18 Step-3b/Step-1 — measured) + the pipeline-integration gotchas
The §17 toolkit was taught to a parallel Ultracode harvest wave (agent prompt = the triage above + the two
worked-example templates). Measured on ov_SC01_077 tractable reach-134 residuals:
- **Step-3b calibration (16 targets, prompt v1):** `match_one` 12/16, **whole-binary 9/16 = 56%** close-rate
  (vs the Phase-17 prompt's 33%). The pins/array-decay moves landed real matches the old "stub the quirk" prompt
  would have lost.
- **Step-1 (31 targets, prompt v2 = +embedded canonical callee sigs +call-site-cast/re-validate):** `match_one`
  **28/31 = 90%**, whole-binary **22 verified**. The big lift was **embedding each callee's canonical signature
  per target** (from `gen_harvest_targets.py`) so agents declare callees right instead of guessing.

**THE match_one→gate GAP is mostly DECLARATION plumbing, not codegen** (so it's cheap to recover):
1. **Call-site casts, NOT redeclaration (the #1 recurring miss).** `match_one` masks jal/%hi/%lo, so a draft
   that declares a callee with the WRONG arity/return still "MATCHES" — then `sig_unify` rewrites that extern to
   the SHARED canonical sig (fewer args / `void`), and the whole-binary gate fails (`too many arguments` /
   `void value not ignored`). FIX = keep the canonical extern, cast at the **call site** (codegen-neutral):
   `((void(*)(s32,s32,s32))func_X)(a,b,c)` for an over-arity call; `x = ((s32(*)(s32,s32))func_X)(a,b)` when a
   `void`-canonical callee's `$v0` is used; `(u16)`/`(s16)` at the use site per the asm `lhu`/`lh`. **Then RE-RUN
   `match_one` on the canonical-typed draft** — applying canonical sigs can change codegen, so gate the draft
   that still MATCHes WITH the canonical decls. (sig_unify can also, rarely, regress a match by forcing a
   canonical that's wrong for the byte-match — e.g. `void`/`s32` over a needed `s32`/`u32` def-sig; that's the
   narrow-param wall on the def itself → stub.)
2. **Stale sibling forward-decl (`M2C_UNK func_X();`).** A function you're matching is sometimes forward-declared
   by an already-matched SIBLING in the same overlay `.c` (m2c scaffolding: `M2C_UNK func_X(); /* extern */`),
   which conflicts with your real def. FIX = reconcile that one line to the real sig (`void func_X(void);`).
   (Proven: func_8012A418.) A standalone `match_one` MATCH that fails the whole-binary gate with
   `conflicting types for func_X / previous declaration` is this class — grep the overlay `.c` for `func_X`.
3. **~~Implicit-int caller plumbing~~ → CORRECTED (Phase 19 / T2, R14): two distinct real classes, NOT
   implicit-int, and propagate-first does NOT fix them.** The 3 "deferred" fns (func_80147514, func_80168F40,
   func_8017209C) were reproduced through the gate to find the ACTUAL blocker (R14 — verify the framing against
   the bytes). Neither is implicit-int; `dedup_propagate` (def → `engine_core.h`) would NOT have resolved
   either (the def still lands at its address-order site, after any file-scope caller extern). The two classes:
   - **(3a) Resident-callee LINK-miss** (func_8017209C). The draft calls a resident EXE/engine function by
     `func_<ADDR>`, but that address carries a **curated name** in `config/symbols.us.txt` (e.g.
     `0x8004CFEC = ratan2`). The linker resolves the curated name, not `func_<ADDR>` → the draft *compiles* but
     fails to **link** (`undefined reference to func_8004CFEC`) → the gate (correctly) reverts. **FIX =
     `tools/canon_resident_calls.py`** rewrites every `func_<ADDR>` whose address has a curated `// func` name to
     that name (extern + call), a pure draft-text transform (body bytes unchanged) → **run it FIRST in the
     recovery pipeline.** Proven: func_8017209C byte-identical after `func_8004CFEC`→`ratan2`.
   - **(3b) Shared-caller ARITY conflict** (func_80147514 = `s32`, func_80168F40 = `void *`). An already-banked
     **shared caller macro** in `engine_core.h` (e.g. `DEFINE_func_80147478`, instantiated at a *lower* address)
     declares the callee **file-scope** as `extern void func_X(void);` (void = no args) then calls `func_X();` —
     but func_X's real def takes an argument → `conflicting types for func_X / previous declaration` (NOT
     implicit-int; it's an explicit `(void)` proto). **FIX = change that caller macro's extern to no-prototype
     `extern void func_X();`** (K&R): byte-neutral for the caller (the empty call is identical), and a no-proto
     decl is **compatible** with a def whose params are **default-promotion-safe** (`int`/`s32`/`long`/pointer —
     NOT `char`/`short`/`float`; the narrow-param wall §3 of the toolkit still applies there). The macro lives in
     the shared header, so **fleet-re-gate** (`make check-all`). Proven: func_80147514 + func_80168F40, all
     136/136 byte-identical, byte-neutral on every overlay (only ov_SC01_077 carries the def; the other 133 keep
     the stub, where a declaration-only change emits no code).

   **The recovery pipeline is therefore: `draft → canon_resident_calls → sig_unify → harvest_verify --chunk 1`**
   (canon_resident_calls first so link-miss names are fixed before any signature unification; sig_unify still
   mandatory for def/callee-sig canonicalization). The 3b no-proto move is a separate, one-time edit per
   caller/callee pair (it touches the shared header) — apply it when the gate reports `conflicting types … (void)`
   from a shared-caller macro and the def's params are promotion-safe.

**Two NEW residual classes found at scale (beyond the §17 quirks):**
- **Per-file `-O0` class.** ~18 functions in ov_SC01_077 were built `-O0` (prologue sig `21F0A003` =
  `addu $fp,$sp,$zero`, args spilled to frame, load-delay nops, redundant `addu rd,rs,$zero`). The correct C is
  byte-exact **at -O0** but the overlay TU compiles `-O2`, and gcc-2.7.2 has **no per-function optimize pragma**
  (opt is per-file, Makefile). So these need their **own `-O0` split file** (the `src/boot.c` precedent,
  per-file `CC1FLAGS := -O0`). HIGH ROI: ~18 fns × reach-134. Members incl. func_8013C360,
  func_8013B568/B598/B6A0/B7AC/B7F4/B83C/BC7C/BCDC/BD34/BD74, func_8013C08C/C0F8/C360/C414/C938/C964,
  func_80144B9C, func_801457A4. (→ Phase 19 build-infra task.)
- **gcc-2.7.2 loop-guard** (func_8012C2D0). **[Phase-20 R14 CORRECTION — see §20]** the real residual is gcc
  STRENGTH-REDUCTION / IV-final-value ADDRESSING, NOT operand-order: the loop end is formed as `&D_80120194`
  (the array base) `+ 0x658C` — the base materialized SEPARATELY then offset (an induction-variable final value),
  while the start is its own symbol `D_801202A0`. The right C is base-relative end + `lhu`/`u16` (gets
  structurally close), but gcc -O2 CONSTANT-FOLDS `base + N` into one address (`lui %hi; addiu %lo`), so no clean
  C form (pointer-var, struct-array index) reproduces the separate base materialization. Still a genuine residual
  — stub; the (uncracked) lever direction is forcing the unfolded IV-final-value, not operand order.
- (also: func_8014F2E0 4-off = §10 store-vs-load schedule placement, base-preservation-vs-load-order mutually
  exclusive — a real §10 residual.)

## §18 Per-file `-O0` split inside an overlay/blob (Phase 19 T1)
> **§18-P29 — the multi-stub cluster carve is splat-integration-fragile (defer, or use the whale's shape).**
> P29 Arm A generalized the whale rollout (§38) to the 0x13410..0x14834 `-O0` cluster via
> `tools/rollout_o0_cluster.py` (3-way `<ov>` / `<ov>_o0` / `<ov>_o2b` carve + `O0_CLUSTER_OBJS` Makefile
> wildcard). It **banked 9/9 -O0 members on ov_SC07_010** (whole-binary, R22 140/140 — the Task-1 swing
> verdict is a BANKED FACT, not just masked-MATCH), **but the SAME carve byte-shifts 006/007/011** (+0x20
> `%lo` data-symbol shift, 34% of bytes, from a CLEAN build; boundaries verified as real fn-starts). Root
> cause is **splat re-disassembly**: 3-way splitting a code subseg that still contains `INCLUDE_ASM` stubs
> makes spimdisasm resolve some `%lo` refs to a different auto-symbol — NOT the compiler, NOT a boundary bug.
> The **whale carve (§38) never hits this** because its `_o0b` split is a thin `#include "../shared/<fn>.h"`
> wrapper with **no INCLUDE_ASM to re-disassemble**. Lesson: a per-overlay `-O0` cluster rollout should route
> each member through a shared-per-member header (whale shape), not leave stubs in the split. Until then the
> fleet `-O0` harvest (~1,233 members / ~0.6pp) is DEFERRED; `docs/decision-log.md` (2026-07-16) has the full
> byte-evidence. This is the "-O0 cluster split infra" Phase 20 "built + reverted", now root-caused.

A cluster of functions compiled `-O0` inside an otherwise-`-O2` binary needs its own `-O0`-compiled `.c` (the
`src/boot.c` precedent — gcc-2.7.2 has no per-function optimize pragma, opt is per-file via a target-specific
`build/src/<path>.o: CC1FLAGS := -O0 …`). Detect `-O0` by the prologue `21F0A003` (`addu $fp,$sp,$zero`) + param
spill/reload + load-delay nops.

**The mid-blob constraint (the non-obvious part).** `src/boot.c` worked because boot is a PREFIX. When the `-O0`
cluster is in the MIDDLE of the address space, you CANNOT keep before+after in one `.c`: a single object's `.text`
is atomic, so the `.ld` references `main.o(.text)` twice but GNU ld consumes it on first match → the after-region
stays concatenated with before and lands at the wrong address (byte divergence appears EARLY, at the first
`jal`/`%hi` to a moved callee, not at the cluster). **Fix = THREE distinct objects** (before / `_o0` / after), each
its own `.c`/subseg so each `.text` is independent and the `.ld` orders them by address. Minimize migration by
keeping the bulky side as the original name (asm paths unchanged) and moving the smaller side to a new subseg
(rewrite its INCLUDE_ASM paths with `sed nonmatchings/<old>" → nonmatchings/<new>"`). Keep the file-top header
(includes + canonical-sig externs) in BOTH halves. R22 clean-rebuild is a 100%-INCLUDE_ASM no-op gate before
adding bodies. NOTE: `tools/split_src_region.py`'s naive item-parser GLOMS a file-top extern block onto a
high-address function name → mis-addresses the split; do the cut by explicit line/offset instead.

**`-O0` gating ≠ `match_one`.** `match_one` compiles `-O2`, so it's WRONG for `-O0` functions — gate them only via
the whole-binary build (which honors the Makefile `-O0` override). `harvest_verify` works IF it builds via `make`;
direct `substitute → make build → SHA` + per-fn bisection is the reliable loop.

**`-O0` matched-idiom notes.** Hoist data externs to the file top, ONE canonical type per symbol (parallel drafts
disagree: `u8` vs `s32` on the same `D_*` → `conflicting types`). Scalar global store (`D_x = k`) and
pointer-loops match cleanly.

**`%lo`-folding indexed global — CRACKED (Phase 20, the array-of-STRUCT idiom).** The residual: for indexed
global access the original FOLDS `%lo` into the store (`lui %hi(sym); addu $at,idx; sw val,%lo(sym)($at)`),
1 ins shorter than our cc1's MATERIALIZE (`lui; addiu %lo; addu idx; sw 0($at)`). **The lever: declare the
global as `extern Struct base[]` where `sizeof(Struct)` == the array stride, and write `base[index].field`.**
This keeps `sym` a symbol_ref through gcc's array-index addressing → it folds `%lo(sym+field_off)` into the
store, byte-matching. The forms that FAIL (and why §18 first called it irreducible): `*(T*)(&sym + index*stride)`
and `*(T*)((char*)&sym + off)` — `&sym` forces the symbol's full address to be MATERIALIZED as a value (lui+
addiu) before the index add, so `%lo` can't fold. Worked example (byte-gated, func_8013B7AC):
`*(s32*)(&D_801DAA08 + a0*0x1C)=0` (materializes, FAILS) → `typedef struct{s32 f0; u8 pad[0x18];} E; extern E
D_801DAA08[]; D_801DAA08[a0].f0 = 0;` (folds, MATCHES). Pick the struct so the accessed field's address == the
target symbol (put the field at offset 0 and base the array at the field's symbol, OR base at the real array
symbol and use the real field offset — same bytes either way; the `%hi`/`%lo` immediates encode the address).
The constant-multiply for the stride (e.g. ×0x1C → `sll 3; subu; sll 2`) is gcc's `synth_mult`, emitted even at
`-O0`. Gate via the WHOLE-BINARY -O0 build (`match_one` is -O2, wrong for -O0). NB: the `-O0` cluster is
overlay-LOCAL (per the correction below) so this banks ×1 per overlay — but the idiom is reusable for ANY
`-O0` (or `-O2`) indexed-global access, fleet-wide.

**`-O0` reach-134 propagation is NOT free.** `-O0` functions can't go through `engine_core.h` (it's included by
each overlay's `-O2` main `.c` → would compile `-O2` → not match). To bank the ×134, each overlay needs its OWN
`-O0` split. Uniform across the fleet (all overlays share vram base `0x80128158`, so the cluster offsets are
identical) → scriptable, but it's per-overlay infra + 134 gates, not the "free ×134" a dedup report implies.

**Phase-20 R14 CORRECTION — the `-O0` cluster is NOT reach-134 byte-identical; the rollout is INVALID.**
Byte-proven: of the 134 overlays that span the cluster (vram 0x8013B568, file 0x13410), **only 1 — ov_SC01_077
itself — has cluster bytes identical to the matched C** (even func_8013B568's first 0x20 B match in just 1).
The cluster functions reference **per-overlay data addresses** (func_8013B568 stores to `D_80187270`/`%lo 0x7270`
in ov_SC01_077 but to `0x80182B04`/`%lo 0x2b04` in ov_SC01_005 — same instruction shape, different overlay-local
global), so each overlay's bytes differ → they are **overlay-LOCAL code, not shared engine code**. The
Phase-18/19 "6/16 matched (reach-134)" label conflated *function-present-at-this-vram* with *byte-identical*
(the precise R14 failure mode: trust the bytes, not the reach label). So the matched C banks ONLY ov_SC01_077
(×1); a fleet rollout via shared C is impossible. Banking these elsewhere = per-overlay RE-matching with each
overlay's own data addresses (extract `%lo` per overlay → template the C) — ~6 tiny fns × per-overlay, the
**×1 per-overlay-unique bucket** (low priority), ~0.2–0.3% for the whole-cluster, NOT the "+0.6% free ×134" the
backlog projected. The §18 split machinery (3-object before/_o0/after split + a `build/src/%_o0.o: CC1FLAGS:=-O0`
pattern rule + a `PROVIDE`-based `.ld` for the out-of-range data syms) was built and byte-validated to *compile/
link* a second overlay, then the gate exposed the per-overlay-data wall and it was reverted (the finding, not
the infra, is the deliverable). Net: skip the -O0 rollout; it's low-ROI per-overlay-unique work, not a shared win.

## §19 Scaling the toolkit waves — the recovery PIPELINE + the propagation CAP (Phase 19 T3)

Two §17/§17a waves over the tractable reach-134 tail, measured. **match_one close-rate is high and rising**
(batch-1 44/50 = 88%, batch-2 35/38 = **92%** after the fixes below); the work is in the **match_one→whole-binary
gap** (declaration plumbing) and then in **propagation** (not matching).

**The gate PIPELINE order matters — canon-only FIRST, sig_unify FALLBACK.** `tools/sig_unify.py` can REGRESS a
draft the agent already wrote canonically (it re-canonicalizes the def/callee sigs and occasionally forces a sig
that perturbs codegen, or mangles a line into a parse error). So gate in two stages (`.run/t3_gate2.sh`):
(1) `canon_resident_calls` → whole-binary gate ALL drafts; (2) `sig_unify` ONLY the stage-1 failures → gate again.
Measured: unconditional sig_unify lost ~5/batch vs canon-first.

**The dominant gate failure at scale = the shared-caller ARITY class → `tools/fix_arity_callers.py` (automated
§17a-3b).** Once garbled hints and sig_unify-regressions are removed, ~100% of the residual gate failures are:
a banked SHARED caller in `engine_core.h` declares the callee `extern <ret> func_X(void);` (or a *different*
arity), conflicting with the real def that takes args. FIX = rewrite the caller decl to no-prototype
`extern <ret> func_X();` — byte-neutral, compatible with promotion-safe params (int/s32/u32/long/ptr; NOT
char/short/float — narrow-param wall). `fix_arity_callers.py --apply --from-file <fails> --drafts <dir>` does it
(skips narrow-param defs), then re-gate; `--revert` to undo. Batch-2: recovered 8/18 this way; the rest were
genuine loose-typing conflicts (caller sig ≠ def sig with call-site casts already in play — Phase-16 wall).

**Garbled callee hints → fixed at the source.** `gen_harvest_targets.py` `INLINE_DEF_RE` was matching an
indented `if (func_X(...) == ...) {` call-expression as a "definition" → a garbled callee "signature" agents
paste verbatim as an extern → PARSE error at the gate. Fix: column-0 + type-only prefix (`^[A-Za-z_][\w \t*]*?`).
0 garbled of 749 after; batch-2 close-rate 88%→92%.

**THE CAP: propagation, not matching.** `dedup_propagate` only lifts a body whose types resolve from
`common.h` + `engine_types.h` (its `compiles_standalone` filter) — so a matched function whose body uses a
**typedef'd / anonymous / sibling local type** stays ov_SC01_077-LOCAL (no ×134, no fleet %). Batch-1 propagated
25/30, batch-2 only 10/25 (struct-heavier). `tools/build_engine_types.py --strip` lifts NAMED structs (0
same-name-different-layout collisions historically) but NOT typedefs → ~16 banked matches still can't propagate.
**Lever (Phase 20): extend the type-lift to typedefs/local types** → recovers those ×134 for ~0 agent tokens AND
raises every future batch's realized yield. The harvest's bottleneck has moved from "can we match it" to "can we
share it."

## §20 The wave-at-scale GATE CAP + residual-class verdicts (Phase 20)

Phase 20 closed the §19 propagation cap (T1 below) then ran the §17/§19 wave + recovery over the reach-134
≤90-ins tail — and hit a HARDER gate cap than Phase 19's. All byte-verified.

### THE CAP: at this tail the match_one→gate gap is the LOOSE-TYPING CALL-GRAPH wall (not cheap plumbing)
Batch numbers: 41/48 `match_one` MATCH (85%), but only **8/41 survived the whole-binary gate (~80% gap** — vs
Phase 19's ~30%). The gap is NOT the §17a/§19 cheap declaration-plumbing (link-miss/arity recovered **~0** here).
Byte-verified cause: a callee (e.g. `func_80153C74`) is declared with **CONFLICTING types at different overlay
sites**, so the draft's extern hits in-TU `conflicting types` — a COMPILE error, not a byte miss. `match_one`
OVER-PREDICTS because it compiles STANDALONE with the draft's own externs **and** masks jal/%hi/%lo — it never
sees the overlay's conflicting decls. **Every recovery lever fails at this tail** (all 0): `sig_unify` /
`canon_draft_decls` impose a single "canonical" that's wrong for some sites (loose-typing); `fix_arity_callers`
(not arity); **no-proto externs** (incompatible with the overlay's NARROW existing decls — `void f()` can't
co-exist with `void f(s16)`); strip-externs (implicit-int ≠ target). **The ONLY fix is the §17a-1 per-site
function-pointer cast** `((ret(*)(args))func_X)(…)` — it takes the callee's ADDRESS and calls with the draft's
intended sig, so there's no global decl and no conflict. Agents don't apply it reliably → **AUTOMATE it: a
recovery pass that, per draft, DROPS the conflicting callee extern + CASTS the call to the draft's sig, then
gates.** That is the Phase-21 cap lever (recovers a batch's lost ~33 reach-134 AND lifts every wave's gate-pass
from ~20% toward ~80%+). The bottleneck has moved again: matching ✓ (85%) → sharing ✓ (§19 type-lift) → now
**in-TU declaration reconciliation under loose typing.**

### Diagnostic lesson: a failed in-TU build leaves a STALE `.o`
When you substitute a draft and the in-TU build FAILS to compile, `build/src/<…>.o` retains the PREVIOUS
(target/stub) bytes → `objdump` of that `.o` shows a FALSE "byte-match." **Always trust the whole-binary SHA
gate, not a per-function `objdump`** (cost a real detour: func_80153C44's stale `.o` looked identical while the
true failure was a `conflicting types` compile error).

### NEW / CONFIRMED residual classes (this session)
- **§10 store-vs-load scheduling (func_8014F2E0, func_80150528) — CONFIRMED unsteerable.** Wave agents tried
  for-init / barrier / precompute / volatile; `sched.c` tie-break: the IV-init lands before the loop guard not in
  the preheader, and the `D_x=0` store schedules BETWEEN two arg-loads instead of after both — mutually exclusive
  with base-preservation. Stub.
- **§10 hoist-vs-remat regalloc tie-break (func_80149374, func_801493D0) — CONFIRMED.** gcc caches a `sp+off`
  buffer address in a freed callee-saved reg + moves (cheaper by its count) where the target REMATERIALIZES
  `addiu $a,$sp,off` per call. Array-decay / pins / barriers / permuter all fail. Stub.
- **IV-combine divergence (func_80177AD4) — NEW.** Our cc1's `combine_givs` won't fold a halfword RMW
  (`lhu;sh -2(p)`) into the byte biv (`sb 0(p)`) the way the target does (one IV at `p+0x20`); it spawns a
  dedicated 2nd IV → wrong base constant (`p+0x1e`). Probe-confirmed (a non-RMW `*p`/`*(p-2)` pair combines fine;
  the RMW spawns the 2nd IV). Genuine codegen divergence, not source-typeable. Stub.
- **Hoisted-invariant PROLOGUE ORDER (func_80177F84).** 3 prologue insns in the wrong order — gcc emits the
  pinned-`$a2` pointer init before the two hoisted loop-invariant constants; the target emits the constants
  first. No prologue permutation is < 3-off; the permuter can't run (the `register __asm__` pins are rejected by
  pycparser). §3/§5-class — stub.
- **The -O1 class (func_80161A90) — NEW build-infra (extends §18).** A function built `-O1` (frame 0x18, `lhu`
  reload, unfolded base, load-delay nops) inside an otherwise-`-O2` overlay. `match_one` (hardcoded `-O2`) CANNOT
  match it. Like the §18 `-O0` class but `-O1` → needs its own `-O1` split file (target-specific
  `CC1FLAGS := -O1`). Detect: prologue/scheduling between `-O0` (`21F0A003`) and `-O2`.

### Operational gotchas (cost real time)
- **Workflow `args`:** pass the target list as a JSON ARRAY, not a JSON string — a stringified array reaches the
  script as one string and `args.map` throws (`names.map is not a function`). Defensive:
  `const names = Array.isArray(args) ? args : JSON.parse(args)`.
- **`harvest_verify --chunk 1` for wave batches.** With `--chunk >1`, ONE draft that fails to COMPILE (a
  loose-typing conflict) fails the whole chunk's build and the bisection mis-attributes the innocent neighbors as
  failures. Gate wave drafts one at a time when the failure mode is compile-conflicts.

### What WORKED — the Phase-20 reusable wins
- **T1 — the typedef type-lift** (`tools/build_engine_types.py` extended). Added `find_typedefs()` (brace-aware:
  anon-struct `typedef struct{…}N;`, fn-ptr `typedef r(*N)();`, alias) + same-name-different-layout collision +
  tagged-struct-typedef overlap guards; emits typedefs in source order AFTER the named structs (deps like
  `A→S` preserved). **Closed the §19 type-blocked propagation cap** — 9 reach-134 fns ×134 for ~0 agent tokens,
  byte-neutral (`--strip` removes the defs; type decls emit no code).
- **T2 — the residual router** (`tools/exemplar_miner.py`). Consumes `wall_taxonomy.json` + per-overlay reach
  (dedup_propagate's computation) → routes every residual to a lever (WAVE / STRUCT / PINS / STUB) →
  `docs/exemplar_curriculum.md` + the reach-134 wave-target list + `.run/exemplar_routing.json`. The "scan all
  residuals, pick the teachers / size the pools" router. Caveat: its `mismatch` is the M2C-DRAFT mismatch, NOT
  the hand-match floor (a loop-guard buckets STRUCTURAL_MISS at mismatch-16 yet hand-floors to 1).

### Phase-20 RESOLUTION — `tools/cast_call_sites.py` BUILT + the cap re-diagnosed (R14, byte-proven)
The §17a-1 per-site cast is now AUTOMATED. **`tools/cast_call_sites.py`** (pure `--in/--out` transform, sibling
of sig_unify/canon_resident_calls): per draft, for every callee whose **canonical TU sig differs from the
draft's intended sig** (exactly the conflict set), it (1) rewrites the callee's decl line → the canonical
declaration (kills the in-TU `conflicting types`, keeps the symbol in scope) and (2) casts every call site to
the draft's INTENDED sig `((ret(*)(args))func_X)(args)` (decl lines never cast). The cast is codegen-neutral —
**confirmed**: gcc-2.7.2 folds `(cast)func_symbol` back to a direct `jal func_X` with the draft's calling
convention. Pipeline: `canon_resident_calls → cast_call_sites → sig_unify (def-sig) → harvest_verify --chunk 1`.

**RESULT on T6 batch-1's 33 gate-fails:** the callee-cast recovered **6 byte-identical** (func_80153C44/
8015CF58/801711FC/80161BE0/801683D8/8015F948); 5 propagated ×134 + 1 local; fleet **58.63%→58.82%**, 136/136.

**THE §20 "~33" PROJECTION WAS WRONG (R14 — the earlier diagnosis was incomplete).** Byte-classifying all 33
gate-fails: the batch is NOT dominated by the callee-conflict class. It splits into THREE directions, ALL
declaration-driven (0 pure codegen-quirk survives `match_one`):
1. **Callee-conflict (~6)** — the draft CALLS a shared callee declared inconsistently → `cast_call_sites` ✓.
2. **DEF-conflict (dominant, ~18) — the GENUINE loose-typing wall, byte-proven unrecoverable by text transform.**
   A banked caller (an `engine_core.h` DEFINE macro, invoked in this overlay) declares the draft's OWN function
   with a sig the matchable def can't satisfy (e.g. func_80161208: callers `s32 f(void)` 0-arg vs def
   `void f(void*)` 1-arg; func_80146A6C: callers `s32 f(s32,void*,…)` vs def `void f(short,int,…)`). Both ways
   fail: keep the draft's def-sig → `conflicting types`; canonicalize the def-sig (sig_unify) → 11/26 compile
   clean but BYTE-MISMATCH (the body genuinely needs the draft's sig). **The symmetric "caller-side cast" fix is
   BLOCKED**: `INCLUDE_ASM` emits only an `__asm__(".include …")` block — it declares NO C symbol — so a shared
   macro's internal `extern func_X` is the ONLY declaration of func_X in the 133 STUB overlays; dropping it (to
   cast the caller) breaks them, and it can't be edited per-overlay (it's in the shared header). The only path
   for these is RE-DRAFTING the body under the caller-canonical sig (a future wave with the canonical pinned),
   and the arity-mismatch subset (0-arg callers vs N-arg def) has NO compatible C sig at all → hard stub.
3. **DATA-conflict — byte-proven MOOT on this tail (R14, do not build the data-cast for it).** A data-analog
   cast (`*(T*)&D_x` against the canonical decl) sounded like the natural `cast_call_sites` extension, but the
   bytes say there's nothing to cast: **0 drafts declare an `extern struct/union`** data conflict, and the lone
   apparent "DATA-conflict" (func_8016A8FC / `D_800AE620`) was a **typedef-REDEFINITION** — the draft re-defines
   `typedef struct{s32 w[8];} Blk20;` inline while `Blk20` is already in `engine_types.h` (both sides use
   `extern Blk20 D_800AE620` — SAME type, no data conflict). Stripping the redundant inline typedef compiles but
   STILL byte-mismatches (the underlying blocker is the def-sig loose-typing wall, class 2). So the data-cast
   would be code for 0 real cases; skip it. (A general "strip inline named-type defs already in engine_types.h"
   pass is a 1-line harvest_verify-style cleanup if a future wave needs it — but it recovered 0 here.)

**Net:** the cast tool is the real, reusable cap-lever for the *callee-conflict* fraction of every wave (it
recovers what §17a-1 casting can, byte-gated) — but it does NOT lift gate-pass to ~80% here, because THIS tail
is dominated by the def-side loose-typing wall, not callee-conflicts. The honest bottleneck for the reach-134
residual: a matched body whose required signature is incompatible with the established caller-canonical, with no
caller-side escape (INCLUDE_ASM declares nothing). Diagnostic discipline that found this: classify EVERY
gate-fail by build-error class (callee `conflicting types` / DEF `conflicting types` for the draft's own fn /
DATA / clean-build BYTE-MISMATCH) before assuming a single cause — the §20 first pass saw one callee example and
generalized it; the bytes said otherwise.

**T3a `%lo`-folding `-O0` — CRACKED (Phase 20).** Not irreducible after all: the array-of-STRUCT idiom folds
`%lo` (declare `extern Struct base[]`, sizeof == stride, access `base[i].field`; NOT `*(T*)(&sym+i*stride)`,
which materializes). Full write-up + worked example in **§18** ("`%lo`-folding indexed global — CRACKED").
Banks ×1 (the cluster is overlay-local) but the idiom is reusable fleet-wide for any indexed-global access.

### §21 — wave-distilled idioms (Phase 21)
Byte-gated wins from the class-grouped waves. Each is a generalizable C *shape* (not a one-off), tied to its
byte-matched evidence fn. (Pins/array-decay/statement-order/shared-ret0/for-vs-do-while are §17–§18 — not re-listed.)
- **mem→mem unaligned N-byte copy → `memcpy(dst, src, N)`:** when the target copies a contiguous *byte* region
  with `lwl/lwr` + `swl/swr` pairs (unaligned 8-byte block, no field math), write `memcpy((void*)dst,(void*)src,8)`
  with `extern void *memcpy(void*,const void*,u32);` — gcc-2.7.2 inlines the small fixed-size copy to exactly that
  lwl/lwr/swl/swr sequence (element-wise `*(T*)dst=*(T*)src` instead picks `lw/sw` for the aligned case or splits
  wrong for unaligned). *fixes inlined-unaligned-block-copy codegen; evidence func_80153800 (sibling func_80146FC4 same shape).*
- **unaligned-SOURCE word load (then byte-read it) → `__attribute__((packed,aligned(1)))` struct in a union, plain
  assignment:** when the source is at an UNALIGNED address (e.g. an odd global) so the target reads it `lwl/lwr` into
  an aligned stack slot (`swl/swr`) and then reads individual bytes off `$sp` (`lbu 0/1/2($sp)`), the memcpy form above
  copies it but gives no typed handle to the bytes; declaring the source a *plain* `int`/`struct` MISSES (gcc assumes
  alignment → `lw`). Mark the source type `aligned(1)` and wrap it with a byte view in a union, then ASSIGN it to a
  stack union and index the bytes: `struct W{int w;}__attribute__((packed,aligned(1))); union U{struct W w; u8 b[4];};
  extern struct W G; union U t; t.w = G; … t.b[0] … t.b[1] …`. The `packed,aligned(1)` makes gcc emit `lwl/lwr` for the
  bare struct assignment (the unaligned read), the `swl/swr` lands it on the aligned stack union, and `t.b[i]` becomes
  the `$sp`-direct `lbu`. *fixes a `lw`-vs-`lwl/lwr` unaligned-source load where you also need per-byte access; evidence
  func_80142A80 (`D_801BD644` read `lwl 3 / lwr 0`, byte-read `lbu 0/1/2($sp)`).*
- **aligned 16-byte field-block copy → one struct assignment:** a contiguous aligned 4-word copy between two memory
  locations is `typedef struct{u32 a,b,c,d;} Blk16; *(Blk16*)(dst)=*(Blk16*)(src);` → gcc emits its a0–a3 4-register
  block load/store (1 ins shorter than four separate `lw/sw`, and fixes the v1/v0 load order + the load-delay nop).
  Four element-wise word copies constant-fold each base to its own `lui` (+ins, wrong order). *fixes word-by-word vs
  block-move + load-delay; evidence func_80163A94 (0x34..0x50 = two Blk16 assigns).*
- **partially-read out-param region → ONE stack struct, not separate scalars:** when a callee fills several fields of
  a stack buffer via `&buf`/`&buf.field` but the caller reads only SOME of them, declaring the slots as separate
  locals lets gcc DCE the unread ones and overlap/shrink the frame (wrong frame size). Make the whole region ONE
  `struct buf;` and pass `(s32)&buf`/`(s32)&buf.field` — the struct keeps every slot live at its true frame offset.
  *fixes DCE-driven frame-size/overlap divergence; evidence func_801749C8.*
- **(refinement of §16 mask-local — the inverse direction) raw `lhu` + `(s16)` at each use:** to force the target's
  `lhu;sll;sra` instead of a folded `lh`, load the global as a RAW `u16` (`iVar=(u16)D_x;`) and apply `(s16)` at
  every USE site — this defeats gcc's `lhu`+sext→`lh` combine fold (the opposite goal to §16's mask-hoist, which
  keeps `lh`+`andi`). *evidence func_801749C8.*
- **(refinement of the §5a/§17 zero-byte barrier) in-place re-tie variant:** `__asm__ __volatile__("":"=r"(x):"0"(x))`
  (output tied to input via constraint `"0"`) forces x to be re-materialized into a register *at that point*, pinning
  where a following store schedules — distinct from the input-only anchor `__asm__ __volatile__("":: "r"(x))` (which
  only anchors x *ahead* of the next op). Use when interleaved stores need a value freshly re-tied mid-sequence.
  *evidence func_80165CA0 (`SHB(x)` macro, combined with `$v0`/`$v1` pins).*
- **disjoint-bits `x + CONST` emits `ori`, not `addiu` → break it with a re-tie barrier:** when x's low bits are
  provably zero where CONST has bits (e.g. `x = (v & 0x7F00) >> 5;` then `x + 0xC00` — masked-then-shifted value
  can't overlap 0xC00), gcc-2.7.2 proves the add is disjoint and folds it to `ori x,x,CONST`; but the target used
  `addiu`. Insert the §21 re-tie barrier `__asm__ __volatile__("":"=r"(x):"0"(x));` BETWEEN the mask/shift and the
  `+ CONST` — re-materializing x there erases the known-zero-bits range, so gcc can no longer prove disjointness and
  emits `addiu x,x,CONST`. (Same barrier syntax as the bullet above, but the effect here is ARITHMETIC OPCODE
  SELECTION, not store scheduling.) *fixes the `add`→`ori` disjoint-bit fold; evidence func_80169058 (the `+0xC00`
  no-bit-overlap add).*
- **steer WHICH giv becomes the loop IV anchor → make that store LAST in source order:** when a loop writes several
  fields off one moving record pointer (`*(T*)(p+k)=…` for several k, then `p += stride`), gcc-2.7.2 combines those
  givs into ONE induction reg, and `loop.c:record_giv` PREPENDS each new giv to `bl->giv` so `combine_givs` picks the
  LAST-recorded (= last in PROGRAM ORDER) store as `giv_array[0]`, the anchor base. The target picks a particular
  offset as anchor (visible in the `.s` as the IV reg = `addiu $iv,$base,K` and every field store reaching off it with
  displacements of one sign, e.g. all `<=0`). To match, write the field whose offset is that anchor (K) as the LAST
  store before the pointer bump; the others (earlier in source) then reach it with the matching-sign displacements.
  (This is the RECOVERABLE counterpart to §20's IV-combine *failure* class — there combine refuses to fold a halfword
  RMW and you stub; here combine DOES fold and you steer the anchor by store order.) *fixes wrong IV base-constant /
  all-positive-vs-all-negative displacement set; evidence func_80178298 (anchor at p+0x12, all stores `<=0` off it; the
  +0x12 store moved last took it 15-mismatch→3).*
- **register-resident `short` truthiness test → `sll rX,16` + branch (NOT a bare `bnez`):** when a flag/counter
  the target keeps in a register (never spilled) is tested for `!= 0` via `sll $v0,$reg,16; beqz/bnez $v0` instead of
  branching on the value directly, the original local was a `short`/`s16` — gcc-2.7.2 lowers a `short` rvalue's
  truthiness by left-shifting 16 (dropping the upper half) then branching. Reproduce it on an `int` local by writing
  the test explicitly as `if ((flag << 0x10) != 0)` (the shift is computed without storing back, so the counter
  stays live in its reg across the increments); equivalently declare the local `s16`. A plain `if (flag != 0)` on an
  `int` emits `bnez $reg` with no `sll` and the diff won't close. *fixes the missing `sll _,16` before a truthiness
  branch; evidence func_8013F244 (`(iVar2 << 0x10) != 0`, the two `sll $v0,$v1,16` merge sites).*
- **force a global RE-LOAD across a store WITHOUT pinning the frame/prologue → NON-volatile `__asm__("":::"memory")`
  (NOT volatile):** when the target reads a global N times with intervening pointer-stores (each section gets its own
  `lhu sym`/reload), gcc-2.7.2 -O2 instead CSEs the *derived* index (e.g. `idx*4` survives in a reg across the store,
  so no reload). A memory clobber forces the reload — but the **volatile** form (`__asm__ __volatile__("":::"memory")`)
  is a hard scheduling fence: it (a) pins the prologue stack-adjust (`addiu sp,-N`) to the top of the function
  (cc1 emits `subu sp` before the asm because the clobber may touch the stack), so a target whose frame alloc is
  *scheduled mid-function* (into a load-delay slot) can't match, and (b) co-schedules large-constant builds
  (`li reg,HI; ori reg,LO`) as an adjacent unit. Dropping `__volatile__` keeps the memory clobber (→ the reload still
  fires) but makes it a *soft* dependency the scheduler reorders around: the `subu sp` then floats down into the
  load-delay slot, AND cc1 splits the constant build around an independent address materialization (`li t0; la a2;
  ori t0` instead of `li t0; ori t0; la a2`). So: **use the non-volatile memory clobber when you need the reload but
  the target has a scheduler-mobile frame and/or a split constant build; use the volatile form only when you also
  want the hard fence.** (The §5a cross-jump barrier still needs volatile — that's a correctness fence, different goal.)
  *fixes simultaneous {global-reload, mid-function phantom-frame placement, split %hi/%lo-constant prologue order};
  evidence func_801758FC (3 sections each reload `lhu D_800B9A02`; phantom 0x10 frame alloc lands in the F7D0
  pointer-load's delay slot; closed 4-/3-mismatch tensions → MATCH 55 ins).*
- **induce a phantom (unused, no-spill) stack frame the target has but your codegen omits → an address-taken local
  array `s32 frame_pad[N]; (void)&frame_pad;`:** when the target reserves `addiu sp,-0x10`/`+0x10` with NO register
  saves and NO spills (a leaf whose original had a stack local the optimizer later kept in regs), gcc's
  `compute_frame_size` rounds `get_frame_size()` up to the next 8 → declare a local whose address is taken (so it's
  not DCE'd and reserves `var_size`) but never stored through. `(void)&frame_pad;` escapes the address with zero
  emitted code at -O2. Size N×4 picks the frame: 1–2 words → 8, 3–4 → 0x10. (This is the INDUCE direction; §5's
  phantom-frame note is the REMOVE direction where gcc *adds* a frame the target lacks.) *evidence func_801758FC (0x10).*
- **store a high-bit (≥0x8000) 16-bit constant to a halfword → `unsigned short*`/`u16*`, NOT `short*`/`s16*`:** the
  STORE is `sh` either way, but the *constant materialization* differs by signedness of the pointee. A `u16` store
  zero-extends → `ori reg,$zero,K` (opcode `0x34`, e.g. `3403c040` = `ori v1,$zero,0xc040`); an `s16` store
  sign-extends → `addiu reg,$zero,K` (opcode `0x24`, e.g. `2403c040` = `addiu v1,$zero,-16320`, value 0xFFFFC040).
  objdump pretty-prints BOTH as `li v1,0xc040`/`li v1,-16320`, so read the opcode (`34xx`=ori vs `24xx`=addiu), not
  the mnemonic. Only matters when bit 15 of the constant is set (0x8000–0xFFFF: 0xc040, 0xaa10, …); for K<0x8000
  both forms emit the same `ori`. Pick `u16*` to get `ori`, `s16*` to get the sign-extending `addiu`. *fixes the
  `addiu`(sign-ext)↔`ori`(zero-ext) constant-build before a halfword store; evidence func_8017E924 + func_8017E974
  (0xc040), func_80182E30 (0xaa10).*
- **`$sp`-manipulating scratchpad-stack-switch trampoline → a FULL `__asm__ __volatile__` body (clobber `"memory"`),
  copied from the byte-proven sibling with ONLY the `jal` target + the `D_801D961x` symbol swapped — plus three
  maspsx rules that are byte-load-bearing.** This 22-ins idiom (repoint `$sp` into the D-cache scratchpad stack at
  `*(0x1F8003FC)`, call one engine fn, stash `$v0` through `D_801D961x`, restore `$sp`) is NOT expressible in C
  (it rewrites `$sp` around a call), so write the whole body as inline asm with `.set noreorder`. It is a 15-member
  reach-134 duplicate family (canonical `func_8014CCB4`), so each match is high-value. The three rules the wave proved
  (each a +1-ins byte-miss if violated): (1) **do NOT write an explicit `nop` after `jal`** — maspsx
  `--aspsx-version=2.56` auto-fills the delay slot; put `lui $at,%%hi(D_801D961x)` directly after the `jal` and its
  auto-nop becomes the slot (→ `jal`/`nop`/`lui` exactly); (2) **no trailing `.set reorder`** — it emits a stray
  epilogue nop; (3) **escape `%hi`/`%lo` as `%%hi`/`%%lo`** inside the `__asm__` string (a bare `%` is read as an
  operand placeholder → assembler error). (General beyond this trampoline: rules 1–3 apply to ANY hand-written inline-
  asm body carrying a `jal` + `%hi`/`%lo` relocations.) *fixes double-delay-nop / stray-epilogue-nop / `%`-placeholder
  byte-misses in a hand-asm `$sp`-switch wrapper; evidence func_8014D04C, func_8014D738, func_8014DF3C, func_8014E434,
  func_8014E6A0, func_8014E934, func_8014ED28, func_8014F1F4, func_8014F468, func_8014F6F4, func_8014FCFC, func_80150480
  (12 banked this wave, family of func_8014CCB4).*
- **byte/`u8` in-place pre-decrement that tests the OLD value → write the subtract as `+ 0xFF`, NOT `- 1`:** for a
  `u8` field decremented in place where the original tests the pre-decrement value (`c = p[i]; p[i] = c-1; if (c==0)…`,
  emitting `lbu;addiu $v0,$v1,0xFF;bnez $v1;sb $v0`), gcc-2.7.2 does NOT canonicalize `c + 0xFF` and `c - 1` to the
  same immediate even though they are equal mod 256 and the `sb` truncates either way — it materializes whatever
  signed-representable literal you wrote. Empirically (this toolchain): `c + 0xFF` → `addiu …,0xFF` (`2462…00FF`,
  matches), `c - 1` (and `p[i]-1`) → `addiu …,-1` (`2462…FFFF`, MISSES); the distinction holds even on a plain `int`.
  So when the target's decrement immediate is `0xFF` (or any positive wrap-literal) rather than `-1`, write the
  wrapping form `p[i] = c + 0xFF;` explicitly. *fixes the `addiu …,-1`↔`addiu …,0xFF` immediate-literal mismatch on a
  byte predecrement; evidence func_8016EBA8 (`param_1[2] = c + 0xFF` with pre-decrement `if (c==0)`).*
- **store a call result AND test/reuse it in one expression → combined assignment `*(T*)(p+k) = local = f();` (NOT a
  store of a re-read local):** when the target does `jal f; sw $v0,k(base)` (the store in the call's delay slot, or
  immediately after) then BRANCHES on `$v0` (`beqz/bnez $v0`) and/or copies it to a callee-saved reg
  (`addu $sX,$v0,$zero`) for use in the success arm, write the store, the test, and the reuse off ONE local that is
  assigned the call result in the SAME statement as the store: `*(int*)(p+0x20) = v0 = f(); if (v0==0){…} else {…use v0…}`.
  gcc-2.7.2 then keeps the result in `$v0` so the `sw $v0` (delay slot) and the `beqz $v0` both read it directly, and
  emits the `addu $sX,$v0` copy ONLY because the success arm reuses `v0` across later calls. The naive two-statement
  form (`v0 = f(); *(int*)(p+0x20) = v0;`) instead emits the copy-to-`$sX` BEFORE the store and loses the bare
  `sw $v0`/delay-slot schedule. (General: any "store an allocator/constructor result to a struct field, null-check it,
  then use it" pattern.) *fixes the call-result store/test landing in the wrong register + lost delay-slot store;
  evidence func_80142DC4 (`*(int*)(param_1+0x20)=v0=func_8012C1B8(); if(v0==0)… else …v0…`).*
- **force a memory-operand RELOAD (two identical `lw`s) with NO barrier → place the intervening store between the two
  reads in SOURCE ORDER:** when the target reads the same field twice (`lw $v0,K(base)` … then `lw $v0,K(base)` again) with
  a store to a *different* field in between — i.e. gcc-2.7.2 -O2 did NOT keep `*(p+K)` cached across that store — reproduce
  the reload purely by statement order: write the dependent store as a statement that *uses* `*(p+K)` and place it BEFORE
  the second use, so an unrelated write (`*(p+J)=…`) sits between the two reads and defeats the load-CSE. No `__asm__`
  clobber and no pin needed (this is the barrier-free counterpart of the §21 memory-clobber reload bullet, which is for a
  *derived-index* CSE; here the CSE'd thing is the *memory load* itself). Hoisting the field into one local (`int t =
  *(p+K); …; use t;`) instead keeps it in a reg → a single `lw`, misses. *fixes a missing 2nd `lw <field>` reload across an
  unrelated field store; evidence func_80168430 (`*(p+0x30)=D[*(p+0x2C)];` placed before `iVar1=(*(p+0x2C)<<17)>>16;` → the
  `sw 0x30` between the two `lw 0x2C` forces the reload, 33/33 ins).*
- **EXPLOIT cross-jumping (the inverse of the §5a barrier) — duplicate the SAME call into BOTH if/else arms to merge
  the `jal` while keeping per-arm operand setup:** when an `if/else` ends by calling ONE function with the same
  argument-register layout but DIFFERENT constant/value args per arm, and the target emits ONE shared `jal` site
  reached by a `j` from one arm + fall-through from the other (each arm doing its own `addu $a0,$base` + `addiu $a1,K`
  beforehand, with a `nop` join delay slot), write the call LITERALLY IN BOTH ARMS: `if(c){ g(p,5); h(p,0x1C); }
  else { g(p,4); h(p,0x11); }`. gcc-2.7.2's cross-jump pass (§5a) finds the two `jal h` insns RTL-identical → merges
  them into one shared site, but the per-arm arg setup differs → stays duplicated → exactly the
  `[arm1:setup; j join][arm2:setup; fall][join: jal; nop]` layout. The naive single-call form (compute K in the `if`,
  then `h(p,K)` once after the join) instead schedules the arg setup differently and loses the dual-setup/`j`/`nop`
  shape. (This is the deliberate-MERGE direction; §5a's `__asm__ __volatile__("")` barrier is the deliberate-KEEP-SEPARATE
  direction — same pass, opposite goal. Combine with the §3-T4 branch-polarity invert to pick which arm is the `beqz`
  fall-through.) *fixes a duplicated-vs-shared `jal` + missing per-arm arg setup / join `nop`; evidence func_80159BE4
  (`func_80154A74(arg0,0x1C)` in the if-arm + `func_80154A74(arg0,0x11)` in the else-arm → one merged `jal` at the join,
  40 ins).*
- **read-modify-write of a SCALAR global where the target materializes the address ONCE and reuses it for both the
  `lw` and the `sw` → access it through a pointer VARIABLE (`T *p = &D_x; *p += 1; if (*p >= K)`), NOT the bare global
  (`D_x += 1`):** when the target does `lui $r,%hi(sym); addiu $r,$r,%lo(sym); lw $v,0($r); … sw $v,0($r)` (one
  address reg, `0($r)` displacement on BOTH accesses), gcc-2.7.2 -O2 reaches that by CSE-ing the `&D_x` address
  expression across the read and the write. Writing the bare global RMW (`D_x += 1`) instead lets gcc fold `%lo` into
  each access INDEPENDENTLY → two separate `lui … ; lw/sw %lo(sym)($at)` materializations (the §18 single-store fold,
  applied twice; wrong reg/ins for an RMW). A pointer var to the global forces the shared base reg. (This is the
  GLOBAL-RMW counterpart of §18's indexed-global fold and §17's stack-buffer remat — distinct trigger: a scalar global
  read AND written in the same region.) NB unrelated to the same fn: read a `+0x34` halfword field with `lhu` (`u16`),
  not `lh`, when the target zero-extends. *fixes two-separate-`%lo`-folds vs one-materialized-base-reg on a scalar
  global RMW; evidence func_80186938 (`s32 *p=&D_801270C8; *p+=1; if(*p>=4)…` → `lui;addiu %lo;lw 0($v1);…;sw 0($v1)`,
  byte-gated).*
- **force a RELOAD between two CONSECUTIVE stores to the SAME global (store a const, then read it back to OR/RMW) →
  qualify the global `volatile`, NOT an `__asm__` barrier:** when the target does `sh K,%lo(sym); lhu %lo(sym); ori …;
  sh %lo(sym)` — i.e. it stores a known constant to a global and then *re-reads it from memory* before the next
  store — gcc-2.7.2 -O2 normally store-to-load-FORWARDS the just-stored constant and CONSTANT-FOLDS the two writes
  into ONE (`D_x = K | 0x4000;` → a single `sh` with `li K|0x4000`), so the reload `lhu` and the second `sh`
  vanish. Declaring the global `volatile` (`extern volatile u16 D_x;`) forbids the forward/fold: each `D_x = …` is
  emitted verbatim and the read between them becomes the `lhu` reload, reproducing both stores. This is the
  TYPE-QUALIFIER reload lever — distinct from the §21 `__asm__` memory-clobber (derived-index CSE across pointer
  stores) and the statement-order reload (two identical loads across an *unrelated* field store): here the value is
  a constant gcc KNOWS, so only `volatile` defeats the store-forwarding; statement order and clobbers do not. Use it
  whenever the target re-reads a global it just stored a literal into. *fixes a folded-away `lhu` reload + merged
  double `sh` to one global; evidence func_801806D8 (`volatile u16 D_80126B96; D_x=2; D_x=D_x|0x4000;` →
  `sh 2; lhu; ori 0x4000; sh`, byte-gated 56 ins).*
- **force ONE specific field/pointer load to RELOAD (target re-emits `lw K(base)` where gcc -O2 CSEs it across
  intervening calls/non-field stores) → cast THAT access `*(volatile T*)`, NOT a global `__asm__` fence:** when the
  target reads a struct field through a pointer twice (`lw 0x64($s0)` … other code (calls, stores to *unrelated*
  addresses) … `lw 0x64($s0)` again) but gcc -O2 keeps the first load cached in a register (a single `lw`, the
  field reused via regalloc — so neither statement-order nor a constant store-forward defeats it), wrap **each
  reload site** in a volatile pointer cast: `iVar = *(volatile int *)(param_1 + 0x32);` (and reuse it for the
  follow-on field reads off `iVar`). The `volatile` makes that ONE access a non-CSE-able memory reference, so gcc
  re-emits `lw 0x64($s0)` there, while leaving all other scheduling untouched. This is the SURGICAL reload lever —
  distinct from the §21 non-volatile `__asm__("":::"memory")` clobber (a function-wide fence, for a *derived-index*
  CSE), the statement-order reload (needs an *unrelated field store* to fall between the two reads), and the §22
  `volatile`-qualified GLOBAL (defeats *constant store-forwarding* of a known literal): here the CSE'd thing is a
  *runtime field load* reused via register, the intervening ops are calls/foreign stores (not a usable field-store),
  and you must NOT add a global barrier (it perturbs the rest of the schedule). *fixes a folded-away 2nd/3rd `lw <field>`
  reload of a pointer-reached struct field across intervening calls; evidence func_801424E4 (`*(volatile int*)(param_1+0x32)`
  ×2 → `lw 0x64($s0)` re-emitted at each use, byte-gated 58 ins).*
- **fill a load-delay slot in a tail-store sequence → read the field into an explicit TEMP one statement EARLY
  (refinement of §2-T2):** when a tail reads several fields from an out-param/struct and then writes several
  *constant* stores, and the target schedules ONE of those field loads early so its load-delay slot is filled by a
  following `li` (the value held in a reg and stored LAST), pull that load up with a named temp: `c = out.c; *(int*)(p+0x1c)=0x5a; *(short*)(p+0x34)=1; *(short*)(p+0xe)=c;` → gcc emits the `lhu` for `out.c` ahead of the
  `li 0x5a` (delay-slot filled) and the `sh c` last from the held register. Leaving it inline as the last store
  (`*(short*)(p+0xe)=out.c;`) instead lets gcc defer a *different* field's store and the schedule diverges. The temp
  only relocates the load in source order; §2-T2 names the mechanism but punts the load-delay case to the permuter —
  this is the concrete C lever for it. *fixes a deferred-field-store / unfilled load-delay schedule in a const-store
  tail; evidence func_801856F8 (`c = out.c;` hoisted before the `0x5a`/`1` stores, byte-gated 71 ins).*
- **handwritten GTE `sqr` body: WRITE the two cop2-latency `nop`s and VERIFY ON RAW BYTES — the assembler keeps
  them; objdump (and `match_one`) only HIDE them (false "stripped" diff):** for a handwritten GTE squared-distance
  fn (`lwc2 $9/$10/$11`, two latency `nop`s, `sqr 0`, `swc2 $25/$26/$27`), write the whole GTE op as an
  `__asm__ __volatile__` body with the `"nop\n" "nop\n"` literally between the last `lwc2` and `sqr` (`: : "r"(&in[0])
  : "$9","$10","$11","memory"`, store block pinning `$2`). `mipsel-as` does **NOT** strip those cop2 nops — they are
  in the object. The trap that made a prior session wrongly mark this whole family "not C-source reachable": **objdump
  ELIDES runs of zero words** (prints `\t...` for the two `00000000` nops), and `match_one` diffs via objdump → it
  reports a spurious mismatch (e.g. "22 mismatched") for bytes that are actually identical. **VERIFY GTE/cop2 fns on
  RAW bytes** (`objcopy -O binary --only-section=.text` then compare words), never on the objdump listing. (Independently
  byte-confirmed here: `+0x054`/`+0x058` = `00000000`/`00000000` precede `4AA00428`/`sqr 0` in the built `.o`.) This
  unblocks the entire handwritten GTE-`sqr` family (siblings func_8013E064/_8013E0FC/_8013E194/_8013E22C/_8013E298/
  _8013E370/_8013E410). *fixes the false "cop2 nops stripped" residual (an objdump zero-run-elision artifact, not a
  codegen miss); evidence func_8013E2C4 (43/43 raw bytes, banked + propagated ×13).*
- **store ONE value to several memory locations → write them as a CHAINED assignment `*a=*b=*c=v;`, NOT separate
  statements:** when the target copies a (callee-saved) value into a SCRATCH reg once (`addu $v0,$sX,$zero`) and
  then `sh/sw $v0` to several locations (often one store in a delay slot), the original wrote the stores chained —
  the chain's intermediate rvalue becomes that single reused scratch temp. Separate statements (`*a=v; *b=v;
  *c=v;`) instead store the source reg directly (no `move`) and miss by ≥1 ins. (Distinct from §21's
  `field=local=f()`, which keeps a *call result* live for a test; here it's one value fanned out to N stores.)
  *fixes a missing `move $v0,$sX`+from-scratch store run; evidence func_80143D28
  (`*(s16*)(iVar3+0x18)=*(s16*)(iVar3+0x1a)=*(s16*)(iVar3+0x1c)=sVar4`).*

> **⚠ CANDIDATE (unverified) — the next two bullets are from `func_801775E0`, a NEAR-MISS (closeness 2, NOT
> byte-banked)**, appended directly by a wave-13 drafter (that drafter→cookbook path is now blocked, `commit:0219`).
> They are plausible gcc-2.7.2 observations but were NOT confirmed by a byte-match. A drafter MAY try them — the
> byte-gate (G3/P9) is the sole arbiter, so a wrong idiom can never bank — but VERIFY before trusting. Drew to
> keep / refine / drop.

- **`lbu` value with SIGNED compares (`bltz` + `slti`, NOT `sltu`) → write each range bound as a SEPARATE `if (…) goto`
  statement, never a chained `||`:** when the target loads a `u8` global with `lbu` (zero-extend → known 0..255) yet
  the comparisons are signed (`bltz $v1`; `slti $v0,$v1,K`) — including a provably-dead `bltz` on a 0..255 value —
  gcc-2.7.2 has emitted the conditions as INDEPENDENT signed `slt` branches. A chained `if (v<0 || v>0xf6 || v<0xf3)`
  CANONICALIZES: gcc proves `v<0` impossible (drops the `bltz`) and folds `v>0xf6 || v<0xf3` into the unsigned range
  trick `sltu $2,$v1,247` / `addiu -0xf3; sltiu 4` (wrong: `sltu`, no `bltz`, fewer ins). Splitting into
  `if (v==0) goto a; if (v<0) goto b; if (v>=0xf7) goto b; if (v<0xf3) goto c;` keeps each as its own signed `slt`+branch
  (the `v<0` becomes a real `bltz`, the bounds become `slti`), reproducing the target exactly. The launder/barrier
  tricks do NOT help (gcc re-derives the u8 range across an `__asm__` move); only the per-condition `if-goto` split does.
  *fixes the unsigned-range-collapse → signed-separate-compare divergence; evidence func_801775E0 (`bltz;slti 0xF7;slti 0xF3`).*
- **shared join-block placement (call/store block reached by ≥2 paths) is steered by which exit the LAST range test
  BRANCHES to vs FALLS THROUGH:** gcc-2.7.2's jump pass lays the join block (e.g. a `jal` reached by both an early
  `beq` and the range-chain fall-through) right after whichever predecessor it processes to fall through. Writing the
  chain's terminal as `if (v>=K) goto join;` (branch TO the join) puts the join AFTER the sibling block (matches a target
  whose join sits between the early-eq block and the tail); writing `if (v<K) goto other; goto join;` (branch AWAY, fall
  to join) FLIPS the entire layout (the early-eq test inverts `beqz↔bnez` too). The two are COUPLED — you cannot
  independently pick the terminal branch polarity AND the join placement; pick the form whose join placement matches and
  accept the terminal-branch polarity it implies (a residual the permuter can't touch under `register __asm__` pins).
  *evidence func_801775E0 (the `if(v>=0xf3)goto call` form gives correct [chain][eq-block][call][else] layout but leaves
  the terminal as `beqz→call` where the target has `bnez→.L674`; the negative form flips to a 50-mismatch layout).*

### §22 — DEF-side loose-typing recovery + grinder blacklist (Phase 21)

The wide **self-MATCH → whole-binary-gate gap** (a draft that `match_one`-MATCHes but the gate rejects) is dominated
by the **DEF-side loose-typing wall**, NOT cheap data plumbing (Phase-20 was right that data-cast is mostly moot —
the lone data exception is a `D_x` whose draft `extern` type disagrees with engine_core.h, fixed by rewriting the
draft extern to canonical and assigning through it). The DEF-side wall: the draft's **byte-correct definition** has
FEWER params than the canonical cross-overlay decl in `engine_core.h` (e.g. def `void f(void)` vs decl
`void f(s32,s32,s32)` because callers across overlays pass args the body ignores) → `conflicting types for f` in the
full TU → gate reject. **Diagnose before building (R14): reproduce the whole-binary error** (substitute the draft,
`make build`, grep `error:`/`conflicting types`) — `harvest_verify` discards it. The warnings at fixed line numbers
(incompatible pointer / built-in `memcpy`) are pre-existing and harmless; the real error is the `conflicting types`.

- **Recovery = adopt the canonical param list on arity mismatch** (`sig_unify.rewrite_def`, Phase-21 fix). Previously
  it rewrote params only when arity MATCHED (return-type-only fallback otherwise — leaving the conflict). Now: when the
  canonical decl has MORE params, take the canonical param TYPES + COUNT, keep the draft's names where they exist, and
  synth `_argN` for the unused extras. Unused params sit in `$a0–$a3` → **free at -O2** → byte-identical, conflict
  gone. Since `sig_unify` is in the `gate_stage` pipeline, this auto-recovers DEF-side near-misses on **every** wave +
  the grinder (compounding, like the Phase-20 type-lift). *evidence: func_8016EDEC, func_8016EE40 banked via this.*
  Still-hard residual (diminishing returns): narrow params (s8/s16/u8/u16/float) where gcc's default-promotion rule
  blocks the no-proto/wider escape (§15/§18), and multi-way loose typing (the same fn called with contradictory
  arities → no single ANSI prototype).
- **Grinder blacklist** (`tools/grinder.py`): a permuter "win" the whole-binary gate STILL rejects is plumbing-bound
  (the masked-0 doesn't survive the real link) — re-permuting can NEVER bank it. Record won-but-gate-rejected fns to a
  persistent `.run/auto/grinder_blacklist.json` and skip them forever (the daemon's `tried.clear()`-after-idle would
  otherwise churn the lowest-`close` plumbing fns endlessly — it banked 0 in ~8h doing exactly that). Frees the
  permuter for genuine regalloc/schedule near-misses (the only class it can actually close).

### §23 — Giant `func_80153E00` cracked (scalar-data CAST); BUT most giant drafts are STALE+INCOMPLETE, and a diag MUST remove artifacts (Phase 21 — byte-proven + a self-correction)

**`func_80153E00` (195 ins, ×134) cracked — a clean 1-instruction near-miss.** Substituting its draft compiles
AND links CLEAN and was 1/195 off. `match_one` over-predicted (compiles STANDALONE with the draft's own externs
AND masks jal/%hi/%lo) → it never saw the residual. Banked ×134 (fleet 62.27→62.31%).

**⚠ DO NOT GENERALIZE "giants are near-misses" (a same-session R14 self-correction).** After func_80153E00, I
diagnosed the other 14 MAIN-file giant drafts and a buggy diag reported **10 byte-MATCHes** — a **STALE-ARTIFACT
MIRAGE**. The real byte-gate (`harvest_verify`, which `os.remove`s the output first) banked **0 of 10**: every
draft FAILS TO COMPILE. They are prior-wave drafts gone **stale + incomplete** vs the grown `engine_core.h` —
`conflicting types for D_x` (the draft declares `u8 D_80126B58` vs canonical `s32`, `u8 D_80126948` vs `u8[]`),
**undeclared** data symbols the draft never externs (`D_800A5E8C`, `D_800B9A08` → link `undefined reference`),
and incomplete types. **These are NOT bankable near-misses** — they need RE-DRAFTING fresh against the current
canonical (a worker wave), not a cheap fix. func_80153E00 banked only because its draft was complete + clean.

**⚠ THE STALE-`.o` TRAP BIT THE DIAGNOSTIC ITSELF (§20, the hard way).** A per-function `objdump` diff that
builds WITHOUT removing `build/src/<ov>.o` + `<ov>.elf` first shows a **FALSE byte-match** when the spliced draft
**fails to compile**: `make` leaves the prior (stub) artifacts, so objdump disassembles the TARGET and reports
"0 diffs." This faked 10 giant MATCHes. **A diag MUST `os.remove` the `.o`/`.elf`/binary before each build** (then
a compile failure → empty disasm → honest "BUILD-FAIL", not a false match). `.run/diag_funcdiff.py` was fixed to
do this. **The whole-binary SHA gate (`harvest_verify`) is the SOLE arbiter (G3/P9)** — it removes the output, so
it was right while the diag lied. When a diag and the gate disagree, the gate wins; suspect a stale artifact.

**THE DIAGNOSTIC (right tool, artifact-safe):** `.run/diag_funcdiff.py <fn> <draftdir>` — build STUB →
`objdump -d` the fn (target); splice draft + build → `objdump -d` (candidate); diff, address column normalized
(`s/80[0-9a-f]{6}/ADDR/`). NOW removes artifacts before each build (else false match). Shows relocation vs
codegen vs type residual in seconds — but a 0-diff here is only trustworthy because of the artifact-removal +
a confirming `harvest_verify`. Run ONLY when no `ov_SC01_077` build is in flight (concurrent builds clobber `build/`).

**THE FIX for `func_80153E00` — the scalar-data-signedness CAST (extends §22, corrects §20's "data-cast moot").**
The 1 diff: target `lhu D_8011DB0C` (unsigned halfword) vs candidate `lh` (signed). The global `D_8011DB0C` is
declared **`extern s16`** canonically (in `engine_core.h` + a banked `DEFINE_*` macro that writes it), but
`func_80153E00` needs a **`u16` read** (`lhu`). Two non-fixes: declaring the draft `extern u16 D_8011DB0C;` →
**`sig_unify` reverts it to the canonical `s16`** (canonical wins, by design) → `lh` again; §22's "assign through
the canonical decl" → also `lh` (the canonical type IS s16). **The fix is the DATA analog of `cast_call_sites`'s
per-site cast: keep the canonical `extern s16` decl, cast the READ site —**
```c
db0c = *(u16 *)&D_8011DB0C;   /* canonical decl stays `extern s16`; gcc folds &sym+deref → a single lhu */
```
gcc-2.7.2 folds `*(u16*)&sym` to one `lhu sym` (no extra address insn), identical to declaring it u16 — but with
NO decl conflict, so it survives the gate pipeline (`sig_unify` leaves the canonical decl alone). Writes
(`D_x = 0` → `sh`) are signedness-agnostic, so only READ sites need casting. **This refutes §20's "data-cast is
MOOT"** — that finding only checked `extern struct/union` conflicts; **scalar signedness/width conflicts
(`s16`↔`u16`, and by extension `s8`↔`u8` `lb`/`lbu`, `s16`↔`s32` `lh`/`lw`) ARE real and recoverable** by this
read-site cast. The same class is hinted across the other giants (e.g. `func_80129CF8`'s note: "`D_80126DB8`
fields s32-store/(s16)-read, lh vs lw"). *evidence: func_80153E00 — 1/195 → 0/195, banked ×134, fleet 62.27→62.31%.*

**TOOLING LEVER (probe-before-build, R14):** if this scalar-data-conflict class recurs across the remaining
giants, build `cast_data_sites.py` (the data sibling of `cast_call_sites.py`): for each `D_x` read whose required
load width/signedness differs from the canonical decl, rewrite the read site → `*(T*)&D_x` (leave the decl
canonical; never cast a write). Folds into `gate_stage` → auto-recovers the class on every wave for ~0 tokens.
Gather evidence on ≥1–2 more giants first (func_80153E00 is N=1).

### §24 — The `ov_SC01_077_a.c` split-file vein: split-aware propagation, but loose-typing-gated (Phase 21)

**The opportunity (real):** the Phase-19 `-O0` work split ov_SC01_077 into 3 TUs (`ov_SC01_077.c` + `_a.c` +
`_o0.c`). The harvest pipeline defaults to `src/{ov}/{ov}.c`, so the **66+ fresh, cached, reach-134 fns in
`ov_SC01_077_a.c` were never waved** — a tooling gap, not a difficulty wall. The main-`.c` reach-134 fuel is
byte-exhausted (1 fresh fn); `_a.c` is where the fresh fuel is. (`tools/build_fuel_manifest.py` + cross-ref the
3 split files' stub sets to enumerate it; `.run/diag_a.py` is the artifact-safe per-fn diff for `_a.c`.)

**What's BUILT (validated):**
- **`dedup_propagate.py` is split-aware** — `overlay_files(ov)` returns `[(main.c, ov), (_a.c, ov_a), (_o0.c,
  ov_o0)]`; source def-finding scans all (`source_text`), the member loop edits whichever split file holds each
  target's stub/def (per-file asm-subdir regex), the structural check spans all files. Single-file overlays are
  unchanged (default path). Validated: source-find locates `_a.c` defs (`--check-only` → 134 members); fail-path
  reverts correctly. (Success-path ×134 of an `_a` fn still pending a clean propagatable+matchable `_a` fn — the wave.)
- **`cast_call_sites.py --src-file <file>`** — canonicalize callee decls against the file the draft LANDS in, not
  main `.c`. **Why it's needed:** a callee can be declared *differently in main vs `_a.c`* (cross-file loose
  typing, e.g. `RotTransSV`), so canonicalizing against main injects a decl that conflicts with `_a.c`'s. Pass
  `--src-file src/ov_SC01_077/ov_SC01_077_a.c` for `_a` drafts. (Default = main, unchanged.)

**The WALL (honest — the `_a` vein is NOT a clean win):** propagation/matching of `_a` fns hits the SAME §16/§20
loose-typing wall as everywhere, in fresh form:
- **Cross-overlay def-conflict → ×1, not ×134.** `func_8012C098` matched in `_a.c` (cast-recovered: a callee
  `func_8012C218(void*)` called 0-arg via `((void(*)(void))…)()`), but a *banked caller in another overlay*
  (engine_core.h DEFINE) declares it `extern void func_8012C098(void)` while the body USES `param_1` → the
  propagated macro's def conflicts there → `dedup_propagate` (all-or-nothing) reverts. Irreducible (no single C
  sig fits a param-using body + a 0-arg caller decl). Banks ×1 only.
- **Within-`_a` loose-typed callee.** `func_8012F274` (decls=0, *would* propagate freely) won't even match:
  `RotTransSV` is declared inconsistently *within `_a.c`* → any single extern conflicts; needs the per-site cast,
  which `cast_call_sites` only applies when the canonical differs from the draft's intent (here it picked one and
  it still clashed with another site). A genuine multi-sig callee.
- **`sig_unify` still drops `_a` fns** (its `cur_stubs`/decls read main `.c` only) → for `_a` waves either give it
  the same `--src-file`/split-awareness or run `canon → cast --src-file → gate` (skip sig_unify; the cast class
  banks, the def-side class is a wall anyway). NOT yet done.

**Net / next:** the enabler tooling is built + safe (fail-closed); the `_a` vein is matchable but its ×134 yield
is loose-typing-limited (unknown fraction are ×1 walls). The proper measurement is a **worker wave** over the
`_a` pool (parallel agents match bodies; the byte-gate + split-aware propagate sort ×134 vs ×1) — needs
`wave_targets` `_a` support + `sig_unify` `_a`-awareness (or skip it). Decide whether the uncertain yield
justifies the wave vs pivoting (the wall is the same as the main vein's).

**UPDATE (cont.6): `sig_unify --src-file` is now BUILT** (closes the open item above). `sig_unify.py --src-file
src/ov_SC01_077/ov_SC01_077_a.c` reads `cur_stubs` + inline/extern canonical sigs from the split file (not the
main `.c`), so `_a`/`_o0` drafts are no longer dropped and DO get the def-side arity-adopt recovery. Validated:
21 `_a` drafts unified WITH the flag vs 0 without; the `_a` close=0 recovery wave then banked func_8012F568 ×134
(commit:0277). `gate_stage` passes `--src-file` to BOTH `cast_call_sites` and `sig_unify` now. See §25 for the
canon-first two-stage gate that makes this safe (sig_unify must be a FALLBACK, not unconditional).

## §25 — The "schedule" class is mostly COALESCING (pin-crackable), not scheduling; + the gate two-stage + h_exact over-counts ×134 (Phase 21, cont.6)

`idiom_loop.py --assess` named **`schedule`** (50 "reach-134", median 15 ins off) as the next idiom. Cracking its
lowest-closeness reach-134 exemplar **func_80128ED8** (close=3) surfaced three durable lessons.

### The crack: the residual was gcc-2.7.2 COPY-COALESCING, not the instruction scheduler
`match_one` diff (3-off): MINE `move $a3,$v1 / sll $v0,$a3,3 / addu $v0,$v0,$t0` vs TARGET `sll $v0,$v1,3 /
addu $v0,$v0,$t0 / addu $a3,$v1,$zero`. The "schedule" label was misleading: gcc COALESCED the index-preserve
copy (`idc = idx`) into the multiply operand (`sll` on the copy `$a3`) instead of multiplying `$v1` directly,
and routed `idc+1` back through the copy's reg. Two **§17 register pins** fixed it (byte-gated, `match_one`
MATCH 53/53):
1. **Pin the preserve-copy to its TARGET register** (`register s32 idc __asm__("$7")` = `$a3`): gcc can no longer
   fold it into the multiply operand → the multiply uses the original `$v1` directly and the copy emits
   SEPARATELY after it. (3-off → 2-off.)
2. **Route the copy's dependent arithmetic through a dead, target-scratch-pinned temp** (reuse an already-dead
   `register __asm__("$2")`=`$v0` pseudo: `cnt = idc + 1; store cnt;`) → the result lands in `$v0` (the target's
   scratch), not back in the copy's reg. (2-off → MATCH.)
**Triage rule:** on a small "schedule" residual, read the `match_one` diff FIRST. A *copy emitted before its
source's other use, with that use reading the copy's register* = COALESCING → pins (cookbook §17), crackable.
Don't assume the scheduler.

### The genuine scheduler — `rank_for_schedule` (sched.c), for when it IS scheduling
gcc-2.7.2's ready-list tie-break order (sched.c, byte-read R17): **(1) PRIORITY** = dependency-chain height to
end-of-bb (longest chain first); **(2) CLASS vs `last_scheduled_insn`** — prefer class 3 (independent / latency-1)
over class 1 (data-dependent on the last insn) — i.e. gcc fills an address-gen→load gap with an INDEPENDENT insn
(this EXPLAINS the "copy fills the slot before the `lw`" schedules the targets show); **(3) LUID** = original
SOURCE ORDER (the stable final tie-break). LEVER for the genuine equal-priority case: reorder the SOURCE
statements (the LUID tie-break — same family as §10's operand/statement-order idioms). When priorities differ or
coalescing intervenes, source-reorder alone won't flip it → use the pins above.

### The genuine schedule WALLS (do NOT re-grind — stub)
- **§10 cross-jump / delay-slot merge** (func_8014FD54, close=2): two `return 0` paths — the target keeps them
  SEPARATE (one fills the inner `beqz` delay slot with `move $v0,0`, one is a standalone zero block); our cc1
  cross-jump-MERGES them → the inner `beqz` gets a NOP delay slot. The §5a `:::"memory"` barrier breaks the merge
  but overshoots +1 (41 vs 40). No C-source form reaches the merged-with-delay-slot-fill schedule. (§10 Residual-B.)
- **store-vs-load placement** (func_8014F2E0/func_80150528, §20-confirmed): the store schedules between two
  arg-loads, mutually exclusive with base-preservation. Stub.

### h_exact OVER-COUNTS ×134 — verify shareability before crediting a class's "reach-134" (R14)
func_80128ED8's crack is byte-identical in ov_SC01_077 but **does NOT propagate ×134** — `dedup_propagate --addr
0x80128ED8` (alone, no stragglers) still `[drop]`s it at ov_SC01_000: a cross-overlay byte-gate reject. So it
banks **×1**, despite `sig_image` h_exact reporting `members=134`. **Why:** h_exact is RELOCATION-MASKED (the
`%hi/%lo` of unresolved syms are 0 in the object), so it matches across overlays that the shared-C macro then
can't reproduce byte-identically (overlay-local data/decl differences — the §24/§20 wall). **Consequence for the
idiom-loop model:** `--assess`'s per-class "reach-134" count (from the backlog's `reach` field = h_exact) is
OPTIMISTIC; a cracked fn's real leverage can be ×1. **Before committing a token-heavy wave to a class, probe
×134-shareability on the cracked exemplar** (`dedup_propagate --addr <fn>`), not just the h_exact count. The
"schedule" class is therefore NOT a confirmed ×134 vein — its closest reach-134 exemplars are one ×1-coalescing
crack + one §10 wall.

### The gate two-stage — sig_unify is a FALLBACK, not unconditional (`gate_stage.py`, §19 folded in)
`gate_stage` ran canon→cast→sig_unify in ONE pass. sig_unify REGRESSED the func_80128ED8 crack: it rewrote the
byte-correct def `s32 f(s32,s32*)` → a banked caller's canonical `void* f(void*,void*)` → gate reject (the raw
draft banked fine via `harvest_verify`). Fix (the §19 "canon-first" design, now IN `gate_stage`): **stage 1** =
canon+cast → byte-gate (already-correct drafts, incl. hand-pinned cracks, bank here); **stage 2** = sig_unify
ONLY the stage-1 failures → re-gate (def-side near-misses recover) — never regressing a stage-1 winner.
`harvest_verify` reads the CURRENT src as baseline, so verified fns ACCUMULATE across the two gate calls (a
stage-1 winner is no longer a stub for stage 2). This is mandatory now that hand-pinned self-contained cracks
flow through the same gate as recovery drafts.

## §26 — The cheap close=0 recovery lever is EXHAUSTED; `idiom_loop --assess` was DOUBLY inflated (Phase 21, cont.7)

cont.6 left two "do this FIRST each cycle" cheap levers: the `_a` close=0 recovery (validated on one fn,
func_8012F568 ×134) and `idiom_loop --assess`'s "51 close=0 reach-134 fns → ×134 for ~0 tokens." cont.7 ran the
`_a` lever to completion and probed the assess. **Both were over-promises; the cheap recovery fuel is dry.**

### The `_a` close=0 recovery banks 0/20 — same def-side wall as MAIN (0/40)
Re-gated the 20 still-stubbed `_a`/`o0` close=0 reach-134 fns through the cont.6 fixed pipeline (`gate_stage
--src-file`, canon-first two-stage; `sig_unify --src-file` fired on all 20). **banked 0.** match_one calls them all
"MATCH" (close=0) but the whole-binary gate rejects every one — the §16/§20 **DEF-side multi-way loose-typing
wall**: the draft's byte-correct def needs a C type that conflicts with a banked caller's canonical decl, and no
single C sig fits both (sig_unify's arity-adopt only fixes the simple-arity case — cont.6's func_8012F568 was
that lone case; the rest are genuine multi-type conflicts). Caller-side fix is blocked (INCLUDE_ASM declares no
symbol, §20). **Conclusion: close=0 + already-recovery-gated = a WALL, not fuel — do NOT re-run recovery on it.**

### `--assess` was inflated TWO ways (now fixed) — verify reach AND closeness before crediting a lever
The assess named "51 close=0 reach-134 → ×134 for ~0 tokens." Two byte-proven inflations (R14/§25 family):
1. **`reach` = masked `h_exact` distinct-overlay count → OVER-counts the real ×134** (§25: func_80128ED8's
   `--check-only` plan says `members=134` but real propagation is ×1). The "reach-134" label is a CEILING.
2. **`load_backlog` didn't drop banked-since-logged fns** (the ledger keeps stale status `near` for a fn matched
   in a later session — e.g. func_8016EDEC/EE40 banked in cont.6's Option-C still counted). And the close=0
   "lever" counted fns already recovery-gated-and-failed (the §16/§20 wall) as if fresh.
**Fix (`tools/idiom_loop.py`, cont.7 — R16 flywheel, so the next session doesn't re-burn the lever):**
- `load_backlog` now intersects the ledger with the live `INCLUDE_ASM` stub set (`_open_stubs()`, mirrors
  `backlog._matched_now`) → drops every banked-since-logged fn (the same drop-now-matched P9 honesty
  `backlog.render` applies). This alone removed the bogus "unknown 14" class + ~10/class of stale-matched inflation.
- The DETERMINISTIC-RECOVERY line now splits **FRESH** (never recovery-gated `recover-*` source = genuine
  ~0-token fuel) vs **WALLED** (already recovery-failed = the def-side wall, "do NOT re-run"). Post-fix:
  **0 fresh, 46 walled.** The cheap lever is genuinely empty.
**RULE:** before trusting an assess class/lever, the live numbers are: real reach = `dedup_propagate --addr
--check-only` is still h_exact (a ceiling) → the only truth is the gate; real closeness = re-measured through
the gate's canon/cast/sig_unify transforms (the stored ledger closeness is optimistic — stale records read 0
where the live residual is 30–41). h_exact over-counts the numerator, stale-ledger under-counts the denominator.

### Where this leaves the reach-134 tail (cont.6 option-3, now CONFIRMED byte-backed)
The cached reach-134 cheap fuel is dry: close=0 recovery = 0 fresh (46 walls); the codegen classes that look
tractable are h_exact-inflated (schedule "39 reach-134" but the cracked-exemplar ×134 fraction is ~50% on n=2 —
func_8012F568 ×134 / func_80128ED8 ×1 — at median 15 ins off = expensive per-fn pin work, poor ROI; do NOT wave
it on the inflated count, §20 "don't wave a wall"). **The remaining levers are all token-heavy fresh-session
work:** (a) the GIANTS (8 reach-134 >150 ins — the byte-weight lever, ~3% auto-yield so mostly hand-finish/backlog
fuel, Phase-16); (b) per-fn pin-cracking the genuine codegen near-misses (schedule-coalescing §25 / regalloc-order).
**REFUTED — the "resolved-reach probe" (cont.7b, R14 self-correction):** I proposed comparing per-overlay
*linked* `.text` to get a real ×134 count. **It doesn't work, because `sig_image`'s `h_exact` is ALREADY
`SHA1(raw image bytes)` — UNMASKED** (sig_image.py:170-171; `h_norm` is the masked tier). So `reach` is the
ACCURATE shipped-byte reach; a resolved-byte probe would just reproduce it. The §25 "h_exact over-counts" wording
conflated two different hashes — the IMAGE `h_exact` (accurate) vs the match_one/draft OBJECT masking. **The real
gap is `reach` (shipped bytes identical) ≥ realizable-×134 (shared-C macro reproduces all N):** func_80128ED8's
shipped bytes ARE identical ×134, but its matched C can't propagate (a callee/decl/loose-typing wall in the
shared-C representation, §16/§20/§24). **That gap is measurable ONLY by `dedup_propagate`'s byte-gate on an
ALREADY-MATCHED fn** — there is no cheap static probe. Don't build the resolved-reach tool.

**The close-N tail can be PERMUTER-achieved, not source-close (cont.7b, R14):** the backlog `closeness` is the
BEST achieved (often by the grinder's randomized regalloc/scheduling permutation), NOT the saved draft's
source-compile distance. func_801775E0 logs `close=1` but its saved `best_draft` compiles **31-off from source**
(prologue save-SCHEDULING, branch-sense, block-order all differ — the §20 regalloc/schedule wall); the close=1 was
a permutation the source doesn't capture. **RULE: before assuming a cheap source crack on a close-1..4 backlog fn,
`match_one` its saved draft to get the SOURCE closeness** — if it's far-off, it's a permuter-class wall (grinder
territory), not a pin target. The genuinely pin-crackable ones are source-close + a single coalescing/CSE residual
(§25 func_80128ED8); the regalloc/save-schedule/cross-jump ones are the confirmed walls (§20/§25).

## §27 — Giant matching recipe (Phase 21 cont.7b — validated on func_80176D94, 152 ins)

Giants (reach-134 >150 ins) are the byte-weight lever. Validated approach (func_80176D94 → structurally matched,
calls/constants/GPU-packet all byte-correct, residual = pure regalloc):
1. **Start from the cached Ghidra-C** (`.run/ghidra_c/<fn>.c`) — giants are often CLEAN (straight-line + many
   calls, no deep control flow), so the body structure comes nearly free. (cont.2's "stale+incomplete drafts"
   were the OLD m2c drafts vs the grown header; the fresh Ghidra-C + canonical context is the fix.)
2. **Arg-arity is the #1 giant blocker (the manifest's `MCOMPILE_arg-arity` bucket).** Giants call many helpers;
   m2c/Ghidra miscount args. Declare each callee to match the ACTUAL call site — count the `$a0–$a3` (+ stack)
   set before each `jal`, NOT the canonical sig. e.g. `func_80177784` canonical is 4-arg but called **3-arg**
   here (`$a3` untouched) → declare `func_80177784(void*, s32, s32)`. (The shared-header canonical conflict is the
   gate's job — `cast_call_sites`; it may bank ×1 if irreducible, §24.)
3. **Sibling templates.** Giants cluster in families (GPU-packet builders, coord transforms). Find an
   already-matched sibling `DEFINE_func_*` in `engine_core.h` with the same idiom and mirror its PROVEN C form —
   e.g. the GPU-coord strength-reduce `((s32)(D * 10355) << 1) >> 16` (sibling func_80176FF4) and the GPU
   linked-list pointer `((u32)addr & 0xFFFFFF) | 0x3000000`.
4. **§17 register pins for the regalloc-SHIFT.** Giants use 5–7 callee regs; gcc's mapping often shifts whole-hog
   (param→$s0 where target uses $s2, etc.). Pin the long-lived vars to their target regs
   (`register T v __asm__("$NN")`). **CAVEAT (cont.7b, byte-proven): do NOT pin a var whose register the target
   REUSES for a later spill** — pinning reserves the reg for that var's whole scope → blocks the reuse → gcc grabs
   a FRESH callee reg (+1 reg, +2 prologue ins). (func_80176D94: pinning uVar5→$s0 blocked the accumulator from
   reusing dead $s0.)
5. **The giant residual class — accumulator-spill coalescing.** A value chained through `$v0→$a0` across calls,
   then needing to survive a LATER call, must spill to a callee reg. The target reuses a now-DEAD callee reg; gcc
   from natural C grabs a FRESH one (+1 reg). Hard to force from C (it's gcc's coalescing graph) → **permuter
   fuel** (the grinder randomizes allocation and may find the reuse). func_80176D94's saved draft
   (`.run/backlog_drafts/`) is exactly this — structurally done, 1–2 callee regs from byte-perfect.
**Net:** giants reach STRUCTURALLY-MATCHED fast (steps 1-3); the last mile is regalloc-coalescing (step 5) — so
giants are ISOLATED-AGENT + permuter work (per `breadth-isolated-agents-not-serial`), not main-loop serial grind.

**WAVE RESULT (cont.7d — the honest yield, R14/P9): a 6-giant worker_wave banked 0.** The agents reached the
SHAPE (the §27 recipe works — bodies/calls/constants/control-flow right) but the whole-binary byte-gate rejected
all 6: 1 was close=0 match_one-MATCH yet gate-REJECTED (func_8014F74C — no callee/data conflict, so match_one
OVER-predicted: the masked standalone match hid a real residual, §25), 1 wouldn't compile whole-binary
(func_80144090, agent-claimed "154/154" but a decl the gate couldn't reconcile), and 4 were genuinely far
(close 53–164 — the agents' "structural match" self-claims were match_one-optimistic). **This confirms cont.2 /
Phase-20 / Phase-16 (~3% wall): giants do NOT auto-bank** — even with the §27 recipe + isolated agents, the
whole-binary gate (masked-residual + plumbing + large regalloc) blocks them. **Giants are HAND-FINISH / backlog
fuel** (the wave's deliverable is 6 RANKED near-miss drafts for human sessions, NOT banks). Do not scale giant
auto-waves expecting %; the automated reach-134 harvest is COMPLETE at this fleet level (every automated lever —
cheap recovery, permuter, giant auto-wave — banks ~0). Forward % = hand-finishing (Drew) or closing the phase.

**Frame-pressure-locked residuals are PERMUTER-ONLY (cont.7d, byte-proven on func_8014EA4C, close=6).** When a
giant's matched body needs a frame-forcing HACK to hit the right stack size — e.g. a DEAD `u8 buf[16]; memcpy(buf+16,
src, 8)` (an out-of-bounds copy whose only job is to force frame 0x60) — its remaining schedule/regalloc residuals
become PRESSURE-LOCKED: any C edit that would steer them (materialize a temp to reorder a store/load; a ternary or
`s32` retype of an abs; a register pin) shifts register pressure → gcc DROPS the dead buffer → frame shrinks
(0x60→0x58) → whole-function offset cascade (close 6 → 23–123). Two hand attempts both cascaded exactly as the
drafter predicted. **The fix is NOT C-steering — it's the decomp-permuter** (the grinder): it randomizes
regalloc/scheduling via semantics-preserving C perturbations the byte-gate scores, exploring the frame-PRESERVING
space the hand-edits can't. Re-log such giants with their true closeness + raw draft (`source=giant-raw`) so the
grinder (close≤30) picks them up; do NOT hand-grind them.

**Deep frame-RE does NOT crack a scheduler-walled giant (cont.7d, byte-proven on func_8014EA4C).** Drew chose
"deep re-RE the real frame so regalloc resolves." The RE finding: the frame is a **dead aggregate copy** — 8 bytes
of a param unaligned-copied (`lwl/lwr`→`swl/swr`, char-aligned dest) to a stack local at sp+0x20 that's NEVER read
(gcc-2.7.2 keeps it — no DSE for aggregates). The drafter's `u8 buf[16]; memcpy(buf+16, a2, 8)` (copy PAST the
array) is a PRECISE reproduction of the exact gcc stack layout — `local[0x38]` or any "robust" remodel produces a
DIFFERENT frame (0x88, copy at 0x30). So the frame is already correct at close=6; **the residuals are NOT
frame-caused** — they're loop-body scheduler (a global store vs a call-arg load order) + regalloc (abs in $v1 vs
in-place $v0), the irreducible §20/§25 wall. **Lesson: when a giant's residual is loop-body schedule/regalloc,
deep frame-RE is a dead end — only the permuter explores that space.** Net for Phase 21: **5 levers
(cheap-recovery, permuter, giant-wave, hand-finish, deep-RE) are byte-proven exhausted at fleet 63.17%** for the
reach-134 tail; the residual is the gcc-2.7.2 scheduler/regalloc wall, addressable only by the (low-yield) permuter
or by accepting it as the matching ceiling at this fleet level.

## §28 — Banking a "close=0 gate-rejected" giant: the canonical-extern recovery (Phase 22 T1, byte-proven on func_8015126C ×134)

Phase-21 (§25/§27 cont.7d) logged a class of giants as "close=0 (match_one MATCH) but gate-REJECTED" and treated them ALL as masked-residual/permuter fuel. **That was incomplete (R14).** A close=0-gate-rejected giant is one of FOUR distinct walls — and one is deterministically bankable BY HAND:

1. **PURE-EXTERN PLUMBING (bankable — the NEW lever).** The draft's self-contained **file-scope** externs conflict with engine_core.h's canonical decls (the giant calls already-matched engine fns; the draft guessed their sigs, e.g. `extern void func_8015173C(void*)` vs canonical `void func_8015173C(s32*)`). match_one's isolated compile (own externs) MATCHes; the whole-binary TU fails to compile (`conflicting types for func_X`). `sig_unify`/`cast_call_sites` do NOT canonicalize these (the gap that stranded them). **Fix = `tools/recover_giant.py`:** for each callee with a `DEFINE_func_X()` in engine_core.h, rewrite the draft's extern to that macro's exact def-sig; then move ALL externs (callee + `D_` data) **block-scope** (inside the body, after `{`). `find_site`/`compiles_standalone`/`dedup_propagate` lift the body + its *internal* externs as one unit — **file-scope externs are excluded from the lifted body → false "not self-contained" skip.** Forward-refs (higher-addr callees) MUST stay declared. Then `harvest_verify` → `dedup_propagate` ×134.
2. **MASKED RESIDUAL (permuter fuel).** Compiles whole-binary but bytes differ — the relocation-mask hid a real codegen diff (func_8014F74C, §25). The recovery won't help → grinder.
3. **STRUCT-WALLED (type reconciliation).** The draft uses a local named `struct S8`/`B8` (the array-of-struct %lo idiom, §18) that collides with the TU's other defs (`conflicting types for S8`) — func_80156B74/func_8014F74C/func_80163C2C. Needs the type lifted to `engine_types.h` (named once) or rewritten anonymous/raw-cast. Not near-free.
4. **REGRESSED DRAFT.** The saved best_draft was clobbered by a later worse attempt (func_80178004: worklist close=0 but saved draft is DIFF 91). Re-derive.

**Triage:** `recover_giant.py` → `match_one` (DIFF → #4) → whole-binary build. byte-identical → #1 banked · `conflicting types for func_X` → was-#1, recovery fixes · `conflicting types for <Type>` → #3 · compiles but bytes differ → #2. **Honest yield:** of the 5 close=0 giants, only func_8015126C was #1 (pure-extern); the rest are #2/#3/#4 — the canonical-extern lever is real but the close=0-giant group is NOT uniformly near-free.

**The coalescing pin (extends §25 — func_8015126C's last mile).** The `(s16)p[0x79] != 1000` compare temp wanted `$a0` (coalesced with the soon-to-be-angle arg); gcc gave `$v1`. An eager named temp forces `$a0` but HOISTS the load (+95 ins). Fix — pin AND keep the load lazy inside the `&&`:
```c
register s32 cmp __asm__("$4");                       /* $a0 */
if (cond1 && ((cmp = *(s16*)(p + 0x79)) != 1000)) { ... }
```
The in-`&&` assignment stays inside the short-circuit (not hoisted) yet lands in the pinned reg. Reusable for any coalesced-compare-temp residual.

**Op gotchas (Phase 22 T1):** run `dedup_propagate` in the **BACKGROUND** (134 builds > the 2-min foreground cap; a SIGTERM/interrupt leaves a non-atomic partial state — macro+instantiations applied, registry unwritten). And `git checkout src/` does **NOT** revert `config/dedup.us.yaml`, so on a redo reset BOTH (`git checkout src/ config/dedup.us.yaml`) or `registered_addrs()` stays dirty and re-skips the function as "already shared."

### §28a — decomp.wiki GCC patterns worth trying on BFM giants (decomp.wiki/compilers/GCC, raw at decompals/decompedia; PS1-applicable subset)
- **Negative struct offsets in loops** — `for (i=…; …; i++, p++)` makes gcc *advance* the pointer + use negative member offsets instead of offset-folding. Directly targets func_801412A8's "OFFSET-FOLDS the 4× prim stores instead of ADVANCING $t6" residual.
- **Branch-invariant code duplication** — when gcc hoists a shared tail (a call) out of two branches and swaps regs, *duplicating that tail inside both branches* fixes the regalloc. An alternative to §17 pins for the call-crossing swap class.
- **Load coalescing** — adjacent struct fields compared together (`if (t->a || t->b)`) fold into one `lw` (+lui/ori/and mask when <4 bytes). Recognition aid for engine code.
- **div-by-constant magic table** (0x66666667→/10, 0x55555556→/3, …) + **s16/s8 div-by-2** sign-extension forms; **gcc-2.7.2.x** `slti …,0` ⇒ `(x & (1<<31)) != 0`.
- **N/A to PS1** (don't chase): `bnel`/likely branches (MIPS II+; R3000 has none), `.lit4` float-literal NOPs (PS2), C++ `bool` load/store (BFM is C).

### §28c — The close=0 recovery is NOT fully exhausted (§26 corrected, R14); + the dedup_propagate registry-skip recovery (Phase 22 T2)
**§26 said "the cheap close=0 recovery lever is EXHAUSTED."** That was over-broad (R14). Re-running `recover_giant.py` (canonical-extern + block-scope) + the whole-binary gate over the **still-live close=0 reach-134 set** (match_one MATCH, gate-rejected) banks a real **~15-20% tail** the prior waves left — Phase 22 T2 banked **7** this way (func_80156ECC, func_80147E44, func_8015ADB0, func_801661CC, func_80166054, func_8012CFA8, func_8012A62C) out of ~43 candidates. The rest (~33) ARE the genuine DEF-side loose-typing / masked-residual wall (§20/§26 holds for THEM). Two enablers this session: (a) the §28b type-lift put more shared types in engine_types.h (so `compiles_standalone` passes for more bodies); (b) `dedup_propagate --auto-from` then propagates not just the new banks but **pre-existing inline-matched-but-never-propagated** functions for free (7 bonus this session — always run `--auto-from` after a harvest_verify batch to sweep them). **Recipe:** survey live close=0 reach-134 (`fuel_manifest.targets` ∩ backlog closeness==0) → `recover_giant` each (strip local struct typedefs first; lift shared ones per §28b) → batch `harvest_verify --chunk N` per region (main / _a, distinct `--src`/`--asm-subdir`) → `dedup_propagate --auto-from` → `make check-all` (the sole arbiter).

**The dedup_propagate registry-skip + its recovery (byte-proven, recurring).** A full `dedup_propagate` run (long byte-gate loop = 134 builds) sometimes ends with the **source propagated (DEFINE macro + ×134 instantiations) but `config/dedup.us.yaml` partially/un-written** (the long loop appears to get killed before/within the register step; the run still reports exit 0). Symptoms: `check-all` 136/136 (bytes correct) but `dedup-check`/`progress.py` under-count (group absent). **Recovery (do NOT revert — the bytes are right):** the tool can't re-register an already-propagated fn (`--auto-from` needs inline-def; `--addr` needs a non-macro site), so register directly via its own helpers — for each addr: `h = load_sig('ov_SC01_077')[addr]['h_exact']` (stable: bytes unchanged), `members = [ov for ov in onboarded_overlays() if load_sig(ov).get(addr,{}).get('h_exact')==h]`, then `append_groups([dict(id=f"E_{sym(addr)}", tier='h_exact', hash=h, source='src/shared/engine_core.h', addr=addr, members=[{'binary':ov} for ov in members])])` (idempotent by id — safe to re-run). Verify with `dedup_integrate.py --check`. **Prevention TODO:** make dedup_propagate write the registry BEFORE the byte-gate loop (or add a `--register-only` mode for already-propagated addrs).

### §28b — The struct-walled close=0 giant (§28 case #3) IS bankable: the engine_types.h type-lift (Phase 22 T2, byte-proven on func_80156B74 ×134)
§28 case #3 ("STRUCT-WALLED — needs the type lifted… **Not near-free**") was too pessimistic — it IS near-free once you do the lift, and the lift unblocks the whole class (every giant sharing those types, including already-banked-but-LOCAL ones via the §19 propagation cap). Recipe (byte-proven on func_80156B74, 214 ins, ×134, fleet 63.22→63.25%):
1. **Identify the draft's named struct/typedef types** (e.g. `typedef struct {s16 a,b,c,d;} S8;`, `B8`, `Blk16`, `Buf32`). These are why the draft was struct-walled: a close=0 draft that re-`typedef`s a name already in its TU = C89 duplicate-typedef → `conflicting types`; and a body containing a `typedef`/named-struct can't be lifted (`dedup_propagate` skips it, line ~366).
2. **Lift the typedefs to `src/shared/engine_types.h`** (defined ONCE; reaches all 136 binaries via `engine_core.h`'s include). Gotchas: a typedef NAME (`S8`, ordinary-identifier namespace) legally coexists with an unrelated struct TAG (`struct S8`, tag namespace) — gcc-2.7.2 accepts both; check for a layout-identical existing type first (e.g. `B8` ≡ the pre-existing `Blk8`) and keep the draft's name to avoid churning already-matched siblings. **Remove the now-duplicate file-scope typedefs from `ov_SC01_077.c`** (the per-function prelude block) or the lifted def collides.
3. **Verify the lift is BYTE-NEUTRAL** before touching the giant (R22): rebuild the binaries whose already-matched fns use those types (the prelude's owner fn, e.g. func_80156848) + 1 overlay + resident → all must stay byte-identical. Typedefs emit no code; only a name collision can bite.
4. **Strip the typedefs (+ any `#include`) from the draft → `tools/recover_giant.py`** (it canonicalizes the engine_core.h-callee externs + block-scopes ALL externs, so the body is self-contained for ×134 with its types coming from the shared header). recover_giant strips only SCALAR typedefs — remove the struct ones yourself first.
5. **match_one caveat:** match_one compiles standalone WITHOUT engine_types.h, so the recovered (typedef-free) draft won't compile there — that's a harness limitation, not a defect. Confirm the MATCH on the ORIGINAL self-contained draft (with its own typedefs); gate the recovered draft with the **whole-binary** `harvest_verify` (which includes engine_types.h via engine_core.h — the real arbiter, G3/P9). Then `dedup_propagate --addr 0x… --source-overlay ov_SC01_077` (BACKGROUND, §28).
6. **Op gotcha (Phase 22 T2, byte-proven):** do NOT run a second `make`-invoking job (`make check-all`, `make report`) CONCURRENTLY with `dedup_propagate` — parallel make corrupted a partial `.o` (`file format not recognized` on ov_SC04_016, caught by check-all + cleared by a clean rebuild). Serialize all make jobs. **NOTE (corrected — §28c):** the propagation's registry-skip (source propagated but `config/dedup.us.yaml` group unwritten) is a SEPARATE recurring issue **independent of concurrency** (it recurred with NO concurrent make on func_80163C2C) — see §28c for the byte-proven recovery; re-running `dedup_propagate` does NOT re-register an already-propagated fn.

### §28d — The "macro-extern-injection" lever: freeing reach-134 inline matches dedup_propagate skips as "not self-contained" (Phase 23, `tools/inject_capped_externs.py`)
The Phase-20 backlog flagged a set of **reach-134 functions matched INLINE in ov_SC01_077 but never propagated** (`dedup_propagate --auto-from` reports "N not self-contained (local types)") — a pure **propagation cap**, not a codegen wall (their bytes are already byte-correct in 077). Phase 23 surveyed them: **29 such reach-134 fns in 077** (main + `_a`). Root cause (byte-diagnosed by running each lifted body through `compiles_standalone` = common.h + engine_types.h): `find_site` lifts only the function DEF (+ *contiguous* preceding externs), but 077.c declares the callees/data at FILE scope, so the lifted macro body has undeclared `func_X`/`D_X` in every other overlay. The classes (run the diagnosis — they are NOT uniform, R14):
- **callee/data extern-undeclared (the clean majority)** — inject the EXACT file-scope `extern …;` the overlay already declares for each referenced symbol, BLOCK-scope (just inside `{`). Byte-neutral (block vs file scope = same codegen; the gate proves 077 stays `d19c9580…`). `compiles_standalone` then passes → `dedup_propagate --auto-from` lifts it ×reach. **`tools/inject_capped_externs.py`** does exactly this, fail-safe (only rewrites a fn if the injected body then `compiles_standalone`; never churns one that still won't propagate). Phase-23 result: **8 freed from `ov_SC01_077.c` main** (each reach-134), 077 byte-identical, propagated ×134.
- **split-file (`_a.c`/`_o0.c`)** — same fix, run the tool with `--src-file src/ov_SC01_077/ov_SC01_077_a.c` (10 of the 29 live there). (`_o0.c` defs are overlay-LOCAL, §18/§20 — never auto-propagate.)
- **missing-extern** — the referenced callee has NO file-scope extern in 077.c (077 builds via gcc's implicit declaration); inject a no-proto `extern <ret> func_X();` (the call-site cast gives the shape) — a tool extension, lower yield.
- **type-walled** — the body references a struct/typedef not in `engine_types.h` (`Buf`, `Vec3`, `Loc`, a PsyQ `MATRIX`); needs the §28b `build_engine_types.py` type-lift first (and the type must actually be inline-defined in 077.c — a PsyQ type needs its header, not a lift).
**Pipeline:** `inject_capped_externs --apply` → `make build BINARY=ov_SC01_077` (gate `d19c9580…`, else revert) → `dedup_propagate --auto-from ov_SC01_077 --min-reach 2` (BACKGROUND, serialize make, §28). The whole-binary byte-gate is the sole arbiter (G3/P9): a wrong injection can't pass. **The lever compounds (R16):** every future LLM/agent inline bank of a shared fn that references file-scope symbols is freed the same way — run the injector before propagating.

## §29 — Reasoning-model (GLM5.2) DEF-side reconciliation idioms + the wall's hard limit (Phase 23 T10.7, `tools/glm_reconcile.py`)
The T10.7 OpenRouter A/B found GLM5.2 is **~10× better than v3 at hard-band CODEGEN** (10/18 vs 1/18 match_one on 16–22-ins `ov_SC01_077` struct-core fns) — but the **DEF-side loose-typing wall** (§20, Phase 16/20) caps *banking* at 4/18 regardless of drafter, because the conflict is *overlay-forward-decl-vs-the-fn's-true-signature*, independent of who writes the body. Aiming GLM's REASONING directly at the wall (`glm_reconcile.py`: body + the conflicting TU decls + this toolkit → a consistent byte-identical decl set; reasoning captured to `.run/glm_reason/` for R16) banked only **1/7** stranded; mechanical `fix_arity_callers --any-proto` **0/7**. **Verdict: the wall is INTRINSIC** — a frontier reasoning model with the full toolkit cracks ~1/7. GLM's *reasoning* is nonetheless expert-grade and the durable value; the byte-neutral reconciliation idioms it articulated (validated by the gate):
- **Match a pointer PARAM's type to the TU's existing forward-decl** (`void*` def-param → `s32*` when the TU declares `func_X(s32*)`): both 32-bit, body casts work identically, byte-neutral — resolves `conflicting types` without relaxing anything (banked `func_80175184`).
- **Call-site cast for a value mismatch**: passing an `s32*` to a `func_Y(s32)` → `func_Y((s32)arg0)` — same 32-bit value in `$a0`, gcc emits NO conversion, byte-neutral.
- **Cast a callee that is a DEFINITION (not a forward-decl, so un-relaxable)**: `((R(*)(A))func_Z)(args)` — the §17a-1 cast idiom, which GLM derived independently.
- **Match a DATA extern's type to the TU's** (`int` vs `u32` at the same width → identical loads/stores; pick the declared one).
- **The HARD limit (why 6/7 fail):** a def with a **narrow-scalar param by value** (`u16`/`s16`/`u8`/`s8`/`char`/`short`/`float`) can't be no-proto-relaxed (K&R default-promotion changes the ABI) AND often can't match the TU's incompatible prototype — this is the irreducible narrow-param wall (§17-stop); GLM correctly diagnoses it (`u16` params emit `sh`; widening to `s32` would emit `sw`) but cannot dissolve it. **Strategic read:** GLM's role is (a) a $0.03–0.08/fn direct drafter for the def-conflict-FREE hard band (~22%, which v3 can't touch), and (b) an idiom TEACHER (capture `reasoning`, distill here + into corpus) — NOT a wall-breaker. The real lever past the wall is community labor (the public flip, Fable5 review §4.3), not a bigger model. **← §30 CORRECTS THIS for a model that reads the gcc SOURCE.**

## §30 — Fable5Max cracks §20/§10 "unsteerable" from the gcc SOURCE: store-vs-load is a `/s` aliasing flag, the def-side wall has a macro escape, + the birthing-boost (Phase 23, byte-proven on giant `func_8014EE14` 248 ins ×134)
A single **Fable5Max** agent (an `Agent` with `model: fable`, given the target asm + `tools/ghidra_c/` + this cookbook + the `match_one`→`gate_stage` loop) matched a 248-ins reach-134 GIANT on the §20/§10 store-vs-load wall — the class 22 phases of Opus/GLM called **"CONFIRMED unsteerable"** — by **reading the actual gcc-2.7.2 source** (`tools/reference/gcc-papermario`) with `-da` RTL dumps. It banked ×134 (leaf `MATCH (248 ins)`; whole-binary `banked:1`; `check-all 136/136`; `dedup-check 1780/0`). **The §29 "not a bigger model" verdict is corrected: a frontier model that goes to the compiler INTERNALS *is* a wall-breaker for the codegen classes.** Three byte-proven idioms:

1. **STORE-vs-LOAD IS A DETERMINISTIC ALIASING FLAG, NOT A SCHEDULER TIE-BREAK (revises §10/§20 "unsteerable").** gcc-2.7.2 `expr.c` sets `MEM_IN_STRUCT_P` (`/s`) only when a load's address is a member/aggregate ref or was "computed by addition" (PLUS_EXPR). The front end folds `p[0]`→`*p`, so **zero-offset / bare-deref loads never get `/s`** → they carry a hard true-dependence on an aliasing fixed-symbol store (`D_xxx = 0`) and get stuck below it; offset/member loads have `/s` and hoist freely. So the store-vs-load "coin-flip" is a binary flag you SET from C:
   - **Grant `/s` (make the load hoist over the store):** write it as a struct-member ref → `((struct { s32 field; } *)p)->field`. **Use an ANONYMOUS struct in the cast** — `dedup_propagate` (line ~366) rejects inline *named* structs, so anonymous keeps the `/s` flag AND stays propagatable ×134.
   - **Deny `/s` (keep the load below the store, e.g. a separate reload the target shows):** keep it a bare `*p` / `p[0]`. (CSE's fixed-scalar-store invalidation only kills non-`/s` entries — that's what forces the target's separate reload.)
   - **The tell in any diff:** a zero-offset pointer load stuck on one side of a fixed-symbol store while *offset* loads float. Re-test candidates: `func_8014F2E0`, `func_80150528`, `func_8014EA4C` (close=6), and every §10/§20 "store-vs-load unsteerable" backlog verdict.
2. **THE DEF-SIDE RETURN-TYPE WALL HAS A MACRO ESCAPE (extends §29).** When a matching def must return `s32` (a `void` return DCEs a computed local → frame shrinks → no match) but the *only* conflicting caller-decl is a **shared `DEFINE_func_*` macro that DISCARDS the return**: **widen that macro's `extern void func_X(...)` → `extern s32 func_X(...)`.** It's byte-neutral for the caller (the return is discarded — verified `check-all 136/136` fleet-wide). §29 said "no escape" because a bare `INCLUDE_ASM` stub declares no C symbol — but a **macro DOES declare the symbol via its `extern` line**, so there is one. (The narrow-scalar-param-by-value wall from §29 still stands — this dissolves only the *return-type* conflict.)
3. **THE "BIRTHING-BOOST" PROLOGUE-ORDER LEVER.** `sched.c:adjust_priority` (pre-reload only) boosts to max priority any insn whose dest reg is set **exactly once** in the fn (`birthing_insn_p`: `REG_N_SETS==1`); sched1 schedules each bb **backward**, so a boosted insn is picked early = placed **late**. Single-set param copies (`s0=a0`) then sink below multi-set const inits (`s6=0/s5=8`, reassigned in a switch → never boosted). **Fix: one zero-byte NON-volatile re-tie `__asm__("" : "=r"(x) : "0"(x))` on the param, placed in a LATER basic block** (after the switch). It counts as a 2nd SET (boost dead), emits nothing, adds no bb0 edges → all inits tie and the LUID/source-order tie-break restores params-first. Generalizes to any wrong prologue/init ORDER between single-set and multi-set defs.

**Meta-lesson (feeds effort-map / R17):** the "idiom well is dry / wall is intrinsic" verdict (T10.8/T10.9, §29) was **model-relative** — true for GLM and the local 7B, false for a frontier model that reads the gcc-2.7.2 source. The wall-breaker recipe: `Agent(model:fable)` + `tools/reference/gcc-papermario` (RTL `-da` dumps) + this toolkit + the `match_one`/`gate_stage` loop, on ONE giant at a time. Cost ≈ 375k agent-tokens / giant across the leaf-crack + whole-binary integration (2 rounds). NB: match_one (isolated) masks in-TU declaration conflicts — always finish on the **whole-binary** `gate_stage` (the §20 stale-`.o` trap can fake a pass; force a clean compile).

## §30a — §30 generalizes to the FULL near-miss backlog (via STANDARD Opus agents, not just Fable5) + 2 more steer levers + the mechanical-integration throughput unlock (Phase 23 (a))
A toolkit pass re-tested 3 backlog "store-vs-load / CONFIRMED unsteerable" verdicts with §30, run by **standard Opus agents (~80–130k tokens each) APPLYING the documented idiom** (not Fable5 *discovering* it). Result: **2 banked ×134** (`func_8014F2E0` 66 ins, `func_80150528` 53 ins; fleet 64.74→64.82%), 1 partial (`func_8014EA4C` 6→3 — its store-vs-load part dissolved by §30, but an orthogonal abs-coalescing/frame-fragility wall survives = genuine permuter/Fable5 territory). **The "unsteerable" backlog is largely MIS-VERDICTED — these near-misses ARE matchable, and standard agents applying a GROWING toolkit crack them cheaply.** Three byte-proven additions:
1. **§30 `/s` REFINEMENT — a cast-wrapped PLUS does NOT get `/s`.** `expr.c:5535` grants `/s` only when the `INDIRECT_REF` operand is a **top-level PLUS_EXPR**; `*(T*)(p + k)` puts a NOP_EXPR (the cast) on top of the PLUS → no `/s`. Only a **bare-typed PLUS** (`q[k]`, `q` a typed `T*`) or a **COMPONENT_REF** (`expr.c:5891`, unconditional `MEM_IN_STRUCT_P=1`) gets it. The universal grant is the **anonymous-struct member-ref** `((struct{s32 f;}*)p)->f` (COMPONENT_REF path), NOT `*(s32*)(p+off)`. (byte-proven func_8014F2E0, func_8014EA4C).
2. **IV-COMBINE: keep gcc's `combine_givs` at N induction vars with a SINGLE base pointer.** Far-field accesses off a separate `q = base + off` pointer make cc1 strength-reduce a **spurious extra IV**. Collapse to ONE base pointer with all fields as plain byte-offsets → cc1 re-combines to the target's IV count. **NB: CONFLICTS with the §30 anon-struct read** (which introduces a separate pointer → re-triggers the split) — read the diff and pick the lever the target's IV structure demands. (byte-proven func_80150528).
3. **INLINE LOOP-LIMIT → preheader-hoist.** An invariant loop limit written as an **inline expression `D_x + K`** in BOTH the entry guard and the loop condition (NOT a cached `end` local) makes gcc's loop optimizer hoist it into the **preheader** — producing the preheader copy insn AND the target's callee-saved regalloc. A cached `u8 *end` local pins it in one reg = wrong. (byte-proven func_80150528).

**INTEGRATION IS MECHANICAL — the throughput unlock.** All 3 giants banked this session (func_8014EE14, func_8014F2E0, func_80150528) hit the SAME whole-binary near-1 after a perfect leaf `match_one`: a `DEFINE_func_*` **caller macro declares the fn `extern void` but the matching def needs `s32`** (a `void` return DCEs a live local → frame shrinks → no match). Fix = §30 #2: widen that caller macro's extern `void`→`s32` — byte-neutral (caller discards the return; `check-all 136/136` confirms). **This is TOOLABLE** — a `gate_stage` recovery pass that, on a leaf-MATCH-but-near-1 fn, tries widening a discarding-caller-macro's extern to the def's return type would let every agent's leaf-MATCH auto-bank. **Campaign implication:** leaf-matching the near-miss backlog is now cheap (Opus agents + the toolkit); the bottleneck is the mechanical integration step → build the tool, then the ~95 "schedule"/80 "regalloc"/31 "hoist" backlog verdicts (many mis-labeled) become an **agent-wave harvest**, with Fable5 reserved for the genuinely-novel residuals (frame-fragility/coalescing walls).

## §31 — THE gcc-2.7.2 CODEGEN MAP: pass → residual → C-lever catalog (Phase 23; 4 Fable5 agents read the compiler source)
Instead of reverse-engineering the compiler function-by-function (Fable5 ≈ 375–475k tokens/giant), 4 Fable5 agents **read the gcc-2.7.2 passes directly** and produced source-cited, byte-proven, rerunnable catalogs. **The full detail is in `docs/gcc-2.7.2-map/{sched,regalloc,loop,cse_expr}.md`** — consult those for the exact lever + exemplar + `file:line` per class. This §31 is the INDEX + triage; apply it, drop to the source only for a class not covered here (then add it, R16).

**⚠️ SOURCE-VERSION CORRECTION (propagate everywhere):** `tools/reference/gcc-papermario` is **gcc 2.8.1, NOT 2.7.2** — a *behavioral* difference (2.8.1 `&&0`-disables biv-elimination paths that are ENABLED in the real 2.7.2 cc1). The **vanilla gcc-2.7.2 source is now at `tools/reference/gcc-2.7.2/`** (SETUP §5.6) — cite it. Every byte-proven lever we have still stands (all validated via `match_one` against the actual pinned 2.7.2 `cc1`, the ground truth); only the *source citations* in §17/§30 were on 2.8.1.

**TRIAGE TABLE — route a residual by class → {STEERABLE (lever in the catalog) | INTRINSIC → permuter}:**

| pass-group (catalog) | STEERABLE (byte-proven levers) | INTRINSIC → permuter |
|---|---|---|
| **scheduling** `sched.md` | S1 LUID=source-order (transcribe target order); **S2 birthing-boost — both directions** (fresh single-set local to *create* a sink; §30#3 re-tie to *kill* it); S4/5/6 load-gap-filler / mem-unit spacing / hazard-front-move (**a 4th rank rule — §25 corrected**); S7 prologue saves; D1 delay-slot content; D2 eligibility; D3 eager-steal | **S3** load/mul chain-priority sink; **S11** the LUID⊗alloc coupling knife-edge (`func_801571C4`) — **⚠ DOWNGRADED (Phase-24 T5b): try S12+S13 first** (reused-s32-temp fence · body-local param copies · asm-copy · dead-read fence — `sched.md §6`); `func_8014E048` (35-off "intrinsic") MATCHED+banked this way |
| **regalloc/reload** `regalloc.md` | RC-1 spill-slot shape (**= DECLARATION order**, not first-assignment); RC-2 wrong-value-spilled (`allocno` density — def/use placement); RC-3 $s-order; RC-4 coalescing un-tie; RC-5 pin side-effects (4 channels); RC-7 remat-vs-spill; RC-8 reload artifacts | **RC-6** pressure-lock (`func_801770E0`); **RC-9** cross-block copy-fold when frame-fragile |
| **loop.c** `loop.md` | L1 IV-count/anchor (single-base-ptr); L2 index-biv elimination; L3 loop reversal; L4 hoisting/preheader (inline-limit); L7 invalid-loop; L8 increment-pos | L5 final-value compensation; L6 giv-add order |
| **cse/expr** `cse_expr.md` | **cross-call ADDRESS-caching = hoist-vs-remat — STEERABLE** (nested-block ptr + post-call `volatile` output re-set); cross-call VALUE-CSE (phantom $s, §30); **/s aliasing — full 4-arm model** + store-side flush lever; stack layout | cse.c 1000-insn table flush (giants); QImode never gets `/s` |

**WALLS BROKEN this study** (classes long "CONFIRMED unsteerable", now byte-proven steerable): **§10/§20 hoist-vs-remat** (the biggest — blocks the 400-ins `func_80132784`); **store-vs-load** (/s flag, §30); **dbr delay-slot** (D1 + S2 fresh-local — `func_801770E0` 53→49, correcting its own agent's "unsteerable" verdict); the **birthing-boost sink** both directions. Incidental banks from the study: **`func_80149374` ×134** (+ `func_801493D0` leaf-matched, whole-binary-deferred). **Genuine remaining walls** (route to permuter, don't hand-grind): S3 chain-priority sink, RC-6 pressure-lock (true form: every edit explodes 20+ insns), the cse mega-flush. **S11 was downgraded in Phase-24 T5b** — `func_8014E048` (the canonical "S11 intrinsic" seed, 28-off even after the directed permuter) fell to the S12 reused-s32-temp fence + S13 head-skip escape + RC-10 preference steering (sched.md §6 / regalloc.md §F); audit pins + try those before any S11 verdict.

**DIAGNOSTIC TELLS (pick the class in seconds):** `$t0` in a spill slot = reload artifact (spilled pseudo, not a source MEM); "every small edit moves 20+ insns" = RC-6 pressure-lock → permuter; a load stuck below a `D_x=0` store while offset loads float = /s-flag (§30); a phantom 7th `$s`-reg held across the fn = cross-call CSE; a prologue init in the wrong order = birthing-boost (S2). The 16-row full tells table is in each catalog.

**HOW THE CHEAP TIER USES THIS:** given a near-miss diff → read the tell → look up the class's lever in the catalog → apply → gate. This is the artifact that lets Opus agents *and* the local model apply compiler-internal levers **without reading 80k lines of source** — the permanent-knowledge payoff.

## §32 — The region-a CAMERA-GIANT idiom set: struct-base hoisting + 4 sibling levers (Phase 24 T7, Fable5-cracked on `func_80129CF8` 191 ins, match_one MATCH; transferable to the 6 sibling giants)
The region-a (`ov_SC01_077_a.c`) giants Ghidra flattens into per-global `lui/%lo` — but the target holds **global base ARRAYS in callee-saved regs across the whole function**. Fable5 read the gcc-2.7.2 source and cracked `func_80129CF8` in 3 edits (202→143→10→0), **no pins, no permuter**. The idiom set (each transferable — `.run/t7/func_80129CF8.c` is the worked example, `.run/t7/GIANTS_SURVEY.md` the target list):

1. **Hoisted `$sN` base = an explicit POINTER LOCAL, assigned AFTER the first call, in the target's `lui` order** (`p2 = D_800AF630; p1 = D_80126DB8;` right after the first `jal`). gcc-2.7.2 has **no cross-bb CSE**, so a base living in a callee-saved reg across calls/branches can ONLY come from a *source* local — you cannot get it from a bare global access. **No `register __asm__` pins needed:** allocation order = density priority `floor_log2(n_refs)*n_refs/live_length` (`global.c:594 allocno_compare`) then first-fit regno (mips.h has no REG_ALLOC_ORDER) → most-referenced ptr→$s0, next→$s1, next→$s2. The init placement survives because sched1's ascending-LUID tie-break (`sched.c:2414 rank_for_schedule`) keeps zero-dep sets in order. A single-set/single-use base local is SAFE from the RC-7 init-sink (its hi/lo SET_SRC is a LO_SUM → fails `rtx_equal_p` at `local-alloc.c:1169-1172`).
2. **Branch polarity is READ OFF THE TARGET OPCODE** (not Ghidra's `if`): target `beqz $v0,.Lcopy` with the other arm as fall-through ⇒ write `if (sel != 0) {fallthrough-arm} else {copy}`. On func_80129CF8 this single inversion fixed **133 of 143** mismatches.
3. **`lw/lw/nop/addu/sw` per-element ladders = the S12 reused-s32-temp fence** — `a = p1[i]; b = cam[j]; cam[k] = a+b;` reusing ONE `(a,b)` pair across all elements. But **leave the LAST element in Ghidra's fresh-temp shape** (`t = p1[last] + cam[..]; cam[..] = ..; cam[..] = t;`) — its unfenced load is what the scheduler hoists into the previous element's load-delay slot, and a following call-arg `&cam[..]` fills the gap before it, both automatically.
4. **A grouped 3-loads/3-stores copy fed by `la $reg,SRC` (split lui/addiu) = a 32-byte STRUCT ASSIGNMENT, never scalar copies:** `*(RView*)(p2 + 6) = *(RView*)D_800AE688;` (RView = the GsRVIEW2-shaped 32-byte struct, now in `engine_types.h`). `expand_block_move` (`mips.c:2361`) emits one `movstrsi_internal` for ≤2*MAX_MOVE_BYTES(32) with 4 scratches; `output_block_move` burns the last scratch on `la a1,SRC` → 3 data regs → the 3+3 grouping. The **dest must go through the pointer local** (`p2+6`, folded to `0x18($s2)`); a bare global dest is CONSTANT_P and degrades to 2 regs. Scalar `a=src[i]; dst[i]=a;` copies schedule as lw/lw/sw/sw pairs — WRONG shape.
5. **Frame bigger than args(16)+saves by a round chunk = a DEAD LOCAL AGGREGATE:** add an unused `RView view;` (32 B) to reserve the missing 0x20 — gcc-2.7.2 assigns stack slots to local structs/arrays at expand time regardless of use, and -O2 never deletes them. Suspect this whenever a sibling's frame is 0x20/0x28 over-accountable.
6. **This class needs NO pins, NO asm fences, NO permuter** — the interp-loop software-pipelining (a2/sll/lh-next/sra/sw + a3-in-jal-slot) is deterministic sched2+dbr output once the bases sit in $s0/$s1/$s2.

**BANKING (Phase-24 T7b — RESOLVED, see §33):** a freshly-matched giant MATCHes standalone (match_one) but its **loose data decls** (`struct BigCopy` / `s32` / `s32[]` / `u8[]` / `s8`-vs-`u8`) collide in-TU with `engine_core.h` when you try to bank it. The fix is a decl-reconcile — declare each symbol its **canonical** type and cast byte-neutrally at the access site (`cam = (s32*)D_80126948;`, `p1 = (s32*)&D_80126DB8;` for a `struct BigCopy` base, `D_801151D4 = (s32)cam;`, `*(u8*)&D_801150D6` to force `lbu` under `s8`) — done by HAND for `func_80129CF8`, now **automated by `tools/reconcile_decls.py`** (§33). **R14 correction:** the T7 note that "banking **×134** hits the wall" was a MISDIAGNOSIS — once the ×1 bank is reconciled, `dedup_propagate --recover` propagates it to all 134 overlays byte-identical for free (proven: `func_80129CF8` ×134, clean fleet 136/136). The wall was only ever the *×1 reconcile* of the loose draft, not the propagation.

## §33 — Automating the giant decl-reconcile: `tools/reconcile_decls.py` (the DATA analog of §20's `cast_call_sites`) + a fleet-majority type oracle (Phase 24 T7b, byte-proven on `func_80129CF8`)
**The gap.** A freshly-matched giant/wave draft byte-matches STANDALONE with its own guessed decls, but to bank ×1 (and then propagate ×134 via a shared `DEFINE_func_*` macro that EMBEDS its externs) its callee/data externs must be FLEET-CANONICAL, else `conflicting types` in-TU. `cast_call_sites` (§20) does this for callee FUNCTIONS; **`reconcile_decls` does it for DATA symbols `D_XXXX`** — the class the giants hit (they hoist global base ARRAYS, §32). It was the last *manual* step in the giant pipeline.

**The oracle (fleet-majority type picker) — new; none existed** (`gen_harvest_targets` read only `engine_core.h` + ONE overlay, first-seen-wins, never saw a fleet disagreement). `reconcile_decls.canonical_data_map()`: an `engine_core.h` macro decl is AUTHORITATIVE (the shared/propagated set every overlay co-instantiates — conform to it and the macro can't conflict per-overlay); else the plurality across ALL overlays + `resident.c` (tie → lexicographically-first spelling, deterministic). Verified **8/8** on func_80129CF8's symbols (`--print-canon D_XXXX` inspects one).

**Byte-neutral cast taxonomy** (the DRAFT's decl type = the *intended* access; cast every use to reproduce it under the CANONICAL storage decl → gcc folds the compile-time cast → identical opcode; the whole-binary byte-gate is the sole arbiter, fail-closed):
| draft decl | canonical | decl → | access → |
|---|---|---|---|
| array `Ed[]` | array `Ec[]` (Ed≠Ec) | `Ec[]` | `D_x` → `(Ed*)D_x`; `D_x[i]` → `((Ed*)D_x)[i]` |
| array `Ed[]` | struct / scalar | canon | `D_x` → `(Ed*)&D_x` (address-of the object) |
| scalar `Td` | scalar `Tc` (signed/width) | `Tc` | `D_x` → `*(Td*)&D_x` (forces the `Td` opcode, e.g. `lbu` under `s8`) |
| ptr `P* D_x` | scalar `Tc` | `Tc` | `D_x` → `(*(P **)&D_x)` (cast-lvalue: store/read a pointer in the scalar slot) |
Implementation: ONE `re.sub` per symbol with a replacement fn (captures the optional leading `&` / following `[`), **single-pass** so a symbol in several forms on one line can't double-wrap (the first draft double-wrapped the ptr-store — the two-sub read+write templates re-matched; collapsed to one pass).

**Pipeline placement:** `canon_resident_calls → cast_call_sites → reconcile_decls → sig_unify → harvest_verify --chunk 1` (wired into `gate_stage`; **idempotent / no-op on drafts without a data conflict** → can't regress the wave). Standalone giant use: `tools/reconcile_decls.py --overlay <ov> --src-file src/<ov>/<ov>_a.c --in <drafts> --out <drafts>-rc`.

**Byte-proof (T7b, no Fable5 needed):** the full loose `func_80129CF8` (intended decls `s32 D_80126948[]` … , un-cast accesses) → `reconcile_decls` (5 symbols reconciled) → swapped into the `DEFINE_` macro → `make build BINARY=ov_SC01_077` = **BYTE-IDENTICAL `d19c9580`**.

**R14 — the tool is an AUTOMATION, not an "unlock":** `func_80129CF8` banks ×134 FREE via existing `dedup_propagate --recover` once reconciled (the "×134 wall" was a stale-asm misdiagnosis, §32). `reconcile_decls`' value is removing the *manual* ×1-reconcile step for every future giant / loose draft (the 6 sibling giants + the wave tail), not unblocking propagation.

## §34 — The `func_80138ED0` giant crack: gcc-2.7.2's **3-qty sort bug** + the **zero-byte asm allocation toolkit** + the **giv-init fence** (Phase 24 T5; Opus→close=21, Fable5→MATCH ×134)
The 2nd region-a giant (159 ins, bit-unpack/tilemap; 2 giant-local data bases, callees `func_8013914C`/`func_800599B8`). Opus applying §32 reached **close=21** (all semantics/control-flow/constants exact); **Fable5 reading the vanilla gcc-2.7.2 source cracked the pure regalloc/schedule residual — every class C-reachable, no permuter.** Each lever byte-verified via `match_one` + gdb-on-cc1. The banking then took the standard pipeline (`cast_call_sites` reconciled `func_8013914C` `(u8*,u16*)`→canonical `(s32,s32)`+call-site cast; `reconcile_decls` a NO-OP — the 2 data bases are giant-local, no fleet conflict) → ×1 → `dedup_propagate --recover` → **×134 byte-identical** (pins/asm body propagates fine; `func_800599B8`'s lone `(s32,s32)` decl is in `ov_SC01_077.c`, a different TU from the `_a.c` bank, so no per-member conflict).

**THE HEADLINE — gcc-2.7.2's 3-qty local-alloc SORT BUG (`local-alloc.c:1441-1463`/:1494-1516).** For a block with **≤3 local register quantities**, the unrolled comparison switch compares *fixed qty numbers* (`qty_compare(0,1),(1,2),(0,1)`) but exchanges *order slots* — when `pri(q1)` is highest the third compare re-fires and undoes the first swap, so **3-qty blocks allocate in qty-CREATION order, not density order** (≥4 qtys go through qsort, correct). Symptom: a low-density local grabs a reg it shouldn't. **Fix: a zero-instruction DECOY qty** (`asm("":"=r"(decoy):"r"(x)); asm("" :: "r"(decoy));`) bumps the block to 4 qtys → the qsort path → correct density-order first-fit (`find_reg`, `global.c:904`; `regs_used_so_far` pre-seeded with the call-used regs, `global.c:352-355`). A real compiler bug, now a reusable lever.

**THE ZERO-BYTE ASM TOOLKIT (allocation/schedule dials that emit NOTHING — the byte-gate certifies the induced codegen):**
- **input-only dummy** `asm("" :: "r"(v))` — floats to `v`'s def; a ref-count / density dial (raise a pseudo's priority / extend a live range one way).
- **multi-input dummy** `asm("" :: "r"(a),"r"(b))` — anchors at the LATEST def; a lifetime-extender / joint-release (releases a,b together in sched1's backward pass → `rank_for_schedule`'s class rule `sched.c:2385`, cost-1 dep beats cost-2 load, orders the emit).
- **def+use pair** `asm("":"=r"(d):"r"(s)); asm("" :: "r"(d))` — mints a decoy qty (the 3-qty-bug fix).
- **giv-init fence** `asm("":"=r"(ba):"0"(ba)); dst = ba;` — forces `emit_iv_add_mult`'s giv-init MOVE (`loop.c:5556 if (reg != result) emit_move_insn`) = `addu dst,ba,$zero`; the general fix for the **"gcc coalesced the giv init, dropping one instruction → full count mismatch"** class on any giant with a counter-derived pointer. (Found by the Opus pass; kept.)

**Statement-position / type levers (no asm):** a leading `pb = param_3;` rides `sched.c:3191-3215`'s "don't delay getting parameters" pin so combine folds the parm-save into it (prologue order); an explicit `u32 pv = uVar1;` before `p = base;` replaces loop.c's `move_movables` hoist-at-loop_start (`loop.c:1652/1810`) with source order; a HImode `% 3` (a `u16` var) defeats gcc's `x%3==0 → beq (x/3)*3,x` fold.

**gdb-on-cc1 (the method that settled it):** the shipped `tools/bin/gcc-2.7.2-psx/cc1` is i386-static WITH symbols — breakpoint `find_free_reg`/`post_mark_life` (`.run/t7/fable/gdbtrace.gdb`) to dump the real qty order + register grants when hand-modeling stalls. Cite the vanilla **`tools/reference/gcc-2.7.2/`** tree (now complete — global.c/local-alloc.c/reload1.c/toplev.c/function.c/flow.c/… from the FSF tarball; sched.c/loop.c/mips.c verified byte-identical to vanilla). **Pass order** (why upstream fixes reach the prologue): sched1 → local_alloc → global_alloc/reload → prologue threading (`toplev.c:3103`) → **sched2** (:3117) → jump2 → dbr; prologue saves are sched2-scheduled, everything upstream tunes sched2's LUID tie-breaks.

**Gotcha:** parallel `match_one` runs on the SAME function share `.run/match/<fn>` — pass a unique `--work` dir or the scores are garbage.

## §35 — The region-a sibling-giant harvest: difficulty ≠ $s-reg count (it's global-array hoisting) + the banking recipe + new loop idioms (Phase 24 T7, 5 parallel Opus-Max agents)
Cracking the 5 remaining region-a giants via parallel Opus agents applying §32/§34 surfaced a **ranking law** + a reusable banking recipe.

**THE RANKING LAW (retires the "8-$s-reg = hardest" heuristic):** a giant's difficulty is set by **whether it hoists GLOBAL base ARRAYS into callee-saved regs**, NOT by $s-reg count. gcc-2.7.2 has no cross-bb CSE, so a hoisted *global* base can only come from a source-local pointer in the exact `lui` order (§32#1) — the genuinely hard part, needing Fable5 for the last-mile regalloc. Giants whose $s pressure is **param / local / output-buffer** derived (even all 8 $s0–$s7 live) **one-shot with Opus alone** (density-order first-fit). Byte-proven: `func_8012D098` (189, all-8-$s) + `func_8012EC04` (178, sibling+GTE-tail) MATCHED one-shot; the 3 residual monsters stall only on tiny (2–15) compiler-internal walls, not the $s allocation. **Triage a giant by its `%hi data bases`, not its $s count.**

**THE BANKING RECIPE (matched giant draft → ×134; per-giant integration is mechanical, §30a):**
1. `fix_arity_callers --apply --any-proto --from-file <fn> --drafts <dir>` — no-proto the caller extern conflicting with the matched def-sig (the DEF-side wall: a shared macro in engine_core.h, or a sibling in the overlay, forward-declares the giant with a different sig → `conflicting types`). Byte-neutral (the call's arg bits are unchanged).
2. `sig_unify` — canonicalize the giant's own CALLEE externs (no-proto `void f()` → the fleet's full proto; else args promote differently standalone vs whole-binary).
3. **Strip draft-local typedefs already in `engine_types.h`** (a redundant `typedef …Blk16;` = `conflicting types` in the shared TU) and **anonymize named local typedefs** (`typedef {…} Buf; Buf b;` → `struct {…} b;`, else it collides with a sibling's `Buf`).
4. `harvest_verify --chunk 1` → ×1, then `dedup_propagate --addr <A> --recover` → ×134.
**Do NOT run `cast_call_sites` on these** — it mis-casts a no-proto `void f()` to `void(*)(void)` (0 params) and breaks the call (fix candidate: treat `()` as compatible-with-any).

**New loop idioms (byte-verified; §31/loop.md fodder):** *dest-off-base giv* — write every primitive store `*(u16*)((s32)p + k)` off ONE biv so they combine into a single dest-addr giv (kills giv-split); *index-form source* `param_3[j+k]` with `j+=2` (not a walked pointer) reduces to one address biv; *sltiu-outer/slti-inner without CSE* — a redundant SIGNED range-guard that must stay `slt`/`slti` needs a **separate signed-int copy** (`int s = u;`), since only CSE-*reuse* canonicalizes signed→unsigned; *div2 range-extension* — a zero-byte `asm("":: "r"(x))` after the last flag-test extends a pinned reg's live range so a trailing `andi` lands in the target reg.

**The 3 deferred residuals (Fable5 batch — close=2/10/15; precise root-cause in `.run/t7/<fn>.c` headers + `docs/backlog.md`):** `func_801392FC` (**2**: combine folds `(s16)`load → atomic `lh` before sched2, so the pipelineable split-load never exists; permuter can't reach) · `func_8013A530` (**10** → **MATCHED ×1**, §36 below — the "RC-6 reload-pressure" verdict was wrong: it was the $2/$3 pins themselves (reload-retry poison + sched1 load-hoist collision); cracked pin-free via the $0-add opaque copy + condition-operand flip + else-arm density dummy, regalloc.md §G) · `func_8013AF20` (**15**: loop-invariant constant-hoist ORDER — the two AND-masks materialize opposite, coupled to the AND-operand order; permuter plateaued at 15). All single-class, high byte-weight (×134), ideal Fable5 targets.

## §36 — Fable5 giant-crack levers (Phase 24 T7 Fable5 batch; accumulates as each lands — full RTL dumps in `.run/t7/fable/`)
**`func_801392FC` (loop count-load, close=2 → MATCH ×134):**
- **CROSS-BB COMBINE LAW.** combine never spans basic blocks (`flow.c:2087` — `LOG_LINKS(y)` created only when `BLOCK_NUM(y)==blocknum`). So a value crossing a loop BACKEDGE — a `u16 cnt` reloaded at the loop tail after a call, `(s16)cnt+1` at the top — is a VARIABLE, not a foldable `(sign_extend(mem))`→`lh`. The "split-and-schedulable" count sign-extend the target shows is **cross-BB dataflow, not a fold-defeat**; `reorg.c fill_slots_from_thread` steals the top-BB `sll` into the loop-back `bnez` delay slot + redirects the label to `sra` → the duplicated `sll` (preheader fall-in + delay-slot copy). Don't hunt for an un-fold; make the value cross the backedge.
- **VOLATILE-FRAME-PARITY.** Make the loop-carried count-load `volatile`. A non-volatile `cnt` gets cse-commoned with the same-address condition read → combine's keep-load fold (`newi2pat`; `combine.c:2089 elim_i2`) keeps a dead ashift-temp's `REG_DEAD` alive → a `(use reg)` planted at the nearest label (`combine.c:10835-10847`) → a stale allocno grabs an extra 8-byte reload slot (frame 0x90 vs target 0x80). `volatile` mems are never cse-hashed (clean condition fold) yet `sched.c:811 read_dependence` (both mems volatile) still lets the `lh` hoist above the volatile `lhu`. `volatile` matches BOTH frame size and schedule — suspect it when a loop-carried count is 8 bytes frame-over.
- **Secondary (byte-verified):** route `buf+0xF` byte-store sums through `s32` temps (defeats the C-frontend QImode-plus operand-swap `addu v1,v1,v0` vs the target's SImode `addu v0,v0,v1`); statement position drives sched2's BACKWARD list scheduler (INSN_LUID tie-break, `rank_for_schedule`) — put `i++`/`acc+=` AFTER the call to fill the `jal` delay; a `register __asm__("$5")` re-arm before an arm's 2nd call limits post-reload cross-jump merge depth (jump2 sits between sched2 and dbr).

**`func_8013A530` (the LARGEST giant, 204 ins, clamp double register-split, close=10 → MATCH ×1; dumps `.run/t7/fable/a530/`):**
- **THE $0-ADD OPAQUE COPY (new tool — the un-reversible, un-cse-able `move`).** `register int zr __asm__("$0"); iVar7 = fc + zr;` emits the byte-identical `addu $rd,$rs,$zero` but as RTL `(plus reg $0)`, NOT `(set reg reg)`: cse's `make_regs_eqv` never links the two (no canon poisoning in either direction — `canon_reg` cse.c:2545 also never rewrites the hard-reg side), and combine cannot absorb the source's load into the dest (no extend+plus pattern). A plain `int iVar7 = fc;` (fc pinned) gets REVERSED by combine — load lands in the pseudo, the pin becomes the copy dest, 1 insn shorter. Use it whenever the target keeps load+copy as two live registers with compares reading the LOAD and arms reading the COPY. $0 is fixed → zero RC-5 side channels.
- **PIN → RELOAD-RETRY POISON (RC-5 ch.2 extends to retry_global_alloc).** The old `iVar7 $v1`/`t $v0` pins put $2/$3 in `bad_spill_regs` (`reload1.c:3900-15` regs_explicitly_used); the div-magic LO/MD "Need" spill forced CASE1's 2nd-product allocno through `retry_global_alloc`, which skips bad_spill_regs → `mflo $t2`. Unpinned: `.greg "Register 177 now in 3"` → `mflo $v1`. A pin can move a register FUNCTION-WIDE through the retry path even where the pinned var is dead.
- **CONDITION-OPERAND ORDER = LOAD PLACEMENT (sched1 backward + mem-unit hazard).** `(int)mem < t-ext` vs `t-ext > (int)mem` produce the SAME canonical slt but mirrored expansion uids; sched1's backward scheduler (boosted-group ties break toward higher uid; `blocking insn N for 1 cycles` when the sh occupies the mem unit) hoists the mem-first spelling's `lh` to the block TOP — birthing the reload INTO the pin/pseudo's live window (the RC-6 "reload-pressure" was really this). The `>` spelling keeps the lh below the addiu that kills iVar7 → reload (local, first pick) and iVar7 (global) sit in $v1 disjointly.
- **DENSITY DUMMY PLACEMENT vs maspsx (#APP blocks the ASPSX slot-hop).** cc1 emits `[lh;lh;addu;slt;beqz]`; maspsx/ASPSX-2.56 HOPS the addu over the slt into the branch delay slot (and re-inserts the load-delay nop) — but NOT across `#APP/#NO_APP`. A zero-byte dummy between the addu and slt kills the hop (that was the last 1-insn diff). Park density dummies inside an ARM as a 2-input `asm("" :: "r"(v),"r"(t))` anchored at t's def — +1 ref lifted iVar7's `allocno_compare` priority (3/10→8/11) past the fe-load's 3/5 → iVar7 allocates first → $v1, fe → $a0.
- **KEEPALIVE KILLS THE DYING-HARD-REG SUGGESTION.** The else-compare's slt-result temp grabbed $a1 via `qty_phys_sugg` (fc/$a1 dying in that slt; suggested qtys allocate first). `__asm__("" :: "r"(fc));` after the clamp keeps $a1 alive there → no suggestion → plain first-fit $v0 (target).
- **The 2nd split is NATURAL (promoted-HI store-copy).** `if ((cmp)) *(s16*)(p+0xc) = *(s16*)(p+0xe);` — the condition's `(int)mem` expands as HI-load+sll/sra, the body's re-load cse-folds onto the HI pseudo, combine merges the extend into one `lh` and re-emits the HI pseudo as a subreg copy → `lh $v1; addu $a0,$v1; slt ..$v1..; sh $a0` for free. Never pin for this shape.

**`func_8013AF20` (185 ins, 3 addPrim GPU-builder loops, close=15 "const-order⊗AND-order coupling" → MATCH, permuter had plateaued 40k iters; dumps `.run/t7/fable/dumps_C/`):**
- **BITFIELD STORE = THE MASK-ORDER DECOUPLER (the libgpu addPrim idiom).** A target preheader that materializes `0x00ffffff` (lui+ori) BEFORE `0xff000000` (lui) while the body still computes `*dest & 0xff000000` FIRST cannot come from user-mask C (`*p = *p & 0xff000000 | *ot & 0xffffff` materializes in expression order, and every operand reorder flips the AND/OR shape with it — the byte-verified 19/182-diff coupling). It comes from the SDK's `setaddr` 24-bit BITFIELD store: `store_fixed_bit_field` (expmed.c:556) expands value∧`mask_rtx(mode,0,bitsize,0)`=0x00ffffff FIRST (`must_and` :667 → :679-681), THEN dest∧`mask_rtx(mode,bitpos,bitsize,1)`=0xff000000 (:694-696), THEN `ior(destmasked,value)` (:706 — dest chain stays op0). scan_loop then finds the mask movables in that insn order → move_movables emits the preheader consts […, 0x00ffffff, 0xff000000] with the body bytes unchanged. Transcribe `addPrim(ot,p)` literally: `((P_TAG*)p)->addr = ((P_TAG*)ot)->addr; ((P_TAG*)ot)->addr = (u32)p;` with the real `P_TAG {u32 addr:24; u32 len:8; u8 r0,g0,b0,code;}` (a bitfield STORE with user-mask RHS also byte-matches; the read is optional). 15→8. **Suspect this lever on ANY OT/linked-list 24-bit-pointer-field target.**
- **2-INSTRUCTION CONSTANTS DODGE THE EQUIV LL-DOUBLING → they WIN the low scratch regs (gdb-proven).** sched1 splits every insn pre-reload (sched.c:4830 `try_split`) → mips.md:3208 `large_int` define_split turns `li 0xffffff` into lui+ori = TWO SETS → `reg_n_sets==2` fails `update_equiv_regs`' single-set gate (local-alloc.c:1021) → the mask ESCAPES the `reg_live_length *= 2` const-penalty (local-alloc.c:1064) that hits every 1-instruction const (addiu-able 3/0x40/0x3d, lui-only 0xff000000). Priorities: mask fl2(7)*7/35 = 4000 ≫ 0x3d fl2(7)*7/72 = 1944 → the mask allocates FIRST (`allocno_compare`) → first-fit $a2 (loops 1/2) / $a1 (loop 3). gdb ground truth: n_sets {61:1, 0xffffff:**2**, 0xff000000:1}; LL pre→post update_equiv_regs 36/35/33 → 72/**35**/66. A preheader const-register contest that looks "impossible by density" is usually this.
- **A do{}while(0) barrier is a LOOP-DEPTH REF INFLATOR (flow.c), not just a LUID shifter.** flow weights every mention by loop_depth (flow.c:2067/2315/2501/2711 `reg_n_refs += loop_depth`; here: preheader set=1, body mention=2, +1 more per extra NOTE_INSN_LOOP nest). The Opus draft's barrier wrapped the three `0x3d` byte-stores → refs 7→10 → pri 4166 > 4000 → 0x3d stole $a2 from the mask (the final 8 diffs). Deleting it (obsolete once the bitfield form reshaped the body) restored the refs tie → mask-first allocation → MATCH. **AUDIT inherited barriers whenever a preheader-const register identity is off by one.**

## §37 — The T7 §G giant endgame: 6/8 cracked, meta-laws + transferable levers (Phase 24, 2026-07-07; FULL byte-verified detail + gcc-2.7.2 line cites in `docs/gcc-2.7.2-map/t7g-giant-harvest.md`)
Cracked **6 of 8** reach-134 §G giants — `func_801571C4` (permuter), `func_8014EA4C`/`func_801372B0`/`func_801770E0`/`func_80176D94`/`func_80148094` (Fable5) — plus **2 genuine walls**: `func_80178004` (biv-init emit-order, close=7) and `func_801412A8` (allocation placement-knot, close=29), both stay INCLUDE_ASM. **4 propagated ×134** (fleet 65.75→65.91%, clean 136/136); 372B0/770E0 banked ×1 (blocked ×134 by the §A pin/asm + local-type self-containment gaps).

**META-LAWS (audit BEFORE deep work):**
1. **SIBLING-ISOMORPHISM (mandatory step-0):** GPU-packet/addPrim builders come in FAMILIES. Diff your target `.s` MNEMONIC sequence vs already-MATCHED siblings (`grep -oP '\*/\s+\K\S+'`); an immediates-only diff ⇒ PORT the banked sibling verbatim + swap constants = one-shot (76D94 fell from 770E0 in ~15 min).
2. **"MUTUAL-EXCLUSION / RC-6 unsteerable" IS A TELL, NOT A VERDICT:** "X must be early AND late, coupled through one priority number / every small edit moves 20+ insns" = a MISSING dep edge or an allocno TIE — real only in the broken graph. 770E0 (the *named* RC-6 exemplar) fell fully source-reachable.
3. **RTL DUMPS ARE NOT STRIPPED** (corrects §34): the shipped cc1 with `-dr -dj -dc -dl -dg` emits full `.rtl/.jump/.combine/.lreg/.greg` — readable ground truth before gdb (`.lreg` refs/length, `.greg` alloc-order/conflicts/preferences, `(use (reg:SI` in `.combine` = phantom stack slots).

**TRANSFERABLE LEVERS (byte-verified):**
- **The `/s`-DEP LATTICE (load+store dual):** force `MEM_IN_STRUCT_P` via a struct-member-at-offset-0 access — `((struct{u16 h;}*)&D_global)->h` (load, 770E0) / `((struct{u32 w;}*)p)->w=…` (store, 76D94) — to restore the missing store↔load dep edge (`sched.c:820` drop clause needs one side /s+varying, the other **non-/s+FIXED-address**). SCOPE: inapplicable when all mem ops are register-addressed (412A8/48094).
- **Allocno-priority ref-boost** (48094): `__asm__("" :: "r"(v));` at the TOP of a block where v is already live-through → +1 flow-ref, 0 live-range, 0 bytes; crosses the `floor_log2(refs)` step in `allocno_compare` (`global.c:588`) → v wins the reg over a short block temp.
- **Coalescable-copy insn_count bump** (78004): whole reg-file shifted by one hoisted loop const ⇒ `move_movables`' threshold at its `>=` boundary — a coalescable copy `{u32 m=v; store=m|…;}` bumps insn_count +1 → hoist refused; combine coalesces m away = 0 bytes. BANKABLE (vs a TU-wide global-register-var).
- **Const-register PIN cascades store order** (770E0): store order is downstream of a const's register via sched2 anti-webs → pin the const (`register u32 c __asm__("$6")=…`), stores re-place free.
- **S2-kill re-tie** (372B0): `__asm__("":"=r"(v):"0"(v))` after last use → reg_n_sets==2 → no birthing boost → source order (single-set pins, INCL. hard-reg, DO boost — corrects §34). + **S2 fire-tick via consumer store order.**
- **qty_compare-TIE audit** (412A8): dozens of "schedule" diffs often trace to ONE equal-priority allocno tie (`find_free_reg`, gdb) broken by qty/block-scan order — a window-temp reuse flips it. + **multi-death block-var law** (`local-alloc.c:472`: reg_n_deaths≠1 → global allocno → chaos).
- **CSE-dodge without a barrier:** `(u16)x` (zero_extend) head vs `x&0xffff` (AND) tail hash differently → no cross-call CSE → no extra callee-save. Prefer over `volatile`-asm re-ties (a FULL sched barrier per sched.c ASM_OPERANDS).

**BANKING PATTERNS (main + `_a` split):** caller-extern reconcile (`void`→canonical return, 571C4); **asm-label alias** for sibling-decl signedness/proto conflicts (`extern u16 X __asm__("D_x")`, 372B0) — beats reconcile's `*(u16*)&D_x` cast whose address-of PERTURBS regalloc; **canonical call-cast + anonymize the shared `/s` struct** for isomorphic-sibling ports (76D94). **×134 blockers (§A gaps → tool fixes):** register-asm pins + overlay-local *named* types fail `dedup_propagate.compiles_standalone` → bank ×1 (needs a pin/asm self-containment shim + a uniquely-renamed type-lift).

**TOOLING (flywheel):** fixed a silent permuter bug — `tools/p16_permute.py` header comments broke `cpp` → decomp-permuter no-op'd `(0s)` on EVERY commented draft (`strip_c_comments`); **a SECOND silent no-op of the same class (Phase 26 session 6): a draft whose GTE ops are `#define`s CONTAINING `__asm__` (the PsyQ `inline_c.h` convention — i.e. most renderer code) got its macro DEFINITIONS chewed up by `hide_asm` (which is built for `__asm__` statements / `register` pins and scans to the nearest `;{}`), swallowing the function itself → pycparser `Function <fn> not found in base.c` → permuter no-op `(0s)`. Fix: `cpp_expand_macros()` pre-expands with `cpp -P` so each GTE op becomes an inline `__asm__` statement hide_asm can carry — applied ONLY when a `#define ... __asm__` is present, so macro-free drafts are byte-untouched. LESSON: the permuter reporting `no match (0s)` is a TOOLING failure signature, never a real search result — always confirm workers actually ran.** `p16_permute` also gained `--asm-subdir` (it was hardcoded to ov_SC01_077's main object, so no core in another overlay/split object could be permuted at all); NEW `tools/permuter_ils.py` (warm-restart iterated-local-search — descends where a cold run plateaus: 48094 72→29). **Escalation: model to close=2 by hand, THEN directed-permuter the residual** (372B0's last lever fell at permuter iter 291; permuter is low-ROI at close=8).

## §38 — The WHALE `func_80144B9C` (770 ins): the -O0 struct-assign memcpy idiom + the -O0 reach-134 ×134 rollout (Phase 24 T7 §G, cheap Opus — no Fable5, no calls.c)

The single biggest byte-weight lever in the fleet (770 ins × reach-134 ≈ +1.6%). It sat at close=2 for a whole session, tagged "needs gcc-2.7.2 calls.c + Fable5" — but a **cheap Opus one-liner** cracked it. Three durable lessons:

**(1) THE CRACK — a STRUCT ASSIGNMENT, not an explicit `memcpy()` call, for the -O0 block-move.** The whale is an **-O0** function (prologue `21F0A003`; `match_one` at -O2 reads only 458/770 — compile it -O0). Its 2-insn residual was a memcpy of a 0x24-byte struct. The **tell:** the target marshals the memcpy args through temp pseudos — `lw $v0=src ; lui/addiu $v1=&dst ; addu $a0,$v1,$zero ; addu $a1,$v0,$zero` — which an explicit `memcpy(&dst, src, 0x24)` call does NOT emit (it loads $a0/$a1 directly). That precompute is the signature of gcc's `emit_block_move → emit_library_call(memcpy)`: the original C was a **struct assignment** `dst = *src_ptr;` where `sizeof(struct)==0x24`. gcc-2.7.2 -O0 expands a `> MOVE_RATIO`-word struct copy to a memcpy library call whose args go through `copy_to_mode_reg` (pseudos) then `addu` into the arg regs = the exact 2 extra moves. **So: an -O0 memcpy whose target precomputes dst/src into pseudos + `addu`s them into $a0/$a1 (vs a direct load) ⇒ write a struct-assign, not an explicit `memcpy()`.** (The prior session tried every *call* form — casts, K&R, builtin ±`-fno-builtin` — but never the struct-assign; no calls.c was needed.)

**(2) THE -O0 REACH-134 ×134 ROLLOUT — per-overlay -O0 split + a shared HEADER (not a DEFINE_ macro).** An -O0 function that is reach-134 (byte-identical in all 134 overlays because it refs only SHARED globals, not per-overlay data — unlike the Phase-20 overlay-local -O0 cluster) still propagates ×134, but NOT via a `DEFINE_func_X()` in an -O2 TU: it only matches at -O0 and gcc-2.7.2 has no per-fn -O0 pragma. Mechanism (`tools/rollout_whale_o0.py`, `tools/split_whale.py`): each overlay's single .c is splat-emitted in vram order, so a **line-based split at the whale's INCLUDE_ASM line** carves it with zero item-parsing (before → keeps the `<ov>` name + `nonmatchings/<ov>` asm paths; whale → its own -O0 object `<ov>_o0b`; after → `<ov>_after` with asm paths rewritten). The whale's C lives ONCE in a shared **header** `src/shared/func_80144B9C.h` (NOT a DEFINE_ macro — its 7 local typedefs make a 200-line `\`-continued macro fragile; a plain header is clean, and the typedefs stay TU-local because `<ov>_o0b.c` includes only `common.h` + this header, never `engine_core.h`). One Makefile wildcard rule `$(WHALE_O0B_OBJS): CC1FLAGS := -O0` compiles every `<ov>_o0b.o` at -O0. Registered as an **h_exact dedup group whose `source` is the header** — this works because `dedup_integrate.group_members` keys only on (binary, vram); a header-share is as valid as a macro-share. **Reusable for any -O0 reach-134 giant** (verify h_exact reach FIRST, R14 — an -O0 fn is only ×134 if it refs shared globals; the Phase-20 -O0 cluster was overlay-local ×1).

**(3) THE memcpy SYMBOL — an `__asm__` label, not a shared rename, and never a two-symbol alias.** The struct-assign emits `jal memcpy` (gcc hardcodes the libfunc name). `0x8005C324` IS memcpy (`libc2/MEMCPY.o`) but the overlays auto-name it `func_8005C324`. Resolve it in the **overlay-only** symbol file `symbols.resident.txt` (`memcpy = 0x8005C324`) — NOT `symbols.us.txt`, because **main DEFINES memcpy via MEMCPY.o** and a shared symbol there would multiple-define in main's link. For an EXPLICIT same-address call elsewhere (the `engine_core.h` block-copy macro's *variable-size* memcpys, which can't be struct-assigns), keep the non-builtin C name `func_8005C324` but give its extern an **`__asm__("memcpy")` label**: the literal identifier `memcpy` triggers gcc's built-in-memcpy codegen → byte mismatch, whereas the asm-label emits the same `jal memcpy` under a non-builtin identifier (only a benign "conflicting types for built-in memcpy" *warning*). **splat REJECTS two symbols at one address** (`func_8005C324` + `memcpy` in one symbol file → `error reading …` at extract), so the single-symbol + asm-label is the fix, never an alias pair.

## §39 — The ×1→×134 giant-endgame: propagate a matched **-O2** giant via the NATIVE DEFINE-macro path (Phase 24 T7 §G close, 2026-07-08)

After the whale, two matched-but-×1 reach-134 giants remained — `func_801770E0` (152) and `func_801372B0` (207). The whale-session handoff proposed a hand-rolled `src/shared/<fn>.h` shared header per giant (the §38 whale mechanism). **That was an -O0 necessity, not the -O2 path** — both banked via the ordinary `DEFINE_func_X()` (`engine_core.h`) macro + `dedup_propagate --recover`. Five durable lessons:

**(1) R14 — verify each "×1" claim against the bytes BEFORE acting.** The handoff named THREE ×1 giants; `func_8014E048` was ALREADY ×134 (a 134-member group + `DEFINE_func_8014E048()` in every overlay, done an earlier task — the handoff conflated its earlier ×1 state). Confirm the current member count (`awk` the group's `binaries:` list) + a representative *other* overlay's site (`INCLUDE_ASM` stub vs `DEFINE_`) before "finishing" any function. A stale handoff line is a claim, not ground truth.

**(2) The DEFINE-macro path HANDLES pins/asm/anon-structs — the whale's shared header is -O0-ONLY.** `func_8014E048` (register-`__asm__` pins + volatile-asm barriers), `func_801770E0` (pins + anon-struct `/s` casts), and `func_801372B0` (pins + asm-label externs + zero-byte barriers) ALL propagate ×134 as plain `DEFINE_func_X()` macros — `compiles_standalone` (real cc1, -O2) accepts every one (the handoff's "compiles_standalone REJECTS pin/asm bodies" was WRONG; the real blockers are (3)–(5)). Reach for a whale-style separate-object shared header ONLY when the fn is **-O0 inside an -O2 TU** (gcc-2.7.2 has no per-fn -O0 pragma → it needs its own object). An -O2 giant = the native macro path, full stop.

**(3) THE `overlay_files` POST-WHALE-SPLIT GAP (the reusable fix).** The whale rollout (§38) split every overlay's `<ov>.c` into `<ov>.c`/`<ov>_o0b.c`/`<ov>_after.c`, but `dedup_propagate.overlay_files` only scanned `_a`/`_o0` — so **every function in the post-whale `_after` region was invisible** to dedup_propagate, for BOTH source-def-find (`func_801770E0` → "no source overlay has it matched") AND stub-replacement in the 133 members. Fix = add `_o0b`/`_after` to the suffix list. **Rule: any new per-file split suffix must be added to `overlay_files` or its functions silently can't propagate** (a green per-overlay gate never fires because the site is never found — verify via the fleet `dedup-check` member count, not just the build).

**(4) `find_site`'s backward extern scan STOPS at a non-extern line — keep the extern block contiguous.** `func_801770E0`'s 5 externs had a `/* comment */` on its own line between them; `find_site` collected only the externs below the comment and dropped the 4 above → `compiles_standalone` failed on undeclared callees. Relocate any standalone comment ABOVE the extern block (byte-neutral). (A trailing `extern …; /* … */` comment IS tolerated; a whole comment LINE mid-block is not.)

**(5) LOCAL-TYPEDEF giant → UNIQUE-rename + lift to `engine_types.h`, NEVER the bare name.** `func_801372B0` declared local `SVEC`/`GLINE` typedefs (above the fn, not in the extracted body) → `compiles_standalone` (common.h + engine_types.h only) failed on the undefined types. Critically, a DIFFERENT `SVEC` (u16 fields — a different fn) lives in `_after.c`, so lifting the bare name would double-define with a conflicting layout fleet-wide. Fix: rename to `Svec_801372B0`/`Gline_801372B0` (all occurrences confirmed scoped to the fn's region first), lift the *renamed* types to `engine_types.h` (the plan-builder explicitly allows bodies USING engine_types.h types — only inline `typedef`/named-`struct{` DEFS are rejected), byte-verify the source overlay unchanged (`d19c9580`), then `--recover`. The rename is byte-neutral (pointer-passing + struct-member codegen is layout-driven, not name-driven).

Result: `func_801770E0` + `func_801372B0` ×134, clean fleet 136/136, dedup 1811→1813/0, fleet 65.95→66.02% (byte-weighted gain larger — 152+207-ins giants). The giant endgame's matched set is now fully ×134; the only remaining reach-134 ×1 fns are small (3 propagatable stragglers `0x80174650`/`0x8012A018`/`0x80165CA0` + 17 local-type-blocked) = the T8 tail (Drew's focus directive: giants only, no small sweeps).

## §40 — Structural families: the MECHANICAL symbol-remap (crack one exemplar → remap the rest, ~0 tokens) (Phase 25 T3/T7, 2026-07-08)

**The reframe:** regroup the UNMATCHED frontier by STRUCTURE (`h_norm`) not bytes (`h_exact`). A multi-member
h_norm family = the SAME engine fn recurring at the SAME address across overlays, byte-shattered only because each
member references PER-OVERLAY symbols (its level's data/code addresses). `tools/family_manifest.py` regroups + ranks
them (Phase-25: 2,764 families / 11.1 MB; levers by ov_SC01_077 membership: **draftable** / **matched-free** / **absent**).

**h_norm families are TEMPLATES, not free dedup (byte-proven, R14):** `dedup_propagate --tier h_norm` on a matched
exemplar banks **0/133** siblings — one C body can't name 134 overlays' different symbols (`D_80187xxx` in ov077 vs
`D_8017Fxxx` in ov000). h_norm masks the reloc fields, so h_norm-identical ⟹ diffs are RELOC-ONLY, but the reloc
TARGETS are per-overlay → not shareable by a single body.

**TRAP — `extract_unit` mistook a DECLARATION for a DEFINITION (Phase 26 session 8, R14).** Its guard was
`not ln.rstrip().endswith(";")`, but m2c writes declarations with a trailing comment —
`M2C_UNK func_80178D40(s32, s32);   /* extern */` — so the raw line ends in `*/` and sailed through. The forward
brace-scan then ran past the decl and **swallowed the NEXT function's body**, handing `remap_hseq` a garbage unit.
Measured: **15 of 35** substantial-family exemplars were phantom "matches" (all still `INCLUDE_ASM` stubs,
including `func_80178D40` and the carried-queue `func_801670E4`), and **3 more** anchored on the Phase-17
canonical-sig layer's `extern … /* match-first, arity N */` decls and templated garbage — so those families were
**silently unbankable**. The whole-binary byte-gate rejected every one, so **no wrong match was ever banked**
(G3/P9 held) — but the engine burned a build per sibling on them, and any `extract_unit`-based readiness analysis
was wrong. Fix: strip trailing comments before the `;` test. **The general lesson (the phase's FOURTH silent-skip
bug, after `find_site`'s braces, `overlay_files`' splits, and `reconcile_decls`' fn-ptr regex): a tool that
silently no-ops on input it cannot parse is indistinguishable from a tool that had nothing to do. Prefer
fail-loud on unparsed input, and regression-gate any change to a "proven" text scanner by snapshotting its output
over the whole corpus before/after — that is what caught this.**

**The lever — mechanical per-overlay symbol remap (`tools/family_remap.py`):** two h_norm-identical members have
identical instruction streams except in the masked reloc fields. So disassemble both overlay images at ADDR
(`extracted/retail/<SC>.CD.dir/FILE_<nnn>.dir/0.4.dec`, vram 0x80128158), positionally pair the resolved reloc
targets (jal target; lui/lo combined addr via hi-register tracking — VERIFIED 22/22 vs splat `.s`), and substitute
the exemplar C's per-overlay symbol NAMES (`D_<ADDR>`/`func_<ADDR>`, **UPPERCASE** hex) with the sibling's. Shared
EXE/resident symbols (0x8002xxxx) map to themselves. Result = the sibling's C, generated for ~0 agent tokens.

**The fleet sweep (`tools/family_sweep.py`):** for each matched ov077 fn with unmatched same-address h_norm-siblings,
remap → gate into each sibling. Two-phase (stage all remaps grouped by (overlay,split) → gate each group ONCE) so
it's ~a few hundred builds, not 156×134. **GOTCHAS:** (1) gate remapped drafts with **plain `harvest_verify`**, NOT
`gate_stage`'s canon/cast/sig_unify transforms — they perturb an already-correct remap → 0-bank. (2) `match_one`
**pre-classify** first: type-using families (LOCAL types like `MatEntry`, defined in ov077.c not engine_types.h)
CC1-FAIL in isolation → defer them, else harvest_verify bisection explodes (~30k extra builds); recover with
`build_engine_types.py --source ov_SC01_077 --strip` (lift local types → engine_types.h, byte-neutral) then re-sweep.
(3) `func_` names are UPPERCASE-hex in src + .s filenames.

**Result (matched-free harvest):** **+16,512 member-matches** in ONE deterministic ~0-agent-token pass, R22 clean-fleet
**136/136**, **fleet 66.02% → 70.82%**. The 11.1 MB structural-family frontier is CHEAPLY recoverable: crack ONE
exemplar per family (the only real work — agent/wave), then `family_sweep` fills the ~133 members free. **Transferable**
to ANY overlay/bank-based decomp where a fn recurs per-region with per-region symbols (→ cross-project idea).

### §40a — The DECL-RECONCILE pass (type-lift so remapped drafts compile in the sibling TU) (Phase 25 T7.2, 2026-07-08)

When the matched exemplar's body references a type defined INLINE in the source overlay's `.c`, the mechanical remap
(§40) reproduces that reference — but the type isn't in the SIBLING overlay's TU, so the sibling draft won't compile
(the sweep's `match_one` pre-classify tags it `type/decl`). Fix = lift the type into the shared header every overlay
includes (`src/shared/engine_types.h` via `engine_core.h`), then re-sweep. **+1,729 members** this way (fleet
70.82→71.32%, clean-fleet 136/136). Three load-bearing gotchas:

1. **The pre-classify is a FALSE-NEGATIVE for lifted types.** `family_sweep`'s `match_one` pre-classify compiles the
   draft in ISOLATION (`mipsel-cpp -Iinclude` + a prepended `common.h`) — it does **not** see `src/shared/engine_types.h`
   (that's pulled only by the real overlay TU, via `../shared/engine_core.h`). So a type-lifted family still
   pre-classifies as `type/decl` even though it compiles + byte-matches in the REAL TU. Verify against the real gate,
   not the proxy (R14): a single `harvest_verify` of the remap into one sibling = byte-identical. Use
   **`family_sweep --no-preclassify`** to route every remappable exemplar straight to the real-TU byte-gate (still the
   sole arbiter — a wrong draft is compile-failed/reverted with bounded bisection cost, since the lift makes most compile).

2. **Overlay SPLIT files (`_a`/`_after`/`_o0`) are SEPARATE .o TUs — a blind "lift all splits" is UNSAFE.** Each split
   has its OWN local type namespace, so two splits can define the same-named type with a DIFFERENT layout and never clash
   (different TUs). Lifting such a type fleet-wide `conflicting types for <T>` in the other split's TU. Also, a split may
   locally `typedef … MATRIX/VECTOR` (PsyQ SDK names) — lifting those fleet-wide SHADOWS the real SDK types. So:
   `build_engine_types --file src/<ov>/<ov>_after.c --exclude <colliding names> --strip` lifts one split's types,
   leaving conflicting/​shadowing names TU-local. Detect collisions FIRST (the tool's own `find_defs`/`find_typedefs`
   across all splits + the existing header; a same-name-DIFFERENT-body pair is the landmine). ov077's only cross-split
   collision was `Buf` (`_a`≠`_after`); `_a`'s `MATRIX`/`VECTOR` were the PsyQ shadows → both deferred. Safe mechanical
   ceiling = base types + one non-shadowing split minus its colliders. The rest (cross-TU renames, PsyQ-layout
   verification, -O0 clusters) is genuine per-type reconciliation, NOT mechanical → backlog.

3. **Every lift must be byte-NEUTRAL.** Type defs emit no code, so `--strip` (move def → header) leaves the source
   binary identical — but VERIFY: rebuild the WHOLE source overlay (all splits) and confirm its locked SHA
   (ov077 `d19c9580`) before sweeping. A broken strip / mis-ordered header surfaces as a compile failure or SHA drift
   at this cheap ~30s gate, before any expensive sweep. Then the full R22 clean-fleet 136/136 confirms no fleet-wide
   header collision. Tools: `build_engine_types.py --file/--exclude`, `family_sweep.py --no-preclassify`.

### §40b — The reloc-tracker blind spot: the indexed-global idiom that hid the "reach-1 tail" (Phase 26 Task 1, 2026-07-11, byte-verified V0/V1)

**The discovery (why the "36k unique tail" was largely a measurement artifact).** Both `norm_stream`
(`sig_image.py`) and `reloc_targets` (`family_remap.py`) tracked lui-hi/lo pairs but **popped the pending hi on
ANY R-type write** (`pend.pop(rd)`). gcc-2.7.2's indexed-global access `D[i]` compiles to
`lui $at,%hi(D); addu $at,$at,$idx; lw $v1,%lo(D)($at)` — the **`addu` PRESERVES the hi anchor** (the index shifts
the runtime value, not the symbol). So every function that indexes a per-overlay global array left its `%lo` fields
**raw** in `h_norm` → the function normalized DIFFERENTLY per overlay → it looked **fleet-unique (h_norm reach-1)**
when it is actually a per-location family, AND `family_remap`'s symbol map dropped those indexed `D_` symbols →
the sibling draft kept the exemplar's array name → **byte-gate fail** (an earlier "unremappable" wall).

**The fix (≤15 LOC, `reloc_targets` R-type branch only — NOT `norm_stream`).** On `add`/`addu` (funct 0x20/0x21),
propagate the pending hi to `rd` when a source reg holds one, else pop:
```python
elif op == 0:                       # R-type
    funct = w & 0x3F; rd = (w >> 11) & 0x1F
    if funct in (0x20, 0x21):        # add/addu: address arithmetic preserves the hi anchor
        rs, rt = (w>>21)&0x1F, (w>>16)&0x1F
        if rs in pend:   pend[rd] = pend[rs]
        elif rt in pend: pend[rd] = pend[rt]
        else:            pend.pop(rd, None)
    else:                pend.pop(rd, None)
```
The `%lo` resolution is unchanged (`pend[rs] + signext(lo)` = the symbol; the index is a runtime reg). **Leave
`sig_image.norm_stream` / `h_norm` UNTOUCHED** — the fleet metrics, the proven h_norm sweep, and the manifest all
depend on its stable (blind) hashing; the h_seq family key (mnemonic skeleton) is unaffected by the tracker, so
families still cluster correctly, and the fix only makes the SYMBOL PAIRING correct so the remapped body byte-matches.

**Verified (build-free, V0/V1 `2026-07-11`):** `func_801407F4` resolves **15/15 relocs vs splat `.s`** (pre-fix: 10),
recovering the indexed arrays `D_80187B88/90/B0`; `func_80141100` (no idiom) stays **22/22 identical** (zero regression);
across 160 real h_norm sibling pairs the new `remap` output is byte-identical to the committed pre-fix output (96 SAME,
**0 lost**), differing only where it strictly recovers indexed relocs. Reproduce: `.run/v0_reloc.py`, `.run/v1_regression.py`.

**Companion fix — single-pass simultaneous substitution.** The old `remap` applied renames **sequentially**
(`for src,dst: re.sub`), which corrupts a chained/permuted map (`D_A→D_B` then `D_B→D_C`, or an immediate value
permutation `0x10→0xA & 0x4→0x10`). Never tripped on h_norm data (disjoint exemplar/sibling address spaces) but the
h_seq imm engine (T2a `imm_map_tier1`/`remap_hseq`) needs it: build ONE `\b(alt|…)\b` regex over the full table (symbols ∪ self-rename ∪
immediates), replace via a dict lookup on the match — each source token is matched once against the ORIGINAL text.
This is also where the T2b **cross-address** self-rename (`func_<FROM>`→`func_<TO>`, definition + recursion) and the
T2a immediate `imm_map` merge into one pass. `remap(addr, from_ov, to_ov, to_addr=None, imm_map=None)` — backward
compatible (to_addr defaults to addr; the pre-26 same-address callers are byte-unchanged).

### §40c — The h_seq per-sibling reconcile: templating a reconcile-class crack ×134 (Phase 26 Task 8, 2026-07-12, byte-proven)

A cracked exemplar whose body needs `canon_sig_reconcile` to bank (type-using / Ghidra-sig — the §41 def-side
wall) **cannot template plainly**: the reconciled ov077 body is TU-SPECIFIC (its canonical-sig casts +
`Name_<addr>` collision-renames fit ov077, not the sibling TUs). Plain `remap_hseq` of the reconciled body
re-hits the wall in every sibling → 0/134. Proven (Task-8 validation slice): the 23 triage isolation-cracks
gate 0/23 raw, reconcile 4/15 into ov077, but the 4 then template **0/4** plainly.

**The fix — per-sibling re-reconcile from the RAW draft** (the h_seq port of §41c's h_norm M2 path):
`family_sweep --hseq --reconcile-raw <RAWDIR>` → for each sibling, `family_remap.remap_hseq_body` h_seq-remaps
the RAW crack draft (symbol §40b + immediate T2a + cross-address self-rename T2b) then `canon_sig_reconcile`
re-reconciles against THAT sibling's own TU. The whole-binary byte-gate is the sole arbiter. Byte-proven:
the 4 triage cracks templated **463/0 ×~133** this way (0 failures). This is the pipeline every reconcile-class
crack (the type-using triage cracks AND the Fable5 cores) flows through to reach ×134. PURE cracks (clean
bodies, no reconcile) still template via plain `--hseq` (Task 5: 399 banked). Key: reconcile PER SIBLING from
the RAW draft, never remap the ov077-reconciled body.

### §31-triage — R17 applies to CODEGEN residuals, never to a compile ERROR (Phase 26 session 7, Drew asked)

Before reaching for `tools/reference/gcc-2.7.2/` or the `docs/gcc-2.7.2-map/`, classify the failure:

| Symptom | Cause | Tool |
|---|---|---|
| The build SUCCEEDS but the bytes differ | a codegen decision (regalloc / sched / cross-jump / CSE / loop) | **R17** — read the pass, or gdb-on-cc1 (§45-B) |
| The build FAILS to compile (`conflicting types`, `undeclared`, `parse error`) | plain C89 semantics — gcc is CORRECT | **our tooling.** Reading gcc source tells you nothing |

Byte-example: the `func_8015AE2C` ×133 sweep blocker is `conflicting types for D_801812A4` — two incompatible
file-scope decls of one identifier in one TU. That is not a gcc quirk; `reconcile_decls` was picking a
**fleet-majority** canonical type instead of the type the TU can actually SEE (its §8b carried decl layer).
A `loop.c`/`global.c` read would have been pure waste. Contrast `func_8017BEBC` (close=2, an `allocno`-priority
tie in `global.c`): compiles fine, wrong bytes → exactly an R17/§45-B target.

**Rule of thumb: "wrong BYTES" → read the compiler. "won't COMPILE" → read our Python.**

## §41 — The DEF-SIDE canonical-sig wall: mechanically banking a drafted giant past `conflicting types` (Phase 25 T5b batch-2, 2026-07-09; `tools/canon_sig_reconcile.py`, byte-proven on `func_8013B274`)

**The wall (dominant for GIANTS — ~universal, vs ~35% clean-bank for small fns):** a drafter writes an
**isolation-MATCH** giant body (`match_one` c=0) with Ghidra-derived **TYPED** params — `void func(u32 *a0, s16 *a2)`.
Placed in the real overlay TU it fails the whole-binary gate on `conflicting types for func_X` (a *declaration*
conflict, NOT a byte diff). The gate's `sig_unify`/`cast_call_sites` can't fix it and it banks **0/16**. Two sources:
1. The TU's callers reference the fn through the **CANONICAL signature** declared in `src/shared/engine_core.h`
   (`extern void func_8013B274(s32 a0, s32 a1, void *a2);`) — but that decl lives **inside a `DEFINE_func_*` macro**,
   so `sig_unify` (which rewrites file-scope externs) never sees it. The draft's typed sig conflicts with it.
2. Absent an engine_core.h decl, a caller *above* the definition gives gcc-2.7.2 an implicit K&R `int func_X()`;
   the draft's `void`/typed-param def conflicts with that. (This is *why* the overlay's "Phase-17 canonical-sig
   layer" at each `_a.c` top uses `s32 func(s32,…)` — it's K&R-`int`-compatible AND byte-neutral.)

**The crack — reconcile the DEF to the canonical sig, BYTE-NEUTRALLY (3 steps, all proven on `func_8013B274` → banked
`d19c9580` byte-identical):**
1. **Strip the draft's redefinitions of ambient symbols.** A `typedef … P_TAG;` identical to `engine_types.h`'s is a
   *redefinition error* in gcc-2.7.2/C89 (not "compatible" like C11). Strip identical-def typedefs; strip `extern`
   decls (func / data `D_*` / `memcpy`) the TU or engine headers already declare — the draft's Ghidra-typed
   re-declaration is a conflict source. (`memcpy` always: a mismatched prototype trips `conflicting types for
   built-in memcpy`; the TU macros / builtin provide it.)
2. **Rewrite the def signature to the canonical** (`engine_core.h` decl if present, else the implicit-int-compatible
   `s32 func(s32,…)` at the draft's arity; arity-grow adds unused params so an N-arg implicit caller still matches).
3. **Cast each type-changed param AT ITS USES — NEVER via an intermediate local.** THE load-bearing insight:
   `u32 *a0 = (u32*)arg0;` at the top introduces a *fresh pseudo* → gcc allocates it a different reg → **regalloc
   shifts → byte diff** (measured: cast-locals gave `70ff4748`, wrong). Casting the param in place —
   `((s16*)a2)[i]`, `((s16*)param + 1)` (preserves stride!), `*(T*)p` — adds **no pseudo**, is free, and preserves the
   isolation-match codegen. `tools/canon_sig_reconcile.py` blanket-wraps every use of a changed param in
   `((origtype)name)` (correct for index/deref/arith/member/already-cast alike). Give it `--tu <split.c>` so it treats
   that TU's already-declared symbols as ambient (strips their redundant draft externs too).

**Result:** **5/16** batch-2 giants banked purely mechanically (`func_8013B274 80130D48 80167DBC 8016DC20 8018514C`);
3 then `family_sweep`'d **×134**. This is the phase's **#1 def-side lever**, now partly automated — reusable across the
whole giant tier AND the batch-1 backlog of "match_one-MATCH but gate-rejected" near-misses (the dominant gate-failure).

**The residual walls (the other 11 — genuine per-fn T7, NOT this mechanical pass; backlogged with cause):**
(a) **non-identical ambient types** — draft's `SVEC`/`ApplyMatrixSV` differ in layout from `engine_types.h`'s (can't
strip: not identical; can't keep: conflicts) → needs a rename or a real layout reconcile. (b) **data symbols declared
inside `DEFINE_` macros** (`D_80078EB0`) — macro-local, not file-scope, so stripping the draft's extern leaves the body
referencing an undeclared symbol, and keeping it conflicts → `reconcile_decls.py`/§33 byte-neutral-access-cast territory.
(c) primitive-typedef redefs the reconcile missed; (d) genuine **byte-diff** (reconcile compiles but codegen differs —
back to permuter/hand). **Sweep fragility:** a reconciled body carries ov_SC01_077-specific canonical sigs/casts, so
`family_sweep` to sibling overlays (with their OWN engine_core.h decls) byte-matches only some siblings (`func_8016DC20`
= 133 siblings failed → exemplar-only). A robust sweep of reconciled giants must re-reconcile per sibling TU (T7 follow-up).

### §41a — v3.1: the def-side wall was ~71% TOOL-shaped — the five measured defects + the laws that dissolve them (Phase 25 T6, Fable5, 2026-07-09)

The T6 curriculum session R14-re-verified ALL 95 draftable-exemplar stubs (every draft in every
`.run/drafts-t5*` dir, best-of, `match_one`): **62/95 are genuine isolation-MATCH** — the frontier's
"match" statuses were honest, and all 11 batch-2 "walls" + the 3 `_o0` giants have byte-correct bodies.
A 6-iteration probe program (reconcile → splice into the REAL TU → full `cpp|cc1|maspsx|as` →
relocation-masked byte-compare of the fn inside the TU object, `.run/t6_reconcile_probe*.json`) then
decomposed the §41 wall into **five mechanical defects of the v1 reconcile itself** — fixed in
`tools/canon_sig_reconcile.py` v3.1, taking the mechanically-bankable set **10 → 44 of 62** (4,254 ins,
13 giants ≥145; `func_8013DD68` gate-validated byte-identical through `make build`):

1. **Scalar-typedef dups** (`typedef … u8;`) must be stripped (C89 redef error) — same set match_one
   strips. Was 11 fns of "redef:u8/u16/s16/s8".
2. **Canonical truth = the PREPROCESSED TU's file scope** (cpp + brace-depth-0 scan), not a token-scan:
   token-scanning counted macro/block-scope names as ambient (over-strip → `undeclared`) and missed the
   TU's own decl of the fn (self-`conflicting types`). NB: a `DEFINE_` macro's extern lands at FILE
   scope when the macro is instantiated at file scope — and gcc-2.7.2 REMEMBERS block-scope extern
   types TU-wide, so both kinds bind later defs.
3. **Never strip a draft extern — BLOCK-SCOPE-MOVE it (types verbatim) when no decl is visible above
   the splice point.** The draft's extern types are LOAD-BEARING (%lo-folding, access width, alignment:
   an ambient-type rewrite byte-drifted 18/62 — e.g. `((s16**)&u8_sym)` derefs at alignment 1 → lwl/lwr).
   Block-scope decls are private and legal even when a DIFFERENT file-scope decl exists below
   (recover_giant's idiom, generalized). Visible-above + identical → drop; visible-above + different →
   ambient + cast-at-use (fn callees per §17a-1; data via access-casts — alignment caveat above routes
   the narrower-object cases to §33/reconcile_decls TU-retype instead).
4. **Colliding typedefs are RENAMED** (`Vec3 → Vec3_<addr>`, attribute-tolerant), never
   layout-reconciled: type names emit no code, so the def side NEVER has a real layout problem
   (SVEC/Vec3/Prim/S8/ApplyMatrixSV walls all fell to the rename — 2 giants banked).
5. **Blanket use-site substitutions must skip decl lines** ("decl lines are never cast" —
   cast_call_sites' rule; violating it emits `extern void ((void(*)(…))f)(…)` parse errors). Also: find
   the def on a COMMENT-MASKED copy (drafts' @stuck headers quote the sig and mis-anchor the rewrite).

**The residue is three real classes (T6 curriculum tiers M3/M4/F):** (a) **arity conflicts with a
visible typed prototype** (a banked caller's macro declares `void f(void*)` arity-1, the byte-true def
needs 3 params) — no draft transform can fix; the cure is the fix_arity_callers-class **no-proto rewrite
of the engine_core.h macro extern** (`extern s32 f();`, byte-neutral for the loose callers), R22-gated —
6 fns. (b) **stale TU decl types** from earlier banked drafts (u8 vs s16* on D_801870B0 etc.) →
`reconcile_decls`/§33 fleet-majority retype, then the drafts bank verbatim — 8 fns. (c) genuine per-fn
residue — 4 fns (incl. `func_80166994`'s real mixed-arity loose-typing entanglement).

**The ×134 sweep law (Q5, 6/6 proven):** sweep the RAW draft via `family_remap.symbol_map`, then
**re-run canon_sig_reconcile against EACH SIBLING's own TU**, then gate. §41's "sweep fragility" was
exactly the missing per-sibling re-reconcile (the ov077-reconciled text carries ov077-specific
decisions). Sibling stubs live in the SAME split-file name fleet-wide (`_after` etc. — the whale-rollout
structure); read the asm subdir off the sibling's INCLUDE_ASM line.

**Refuted:** the batch-3 "-O0 in-context byte-diff needs an -O0-specific reconcile" — all 3 `_o0`
giants (329/198/154 ins) probe BANKABLE at -O0 under v3.1 unchanged; the old diagnosis was v1's
declaration perturbation, not a -O0 return-type law.

**Probe-method notes (reusable):** the in-TU masked byte-compare (`insns_from_object(tu_o, fn)` vs
`insns_from_s(splat_s)`) is a fast, link-free gate proxy — but it is **jal-symbol-blind** (mask eats
the target field), so `harvest_verify` stays the arbiter (G3/P9). And **never hand-type a SHA**: a
mistyped `--good-sha` made a byte-perfect gate run report MISMATCH — read it from `config/check.*.sha`.

### §41b — T7 execution: the object-only probe OVER-counts BANKABLE by two link/rodata classes (Phase 25 T7-M1, 2026-07-10)

Executing the §41a curriculum banked **37 of the 40** non-jumptable M1 exemplars byte-identical through the
whole-binary gate (`tools/t7_bank.py`: reconcile-at-bank-time + `harvest_verify`, chunk-bet with per-round
re-reconcile for cross-fn ambient mutation). The 7-fn gap between the T6 probe's "44 BANKABLE" and reality is
**two integration classes the T6 in-TU masked object-compare could not see** — a sharper statement of "probe ≠
gate" (R14): the probe compiles to an OBJECT and masks jal/%hi/%lo, so it is blind to both *rodata* and *link*.

1. **Switch jump tables in rodata (4 fns: the 3 `_o0` giants + `func_8012ACE0`).** Their `.text` is byte-perfect
   — the unmasked diff is 100% `j .L…` / `lui/addiu %hi/%lo(jtbl_…)`, all masked-EQ, **zero real `.text`
   diffs** — but the switch emits a **jump table in rodata** (`jtbl_801D836C` …) that the object-only compare
   never looked at, and the whole-binary SHA diverges there. **This REFUTES the T6 curriculum's "Q3 -O0
   reconcile REFUTED" claim** (the probe said the `_o0` giants bank; the gate says no) — the batch-3
   "in-context byte-diff" finding STANDS. Route: the jump-table-in-rodata workflow (cookbook §8, the LZSS/§5a
   precedent — carve/match the `jtbl_*` rodata), F-band, NOT mechanical M1.

2. **Last-referencer link-wall (3 fns: `func_8016D688`/`D_801D9C20`, `func_8016D1D8`/`D_801D9C20`+`D_801D9C60`,
   `func_80165240`/`D_8018977C`).** The fn is the ONLY asm referencer of a scratch data symbol; splat
   auto-generates that symbol into `undefined_syms_auto.txt` *from the disassembly*, so C-ifying the last
   referencer **drops the symbol** → `ld: undefined reference to D_801D9C20`. Compiles clean, fails at LINK
   (the object-only probe never links). Fix (M-linkwall tier): declare the symbol so ld resolves it — a manual
   undefined-syms entry or a splat data-symbol carve at that address (the bytes already live in the overlay
   image). Deferred pending the splat symbol-provisioning mechanics (don't guess an address into the byte-locked
   build). Reusable class: ANY bank that removes the last asm reference to an overlay-local data/scratch symbol.

**Method upgrade for future curricula:** an in-TU object probe is a necessary filter but NOT the gate — it
misses rodata (jump tables, float/string pools) and all link-time resolution. Size a "mechanical" tier from
the WHOLE-BINARY gate on a sample, or expect a ~15% object-probe over-count and treat the surplus as the two
classes above. `tools/t7_bank.py` (reconcile-per-round + chunk-bisection) is the reusable M1 driver.

### §41c — T7-M2: the ×134 def-side-wall sweep via per-sibling RE-reconcile (Phase 25, 2026-07-10; 4,389 banks, ~0 agent tokens)

§40's mechanical `family_remap` (symbol-remap a matched exemplar → sibling) banks **0** for the def-side-wall
giants: the ov077-reconciled body carries ov077-specific block-scope-vs-ambient decisions, and each sibling's
DIFFERENT decompile state (different fns banked above the splice) needs those decisions RE-COMPUTED. The
Q5-proven fix, now `tools/family_sweep.py --reconcile <rawdir>`: per (exemplar, sibling), symbol-remap the
**RAW** draft (source→sibling via `family_remap.symbol_map`) then **re-run `canon_sig_reconcile` v3.2 against
THAT sibling's TU**, then the plain whole-binary byte-gate. `engine_core.h` is SHARED so the canonical sig is
identical fleet-wide; only the per-overlay symbol names + the sibling's visible-above set change.

**Result: 4,389 of 4,655 member-remaps banked (94%)** across 133 overlays for the 35 M1 exemplars — fleet
**72.29% → 73.58%** (+1.29%), R22 clean-fleet **136/136**, dedup-check 1813/0. The 266 misses are per-sibling
loose-typing walls (the sibling banked a conflicting-type neighbor) → backlog. Cost: local cpp+build only,
zero agent tokens. **Cost note:** the per-member re-reconcile runs cpp on the sibling TU prefix for
`visible_above` — ~2 s/member (≈45 min staging for 4,655), then the group gate. `_AMBIENT_CACHE`/`_VISIBLE_CACHE`
are cleared per sibling-TU inside the sweep (the sibling source is static during phase-1 staging, so the caches
stay valid across exemplars for one TU). **This is the endgame's economic engine for the def-side-wall giants:
crack + reconcile ONE exemplar, sweep it ×134 mechanically.**

### §41b addendum — M4 "reconcile_decls" tier is ALSO a probe over-count: 0/8 mechanical (Phase 25 T7-M4, 2026-07-10)

The T6 curriculum's third "mechanical" sub-tier (M4: 8 object-probe BYTEDRIFT fns projected to bank via a
`reconcile_decls` §33 TU-retype) is **REFUTED by the whole-binary gate: 0/8 bank** (`reconcile_decls → canon_sig_reconcile → gate`).
Root cause, same R14 pattern as §41b's jumptable/linkwall: the T6 object-probe's "BYTEDRIFT" does NOT imply a
data-type conflict. **4 of the 8 have `reconcile_decls` "touched 0"** — no data decl even differs from the
fleet-canonical — so their in-TU drift is pure codegen (scheduling ORDER: e.g. `func_8013E83C` reads
`D_80115118` before the prologue in the target; `volatile`-loss: `func_801418F8`'s `D_8011511A` read-back;
callee interactions). The other 4 have real data-decl differences but `reconcile_decls`' byte-neutral cast
still perturbs the schedule. **These 8 are F-band** (byte-correct in ISOLATION — match_one c=0 — but drift
8–69 in the real TU) → permuter-ILS / §31, not a mechanical tier. `reconcile_decls` remains valid ONLY for a
genuine data-TYPE conflict where the cast is schedule-invariant (its §33 giant proofs); it is not a driftfix.

**Net honest tally of the T6 "mechanical" projection (58 fns / ~2.5 MB):** truly mechanical = M1 37 + M3-clean 2
= 39 exemplars (banked + swept ×134 = ~4,694 fleet fns, fleet 72.29→73.66%). The other 19 were probe
over-counts → F-band/specialist: 8 M4 (codegen drift) + 4 jumptable (rodata) + 3 linkwall (undefined-sym) +
4 M3-residue (arity/loose-typing). **Lesson (reinforces §41b): size a "mechanical" tier from the WHOLE-BINARY
gate on a full sample, never from an object-only probe — it can't see rodata, link, OR in-TU codegen
perturbation. Expect ~⅓ of an object-probe "BYTEDRIFT/COMPILE-FAIL" bucket to be genuine per-fn work.**

### §41d — `void`→`s32` is NOT always byte-neutral: gate the RAW draft FIRST (Phase 26 session 6, byte-proven)

**R14 correction to the Phase-17 canonical convention.** The canonical-sig form ("`s32` return — `void`→`s32`
is byte-neutral, §3a-1") is **false for a `void` body with no `return` statement**: promoting the return type
makes gcc-2.7.2 emit **one extra instruction**. Byte-proven on `func_80182268` (31-ins jr, ov_SC01_077):

| draft | result |
|---|---|
| `void func_80182268(void *a0)` (raw) | **MATCH, 31 ins** |
| `s32 func_80182268(void *a0)` (return type alone) | DIFF, **32 ins** |
| `s32 func_80182268(s32 a0)` (what `canon_sig_reconcile` emits) | DIFF, **32 ins** |

The extra word is invisible in a leaf diff but **lethal whole-binary**: it pushed the isolated object's `.text`
4 bytes long, shifting every data symbol +4 → ~271,000 differing bytes and a 5-byte-longer image. `match_one`
said MATCH; only the whole-binary gate caught it (G3/P9 again).

**The rule (generalizing §19's `sig_unify` lesson): every recovery pass is a FALLBACK, never unconditional.**
`canon_sig_reconcile` exists to break the §41 def-side wall — it must not run on a draft that already compiles.
`jtbl_family_bank` now gates **raw → (on failure) reconciled**, and `canon_sig_reconcile` only promotes the
return type when a canonical extern actually demands it. Corollary: a function with **no** canonical decl
anywhere (grep `engine_core.h` + the overlay `.c`) should be banked exactly as drafted.

## §42 — The F-band ≤28 regalloc crack wave: register-pin/DENSITY levers beat the permuter (Phase 25 T7 F-band, 2026-07-10; Ultracode 9-worker wave, 4/9 banked byte-identical, 266 swept ×134)

The F-near ≤28 band (14 fns / ~1,393 ins, one ov_SC01_077 h_norm exemplar each) is **regalloc-order-DOMINATED**
(9 of 14 = saved-register `$sN` allocation/ordering swaps). The permuter is **structurally blind** to this class:
it mutates C source, and pycparser rejects `register __asm__` (§5a/§17), so a pure `$sN`-allocation swap has no
source-mutation reachable. **Empirically proven this wave:** permuter-ILS (regalloc-directed `_REGALLOC` weights,
8×120 s warm-restart) plateaued at base on EVERY regalloc fn (func_80134C20 stuck@3; schedule-class func_8017EF50
stuck@4, func_80168828 8→5) — **0 closed**. A 9-worker Ultracode wave applying MANUAL §17/§31 levers cracked
**7/9 to byte-0 in isolation**, of which **4 banked byte-identical** through the whole-binary gate.

**The winning levers (all zero-runtime-code, semantics-preserving; full RTL in `subagents/workflows/wf_0329d3c2-75c/`):**
1. **The §31 DENSITY lever (the workhorse for `$sN` races).** To win a razor-thin saved-reg allocation, ADD a
   zero-byte dead-read `__asm__ __volatile__("" :: "r"(v));` on the pseudo you want gcc to prefer — it bumps `v`'s
   ref-count so the local-alloc density heuristic gives it the contested `$sN`. **Calibrate the COUNT exactly**
   (func_80134C20: ONE dead-read of the master reclaims `$s5`; TWO over-boost it into `$s4` → 13-off). Proven:
   func_80134C20 (230, MATCH), func_801365B8 (155, 11→2).
2. **The opaque asm-COPY for a param live-range split.** `__asm__("addu %0,%1,$zero" : "=r"(copy) : "r"(orig));`
   (or the §17 in-place re-tie `__asm__("" : "=r"(p) : "0"((T)p));`) forces gcc to keep `orig` in its incoming arg
   reg for early reads while `copy` carries the later reg — reproducing the target's single-pseudo live-range split.
   Proven: func_8017B614 (RC-9 hoist-vs-remat, MATCH). CAVEAT: reorg.c forbids `__asm__` in a delay slot, so an
   asm-copy that must fall in one lands a slot early (func_801365B8's irreducible 2-off).
3. **Frame-pad induction:** `s32 pad[2]; (void)&pad;` — address-taken-then-discarded local defeats -O2 DCE, reserves
   8 unused var_size bytes to match a target frame (0x20 vs 0x18), shifting every save offset; `(void)&pad` emits
   zero code. Proven: func_80141A60 (MATCH). **CAVEAT: frame-pad is ov077-specific — its 133 h_norm siblings ALL
   byte-drift on remap (each sibling's natural frame differs) → frame-pad families are EXEMPLAR-ONLY, NOT ×134-sweepable.**
4. **Array-initializer LUID shift:** `s32 a[2] = {x, y};` vs two `a[0]=x; a[1]=y;` reorders the const-materialization
   LUIDs → sched2 emits the callee-save stores before the const chain (matches a target prologue-weave, S7). Proven:
   func_80180F10 (MATCH).
5. **u16* zero-extend for a high-bit halfword store constant:** storing 0x8000+ through `unsigned short *` zero-extends
   → `ori $r,$zero,0xFFF8` (opcode 0x34) vs `short *`'s sign-extend `addiu`/`li -8` (0x24). func_80141A60.

**DIRECT `register T v __asm__("$21")` pins OFTEN BACKFIRE on giants** — they wreck the prologue save-birthing order
and clobber the dead pinned regs (func_80134C20: direct pins = 97-off vs density = MATCH; func_80180F10: pin = 37-off
vs array-init = MATCH). **Reach for the DENSITY lever first; use hard pins only when the residual is a clean,
uncontested-reg home** (the `dont-conclude-unsteerable` memory still holds: try SOMETHING before declaring a wall,
but density > pins on the giants).

**Attrition — isolation-MATCH ≠ real-TU bank (reinforces §41b):** 7 iso-MATCH → **4 banked, 3 real-TU byte-drift**
(compile OK, byte-differs). func_8017B614's drift = the **T1 memcpy-builtin→call class** (the sibling TU's
`extern memcpy` disables the builtin, so the worker's inlined lwl/lwr block-move lowers to a CALL) → re-crack with
field-by-field or explicit `memcpy(x,y,8)`. func_801365B8 = a GENUINE irreducible cse-representative conflict → G4/INCLUDE_ASM candidate.

**Tooling gotchas (each cost a false-fail cycle):** (a) `harvest_verify.py` for a NON-resident binary MUST pass
`--out build/<bin>/<bin>` — its `build()` removes+sha1s `--out` (default `build/resident/resident`), so an overlay run
without it reports "final SHA None"/fail for EVERY draft even when byte-identical. (b) `canon_sig_reconcile` can't
extract a def whose body has a fn-pointer cast `((s32(*)(...))func)` — such a draft banks RAW (no reconcile) if its
sig is already canonical (func_80180F10). (c) R22 clean-fleet: `make clean` nukes the WHOLE splat tree (asm/); `make
extract` re-splits only the DEFAULT binary — you must `make extract BINARY=$b` for ALL 136, else 135 fail "can't open .s"
(a build-infra false-fail, not a byte mismatch).

**Wave economics:** 9 xHigh workers ≈ 1.66 M subagent tokens → 4 banked + 266 swept ×134 = **~270 fleet fns**. The ≤28
regalloc band is genuine frontier — budget ~40-50% bank-rate per wave, NOT the mechanical tiers' ~94%.

### §42a addendum — wave 2 (residuals + 29-100 band): iso-MATCH ≠ real-TU bank, the memcpy→struct-assign fix, +5 levers (2026-07-10b)

**THE #1 LESSON — a crack worker must verify against the RECONCILED REAL TU, not isolation.** Wave 2's 14 workers
produced 9 iso-MATCHes but only **4 banked** — **5 iso-MATCHes DRIFTED** in the real overlay TU (func_80136824/
80164930/8014DD8C/8016C188/80168828). The ONE iso-drift fn that banked (func_8017B614) did so because its worker
**embedded the def into a scratch copy of the real split `.c`, compiled the WHOLE TU (builtins ON = the real
condition), and objdump-compared** to the isolation MATCH — catching the drift cause and fixing it. isolation
`match_one` uses `-Iinclude`+prepended common.h; the real TU adds engine_core.h types, a `memcpy` decl, and the
reconciled sig — any of which shifts codegen. **Wave-3+ crack prompt MUST require: after iso-MATCH, splice into a
scratch copy of `src/ov_SC01_077/<split>.c`, `cc1` the TU, and confirm the target fn's bytes are identical modulo
link relocation — THEN report MATCH.** (Cheap: one extra TU compile per worker; converts ~50% real-TU attrition to near-0.)

**The memcpy-builtin→CALL fix (extends the T1 class, byte-proven func_8017B614):** a small fixed-size mem-copy written
as `memcpy(x,y,8)` inlines to lwl/lwr/swl/swr in ISOLATION but lowers to a `jal memcpy` CALL in any TU that declares
`extern memcpy` (a sibling triggers `conflicting types for built-in function memcpy`, disabling the builtin TU-wide) →
byte-drift. **FIX:** `typedef struct { u8 b[8]; } Blk8;  *(Blk8*)dst = *(Blk8*)src;` — struct-assign routes through
`emit_block_move` (identical lwl/lwr/swl/swr bytes) but references NO `memcpy` SYMBOL, so it is immune to the
builtin-disable. Mirrors the codebase's own family idiom (matched sibling func_8017B368 uses `(*(SV4*)&D_x)=loc;`).
Verify with `cc1 -fno-builtin`: struct-assign still emits lwl/lwr; the memcpy draft emits `jal memcpy`.

**Five lever refinements (wave-2 journal `wf_dbadb86a-6b7`):**
1. **`register int` NOT `register short` for a pin whose value is already sign-extended** (an `lh` result) — `register
   int g __asm__("$6"); g = *(short*)p;` pins to $a2 with no `sll/sra` penalty; `register short` re-adds the extend
   (func_8017EF50).
2. **Never density-dead-read a pseudo that is LIVE ACROSS A BLOCK** — the `__asm__("":: "r"(v))` adds a real
   instruction (count+1) and backfires; instead RESTRUCTURE the pseudo away (compute fresh at each use) (func_80136824).
3. **When density fails, use STATEMENT-BLOCK reordering for `$v0/$v1` birth order** — group the var you want in $v0 so
   it is first-born + dense; density dead-reads that must keep a var live past its consuming `sll` produce the wrong
   schedule (func_80164930).
4. **Birthing-boost coupling: a single-set const-load (`li $v1,0x40`) sinks to just before its EARLIEST-scheduled
   consumer, not to its C statement position** — to move the load, reorder the CONSUMER store-block, not the assignment
   (func_80168828).
5. **for-init LUID ordering controls the delay slot** — `for (i=0, lim=0x19, p=P; i<N; i++)` makes `i=0` win the beqz
   delay slot and emits `lim` before the pointer `lui/addiu`; a plain pre-loop `int lim=…;` captures the delay slot
   instead (func_80164930).

**Wave-2 economics:** 14 workers ≈ 2.47 M tok → 4 banked + 399 swept = **~403 fleet fns**. Bank-rate 4/9 iso-MATCH —
LOWER than wave 1 (real-TU attrition), fixable by the real-TU-verify rule above. The 5 nears (func_80134A74 71→16,
func_80133AB0 →28 aligned, func_8012FCC4 beqz/jal delay-swap, func_80185BA4 65, func_801670E4 70 "irreducible") are
permuter-ILS fuel / G4 candidates.

### §42b addendum — wave 3 (Max, 2026-07-10c): THE STALE-OBJECT GATE TRAP + the read-global `&`-cast drift + fix

**THE #1 METHODOLOGY BUG (invalidated wave-2's "iso-drift" labels; fix ALL gates).** A per-function real-TU
check that does `make build BINARY=<ov> >/dev/null 2>&1` and then runs `asm-differ -o <fn>` **without checking
the build exit code and without removing the split `.o` first** will diff a **STALE object** whenever the build
FAILS — reporting a phantom **score 0 / "MATCH"** for a draft that never compiled. Measured this wave: three
wave-2 "iso-drift" fns (func_8016C188, func_80168828, func_80136824) read as score-0 on the first pass, then
**NOCOMPILE** on a forced-clean pass (`rm build/src/<ov>/<split>.o` + exit-code check). Root cause of the false
score: the stale `.o` from a prior good build survives the failed compile, and `asm-differ -o` happily diffs it.
**This is almost certainly why wave 2 mis-classified 5 fns as "iso-MATCH → drift"** — several likely never
compiled in the real TU at all. **MANDATORY gate shape (now in `.run/crack3/diff.sh`):** `git checkout <split>` →
splice → `rm build/src/<ov>/<split>.o` → `make build BINARY=<ov>` and **assert exit 0** → `sha1sum` the built
binary vs `config/check.<ov>.sha` (the real whole-binary arbiter) → only THEN `asm-differ -o` for the diff view.
Never trust a piped `make build` you didn't exit-check. (Compounds with the §42a `--out` gotcha — both produce
false PASS/FAIL on overlays.)

**The `*(T*)&D_sym` read-global drift (a `canon_sig_reconcile` defect) + the fix — byte-proven on func_80164930.**
`canon_sig_reconcile` rewrites an ambient-conflicting global access as `*(u16*)&D_sym` (cast-at-use, to dodge a
type conflict). For a **write-only** global this is byte-neutral (`lui at,%hi; sh v,%lo(at)` — direct addressing).
For a **read** (esp. read-modify-write) global it **DRIFTS**: `&D_sym` forces gcc to materialize the FULL address
into a held register (`lui a0,%hi; addiu a0,a0,%lo; lhu v0,0(a0)`) instead of the target's direct
`lui v0,%hi; lhu v0,%lo(D_sym)(v0)` — and it reuses that held reg for the store, shifting the whole schedule.
**The wall:** the target read needs `lhu` (u16) but the ambient TU decl is `s16`; a block-scoped
`extern unsigned short D_sym` inside the fn is a **hard `conflicting types` ERROR** in gcc-2.7.2 (cc1 exit 33,
NOT a warning — signed/unsigned short mismatch). **The fix:** flip the **file-scope** decl to the exact type
(`extern s16 D_8018971C;` → `extern u16 D_8018971C;`) — byte-neutral when the only other referencer is store-only
(func_801647A4 stores `= 0x80` → `sh` either way) — and reference the global **directly** (no `*(T*)&`). Result:
whole-overlay `d19c9580` BYTE-IDENTICAL, func_801647A4 unaffected. **General rule for drafters/reconcile:** a
read global that needs a specific load width (`lhu`/`lh`) must be a **direct-typed lvalue at file scope**, never
`*(T*)&sym`; align the whole TU on one type rather than casting at use. **Sweep caveat:** the file-scope-decl
flip is per-TU, so `family_sweep --reconcile` must also flip each sibling's decl (or the sibling's caller must be
an unmatched stub with no conflicting decl) — else siblings NOCOMPILE like the frame-pad class (§42 lever 3).

**Wave-3 consequence:** the wave-2 `uc2_gate_*` drafts are **not** reliable seeds — several NOCOMPILE (unreconciled
callee externs conflicting with the TU canonical-sig layer, e.g. `conflicting types for func_80015954`) and the
"iso-MATCH" labels were stale-object phantoms. Wave-3 targets must be **re-reconciled + rigorously rebuilt** per fn
(the `.run/crack3/` harness), not gated from the wave-2 artifacts. Confirmed banks this wave: **func_80164930**
(the read-global fix above).

### §42c addendum — wave 3 (Max orchestrator + CORRECTED Ultracode fan-out, 2026-07-10c): the real-TU-faithful parallel harness (rtu_match) + 7/9 crack, ZERO iso-drift

**THE TOOL that makes a reliable crack fan-out possible — `tools/rtu_match.py` (real-TU-faithful, parallel-safe).**
Wave-2 workers self-checked in ISOLATION (match_one), blind to in-TU decl/global-type/memcpy-builtin drift, so their
iso-MATCHes drifted at the whole-binary gate (~50% attrition). FIX: compile the WHOLE split `.c` with the candidate
spliced and INCLUDE_ASM neutralized (`-DINCLUDE_ASM(a,b)=` + `-Isrc/<source>` for the relative `../shared` include)
→ masked-diff the fn. No `asm/`, no shared overlay build → many workers run in PARALLEL in per-fn temp dirs. Because
gcc-2.7.2 -O2 compiles each global fn independently, the neutralized whole-TU compile reproduces the exact ambient
context, so a `rtu_match` MATCH HOLDS at the whole-binary gate. **Measured: 7 real-TU MATCHes → 7/7 banked
byte-identical (individually + combined `d19c9580`), ZERO drift** (vs wave-2's ~50%). Corrected fan-out = 9 xHigh
workers ~1.27 M tok → 7 MATCH + 2 DIFF(→permuter). This is the reusable engine for the phase tail: reconcile-first
+ rtu_match-gated + the levers below. Supports `//@EDIT old||new` file-scope pre-edits.

**DURABLE LEVERS from the 7 cracks (all rtu_match-byte-gated):**
1. **Callee-ARITY unblocks a delay-slot "steal" (func_8012FCC4 — the "irreducible" that wasn't).** A spurious extra
   register arg on a callee that is LIVE ACROSS the call blocks gcc reorg `fill_slots_from_thread` from sharing a
   downstream constant into a branch delay slot (reads as an irreducible ~3-off beqz/jal delay swap). **Before
   conceding a delay-slot residual as irreducible, RE-DERIVE THE CALLEE ARITY FROM THE ASM**: drop the bogus arg →
   the target schedule falls out of stock reorg, no barrier/pin/mutation.
2. **Pointer-holding global via `*(T**)&sym` → `lui;lw %lo`(load ptr)+`lh off(ptr)`(deref) (func_80136824).** A
   file-scope `extern u8 D_x` that actually HOLDS a pointer: read as `(*(s16**)&D_x)[i]`. Byte-neutral vs the u8 decl.
3. **Array-decay CSE (func_80136824, the load-bearing extra):** reading `extern s32 D_x[]` (ARRAY) as `*(s16**)&D_x`
   or `D_x[0]` makes gcc CSE the decayed BASE addr into a held reg (`lui;addiu;lw 0(reg)` reused) vs the target's
   per-use direct `lui;lw %lo(sym)`. FIX: `//@EDIT extern s32 D_x[];||extern s16 *D_x;` (flip to a SCALAR POINTER).
   (Scalar u8 symbols fold %lo fine; only the array decays.)
4. **§17 zero-reg-copy `x + zr` for a delay-slot-SAFE live-range copy (func_80134A74):** `register u32 zr __asm__("$0"); y = x + zr;`
   copies a pseudo with NO `__asm__` op, so it CAN land in a branch delay slot (an `__asm__` volatile copy cannot, and
   disrupts delay-fill → +1 ins). Use to hoist a masked value into a bnez delay slot / before a range-check.
5. **void→s32 flip for a discarded-return callee decl (func_8014DD8C):** when a fn truly returns a value (`addiu $v0,1`)
   but a shared `DEFINE_func_*` macro in engine_core.h declares it `extern void` and the caller DISCARDS the return,
   flip that macro-internal extern `void`→`s32` (byte-neutral fleet-wide; stops the void-decl DCE'ing the return).
   R22-confirm fleet neutrality. Precedent: §20 func_8014EE14.
6. **register-arg capture into a NORMAL pseudo for a callee-saved param (func_80168828, SWEEP-SAFE, no //@EDIT):**
   to force incoming `$a0` into a callee-saved reg (target `addu $s1,$a0,$zero`): declare the fn `(void)`, then
   `register s32 a0v __asm__("$4"); s32 param_1 = a0v;`. The copy into a normal pseudo (live across calls) gets a
   callee-saved home. A direct `register ... __asm__("$4")` leaves it in call-clobbered $a0 (wrong frame → 100-off).
7. **Free-floating load temp for a scheduler hoist (func_8016C188):** extracting an arg-load into its own statement
   (`s32 t34 = *(s32*)(s1+0x34);`) lets the scheduler hoist it early to fill a load-delay slot (vs pinned late by the
   call) — closed 63 mismatches at once.

**block-extern-vs-definition is an ERROR, not a warning (func_80133AB0/8014DD8C):** in gcc-2.7.2 a block-scope
`extern` whose sig conflicts with the function's own DEFINITION hard-errors (cc1 exit 33). A TU that forward-decls the
fn with a wrong/loose sig must be reconciled (match the def's sig; `//@EDIT` the caller decl when it discards the
return or the arg is already the right width in-register). The dominant "reconcile-first" wall for the F-band exemplars.

**The 2 DIFFs (permuter tier), seeds in `.run/crack3/wave3/`:** func_801670E4 (70→48; block birth-order levers landed,
"assign p/i late" shape from sibling func_8016A290) and func_80185BA4 (structurally 177/177, pure scheduler +
caller-saved temp-numbering residual, no responsive C lever) — decomp-permuter fuel.

### §42d addendum — wave 4 (rtu_match fan-out over the mapped frontier, 2026-07-10c): 24/26 MATCH, +5 durable levers

**META-YIELD (validates the frontier-map "reconcile-first" bucket):** a 26-worker rtu_match fan-out over the
tractable-band draftable exemplars (the frontier map, `docs/phase25-frontier-map.md`) landed **24/26 MATCH**
(20 banked byte-identical, 2 permuter, 4 needing per-fn link/drift fixes). Confirmed: **for the F-band exemplars,
reconcile-first is often the WHOLE fix** — several (func_80131B14) were byte-correct in the body and only their
TU-canonical decl layer conflicted; strip/align the decls → MATCH with no schedule/regalloc grind. The engine =
reconcile-first + rtu_match-gated + the §42/§42c/§42d levers.

**NEW / generalized durable levers:**
1. **Return-type flip goes BOTH ways (generalizes §42c #5).** If a fn genuinely RETURNS a value but a discarding
   caller's decl says `void`, flip the decl `void`→`s32`/`short` (func_8014FE60, func_8016CF04) — the void decl
   DCE's the return computation. INVERSELY (func_8016DF5C): if a fn is effectively VOID (bare `return;`) but the
   draft declares it `s32`, flip `s32`→`void` — an s32 return keeps `$v0` LIVE at the epilogue, blocking reorg's
   eager fall-through delay-slot steal (a single-instruction cascade). Read the asm: does `$v0` carry a value out?
2. **Address-recompute-vs-CACHE — the unifying read-global rule (subsumes §42b read-global + §42c array-decay CSE).**
   Taking `&D_sym` (via `*(T*)&sym` or a cached local ptr) makes gcc materialize the symbol address into ONE reg
   (`lui;addiu`) and **CSE it across all uses** → FEWER `lui` than a target that recomputes `%hi/%lo` per reference
   (direct global access). When the target shows a fresh `lui $scratch,%hi; op %lo(sym)` at EACH use, declare the
   global directly at the right type/scope (`extern volatile unsigned short D_x;` etc.) and reference it plainly —
   never `&sym`. When the target instead HOLDS the address in a reg across uses, cache it (`T* p = ...;`). Same
   root cause behind func_80164930, func_80136824, func_801418F8, func_80136334.
3. **The full-inline-asm TRAMPOLINE idiom (func_8014FBC0, the 22×1996 family).** The scratchpad-stack-switch
   trampolines (func_8014F468/F6F4/FA04/FCFC/…) are hand-asm: the callee symbol AND the global live INSIDE the
   `__asm__` string (`%hi`/`%lo` escaped as `%%`), so ZERO C externs are declared → nothing to reconcile. maspsx
   2.56 auto-fills the `jal` delay slot with a nop (do NOT write an explicit post-jal nop). **family_remap must
   substitute the callee/global symbols INSIDE the inline-asm string, not as C extern lines** (the x134 sweep of an
   inline-asm family needs this — else siblings drop).
4. **memcpy→struct-assign, re-confirmed at scale (func_8017B238, §42a):** the TU's file-scope `extern memcpy`
   disables the builtin → 8-byte moves lower to CALLs; model on the matched sibling's align-1 `typedef struct{u8 b[8];}`
   struct-assign (routes emit_block_move, zero memcpy ref). Pair with the `register u8* __asm__("$16")` +
   in-place re-tie pin to hold the src pointer across the moves.
5. **phantom-frame induction (func_80136334, §42-refined):** a value live across BOTH arms of a branch makes gcc
   reserve a spill slot the no-frame twin lacks — induce the frame with `s32 frame_pad[2]; (void)&frame_pad;`.

**Wave-4 economics:** 26 workers ~2.36 M tok → 24 MATCH → 20 banked + swept ×134. Bank-rate 20/24 at the
whole-binary gate (4 hit rtu-blind link-walls / drift — rtu_match is `.text`-only, §41b/§42b caveat; those need the
whole-binary/link gate). The 2 permuter DIFFs: func_8012E364 (c=4), func_801549F8 (c=3, jtbl delay-slot).

### §42e — propagating a CRACK ×134: the def-finder bug + the byte-drift residual (the "remap-fail" misdiagnosis)

Cracked F-band exemplars don't all propagate ×134 through `family_sweep --reconcile` — waves 3/4 dropped ~1,200
siblings. Diagnosis (a two-layer story; both matter for future sweeps):

1. **THE def-finder BUG (`canon_sig_reconcile`, fixed) — mislabeled "remap-fail".** `family_sweep`'s `reconcile_remap`
   returns None on ANY failure and the caller counts it as "remap-fail", but `family_remap` itself SUCCEEDS (verify with
   `tools/family_remap.py --addr … --from … --to …` — it pairs the symbols fine). The real None came from
   `canon_sig_reconcile.reconcile` raising **"no definition of func_X found in draft"**: its def-finder regex required a
   leading `\n` (`\n(<type> fn(...)){`), but a raw draft whose `//@EDIT` header lines were stripped has the fn
   **definition on line 1** → no match. FIX: `\n` → `(?:^|\n)` (also match a def at draft start). This alone fully
   recovered func_8014FE60 (133/133 siblings) once paired with its shared-header return-type flip.
2. **THE byte-drift residual (the genuine `--edit-remap` work).** Families cracked with a **file-scope `//@EDIT`** (the
   array-decay pointer flip §42c#3, the no-proto flip) or a **shared-header return-type flip** (§42d#1) reconcile per
   sibling but BYTE-DRIFT, because those edits live OUTSIDE the function body that `family_sweep` remaps: the pointer/
   no-proto `//@EDIT` targets per-overlay decls (must be symbol-remapped + applied per sibling), and the return-type
   flip targets the ONE shared engine_core.h macro (apply once, globally — like func_8016CF04/8014FE60). `family_sweep`
   carries neither. So a `--edit-remap` = {per-sibling: remap the exemplar's `//@EDIT` symbols and apply to the sibling
   split; once: apply any shared-header flip globally} recovers this class. func_8016DF5C/80136334/8013D9B0/80156044
   are the backlog exemplars.

**Forward rule (frontier-map leverage realism):** a crack's ×134 is only free if its body is self-contained (no
`//@EDIT`, no shared-header flip). Before counting a cracked family's ×134, note whether it carries out-of-body edits;
if so it's exemplar+`--edit-remap`, not exemplar×134-free. **LESSON (R14):** trace a tool's real exception, not its
summary label — "remap-fail" was a swallowed reconcile-throw two layers down.

**BUILT + measured (Phase-25 task B, 2026-07-10):** `family_sweep --edit-remap MANIFEST` (JSON: per family, `edits`
= split-scope `//@EDIT old||new` in EXEMPLAR symbols, symbol-remapped per sibling via `family_remap.symbol_map`;
`ec_edits` = once-global `engine_core.h` flips, byte-neutral). Per sibling it applies the remapped edits to the split
+ stages the `family_remap` body + gates the (overlay,split) group via plain `harvest_verify`. Orphaned edits from a
failed sibling are byte-neutral (R22-checked). Manifest at `.run/edit_remap_manifest.json`.

**THE CC1-CRASH WALL (the decisive R14 finding — only 2 of the 6 backlog families recovered):** the whole-binary
byte-gate is the sole arbiter, and it revealed that **out-of-body-edit families split into two classes:**
- **array-decay pointer-flip** (`extern s32 D_x[];`→`extern s16 *D_x;`, a per-overlay symbol) — **recovers cleanly
  ×134.** `func_80136824` + `func_80136334` → **266/266 siblings banked byte-identical, 0 failed** (2×133). Light
  register pressure; `family_remap` body + the remapped split-edit is sufficient (no reconcile, no extern injection).
- **register-pin-heavy** (GTE 20-pin bodies `func_8013D9B0`/`func_8016DF5C`; an exotic `register int zr __asm__("$0")`
  zero-register pin `func_80133AB0`; the inline-asm trampoline `func_80156044`) — the original verdict here was
  **"cc1-2.7.2 SIGABRTs compiling the *sibling* TU… ov077-TU-context-specific… NOT mechanically ×134-recoverable, stay
  exemplar-only (×1)."** ⚠️ **REFUTED — Phase-27 (Fable5 characterization, `.run/giants/pin_crash_sigabrt.md`).** See
  the corrected verdict below; the pin-×1 ceiling was a STAGING-TOOL artefact, not a compiler wall, and it is fixed.

**§42e-CORRECTION — the "pin-crash wall" is the `extract_unit` macro-drop, not the pins (Phase-27 T5 + SIGABRT
characterization, 2026-07-15).** The SIGABRT is real and now exactly located — **`gcc-2.7.2/sched.c:2725`,
`create_reg_dead_note()`: `if (dead_notes == 0) abort();`**, a sched1 REG_DEAD-note conservation bug (flow places the
pinned reg's death on the fall-through path; sched1's clobber-aware per-block recount demands a death note for a
use-after-call in the CALL's block, whose harvested note-pool is empty → abort; backtrace `abort ←
create_reg_dead_note ← attach_deaths ← attach_deaths_insn ← schedule_block`). **But it was TRIGGERED by
`family_remap.extract_unit` dropping the body's file-scope `#define` dependencies**, not by any TU context:
- **Of the 4 "crash-walled" families only `func_8013D9B0` ever genuinely SIGABRTed** — and only because the dropped
  `gte_*` macros became implicit-declaration CALLS, putting its caller-saved pins into the fatal shape. The other
  three were **exit-33 plumbing** (a dropped multi-line typedef `func_80133AB0`; a dropped single-line typedef
  `func_8016DF5C`; the one-line-wrapper false-positive `func_80156044`) **misfiled as crashes** because the era
  one-big-split gate shared a TU compile with d9b0 and reported its Error-134 for all of them (the R14 lesson,
  recursed: one exit code folded three distinct failures into a phantom "universal SIGABRT").
- **Properly staged, all four compile CLEAN in sibling TUs:** `func_80133AB0` 133/133 (today AND at the era commit),
  `func_8013D9B0` 133/133 (today, fleet-swept), df5c + x6044 spot-proven. **T5's `_carry_macros` fixes (a) the
  `#define` drop**; (b) multi-line typedefs route through the `engine_types.h` lift; (c) the one-line-wrapper
  false-positive is already fixed by the current comment-strip guard; (d) per-sibling decl flips are `--edit-remap`.
- **The fatal-pin predicate (checkable at DRAFT time, probe-matrix-proven):** FATAL = a `register T x __asm__("$N")`
  pin where `$N` is **caller-saved** ($2–$15, $24, $25), the value is **used after a CALL_INSN**, and the post-call
  use has a **branch-dependent use-then-conditionally-set** shape. SAFE = callee-saved pins ($16–$23, $30) in any
  shape; caller-saved pins whose live range never crosses a call; use-only or single-level-conditional shapes; `$0`
  pins. (12-line minimal repro + probe matrix in `pin_crash_sigabrt.md`; `-fno-schedule-insns`/-O1 suppresses it —
  a safe "is this the dead-notes bug?" probe, useless for matching.) So ov077 banked these pins precisely because,
  in its TU (macros present), no pin crossed a real call.
- **DIAGNOSTIC (R14, corrected):** exit **134** + the `create_reg_dead_note` backtrace = this bug, always; exit **33**
  = ordinary decl/typedef plumbing. Distinguish them (T4 surfaces cc1 stderr; don't fold both into "cc1-crash").
- **Takeaway:** the pin-×1 ceiling does NOT exist — **P31's pin-propagation route is OPEN.** Route pin-heavy families
  back to the mechanical `family_sweep` harvest (macros now carried); byte-identity per sibling is the byte-gate's
  question, but cc1-crash is no longer a barrier. (Array-decay pointer-flip families were never affected and still
  recover cleanly ×134.)

## §43 — The K&R s16-param definition DISSOLVES the "narrow-param wall" for by-value register args (Phase 25 task A, Fable5 crack of the 369-ins giant `func_80166994` ×134, 2026-07-11)

§17/§29 called a def with **narrow-scalar by-value params** an *irreducible* wall: it can't be no-proto-relaxed
(K&R default-promotion "changes the ABI") and often can't match the TU's `s32` canon-sig prototype → stub it.
A Fable5 giant crack **byte-proves that verdict is too broad for s16** (and s32) by-value params.

**The refinement — use a K&R definition:**
```c
s32 func_X(param_1, param_2, param_3, param_4)
    s32 param_1; s16 param_2; s16 param_3; s16 param_4;   /* K&R: params declared narrow */
{ ... }
```
On MIPS all four args arrive in `$a0–$a3` as 32-bit words. K&R **promotes the `s16` params to `int` for the
PROTOTYPE** — ABI-identical to the canon-sig `s32(s32,s32,s32,s32)` (so **no `conflicting types`, no `//@EDIT`
for the param types**) — while the BODY still treats them as `s16`, producing the target's **lazy per-use
in-place narrow/extend**: `sll aN,aN,16 ; sra aN,aN,16` on the *arg register itself*, with the raw values
stashed to callee-saved pseudos first (s3←a1 …) and re-extended per use after calls. The `(s16)param_of_s32`
cast form CANNOT reproduce this — it extends into fresh `v0/v1` temps instead.

**Triage tell (read it off the diff):** target does `sll aN,aN,16` **in place** on an arg reg + copies the raw
`aN` elsewhere *first* ⇒ true s16 param ⇒ K&R form. Extends into `v0/v1` temps ⇒ it's a cast-of-s32, keep s32.

**The return-type flip pair (void-return value-drop):** if the def returns `s32` but the ambient decls say
`void`, gcc-2.7.2 **discards `return expr;` in a void fn** (pedwarn) → you lose the target's exit
materializations (`addiu v0,zero,1` / `addu v0,zero,zero`). Fix = flip `void`→`s32` at BOTH:
- (a) the **split** canon-sig decl (`//@EDIT void func_X(...);||s32 func_X(...);`) — a self-fn decl, EXEMPLAR-
  SPECIFIC (the canon-sig layer put it in ov077; **siblings usually have 0 of these** → make the split-edit
  OPTIONAL in `family_sweep --edit-remap`: apply where present, never skip — the byte-gate is the arbiter), and
- (b) the **engine_core.h** `DEFINE_func_*` externs (`ec_edit`, once-global, **byte-neutral** because every
  caller discards the result — the func_80156044 trampoline precedent, now for a real returning fn).

**Zero-footprint body ⇒ ×134-clean:** put ALL typedefs + externs **block-scope inside the function** (a
conflicting *file-scope* typed extern is a hard cc1 error, exit 33, not a warning). Access a global as
`&((Struct *)D_xxx)[i]` over an ambient-compatible `extern u8 D_xxx[];`. **No `register __asm__` pins** → it
propagates ×134 via `family_sweep --edit-remap` with **no cc1-crash** (contrast the pin-heavy §42e families
that SIGABRT in sibling TUs — structural cracks are the ×134-safe ones).

**Scope (byte-tested = s16 only):** proven for **s16** by-value register params. `u16`/`u8`/`s8`/`float`
by-value, and any narrow param accessed via **memory** (sh/sw width differences), remain §29 walls until
byte-tested. So §29's blanket "narrow-param wall" narrows to **"narrow params that aren't s16/s32-by-value in
an arg register."**

**Flywheel (R16):** this idiom is now **cheap-Opus-applicable** — no Fable5 needed — for any giant whose diff
shows the in-place-`sll` triage tell. Check each remaining giant for the s16-param class before spending the
Fable5 tier. (Also caught: the prior wave's `@stuck: none — MATCH` note on `func_80166994` was **stale/false**
— match_one re-ran DIFF 366/369; verify a "MATCH" claim against the bytes, R14, never trust a stale note.)

## §44 — The Phase-25 cheap-Opus giant batch: 5 structural levers + the §43 extension (2026-07-11, 6 crackers over the frontier giants)

A 6-agent **cheap-Opus** batch (each applying §43 + §31 + the giant recipe, escalate-if-new-class) over the 6
frontier giants (209–399 ins, all reach-134): **3 banked ×134** (`func_80166994` §43; `func_80135480`;
`func_80163EC8`), **4 pin-free/light-pin Fable5 seeds** (the intrinsic wall), and **5 reusable levers**. Meta-
lesson: **cheap-Opus-first was right** — 3 giants + 5 levers + clean seeds for far less than 6× Fable5 — and
**§43 does NOT universally transfer**: only 1 of 6 was a K&R-s16 case; each giant is its own class.

**Lever 1 — §43 EXTENSION (widen the triage).** The §43 tell "in-place `sll aN,aN,16` on an arg reg" is too
narrow. If the target holds `arg0` in **two callee regs** (a non-coalesced duplicate, e.g. `move s6,a0; move
s7,s6` — one for a sign-test, one for a mask-test), the K&R `s16 arg0;` def **reproduces that duplication with
zero pins** even when the sign-extend lands on the callee **stash** (`sll $sN,16`), not on `$aN`. `(s16)cast`
collapses it to one reg. **Rule:** try the K&R s16 form whenever the target shows a duplicate-`arg0` pattern,
not only the in-place-`$aN` tell. (`func_80133CD4`.)

**Lever 2 — pointer-var decl (avoid the `&sym` CSE-hoist).** A held global pointer the target reloads per use:
declare it `extern u16 *D_xxx` and access it **directly** (`D_xxx[i]`), NOT via `(*(u16 **)&D_xxx)[i]`. The
`&D_xxx` form CSE-hoists the address into a callee reg (one `lui;addiu`, reused); the direct pointer-var form
emits a fresh `lui %hi; lw %lo` per use — matching the target's reload pattern. (`func_80133CD4`,
`func_80135480`.)

**Lever 3 — block-scoped-pointer-split (local-alloc a reused output pointer).** A single pointer reused to
write **multiple output-store groups across separate return tails** becomes a **global allocno pinned to one
register**, so it can't match a target that uses a different reg per tail. **Split each store-group into its
OWN block-scoped `set-once / used-N / dies-once` pointer** → each becomes a **local-alloc pseudo** that picks
the per-window lowest-free scratch, reproducing the target's per-tail allocation AND un-sticking coupled
delay-slot fills elsewhere in the schedule. Pin-free. (`func_80135480`, 258 ins; §31 RC-4 extension.)

**Lever 4 — cross-jump the duplicated tail (steer a "permuter-only" dbr class).** For a shared reset/exit tail
whose target shows **call-arg-hoist into a branch delay slot + per-predecessor const-rematerialization**: write
the tail **duplicated inline in BOTH predecessors**, NOT as one shared `goto` block. gcc-2.7.2 `jump.c`
**cross-jumps** the two copies, reproducing the exact dbr schedule (the call arg hoisted into the `bnez` delay
slot serving both paths; the mask re-materialized per-predecessor in the `j`/`beq` delay slots, sharing a reg
with the neighbouring `lh`). This cracks a residual §31 files under **D1/D2 as permuter-only** — it is
**steerable**. (`func_80163EC8`, 234 ins; one benign `$v0` pin.)

**Lever 5 — the "intrinsic wall" (what cheap-Opus canNOT do → Fable5/permuter).** The **§37 allocno-tie /
RC-6 pressure-lock / scheduling-position** class: a pin-free structural seed floats at close 30–67 but the
residual is a **whole-function register permutation or a schedule-position tie-break that no C-lever reaches**
at the Opus tier — a caller-vs-callee allocno *heuristic* choice (`func_80133CD4` s0v→$v0-vs-$s0). The cheap
tier's job here is to produce a **pin-free, structurally-complete seed** (correct body + count, zero file-scope
footprint) and **hand off honestly** (no forced/pinned false match). Escalation: **Fable5 with
`tools/reference/gcc-2.7.2/` and the §34 gdb-on-cc1 `find_reg`/`post_mark_life` method** (it reads the
allocator's actual decision), or the pin-free seed → decomp-permuter.
> ⚠️ **Phase-27 reclassification (regalloc-map §H, `.run/giants/*.fable.md`):** the three functions this lever
> once cited as intrinsic — `func_8014D820` "RC-6 pressure-lock", `func_8016CBC0` "coalescing knife-edge",
> `func_801670E4` "i=0/p co-location" — were each **oracle-refuted**: `func_8016CBC0`'s callee-saved swap CRACKED
> byte-zero (a `floor_log2` density gap, and gcc-2.7.2 has **no** coalescing so "knife-edge" was never the class),
> `func_8014D820`'s block-0 cracked pin-free 261→110 (reused-load-temp serialization; the sched.c:3199 pin was a
> red herring), and `func_801670E4`'s dominant residual is **RC-6 register allocation, not S3 scheduling** (proven
> by the reg_renumber-swap oracle). The pattern (continuing map §F/§G): an "RC-6 intrinsic" verdict is usually
> map-incompleteness — audit for a density/lifetime/merge lever before declaring it. And the old "NEVER ship the
> pinned variant — it SIGABRTs sibling TUs (§42e)" is **corrected** (§42e-CORRECTION): the SIGABRT was a staging
> macro-drop, now fixed; a pin whose live range does not cross a call is safe to propagate. Prefer pin-free still
> (fewer failure modes), but the pinned-×1 ceiling is not real.

## §45 — The flagship `func_80133CD4` crack (399 ins ×134): the merged-variable permutation-breaker + the 1-death local-alloc gate (Phase 25 task A giant escalation, Fable5 gdb-on-cc1, 2026-07-11)

The 399-ins flagship — a "whole-function register permutation" that walled the directed permuter (masked-172) and had been tagged intrinsic for ~22 phases — fell **PIN-FREE (×134-clean)** to a Fable5 gdb-on-cc1 crack (whole-binary byte-gate **BYTE-IDENTICAL** `d19c9580`, banked ×134). Four reusable, byte-proven levers (worked example `.run/giants/func_80133CD4.fable.c`; dumps + gdb oracle in `.run/giants/fable_cd4/`):

**Lever A — MERGED ACCUMULATOR VARIABLES break a "whole-function permutation" (the headline: 378→147 mismatches).** When the target holds ONE `$sN` across **disjoint value-regions** (e.g. `$s0` = {call-3 result → denominator → loop-accumulator}), gcc-2.7.2 global-alloc has **no coalescing** (K8), so one hard reg spanning disjoint regions can only come from **one reused source variable**. Merge the disjoint C variables into one → the allocno becomes call-crossing (K4, `global.c:917`) with a high merged ref-count → top density (K2, `global.c:594 allocno_compare`) → it allocates FIRST → plain regno first-fit (K3) reproduces the ENTIRE callee-saved permutation (the arg0→$s7/$fp end is §43's K&R double-copy). **AUDIT for reused-variable chains BEFORE calling a whole-function permutation "unsteerable"** — it is the original C reusing one variable per accumulator chain, not a compiler mystery. Retires the "N-callee vs N−1-callee permutation" giant-wall class.

**Lever B — the 1-death local-alloc gate + the in-out-asm fix (67→13; found by a gdb ORACLE).** A shared read-temp serialized through one register (target: `lh; lh` into the same reg separated by a byte-visible `nop`) is a **2-SET variable**, which local-alloc REJECTS: `reg_n_deaths != 1` (`local-alloc.c:472`) forces it to a GLOBAL allocno, allocated after every block-local qty → it loses the low-scratch first-fit and the whole caller-saved block permutes. **No pure-C spelling yields 2-sets/1-death** (flow emits REG_DEAD per region `flow.c:2533`; combine's 2-insn merges undo, its split path needs `i1` = 3-insn combos only `combine.c:1737`; cse dissolves every 1-set spelling — all byte-tested). The escape (`flow.c:2511`): **no REG_DEAD when a reg is SET in the same insn it last USES** — expressible ONLY as an **in-out asm** `__asm__("lh %0, off(%2)" : "=r"(h) : "0"(h), "r"(p) : "memory")` (the `"0"(h)` input-tie makes read-2's `lh` use+set `h` in one insn) → 1 death → LOCAL qty → wins `$v0` by qty-birth tie-break → the rest cascade by first-fit. **PIN-FREE / ×134-safe** (generic constraints, real opcode, no hard-reg names — NOT a `register __asm__("$N")` pin → no §42e sibling-TU SIGABRT). The `"memory"` clobber doubles as a delay-slot fence.
- **THE METHOD — the gdb ORACLE (§34 flywheel).** When a hypothesis reduces to ONE compiler-internal quantity, *patch it mid-compile and diff the output* (`break *local_alloc; set reg_n_deaths[h]=1`). One run turns "plausible root cause" into "proven," licensing the (expensive) hunt for the C form that induces it. `-dS`/`-dR` dump sched1/sched2 with per-insn dependence lists on reload-born insns — read those before hand-modeling. In the shipped i386 cc1, `qty_first_reg` lives at `0x82c5404` (the `info address` symbol is stale for this binary).

**Lever C — offset-0 `/s` store asymmetry (last 5 diffs).** `p[0] = x` expands **non-`/s`** `(mem (reg))` while `p[k≥1]` are `mem/s` → a fixed-address (reload-born) load keeps its true-dep ONLY against the offset-0 store (`sched.c:820` drop-clause needs /s+varying on one side, non-/s+fixed on the other). `((struct { s32 w; } *)p)->w = x;` `/s`-ifies the offset-0 store → dep dropped → the load floats to the earlier delay gap. **Store-side twin of §37's load-side `/s` lever.**

**Lever D — goto-shared-return isolates the exit `li` (tail).** A common `return 1` reached by `goto ret1:` gets its OWN basic block → stops sched1 hoisting the exit `li v0,1` into a last-element load-delay slot cross-BB (freeing `$v0` for a trailing temp); dbr still steals the `li` into the branch delay slot. Use when a return-constant materializes one instruction too early.

**Transfer caveat (the §44 meta-lesson holds):** each giant is its own class — Levers A/B are regalloc-**permutation** tools; apply them to a walled giant only when its residual IS a merged-variable or 2-set-temp permutation (read the `.greg`/`.lreg` tell first). The Phase-25 flywheel applies A–D via cheap-Opus to the sibling walled giants (`func_8014D820` RC-6, `func_801670E4`, `func_8016CBC0`), escalating to Fable5 only for a genuinely new class.

## §46 — The `func_80178D40` crack (890 ins ×134, the heaviest core in the game): four LOOP-STRUCTURE levers cheap-Opus found by reading loop.c/jump.c/cse.c (Phase 26 session 8, 2026-07-13)

The heaviest jr core (890 ins, reach 134 = 477 KB) sat at **close=39 with every case byte-exact but one**. All 39
residuals lived in a single 44-instruction case body. **No pins, no permuter** — every residual was *structural*,
and the permuter could not have reached any of them. Cheap-Opus + the §31 map closed it to **MATCH 890/890**.
These four levers are new and general; the classes recur in every loop-bearing overlay function.

**L1 — A loop's `break` must NOT land on the loop's own fall-through label (the PEEL lever).**
When a `break` target *coincides* with the loop's natural fall-through exit, the RTL leaves `NOTE_INSN_LOOP_BEG`
followed by an unconditional jump — which fires `duplicate_loop_exit_test` (`jump.c:2131`, called from
`jump.c:599`). gcc **rotates the loop and peels iteration 1**; if the induction variable is provably 0 the peeled
`i++` const-folds (`li $a2,1`) and drags a whole `lui/addiu/lw` address re-materialization block with it.
**Fix: write `goto <label>;` instead of `break;` — the same destination, a different construct.** It stays a plain
do-while and the peel vanishes. *Tell: an extra address-materialization block and a `li reg,1` at the loop head.*

**L2 — To make a reg-reg COPY survive, split its def and uses across extended basic blocks.**
A source-level `fp = q;` **always dies**: cse's `canon_reg` rewrites later uses back to `q` (`qty_first_reg` keeps
the older register) and flow deletes the dead set. Every "just write the copy in C" variant collapses. But cse
**resets its hash table at a label with >1 predecessor** (a loop top), so a copy defined in a *guard* block and
used only *inside* the loop cannot be propagated away:
```c
if (arg1->a.w != 0) { fp = arg1->a.w; ... do { ... fp ... } while (...); }   /* addu $v1,$v0,$zero survives */
```
**Test the memory, assign inside the branch.** *(Hoisting the same load into the loop preheader instead puts the
copy AFTER the `lui/addiu` — right copy, wrong place.)*

**L3 — A store merged into a shared tail must be written INSIDE the branch that reaches it.**
`if (i != 10) { D_801DAB2C = 3; break; }` lets jump2 tail-merge the `lui/sh` into the shared tail label and lets
reorg steal the `li 3` into the `bne` delay slot. Storing unconditionally *before* the `if` blocks the merge and
costs 3 inline instructions. (Same family as §8's cross-jump-merge-of-direct-stores.)

**L4 — The un-coalesced loop copy = a NON-REPLACEABLE giv, and it needs all THREE parts.**
This copy cannot come from C (see L2); it must come out of loop.c as a reduced giv whose move survives:
  (a) an **index giv** — `p = &D_801DA764[i];` (not a hand-rolled pointer walk);
  (b) the giv is **used outside the loop** (e.g. the "found" body after the loop stores through `p`) → `record_giv`
      (`loop.c:4437`) marks it *non-replaceable* → `emit_insn_after (move dest, new_reg)` at `loop.c:3945`;
  (c) the **biv increment is LAST in the body** — loop.c inserts the reduced giv's `addiu` immediately *before*
      the biv increment, so `i++` at the bottom puts `addiu $a0,$v1,4` into the loop-back **delay slot**. With
      `i++` at the top the giv-add lands at the top, nothing fills the delay slot, and reorg *steals the loop-top
      `move`* into it — duplicating it, +1 instruction (891 vs 890).

**L5 — Two structurally identical loops must differ in a REGISTER, or `cross_jump` merges their tails.**
Loop3 reusing loop1's pointer pseudo put both "found" bodies in `$a0`, made them textually identical, and jump2
**cross-jumped them into one block** (−2 ins). Giving loop3 its own pseudo frees it into `$v1`, so
`sw $zero,0($v1)` ≠ `sw $zero,0($a0)` and the blocks stay distinct. *Corollary of §8's cross-jump lever, inverted:
when you need two tails to STAY separate, separate their registers.*

**Meta (confirms the §44 law + Phase-23's finding).** Every one of these was found by **reading the actual
gcc-2.7.2 passes** (`jump.c`, `loop.c`, `cse.c` in `tools/reference/gcc-2.7.2/`) and none by search: the residual
class was "the compiler produced the wrong BYTES", so **R17 applies and the map/source is the lever**. And the
tier held — *cheap-Opus applying the documented map* cracked the game's heaviest core; Fable5 was not needed.

## §47 — The live-length SLIDER: splitting a global.c allocno-priority TIE with one zero-byte asm (Phase 26 session 8, Fable5 Max, byte-proven on `func_8017BEBC` 952 ins ×113)

The close=2 endgame class: **allocation order and emission order are COUPLED** (both follow creation/LUID
order), but the target needs them to DIFFER. `func_8017BEBC`'s two hoisted invariant addresses (`&g.sz1`,
`&g.sz2`) tie in `allocno_compare` priority; the tie-break is creation order, so natural operand order gives
correct emission + swapped allocation (close=10), and permuting the asm operand list gives correct allocation +
transposed preheader emission (close=2). The permuter provably cannot reach it (not statement-permutable; 25 min,
no close). **The fix decouples them: make the priority difference REAL so the tie-break never fires.**

**The method (no gdb needed — the dumps are the oracle):**
1. Compile with the pinned cc1 + `-dl -dg` (a file input, so `t.i.lreg`/`t.i.greg` appear). Find the two
   preheader `addiu`s in the `.greg` RTL by their `const_int` (the sp offsets), take their insn UIDs, find the
   same UIDs in the `.lreg` RTL to get the PSEUDO numbers, then read each pseudo's line:
   `Register 228 used 13 times across 783 insns` / `Register 230 … across 782 insns`.
2. Compute `pri = (int)((double)(floor_log2(n_refs) · n_refs) / live_length · 10000 · size)` (global.c:594).
   Here: int(390000/783) = **498** = int(390000/782) — an exact int-truncation tie.
3. Find the boundary: the tie splits when the pair straddles an integer of `numerator/L`. Here +1 on both
   (L = 784/783) gives **497 vs 498** — split. (−1 would also split; you can only ADD insns.)
4. **The slider: `__asm__ volatile ("");` placed BETWEEN TWO EXISTING GTE volatile asms** inside the common
   live range. Adjacent to an existing volatile asm it adds NO new cse/sched barrier (one is already there) —
   it is purely +1 static insn at global-alloc time, emitting only `#APP/#NO_APP` (zero bytes).

**Why the split can only go the right way:** the later-created pseudo is defined one insn later in the
preheader and dies at the same last use → it ALWAYS has the shorter live range → `pri(later) ≥ pri(earlier)`,
with equality only on a quantization plateau. Sliding the window off the plateau therefore always hands the
later-created pseudo the earlier allocation — which is exactly the "allocation ≠ creation" the target needs.
(If the target needed the OTHER direction, it would be unreachable by this dial — creation-order permutation
covers that case instead, §45-A.)

- **Placement rule:** next to an existing volatile asm (GTE-heavy functions are full of them). A bare
  `asm("")` elsewhere is a cse table-flush + sched barrier + a maspsx `#APP` hop-killer (§42) — the classic
  perturbation trap. Between two volatile asms all three are already blocked.
- The slider adds +1 live-length to EVERY pseudo spanning the insertion point — any OTHER exact-tie pair
  straddling a boundary could flip. `match_one` verdicts the collateral instantly (here: none; MATCH first try).
- ×N template-safe: the slider is body-local, pin-free, and travels with the template.
- Banked through the §8 whole-binary gate (jr function — match_one alone is NOT the arbiter, §8a): lazy
  isolation → carve (9-piece interleave) → splice → **BYTE-IDENTICAL**. One TU-visible decl reconcile was
  needed on the way (`D_800B9A02` — declare the TU's `short`, force the unsigned access at use
  `(*(u16 *)&D_800B9A02)`, the §8d sub-class (b) hand-move).

## §48 — The 12-core jr crack wave: the ALLOCNO-PRICING dials and the EBB rule (Phase 26 session 8, Ultracode, 9/12 MATCH first pass)

Twelve heaviest unmatched jr cores, one agent each, §31/§46/§47 in the prompt: **9 byte-exact MATCH,
3 near (close=2/2/21), 0 dead ends.** Every crack came from READING the pass (`loop.c`, `jump.c`,
`cse.c`, `global.c`, `local-alloc.c`, `mips.c` in `tools/reference/gcc-2.7.2/`), none from search.
The levers cluster into three families — and the first family is the important one, because it turns
register allocation into something you can **steer from C without changing a byte**.

### A. ALLOCNO-PRICING DIALS — move a value into the register you want, byte-neutrally
All three exploit `global.c:594`  `pri = (int)((double)(floor_log2(n_refs) * n_refs) / live_length * 10000 * size)`.
Higher density allocates first (and first-fit takes the lowest free reg). So **any C edit that changes a
pseudo's refs or live-length while leaving the emitted insns identical is a free register dial.**

- **§48-A1 — SINK THE INIT INTO THE IF/ELSE ARMS** (the biggest of the three; `func_8015A3C8`).
  ```c
  if (c) { min=A; grav=B; }        →   if (c) { min=A; grav=B; hi=0; }
  else   { min=C; grav=D; }            else   { min=C; grav=D; hi=0; }
  hi = 0;                              /* nothing at the join */
  ```
  **Byte-identical**: jump2/cross_jump runs AFTER regalloc and merges the two identical
  `move rD,zero` tails back into the single insn at the join. But at ALLOCATION time the pseudo was
  re-priced: measured 5 refs/318 live → 6 refs/**162** live, priority 314 → 740 — enough to jump two
  other allocnos and take `$s0`. *An init at a merge point is live across every path into the merge;
  the same init duplicated into the arms is not.*
  **Rule: to RAISE a local's priority, sink its initializer into the arms of a preceding if/else.
  To LOWER it, hoist the init to the join.** (Companion to §47's live-length slider: that one shifts
  a length by ±1 to split a tie; this one collapses a length outright.)
- **§48-A2 — the LOCAL-ALLOC `$s0` OCCUPANT** (`func_8015A3C8`). A temp that is (a) referenced in ONE
  basic block and (b) crosses a call gets a callee-saved reg from **local**-alloc, *before* global-alloc
  runs. It lands in `$s0` and enters `regs_used_so_far`, which forces the highest-priority global allocno
  (the `arg0` copy — always first) off `$s0` onto `$s1`. **If the target has arg0 in `$s1`, look for a
  call-crossing block-local temp and give it its own variable.** m2c will happily merge it with a
  same-register variable; that merge destroys the occupant and rotates every `$s` reg.
- **§48-A3 — BLOCK-SCOPED PER-CASE TEMPS ARE A local-alloc TIE GATE** (§44-L3, now source-cited;
  `func_8017A4AC`). A function-scope scratch shared by 9 switch arms is a MULTI-BLOCK pseudo, and
  `local-alloc.c:1765` **refuses to tie** it — so `lhu/sll/sra` gets three different hard regs. Declare
  the temp INSIDE the case and local-alloc ties operand 0 to the dying input, collapsing the chain into
  one register. **In a jr-switch dispatcher, NEVER share a scratch across arms.**

### A4 — SINK THE CONSUMER CALL INTO THE ARMS (the inverse of A1; `func_8016AB6C`, byte-proven)
A1 sinks an *init* to SHORTEN a live range. This sinks the *consumer* to DELETE the allocno outright.
```c
if (c) { s3 = f(A1,P1)+3; p = P1; }      →   if (c) { s3 = f(A1,P1)+3; g(obj,P1); }
else   { s3 = f(A2,P2)+9; p = P2; }          else   { s3 = f(A2,P2)+9; g(obj,P2); }
g(obj, p);                                   /* `p` no longer exists */
```
**The mechanism (why the join-copy is poison).** A value defined in both arms and consumed only by a call in
the join becomes a cross-block **global allocno** whose copy-preferences include the ARG register. And
`find_reg`'s copy-preference override scans `for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)` — **plain ascending
regno, NOT `reg_alloc_order`** — so `$5` (=`$a1`) deterministically beats `$16` (=`$s0`). The only escape is
`allocno_calls_crossed > 0`, which makes `find_reg` set `used1 = call_used_reg_set` (`global.c:906`) and strip
the caller-saved prefs — but a pseudo defined *after* one call and dead *before* the next crosses ZERO calls,
so the arg reg wins and your value lands in `$a1` instead of the target's `$s0`.
**Duplicating the call into both arms deletes the pseudo**: the pointer demotes to a *block-local* that crosses
a call, so **local-alloc** parks it in a callee-saved reg — and that also PRESERVES the §48-A2 `$s0` occupant
that pushes `arg0` onto `$s1`. The duplicated `[addu $a0][addu $a1][jal]` tail is identical in both arms *after
reload*, so **jump2's cross_jump re-merges it into one join block — zero extra bytes** — and dbr fills the jal's
delay slot with the second move.
> **Rule: if a value is defined in both arms and the target keeps it CALLEE-SAVED, duplicate its consumer call
> into the arms. cross_jump refunds the bytes.** (Also note `set_preference`, `global.c:1535`, applies
> `reg_renumber[]` — so a *locally*-allocated pseudo appears in the pref set as its hard reg. That is why `$16`
> was even a contender.)

### B. THE EBB RULE — the general form of §46-L2
**cse resets its hash table at a label with >1 predecessor.** So *anything you need to survive cse must
have its def and its uses in different extended basic blocks.* Three instances, one rule:
- a **reg-reg copy** (§46-L2): `fp = q;` always dies — unless defined in a guard block and used in the loop.
- a **held global address** (`func_8015B950`): `la $sN,&G` in a loop preheader. gcc will NEVER emit this
  from plain global refs (a SYMBOL_REF is already a legal MIPS address), and `s16 *p = &G;` is
  constant-folded straight back by cse's `find_best_addr`. **Fix:** define `p = &G` at the top of the loop
  body and use it only inside a **case body reached through the jump table** — cse starts a fresh table at
  the jtbl target label, cannot see `p == &G` there, the `la` survives, and `loop.c move_movables` hoists
  it to the preheader where global-alloc gives it a callee-saved reg.
- a **pointer-to-global held across calls** (`func_8017A4AC` L2): `struct X *w = &D_SYM;` at function top,
  used deep in a switch arm → survives, spans calls, gets `$s0`.
> **Corollary (`func_8013F350` L2):** a pointer-to-global survives *only if every use is at offset 0*.
> With `p[k]`, k≠0, cse's `fold_rtx` folds the SYMBOL_REF into `CONST(sym+k)` — a legal address — and the
> `la` loses its last user and is rematerialized away. For offset uses you need a **struct** (below).

### C. TYPE- AND SHAPE-DRIVEN CODEGEN (the C type literally selects the addressing mode)
- **§48-C1 — STRUCT vs SCALAR GLOBAL** (`func_8013F350` L1 — verified with 14 micro-probes). A
  **scalar-typed** global always folds to the direct macro (`lui %hi; lhu %lo`). A **struct-typed** global
  accessed by field always materializes a base (`la $b,SYM` + `off($b)`) once there are 2+ struct MEMs in
  the block. **So: target shows `la` + nonzero offsets → declare a struct. Target shows plain `lui/%lo`
  → declare a scalar.** A scalar and a struct at the same address may coexist; declare whichever each
  site needs.
- **§48-C2 — `lwl/lwr/swl/swr` block copy == a plain struct assign of a 2-BYTE-ALIGNED struct**
  (`func_80131340` L1; `mips.c:output_block_move`, vanilla line 2580). The `lw/sw` arm is taken ONLY when
  `bytes>=4 && align>=4`; align 1 AND align 2 both fall through to the unaligned pair. So
  `typedef struct { u16 x,y,z,w; } V; a = b;` emits lwl/lwr+swl/swr even between two 4-aligned stack
  slots. **m2c's `(unaligned s32)` on an 8-byte object means "declare a 4×u16 struct and assign it"** —
  not "hand-roll a byte copy". No memcpy, no packed attribute.
- **§48-C3 — DEAD-SIBLING-SCALAR TRAP** (`func_8017A4AC` L1 — cost 108 instructions). An arm that fills a
  param block and passes its address MUST use a real **array**. Declare `u16 sp18, sp1A, sp1C` and take
  only `&sp18`, and gcc sees the siblings as never-address-taken → their stores are DEAD → flow deletes
  the stores *and the loads feeding them*. **Diagnostic signature: the index chain repeated N times but
  only ONE load.**
- **§48-C4 — CONST BEFORE LOAD** (`func_8015A3C8` L-B): to get `lui` into a branch delay slot, give the
  compare constant a source temp one statement EARLIER, so its def precedes the operand load
  (`lo = -0x94000; t = *p; if (t < lo)`). `gen_int_relational` force_reg's a large compare constant AT
  the compare — i.e. after the load — and sched2 ties on LUID. *Dead end: writing `if (-0x94000 > t)`
  does NOT work; `compare_from_rtx` canonicalizes a CONST_INT op0 back to op1.*

### D. THE CROSS-JUMP RATCHET (the sharpest new trap — `func_80131340` L-C)
Two cases needing **opposite branch senses on the same test** cannot be written as a mirrored `if/else`.
It looks right and even emits the right `blez` — but after cross_jump collapses both bodies to jumps,
`jump.c`'s *"invert a cond-jump that jumps over an uncond-jump"* fires, flipping `blez`→`bgtz`; the two
cases are now byte-identical, so the NEXT cross_jump round swallows the compare entirely (−4 ins).
**cross_jump + jump.c-invert together are a RATCHET toward collapse.** Break it with explicit `goto`s into
labels living inside the *other* case's body: the branch targets become FAR, the invert-over-jump has no
adjacent label to fire on, and only the intended tails merge. (Same family as §46-L5: when two sites must
stay distinct, make them structurally distinct — separate registers, or separate branch targets.)

### E. Meta
- **9/12 first-pass MATCH with cheap agents.** The map is doing the work: every core was cracked by an
  ordinary Opus agent applying documented idioms + reading the pass. The Phase-23 tier doctrine holds —
  Fable5 DISCOVERS a class; everyone else APPLIES it.
- **The `jr` §8a check is mandatory and it caught nothing this time — because it was in the prompt.**
  Every agent verified its `.rodata` table against the target jtbl and reported the evidence. Bake the
  trap into the prompt, not into the post-mortem.
- The 3 near-misses are all pure allocation/emission-order residuals (close=2, 2, 21) — §47-slider class.

## §49 — The LUID DIAL: a zero-byte SCHEDULING dial (the sched.c analogue of §47) — `func_8017A4AC` (536 ins ×134), Phase 26 session 8

§47 splits a **global.c allocno-priority** tie by shifting a live-length. This splits a **sched.c
`rank_for_schedule`** tie by shifting an insn's position in the expand stream. Same philosophy: *when a tie is
broken by an accident of ordering, change the ordering — without changing a single emitted instruction.*

**The residual.** Two adjacent instructions transposed, **registers already identical** — a pure emission-order
residual. Not §47: `global.c` was innocent.

**The mechanism (two passes, and the proximate cause is not the root cause).**
- **sched2 (proximate).** gcc-2.7.2 schedules **BACKWARD** (`.sched2` prints `T-1` = the last insn). At the tie
  point both candidates measured `priority = 2` and the same class vs `last_scheduled_insn`, so
  `rank_for_schedule` fell through to its final tiebreak — `return INSN_LUID (tmp) - INSN_LUID (tmp2);` — i.e.
  **the tie is decided purely by position in the `.greg` stream**.
- **sched1 (root).** `adjust_priority` → `birthing_insn_p` (`bb_live_regs[dest] && reg_n_sets[dest]==1`) hands
  every register-DEFINING insn `LAUNCH_PRIORITY = 0x7f000001` (`max_priority`, sched.c:2574). That boost lets
  the load chain seize the early backward cycles and **sinks** the un-boosted insn past its rivals — so the
  `.greg` LUID order comes out inverted and sched2's tiebreak then picks the wrong one. *(A dead-end store —
  `(set (mem) …)`, never "birthing", priority 2 — is starved and always floats to the front of its block.)*

**THE DIAL — materialize a call argument's sign-extension into an explicit `s32` temp, placed AFTER the
intervening statement.**
```c
case 19: {
    s16 a, b;  s32 ea, eb;
    a = ring[i]; i = (i+1) & 0x1FF;  ea = a;      /* NOT next to the load — see below */
    b = ring[i]; i = (i+1) & 0x1FF;  eb = b;
    f(ea, eb);                                    /* prototype widened to (s32, s32) */
}
```
It moves the `sll/sra 16` pair EARLIER in the expand stream (lowering its `INSN_LUID`) while emitting **exactly
the same instructions**. Two placement rules are load-bearing:
- **The prototype must be `(s32, s32)`** so the call itself adds no conversion.
- **`ea = a;` must sit AFTER the store, not next to the load.** Adjacent to the load, `combine` fuses
  `lhu`+`sll`+`sra` into a single `lh` and you LOSE 3 instructions. The intervening store blocks that fusion,
  so the `sll/sra` pair survives — identical bytes, earlier LUID.

**The zero-byte dial family is now three (all emit nothing; all steer a tie):**
| dial | pass | what it shifts | §  |
|---|---|---|---|
| live-length slider (`asm("")` between two volatile asms) | `global.c` allocno priority | live_length ±1 | §47 |
| sink-the-init / sink-the-consumer-call into the arms | `global.c` / `local-alloc` | refs + live-range, or deletes the allocno | §48-A1/A4 |
| **LUID dial (materialize a temp, placement-controlled)** | **`sched.c` rank_for_schedule** | **INSN_LUID (expand-stream position)** | **§49** |

**Method note (this is how it was measured, and it is reusable):** `-dS -dR` on cc1 emits the `.sched`/`.sched2`
traces — the ready lists, the computed priorities, and the chosen order. When a residual is "two instructions
swapped, same registers", dump the schedule and read the tie: if the priorities are equal, you are on a LUID
tiebreak and the fix is a *placement* change, not a register change. Harness: `.run/a4ac/dump2.sh`.

## §50 — Refinements that BOUND §47/§48 (from the `func_80135EB0` wall, 21→6; Phase 26 session 8)

The one wave core that did NOT close still paid for itself: it produced the exact encoding of the §47 priority
formula, a hard limit on the "cross_jump refunds the bytes" claim in §48-A1/A4, and a maspsx gotcha that
explains a layout choice in the original we had never understood.

**§50-A — THE PRIORITY ENCODING (use this; do not re-derive it).**
`pri = floor_log2(refs) * refs * size / (death − birth)`, where **birth/death are `2 * insn_number`** — and
**death is `2*M`, not `2*M+1`** (discriminated experimentally by the pre/post behaviour of a probe pseudo).
Ties break by **ascending qty number = BIRTH ORDER**. Worked: hoisting one statement above another pushed a
pseudo's birth one insn later, shrinking its qty range 11→10 → pri 0.4545 → **0.5**, exactly tying a rival —
and because its qty is numbered first, it won the tie and took `$v1`. *A tie you can compute is a tie you can
break: shift a birth, or shift a death.*

**§50-B — ⚠ THE CROSS-JUMP REFUND HAS A FLOOR (this BOUNDS §48-A1 and §48-A4).**
§48-A1/A4 say "duplicate the code into both arms; cross_jump re-merges the identical tails after regalloc, so
it costs zero bytes." **That is only true when the tails are ≥ 2 instructions, or when one path FALLS THROUGH
into the merged block.** `jump.c:1993` calls `find_cross_jump(..., minimum=2)` and **does not count the jumps
themselves** — so **two `j`s with a 1-instruction common tail will NOT merge.** Only the `minimum=1` path (a
jump compared against the code *before its own target label*) merges a single instruction.
> **Before using A1/A4, check the tail length.** A 1-insn tail reached by two jumps costs you a real
> instruction — the refund does not arrive. (This is what turned a correct-registers attempt into 290 ins.)

**§50-C — `s16` PARAM + `x | 1` MANUFACTURES A POISON TEMP; `s32` DOES NOT.**
With `s16 arg1`, `v = arg1 | 1;` expands to `ior→T; sll; sra` (REG_EQUAL `sign_extend`) — the `ior` can *never*
write `v`, so a temp is born, and its hard reg leaks into the allocator as a plain preference (see §50-D).
With `s32 arg1` it is ONE insn writing `v`: combine's split reuses `i2dest` (`combine.c:1818-1836`, gated on
`!reg_referenced_p(i2dest, newpat)`) and **no temp exists at all**. Byte-neutral when the target's prologue does
no truncation (`addu $s3,$a1,$zero`). *Widening a parameter can delete an allocno.*

**§50-D — COPY PREFERENCES BEAT PLAIN PREFERENCES, AND THEY NEED A BLOCK BOUNDARY.**
`set_preference` (`global.c:1535`) runs a pseudo through `reg_renumber[]`, so a **block-local** temp leaks *its
hard reg* as a plain preference — and `find_reg` scans plain prefs in **ascending regno**, so `$v0`(2) beats
`$a1`(5) deterministically. To override it you need a **copy** preference (`find_reg` checks those FIRST,
global.c:1000-1030), which requires the arg setup to be a bare `(set (reg $aN) (reg P))` — and that means the
copy must live in a **different basic block** from P's last def, because **combine's LOG_LINKS never cross
blocks**. Route a second call through the *same* call site (a `goto` into a label at the shared `jal`) to give
that block ≥2 predecessors; reload then deletes the now-no-op copy — **zero bytes**.

**§50-E — maspsx/gas MERGES `lui $at` FOR TWO STORES TO THE SAME 64 KB PAGE.**
Reordering global stores to lengthen a live range **loses an instruction**: when two stores to the same 64K page
become adjacent, the assembler merges their `lui $at`. *This explains a layout we had never understood* — the
original interleaves `D_801152AA / D_80126720 / D_801152A8 / D_80126724 / D_801152AC / D_80126722` precisely to
keep same-page stores apart. **Never "tidy up" the store order of a matched function.**

**§50-F — the documented wall (honest defer).** The residual 6 are a `local-alloc.c:1568` (`qty_compare_1` /
`block_alloc`) priority race needing the *opposite* winner from §50-A's: `Q_x2` = 5 refs/range 18 → 0.5556 beats
`Q_unkE` = 2 refs/range 4 → 0.5. Flipping it needs either x2's range ≥ 11 (pri ≤ 0.4545) or unkE's range = 1 —
and **both are blocked by sched.c**, which always fills the load-use stall between `lh` and its consumer, and
places byte-free (reload-deleted) copies *only* in such stalls. The one productive angle left: a lever that
injects a **reload-deleted no-op reg copy** inside `[lhu 4($a2) … sh %lo(D_801152AC)]`. That is the whole delta.

---

## §51 — TOOLING INTEGRITY: the silent skip, and how to hunt it

> Phase 26-A (the inserted tooling-integrity audit). 68 findings across ~36 tools. This section is the
> METHOD and the LAWS; the findings themselves are in `docs/tooling-audit.md`, the strategic why in
> `docs/decision-log.md`. **Read this before writing any tool that scans the corpus.**

### §51a — The bug class

> **A scanner extracts N items from a corpus. The true count is M > N. Nobody ever compared N to M.**

That is the whole class. It is not a typo, it is a *structural* blind spot, and it produced every one of
the seven bugs found in Phase-26 session 8 and the twenty-eight found in the audit. Its signature:

* the tool reports success;
* the number it reports is *smaller than reality* and self-consistent;
* nothing downstream can tell, because **a target that is never nominated produces silence, not an error.**

Measured consequences in this project: **91.6% of all remaining work was invisible to target selection**
(a 3-file allowlist against a 14-file tree); the byte-gate could reach **4.9%** of the canonical overlay;
**62% of the endgame plan's byte-weight was already-matched phantom targets**; and one 10% hole in a
callee-signature oracle made **nine byte-exact functions look like an intrinsic compiler wall.**

### §51b — Why the byte-gate cannot save you

**The whole-binary byte-gate is a perfect CORRECTNESS oracle and a NULL COVERAGE oracle.** It has never
once accepted a wrong match. It is also blind *by construction* to work never attempted: it has been
green since Phase 5, when 0% was decompiled, because `INCLUDE_ASM` pastes the ORIGINAL assembly.

> **A green byte-gate is compatible with ANY decomp percentage.**

So the instrument the project trusts absolutely cannot see this class at all. Do not reach for it here.

### §51c — THE METHOD (do not audit by reading the regex)

Reading regexes is the failure mode that *wrote* these bugs. For every scanner:

1. Build a deliberately **OVER-APPROXIMATING** candidate detector for what it is *supposed* to find.
2. Run **both** the detector and the real scanner over the **real corpus** (production data, not a toy).
3. `gap = candidates − parsed`.
4. **Classify EVERY item in the gap** — real silent skip, or justified exclusion. "I sampled a few" is
   not acceptable; if the gap is large, classify by shape and count each shape.
5. **Measure the blast radius against the corpus.** Not "this could affect X" — go count how many
   functions/members/banks are *actually* affected today. Distinguish LIVE from LATENT (armed but not
   firing). Both are real; conflating them is not.
6. Pair each finding with an **adversarial skeptic** told to REFUTE it. In this audit the skeptics killed
   4 of 32 findings outright and corrected magnitudes in **both** directions.

### §51d — THE LAWS

**LAW 1 — Derive, don't re-derive (R33).** Where a proven invariant answers the question, derive the
answer from it rather than re-parsing the source.

* The invariant here: *the fleet builds byte-identical, and `INCLUDE_ASM` pastes the ORIGINAL assembly,
  therefore a function NOT wrapped in `INCLUDE_ASM` is byte-exact.*
* `progress.py` is the proof, in one file: `weighted_metrics()` **derived** from the invariant and was
  correct; `classify()` **re-parsed C** and inherited a bug. Same question, two tools, and *the one that
  refused to re-derive was the one that was right.*
* **The best outcome of an audit is a DELETED SCANNER, not a fixed regex.** 28 findings collapsed to one
  defect — *a hand-maintained model of the corpus layout sitting on top of a filesystem that already
  answers the question* — and the fix was **one derived oracle (`tools/corpus.py`) and ~10 deleted
  scanners.** A dict literal is strictly worse than the filesystem AND it **fails OPEN** (silently yields
  a plausible wrong answer) instead of closed.
* Corollary: **a derived fact cannot rot; a hand-maintained copy of it is a liability that grows with
  every structural change.** `.run/fuel_manifest.json` recorded 130 live stubs on 2026-07-08; the same
  code returned **30** six days later, because a TU split moved ~100 stubs out from under a dict literal.

**LAW 2 — Assert your COVERAGE, not merely your correctness (R32).** A tool that scans the corpus must
compare what it found against an over-approximating candidate set, and fail on the gap.

> ⚠️ **The sharpest lesson of the audit, and a correction to the first draft of R32:**
> `build_engine_types` **was never silent.** It printed `[overlap] … handle manually` *every single
> time*, for four phases, while hard-exiting on **81% of its own corpus** — the type-heavy tail's only
> sanctioned unblocker, unable to run on the corpus that tail lives in. It went unfixed because the
> message reads like a rare edge case rather than a four-fifths coverage failure, **so nobody ever
> counted it.**
> **A loud failure that nobody counts is exactly as invisible as a silent one.** "Fail loud" is not the
> rule. **"Assert your coverage" is the rule.**

**LAW 3 — When an oracle is structurally blind to a class of error, add a SECOND ORACLE THAT CAN
DISAGREE WITH IT (R34).** Not a better assertion inside the first one.

* `config/symbols.us.txt` declared a main-EXE RAM symbol at an address that is *live code* in every
  overlay. splat cut **97 real functions in half** and **invented 96 phantoms** — 193 slices unmatchable
  *by construction* (one phantom's `.s` literally begins `lw $ra,0x10($sp)` / `addiu $sp,$sp,0x18` /
  `jr $ra`: splat cut a function immediately before its **epilogue** and called the epilogue a function).
* **The byte-gate stayed green throughout and always would have**, because the `.s` halves are pasted
  back verbatim in original order. One phantom even got **banked** as a real match.
* What exposed it: `sig_image` computes function boundaries from the ORIGINAL bytes *without splat*, and
  **disagreed**. `make audit-corpus` is now that second oracle, standing.
* We had both oracles all along and never made them argue. **Redundancy is only worth what you spend
  comparing it.**
* ⚠️ **Scope a cross-oracle check to the domain where the second oracle is genuinely independent.** Run
  naively over all 136 binaries the same check reports **914** slices; the truth is **193**. main/resident
  are signed by the *Ghidra* dumper, whose boundaries are shorter by design — so the comparison measures
  *Ghidra's* limits, not splat's errors. **A check applied outside its valid domain does not become more
  thorough; it becomes noise.**

**LAW 4 — A rule that needs a human to remember it is not a gate. Make it structural.**

* `.o ← .s` is **not** a dependency `make` can see: assembly arrives via `INCLUDE_ASM`, expanded to a
  `.include` consumed by maspsx/as *after* cpp, while `-MMD` tracks headers only. Re-extract, build
  incrementally, and make links a **stale object**.
* This is not merely slow. `INCLUDE_ASM` pastes the ORIGINAL bytes, so a stale object still yields the
  original image: **SHA1 goes GREEN while the split you just changed is never exercised.** A broken
  `config/` change can be "verified" by an incremental build.
* R22/H3 already legislate this ("clean rebuild"; "`make clean` after any `config/` change"). They are
  right, and they were broken anyway — by me, mid-audit. So `extract` now **deletes the objects that
  include what it just rewrote**. Structural, not advisory.

### §51e — The false-wall pipeline (why this is not just hygiene)

A silent skip does not stay quiet. It **compounds into a false wall**:

1. `wave_targets` hands a drafter an asm path that does not exist (78 of 87 targets).
2. The drafter drafts against nothing and fails.
3. The failure is booked into the backlog as a **matching** failure.
4. `reserved_walls()` reads the backlog and **permanently blacklists a function that was never attempted.**

Same shape with a lying closeness oracle: `masked_diff` left `R_MIPS_PC16` unmasked, so **155 functions
scored a phantom non-zero** against an unresolved placeholder that can never compare equal. An agent
grinds forever at a wall that is not there, and the result is filed as an intrinsic compiler residual.

> **Before you write up a wall as intrinsic, prove your instruments could have seen the alternative.**
> How many of the walls "byte-proven" across 26 phases were lookup misses wearing a wall's clothes?

### §51f — Checklist for any new corpus-scanning tool

* [ ] Does the **filesystem** already answer this? Then glob it — never keep a second copy (LAW 1).
* [ ] Does a **proven invariant** already answer this? Then derive it — never re-parse (LAW 1).
* [ ] Over-approximating candidate set + `assert found == candidates`, failing with the unparsed items (LAW 2).
* [ ] Does it print a count nobody checks? Then it is not asserted — it is decoration (LAW 2).
* [ ] Symbol regexes: **any C identifier**, not `func_[0-9A-Fa-f]{8}` — curated names exist, and curated
      naming *increases* as RE quality improves, so a `func_`-only oracle **rots by design**.
* [ ] File lists: **glob**, never a suffix allowlist — the next split kind re-opens the hole.
* [ ] Definition detectors: handle **K&R** (`f(a)` / `int a;` / `{`), **multi-line signatures**, and
      **single-line bodies**. K&R is this project's house style for exactly the biggest, highest-reach
      functions. And find the signature's closing paren with a real **paren-walk** — `line.count('(')` and
      `split(')')[-1]` both land on the wrong paren for a one-line body containing a call.

### §51g — When the thing you are scanning has a GRAMMAR, parse the grammar (`tools/cdecl.py`)

> The `cdecl` build (Phase 26-A). Fifteen tools carried their own regex model of "what is a C
> declaration". They disagreed — two tools in ONE pipeline disagreed about whether
> `extern s32 D_a, D_b;` is a declaration at all — and all fifteen shared one character class:
> ``extern\s+([A-Za-z_][\w\s\*]*?\bD_[0-9A-Fa-f]+\s*(?:\[\s*\])?)\s*;`` which cannot hold `(`, `,`,
> or a non-empty `[N]`. So three whole shapes were invisible to every one of them: **fn-ptr / jump-table
> arrays** (`extern void (*D_8018E858[])(void);`), **sized arrays** (`extern s32 D_80127530[4];` — one
> unparsed `[4]` blocked `func_801387B8` in 134 TUs), and **multi-declarators** (where the *whole line*
> is dropped, not just declarator 2..N).

**THE LESSON. Do not enumerate shapes — parse the grammar.** The audit's own prescription was a
shape-aware *alternation* per tool. That is N more chances to diverge, and it only ever covers the shapes
someone remembered. C's declarator grammar is small, closed, and **total**: it describes fn-ptr arrays,
2-D arrays, multi-declarators, fn-ptr parameters and K&R identifier-lists *without being told they
exist*. A ~250-line recursive-descent parser is **less** code than the fifteen regexes it deletes, and it
is total **by construction** rather than by anyone's memory.

Measured, whole corpus: **2,952,246 depth-0 statements → 2,731,521 declarators, 0 parser defects**;
**50,405 distinct declarations round-tripped through the real cross-gcc, 0 rejected**.

**LAW 4 — The candidate set can be DERIVED too (R33 applied to R32).** Every other tool here
hand-maintains an over-approximating candidate regex in order to measure its own coverage. It does not
need one: **at file scope, C admits nothing but declarations.** So the candidate set is *every depth-0
statement*, taken from the grammar itself — the strongest assertion available, and one that **cannot
rot**, because there is no second model to drift.

**LAW 5 — Let the compiler adjudicate your own coverage gap.** When 40 statements would not parse, the
temptation is to decide for yourself which "don't count" — which is grading your own homework, the exact
habit that produced the fifteen bugs. Instead, hand each one to gcc: **a statement gcc also rejects is
not C**, so rejecting it is *correct* and the INPUT is corrupt; a statement gcc **accepts** and your
parser does not is *your* defect. The exclusion set becomes a verdict from the C front end rather than an
opinion. (Outcome here: 33 residual, **all 33 adjudicated NOT-C by gcc**, all in dead `.run/drafts*`
scratch, **none in `src/`**. And an honest R14 near-miss: they were written by a *recovery tool* that
prepended `extern` to an `if` statement — but the current oracle emits **0 garbage over 300 signatures**,
so the bug was already fixed in Phase 19. Mechanism confirmed, consequence nil: verify the blast radius,
not just the defect.)

**LAW 6 — Column 0 is not file scope.** m2c emits goto labels (`done:`, `block_13:`) at **column 0 inside
function bodies**. Every tool that equates "starts at column 0" with "is at file scope"
(`reconcile_tu.tu_visible`, `scope_data_externs`, `jr_isolate_all`) rests on a heuristic the corpus
violates. Track brace depth; it is ten lines.

**LAW 7 — A raw text scan cannot see a TU's declarations, and `cpp` can.** `src/shared/engine_core.h` is
**23,546 backslash-continued lines inside 1,801 `#define` macro bodies**. A declaration in a macro *body*
declares nothing — it becomes a declaration only where the macro is **invoked**, above the invocation
point (the §8c law). So a raw scan is wrong in *both* directions: skip the `#define`s and you miss all
1,801; read them and you invent ambient decls the TU never had. **`cpp` answers it exactly, in 54 ms on
the largest TU** (~20 s for the whole 678-TU fleet, cacheable) — which is why
`canon_sig_reconcile._file_scope_statements` was the one scanner the audit measured CLEAN, and why any
tool carrying its own model of macro expansion (`reconcile_tu._macro_externs()`, `.rstrip('\\')` and all)
is re-deriving what the build already guarantees. **Corollary:** `reconcile_decls.DATA_DECL_LINE_RE` is
line-anchored, and every decl in `engine_core.h` ends in a `\` — so its "authoritative tier" over the
shared header finds **zero** declarations. It has always been empty.

**LAW 8 — A block-scope `extern` is not a file-scope canonical.** `gen_harvest_targets` and `sig_unify`
both count `extern`s declared *inside a function body* (6 of them in `engine_core.h`) as authoritative
file-scope declarations. A block-scope decl is private to its function and expires at its `}`; promoting
one to ambient truth is precisely the confusion behind the §8d `conflicting types for D_801812A4` wall.
A depth-aware parser excludes them for free.

**And the dividend: a real parser lets you assert things that were previously unaskable.** With `cdecl`
in hand, *"every canonical signature the callee oracle emits must PARSE as a C declaration"* becomes a
one-line check. Before it, nothing in the repo could tell a signature from garbage — which is how
`extern if ((func_80029178(0x119) & 0xFF) != 0);` got written into a draft and then read, downstream, as
a compiler wall.

**Gate:** `make audit-cdecl` (coverage + gcc). Standing, because a loud failure nobody counts is exactly
as invisible as a silent one (LAW 2).

**LAW 9 — THE ADJUDICATOR MUST BE THE COMPILER THAT COMPILES YOUR CODE.** Not the C standard, and not
whatever `gcc` is on the PATH. Building `cdecl.compatible()` (*"will this declaration coexist with that
one?"* — the question every recovery pass actually asks) against **modern** `mipsel-linux-gnu-gcc` and
against the **real gcc-2.7.2 `cc1`** gives three different answers, and only one of them is the truth:

| declarations in one TU | C standard | modern gcc (C11) | **gcc-2.7.2 `cc1`** |
|---|---|---|---|
| `typedef int X;` twice | error | **accepts** | **ERROR** — `redefinition of 'X'` |
| `extern u16 X;` + `extern volatile u16 X;` | error | error | **ACCEPTS** |
| `void X(s16);` then `void X();` | error | error | **ACCEPTS** |
| `void X();` then `void X(s16);` | error | error | **ERROR** |

Validate against modern gcc and you encode rules cc1 rejects and miss rules cc1 accepts — a recovery pass
that "approves" declarations the real front end refuses is exactly the failure this whole audit is about.
`cdecl --compat` therefore adjudicates with `tools/bin/gcc-2.7.2-psx/cc1`, and now agrees with it on
**1,485/1,485 live corpus pairs**. Two rules in that table were *refuted* by the oracle after I had
already written them from the standard.

> 🏆 **AND THE LAST ROW IS A WALL COMING DOWN.** The no-prototype rule is **ORDER-DEPENDENT**: only
> `()`-then-narrow-prototype fails; **prototype-then-`()` compiles fine.** Phase 15 wrote this class up as
> *"the 159 arity/narrow-param conflicts — no clean deterministic fix"* and closed it. **The stated cause
> does not hold.** Whether the resulting codegen matches is a separate question the byte-gate answers —
> but the door was never locked. It took four three-line probes and 90 seconds to find out. **Probe the
> compiler for FACTS; read its source only for LEVERS; byte-validate both** (we read `gcc-papermario` for
> five phases believing it was 2.7.2 — it was 2.8.1).

**LAW 10 — DERIVE *WHICH* TU, TOO — not just what is in it.** `cast_call_sites` / `sig_unify` /
`reconcile_decls` take `--src-file`, an **optional, hand-passed** flag naming the TU to canonicalize
against; unset, it defaults to `src/<ov>/<ov>.c`. No caller knows about the Phase-26 `_jr_<ADDR>` carves.
Measured on ov_SC01_077: **263 open stubs across 12 TUs — only 13 in the main `.c`. 95.1% of drafts were
being reconciled against a translation unit that would never compile them**, while `harvest_verify`
(fixed in A3) correctly spliced them into the right one. `corpus.stubs()` already knows the answer — the
`INCLUDE_ASM` line is self-describing. **Ask, don't assume.** Fixing it took the callee-conflict repair
from **8 → 58 of 196** drafts (7× reach).

> **AND THE HONEST OTHER HALF (P9/R14):** those 58 produced **ZERO new banks.** The historical draft tail
> fails on *codegen*, not plumbing — `func_801387B8`, which the audit blamed on a single unparsed `[4]`,
> is really 67/100 instructions off with a `$s0`/`$s1` swap. What the fix *did* buy is real but narrower:
> **52 drafts moved from "won't compile" to "compiles, N instructions off."** That is not a bank — it is
> the difference between an **invisible failure that reads as a compiler wall** and a **scored near-miss
> the permuter and the §47/§48 dials can act on.** Which is the audit's thesis exactly. Do not sell it as
> more than it is; three times in one session a confirmed mechanism produced a null consequence.

**LAW 11 — A FIX IS NOT LANDED UNTIL ITS CALLER STOPS OVERRIDING IT.** The single worst defect in the
audit was not in a scanner. It was one default argument in the caller of a scanner we had *already fixed*:

```python
# tools/gate_stage.py:315
summary = run_gate(a.drafts, binary=b, src=a.src or f"src/{b}/{b}.c", ...)   # <- ALWAYS the main .c
```

`src` **restricts the byte-gate to ONE translation unit.** A3 had just taught `harvest_verify` to derive
each draft's home TU *when `--src` is omitted*, lifting the byte-gate's reach from **4.9% to 100%** — and
**`gate_stage` never omits it.** So the primary banking path (every wave, the grinder, the orchestrator,
`bulk_harvest`) stayed structurally incapable of banking **250 of 263 stubs**, *after the fix*, *because of
its own caller's default*.

> **AND HERE IS WHY IT SURVIVED 26 PHASES.** `harvest_verify` cannot splice a draft whose stub is not in
> the TU it was pointed at, so the draft simply never verifies — and is then logged as `near`/`failed`,
> i.e. **as a matching problem**. The wave reports a low close-rate and the function goes to the backlog
> as a residual.
> **A tool that CANNOT bank a function is indistinguishable, in every log this project keeps, from a
> function that CANNOT BE banked.**
> Proof, same draft, same gate, same second: `gate_stage` rejected `func_80129C40`; `harvest_verify` run
> directly (no `--src`) **verified it byte-identical and banked it.**

**And a counting bug that hid the hiding:** when `match_one` says MATCH but the whole-binary gate rejects,
`gate_stage` logs `status="near"` and **never increments the counter**. A run of 63 such drafts printed
`banked 0, near 0, failed 0` — *three zeros that do not sum to 63* — for phases. **Nobody added them up.**
(LAW 2 again, and note the shape: the number was not wrong, it was ABSENT.)

**Checklist item, promoted to the top:** after fixing a scanner, `grep` every call site and ask *does any
caller pass a default that re-disables this?* An audit that stops at the callee is half an audit.

## §52 — The WALKER-FAMILY skeleton: 6 regalloc-order levers + a deeply-characterized intrinsic wall (`func_80178004`, 165 ins ×134; Phase 26, Fable5, 2026-07-15)

`func_80178004` is the exemplar of the **regalloc-order** residual class (12 reach-134 siblings share it: the
9 close=0 + 3 close-21+ cores). A ~93-min / 477k-token Fable5 pass drove a PIN-FREE draft to
**structure-exact (163 vs 165 ins); residual = pure register identity** — byte-verified (`match_one` 126/165
masked; the 126 is dominated by one `$s0`↔`$s2` swap rippling ~90 lines). It did **not** byte-match: the wall
reduces to **three compiler-internal integers** and is (probably) intrinsic to vanilla gcc-2.7.2.
**Correction (R14):** the historic "pinned MATCH" was a myth — the pinned seed was NEVER a match (best
historic permuter score 5, pinned); this is the deepest state the function has reached. Artifacts + gdb
oracles under `.run/fable_80178004/` (repro `runorc.sh`); Fable5-derived, headline byte-verified.

### The 6 levers (the "walker-family skeleton" — apply to the 12 siblings; levers 1-5 retire ~half the residual)
1. **Mutated-parameter pointer.** Declare the walking pointer AS the mutated parameter (`u32 *p`=arg0, then
   `p += …`). Any `p = (u32*)a0` COPY leaves the initial value live in the param pseudo → cse1 rebases every
   store block onto constant offsets and DELETES the pointer-walk. The single biggest lever; transfers to
   every walker-style function.
2. **No derived-base variable.** Never declare the second pointer — write `p[1..3]` directly and let loop.c
   mint a combined DEST_ADDR giv of the biv (anchor = last-recorded giv → the -8/-4/0 offsets; preheader init
   reads the biv reg). A source-level `q` biv makes loop.c reduce the (q-4,q-8) pair into an EXTRA pointer
   (loop.c:3824 worthwhile test).
3. **In-loop constant remat.** A constant the target recomputes in-loop must be a **user variable assigned in
   BOTH if/else arms** (`n_times_set==2` fails scan_loop's movable gate, loop.c:698-712 → stays in-loop). A
   bare literal is hoisted.
4. **Split the OR across two statements.** `t = …|0x4000; p[3] = t|0x6d160000;` beats tree-level constant
   reassociation → in-loop `ori` + a hoisted lui-only temp.
5. **Break biv-recognition.** Interpose one statement between `n = i+1` and `i = n` (basic_induction_var
   follows a copy only to the immediately-previous insn, loop.c:4862) → the target's literal counter survives
   instead of a `<<16` giv.
6. **Diagnose allocation walls with gdb-on-cc1 FIRST.** `peek2.gdb` (allocno_order/find_reg) + a 3-integer
   oracle (`reg_n_deaths`/`reg_n_refs`) tells you in minutes whether a register identity is even reachable —
   before grinding C.

### Why the wall is (probably) intrinsic
The walker is a block-local 1-death qty → **local-alloc runs first and hands it the first free callee-saved
`$s0`** (local-alloc.c:472/2103; nothing can pre-occupy s0/s1 for a call-crossing qty). Force it global
(deaths≥2) and its priority `floor_log2(44)*44/103 ≈ 21000` dominates → allocated first → pass-1 first-fit
`$s0` again (global.c:924, callee prefs stripped for call-crossers). The target needs `pri < 2400` ⇒ effective
refs ≤ ~10-12, but **REG_N_REFS counts RTL mentions, fixed at 44 by the bytes**, and every legal construct
only pushes it UP (each ruled out with file:line). **One untested lever:** instrument `qty_n_refs` (local-alloc
SUMS at tying, local-alloc.c:1869) vs flow's per-reg `REG_N_REFS` with `peek2.gdb` on tied-copy chains — if a
tie shape yields a low-ref *global* view of an s2-window value, the wall falls; else it's the ×1-pinned +
whole-binary-gate route.

**Flywheel note (R16):** even walled, this pass paid off — a cheap-Opus wave applying levers 1-5 should crack
the siblings that are NOT at the intrinsic wall. Fable5 DISCOVERS the skeleton; cheap-Opus APPLIES it.

### §52a — The regalloc sibling wave: new levers + two new wall classes (cheap-Opus applying §52, 2026-07-15)

Ran §52 as a 6-agent Opus wave over the regalloc-order reach-134 cluster: **2/6 banked ×134** (`func_80171FFC`,
`func_801775E0` → 268 instances, R22 136/136), the other 4 = precisely-characterized walls. Banks and walls
each yielded a byte-verified, reusable lever:

**New banking levers (each verified by a whole-binary bank):**
- **Pass the callee its real arguments** — `f((s32)a0,(s32)a1)`, NOT the void-cast no-arg trick
  `((T(*)(void))f)()`. When params are saved to callee-saved regs before the first call, the void-cast form
  STRIPS the param pseudos' arg refs → shuffles the `$s0/$s1/$s2` order (RC-10 density). Passing the args
  naturally BOTH suppresses arg-setup moves (params already in place) AND preserves the density order. (`func_80171FFC`.)
- **Recompute a store-base in BOTH if/else arms** (the §52-lever-3 analogue for a base pointer): keeps the
  recomputed base live across the branch-merge so subsequent `p[k]` address off it, not gcc address-CSE onto a
  still-live keeper base. (`func_801775E0`.)
- **Copy-chain direction:** use the incoming param DIRECTLY as the persistent keeper (`keep = param+off`) with a
  working copy `w = param`; gcc saves `param→$sK`, chains `$sJ=$sK`. An explicit keeper var reverses it. (`func_801775E0`.)
- **`pp`-declaration position drives the prologue schedule** (RC-1/K1): declare a param-copy pseudo AFTER the one
  you want saved first — sched1 emits in pseudo-creation order. (`func_801775E0`.)
- **A `const`/`RTX_UNCHANGING_P` pre-call load frees a sched2 prologue save-order tie** (RC-3):
  `f(*(const s32*)(a0+off))` — sched.c:true_dependence drops the load↔store deps so `sw $s0`/`sw $ra` stop readying
  simultaneously → the descending-regno save tie staggers right. BOUNDARY: it can OVER-free (the load then hoists
  above the saves), so it fixes save-order but not always the whole function. (`func_80131A34`.)

**Two NEW intrinsic-wall classes (byte-characterized, P9 — distinct from §52's flagship `$s0` local-alloc wall):**
- **Caller-saved priority-first-fit wall.** A long-lived block-local value (`$v0/$v1/$a0` scratch) stored many
  times has LOW `qty_compare` priority (`floor_log2(refs)·refs·size/(death−birth)`) → loses the low-reg first-fit
  to its SHORT-lived competitor. §31-B in-out-asm and §47 live-length split TIES only, never a priority GAP, and
  the competitor can't be lengthened without deleting an instruction the target keeps. Needs pins → ×1-only.
  (`func_80169228`, bounded to 3 register identities.)
- **Non-coalescing delay-slot copy wall.** A value computed in `$vX`, tested, then copied to `$vY` to survive a
  clobber in the branch delay slot needs two non-coalescing equal-valued pseudos. Every pure-C `y=x` is destroyed
  by cse.c `canon_reg`/`make_regs_eqv` head-promotion or global-alloc coalescing; the only preserving forms are
  `#APP` asm (blocks reorg's delay-slot fill) or a `$0`-add (SIGABRTs cc1 in sibling TUs, §42e). Intrinsic
  pin-free/sweep-safe wall. (`func_80177AD4`, 1 instruction.)

**Wave economics:** ~⅓ of a fully-walled cluster cracks pin-free by applying the idiom; the rest wall on a small
set of distinct, now-named mechanisms. Cracks bank ×134; walls become permuter seeds or documented dead-ends.

### §52b — Sibling wave 2: more de-pin levers, a third wall class, and the match_one→whole-binary gap at scale (2026-07-15)

A second 6-agent Opus wave (armed with §52a) over the close=0 regalloc cluster: **3/6 banked ×134**
(`func_801379FC`, `func_801497A8`, `func_801495C4`), 2 whole-binary-near, 1 new wall. Additional VERIFIED levers
(each proven by a whole-binary ×1 bank):

- **Per-loop pseudos for a register role-swap** — when the target uses pointer=$s0/index=$s2 in one loop and the
  swapped roles in another, a single shared C var can't (one hard reg each). Declare SEPARATE per-loop locals
  (`s32 p; s32 idx;` inside each block); the swap falls out of K2 density (the ref-heavier value wins the low
  callee-saved per block). (`func_801379FC`.)
- **The RC-7 "second-set" dial** — `u8 *s = SYM; __asm__("" : "=r"(s) : "0"(s));` makes `reg_n_sets(s)==2`,
  failing `update_equiv_regs`' single-set gate → NO `REG_EQUIV` → the value is NOT rematerialized at its use → it
  must hold a callee-saved reg across calls (matching a target that keeps a base in `$s1`). Zero bytes, sweep-safe
  (generic `"=r"`/`"0"`, no `$N` — distinct from the §42e `$0`-add). (`func_801497A8`.)
- **Value-barriers dissolve the CSE-stack-address-common wall** — when correct stack-slot order (RC-1 decl order)
  forces a `&buf`(sp+off) to be CSE-commoned across two calls into a call-crossing pseudo that steals a
  callee-saved reg, wrap each `&buf` use in `__asm__("" : "=r"(m) : "0"(&buf))` so cse can't fold them → each
  rematerialized fresh at its call. STEERABLE (banked), not intrinsic. (`func_801495C4`; its `func_8014964C`
  template used a register pin + 5 barriers — the **pin was superfluous**.)

**A third intrinsic wall class (byte-characterized, P9):** the **symbol-address-base "wins-low-needs-high" wall**
(dual of §52a's caller-saved-priority wall). A 2-instruction symbol-address base feeding its own N loads is the
densest block-local pseudo → first-fits the LOW reg (`$v0`), but the target needs it HIGH (`$a1`); making it
low-priority is structurally impossible (a base can't out-rank the loads it feeds), and the movstri form that
would place it high triggers the §52-flagship `(plus $fp const)` local-alloc theft (`update_equiv_regs` can't
rematerialize a non-CONSTANT_P source). Only a register pin resolves both → ×1-only. (`func_8012B4B8`, close=15.)

**Process finding — the match_one→whole-binary gap at wave scale:** ~half of the agents' match_one close=0 drafts
do NOT bank whole-binary (isolated reloc-masked compile overstates; A10). The whole-binary gate is the sole
arbiter — a match_one MATCH is a CANDIDATE, not a bank; budget the gate cycles.

## §53 — SWEEP A FAMILY WITH THE TOOL ITS EXEMPLAR NEEDED: the jr/switch carve, and how omitting it manufactured the "families don't template" doctrine (Phase 28 T1, 2026-07-15)

**The law (one line):** *a family sweep must reproduce every build step the exemplar's own bank required.*
Omit one and the gate rejects every sibling — a result that reads exactly like an intrinsic wall, at any scale.

### The case

`0x8017BEBC` (952 ins, the largest unmatched core in the game; 115 unmatched members across 21 addresses,
`addr_tag: scattered`, PURE 109 / IMM 6) was the roadmap's **B2 — "possibly the largest cheap win left."**
Phase-27 T5 swept it with `family_sweep`, banked **0 of 8**, recorded *"all genuine byte-DIFF"*, and
generalized it to **"h_seq/h_norm structural families do not mechanically template (≈0%)"** — which
rewrote the endgame's arithmetic to "(cores cracked) × (reach), NOT (families) × 120"
(`PhaseEnd_Phase27` Roadmap delta; `docs/calibration.md` called it *"the decisive P28/P29 input"*).

**Re-run through the carve path: 8 of 8 BANKED** (4 same-address + 4 cross-address via `to_addr`),
`make clean` + extract-all + `check-all` → **140/140 byte-identical**.

### Why 0/8 was structural, and predictable from two words

`0x8017BEBC` is a **jr/switch** core. §47 banked its exemplar as *"lazy isolation → carve (9-piece
interleave) → splice → BYTE-IDENTICAL"* and explicitly noted the fix is *"×N template-safe."*
`family_sweep.hseq_sweep` stages C and gates — **it has no carve step**. So gcc's generated jump table is
never placed at the sibling's address, and the residual is exactly:

```
classify_member(ov_SC01_000 -> ov_SC01_001) = PURE, ndiff=2   # positions 343, 345 — TWO WORDS
  idx 343: 3c01801a vs 3c01801f   lui $at,%hi(jtbl_801EC44C)
  idx 345: 8c224374 vs 8c22c44c   lw  $v0,%lo(jtbl_801EC44C)($at)
config/overlays.mk:112  ov_SC01_000_JTBL_INTERLEAVE := ...,ov_SC01_000_jr_8017BEBC.o,tail12.data.o,...
config/overlays.mk:134  ov_SC01_001_JTBL_INTERLEAVE := ...      <- no jr_8017BEBC entry. The table is unplaced.
```

A **PURE, ndiff=2** family is the closest thing to templatable that exists. It failed on a build-config gap.

### The rule

- **A family with `has_mid_jr: true` MUST be swept with `tools/jtbl_family_bank.py`**, never `family_sweep`.
  It carves per sibling (`jtbl_carve` → `make extract` (+`ld_interleave` sandwich) → remap → whole-binary gate,
  revert-on-fail). `family_sweep` is correct only for non-jr families.
- **`--raw` the standalone crack**, not the banked TU. `extract_unit` on a banked jr body hands the sweep the
  TU's file-scope decl layer (here two `D_800B9A02` externs) = §41c pollution. The preserved crack
  (`.run/phase26-cracks/<fn>.c`) carries the fix *and* its reconcile at **block scope**, so it travels.
- **Trust the file, not its header.** `func_8017BEBC.md` still says *"close=2 of 952"* — the state BEFORE
  §47's slider closed it. The `.c` was updated; the `.md` was not. Templating from a body you believe is a
  near-miss, or reading a stale header as current, produces zeros you will misread as a wall.
- **`symbol_map` does NOT need a `jtbl_` prefix.** Tempting and wrong: a compiler-generated switch table is
  never named in C, so there is no token to substitute (`grep jtbl src/ov_SC01_000/…_jr_8017BEBC.c` → nothing).
  The fix is **placement** (carve + interleave), not substitution. *(This was a real mid-plan error: the
  diagnosis "symbol_map cannot generate jtbl_" is TRUE and the fix derived from it is FALSE.)*

### The meta-lesson (R35, and why this one is expensive)

The 0/8 was cited as the decisive input for two phases of planning. Three compounding failures made it:
1. **Wrong tool for the class** — swept a jr family with a carve-less sweeper.
2. **n=1, least-representative** — `has_mid_jr` is **3 of 163** matched-exemplar families; the rarest class
   was generalized to the whole frontier.
3. **The corroborating evidence was pre-fix** — the three Phase-26 exhaustion probes (tiny-IMM 0/241,
   PURE 0/134, pinned 0/133) all predate `_carry_macros` (P27 T5, `commit:0637`). P27's own decision-log calls
   its re-probe *"a **fourth** phantom exhaustion proof"* — naming the mechanism that would have faked the
   first three, and never re-running them.

**Before a 0% retires a lever, ask: did I run the steps the exemplar's own bank required? is this family
representative of the class I'm generalizing to? was the corroborating evidence taken through the same
broken tool?** A 0% from a broken tool and a 0% from a working one are the same number and opposite facts.

## §55 — Core-crack wave levers + the GATE-ORCHESTRATION law (Phase 29 T3, 13-agent ultracode wave, 2026-07-17)

A 13-agent `worker_wave` over 6 fresh cores (260–371 ins) + 7 B3 near-misses (100–141) returned **7 MATCH /
6 near**; 5 banked whole-binary. The durable yield is the levers + the orchestration law.

### §55a — New byte-proven levers (each from a banked or near draft)
- **§49-variant — suppress sched1's `birthing_insn_p` LAUNCH_PRIORITY boost by `reg_n_sets` 1→2**
  (`func_801325B8`, 113 ins, BANKED, reproduced twice). Route the load through a temp assigned in BOTH
  halves of a branch: the pseudo now has `reg_n_sets==2`, so it is no longer "birthing", the priority boost
  disappears, and two transposed loads un-invert **at zero byte cost**. Companion to §30's birthing-boost.
- **`birthing_insn_p` governs sched1 PLACEMENT, steerable both ways** (`func_80177940`, 101 ins, close=5):
  an *in-place single-variable update* makes a chain **non**-birthing → sched1 stops sinking it (18→10);
  a *fresh pseudo* for `c<<16` makes it birthing (10→5). Also: `__asm__("" : "=r"(v) : "0"(v))` is a
  zero-code CSE fence that blocks the cse2 fold of a duplicated chain.
- **`cc1 -dL` prints loop.c `move_movables` decisions** (moved / not-desirable, per movable) — the
  threshold (−3/movable) is steerable by statement order. A **dead second set** (`col = 0;`) makes
  `n_times_set != 1`, so a constant is not a movable and stays in-loop. (`func_80177940`.)
- **Switch TREE vs jump table — `CASE_VALUES_THRESHOLD` is 5** (`func_801387B8`, 100 ins, BANKED): 4 cases
  `{1,7,10,23}` < 5 ⇒ gcc emits a branch tree (forward-beq-to-body + lone median `slti`), NOT a jtbl — so a
  guard like `if (cmd != 0)` **must stay OUTSIDE** the switch or a 5th case forces a jump table. `u8 cmd`
  buys a signed `slti` on the split AND an unsigned `sltiu` on `cmd >= 0x20` for free; case bodies emit in
  SOURCE order. **Ghidra's if-chain for a switch is a decompiler artifact** (floors at 49-off) — recognize
  the dispatch tree.
- **Block-scope beats `*(T*)&sym` for a conflicting extern** (`func_8014ADE0`, BANKED): when a
  `DEFINE_func_*` macro declares `extern s16 D_X` and you need `s32`, a **block-scope `extern s32 D_X`**
  is a warning (not an error) — but it is **order-dependent: block-scope must precede the file-scope decl**
  (reverse = hard error, cc1 exit 33). `*(s32*)&D_X` FAILS (~100-ins shift — the §18 `&sym`
  materialize + CSE trap).

### §55b — THE GATE-ORCHESTRATION LAW (3 traps, ~3.5h lost; all recovered, 0 data lost)
1. **`gate_stage`'s propagate step is FLEET-WIDE** (`dedup_propagate --auto-from`), NOT scoped to the drafts
   you gated. Running `gate_stage` once per src-file group therefore re-runs the whole-fleet scan N times;
   each exceeds the 3600s timeout and dies **mid-mutation** → partial propagate damage (measured: **90/140
   overlays broken, 887 files, engine_core.h +561**). **LAW: `--no-propagate` on every per-group gate, then
   ONE targeted `dedup_propagate --addr <banked addrs>` at the end.**
2. **COMMIT the cheap verified banks BEFORE the expensive propagate.** The byte-gate is minutes; the
   propagate is ~2h and mutates 300+ files. Gating and propagating in one motion means every propagate
   failure takes the (already-verified) banks down with it. Commit, then propagate as a standalone
   revertable step.
3. **A reverted `src/` needs a RE-EXTRACT** (the R22 corollary, again): `git checkout -- src` restores the
   `INCLUDE_ASM` stubs, but `asm/` still reflects the BANKED state (splat emits no `.s` for a matched fn) ⇒
   `corpus.CorpusError: N stub(s) have NO .s on disk`. Recovery = `git checkout -- src docs .run` **+**
   `make extract BINARY=<ov>`. (R34's second oracle caught this loudly — working as designed.)
4. **`gate_stage`'s default `.run/harvest_verified.txt` ACCUMULATES across runs and its CLI exposes no
   `--verified-out`** ⇒ after a revert it reports a **phantom `banked: N`** for functions still stubbed in
   `src` (stale residue). **Trust the SOURCE (`grep INCLUDE_ASM`), never the report** — R32/R35 class, and
   **still armed**: either expose `--verified-out` on the CLI or unlink the default before each gate.

### §55c — Sizing the propagate: a TARGETED propagate is ~4 min/core, and "it's slow" was a BROKEN-TREE ARTIFACT
`--check-only` prints the real plan first — always use it (it also aborts free when a group is undroppable).

**The real cost, measured on a HEALTHY tree: `--addr <1 core>` = 233s for 138 members** → 3 cores ≈ 12 min.
`[ OK ] 138 overlays byte-identical after propagation`.

**The trap (and a live R14/R35 self-correction worth remembering):** the same 3-core targeted propagate had
*timed out at 3000s* earlier in this task, and I wrote "**needs ~2h+**" into the commit + this cookbook as a
*measurement*. It was nothing of the kind — it was propagating into a tree still carrying the partial damage
of a previous killed `--auto-from` (90/140 overlays broken), so every member-gate was failing/retrying. On a
clean tree the identical command is ~20× faster. **A timing taken on a broken tree is not a measurement of
the tool** — it is a measurement of the breakage. (Same shape as the §53 carve-law and the §54 def-sig
findings: the number was real, the attribution was wrong.) Recover the tree FIRST (revert + re-extract),
THEN measure.

- Only **`--auto-from`** is genuinely fleet-slow (it scans every matched fn) — that is the one to avoid, not
  the targeted `--addr` path.
- **`h_exact` share is all-or-nothing:** one straggler overlay (`ov_SC03_093`) drops the whole group unless
  `--recover` (per-overlay exclude) is passed.
- **Local-type bodies are skipped** ("not self-contained") until `build_engine_types` lifts their types
  (§19/§20 propagation cap) — 2 of this wave's 5 banked cores were blocked this way.

## §54 — `--fix-def-sig`: the member's CANONICAL DECLARATION is a build step too (tiny-IMM mega-pools, +4,801, Phase 29 T6, 2026-07-16)

The §53 law — *sweep a family with the tool its exemplar needed* — has a fourth instance beyond the jr-carve
(§53) and the -O0 flag (Task 1): **the member's shared-header declaration.** The two tiny-IMM mega-pools
(`0x80131eec`, `0x80130d0c`; ~15-ins jump-table dispatchers `D_x[*(u16*)(a0+2)]()`, ~2600 members each) banked
**1/4966 (0.0%)** via plain `family_sweep --hseq` AND **0/2470** via `--reconcile` (canon_sig_reconcile).

**Root cause (byte-proven, after 3 masked-metric mis-reads — see decision-log 2026-07-16):** `family_remap`
copies the EXEMPLAR's def signature onto each member. When a member is **forward-declared in
`src/shared/engine_core.h`** with a caller-derived signature (a shared engine fn calls it:
`extern void func_8015FAAC(s32 *a0);`) that *differs* from the exemplar's (`void *a0`), the member TU throws
`conflicting types for func_X` (cc1 exit 33) and never compiles. The exemplar itself has no such header decl
(that asymmetry is why the family templates in ov_SC01_077 but not its members). This is INVISIBLE to
`diff_regions`/`match_one`/`masked_diff` (they compile the draft STANDALONE, so no header decl to conflict
with → they report `O2:MATCH(0)`), and to `--reconcile` (it reconciles against the sibling TU's local decls,
not the *included* header).

**The fix — byte-neutral, gate-arbitrated.** `family_sweep --fix-def-sig` (`header_sig_map` parses the 1005
`extern … func_X(…)` decls in `engine_core.h`/`engine_types.h`; `reconcile_def_sig` rewrites the member draft's
DEF sig to that canonical). A pointer-type param diff (`s32*` vs `void*`, `(s32)a0` identical) doesn't change
codegen; the whole-binary gate rejects anything that does (G3/P9). Result: pool 1 **94%**, pool 2 **99%** =
**4,801 banked**. Consider making `--fix-def-sig` default-on for the h_seq path. Meta: a masked/standalone MATCH
is a candidate, never a diagnosis — reproduce the real member TU and read the real cc1 error (R35).

## §56 — Banking a hand-drafted GIANT into its exemplar TU: self-contained draft vs live-TU decls, 4 reconciliation tactics (`func_8013FAF8`, 312 ins ×138, Phase 29 T4, 2026-07-17)

A hand-crafted giant draft is **self-contained** (its own typedefs + externs) so `match_one` can compile it
standalone. Splicing it into its live exemplar TU surfaces decl conflicts the standalone compile is blind to
(same blind spot as §54, but a GIANT touches dozens of symbols). `harvest_verify` strips the typedefs the TU
already provides (per-TU strip-set) but **NOT the externs** — those you reconcile by hand. Every fix below is
byte-neutral and re-verified two ways: `match_one` must stay green AND the whole-binary gate must stay
byte-identical (G3/P9). The loop: `harvest_verify --binary <exemplar> --drafts <isolated-dir>` → it prints ONE
`PLUMBING: <cc1 line>` per fail. **That classifier line is often a red herring** — it grabs the FIRST
`conflicting types` in stderr, which may be a pre-existing benign warning (`conflicting types for built-in
function memcpy`, present in the 140/140 baseline). Get the FULL cc1 stderr (splice manually, `make build
BINARY=<ov> 2>&1 | grep error`) and fix the REAL errors bottom-up.

The four conflict classes and their byte-neutral fixes (all proven on func_8013FAF8: s16/s16 def, 3 data + 2 fn
conflicts, ~5 gate iterations):

1. **Def-sig conflict** (draft `void func_X(s16,s16)` vs the fleet-canonical `extern void func_X(s32,s32)`,
   404 decls). **NARROW the extern fleet-wide s32→s16** — NOT `--fix-def-sig`. `--fix-def-sig` rewrites the
   DRAFT to the canon; here the s32 def diverges from the target at insn 22 (the `for(i=arg0;i<arg1)` compare
   promotes differently). **Direction test (R35):** the correct direction is whichever keeps `match_one` green
   — test the canon-typed variant explicitly before assuming `--fix-def-sig`. Byte-neutral iff EVERY fleet
   caller passes cast/small-const args — verify (`grep -rh 'func_X('`): here all were `(s16)`-cast or `0/5/7/8`.

2. **Data-symbol conflict, file-scope decl BEFORE the splice point** (block-scope is §55a-BLOCKED — a
   block-scope extern after the file-scope one is cc1 exit 33). Use the TU's established **§18 cast-at-use-site**
   convention: `*(s16*)&D_80115128` (forces `lh`), `*(u16*)&D_800B9A02` (forces `lhu`),
   `((s32*)&D_80187AC0)[i]` — the cast fixes the load width **independent of the decl's signedness**, so you
   keep the TU's existing decl untouched and there is **no conflict at all**. This is also **propagation-safe**:
   unlike block-scope, it carries no macro-slot-ordering dependency across the 137 member TUs. Caveat (§18):
   `&sym` can CSE-hoist across many uses in a tight loop — verify it didn't (func_8013FAF8: 5 uses of
   `&D_800B9A02`, no hoist; giants with few uses/symbol are safe, re-test if a symbol is hammered in an inner loop).

3. **Data-symbol conflict, file-scope decl AFTER the splice** — block-scope extern is legal here (§55a), but
   **prefer the tactic-2 cast form anyway** for propagation safety (the member TUs won't share the ordering).

4. **Function-extern conflict** (draft `extern s32 func_Y(s32,…)` vs the TU's own DEF `func_Y(s16,…)` /
   `int func_Z(int)`): reconcile the DRAFT's decl to the TU's type + a byte-neutral call-site cast, e.g.
   `ot = (s32*)func_80141100((int)ot)`. Pointer↔int and s16↔s32-of-an-already-sign-extended-value are free.

**Then R22 clean-fleet (mandatory):** the tactic-1 narrowing edits `engine_core.h` (404 decls, 266 files) —
`harvest_verify` gates only the exemplar binary, so the fleet-wide byte-neutrality of the narrowing is unproven
until `make clean && extract-all && check-all` = 140/140. func_8013FAF8: 140/140, +312 ins ×1 (propagate ×137
is the separate §55b step). **The README's "pure def-sig plumbing" undersold it** — a giant is a *multi-symbol*
reconciliation; budget ~5 gate iterations, not one edit.

### §56b — PROPAGATING an h_seq giant: the exemplar's externs MUST be fleet-canonical, not the draft's types

An h_seq family (masked-identical body, per-overlay symbol names/reloc targets) propagates via
`family_sweep --hseq --only <addr> --source <exemplar> --allow-pins` — it copies the exemplar's matched C
into each member and **remaps the per-overlay data symbols** (the undefined-`D_xxxxxxxx`-reference the raw
exemplar throws in a member is exactly what the remap resolves; a manual `harvest_verify` of the raw exemplar
into a member is NOT a valid family test — only `family_sweep` remaps). But it copies the exemplar's **extern
block VERBATIM** (only the data symbols are remapped, not the callee-extern *types*). So if your hand-crafted
exemplar declared a callee with a type that diverges from the **fleet-canonical** (the member consensus /
`engine_core.h`), *every* member TU throws `conflicting types for func_Y` and the whole sweep banks **0/137**.

**The fix (byte-neutral, unblocks the entire family in one edit):** before sweeping, audit every callee extern
in the banked exemplar against the fleet-canonical —
`grep -rh 'extern.*\bfunc_Y\b' src/ov_*/ | sort | uniq -c | sort -rn | head -1` — and rewrite the exemplar's
decl to the high-count consensus form. Return-type and pointer↔int param diffs are byte-neutral (gcc-2.7.2
warns, doesn't error; the call's arg *values* are unchanged, and a discarded/`(cast)`-assigned return emits
identically). func_8013FAF8 had **4** divergent externs (`func_8005A600` void→s32, `func_80024054`
s32→void*, `func_80137D08` s32*→int, `func_8013AB54` s32*→s32); aligning them in the *committed* exemplar
`.c` (family_sweep reads the tree, not your `.run/` draft) took the sweep from **0/137 → 137/137 banked**,
+312 ins ×137 ≈ +42.7k ins, R22 clean-fleet 140/140. Meta: a hand-authored exemplar carries the *drafter's*
type guesses; the fleet already voted on the canonical — make the exemplar agree before it becomes the template.
(Contrast the h_exact path — `dedup_propagate --recover` — which auto-reconciles conflicting *caller* externs;
`family_sweep` does not, so you pre-align the *callee* externs by hand.)

## §57 — The SELF-decl normalize: the sibling's OWN caller declares the templated fn divergently (the third §17a-1 direction; `tools/normalize_self_decls.py`, func_801670E4 ×137, Phase 29, 2026-07-18)

§17a-1 (fold a compile-time fn-ptr cast of a known symbol back to a bare `jal`, byte-neutrally) has **three**
directions, one per "who declares the conflicting signature":

| tool | the conflicting decl is of… | lives in |
|---|---|---|
| `cast_call_sites` (§20) | a **callee** the draft calls | the DRAFT's own forward-decls |
| `reconcile_tu` (§8d/§33) | a **data** symbol `D_xxxx` | the DRAFT's own externs |
| **`normalize_self_decls` (this)** | **the templated fn F ITSELF** | the SIBLING TU's *other* already-banked functions |

**The blocker (byte-proven, func_801670E4 ×137).** `family_sweep --hseq` templates F's DEF into each sibling TU.
But that sibling's OWN already-matched caller of F may carry a **block-scope decl of F** left when *that overlay's*
caller was matched — in a different C form than the exemplar's caller used. ov_SC01_004, `ov_SC01_004_jr_8015AE2C.c`:
the stub of F (→ where the def lands) and `func_80167540`'s local `extern void func_801670E4(struct Entity_80167540 *,
s32, s32, s32);` sit in **one TU**; splice F's def (`s32 func_801670E4(s32,s32,s32,s32)`) and cc1 exit-33s with
`conflicting types for func_801670E4` — twice (once vs the def, once vs the canonical decl the `DEFINE_func_*` macro
injects at file scope; the second is error-recovery cascade from the same one decl). **The EXEMPLAR never hit this**:
ov_SC01_077's copy of that same caller used the fn-ptr CAST form instead of a decl, so the conflict is **per-sibling
and invisible in the exemplar** (like §54's header-decl asymmetry and §56b's exemplar-externs, a third "the two overlays
matched the same code in different C forms" trap). All 133 still-stubbed siblings carried the identical block-scope decl.

**The fix (byte-neutral, gate-arbitrated).** For each decl of F in the sibling TU **incompatible** with F's def
(`cdecl.compatible`, the cc1-validated oracle — a no-prototype `void f()` never conflicts in either TU order, §51g,
so skip it): **DROP the decl** (F's def is now the declaration cc1 sees) and **CAST every call of F in that decl's
scope to the decl's ORIGINAL sig** — `func_F(a)` → `((void(*)(struct Entity_80167540 *,s32,s32,s32))func_F)(a)`. This
is the byte-faithful move (preserves the caller's exact ABI, the form the exemplar's caller already used); the
`sig_unify` "rewrite the decl to canonical, keep the bare call" alternative reconverts the args to the canonical
param widths and drifts codegen (§20). Manually proven byte-identical on ov_SC01_004 (**remove the stale output
first** — a failed compile leaves a passing STALE binary that false-passes SHA, §42b) before the tool existed.

**Wired.** `tools/normalize_self_decls.py` (`fix(tu_text, fn, ref_decl)` — scope via `cdecl._mask`ed brace-depth,
block scope → the enclosing top-level fn body, file scope → to EOF; idempotent no-op when no divergent decl exists).
`family_sweep --hseq --normalize-self-decls`: a new per-sibling stage after `reconcile_def_sig` that edits the
**sibling TU FILE** (F's callers live in F's own TU = `harvest_verify`'s baseline, like `edit_remap_sweep`), with a
snapshot + **final-SHA-MISMATCH revert backstop** (a MISMATCH ⇒ a transform bug, since `harvest_verify` always
reverts a wrong DRAFT — so a wrong draft leaves the binary byte-identical, only a non-neutral TU edit can MISMATCH).
Result: **func_801670E4 133/133 banked, 0 failed** (family 4→137/137), 0 backstop fires. **Do NOT add `--fix-def-sig`
for this family:** the raw draft def `s32 func_801670E4(s32 arg0,…)` is already type-compatible with canonical
(param NAMES are irrelevant to a C prototype); `--fix-def-sig` renames the params to `a0..a3` while the body still
says `arg0..arg3` → `arg0 undeclared` (the "rare name mismatch" its own docstring warns of). Diagnose the sweep's
ACTUAL blocker (splice one member, read cc1) before stacking plumbing flags (R35).

**Not every type-lifted family needs this:** `func_8016CBC0` (also 137-member, also blocked) has NO divergent
self-decl (survey the members: `grep 'func_X(' the-member-TUs`) — its blocker is a local-typedef lift (§ type-lift,
like func_8012956C), a different lever. Route by the real cc1 error, not by "it's a stuck 137-family."

### §57a — Two NSD corrections + the SURGICAL-ONLY law + the honest broad-sweep yield (Phase 29, 2026-07-18)

Three findings from applying §57 at scale, all byte-grounded:

**(1) REWRITE the divergent decl to canonical — do NOT drop it (the def-after-caller trap).** The first §57
build DROPPED the divergent decl. That is byte-neutral only when F's def sits ABOVE the caller in the TU (so the
def itself provides the caller's forward visibility — `func_801670E4`, def-before-caller). `func_8013D53C` is
def-AFTER-caller: a FILE-scope `void f(void)` forward decl, F's def spliced BELOW it — drop the decl and the
caller gets `func_8013D53C undeclared`. The fix is exactly what `cast_call_sites` does: **rewrite** the decl to
the def's canonical sig (matches the def → no conflict, AND keeps forward visibility), then cast the calls to the
decl's ORIGINAL sig (byte-exact). Works both ways (a canonical forward decl above/below the def is compatible).

**(2) `(void)` is NOT no-proto — do not skip it.** The first build skipped `params in ('', 'void')`. But `void
f(void)` is a 0-param PROTOTYPE that genuinely conflicts with a >0-param def (`cdecl.compatible(void f(void*),
void f(void)) == False`), while a true no-proto `void f()` is compatible in either order (§51g). Skip ONLY the
literal empty `()` (also the §32 no-proto-mis-cast guard); let `cdecl.compatible` judge `(void)`. This was why the
BUILD SPEC filed D53C's `(void)`/(T) arity class as "not this pass" — it was a tool gap, now closed.

**(3) NSD is SURGICAL-ONLY; `--fix-def-sig` is broad-safe — the blast-radius asymmetry.** `--normalize-self-decls`
edits the **TU file** (F's callers live in F's own TU), so a non-neutral edit poisons the ENTIRE `(overlay,split)`
group — and unlike a bad DRAFT (which `harvest_verify` bisects away per-member), a bad TU edit can't be isolated;
the whole group's build MISMATCHes and the backstop reverts all of it. A broad `--band substantial
--normalize-self-decls` (esp. combined with `--fix-def-sig`, whose canonical-rewrite changes NSD's reference sig)
banked **7** with ~752 groups backstop-reverted. `--fix-def-sig` edits DRAFTS (bisect-safe per member), so it IS
broad-safe. **Law: apply NSD per-family (`--only`, on a surveyed self-decl blocker); apply `--fix-def-sig` broadly.**
The backstop makes broad NSD SAFE (0 false banks) but useless.

**(4) The honest broad-sweep yield (R14/R35): staging ≠ banking.** The 60 substantial matched-ov077 families with
2,163 stubbed members STAGE 2,169 drafts, but a broad `--fix-def-sig` sweep banks only **137** (one def-sig family +
stragglers) — 2,032 fail. The substantial-family frontier is NOT broadly mechanical; each family carries its own
blocker (self-decl / type-lift / def-sig+caller / genuine codegen). **Gate-probe a SAMPLE before scaling a yield
estimate off the STAGED count** — the phase's own invariant, which I violated by projecting ~1,500 from 2,169 staged.
`func_8013D53C` is the archetype: NSD + a `Cmd_8013D53C` type-lift clear its plumbing (it now COMPILES), and the
sweep banks **14/137** — the h_seq members whose bodies happen to match the exemplar — while **123** carry a genuine
per-member codegen DIFF (the hard cse.c-wall crack does not fully template). So it is a PARTLY-mechanical family:
the plumbing levers harvest the easy fraction ×0 tokens, the residual 123 are permuter/Fable fuel. **NB the NSD
edits are byte-neutral even where the member does NOT bank (the caller's canonical decl + cast matches with F still
a stub), so they persist on all 137 TUs — revert the ones that didn't bank (still carry the stub) so you commit
banks, not churn on matched code.** The classifier's `PLUMBING` count is a §56 memcpy red-herring; read full cc1 stderr.

## §58 — match_one MATCH ≠ BANK: the four blind spots + the crack-wave reconcile-before-bank law (Phase 29 crack-wave, 2026-07-18)

A crack-wave drafter iterates a C body against `tools/match_one.py` (standalone compile of ONE function
with the DRAFT's own externs + relocation masking). That is the right per-function oracle, but it is
STRUCTURALLY BLIND to everything that only surfaces when the def is spliced into its real TU + the whole
binary is linked. An 11-core wave produced 9 match_one MATCHes; **all 9 gate-failed the whole-binary bank
with ZERO codegen problems** — every failure was one of four integration classes match_one cannot see:

  (a) **Ghidra symbol names.** Drafters paste `DAT_801d9c20` / `PTR_DAT_80186ad0` (Ghidra) instead of the
      splat `D_801D9C20`. match_one links the draft's own `extern`, so it never notices; the whole-binary
      link fails `undefined reference`. FIX: rename `DAT_<hex>`/`PTR_DAT_<hex>` → `D_<UPPERHEX>` (verify the
      splat label exists: `grep -rn D_<HEX> asm/<ov>/data/`).
  (b) **Def-sig conflict vs the fleet.** The draft's def sig (from m2c/Ghidra) diverges from `engine_core.h`
      or the TU's own caller-decls. **The draft sig is byte-TRUTH (it MATCHed); the header/caller decl is
      often a stale stub-era guess** (`void func_80164E40(void)` where the truth is `s32` — `canon_sig_reconcile`
      forcing the draft to `void` produced a DIFF, i.e. dropped the return computation). Conform the DECLS to
      the draft, byte-neutrally: narrow the `engine_core.h` extern void→s32 (callers that ignore the return
      are unaffected — R22 clean-fleet confirms neutrality), or `tools/normalize_self_decls.py --tu --fn
      --canon "<draft sig>"` when the TU's own caller declares F divergently.
  (c) **Callee-decl conflict.** The draft declares a callee with a sig conflicting with the TU's canonical →
      `tools/cast_call_sites.py` (fn-ptr-cast the calls, drop the divergent extern).
  (d) **Opt-level.** A function in an `-O2` segment can actually be `-O0` (frame pointer, per-case stack
      reloads). match_one masks this if the agent tried `--o0`; the whole-binary `-O2` build then DIFFs. FIX:
      relocate the def into the overlay's `_o0`/`_o0b` object (whose .text covers that addr). A "DIFF" verdict
      is often THIS, not a codegen miss (func_8013C0F8 was mis-filed as a real -O0 DIFF; it was §8 jtbl).

**LAW:** a crack-wave's match_one MATCHes are CANDIDATES; budget a reconcile pass before banking. Best is a
pre-bank auto-reconcile (rename → cast_call_sites → reconcile_tu → normalize_self_decls / narrow-extern), then
the whole-binary gate. And feed it upstream: tell the drafters to use splat `D_` names + the `engine_core.h`
canonical callee sigs, which removes (a) and (c) at the source. `harvest_verify`'s per-draft failure LABEL is
a first-diagnostic red-herring (it reported a shared `built-in memcpy @4017` for 7 unrelated drafts) — always
read the REAL error by splicing ONE draft and reading full cc1/ld stderr (and beware the §42b stale-image
false-pass: on a build FAIL the old image lingers, so confirm rc==0 before trusting a sha). 6/9 banked this way.

## §59 — Three h_seq sweep-residual classes match_one/the-exemplar-bank don't reveal (Phase 29 crack-wave close, 2026-07-18)

After a core banks ×1 in ov_SC01_077 and swaps to `matched-ov077`, `family_sweep --hseq --only` can still bank
0/137 for reasons invisible at the exemplar (they're per-SIBLING, or per-overlay data facts). Three seen in one batch:

- **(1) The exemplar's LOCAL struct type is dropped by the remap** (func_80165240, 0→137/137). The exemplar TU
  defines `struct W4 { u32 w; } __attribute__((packed,aligned(1)))` inline; `remap_hseq` templates the DEF but
  not that local type, so each sibling's `*(struct W4*)dst = *(struct W4*)src` lowers to a DIFFERENT-sized memcpy
  → byte-DIFF (compiles clean — it's a DIFF, not a compile error, so match_one/standalone never sees it). FIX:
  prepend the local struct decl to each member draft (the tiny-inline-type analog of the §57/func_8016CBC0
  engine_types.h lift — but too small/local to lift; carry it in the template). Symptom is "compiles, 0/137 DIFF."
- **(2) h_seq data is per-overlay RELOCATED — there is NO fleet-fixed data address** (func_8016D1D8/D688,
  0→274/274). The exemplar body reads `D_801D9C20` (a tail work-buffer); the WRONG assumption is that 0x801D9C20
  is the same in every overlay. It is NOT — each overlay's buffer sits at a different base (ov_000 → 0x801A4B78).
  `remap_hseq`'s `symbol_map` keys the byte-OFFSET labels (`D_801D9C21`…) not the base symbol the C uses, so the
  base is left unresolved → `undefined reference`. FIX, scripted per sibling: `base = symbol_map["D_<off>"] − off`;
  declare `D_<base> = 0x<base>; // type:u8` in `config/symbols.<ov>.txt` (in-overlay → re-extract emits the linker
  def, byte-neutral); remap the exemplar's base symbol → `D_<base>`. (A few SC07 stragglers also needed carried
  externs like `ApplyMatrixSV` dropped — their TU declares them with a conflicting sig, §20/§58c.)
- **(3) jtbl carve isolation/table-drift walls** (2 cores blocked, genuine tooling). `jtbl_carve` refuses a
  NON-CONTIGUOUS same-subseg table (another matched fn's carve already occupies the subseg); isolating requires
  `jr_isolate`/`split_src_region`, which **cannot partition the Phase-17 canonical-sig-layer TU** (`trim: cannot
  resolve address of item`). And a merged two-table span (§8e-2) trips `jtbl_rodata_pads: more rodata .align than
  pad specs` when the -O0 code object holds more jump tables than the span's derived pad spec ("one contiguous
  .rodata run per object"). Both are documented walls — bank the contiguous/last-table cases, report the rest.

Meta: a `family_sweep --hseq` "0/137 banked" is a per-sibling INTEGRATION signal, not a codegen verdict — read one
sibling's real gate result (COMPILE-fail vs byte-DIFF) before concluding. Extends §58 (match_one blind spots) to the
sweep stage.

## §60 — Classify the residual, don't rank it: the deterministic residual→class classifier and what it measured about the backlog (Phase 29 Task-13A, 2026-07-21)

**The instrument.** `tools/residual_class.py` decides a near-miss's class FROM THE BYTES. It decodes each
mismatching MIPS word into `(operation-skeleton, register-fields, immediate)` and runs a decision tree:
drift first (a single inserted instruction desynchronises the tail and inflates `closeness` by the tail's
length — a 1-instruction structural delta wearing a 200-mismatch costume), then a consistent-injective
**register map** (⇒ `REGALLOC-PERM`, the §31 S11/RC-3 class), same-multiset-different-order (⇒
`SCHEDULE-REORDER`), nop-vs-instruction (`DELAY-SLOT`), then operation-family splits (`WIDTH` lw↔lh =
the §18/§43 idioms, `BRANCH-POLARITY`, `STRENGTH`, `ADDRESSING`), then immediate-only (`IMM-OFFSET`
constant delta = a frame/struct-layout shift, `IMM-VALUE`). Every path ends in a NAMED class; an opcode the
decoder does not cover is `UNKNOWN` and COUNTED (R32). Each class routes to a **bucket** — `permuter` /
`structural` / `integration` / `redraft` — which says WHICH TOOL the failure wants.

`tools/autopsy.py collect` materialises the corpus by recompiling every open backlog draft through the
EXISTING `match_one` path (R33 — never a second copy of the pipeline), deriving the two silent-artefact
inputs rather than guessing them: the **asm subdir** (from the stub's self-describing INCLUDE_ASM line) and
the **-O0 flag** (`corpus.is_o0`, parsed from the Makefile's own -O0 rules with a coverage assertion). 1,752
drafts in ~21 s at -j12.

**Cross-check (R34).** The classifier's `closeness` is computed by a different route than
`masked_diff.structured_diff`'s; `collect` asserts equality on every row and refuses the corpus on any
disagreement. 1,673/1,673 agreed, 0 classifier errors — so the MIPS decoder covered every opcode in the
real corpus.

### What it measured — the whole open backlog, byte-grounded

| bucket | fns | reach-wtd | meaning |
|---|--:|--:|---|
| `redraft` | 699 | 2,162 | the stored draft is **not this function** (a 15-ins body vs a 132-ins target) |
| `structural` | 578 | 7,761 | local mutation cannot introduce it — wants a C idiom, not CPU |
| `integration` | 306 | 2,303 | byte-correct standalone; blocked on plumbing (§58/§59) |
| `permuter` | 75 | 740 | a search-closer can actually reach it |
| `unknown` | 2 | 2 | the LLM tier's residue |

**THE FINDING: of the 972 records the grinder's own filter admits, 75 (7.7%) are permuter-shaped.** 547 are
structural and 348 are junk drafts. The daemon has been spending ~92% of its CPU where the permuter provably
cannot win — which is the byte-grounded explanation of "7 banks all-time, all in Phase 21, 0 since"
(Phase-22 audit). It was never a missing transform; it was **targeting**. `grinder.candidates()` now filters
on the measured bucket (1,303 → 78 candidates) and takes its directed `permuter_weights` profile from the
measured class instead of the logged label — 91% of records carry NO label, so `classify()` returned None and
the search ran on gcc defaults. Degrades to the old undirected behaviour if the corpus is absent, and says
which mode it is in (`--no-targeting` A/Bs it).

### Two corollaries worth remembering

1. **A large `closeness` and a hard function are different things.** 699 records rank as "near-misses" with
   closeness up to 278 purely because a stub-sized draft was scored against a large target. Ranked by
   closeness they look like a wall of nearly-done work; they are **un-attempted work misfiled as
   near-misses** — fresh crack fuel, not a backlog of hard functions. Hence the separate `redraft` bucket:
   the routing is opposite (re-draft vs seed-tweak).
2. **`match_one` MATCH still ≠ bank (§58), measured.** A 12-draft gate probe of the `integration` bucket
   (reach-134, ov_SC01_077) banked **1 of 12**; the other 11 failed PLUMBING. So the 306 is a pool of
   integration candidates whose conversion depends on the reconcile ladder — it prices Task 14, it is not
   306 free banks. (Note the harvest_verify failure LABEL is the §58 red-herring: 10 of the 11 reported the
   same `conflicting types for built-in function` line from an unrelated TU position.)

### The parallel-probe race this surfaced

`masked_diff._common_typedefs()` wrote, read and deleted ONE shared path `src/.masked_diff_probe.c`. Under N
concurrent `match_one`/permuter processes, whoever unlinked first made another's open/parse fail, and that
process died with a traceback instead of a verdict: **14 of 1,752 drafts lost in a single 12-way run (0.8%)**
— and every parallel wave has paid it invisibly, because a drafter that crashes on its self-check merely
looks like a drafter that failed. Now per-PID. Same defect class, one level down, as the Phase-28
`match_one --work` shared scratch whose docstring promised the isolation its default contradicted.

### §60a — What the first DIRECTED grinder run exposed (Phase 29 Task-13B, 2026-07-21)

Turning the targeting on and running the grinder bounded (`--once --batch 8 --permute-secs 90`) produced a win
on the FIRST candidate — `func_80181F78`, close=1, classified `DELAY-SLOT`/schedule, banked in ~6 min — and
then immediately surfaced three latent defects that had been unreachable **because the daemon had not banked
anything since Phase 21**. All three are the same shape: a step whose REPORT and whose WORK had quietly
diverged.

1. **`gate_stage`'s commit path crashed on `src=None`.** `src` is deliberately never defaulted (the Phase 26-A
   audit: a default would silently PIN the gate to the main `.c`), but the commit did `git add src …`
   unconditionally. So every caller that omits `src` — grinder, orchestrator, idiom_hunt — crashes
   **the moment it banks**. Fix: `git add -u src/` (every modified tracked file under src/), which also
   retires the `src/ov_*/*.c` filename glob that once omitted 4 R22-verified banks from a commit because a
   family's members do not all live in the same-named split.
2. **The `_xform` ladder dirs accumulate.** `<drafts>-cn/-cast/-rc/-uni` are reused across runs and the
   transform tools only write the drafts they are handed, so every stale draft from every previous run
   survives and is re-submitted to the byte-gate. Measured: the grinder submitted **1** draft, the gate
   processed **34** and banked **2**. Nothing wrong entered the tree (G3/P9: the gate banks only
   byte-identical output) — but a run banked a function it was never asked to try, and would have committed
   it under a message naming a different one. Fix: clear the out dir per run. Note the symmetry with R32: a
   scanner that silently NARROWS its input hides work; a stage that silently WIDENS it fabricates provenance.
3. **The grinder fired the fleet-wide propagate from inside the gate.** `gate_stage(propagate=True)` runs
   `dedup_propagate --auto-from` — the §55b path that timed out at 3600 s and left 90/140 overlays broken,
   and which, being *inside* the gate, takes the banks down with it when it fails. The unattended caller must
   never fire it: bank with `propagate=False`, commit the cheap verified banks, then run ONE targeted
   `dedup_propagate --addr` as its own batch.

**The transferable point:** a tool that has been failing for a long time accretes latent bugs on its success
path, because nothing exercises it. Before trusting an unattended fix-and-run, budget for the first success
to fail — and check the tree state, not the exit code (here the durable Task-12 winner save in
`.run/permuter-winners/` is what made the crash a non-event).
