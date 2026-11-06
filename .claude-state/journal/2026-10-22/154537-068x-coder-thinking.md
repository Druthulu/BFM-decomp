---
ts: 2026-10-22T21:45:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SNJIKdMgqwC5qvhgHIO5
---
Still 2. Time: ~15:55, item 3 at 14 min, 24 tries.

Let me think once more about the sched2 tie-break. In the target: sw ra before li. In mine: li before sw ra.

sched2 is a bottom-up scheduler: it fills the block from the END backwards. The last insns scheduled are the earliest in program order. So "81 (T-13), 85 (T-12), 4 (T-11), 14 (T-10), 83 (T-9)..." — hmm, the dump showed "ready list at T-11: 4 (1)" and "T-12: 85 (1)" and "T-13: 81 (1)". And at T-9 "insn 83 has a greater potential hazard, now 83 14 4" then "ready list at T-10: 14 (1) 4 (1)". So 83 was launched at T-9 (or T-10?). The final program order = launch order reversed: last launched = earliest. So order: 81, 85, 4, 14, 83, ... hmm that gives 14 before 83 → li before sw ra. Yes matches mine.

So sched2 launched 83 (sw ra) at T-9 (later) and 14 (li) at T-10. The bottom-up scheduler launches from the end; the insn launched LAST is placed FIRST. So 83 launched at T-9 means it's placed after 14. To get the target (sw ra before li), 83 must be launched later than 14.

The choice at T-10: ready list "14 (1) 4 (1)" and it launched 14. Then at T-9: "14 4 83" → 83 was added to the ready list and had "greater potential hazard" → picked.

So the question: why is 83 (sw ra) only ready at T-9 while 14 (li) is ready at T-10? Because 83 must wait for something? "insn 83 has a greater potential hazard" — it was in the ready list at T-9.

In the target, the barrier would have prevented sw ra from being in the ready list until the barrier... 

Hmm, at T-10 the ready list has 14 and 4; 83 isn't ready yet (it depends on the s0 store? or on the sp adjustment). sw ra,36(sp) depends on the sp addiu (insn 81?) — that's at the very start.

Wait: the bottom-up scheduler: at T-1 it schedules the last insn of the block. The block ends at the branch. It works backwards. Insn 83 (sw ra) becomes ready only after the insns *after* it in program order are scheduled. Since sw ra is 4th in program order, it becomes ready late — at T-9. And the li (14) is 5th, ready at T-10. Hmm, so in mine 14 was launched before 83.

The choice at T-10 was between 14 and 4; then at T-9 between 14, 4, 83 → picked 83? But then 83 would be placed... 

I'm going in circles. Let me consider: in the target, at T-10 the pick was 83 rather than 14, which would require 83 to be ready at T-10 and 14 not, or the hazard rule to fire.

The hazard rule fires when both are ready. In mine at T-9 both 14 and 83 are ready and 83 wins — but 14 had already been launched at T-10.

So the fix: make 14 (the li) NOT ready at T-10, i.e. delay its birth. What makes the li ready? Its dependence on insns after it. The li v0,-64 is a leaf (no deps) — it becomes ready as soon as the scheduler reaches it.

Hmm, in a bottom-up scheduler, an insn with no successors becomes ready immediately... so both would be ready early.

OK: in mine, at T-10 the ready list is "14 (1) 4 (1)" — 83 is NOT there. Why? Because 83's successor chain isn't scheduled yet: sw ra is a store; the scheduler requires its "following" insns to be scheduled first (dependence). Since 83 is a store with no dependents, it should be ready...

Whatever the internals, empirically the target order requires the barrier.

Let me try one thing: what if the zero-store and the -0x40 store come *before* the li in a way that... 

Actually — what if I make the -0x40 store's value come from the *b-copy load*? No.

New idea: **make the li be born later by using a value that's already in a register**: -0x40 could come from... nothing.

Alternative: **make the li a `lui`-free constant load from a different path**: no.

Let me consider that maybe the answer is a *different* framing: what if I declare `loc` as two s16 variables? No — the asm uses sp+16/sp+18 and a 16-byte struct.

I'll call it: after 24 tries and ~15 min, this is a WALL of the same family as item 2 but the init-at-decl trick doesn't apply because the struct's first store is a zero (no li) and the second needs the li.

Hmm wait — actually! What about declaring `loc` with an initializer for the FIRST store only, i.e.:

```
S16_SC02_005_8017F7CC loc = {{0}};   // no
```

Hmm, what about this: the initializer trick worked in item 2 because the stores became part of the decl, emitted in the prologue *before* the load. Here I want the `li v0,-64` to be born before sw ra — no, AFTER sw ra.

If the -0x40 store were part of the declaration initializer, its li would be emitted at the decl point — which is still after the prologue's sw ra (the prologue is emitted first). Would the decl-initializer li land before or after sw ra? In item 2, the initializer stores landed AFTER sw ra (slots 4,5) and before the load. And sched2 kept sw ra at slot 3.

So: if `loc`'s -0x40 store were an initializer, the li might land after sw ra! Let me try a full initializer for loc:

```
S16_SC02_005_8017F7CC loc = { {0, 0, 0xC0, 0xFF, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0} };
```
This is byte-wise → sb stores, changing asm (d8 gave 54 ins, 6).

What if I write the initializer with an s16 view? Can't — the struct has u8 arrays.

Unless I declare a different local type! The C source can declare `loc` as any 16-byte type. E.g.:

```
s16 loc16[8] = {0, 0, -0x40, 0, 0, 0, 0, 0};
```
and then use `*(M8_...)&loc16[4] = D_801E2DD8;`. The asm: the initializer would produce sh stores for each non-zero element? For `s16 loc16[8] = {0,0,-0x40,...}` the compiler might emit 8 sh stores or 4 sw stores. Hmm, in item 2 `s16 sp10[2] = {0, -0x40}` produced exactly `sh zero,16; sh v0,18` (2 stores). For 8 elements it'd produce 8 sh stores (or optimize). Risky but worth a test.

Actually — what about keeping `loc` as is but adding a *second* local with the same init trick to trigger the prologue ordering? No, that adds insns.

Hmm, but actually the simplest: declare `loc` as Entry16 but initialize via a small helper variable? no.

Let me try the s16[8] idea:
```
void func_8017F7CC(s32 param_1) {
    ...
    s16 loc[8] = {0, 0, -0x40, 0, 0, 0, 0, 0};
    ...
    *(M8_SC02_005_8017F7CC *)&loc[4] = D_801E2DD8;
```
Hmm, the M8 copy needs the address of loc.b = sp+24. `&loc[4]` = sp+16+8 = sp+24. OK.

But the initializer for 8 s16 elements: gcc would emit 8 sh stores, most of them zero. The target only has 2 sh stores (16 and 18). So this fails.

Alternative: declare two s16s:
```
s16 loc0 = 0;      // sp+16
s16 loc2 = -0x40;  // sp+18
u8 blob[8];        // sp+20..27
```
Hmm, the layout: loc.a.raw[0..7] at sp+16, loc.b.raw at sp+24. The code stores raw[0..1] = 0 (sh at 16) and raw[2..3] = -0x40 (sh at 18), then the b copy at sp+24.

If I declare:
```
s16 loc0 = 0;
s16 loc2 = -0x40;
u8 blob[8];
```
the frame would be sp+16, sp+18, sp+20 (blob) — but the b copy writes at sp+24. Alignment: blob at sp+20, 8 bytes → sp+20..27, so &blob[4] = sp+24. Then `*(M8*)&blob[4] = D_801E2DD8;`.

Frame: the total would be 16+8 = 24 bytes + saved regs... The original frame is 40 with loc at sp+16 (16 bytes) → 16..31, then ra at 36, s0 at 32. With blob at sp+20..27 it'd be different.

Too fragile. 

Alternative: declare `s16 loc16[2] = {0, -0x40};` and a separate 8-byte local placed right after:
```
s16 loc16[2] = {0, -0x40};   // sp+16, sp+18
u8 blob[8];                  // sp+20?
```
The original loc.b is at sp+24 (16+8). If loc16 is at sp+16 (4 bytes) and blob at sp+20, then &blob[4] = sp+24. But then the b-copy writes at sp+24..31 which is inside blob[4..11] — out of bounds. Ugly but the asm would be the same if the frame layout works out.

Risky. Let me first test the simpler question: does a declaration initializer put the li after sw ra? Test: `s16 loc16[2] = {0, -0x40};` replacing the two stores, keeping the rest (using a cast for the b copy at the right offset):

```
s16 loc16[2] = {0, -0x40};
*(M8_SC02_005_8017F7CC *)&loc16[2] = D_801E2DD8;
```
`&loc16[2]` = sp+16+4 = sp+20, but the target needs sp+24. Hmm, unless the compiler pads... no.

What if I use a 16-byte array with only the first two initialized:
```
s16 loc16[8] = {0, -0x40};
```
This zero-initializes the rest → 8 stores. Bad.

OK: what about `s16 loc16[2] = {0, -0x40};` plus `s32 pad[2];` and writing the b copy at `(u8*)loc16 + 8` = sp+16+8 = sp+24 if loc16 is at sp+16 and there's no padding. The compiler allocates loc16 4 bytes at sp+16, then pad at sp+20. Then (u8*)loc16+8 = sp+24 — inside pad[0]. Writing 8 bytes there is UB-ish but compiles to the same insn if the address folds.

Frame size: loc16 (4) + pad (8) = 12 bytes at sp+16..27, plus ra/s0 → frame 40? The original had 16 bytes at sp+16..31. So the frame might shrink to 32. Risky.

Alternative: `s16 loc16[2] = {0, -0x40}; u8 b[8];` where b lands at sp+20 → (u8*)b+4 = sp+24. Hmm.

Actually — simplest: declare a 16-byte local with an initializer that covers only the first 4 bytes and leaves the rest unspecified:
```
u8 blob[16] = {0, 0, 0xC0, 0xFF};   // byte stores → sb, bad
```

Hmm.

OK, alternative idea that avoids all this: use the *item-2 trick* on the b-copy? No, the issue is the li.

Let me reconsider: is the li really the only diff? Yes: sw ra vs li swapped.

What if the -0x40 store came BEFORE the zero store in program order but sched2 put the li... c1 gave 3 (worse).

What if I make the zero store use a register too, e.g. `*(s16 *)&loc.a.raw[0] = iVar2 - iVar2;`? folds.

I'm at 15:58, ~17 min, 29 tries. Let me do a couple more and then WALL.

Actually, one more idea worth trying: **`s16 m = -0x40;` declared at the top with init at decl**, then the store uses m. In item 2 the init-at-decl fixed the schedule. Here the li would be born at the decl (before the stores), still after the prologue... but its position relative to sw ra? The decl of m comes after the prologue in expand order, so sw ra (prologue) is first. Then the li. That's exactly the target order! c2 did `s16 m = -0x40;` right before the stores and gave 2 — hmm, but where was the decl? c2 placed it after the two... no: c2 replaced ST with "s16 m = -0x40;\n *(s16*)&loc.a.raw[0] = 0;\n *(s16*)&loc.a.raw[2] = m;\n ..." — so the decl is the first statement. It scored 2. Maybe the residual is different now? Let me check c2's diff.

Let me check c2 and d3 diffs.
