---
ts: 2026-11-06T17:39:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tLkTopIXvwn9SVhqXvRV
---
Time 14 min. All 7.

I need 6 more minutes for the WALL. Let me continue with more variants, maybe trying to directly attack the preference by changing the setters' source registers.

Idea: make the second setter's source a pseudo that local-alloc puts in v1 — then the preference includes v1 (already). To get v0, make the FIRST setter's source be a v0 pseudo: e.g., `sh16 = (s32)(u16)p[0x79] << 16;` in the THEN arm too (so both setters load p[0x79])? In the then arm, p[0x79] = angle was just stored; a reload would be an extra lhu. x1 (sh16 = p[0x79] << 16) — cse forwarded the angle value.

What if we prevent the CSE by using a different expression that forces a load? e.g., `sh16 = *(volatile u16 *)(p + 0x79) << 16;` — volatile load in the then arm (an extra load) → different bytes but maybe the allocation matches; the score would show.

Hmm.

Let me think about the preference again from the global.c code: `set_preference(dest=75, src)`. For the second setter, src=147. If reg_renumber[147] = 2 (v0), the preference includes v0. The dump says only v1 (3). So maybe reg_renumber[147] = 3 (v1) — the load temp is in v1, not v0! And for the first setter, src=77 with reg_renumber[77] = 3? But the dispositions said 77 in 4 (a0).

Hmm, the dispositions list "75 in 3 76 in 4 77 in 4" — wait, that's from the *nopin greg* dump: "72 in 16 73 in 18 74 in 17 75 in 3 76 in 4 77 in 4". So 77 in 4 (a0), 75 in 3 (v1).

The preference for 75 is 3 — from which setter? Maybe a setter I haven't considered: the RTL after sched1 might have a copy `(set 75 (reg X))` introduced by... no.

OR the preference comes from `hard_reg_preferences` being propagated through *allocno coalescing* (line 815: IOR between coalesced allocnos). If 75's allocno is coalesced with another allocno that has a v1 preference, 75 inherits it.

Coalescing happens for copies: if there's a copy between 75 and another pseudo... The store `(set (mem) (subreg (reg 75)))`? no.

Hmm, `(set (reg 75) (ashift (reg 77) 16))` — set_preference(75, 77) where 77's reg_renumber is 4 → preference 4. And `(set (reg 75) (ashift (reg 147) 16))` → preference 2 (if 147 is v0).

The dump says 3. So maybe the sched1 RTL differs from the flow dump: sched1 might have introduced a `(set (reg 75) (reg ...))` copy? Let me look at the sched dump again around 396/419 — I did, it's the same.

Wait, maybe the greg dump I read ("75 preferences: 3") is from a *different* function in the TU! The grep showed one "Function func_8015126C" at 67505; the line "75 preferences: 3" was in that section? I read lines 67505-67540 and saw "75 preferences: 3" at 67512-ish. Yes, it's our function.

Hmm, so the preference is v1. Where from? Perhaps `set_preference` is called with dest=75 and src = `(subreg (reg X))` for a *different* insn that sets 75 — maybe the prologue/epilogue? No.

Honestly, the mechanism doesn't matter for the outcome: the target needs v0 and lever-free we get v1.

Let me use the remaining minutes to try a few more shapes, then record.

One more idea: change the *type* of the shift operands to alter which insn pattern is used: `sh16 = angle << 16;` with angle s32 vs u32 (d1=7).

What about `sh16 = (s32)((u32)angle << 16);` (x2=7).

What if the shift is written as `angle * 0x10000` (d3=7)? gcc uses sll.

What if we use a *different multiplier* that's not a power of 2? wrong semantics.

I'll record the WALL after reaching 20 min. Let me run 3 more batches over the next 6 minutes.

Actually, let me try the "volatile reload" idea to change the setter's source register: in the then arm, force a fresh load of p[0x79] (which is angle). The load temp's reg might be v1/v0 → the preference changes. Even if it adds an instruction, if the allocation matches we'd see a lower score... but the extra instruction makes 255 ins vs 254 → not a match. Unless the reload replaces the angle use (the angle value would still be used for the store). So an extra insn. Not a match.

Let me instead try: in the then arm, `sh16 = p[0x79] << 16;` (x1) — cse forwarded. What if we make the store and the shift use different variables so no forwarding: `angle2 = func(...); p[0x79] = angle2; ... sh16 = angle << 16;` where angle is... no.

Time. Let me do a couple of "do-while block split" variants around the sh16 assignment (C0535 technique) — the block split might change local-alloc's qty grouping and the preference:

m1: `do { sh16 = angle << 16; } while (0);` in the then arm and similarly the else.
m2: `do { p[0x79] = ...; } while (0);` around the final store.

Let me test.
