---
ts: 2026-11-06T08:06:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2lIl5LNbbwZJNog043Je
---
v10 (swap stores) gets 68 ins but the order of the loads/computation differs. Not close enough.

Let me think about the real-C mechanism. The target computes m and ang early because the keepalive forces it. Without the keepalive, sched1 sinks them. To force them early naturally, the source must use m/ang before the stores in a way that emits code or is ordered.

Idea: what if the original stores `m` or `ang` somewhere? No.

Idea: the original's `v` is not a local; maybe `m` is computed from `obj->unk60` directly at each use:
```
m = obj->unk60 & 0x1F;
ang = ...;
...
```
If `m` is loaded via `obj->unk60 & 0x1F` and `v` separately, the compiler might compute m early. But the target loads unk60 once (lhu v0,96) and uses v0 for both m and v+1.

Idea: maybe the original computed `v + 1` and stored it, and `m` from v; the order in source: `v = obj->unk60; ... obj->unk60 = v + 1;` — the store of v+1 uses v, so v must be live. m uses v too. If the source computed `m` AFTER the store (i.e., `obj->unk60 = v + 1; m = v & 0x1F;`) then... no, target computes m before the store.

Hmm, wait: the target computes m and ang BEFORE the stores. The source computes m and ang before the stores too. The scheduler sinks them. What if the source's stores are in a different order such that the sink is blocked? v10 swapped the stores, which changed things.

Let me look at the target's exact order again:
```
lhu v0,96(s0)   ; v
lhu v1,10(s0)   ; t
andi a0,v0,0x1f ; m
sll s1,a0,0x7   ; ang
addiu v1,v1,-16 ; t-16
sh v1,10(s0)    ; unkA
lw v1,80(s0)    ; unk50
addiu v0,v0,1   ; v+1
bnez v1
sh v0,96(s0)    ; unk60
```
So m/ang computed between the two loads and the store.

Mine:
```
lhu v0,10(s0)   ; t (first!)
lhu v1,96(s0)   ; v
addiu v0,v0,-16
sh v0,10(s0)
addiu v0,v1,1
andi v1,v1,0x1f
sh v0,96(s0)
lw v0,80(s0)
bnez v0
sll s1,v1,0x7
```
The load order is reversed too (t before v). sched1 ordered the two independent loads by priority: in target, v first; mine, t first.

The keepalive forces m/ang (which depend on v) to be computed early, which in turn forces the v load early (before t). Without it, the t load (which dies early into the store) is scheduled first.

Real-C: what makes the v load and m computation higher priority? If m is used earlier... 

Idea: use `m` in the `ang` expression AND use ang before the stores. Ang's use is after. Hmm.

Idea: the original might compute the GTE/other stuff between? No.

Let me try: compute `r` or the call arguments earlier? No.

Let me try the C0535 do-while around the m/ang computation + stores (v6 gave 10). Let me try different block placements:
- do-while around the m/ang computation only.
- do-while around the two loads + m/ang.
- do-while around the stores.

Also, maybe the answer is a statement reorder: move `t = obj->unkA;` AFTER the m/ang computation but before the stores (it already is). Move the stores before `t = ...`? Then t's load is later.

Let me try:
- v11: `t = obj->unkA;` moved after `m`/`ang` (already) but also after the stores? No.
- v12: compute `v+1` into a temp `vv = v + 1;` before m.
- v13: compute `t-0x10` into a temp.
- v14: do-while around m/ang.

Let me generate more.
