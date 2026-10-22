---
ts: 2026-10-22T00:39:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_7ipqhd3RDQ0Gpu1QEkG3
---
The target's frame: 32 bytes, with s0 at 24(sp) and ra at 28(sp). The lower 24 bytes (0-23) are unused (the pad). Mine: 24 bytes with s0 at 16(sp), ra at 20(sp) → the lower 16 bytes unused.

So the target reserves 8 more bytes at the bottom. `s32 pad;` = 4 bytes; with 8-byte alignment, the locals are: pad (4) + v0 (4) + v1 (4)? Hmm.

Wait, in the target the locals v0/v1 are in registers (not stack). The frame is: ra (28), s0 (24), and 24 bytes below for the "pad" (a local array?). Hmm, in the source: `s32 v0; s32 v1; s32 pad;` — all unused-as-locals (they're in registers). So the frame is: 8 (ra+s0 saved) + 24 = 32. The 24 bytes = the locals' stack area (v0, v1, pad = 12 bytes → aligned to 16?) Hmm.

Mine: 24 bytes = 8 (ra+s0) + 16 (locals area). So the target's locals area is 24 vs mine 16 → the difference is 8 bytes = 2 slots.

Hmm! So the `pad` in the target occupies 8 bytes? `s32 pad;` is 4 bytes. Hmm, but with the "m"(pad) input, the asm takes the *address* of pad → the variable is address-taken → it must live in memory → 4 bytes. Then the locals area = v0(4) + v1(4) + pad(4) = 12 → aligned to 16. Hmm, that gives 16, not 24.

Hmm, the target's 24-byte locals area suggests 3 slots of 8 bytes?? Or maybe GCC's frame layout: the locals area is aligned to 8 and the total frame to 8. Hmm: 8 (saved) + 12 (locals) = 20 → aligned to 24? Hmm, and the target is 32.

Wait, maybe the difference: in the target, the locals area is 24 because of the *frame pointer* rules... Let me instead consider: what if the target's frame includes an extra 8 bytes because `pad` is a *4-byte* local and the compiler reserved space for a "pad" of 8 (as the comment in another function said "s32 pad[4]; /* load-bearing dead local: reserves 16B var_size */")?

So maybe the real source had `s32 pad[2]` or the frame was forced to 8 bytes more.

Hmm, in my c1 (no asm), the locals are v0, v1, pad — but `pad` is unused → GCC removes it → the locals area = v0+v1 (8 bytes, but they're in regs) → hmm, GCC still reserves stack space for locals that are address-taken or spilled. If v0/v1/pad are all in registers, why is there a 16-byte locals area at all? Because the frame is aligned: 8 (ra+s0) + 16 = 24.

Hmm, so GCC reserved 16 bytes for the locals area even though they're all in regs? That's GCC's standard: the frame includes the local area for all locals (var_size). With v0, v1, pad = 12 bytes → rounded to 16.

In the target: 24 bytes of local area → the locals total ≥ 17 bytes → e.g. v0, v1, pad + something = 12+? Hmm. Or maybe the target's locals area is 24 because `pad` was *address-taken* (the asm's "m"(pad)) and thus forced to the stack, plus GCC's frame layout for address-taken locals adds 8?

Hmm, in the source there's a comment in the *other* function: "s32 pad[4]; /* load-bearing dead local: reserves 16B var_size matching target's 0x28 frame */". So the pattern is: a dead local array that reserves stack space.

For our function: `s32 pad;` (4 bytes) with the asm's "m"(pad) making it address-taken → the variable must be in memory → 4 bytes at a specific offset → the frame's local area = ... let me compute: with pad address-taken, GCC allocates it at a fixed offset in the frame (say sp+0), and the frame = 8 (ra,s0) + 4 (pad) → aligned to 8 → 16? But the target is 32.

Hmm, wait. Maybe the "m"(pad) input makes GCC allocate pad at a *negative* offset requiring a frame pointer? Hmm.

Let me think about the target's frame: 32 bytes with ra at 28 and s0 at 24. The area 0-23 is unused. So the local area is 24 bytes. If the locals are v0, v1, pad (4 each = 12), why 24? Unless GCC's frame layout puts the locals at 0..11 and then *rounds*... no, 24 ≠ 12.

Hmm, maybe the "m"(pad) input forces a *frame pointer* (fp) usage? No, the target doesn't use fp.

Hmm, alternatively, maybe the *asm's* memory input forces GCC to reserve a "scratch" area? Hmm.

Honestly, the practical approach: try plain-C variants that force a bigger frame:
- `s32 pad[2];` (8 bytes) → the local area = 16 → the frame = 8+16 = 24. Same as now. Hmm.
- `s32 pad[4];` (16 bytes) → local area 24 → frame 32! That matches the target's frame.

But `pad` must be *address-taken* to be allocated... otherwise GCC removes it entirely (the frame would be 8 → 8, aligned 8). Hmm, but the current mine has a 16-byte local area with `s32 pad;` (unused). Hmm! So unused locals DO get stack space in this build? Let me check: mine's frame is 24 = 8 + 16. The locals are v0, v1, pad = 12 bytes → 16 with alignment. So yes, the local area is reserved even for unused locals (GCC 2.7.2 reserves the frame space for all declared locals — "var_size" — and the dead `pad` still occupies its 4 bytes).

Hmm interesting. So to get a 24-byte local area I need the locals to total ≥ 17 bytes. E.g. `s32 pad[4]` (16) + v0 + v1 (8) = 24 → the frame = 32.

But the constraint: the *original* source declares `s32 pad;`. If I change it to `s32 pad[4];`, the frame matches. But is that legitimate? The "pad" is a dead local; its *size* is a free parameter of the C. Changing `s32 pad;` to `s32 pad[4];` is a plain-C change (a "widths"/"decl" move). It doesn't add a lever. Hmm, but it does change the source's declaration of a variable whose only purpose is the frame. Since the *lever* (the asm) is what forces the address-taken-ness, and the frame is the observable, I think changing the pad's size is a legitimate lever-free move (it's a "decl/scope" move in the C0505 catalog).

But then the register part (v0 vs v1) remains. Hmm, the score would go from 19 to maybe 8.

Hmm, so item 5 needs BOTH: the frame size AND the v0/v1 copy.

The v0/v1 copy: in the target, `move v1,v0` exists; mine doesn't (GCC merged the copy).

Hmm! Wait: in the target, the *asm* is `__asm__ volatile("" : "=r"(v0) : "0"(v0), "m"(pad));` — the "m"(pad) input! A memory input means the asm *reads* memory → GCC must ensure the memory is up to date → and it also means the asm *cannot* be moved across stores... but more importantly: does the "m" input prevent the *coalescing* of v0 and v1? Hmm, no.

Hmm, why does the target have `move v1,v0`? Because the source says `v1 = v0;` and the copy is preserved. The reason it's preserved in the target: the asm redefines v0 → v0's value after the asm is unknown → v1 (the copy of the old v0) is a *different* value from v0 → they can't share a reg.

In mine: v0 and v1 are the same value → merged → the copy is dropped (and the else branch uses v0 directly).

Plain-C: to keep the copy, the *source* must make v0 and v1 genuinely different after the copy... but the source's semantics require v1 = the old v0 and v0 = v1 - 2 in the else branch.

Hmm, hmm! What if the source is restructured so that the *test* uses v1 and the *else* branch uses v1, while v0 is redefined *before* the test? Like:

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    if (v1 < 3) {
        v0 = *(s16 *)(...);      /* v0 redefined */
        ...
    } else {
        v0 = v1 - 2;
        ...
    }
}
```
Here, at the test, v0 and v1 are equivalent → the test on v1 can use v0 → merged. Hmm.

What if the copy is made *after* a redefinition of v0? E.g.:
```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;            /* the copy */
    v0 = v0;            /* ??? */
```

Hmm. What if the *test* is on v0 and the *else* branch uses v1, and v0 is redefined in the *if* branch — GCC merges because the else branch's use of v1 can be rewritten to v0 (they're equal at that point).

To block the rewrite, v0 must differ from v1 at the else branch's use. E.g. if the else branch is:
```
} else {
    v0 = v1 - 2;
    unkFC = v0;
}
```
The use of v1 is at "v1 - 2". If instead the source were:
```
} else {
    v0 = v1;      /* hmm */
    v0 = v0 - 2;
```
no.

What if the *if* branch's redefinition of v0 were moved *before* the test (i.e. the source computes something else)? Hmm.

OK, alternative approach: what if the *copy* is not v1 = v0 but a *recompute*:
```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = CAST_SIGN(s16, a0, 0xFC);   /* a real 2nd load of the same value */
    ...
}
```
Then v1 is a *separate* load → CSE folds it into v0's load (same address, no intervening store) → merged again. Hmm, but the *asm* has a "m"(pad) input... no memory clobber, so no.

Hmm, what if there IS an intervening store between the two loads? In the source, the first branch (`if (func_8012BEE8() != 0)`) stores to unkFC, but that's the other branch.

Hmm.

What if the value is loaded from a location that could change? No.

OK, so item 5's v0/v1 copy needs the "opaque v0" effect, which in plain C requires v0 to be *redefined* between the copy and the use, with the redefinition being a no-op semantically...

Hmm! What about this: the *if* branch redefines v0 (`v0 = *(s16 *)(...)`). What if the *test* used v1 and the if-branch's first statement redefines v0, and the *else* branch used v1:

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    if (v1 < 3) {
        v0 = *(s16 *)(((Unkstruct_8017EBA0_2 *)a0)->unk20 + 0x12);
        v0 = (v0 + 2) & 0x3FF;
        if (v0 < 4) { unkFC = 0; }
    } else {
        v0 = v1 - 2;
        unkFC = v0;
    }
}
```
At the test (v1 < 3): v0 == v1 → the test can use v0 → merged. Hmm.

BUT: what if the *if* branch redefinition of v0 happens *before* the test in the RTL (i.e. the compiler moves it up)? The target's asm:
```
30a0: lh v0,252(s0)
30a8: beqz v0,30ec
30ac: move v1,v0        <- the copy (in the delay slot!)
30b0: slti v0,v0,3
30b4: beqz v0,30e8
30b8: addiu v0,v1,-2    <- the else branch: v0 = v1 - 2
30bc: lw v0,32(s0)      <- the if branch: v0 = unk20
...
30e8: sh v0,252(s0)     <- unkFC = v0 (the else branch's result)
```
Note: in the target, the *else* branch computes `addiu v0,v1,-2` — using v1 (the copy). And the if branch computes v0 = unk20 etc. So in the target, v0 and v1 are separate regs.

For GCC to keep them separate, v0 must be *redefined* somewhere between the copy and the uses. In the target's code, v0 is redefined in the if branch (30bc: lw v0,32(s0)) — but that's *after* the test. The test at 30b0 uses v0 (slti v0,v0,3) — so at the test point, v0 is still the old value. So the copy v1 is only needed in the *else* branch (where v0 is not redefined before the use) → removable. But the target kept it!

Because the asm made v0 opaque: after the asm, v0's value is unknown → the test `v0 < 3` uses the *unknown* v0, and the copy v1 = the old value... wait, but then the test would be on the unknown value, not the loaded one! Hmm, but the target's test at 30b0 is `slti v0,v0,3` where v0 = the loaded value (the asm's output is in the same reg v0, so the value is unchanged in practice, but the compiler doesn't know it).

Hmm, so in the target, the *test* is on the opaque v0 (which is in v0), and the *else* branch computes v0 = v1 - 2 where v1 = the *pre-asm* value. Since the compiler doesn't know v0's value after the asm, it can't use v0 in the else branch → it uses v1 (the copy). And the copy can't be coalesced with v0 (different values).

So the asm's effect = "v0 is unknown after the asm" → forces the copy v1 to be kept in a separate register.

Plain-C: to have v0 unknown after the copy... the same opacity problem. ARGH.

Hmm, but hold on! Maybe there's a plain-C way here: what if the *else* branch used a *recomputed* value instead of the copy? E.g.:

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    if (v0 < 3) {
        v0 = *(s16 *)(((Unkstruct_8017EBA0_2 *)a0)->unk20 + 0x12);
        v0 = (v0 + 2) & 0x3FF;
        if (v0 < 4) { unkFC = 0; }
    } else {
        v0 = v0 - 2;      /* uses v0 directly, no copy */
        unkFC = v0;
    }
}
```
That's the "merged" version = mine (49 ins, v1 instead of v0). The target has the extra `move v1,v0` and uses v0/v1.

So the difference is exactly the copy. And the copy is only preserved if the compiler can't prove v0 == v1 at the use.

Hmm! What if the *if* branch redefinition of v0 were *hoisted* before the test in the source? I.e.:

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    if (v1 < 3) {
        v0 = *(s16 *)(...);
        ...
    } else {
        v0 = v1 - 2;
        ...
    }
}
```
The test on v1: at that point v0 == v1 → the compiler rewrites the test to use v0 (or v1 to v0) → merged. Hmm, but which direction? cse's make_regs_eqv makes them one canonical reg → the copy is removed.

Hmm, what if the source *deliberately* makes v0 different: e.g.

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    v0 = v0 + 0;   /* no */
```

What if the *else* branch is written to use v1 in a way that forces it: e.g.
```
} else {
    v0 = v1 - 2;
    unkFC = v0;
}
```
The use of v1 is in "v1 - 2" → rewritable to "v0 - 2" (since v0 == v1) → the copy dies.

To block it: v0 must be *changed* between the copy and the else branch's use, on the *else* path only. E.g., if the source had, in the else branch:
```
} else {
    v0 = v1 - 2;
```
no change before the use.

What if the *order* of the branches in the source were swapped (the `v0 < 3` test first, then the recompute)? I.e.:

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    if (v0 < 3) {
        v0 = *(s16 *)(...);
        v0 = (v0 + 2) & 0x3FF;
        if (v0 < 4) { unkFC = 0; }
    } else {
        v0 = v1 - 2;
        unkFC = v0;
    }
}
```
(current source).

Hmm what if the *if* branch's redefinition were `v0 = ...` placed *before* the copy? Like:

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    ...
```

OK here's another thought: what if the *copy* v1 = v0 is *not* the issue, but rather the asm's "m"(pad) input (a memory reference) forces GCC to keep v0 in a register *at the asm point* — and the fact that the asm is *volatile* means it can't be moved/deleted, and it acts as a *barrier* for the value numbering (the asm redefines v0 → v0's value after the asm is a new value).

In plain C, the equivalent barrier for a *value* is... hmm.

OK, let me try a completely different plain-C formulation for the else branch: what if the source used the *original* value directly, i.e. re-read the field?

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    if (v0 < 3) {
        v0 = *(s16 *)(((Unkstruct_8017EBA0_2 *)a0)->unk20 + 0x12);
        v0 = (v0 + 2) & 0x3FF;
        if (v0 < 4) { unkFC = 0; }
    } else {
        v0 = v0 - 2;
        unkFC = v0;
    }
}
```
That's mine (49 ins, v1). The target wants: v0 = the loaded value, v1 = a copy, the test on v0, and the else branch using v1.

Hmm, what if the source is:
```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    if (v0 < 3) {
        ...
    } else {
        v0 = v1 - 2;
        unkFC = v0;
    }
}
```
(current) — the compiler removes the copy.

What if the *test* were on v1 instead of v0 AND the if-branch redefinition of v0 came *first* in the source? Hmm, the if branch is:
```
if (v0 < 3) { v0 = *(s16*)(...); ... }
```
The redefinition is inside.

Hmm, what if we restructure the *whole* if/else so that v0 is redefined *before* the test on the else path? Like:

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    if (v1 < 3) {
        v0 = *(s16 *)(...);
        v0 = (v0 + 2) & 0x3FF;
        if (v0 < 4) { unkFC = 0; }
    } else {
        v0 = v1 - 2;
        unkFC = v0;
    }
}
```
The test on v1: cse would canonicalize v1 → v0 (they're equal) → the test uses v0, and the else branch's use of v1 → v0. Merged. Hmm.

Unless cse's canonicalization goes the *other* way: if v1 is canonical, the test uses v1 and the else uses v1, and v0 is only in the if branch → then the copy might be kept! Because v0 (the loaded value) is used in the test... hmm, if v1 is canonical, then the load's result would be renamed to v1 → the test on v1, and v0 = the same reg → still merged.

Hmm. cse's make_regs_eqv merges the two regs into one; the copy insn (move) is then deleted. So it's merged regardless.

So the ONLY way to keep a physical copy is if the two values are *not* provably equal. The asm makes them not provably equal.

=> item 5's v0/v1 = WALL (opacity). But the frame part might be crackable. Hmm, but both are needed for score 0.

Hmm, hold on! What if the copy is preserved because the *use* of v1 is in a *different* basic block where v0 has been redefined? Look at the target: the else branch is at 30b8: `addiu v0,v1,-2` — v0 is redefined by this instruction (v0 = v1 - 2). The *use* of v1 is in the same instruction that redefines v0. So the rewrite "v0 = v0 - 2" is possible if v0 == v1 at that point → yes it is → removable. So the target's copy is *only* there because of the asm's opacity.

=> Item 5: WALL. Mechanism: the volatile asm's tied output makes v0 opaque after the copy, so the copy v1=v0 cannot be coalesced (the target keeps `move v1,v0` and uses v1 in the else arm) and the "m"(pad) input keeps the `pad` local address-taken (frame 32 vs 24). Plain C: the copy is coalesced away (49 ins) and the frame is 8 bytes smaller.

Tag: new tag, e.g. `cse-copy-merge` (exists in walls.txt? there's `combine-copy-merge` and `cse-copy-merge` in moves.md as wall tags but walls.txt has: cse-const-addr, sched1-argcopy-hoist, sched1-birth-boost, callee-saved-order, flow-unused-result, sp-stack-switch, no-c-spelling, hand-asm). The walls.txt list is the canonical tag list: "A new tag: <pass>-<what>, lowercase, defined in the coder's results evidence." So I can define new tags. moves.md uses tags like "cse-copy-merge" — so tags can be new.

For item 5: `cse-copy-merge` (the copy v1=v0 is merged; the asm's opacity is what keeps it). Plus the frame part. Let me use `cse-copy-merge` and mention the frame in the evidence.

Hmm, but the frame difference is also part of it: the "m"(pad) input forces the pad local to be address-taken (frame 32). In plain C I could fix the frame by making pad bigger (s32 pad[4]) — that's a legit move. So the *remaining* wall is the copy merge.

OK. Let me now speed up. I'll try the "real 2nd set" move on the most promising items. Given the pattern (all three levers are "opacity" levers), most items will be walls. But let me check the ones with score 6 (func_8018C730) and the compile errors (func_8018CDEC, func_80191020) — those might be different.

Let me look at func_8018C730 (score 6, 18 vs 23 — 5 instructions missing!).
