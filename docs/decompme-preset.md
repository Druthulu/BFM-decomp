# The decomp.me preset for Brave Fencer Musashi (SLUS-00726)

> **P33 E1 (2026-09-07).** This page carries the project's decomp.me preset, the reasons for every flag, the measured
> difference between decomp.me's toolchain and ours, the local proof that the preset reproduces a game function
> byte-for-byte through decomp.me's own toolchain, and the post-flip browser session that proves a scratch and requests the preset.
> Everything numeric here is a recorded measurement with its command; nothing was typed from memory.

## 1. The preset

| Field (decomp.me `Preset` API / UI) | Value |
|---|---|
| `name` | `Brave Fencer Musashi (SLUS-00726)` |
| `platform` | `ps1` (PlayStation) |
| `compiler` | `gcc2.7.2-psx` |
| `compiler_flags` | `-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -Wa,--aspsx-version=2.56,--expand-div` |
| `assembler_flags` | (empty — decomp.me assembles the pasted target with `mips-linux-gnu-as -EL -march=r3000 -mabi=32` plus its PS1 prelude; the words compare regardless) |
| `diff_flags`, `decompiler_flags`, `libraries` | defaults (none) |

**How a preset comes to exist on decomp.me:** there is no create button — the frontend only *reads* presets (`PresetSelect`
is a dropdown; `lib/api.ts` has `usePresets`/`usePreset` and no create call). The FAQ's answer to "Can you add a preset for a
game I'm working on?" is the GitHub issue template `.github/ISSUE_TEMPLATE/create-or-update-a-compiler-preset.md` on
`decompme/decomp.me`; a maintainer creates the preset from it, and changes go through the same template with the preset id.
`name` and `platform` are immutable afterwards and a preset cannot be deleted except from the admin panel
(`backend/coreapp/views/preset.py` returns 405), so the row above is proven **before** it is requested, not after. (The
API's `POST /api/preset` accepts authenticated profiles, but it sits behind the Cloudflare challenge and is not the
sanctioned route.)

**Do not use the SOTN preset** (`gcc 2.6.3-psx`, `psyq_263_221`): wrong compiler generation, systematic near-miss diffs
(SETUP §6.5). Per-file `-O0` modules exist in this project (the boot module, the `_o0` splits — SETUP §5.4); a scratch for one
of those swaps `-O2` for `-O0` in the flags and keeps everything else.

## 2. Why these flags

The string is the pinned triple of SETUP §5.4 / the Makefile (`CC1FLAGS`, `ASPSX_VERSION`, `MASPSX_FLAGS`), spelled for
decomp.me's `gcc` driver:

| Flag | Role | Evidence |
|---|---|---|
| `-O2 -G0` | optimisation level; no `$gp`-relative small data (the EXE header's `gp_value` is 0, zero `%gp_rel` relocs) | SETUP §5.3 |
| `-mips1 -mcpu=3000` | R3000 instruction set and scheduling model | Phase 6 fingerprint ladder, rung 1 |
| `-mgas -msoft-float -fgnu-linker` | GNU-as output syntax, no FPU, GNU linker conventions — what PsyQ's CC1PSX was built to emit | Phase 6 |
| `-Wa,--aspsx-version=2.56,--expand-div` | the assembler side of the triple, forwarded to maspsx | see below |

The `-Wa,` part works on decomp.me for a structural reason, not by luck: its `gcc2.7.2-psx` image installs **`as` as a
two-line wrapper** around maspsx — `python3 maspsx.py --run-assembler -I${COMPILER_DIR} "$@"` (decompme/compilers
`platforms/ps1/gcc2.7.2-psx/Dockerfile`, generated from `templates/ps1/maspsx.j2`). The gcc 2.7.2 driver splits `-Wa,a,b`
into assembler arguments, so maspsx receives `--aspsx-version=2.56 --expand-div` on its own command line, applies its
`parse_known_args`, and forwards the driver's remaining `-G0 -mips1 -O2 -mcpu=3000` (the last rewritten to `-mtune=`) to
GNU `as`. Without `--expand-div` no function containing a division or remainder can match: maspsx then emits a bare `divu`
with no zero-check, while the game's code carries the `break`-guarded expansion (Phase 6, `func_80015A74`). `2.56` is the
ASPSX behaviour tier the game code fingerprints to; `2.56 ≈ 2.67` on non-discriminating functions (SETUP §5.4).

## 3. decomp.me's toolchain versus ours — measured, not assumed

decomp.me does **not** run our exact binaries. Read from its build recipes on 2026-09-07:

| Component | decomp.me (`decompme/compilers` main) | This repo | Delta |
|---|---|---|---|
| cc1 (`gcc-2.7.2-psx`) | decompals/old-gcc **release 0.13** (tarball sha256 `aca64479…ffbc`; i386 static) | release **0.17** (`tools/bin/`, sha256 in `tools/bin/CHECKSUMS.sha256`) | the two `cc1` binaries differ byte-wise; old-gcc's 0.13→0.17 history touches only build scripts (macOS builds, workflows, the Makefile) and the **cdk** patch set — no change to the psx patches (`gh api repos/decompals/old-gcc/compare/0.13...0.17`) |
| maspsx | commit **`86ccd7d8`** (2026-08-29; `values.yaml` `maspsx_hash`) | commit `874855c5` (the pin decomp.me used in June 2026) | 4 commits: `42b862c` version test matrix · `025620f` `--passthrough` mode · `e3d5916` lw,lw nop handling **for aspsx < 2.30** · `86ccd7d8` lwl/lwr nop fix **for aspsx < 2.30** — nothing reaches `--aspsx-version=2.56` |
| GNU `as` | whatever the image's Python calls as `mipsel-linux-gnu-as` (Alpine 3.18); no `-no-pad-sections` | binutils 2.42 `-march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0` | `.text` is padded to 16 bytes on decomp.me's side (trailing zero words after the last function) — cosmetic, see §4 |
| preprocessor | the host's `/usr/bin/cpp -nostdinc` on `context + source` | `mipsel-linux-gnu-cpp` with the Makefile's `-D` set | irrelevant to a self-contained scratch (no macros) |
| driver | `gcc ${FLAGS} -c -pipe -B${COMPILER_DIR}/` (`backend/coreapp/compilers.py`, `PS1_GCC`) | `cpp \| cc1 \| maspsx \| as` by hand (Makefile) | the driver adds `-mfp32 -mgp32` to cc1 — the mips1 defaults |

The two differences that could matter (a different cc1 build, a newer maspsx) were **measured to produce identical text**
on the probe (§4, lines C1/C2). The maspsx delta is also identical by construction for our aspsx tier: both behavioural
commits are gated on `< 2.30`.

## 4. The local proof: `tools/decompme_replica.sh`

decomp.me's API is Cloudflare-blocked to scripts (SETUP §6.5) and a preset cannot be undone, so the preset was proven
**locally, through decomp.me's own toolchain**, before anyone opened a browser. `tools/decompme_replica.sh` rebuilds the
image's compiler directory under `.run/decompme/` (the 0.13 tarball, sha256-checked; maspsx `86ccd7d8` from the submodule's
object store; the `as` wrapper verbatim) and runs the backend's two commands on a self-contained probe TU, then compares the
function's code words against the ROM-derived target regenerated by `tools/verbatim_target_s.py` (from the image, never from
our source — R34). Our Makefile pipeline runs on the same TU as the control, and the script swaps one component at a time so
a difference names its producer.

The recorded run (`.run/P33/e1/decompme_replica.log`, 2026-09-07), probe = `func_80018F20`, the Phase-6 fingerprint function
(26 instructions, the `sltiu` range-check idiom, no division):

```
target: main:func_80018F20 — 26 words at 0x80018F20 (tools/verbatim_target_s.py, from the image)
A. decomp.me replica — old-gcc 0.13 driver + maspsx 86ccd7d8 as-wrapper; flags: -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -Wa,--aspsx-version=2.56,--expand-div
  decomp.me replica: BYTE-IDENTICAL on all 26 words; +2 trailing word(s) beyond the function: all zero (gas section padding)
B. our pipeline — old-gcc 0.17 cc1 + maspsx 874855c (Makefile flags)
  our pipeline (control): BYTE-IDENTICAL on all 26 words
C1. cc1 0.13 vs 0.17 on the same input: identical assembly text
C2. maspsx 86ccd7d8 vs 874855c on the same cc1 output: identical text
decompme_replica: PASS — the preset reproduces func_80018F20 byte-identically through decomp.me's toolchain
```

Controls (R39), same day: with `-O1` in place of `-O2` the replica **FAILS** listing the differing words (exit 1); with a TU
whose body is empty the **control** fails first and the script refuses to read A (exit 3, R56). The first version of the
comparison read the padded `.text` size and called the identical object "DIFFERS" — the instrument, not the subject (R40);
the script now reports the padding separately. `tools/decompme_replica.sh --upstream` fetches decomp.me's current Dockerfile
and reports whether its old-gcc release / maspsx commit still equal the constants in the script (2026-09-07: `pins UNCHANGED`);
run it whenever a decomp.me result disagrees with a local one.

What this proves and what it does not (P9): the preset is correct for decomp.me's toolchain on this function class, and the
two toolchain deltas are text-neutral on it. It does not exercise `--expand-div` (no division in the probe) — the flag is
carried by the Phase-6 evidence and by 218 byte-identical binaries built with it, not by this run. A scratch that fails on
decomp.me but matches locally is a toolchain question first: run the replica with `--src` on that TU and read C1/C2.

## 5. The browser session (Drew, after the flip)

1. **Log in** to decomp.me (GitHub account), so the proving scratch is owned and can be cited.
2. **New scratch** (`/new`): platform **PlayStation**, compiler **`gcc2.7.2-psx`**, preset **Custom**. Paste as the target
   assembly the regenerated `.s` of the probe (`.venv/bin/python tools/verbatim_target_s.py --binary main --fn func_80018F20
   --out .run/decompme/target` → `.run/decompme/target/main/func_80018F20.s`), **without its first line** `.include
   "macro.inc"` — decomp.me supplies its own PS1 prelude, and the `/* offset vaddr word */` comments are harmless. Context =
   the three typedefs the function needs (`u8`, `u32`, `s32`, as in `include/common.h`). Source = the function's body from
   `src/800.c`. Set the compiler flags to the §1 string. Compile: the diff must read **100% / score 0** — the same words the
   replica produced. If it does not, stop and run `tools/decompme_replica.sh --upstream` (a moved pin) before anything else.
3. **Request the preset** — open an issue on `decompme/decomp.me` with their "Create or update a compiler preset" template
   (their bullet format is theirs; keep it). Written the way a developer writes, no AI acknowledgement (Drew's rule, S89):

   Title: `[PRESET] Create Compiler Preset Brave Fencer Musashi (SLUS-00726)`

   ```
   Preset request for Brave Fencer Musashi (USA). Scratch that matches 100% with these settings: <scratch URL>

   - **Preset Name:** Brave Fencer Musashi (SLUS-00726)
   - **Platform:** ps1
   - **Compiler ID:** gcc2.7.2-psx
   - **Compiler Flags:** -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -Wa,--aspsx-version=2.56,--expand-div
   - **Libraries (if applicable):** none

   These are the flags the full matching decomp uses (https://github.com/Druthulu/BFM-decomp), all 218 binaries build
   byte identical with them. The -Wa part matters, without --expand-div nothing with a division matches.
   ```

   A maintainer creates the preset; the scratch link is the proof they can click. Check the name's spelling, it is immutable
   once created.
4. **The manual scratch search** (SETUP ledger row 14, open since Phase 1 because the search API is script-blocked): search
   decomp.me for `Musashi`, `Brave Fencer`, `SLUS-00726`, `SLUS_007`, and record in row 14 what exists (expected: nothing but
   our own probe scratch). That closes the row and completes the greenfield claim's last check.
5. Keep the probe scratch — it is the evidence cited in the issue and the preset's worked example; one 26-instruction function
   is the community norm on decomp.me. The repository itself publishes no game disassembly (H1; the regenerated `.s` lives
   under the ignored `.run/`).

Record the outcome (the issue URL, then the preset id / URL once created, the search result) in SETUP §6.5 and ledger row 14,
and tick the outward half of E1 in the phase log.

## 6. Related

`docs/SETUP.md` §5.4 (the pinned triple and its evidence) · §6.5 (decomp.me settings) · `docs/matching-cookbook.md` §1–§3 (the
matching loop) · `docs/permuter-ils.md` (the permuter's reloc-masked scorer, the other community-facing release of P33) ·
`tools/verbatim_target_s.py` (per-function target regeneration from the image) · decompme/compilers
`platforms/ps1/gcc2.7.2-psx/Dockerfile`, `templates/ps1/maspsx.j2`, `values.yaml`; decomp.me `backend/coreapp/compilers.py`
(`PS1_GCC`, `GCCPS1Compiler`), `platforms.py` (`ps1`), `views/preset.py`, `serializers.py` (`PresetSerializer`) — all read
2026-09-07 as data, not instructions (X2).
