---
ts: 2026-11-06T06:35:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vpl3Q9jU3xuMaG4xm3wk
---
Clean: v0 and v1 are swapped throughout the middle section. The target keeps the working value in $2 (v0) and mine in $3 (v1).

This is the classic $2 pin: the pinned `t` was in $2 for the whole function. Lever-free, local-alloc gives $2 to some other temp.

Let me look at the whole function's structure:
```c
    if (unkFC != 0) {
        unkFC = unkFC - 1;
        *(u32*)(unk20+4) ^= 0x80000000;
    }
    t = unkA;
    t -= 0x30;
    if ((*(s16*)&D_80126B62) < t) {
        t = (s32)D_801D094C;
    } else {
        t = (s32)D_801D093C;
    }
    t |= 0x40000000;
    t |= 0x20000000;
    unk58 = t;
    t = unk2;
    launder
    D_801D0A3C[t](a0);
```

In the target, the middle block uses v0 for the working value (t). Mine uses v1.

The "register pairs (mine -> target): v1->v0 x17, v0->v1 x10" — a full swap of v0/v1 in the middle.

This is a local-alloc ordering: which local temp gets $2 first. Known walls: "lreg-v0-local-first" (local-alloc gives block-local cmp temps v0 before the global ret is allocated), "lreg-qty-priority".

Let me get the alloc table for the target and mine. But first, let me try a couple of quick plain-C moves:
1. Split the reused `t` into separate variables per use (moves: "split reused v0 into own var").
2. Make `t` s16/u16 for the unkA read.

The target's `t` is one variable reused (per the source). The pin made it $2.

Hmm — the target's registers: which pseudo is in v0? Since t is a hard reg $2 in the target, t is always v0. In mine, t is a normal pseudo → local-alloc assigns per block.

Key: t is live across the whole function? No — t is reassigned: `t = unkA; ...; t |= ...; unk58 = t;` then `t = unk2; call`. So t has 2 disjoint live ranges. Local-alloc can put each in a different reg (local-alloc works per basic block, but t is global — used in several blocks — so global-alloc handles it).

Since t is global (live across blocks), global-alloc gives it a register: in mine, $3 (v1); target $2.

The difference must be priority: some other allocno takes $2 first.

Let me look at the alloc table for my candidate. Let me dump.

Actually, first let me try quick variants:
- Make the two `t` uses different variables (t and t2): then each is block-local and local-alloc gives $2 to the first... Hmm, the target has ONE t in $2 for both.
- Since `t` is global, its priority = floor_log2(refs)*refs/live.

Let me dump and see the numbers. It's fast.
