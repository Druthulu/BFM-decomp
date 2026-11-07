---
ts: 2026-11-06T10:02:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_psgx2oAi4JdijNoz2Tko
---
Now I see. The relevant allocnos: r74 (4 refs, live 8, pri 10000, conflicts v0,a0,sp, blk 2) and r75 (2 refs, live 8, pri 2500, blk 2). Also r90 (v1, pri 5000, live 4) and r86 (v1, pri 4000, live 5), r85 (a0, pri 4000).

Hmm. r74 = t (4 refs, 8 insns). r75 = tb (2 refs, 8 insns). But the final: t is in v1, tb in v0. The table says r74 conflicts v0,a0,sp (so r74 cannot be v0!) and r75 → v0.

Why does r74 conflict with v0? "conflicts v0,a0,sp" — because r74 is live where v0 is live. Hmm. r74's live range spans 8 insns; v0 is used by neighboring allocnos (r80, r89, etc. all get v0). r74 lives across the `li a0,2274` and the sh etc.

Wait, actually maybe r74 is `t` and it conflicts v0 because some other pseudo is in v0 during its life. And r75 is tb.

But in the target, t is in v0 and tb in v1. So in the target, t (with the pin) doesn't conflict with v0? Hmm, but the target's t IS v0. So the conflict is a property of the lever-free body's structure, not fixed.

The "conflicts v0" for r74 means at some point r74 is live while v0 is occupied by another allocno. If we reduce that overlap, r74 could take v0.

The candidates that occupy v0: r80, r89, r91(a0), r92, r93, r94, r95, r97, r101, r79, r87, r88... many are block-local or global.

Actually this is global-alloc, so conflicts are computed over the whole function's live ranges. r74 (t) lives 8 insns in block 2; during that window, v0 is used by e.g. r92 (pointer, blk2) etc.

The lever-free body has extra v0 users in that window that the pinned body doesn't? No — the pinned body has the same C except pins.

Hold on. With the pin on tb ($3=v1), tb was forced to v1, so r75 was a hard reg. t then took v0. In the lever-free body, tb is a normal allocno (r75) and it conflicts... The conflict graph differs because tb no longer hard-pinned.

Key: r74 (t) conflicts v0. So something else in v0 overlaps t. What is in v0 during t's life? Let me find: in the final code, during insns 52-59, v0 is used at 53 (lw tb) — but tb is r75 which got v0. Wait, the conflict is between r74 and v0, meaning some allocno assigned v0 overlaps r74's live range. If r75 (tb) is assigned v0 and r75's life overlaps r74's life (they overlap: t lives 52-59, tb 53-58), then indeed r74 conflicts with whoever gets v0 = r75. Circular! The conflict graph is: r74 and r75 conflict with each other (both live simultaneously). Whichever gets v0, the other gets v1.

So the conflict is mutual; the assignment order decides. r74 pri 10000 > r75 pri 2500, so r74 should be allocated first and get... the first free reg. But "conflicts v0,a0,sp" for r74 means even before assignment, r74's conflict set includes v0 due to OTHER allocnos, not r75.

Hmm, but the table's "conflicts" column is from the .greg dump: it lists hard registers that are "live" during the allocno's range because some other allocno has a copy preference or is hard? Actually global-alloc's conflict computation: a hard reg conflicts if it's live at the allocno's start. The listed "conflicts v0,a0,sp" means at r74's start, v0, a0, sp are live (hard regs used by other pseudos). 

So r74 can't be v0 because v0 is live at r74's birth. Which pseudo holds v0 at r74's birth (insn 52)? Looking at the code, at insn 52 v0 was just used at 51 (`sh v0,26(a2)`). Hmm, after that v0 is free. But the allocno r79/r80 etc. might be assigned v0 and live across.

This is getting deep. Let me take the practical route: find a C change that removes the v0 conflict at t's birth. E.g., if the value loaded at insn 51 (sh v0,26(a2)) is a separate allocno that dies, but global-alloc thinks v0 is live into 52 because some allocno that got v0 extends.

Alternatively, target's t in v0 means in the target the conflict didn't exist. The target has the pin on tb, so tb isn't competing. But the conflict "v0 at t's birth" comes from another allocno.

Let me look at which allocnos are in v0 around there. From the table: r92, r93, r94, r95 (blk 2, pri 10000, live 2) — these are the short block-local loads in block 2. And r79 (blk 0, live 3), r87/r88 (blk 2, live 3, pri 6666).

Hmm. Actually, maybe I should look at this from a different angle: what real-C move reduces t's live range or removes the overlap?

t (r74) lives 8 insns: from `lw t,76(s0)` (52) to `addiu v0,t,-8` (59). tb lives 53-58.

If I make t's life NOT overlap v0's... 

Honestly, given the budget (20-30 min), let me try a few more variants quickly:

V4: reorder: put the unk54 block AFTER the unk50 block. Source:
```
t = s0->unk4C; s0->unk6 = t;
t = s0->unk50; s0->unkA = t - 8;
tb = s0->unk54; s0->unkE = tb;
```
But that changes code order vs target. Target order: unk4C store, unk54 store, unk50. So no.

V5: Use `u16` temporaries:
```
u16 t; u16 tb;
```
Then the load is lhu? Target uses lw for these (lw v0,76). The struct field unk4C is likely s32; assigning to u16 would produce lw + sh (store) but the temp would be HImode... Actually `t = s0->unk4C` with t u16 → lhu? or lw then sh. Hmm.

V6: Declare t and tb at the top (already). Change declaration order.

Let me look at what "conflicts v0" means more concretely by comparing with the target (orig with pins) allocation table. Let me dump orig and run alloc_table. That will show t's conflict set in the matching body. If in the matching body r74 doesn't conflict v0, then I know the conflict is caused by lever removal.

Let me do that: splice orig.c, dump, alloc_table.
