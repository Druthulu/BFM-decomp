# §P40 T1 — 2026-10-14: which census dir each tool reads; the two ledgers stay local

## Census dirs (settled, measured at 1109994812)
- Gate + work dir `.run/P37/census`: `type_census.py` default `OUT_DIR_DEFAULT` (type_census.py:54), so `--check-casts --residue` writes `residue_census.{json,txt}` there and reads its `sites.jsonl`; `restruct.py` `CENSUS` (restruct.py:100: struct_map, body_base_type, sites.jsonl for `--check-residue`); `restruct_cycle.sh:66` refreshes it each batch.
- Series dir = the newest `.run/P<N>/census/type_census.json` by numeric N (today `.run/P39/census`): `readability_progress.py:63`, `progress.py:1181` (Types block); `progress.py:1214-1218` pairs the residue gate clause from that dir, else the newest `residue_census.json` by mtime (today P37's). `restruct_cycle.sh:69-71` refreshes the newest dir after each batch.
- Lever census: `.run/P36/census` (lever_census.py:53); `progress.py:1162`.
- Creating any `.run/P40/census/type_census.json` moves the series to it. Do it on purpose or not at all (scratch goes to `.run/P40/<task>/`).

## The ~5-6 site "P37/P39 disagreement" (3.39 T9:25, T11:19) is not a dir difference
- With both dirs run on the same tree they agree exactly (P 257,475, M 15,129); a `--no-cache` run gives an identical `sites.jsonl`.
- The gap is two predicates. The series shows `casts.by_form` (every raw site); the gate shows `casts.check_raw` / `residue_split`, which drops the `defline` sites, i.e. the casts inside `#define` lines of `include/common.h` (:43 M, :74-78 P), via type_census.py:2039. by_form − check_raw = P 5 + M 1, matching T11's 6.
- The README Types block printed the four-form total (by_form) beside the gate clause (check_raw), so the two numbers looked like a disagreement.

## Ledgers
- `.run/P36/delever/ledger.jsonl` untracked at fae956dbcb (`git rm --cached`); `.gitignore` lists both ledgers explicitly (the `.run/` line already covers them).
- Gz snapshots: `.run/keep/p36-delever-ledger-20261014.jsonl.gz` (sha256 of content bbac6c64…, 32,633 lines) and `.run/keep/p37-restruct-ledger-20261014.jsonl.gz` (3e0e5cc5…, 269,013 lines). Restore with `zcat`.
- `commit_task.sh` refuses an ignored path (it runs `git add` without -f); a staged `git rm --cached` is committed by passing any other path.

## Gotcha
- `type_census.py --no-cache --out-dir <new dir>` crashes in `write_parked` (FileNotFoundError): the dir is created only on the cache path (:1064). Run `mkdir -p` on the dir first.
