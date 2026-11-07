---
ts: 2026-11-06T16:47:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_p2SSw8yuOSjyYD2ieNyq
---
PSEUDO_REGNO_SIZE for HImode = (2+3)/4 = 1; for SImode = (4+3)/4 = 1. Same. So the size doesn't change with HImode. The priority is the same.

So s16 h wouldn't change the priority (unless n_refs/life change). Hmm.

Let me think differently: the priority difference is h (nrefs 3, life 2) vs t (nrefs 2, life 4). To flip, I need t's priority > h's.

t's pri = 1*2*1/4 = 0.5 → 5000 (if size 1!). Wait, I used size 4 before. With size 1: t = floor_log2(2)*2*1/4 = 1*2/4 = 0.5 → 5000. h = floor_log2(3)*3*1/2 = 1*3/2 = 1.5 → 15000. So h > t.

To flip: increase t's refs or shorten its life; decrease h's refs or lengthen its life.

- t's life: from the sll to the addu. If I move the `t = s0 << 1;` statement LATER (closer to its use), t's life shortens → priority rises. But the target's instruction order has the sll early (at 2734). sched1 might reorder anyway. Let me try moving the t computation after the h load:
```c
a = s0 << 9;
h = *(s16 *)((u8 *)s1 + 0x70);
t = s0 << 1;
s0 = s0 + 1;
func(...t...);
```
The target order is sll a0; sll v0; lh v1; addiu s0. If I reorder the source to a, h, t, s0, sched1 may reorder to the target order (sll t before lh) if it helps. Hmm.

- Alternatively lengthen h's life: h is used at the sll and addu. If h's last use were later... it isn't.

- Increase t's refs: t is used once (in the addu). If t were used twice, refs 3 and life same → pri = 1*3*1/4 = 7500, still < 15000.

- Decrease h's refs: h's uses are the sll and the addu. If the C uses h once (e.g., compute `h << 4` inline in one expression), the tree would still have 2 uses of the register (the sll and the addu). Hmm, unless the expression is `((*(s16*)(...)) << 4) + s2` computed inline without a variable — then the loaded value is used once (in the sll). Let's see the RTL: `h = lh; sll h,h,4; addu h,h,s2; addu t,t,h`. If h is inlined as a temp used once, the qty would have nrefs 2 (def + sll use) and life shorter (def to sll). pri = 1*2*1/2 = 1 → 10000. Still > t's 5000. Hmm, but the life would be shorter: def at insn i, use at i+1 → life 1 → pri = 1*2*1/1 = 2 → 20000. Worse (higher).

Hmm wait, I have the direction wrong? Higher priority gets allocated first, and the first allocated gets $2 (v0). Mine: h gets $2 (v0) — wait no! Mine: h=v0 ($2) and t=v1 ($3). Yes, h (higher pri) got $2. Target wants h=$3, so t must be allocated first (get $2), and h gets $3.

So I need t's priority > h's.

t pri 5000; h pri 15000. Need to raise t or lower h.

Lower h: longer life or fewer refs. 
- If h's def is earlier and use later (longer life): e.g., load h BEFORE `t = s0 << 1` and `a = s0 << 9`. Source order: `h = lh; a = s0 << 9; t = s0 << 1; ...`. Then h's life spans more insns → pri drops. Target order: sll a0; sll v0; lh v1 — sched1 would need to move the lh after the two slls. That's plausible (sched1 reorders). But the birth order affects the qty numbering/priority: with h born first, its qty number is lower; priority by pri first.

Actually, the priority is computed from the RTL AFTER sched1? No! Order of passes: flow, combine, sched1, local-alloc, ... So local-alloc runs after sched1, on the sched1-reordered RTL. So the RTL order at local-alloc time is the sched1 order. If sched1 orders the target's insn order (sll a, sll t, lh h), then h's birth is after t's. Hmm.

So the live ranges at local-alloc time are what matter. In the current build, sched1 already produces the target order? Mine's diff shows `sll v1,s0,0x1; lh v0,112(s1)` — same order as target (t then h). So the RTL order is the same; only the allocation differs.

So priorities: h higher. To flip without changing the RTL order, I need the *refs/life* to change. Hmm.

Wait, let me recompute nrefs. reg_n_refs counts the number of references (defs + uses). Let me actually look at the lreg dump for this function to get the exact numbers. Let me dump the plain body.

Let me use --keep and dump.

Actually, faster: let me check the register stats from the lreg dump. Let me do the keep+dump.
