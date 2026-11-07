---
ts: 2026-11-06T08:07:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WiEANNtDCNxljmiS4uJV
---
v10: 
```
lhu a0,96(s0)   ; v
lhu v0,10(s0)   ; t
addiu v1,a0,1   ; v+1
addiu v0,v0,-16 ; t-16
andi a0,a0,0x1f ; m
sh v0,10(s0)    ; unkA
lw v0,80(s0)    ; unk50
sll s1,a0,0x7   ; ang
bnez v0
sh v1,96(s0)    ; unk60
```
Target:
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
Very close! Differences:
- register names: v is a0 in mine vs v0 in target; t is v0 vs v1; unk50 is v0 vs v1.
- order: mine computes v+1 before m/ang and stores unk60 in the delay slot; target computes m/ang before t-16, and v+1 after lw unk50.

So the target keeps v in v0, t in v1. Mine has v in a0, t in v0. The register choice: target v0/v1; mine a0/v0. Why? In v10, the first load (v) is into a0 because... local-alloc assigns. The target's v in v0.

The target's m is in a0. Mine's m is in a0 too (andi a0,a0). 

So the difference is the load temps: target uses v0/v1 for the loads, a0 for m; mine uses a0/v0 for the loads, a0 for m (m reuses v's reg after andi). 

The target's `andi a0,v0,0x1f` computes m into a0 from v0. Mine's `andi a0,a0,0x1f` from a0 (v). Both a0 for m.

The load register assignment (v0 vs a0) is local-alloc's choice. Hmm.

This is a local-alloc qty priority/order issue. The keepalive affects it.

Let me try combining the swapped stores (v10) with other moves to fix the order:
- v10 + do-while around m/ang.
- v10 + name v+1.
- v10 + reorder t load before v? (v10 has v first already).
- v10 + compute m before v+1.

Let me also try: store order swap + move the `v+1` computation later (after the branch). The target computes v+1 after lw unk50. In source, `obj->unk60 = v + 1;` is before the if. sched1 could sink v+1 to the delay slot. In v10 it did (sh v1,96 in delay). In target, `addiu v0,v0,1` is before bnez and `sh v0,96(s0)` in the delay slot. So target computes v+1 before bnez; mine computes it early (insn 17). Both before bnez; the difference is the position.

Let me try v10 + do-while around m/ang to force them early:
```
obj->unk60 = v + 1;
obj->unkA = t - 0x10;
do { m = v & 0x1F; ang = ...; } while (0);
```
No, m/ang are before the stores in source. The do-while around them after the stores? Let me generate combos:
- w1 + swap stores + do-while m/ang (in source order: m/ang before stores, so the do-while is before).
- w1 + swap stores + compute m/ang after the stores (source order changed) — but target computes m/ang before t-16.

Hmm. Let me look at the exact target order relative to source:
Source: v load, m, ang, t load, unkA store, unk60 store, if.
Target: v load, t load, m, ang, t-16, unkA store, unk50 load, v+1, bnez, unk60 store.
So target interleaves: the t load moved up before m/ang; m/ang moved after the t load; t-16 after ang; v+1 after the unk50 load.

The natural C likely has this order already: maybe the source is:
```
v = obj->unk60;
t = obj->unkA;
m = v & 0x1F;
ang = ...;
obj->unkA = t - 0x10;
obj->unk60 = v + 1;
```
i.e., t loaded BEFORE m/ang! Let me check: v3_tfirst moved t before v, not v,t,m. Let me try: v load, t load, m, ang (t load before m/ang). That's v25? v25 was "store_then_m": v, t, m, ang — yes! v25_store_then_m:
```
v = obj->unk60;
t = obj->unkA;
m = v & 0x1F;
ang = ...;
```
Score 17. Hmm, but let me check its listing — maybe the loads got reordered again.

Actually v25 changed BODY to v, t, m, ang. Score 17, 69 ins. Not better.

Let me try v25 + swap stores. And other combos. Let me generate.
