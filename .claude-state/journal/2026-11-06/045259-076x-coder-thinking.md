---
ts: 2026-11-06T11:52:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TSWjwgNzRuM8Px5b9cUh
---
I duplicated "otfirst" and "otboth" as nearly identical (otboth is the same as otfirst but the first store uses ot). Actually "otfirst" uses `*ot` in the first store too — identical to otboth. Let me fix otfirst to use the recomputed expression (as base) while ot is looked up first. Let me edit: in otfirst, `*(u32 *)p = (pv & 0xFF000000) | (*(u32 *)D_800AE7BC[D_800B9A02].a & m24);`. Then otboth keeps *ot. Fine, let me patch.
