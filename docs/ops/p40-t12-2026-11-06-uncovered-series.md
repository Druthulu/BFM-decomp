# P40 T12 — 2026-11-06: the `uncovered` series beside raw casts

- `tools/readability_progress.py`: appended column `uncovered` = sum over P/I/X/M of `residue_census.json` `by_form[f].uncovered`.
  Source: the residue census beside the snapshot's type census (newest `.run/P<N>/census`), else the newest by mtime; used only
  when its sibling `type_census.json` is fresh (HEAD or src stamp) and not newer than it; otherwise blank with a stderr note.
  Older rows stay blank.
- So a snapshot that should carry `uncovered` first runs `PY tools/type_census.py -j 16 --check-casts --residue --out-dir .run/P<newest>/census`
  (one run writes both files into the same dir; ~3 min).
- `tools/timeline.py` `cast_rows()` adds form `uncovered`; `render_svg` draws it in orange on the four-form series' base (so 0 sits on
  the floor under the raw line), with the legend "raw = debt left; uncovered = what the gate fails on. Green by ledger is not debt gone."
