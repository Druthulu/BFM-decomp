---
ts: 2026-11-06T06:36:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CXQebTE52GILPQGSGpCC
---
qty priority = floor_log2(n_refs)*n_refs*size / (death-birth).

The tag temp: n_refs 2 (load + and) — wait, the loaded value is used by `and`, so 2 refs? (set + use). live ~2-3.
oidx: n_refs 2 (set + 2 uses = 3?), live ~5.

pri_tag = 1*2/2 = 1; pri_oidx = 1*3/5 = 0.6. So the tag temp has higher priority → gets the first free reg.

Target: oidx gets v1 ($3) and tag gets a0 ($4). So in the target, oidx was allocated BEFORE the tag temp, meaning oidx had higher priority. Hmm.

Unless v0 ($2) is taken by something else in the target at that point. Hmm.

In the target, `lw a0,0(a3)` — the tag temp is a0 ($4) and oidx v1 ($3). Since qty allocation picks the first free register in the class order, and $2 (v0) is used by the `lw v0,0(at)` etc.

Hmm, local-alloc processes each basic block separately; the qtys in the tail block get registers based on priority.

Given the difficulty of tuning this, and that I already have a PARTIAL:pin at score 0, let me try just a couple of width/order tweaks on the *tag* expression: e.g. write the tag update using a temp variable:
```
s32 tag = *(u32 *)pkt & 0xFF000000;
*(u32 *)pkt = tag | (...);
```
That changes the RTL (an explicit temp might merge).

Or use a `u32` temp.

Let me try 3:
- t1: `s32 tg = *(u32*)pkt & 0xFF000000; *(u32*)pkt = tg | (...)` 
- t2: `s32 tg = *(u32*)pkt; *(u32*)pkt = (tg & 0xFF000000) | (...)`
- t3: oidx declared at the top with an initializer.

If none works, record PARTIAL:pin (b2.c) with best 0.

Actually, wait. Let me reconsider: maybe the simplest is to check whether `w2` as s16 is *needed* — v0 has 197 ins and score 13, while w0 had 192/68. So s16 w2 fixed the count. That means the pin removal needs s16 w2. Fine.

Now for oidx, maybe a similar width/type trick: `oidx` as `s16` was 68 (bad). Hmm, that was from w0 (w2 s32). Let me retest oidx widths on top of v0 (w2 s16).

Let me batch: oidx s16, oidx u32, oidx u8, tag temp variants.
