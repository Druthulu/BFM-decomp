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
