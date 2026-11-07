---
ts: 2026-11-06T04:22:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vL0shuViUYioyfmieKLz
---
Key: "When all instructions have a latency of 1, there is no need to move any instructions... all instructions will end up with a priority of one, and hence no scheduling will be done." So sched1 only reorders when priorities differ. In mine, the p load was moved above the multiply, so its priority must exceed the sll's. The p load (lw) has a load latency (MIPS load delay = 1?), while the sll/addu have latency 1. The p load's use is the addiu/sh. Hmm.

Actually the move we see (p load hoisted above the sll chain) is exactly what sched1 does to fill the load delay: the p load takes 1-2 cycles; scheduling it early hides the latency. The target does NOT hoist it, meaning in the target the p load's priority was lower or the scheduler chose otherwise.

The comment says priorities are 1 for latency-1 insns; the load has a higher "cost" so it gets moved. In target, the p load is after the chain, so sched1 did NOT move it — perhaps because in the target's RTL, the p load was in a different basic block or had a dependency.

Hmm wait — maybe the target's p load has a dependency on the multiply because the ORIGINAL C's store address computation reused a register? No.

Or maybe the original C's `<0x11` arm computed the store as `((Unk*)p)->unk18 = v` where p was assigned BEFORE the multiply in source, and the reload... no.

Let me look at the fence comments again: "the first keeps the whole obj->0x1C multiply above `p`'s load (it must not overlap the obj->0x1C pseudo, which also wants $v1), the second keeps the `+ 0x600` below it -- target order is sll / lw / addiu."

So the fence after the multiply keeps the multiply above p's load. And the fence after p's load keeps +0x600 below p's load. The second fence is between p's load and the add. In the target, order is sll/lw/addiu.

Without fences, sched1 hoists the p load above the sll. To keep the multiply above the p load, we need a dependency: the multiply's result feeds... nothing related to p. Hmm.

BUT: maybe the original C had the multiply computed into a variable that is ALSO used as the store address? No.

Alternatively, maybe the original had the store as `((Unk*)p)->unk18 = v` where p was loaded BEFORE the multiply, and the target's p load is a *reload* caused by the earlier sh. The target's order: the raw 0x1A store loads model (4924), stores (492c), then obj->1C load (4930), chain (4938-4940), then p reload (4944). The p reload is naturally after the chain because it's born after the chain in the RTL. sched1 in the target didn't hoist it. Why? Maybe because the p reload's priority is 1 and the chain's is higher.

In mine, sched1 hoisted it. The difference could be the RTL order of the obj->1C load vs the p load: in target, obj->1C load is before the p load; in mine too.

Hmm, let me try to make the p load's priority LOWER by making its use closer? No, closer = higher priority.

What if I make the p load depend on the multiply result through a real computation that folds away at the RTL level? E.g., `p = (Unk*)((s32)((Unk*)a0)->unk20);` no.

What if the store's address uses v? Like `((Unk*)p)->unk18 = v;` — no.

OK, alternative: maybe reproduce the target by using a different variable for the model pointer in the `<0x11` arm so that the reload isn't cse-forced but naturally placed. E.g., load `p` BEFORE the 0x1A store (so it's forwarded? no, the store kills it). Hmm.

Wait, actually: what if the `<0x11` arm's 0x1A store is written with the p variable rather than the raw expression? Source:
```
p = ((Unk*)a0)->unk20;
((Unk*)p)->unk1A = 0xC00;
v = multiply;
p = ((Unk*)a0)->unk20;   // reload
v = v + 0x600;
```
That's the same but with p loaded before the store. The first p load would be used by the store; then the reload. Same as target (which loads model for the store via the raw expression). The raw expression and p are the same.

Hmm.

Let me consider that maybe the target's schedule is influenced by `p` being loaded with the SAME pseudo as the first model load. If p is one variable assigned twice (p = model; store; p = model;), the two loads write the same pseudo. Then the second load's dest is the same reg as the first, and the live ranges are short. cse can't forward (the store kills). sched1: the second load writes p, which is also the register... The target's p is v1 for both. In mine, the first model load (raw) goes to v1 (4920 lw v1), and the reload goes to a0. If they were the same C variable p, they'd be the same pseudo → same register v1! That would fix the register difference and possibly the schedule (the pseudo's live range).

Let me rewrite the `<0x11` arm:
```
p = ((Unkstruct_800B5CB8 *)a0)->unk20;
((Unkstruct_800B5CB8 *)p)->unk1A = 0xC00;
v = *(s32 *)(obj + 0x1C) * 3 * 32;
p = ((Unkstruct_800B5CB8 *)a0)->unk20;
v = v + 0x600;
```
Now p is assigned twice. The second assignment reloads. cse: after the store, the model load entry is invalidated, so the second `p = ...` is a real load. The two loads share the pseudo p. This is a real "pointer reuse" move.

Let me test (u1). Also, the same could apply to the `==0` arm (line 49-50: raw store then p load) — rewrite with p:
```
p = ((Unk*)a0)->unk20;
((Unk*)p)->unk1A = 0x600;
p = ((Unk*)a0)->unk20;
v = 0x1200;
```
Hmm, but in the `==0` arm target: 48e8 lw v1,32(s1); li v0,1536; sh v0,26(v1); 48f4 lw v1,32(s1); j; li v0,4608. Both loads into v1. Yes! Same pseudo → same reg. Let me apply the same to both arms.

Let me build u1 from nopin (not w4) with these rewrites, keeping the do-while? Let me first try without do-while but with pointer reuse.

Actually, the `==0` arm's improvement came from the do-while. With pointer reuse, maybe the do-while isn't needed. Let me build u1 = nopin with:
- `==0` arm: p = model; ((Unk*)p)->unk1A = 0x600; p = model; v = 0x1200;
- `<0x11` arm: p = model; ((Unk*)p)->unk1A = 0xC00; v = mult; p = model; v += 0x600;

Let me write it from nopin.c. Let me view nopin lines 44-60 again (I have them). I'll construct with awk carefully.

nopin.c:
44:        } else if (*(s32 *)(obj + 0x1C) == 0) {
45-48 comments
49:            ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk1A = 0x600;
50:            p = ((Unkstruct_800B5CB8 *)a0)->unk20;
51:            v = 0x1200;
52:        } else if (*(s32 *)(obj + 0x1C) < 0x11) {
53:            ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk1A = 0xC00;
54-56 comments
57:            v = *(s32 *)(obj + 0x1C) * 3 * 32;
58:            p = ((Unkstruct_800B5CB8 *)a0)->unk20;
59:            v = v + 0x600;

Rewrite:
49 -> p = model; ((Unk*)p)->unk1A = 0x600;
50 -> p = model;
53 -> p = model; ((Unk*)p)->unk1A = 0xC00;
58 -> p = model;

So essentially insert `p = model;` before each raw store, and keep the existing p assignment after. That gives p two defs.

Let me do: at NR==49 print "            p = ((Unkstruct_800B5CB8 *)a0)->unk20;" then the modified store using p; at NR==53 similar.

I'll generate with awk.
