---
ts: 2026-11-06T12:30:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EpGIAhUqyTlHlAxd1D10
---
The keepalive at 201 uses `my` to extend its live range (+7 insns, +3 weighted refs) so that mny's priority (22115) beats my's (22072) and mny gets $a2.

Real-C equivalent: extend my's live range by a real use later — but a real use costs an instruction.

Hmm, unless the use can be folded. E.g. `my` is used at line 186/188. If we move a use of `my` later... 

What if the *statement order* is changed so that `my`'s live range naturally extends (e.g. compute my's value earlier and use it later)? That's real C: e.g. hoist `my = ...` — no.

Actually here's a thought: the keepalive makes my live to line 201. If instead we moved a real use of `my` past line 201 — but the next use of my is at line 252 (`my = tmpxy[0].vy;` — a redefinition). So no use exists after 201.

Real C can't extend a live range without an instruction. This is exactly `global-pri-bank-order` / `greg-ref-count` territory.

I'll WALL item 3. Need 30 tries. I've done: v0, d201, d202, d223, d291 = 5. Need 25 more.

Let me generate 25 cheap variants:
- declaration reorders (my/mny/mx/mn order): 3
- statement reorders in the 180-190 region: 5
- statement reorders in the 250-270 region: 5
- box fill order variations: 4
- combos with d202 (barrier removed) to see if any reduces below 71: 8

Actually for a WALL, best = the lowest lever-free score. Let me include variants that might reduce the total.

Let me write a generator with 25 variants quickly. Keep it simple: mostly permutations of small statement groups and declaration orders.

Region 60-74: the box fill. Region 180-190: my/mny. Region 250-270: same for the second copy.

Let me look at lines 60-80 and 240-300 to design variants.
