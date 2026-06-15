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
