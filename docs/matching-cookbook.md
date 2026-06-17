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
