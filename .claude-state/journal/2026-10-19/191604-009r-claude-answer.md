---
ts: 2026-10-20T01:16:04.013Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a543aec0a7c70e120
model: claude-opus-5-5[1m]
effort: medium
turnId: 279f4a59-e9bd-43fe-b6f4-cb544d688d68
usage: {input: 28, cacheRead: 1367088, cacheWrite: 25350, output: 11134}
---

I've finished the review. About 25 GB of the 40 GB in `.run/` can go: that would take free space from about 6 GB to about 31 GB. Nothing has been deleted yet.

**What I'd delete (about 25 GB)**

| What | Size | Why it's safe |
|---|---|---|
| Old matching-campaign drafts: 121 `wave_xx` folders, the `wave_m*`, `wave_p31*` and `wave_g*` folders, `sweep_*` staging, and 303,550 loose `wave_*_targets.N.json` files | about 9 GB | All from Aug–Sep, from the campaign lane we retired in Phase 31. Every function is matched now, so the "recovery pass" these drafts were kept for no longer applies. Any wave folder that a tool or doc still names is excluded. |
| P32 `t3`, except its 89 git-tracked files | about 6.1 GB | Old object and compile trees with no reader. The reports, verdicts and bodies that matter are tracked and stay. |
| P36 lever-removal scratch: `delever/obj`, `engine/score`, `declrepair`, the permuter runs, the `regen` candidate folders and the agent packs | about 7.2 GB | Compiler output and search scratch. The ledgers and outcome files the tools read stay: `delever/ledger.jsonl`, `engine/outcomes.jsonl`, `engine/bodies`, `regen/*.tsv`, `permuter/outcomes.jsonl`, `agents/METHOD_S103.md`. So do all tracked files. |
| P37 `census/cache` | about 1.2 GB | A speed-up cache. It rebuilds by itself on the next `tools/type_census.py -j 16 --sites`. |
| `hseq_*.txt`, 80,070 files | about 0.3 GB | `tools/family_sweep.py` rewrites them. |
| `tmp*` folders, about 63,000 empty or near-empty ones | about 0.2 GB | Temp folders that two tools never remove (below). Anything touched in the last day is skipped. |
| `keep/p37-ledger.jsonl` | about 0.3 GB | I checked it: its 269,013 lines are byte-identical to the start of the live ledger, and the compressed snapshot beside it has the same lines. |
| Small dead scratch: `match/`, `gate_main_fail`, `gate_lane`, `p31p_repair`, `p31q_repair`, `T3`, P38 `t51` (except `c2_renames.tsv`) | about 0.6 GB | Nothing reads them. |

**What I'd keep, and why**
- **PA3's own entries:** `P40/` (the open phase), `mod/`, `plans/`, `status.json` and `health.json`.
- **Data the tools read:**
  - the live ledgers `P37/restruct/ledger.jsonl` and `P36/delever/ledger.jsonl`, and the rest of P37's census;
  - `P39/census`, which feeds the progress chart;
  - `P35`, `P33` and `P33.5`;
  - `auto/`, which holds live locks and state;
  - `obj40/` and `obj42/`, which the Makefile links against;
  - `ghidra_c/`, which comes from Ghidra and is expensive to rebuild;
  - `c294/`, `giants/` and `ghidra_export/`;
  - the `sig.*.jsonl` signature files, `backlog.jsonl`, `fuel_manifest.json`, `atlas.json` and its companions.
- **Snapshots:** the three compressed ledger snapshots in `keep/`.
- **`P33/permuter-upstream`:** it holds an unpushed git branch, `reloc-masked-scorer`.
- **Everything git-tracked:** untouched. The script uses `git clean -X`, which can only remove ignored files.

**What can be rebuilt instead of kept.** These stay this time, but each can be regenerated if we ever need the space:
- the overlay signature files, with `make sig-overlays` (about 4 s);
- `atlas.json` and its companions, with `make atlas`;
- the logs, with `make extract-all` / `make check-all`;
- `ghidra_export`, with `tools/ghidra_export_annotations.sh` (about 18 s).

**Two folders I'm not sure about, kept unless you say otherwise (2.6 GB)**
- **`keep/p39-census` (1.4 GB).** A copy of the 3.39 census that differs from today's in 5 files. It looks like a frozen baseline from early this phase, and only a log mentions it.
- **`P38/census` (1.2 GB).** Nothing uses it except an out-of-date default in `tools/struct_twins.py`. The task summaries already say to point that tool at P37. Deleting it is safe once a coder fixes that default.

About 2 GB of other small older folders (`S*`, `s*`, `t*`, `drafts*`) also stay for now. Some of them are cited in the ops docs, and checking each one isn't worth it for the space.

**One cause to fix later.** `tools/psyq_integrate.py:83` and `tools/psyq_link_region.py:86` create temp folders in `.run/` and never remove them. That's where the 63,000 `tmp*` folders came from. A coder can fix that after this phase closes.

Pick an option in the picker. On a yes, I'll write the deletion script, check every path in it and give you one `!` command to run.
