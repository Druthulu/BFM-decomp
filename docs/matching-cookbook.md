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
block at the TOP of `ov_SC01_077.c` (LOCAL, not engine_core.h — reach-1 names differ across overlays).
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
6. **Op gotcha (Phase 22 T2, byte-proven):** do NOT run a second `make`-invoking job (`make check-all`, `make report`) CONCURRENTLY with `dedup_propagate` — parallel make wrote a partial `.o` (`file format not recognized` on ov_SC04_016) AND the propagation's final byte-gate+registry step was lost (source propagated, but `config/dedup.us.yaml` group unwritten → progress.py under-counts). Serialize all make jobs; re-running `dedup_propagate` is idempotent (detects the existing macro/instantiations, just rebuilds+registers).
