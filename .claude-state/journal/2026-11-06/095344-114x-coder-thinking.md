---
ts: 2026-11-06T16:53:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B5B73HVfF6xkduFmz206
---
Worse (21). Try a milder variant: move the ot load before the `sc = ...` computation (same block, after the branches). In no_ot, the load is after sc. Let me check the current order: 
```
cnt = cnt << 2;
sc = ((D_80126950 + 0x1F4) * 3) << 4;
sc = sc / cnt;
ot = load;
sx = L.sx0; sy = L.sy0;
```
If ot moves before `sc = ...`, it's still after the branches; block-local, but its position in the block changes the priority? Priority depends on birth/death UIDs and refs — moving it earlier extends its life (lower priority), so it might lose t0 to another local. Let me try: move the ot load to right after `cnt = cnt << 2;`.

Also try moving ot before the `if (cnt <= 0)` check (that was ot_early).

Alternatively, make ot live longer by using it in the loop: e.g., replace `otAddr = ot + cnt;` with `otAddr = ot + cnt;` (same) and AddPrim(otAddr,...). What if the source used `AddPrim(ot, prim)`? no.

Let me try the "move before sc" variant.
