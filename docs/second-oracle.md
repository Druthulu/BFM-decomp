# The second, disagreeing oracle — coverage & the main-EXE deferral (Phase-27 T10)

> **R34:** the whole-binary byte-gate is a perfect CORRECTNESS oracle and a NULL COVERAGE oracle —
> it is green at any decomp %, so it cannot see a function splat mis-sliced or invented (the `.s`
> pieces paste back verbatim, image byte-identical either way). Only a SECOND, INDEPENDENT boundary
> oracle can. `make audit-corpus` (`tools/corpus.py --audit`) is it: it cross-checks splat's function
> boundaries against `sig_image`'s, which are derived from the ORIGINAL bytes without splat or Ghidra.

## Coverage (who the second oracle can see)

| binary | independent sig? | covered | why |
|---|---|---|---|
| 138 overlays | `sig_image` (byte-derived) | ✅ | validated 58,524/58,621 vs spimdisasm |
| resident | `sig_image` (**Phase-27 T10**) | ✅ | `make sig-resident` — 144 fns, all 21 stubs present, 0 phantom/truncated |
| main | `sig_image` multi-range (**P31 S77**) | ✅ | `make sig-main-oracle` — 28 game-code ranges, 986 fns, **0 phantom / 0 truncated / 1 pad-tail** |

`corpus.sig_is_independent()` gates the check to exactly this domain: a boundary cross-check applied
where the two oracles were never measuring the same thing is noise, not thoroughness (the audit's own
R14 lesson — over all 136 it reported 914 "slices"; in-domain, 193, all one real defect).

**Resident (now covered).** `make sig-resident` signs the resident flat blob with `sig_image`
(`--vram-base 0x800CEDF8`) instead of the Ghidra dumper, making its sig independent. Probed clean
(0 phantom + 0 truncated). ⚠️ The check is only valid while `.run/sig.resident.jsonl` IS the sig_image
sig — run `make sig-resident` before `make audit-corpus` (a stale Ghidra sig there resurrects the
"measuring Ghidra's limits" artefact). `h_exact` is raw-byte SHA1, so `weighted_metrics` is unaffected
by the swap (fleet % unchanged to the decimal).

## Main EXE — DELIVERED (P31 S77). The deferral below is kept as the design record.

`make sig-main-oracle` signs the ORIGINAL EXE bytes and `corpus.sig_is_independent("main")` is now
True whenever `.run/sig.main.oracle.jsonl` exists. All three structural blockers are closed:

1. **The 0x800 header** — `--vram-base 0x8000F800` maps file offset 0 to vram, so the header simply
   falls below the first code range. No `--skip` needed.
2. **Interleaved data + linked islands** — new `--segments <splat yaml>`
   (`sig_image.code_ranges_from_splat`) derives **28 game-code ranges** from the yaml's SEGMENT rows.
   It reads `[file_off, type, name]` and NOTHING else: segment *types* are coarse structure, not
   splat's *function* boundaries, so the two oracles stay independent exactly where it matters.
   `--exclude-subsegs` drops the LINKED PsyQ blocks.
3. **One text range** — the signer now loops ranges, bootstrapping entries INSIDE each. Per-range
   discovery is what stops the linear partition running through a data island and minting functions
   out of it, i.e. the detector manufacturing the phantom class it exists to detect.

**The trap was avoided, not worked around.** Entries are still found by byte-derived jal-closure;
nothing is seeded from splat's symbols. `.run/sig.main.jsonl` (the splat-SEEDED atlas sig, P31 T3)
is a DIFFERENT file and the audit never reads it — `corpus.ORACLE_SIG` keeps them apart.

**Domain (R14).** The oracle signs game code only, so `audit("main")` filters the LINKED stubs out.
Auditing them against it would report ~960 phantoms that are artefacts of comparing two oracles that
never measured the same thing — the same 914-vs-193 mistake this file already warns about.

**First finding, and it is a real one.** `func_80062144`: splat's `.s` says 65 instructions, the
byte-derived boundary says 64. The extra line is a `nop` at `0x80062244`, emitted one line BELOW
`endlabel`. That is a **PAD-TAIL**, now its own audit class — a known alignment artefact the matching
side handles by emitting the pad from C (cookbook §295; two S77 wave agents did exactly that on
`func_8005E13C` and `func_8005D538`), not a splat mis-slice. Reporting it as TRUNCATED would have
made the oracle's first real finding look like a defect and buried the class that is one.

**Fleet status after wiring:** `make audit-corpus` → **0 PHANTOM + 0 TRUNCATED**, +1 PAD-TAIL.

---

## (Historical) Main EXE — why sig_image could not sign it

`tools/sig_image.py` assumes a flat blob whose file offset 0 IS its vram base, one contiguous code
region, and one `[lo,hi)` text range. The main EXE breaks all three — structurally, not with a flag:

1. **PS-X EXE header.** The EXE has a 0x800 header before the code; `sig_image` maps `off = start −
   vram_base`, so file offset 0 must equal vram. Needs a `--file-offset`/`--skip 0x800`.
2. **Interleaved data islands + linked PsyQ regions.** `detect_code_end` stops at the first sustained
   invalid run, and `bootstrap_seeds` linear-partitions from one entry — both assume ONE code prefix
   then data. main has rodata/data islands and linked libcd/libgs/… regions between code. Needs an
   island list, not a single range.
3. **One `--text-lo/--text-hi`.** No multi-range support.

**The trap in the cheap workaround.** Seeding a main sig_image run from splat's symbols destroys
independence *for the PHANTOM class specifically* — a phantom IS a splat-invented address, so seeding
from splat makes every phantom look real. A seeded run still buys the TRUNCATED class (boundaries
re-derived by `func_end`), but it is a half-oracle, and calling it "the second oracle" would be the
exact self-deception R34 exists to prevent. So: **deliver an honest deferral, not a fake oracle.**

**The scoped design (when it's built):** teach `sig_image` (a) a `--file-offset` for the header, (b) a
segment list (from the splat yaml's `[vram, type]` rows — types, not function boundaries, so it stays
independent of splat's *function* slicing) so it signs each code segment and skips data/linked islands,
(c) multiple text ranges. Then `sig_is_independent("main")` → True and the EXE joins the audit.

**Interim (Phase-27):** main's boundary blind spot is DOCUMENTED, not silently green. A cheaper partial
that closes it sooner: a fresh **Ghidra** `make sig-refresh` (R23 — MCP stopped) at least refreshes the
month-stale main sig `weighted_metrics` reports from; it is not independent (Ghidra boundaries), so it
does not serve the audit, but it makes the MAIN game-code weighted number current.

## The completion metrics (roadmap §1 "all three, with main in the denominators")

`tools/progress.py --fleet` reports:
- **fn-count byte-ident** — includes main (×134-inflated; one crack counts per overlay).
- **instr-weighted** — resident + 138 overlays (the decomp.dev-DISPLAY number). Main is NOT folded in.
- **distinct-code** — each h_exact class once.
- **MAIN game-code weighted** *(new, T10)* — reported SEPARATELY, `main_pct`, from main's
  LINKED-excluding Ghidra sig. It is game-code-only (LINKED = complete, in fn-count) and PROVISIONAL
  (the sig is dated; see `main_sig_date`). It is not folded into the decomp.dev-comparable fleet number
  because folding a stale/incomplete value would mislead the flip-timing checkpoint. A fresh/complete
  main sig (sig-refresh, or the sig_image-on-main oracle above) makes it authoritative and foldable —
  a roadmap decision for when the number is trustworthy.
