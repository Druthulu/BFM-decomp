# PsyQ SDK sample-source notes (P31 T2 seed — grows as the drafting lanes consume it)

> **What this is.** The PsyQ 4.0 dev CD on disk (`tools/psyq/…(Track 1).bin`) contains Sony's SDK
> sample C source — the skeletons era programmers (Square included) started from. Extracted in P31
> T2 to **`tools/reference/psyq-sdk/`** (gitignored, regenerable — see `docs/SETUP.md` §5.6 for the
> exact command + counts). This doc is the committed knowledge: what's there, the toolchain
> provenance found on the disc, and the style conventions that should inform drafts. It is a SEED —
> extend it as agents mine specific samples for specific BFM subsystems (R16).

## Why it matters for matching (not for the libraries)

The PsyQ code **inside** BFM is already byte-identical via object linking (LINKED 959, Phases 7–8)
— nothing to decompile there. The samples matter for **Square's own code that calls PsyQ**: byte
matching is sensitive to source shape (variable order, loop idiom, temp usage), and Sony's samples
are the canonical shapes those call sites were written from. Highest-leverage consumers: **main's
~1,034 remaining stubs** (boot/CD/GPU/pad — the most sample-like code in the game) and any overlay
function anchored on PsyQ calls.

## Inventory (extracted 2026-08-14)

- **2,374 files / 231.6 MB** from the ISO (7 out-of-track `.DA` audio files skipped — audio tracks,
  no code). **400 `.c` files**: 382 under `PSX/` (373 in `PSX/SAMPLE/`), 17 `PSSN/`, 1 `3RDPARTY/`.
- `PSX/SAMPLE/` groups: `CD/` (EARTH, MOVIE, STR3D, TUTO) · `GRAPHICS/` · `SOUND/` · `MODULE/` ·
  `ETC/` · `MATH/` · `CMPLR/` (compiler-behavior demos!) · `KANJI/` · `PRESS/` · `DS/` · `SCEA/` ·
  `SCEE/` · `AUTOPAD/` · `DONGLE/`.
- Also on the disc: `PSX/INCLUDE` + `PSX/LIB` (another copy of headers/libs), `DOC/`, `GNU/`
  (compiler **binaries** + SN documentation — no GNU source on the disc), `CDGEN/`, `BETA/`.

## Toolchain provenance found on the disc (feeds the §31 map's source-version note)

**`GNU/SNGNUVER.TXT`** — SN Systems' own build-history for the PSX gcc: lineage
`2.7.2.SN32.3.x`, current at disc mastering **`2.7.2.SN32.3.7.0002` (14.5.97)**, with a per-build
changelog naming the exact files SN patched vs vanilla 2.7.2:

- `MIPS.C` — temp-file handling fixes (non-codegen)
- `CCCP.C` — DOS-path/`.OBJ`-suffix preprocessor fixes (non-codegen)
- `SDBOUT.C` — debug-output dimensions (non-codegen)
- `N64.H` — no `__main` insertion when `main()` defined (startup, non-codegen for our fns)
- **`UNROLL.C` — "parameterise max. number of insns allowed in an unrolled loop" (CODEGEN-RELEVANT):**
  the one named SN divergence from vanilla 2.7.2 that could move bytes (loop-unrolling limits).
  If a loop-unroll-shaped residual ever defies the vanilla-2.7.2 `unroll.c` model, this is the
  first place to look. (`GNU/SNGNUBUG.TXT` = known-bugs list, same vintage.)

Everything else in the changelog is plumbing — consistent with 26 phases of byte evidence that our
pinned vanilla-shaped cc1 reproduces the game's codegen.

## Style conventions (first skim — STR3D/TUTO0.C and peers; refine per-subsystem as mined)

- `/* $PSLibId: Run-time Library Release 4.0$ */` header stamps; Shift-JIS comments alongside English.
- **File-scope `static` state** over locals-passed-around; globals for buffers with ALL-CAPS
  `#define` addresses (`#define TEX_ADDR 0x80010000`).
- `#define`-driven feature config (`#if defined(...)`) rather than runtime flags.
- Init/start/poll function triples for streamed subsystems (`init_anim` / `start_anim` /
  `poll_anim`) — a shape to expect in BFM's loader/streaming code.
- Old-style parameter lists and int-heavy typing (K&R-adjacent), consistent with the loose-typing
  wall measured in BFM's engine.

## How to consume (the lane hook)

When drafting a PsyQ-call-anchored stub (especially main), `grep -ril <PsyQ-fn>` over
`tools/reference/psyq-sdk/PSX/SAMPLE/` and hand the closest sample to the drafter as a style
prior. `SAMPLE/CMPLR/` is a bonus corpus: Sony's own compiler-behavior demos, useful as §31-map
exemplar inputs.
