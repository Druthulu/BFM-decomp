---
ts: 2026-11-06T12:05:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n0pmqmoDbxU6bg05t2sl
---
k3's residual: 
1. `lui s2,0x0; addiu s2,s2,0` (D_800CB820 address) is materialized early in mine (insns 4-5) vs target later (25-26). Plus `move s3,zero` (i=0) early in mine vs target at 27.
2. `sb v1,85(sp)` (f.col[1].b = 0x70? no, cv store) and the jal order swapped.

So mine hoists the D_800CB820 address and i=0 to the top; target keeps them at their source position (after the corner stores).

Real C: the p = D_800CB820 statement is after the launder block in source; mine hoists it because sched1 sees it as independent (no barrier). The barrier was the fence.

Can real C prevent that? Make `p = D_800CB820` depend on something? Hmm, `p` is used in the do-loop later.

What if p is assigned inside the do-loop's first use? E.g. `p = D_800CB820;` moved just before the loop (it already is). The scheduler hoists it.

Hmm, but note: target has the address materialization at 25-27, i.e., after the call! Let me see: target 25-27 = lui s2; addiu s2; move s3,zero. And the call is at 648 (after). Hmm, the diff indices are confusing.

Let me try reordering: move `p = D_800CB820;` and `i = 0;` later (after the func_80149350 call) — semantically fine? p and i are only used in the do-loop after the call. Yes! Let me test moving them after the call and the c stores.

Actually in the source:
```
    p = D_800CB820;
    i = 0;
    f.col[0].b = 0; ... f.code = 0x50000000; f.cz = arg3; f.col[1].r = cv; f.col[1].g = cv;
    func_80149350(node, va, vb);
    c = f.cx; ... 
```
So p/i are assigned before the col stores. Moving them after the call might match the target better.

Let me try k11: p/i after the call. Also k12: p after the call, i before.

Also the second cluster: `sb v1,85(sp)` before/after the jal — that's the f.col[1].g = cv store vs the call. Target: sb at 37 then jal at 38? The diff says target has sb v1,85 then jal; mine has jal then sb. Since f.col[1].g is set before the call in source, target emits sb before jal. Mine schedules the sb into the jal delay slot. Hmm.

Let me test the p/i move.
