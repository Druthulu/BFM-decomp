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
  object list in a committed regen script (`tools/make_libgs_block6.sh`) — SDK-derived dir, gitignored.

---

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
