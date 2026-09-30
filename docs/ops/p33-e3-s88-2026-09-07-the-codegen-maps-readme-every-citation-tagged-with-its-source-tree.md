### P33 E3 (S88, 2026-09-07) — the codegen map's README + every citation tagged with its source tree
- **Why.** `docs/gcc-2.7.2-map/` was written (Phase 23) against `tools/reference/gcc-papermario`, which is gcc **2.8.1**, and
  audited (P29 S23) against the vanilla 2.7.2 subset — the mechanisms held (119 confirmed · 40 line-drift · 7 refuted of 21
  raised · 4 unverifiable) but the line numbers stayed MIXED. `docs/gcc-2.7.2-map/README.md` (NEW) is the map's front page:
  the five files and their pass groups, the condensed §31 triage table, the byte-proof method, the provenance legend, the
  2.8.1 line-number caveat (`combine_regs` +103 … `choose_reload_regs` +611), the gcc-source fetch note (GNU ftp tarball,
  sha256 `7cd8bce5…`; the papermario pin), and the tag census. In `tools/doc_links.py`'s default set.
- **`tools/gccmap_cites.py`** (the row above). Derivation order, from the trees never typed (R33): a quoted source snippet
  near the cite → an underscore identifier's function extent (`^name (` headers, GNU style) → the nearest occurrence within
  ±60 lines → the author's cue (`papermario …` / `2.7.2 …` / the decisive `→2.7.2 :NNN` arrow) → `cite_overrides.tsv`
  (human verdicts with the construct + its line in the other tree) → a TIE is a valid 2.7.2 line. A cue that contradicts
  the evidence leaves `[?]` (R34); a line past the end of the 2.7.2 file is 2.8.1; `engine_core.h` is `[repo]`.
- **Three instrument defects found by its own controls/verify (all fixed before the tags were written):** (1) span pairing
  inside a text window inverted the backtick pairs and dropped the identifiers right next to a cite; (2) fenced code blocks
  inverted the pairing for the rest of a document; (3) after writing, a neighbouring cite's tag read as a `2.8.1` cue —
  the instrument reading its own output (R57) — caught by `--verify`, which re-derives every written tag.
- **Census:** 135 cites in 5 files — see the README's tag table for the final counts; `--controls` 6/6 (the map's own
  known-true cases, both drift directions); `--check` OK; second write = 0 files changed (idempotent).


