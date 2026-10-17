---
ts: 2026-10-17T11:46:42.351Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I'm checking the residue TSV rows to match file names against function names, trying to untangle which row corresponds to which overlay source file like ov_SC06_018 and ov_SC06_033.

I realize different packs can share the same function name across overlays, like func_8018BCD4 appearing in both SC06_033 and SC03_001 as distinct functions, so I need to pick the correct exemplar pack per class: 26f44 maps to ov_SC06_018__func_8018FF98, 45b3d to ov_SC06_011__func_8017DE14, 7e3ee to ov_SC03_090__func_80187F4C, c5888 to ov_SC05_018__func_80185754, e9540 to ov_SC03_124__func_8018A788, eb3ad to ov_SC01_009__func_8017EB08, and ed951 to ov_SC03_093__func_80182000. Now I want to verify by checking the residual headers and body sizes for all seven of these.
