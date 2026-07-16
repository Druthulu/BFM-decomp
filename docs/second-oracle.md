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
| main | — | ❌ **deferred** | `sig_image` cannot yet sign the EXE (below) |

`corpus.sig_is_independent()` gates the check to exactly this domain: a boundary cross-check applied
where the two oracles were never measuring the same thing is noise, not thoroughness (the audit's own
R14 lesson — over all 136 it reported 914 "slices"; in-domain, 193, all one real defect).

**Resident (now covered).** `make sig-resident` signs the resident flat blob with `sig_image`
(`--vram-base 0x800CEDF8`) instead of the Ghidra dumper, making its sig independent. Probed clean
(0 phantom + 0 truncated). ⚠️ The check is only valid while `.run/sig.resident.jsonl` IS the sig_image
sig — run `make sig-resident` before `make audit-corpus` (a stale Ghidra sig there resurrects the
"measuring Ghidra's limits" artefact). `h_exact` is raw-byte SHA1, so `weighted_metrics` is unaffected
by the swap (fleet % unchanged to the decimal).

## Main EXE — why sig_image can't sign it yet (the deferral)

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
