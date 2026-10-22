---
ts: 2026-10-21T23:38:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_aRn1dGJqZObUuK9H1npa
---
Excellent, very informative. The unpinned version:
- `li v0,-160` at 73 (v0 = $2) with `sh v0,20(s0)`, `sh v0,36(s0)` — so c1 got $2 (v0) and the other constants got... let's see: `lw v1,28(s1)` at 62 vs target `lw a2,28(s1)`, and `sb v1,42(s0)` vs `sb a2,42(s0)`. So the byte value register is v1 in mine, a2 in target.

Wait, the target at 271c has `lw a2,28(s1)` and `sb a2,42(s0)` — so the last byte load (unk1C) is in a2 ($6) in the target. Hmm, in the target all 12 byte loads use v0 except the last one which uses a2. Interesting — because at 271c the load of v0 was already used and a2 is free.

Hmm, actually in the target: `lw v0,28(s1)` repeated 11 times with `sb v0,...`, then the 12th `lw a2,28(s1)` + `sb a2,42(s0)`. And a2 is also used for the call `func_8005A600`? No — a2 was set to zero for that call. So after the call, a2 is free and gets reused for the last byte load.

So target allocation: v0 ($2) used for the byte loads and for constants 0xA0/-0x78/0x78, v1 ($3) for c1=-160, a2 ($6) for the last byte load.

Mine (unpinned): v0 for c1 (-160), v1 for the byte loads, and the "li v1,-160" line missing at position 60 — mine has `addiu a1,s0,12` where target has `li v1,-160`, meaning in mine the -160 load happened earlier (at 73?) no wait, mine has `li v0,-160` at 73, later. The diff is a bit confusing due to alignment. Key differences:
1. mine has an extra instruction (91 vs 90).
2. The -160 constant is in v0 instead of v1, and scheduled later (li at 73 vs 60).
3. Byte loads in v1 instead of v0 (a2 for last).

The "extra instruction": maybe a nop padding? The `replace mine[54:55] target[54:55]  54 nop | move a0,s2` suggests nop padding in mine vs target having move a0,s2 in a different position (scheduling difference). Total 91 vs 90: one extra nop? Actually MIPS with .set reorder fills delay slots.

Strategy: I need c1 = -0xA0 to be allocated $3 and the byte value in $2.

Key insight: in the target, the byte loads are all in v0 and the -160 constant in v1. In the unpinned version, GCC's local-alloc gave v0 to c1 and v1 to the byte. Why? Because c1's live range... hmm.

Ideas to force $3 for c1 without a pin:
- Make c1's live range longer (live from early to late) so it gets a lower-priority register... Actually in GCC's local-alloc, the pseudo with higher priority gets the better (lower-numbered) register. Priority is computed by "allocno priority" which includes number of refs, live range length, etc. The byte value has 12 sets + 12 uses = 24 refs, so it should win $2 over c1 (3 refs). But in mine, the byte got v1 and c1 got v0! That's the opposite. Hmm, because the byte loads are separate pseudos (each `sb` reloads), and each is a separate pseudo with 1 set + 1 use (2 refs). Then c1 (1 set + 2 uses) wins.

Hmm interesting. So in the target, each byte load pseudo gets v0 (the first color) and c1 gets v1 (second color). In mine, c1 got v0 and the byte pseudos got v1? That doesn't match "priority" logic... unless the colors are assigned in order of allocation: local-alloc processes the pseudos in some order and assigns colors to live-range-overlapping sets.

Actually the local-alloc algorithm: it processes allocnos in order of decreasing priority, and for each, tries to find a reg not conflicting. The "conflict" is determined by live range overlap. If c1's live range overlaps the byte pseudos' ranges, they need different regs. The order matters.

In mine, c1's live range (from `c1 = -0xA0` at position 36 to the two sh stores) — hmm the assignment `c1 = -0xA0;` is placed right before the sh stores in the source (line 36 in orig: `c1 = -0xA0;` then the two stores). Wait in orig.c:

```
        *(s16 *)(p + 0x1C) = 0xA0;   /* x1 */
        *(s16 *)(p + 0x2C) = 0xA0;   /* x3 */
        *(s16 *)(p + 0x16) = -0x78;  /* y0 */
        *(s16 *)(p + 0x1E) = -0x78;  /* y1 */
        c1 = -0xA0;
        *(s16 *)(p + 0x14) = c1;     /* x0 */
        *(s16 *)(p + 0x24) = c1;     /* x2 */
```
So c1 is set right before its uses → short live range.

But gcc scheduled `li v1,-160` way earlier (position 60) in the target, meaning it hoisted the constant load.

The point: the target's allocation has c1 in v1 ($3) while all others in v0 ($2). Since local-alloc gives the *first* color to the highest-priority pseudo, and the byte pseudos are numerous...

Hmm, in the target each of the 12 byte loads is in v0, so those pseudos have priority over c1. In mine, the byte pseudos got v1 and c1 got v0. So in mine c1 outranked the byte pseudos. Why the difference? Because in the target, the byte load pseudos are... hmm, target is the same source (with pin). The pin changes allocation (c1 forced to $3, so others get v0).

So without the pin, gcc's preference gives c1 the first color. To flip, I need to change the relative priority of c1 vs the byte pseudos, or lengthen c1's live range so it overlaps more and gets pushed later, or shorten the byte pseudos' priority.

Options from the catalog:
- Use s16 c1 (m03 gave 11 too).
- Make the byte loads go through a temp so the pseudo has more refs? e.g. `u8 b = ((Unkstruct*)a0)->unk1C;` then store b 12 times: then one pseudo with 1 set + 12 uses (13 refs) — high priority → v0, and c1 → v1. But the target reloads from memory 12 times (each `lw v0,28(s1)`)! Because it's a volatile? No — `((Unkstruct_800B5CB8 *)a0)->unk1C` is a plain load; the target re-loads it each time, meaning the source must reload (a0->unk1C is not a local var, but GCC would normally CSE it into one load). Unless unk1C is declared volatile! Let me check the struct definition. If the field is volatile, each access reloads. That's how the target gets 12 separate loads.

So the struct field is likely volatile. Then a temp would still be 12 loads if I write `b = a0->unk1C` each time (a temp assignment per store). Let me check the type.

Let me look at the struct Unkstruct_800B5CB8 in src.

Also the target has the last byte load in a2 ($6) instead of v0 — that's a register-pressure/scheduling artifact.

Plan: to make the byte pseudos win over c1, I want each byte load to be a separate pseudo with enough priority. Currently in mine they lost. Why? Because in mine, the byte pseudos got v1 anyway — so they were assigned color 2. The local-alloc assigns: process pseudo with highest priority first → gets best reg. c1 has 3 refs (1 set, 2 uses) and its live range spans the two sh stores. The byte pseudos: 1 set (lw) + 1 use (sb) = 2 refs, but they're numerous. Priority in local-alloc = based on live range length and number of refs: c1's live range is long (spans several stores) → high priority (long live range = higher priority? in local-alloc, priority = "live range length * something + refs"?).

In GCC's local-alloc, `allocno_priority` computes: priority = (REG_LIVE_LENGTH) * something? Let me recall: In local-alloc.c, `allocno_priority` computes based on the number of references and the live range length: `priority = (REG_N_REFS * ... )`? There's a concept: "the priority of an allocno is the number of references, plus the live range length" (higher priority = allocated first). The byte pseudos have short live ranges (load→store adjacent), so they get lower priority than c1 (long live range, spans the whole const block).

In the target, c1 is pinned to $3, and the byte pseudos get $2. To reproduce that without a pin, I need the byte pseudos to outrank c1 or to conflict with c1 such that c1 gets the second color.

Alternative: shorten c1's live range! If c1's live range is short (set right before the stores), it might have lower priority than the byte pseudos. But c1 is set right before its uses in the source, and gcc hoisted the `li` to position 60 (early). Hmm, in mine the li is at 73 (late, near its uses) — actually mine had "li v0,-160" at 73 then the two sh at 74,75, and the target has li at 60 and sh at 74,76. So in mine the constant load is adjacent to the stores (short live range after scheduling) — yet c1 still won v0.

Hmm, so the local-alloc decision is made before scheduling, on the pre-schedule live ranges.

OK, different approach: what determines whether c1 gets $2 vs $3? local-alloc assigns colors in order of decreasing priority, and each allocno takes the "best" free reg. So the highest-priority allocno gets $2 (v0) here. If I can make some other pseudo have higher priority than c1, that pseudo takes $2 and c1 slides to $3.

Candidates for higher priority: the `ot` variable (D_800A651C[...].a) — it's used in the two AddPrim calls, live across the whole function (long live range, 3 refs). In the target ot is in s2 (a callee-saved reg, global-alloc). Fine.

The byte load pseudos: 2 refs each, short live range.

Hmm, what about the last byte load in a2 in the target? That suggests the 12th byte pseudo got $6 — meaning the first 11 got $2 and the 12th got... $6?? That's odd. Actually in the target, look:

```
2710: lw v0,28(s1)
2714: li v1,-160
2718: sb v0,34(s0)
271c: lw a2,28(s1)
2720: li v0,8
```
So the 12th byte load used a2 ($6) while 11th used v0. The reason: the 12th load is at 271c and its store `sb a2,42(s0)` is at 2758 — a long distance! Between them, v0 gets reused for constants. So the 12th byte pseudo has a long live range, and it got $6 because $2/$3/$4/$5 were busy? Hmm, at that point v0 and v1 hold constants.

Wait, why is the 12th byte load so far from its store? Because in source order the stores are: 0x10,0x18,0x20,0x28,0x11,0x19,0x21,0x29,0x12,0x1A,0x22,0x2A, then 0xF,0x13, then s16 stores. The last byte store is 0x2A at p+0x2A = 42. So the 12th byte load (for 0x2A) is separated by all the const stores. The scheduling interleaved.

OK. This is getting deep. Let me take the empirical route: I have ~20-30 min per item and 5 items. Let me think about what's likely to work, given moves from other shards.

Alternative approach: make c1's value not come from a variable at all but structure so that the -160 constant is in $3 naturally. Hmm.

Think about local-alloc priorities more concretely. In GCC (mips), local-alloc processes allocnos; for each in priority order it calls find_reg. Priority computation in local-alloc.c:

```
allocno->priority
  = ((double) (REG_N_REFS (reg) + ...) ...)
```
Let me recall actual code (gcc/local-alloc.cc):

```
static int allocno_priority (int n, allocno *a, reg_or_regclass_t rtx, reg_or_regclass_t reg)
{
  int reg_class_size = regclass_num_regs[reg_class];
  int size = ...;
  int weight = 0;
  ...
  weight += REG_LIVE_LENGTH (reg) * 4;  /* longer live range -> higher weight */
  weight += 2 * freq;  /* frequency */
  ...
}
```
Something like: `weight = REG_LIVE_LENGTH * 4` plus `2 * freq`. And REG_LIVE_LENGTH is the live range length in insns (or block count). So c1 (long live range) > byte pseudos (short). That's why c1 got $2.

To flip: make c1's live range SHORTER than the byte pseudos' live ranges? Hard: c1 must span from its set to 2 stores; the byte pseudos span 1 insn.

But wait: in the target, c1 is in $3 = second best. And the byte pseudos got $2. So in the target the byte pseudos outranked c1? Or maybe c1's pin forced local-alloc to allocate $3 to c1 first (pinned allocnos are allocated first), and then the byte pseudos took $2.

For an unpinned version: we need some pseudo to outrank c1. Which pseudo could have a long live range and be in the "v0" slot? The constants 0xA0, -0x78, 0x78: each is a separate pseudo (1 set, 1-2 uses). 0xA0 has 2 uses (sh 28, sh 44) → live range spans 2 stores, medium. -0x78: 2 uses. 0x78: 1 use.

Hmm, so c1 (2 uses) and 0xA0 (2 uses) have comparable priority; the tie-break matters.

In the target, note the order of allocation: constants 0xA0, -0x78, 0x78 all got v0 (same color, disjoint ranges). c1 got v1. So among the "const" pseudos, c1 was the one that got the second color. Why? Because its live range overlaps with 0xA0's live range? Let's see the target:

```
2730: li v0,160
2734: sh v0,28(s0)
2738: sh v0,44(s0)   <- 0xA0 second use
273c: li v0,-120
2740: sh v0,22(s0)
2744: sh v0,30(s0)   <- -0x78 second use
2748: li v0,120
274c: sh v1,20(s0)   <- c1 use
2750: sh v1,36(s0)   <- c1 use
2754: sh v0,38(s0)   <- 0x78 use
```
So c1's uses at 274c,2750 overlap with 0xA0's live range (2730-2738) and -0x78's (273c-2744) and 0x78's (2748-2754). Hmm, in local-alloc terms, the live ranges in the *unscheduled* code: c1 is set at position X and used at two stores; 0xA0 set and used at two stores; these overlap in the pre-schedule order? The source order:

```
*(s16*)(p+0x1C) = 0xA0;   // set 0xA0, use
*(s16*)(p+0x2C) = 0xA0;   // use
*(s16*)(p+0x16) = -0x78;  // set, use
*(s16*)(p+0x1E) = -0x78;  // use
c1 = -0xA0;               // set c1
*(s16*)(p+0x14) = c1;     // use
*(s16*)(p+0x24) = c1;     // use
*(s16*)(p+0x26) = 0x78;   // set, use
*(s16*)(p+0x2E) = 0x78;   // use
```
In unscheduled order the ranges of 0xA0, -0x78, c1 don't overlap each other (each is set then used before the next is set) — except c1 spans to its 2 stores. But they're all in the same basic block; live ranges in a single BB: after the last use of 0xA0, its range ends. So they don't conflict! Then why can't they all share v0? They can — 0xA0, -0x78, 0x78 all got v0. And c1 got v1 (in the target, forced). Hmm, in the target c1 is pinned so it can't be v0.

In the unpinned version, c1 got v0 and 0xA0/-0x78/0x78 got v1! Let's check the mine disassembly: the diff showed mine[62] `lw v1,28(s1)` and mine[78] `sb v1,42(s0)` — so the byte values are in v1 in mine. And the constants? Let me disassemble mine to see.

Let me get the candidate object with --keep and disassemble. delever_search --try --keep prints the candidate object path. But --keep leaves scratch; I must clean up. Let me do it and then remove.

Actually simpler: compile the body myself? No, easier: use --keep, disassemble with disasm.py, then rm the scratch dir.

Let me try.
