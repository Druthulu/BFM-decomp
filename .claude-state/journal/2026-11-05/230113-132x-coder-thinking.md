---
ts: 2026-11-06T06:01:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vWGzyYfUEsYWmm3625L7
---
Now write notes.md for the three family items. Also cleanup: delete the hdump dump dirs (item 1 and 75820) per the brief ("cc1 dumps go under your item dir and are deleted as soon as you have read them"). The dump dirs are ~big. Let me remove them.

Item dirs with dumps:
- .run/P40/T11/G21x/func_80150170__func_80150170/dump
- .run/P40/T11/G21x/func_80175820__func_80175820/dump
- .run/P40/T11/G21x/asmframe (probe dirs) — scratch, remove.

Also the .run/P36/engine scratch from --keep — the brief says `--keep` scratch is removed after use. Those are in .run/P36/engine/score/... (shared engine scratch). I should remove my item's scratch dirs: ov_MAIN_012__func_80150170, ov_MAIN_012__func_80175820, etc. Hmm, those may be shared. The tool creates per-item scratch under .run/P36/engine/score/<tu>__<fn>/p<pid>. Let me remove the specific ones I created (func_80150170, func_80175820, func_801758FC, func_801759D8, ov_SC04_018__func_80180D38). Actually --keep scratch is per-call; the tool normally deletes them. I'll remove the dirs I saw.

Let me first write notes, then cleanup.

Notes for 75820: describe the match.
Notes for 758FC: same.
Notes for 759D8: same + struct decl placement.

Let me write them.
