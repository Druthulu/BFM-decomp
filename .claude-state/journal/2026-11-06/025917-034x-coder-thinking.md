---
ts: 2026-11-06T09:59:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_82EutWFOuiQIxcRLWlbg
---
The object contains the whole TU, and the label is func_800CD314 but the code shown is a different function (func_800CD5F8). Because the object includes all functions; the `--keep` object is the whole TU compiled, and insns_from_object with fn restricts to that function label. My sed matched `<func_800CD314>` but the tail went past into the next function. Let me extract only the func_800CD314 block.

Actually the last jal is `R_MIPS_26 func_80146C3C` with `move a0,s2` — that's in func_800CD5F8. Let me find the func_800CD314 label specifically.
