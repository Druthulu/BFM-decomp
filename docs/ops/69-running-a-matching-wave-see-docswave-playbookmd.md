## §6.9 Running a matching wave — see `docs/wave-playbook.md`

**GATING IS FULLY PARALLEL AS OF P31 S67 — there is no serial lane.** `tools/parallel_gate.py`
handles jtbl carves too (`isolate_asm()` gives a carving worker a writable copy of the ONE binary's
3.6-5 MB asm subtree instead of symlinking all 448 MB). Measured: 13 fns/13 binaries in 139 s and
19 fns/14 jtbl binaries in 188 s, against 58 minutes for a single jtbl binary serially.
**Always `make -j$(nproc) build`** — a per-binary build is ~35 objects and was single-threaded
(7.18 s -> 1.18 s, byte-identical); every tool that shells `make build` now passes `-j`.

The start-to-finish operational sequence (draw → cards → packs → validate → draft → split-gate →
twin_sweep → harvest → R22 → checkpoint), with the measured failure that justifies each guard.
The tooling-inventory rows below are the per-tool REFERENCE; the playbook is the PROCEDURE.
`docs/automation-runbook.md` is the retired OpenRouter-era campaign — not the current pipeline.

