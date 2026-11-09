# 3.42 T5 — 2026-11-08: share_body_cycle.sh commits via commit_task.sh

- `tools/share_body_cycle.sh` commits each green batch with `bash tools/commit_task.sh $TASK "<bucket batch line>" <paths>`; paths = every changed/untracked file under `src/` and `config/` (`git status --porcelain --untracked-files=all`). `TASK` env, default `T5.c1`: `TASK=T6.c1 bash tools/share_body_cycle.sh 1 10 2 cross`.
- A batch with no src/config change is not committed (all classes rejected); the cycle goes on.
- R22 is no longer an `--allow-empty` commit: the cycle prints `cycle: R22 after batch k — <line> at <sha>`, log `.run/3.42/baseline/r22_t5_<bucket><k>.log`.
