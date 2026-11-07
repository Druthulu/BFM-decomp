---
ts: 2026-11-06T08:04:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QHmjdZ4U1IL8NTZJjhPO
---
Score 17, 69 ins vs 68. The lever-free body computes things in a different order/with an extra instruction. The target has `lhu v0,96(s0)` first (obj->unk60 at 96?) then `lhu v1,10(s0)` (obj->unkA at 10). Mine loads unkA (10) first, then unk60 (96). Source order: `v = obj->unk60; m = v & 0x1F; ang = ...; t = obj->unkA;`. So unk60 load is before unkA. Target: unk60 (96) first, then unkA (10). Mine: unkA (10) first then unk60 (96) — sched1 reordered. Hmm, mine[15] is `lhu v0,10(s0)` and mine[16] `lhu v1,96(s0)`. So mine loads unkA first (reordered).

The target:
```
lhu v0,96(s0)     ; v = unk60
lhu v1,10(s0)     ; t = unkA
andi a0,v0,0x1f   ; m = v & 0x1F
sll s1,a0,0x7     ; m << 7
addiu v1,v1,-16   ; t - 0x10
sh v1,10(s0)      ; unkA = t - 0x10
lw v1,80(s0)      ; obj->unk50
addiu v0,v0,1     ; v + 1
bnez v1,...       ; if unk50
sh v0,96(s0)      ; unk60 = v+1 (delay slot)
```
Mine:
```
lhu v0,10(s0)     ; t
lhu v1,96(s0)     ; v
addiu v0,v0,-16   ; t-0x10
sh v0,10(s0)      ; unkA
addiu v0,v1,1     ; v+1
andi v1,v1,0x1f   ; m
...
lw v0,80(s0)      ; unk50
bnez v0
sll s1,v1,0x7
...
```
So mine reordered the unkA store before the m computation, and the branch. The keepalive forces m and ang to be computed (live) before the stores, which matches the target's order.

Real-C fix: ensure m and ang are computed before the stores. They ARE computed in source before (m, ang assignments precede t=unkA and the stores). But sched1 reorders. The keepalive adds uses that pin the order.

To reproduce naturally, maybe the original computes m and ang and uses them in the stores? Or the original has the stores after the if? Let me think about the natural C: the target computes m before the unkA store and keeps m in a0 (register pairs v1->a0 x2). The keepalive forces m and ang live.

What real C keeps m and ang live across the stores? Their uses are in the if/else after the stores. So they ARE live across the stores naturally! The compiler should keep them. But the register allocator/scheduler reordered the stores.

Hmm, mine recomputes? Let me see the full mine. Actually mine computes m into v1 after the stores, using v (still in v1). It deferred the m computation (andi) until after the store, recomputing from v. That's sched1 sinking the `andi` to its use. The target computes m early (andi a0,v0,0x1f) because the keepalive required m in a register at that point.

So the natural C must use m earlier or force its computation. What real C uses m before the stores? In the source, `m` is used only in `func_80047948(m << 7)`. Hmm.

Maybe the original source computes `m << 7` earlier:
```
s32 m = v & 0x1F;
s32 r;
...
r = func_80047948(m << 7);
```
No.

What if the original uses `m` in the `ang` computation? `ang = ((m << 8) & 0x7F00) >> 1;` uses m. So m is used to compute ang, which is before the stores. The compiler could compute m, then ang, then keep both. The target does exactly that: `andi a0,v0,0x1f; sll s1,a0,0x7` — wait, `sll s1,a0,0x7` is m<<7 computed early (s1)! Then ang? Let me see the full target around there. The target has `sll s1,a0,0x7` right after the andi — so the target computes `m << 7` early (into s1) and keeps it. That's the argument for func_80047948. And ang is computed too.

So the natural C likely has `m << 7` as a separate expression used later, and the compiler hoists it. The source has `func_80047948(m << 7)` in the if/else (twice!). The `m << 7` is used in both branches (same value). The compiler computes it once early (s1) because... in mine it computes it late (sll s1,v1,0x7 after the branch).

Wait, target: `sll s1,a0,0x7` at insn 18 (before the stores and the branch). Mine: `sll s1,v1,0x7` at insn 25 (after the branch). So the target hoists `m<<7` early; mine sinks it. The keepalive forces m live, which lets sched1 hoist the sll.

Real C: if the source names `m << 7` as a variable:
```
s32 m7 = m << 7;
...
r = func_80047948(m7);
else r = 0x1000 - func_80047948(m7);
```
Then m7 is a variable used in both branches; the compiler would compute it early (at its definition). That's a real-C move ("temps"). Let me try. Similarly, `ang` might be computed early; `func_8004787C(ang)` is used later. Target keeps ang? Let me see the target's register pairs: v1->a0 x2. Let me look at the full target dump to map.

Let me dump the target.
