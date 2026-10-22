---
ts: 2026-10-22T07:14:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_F8RcXGlrhks5dgL95lCz
---
All stuck at 14. The difference is the magic constant's register (a0 vs v0) and the dividend's register.

Let me think about what makes the target use a0 for the magic constant.

In the target: `lui a0,0x6666; ori a0,0x6667` — a0 is an ARGUMENT register. In this function, a0 is the function's parameter (a0 = the entity pointer) and it's kept in s0 (`move s0,a0` at the start). So a0 is free for temporaries.

Hmm, so why would the constant land in a0 rather than v0? Because of the local-alloc's qty/priority ordering: the constant pseudo has 2 uses; the dividend temporaries have more.

Hmm, in mine the constant is in v0 and the dividend in a1. In the target the constant is in a0 and the dividend in v1.

So the allocation order differs: target: [a0 (const), v1 (dividend)]; mine: [v0 (const), a1 (dividend)].

Hmm! Notice: in the target, the registers used are a0 and v1; in mine, v0 and a1. Both pairs are "one caller-saved arg reg + one v reg" but swapped.

Interesting: in the target, the constant (2 uses, born early) got a0 and the dividend got v1. In mine, the constant got v0 and the dividend got a1.

Hmm, so it's a swap of the arg-reg vs the v-reg allocation between the two pseudos.

What decides? local-alloc's "qty" and the priority order: the pseudo with more refs gets the lower-numbered reg? Hmm.

The tree's launder affects: with the launder, vol has 2 sets. Hmm.

Let me think about the actual pseudos at the sched1 stage in the tree:
- The vol division: the dividend = (160-av)*127 → a pseudo; the quotient → vol's pseudo (or a copy).
- The magic constant pseudo (0x66666667) with 2 uses.
- The sx division: dividend = sx+160.

Hmm.

Since the difference is subtle (a register swap of 2 pseudos), maybe a different spelling changes the priorities.

Let me consider: what if the vol division is written as `vol = ((0xA0 - av) * 0x7F) / 0xA0;` (as the tree) and the launder is replaced by giving vol a 2nd set in a way that mirrors the tree's RTL (a copy from the division result)?

E.g.:
```
s32 vq = ((0xA0 - av) * 0x7F) / 0xA0;   /* the division result */
vol = vq;    /* copy: vol has 1 set */
```
Hmm, vol needs 2 sets.

What about:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol = vol;   /* cse removes */
```

Hmm.

What about the C0458 "copy then accumulate on the copy" pattern:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;   /* vol: 1 set */
vol2 = vol;                            /* copy */
vol2 = vol2 + 0;                       /* hmm */
```
no.

Let me reconsider. Maybe the register difference comes from the ORDER of the two divisions' RTL: in the tree, the launder creates an insn BETWEEN the two divisions (the asm), which changes the insn UIDs and hence the ready-list tie-breaks (LUID order) → different scheduling → different allocation.

Ugh, so we're back to needing an RTL insn between the two divisions. Hmm!

But hold on: in cand02 the multiply ORDER is right (vol's mult before the pan's mult) and the count is right. The remaining diff is the register allocation of the two pseudos (constant → a0 vs v0; dividend → v1 vs a1) — a local-alloc outcome.

What if I try the compound form but ALSO keep a copy so the RTL has an extra insn:
```
vol = (0xA0 - av) * 0x7F;
vol /= 0xA0;
```
vs the tree's shape:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;   /* 1 expression */
<asm>                                  /* an insn */
```

What if I write:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
do { } while (0);   /* !FAKE: do-while — an RTL insn? no, an empty loop has no insn */
```
Hmm, an empty do-while has no insns (but adds loop notes). The asm adds an insn.

What about `vol = vol;` inside a do-while: `do { vol = vol; } while (0);` — the self-copy might be an insn (a copy pseudo) → an RTL insn that emits nothing (coalesced)!

Hmm, that's the "asm replacement" attempt: give vol a 2nd set AND an RTL insn between the divisions. Let me try:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
do { vol = vol; } while (0);   // !FAKE: do-while
```
Hmm, but the self-copy is probably folded by cse (the value is the same) → no insn.

What about:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
do { vol = (s32)vol; } while (0);   // !FAKE: do-while
```
A cast to the same mode → folded.

Hmm. What about a compound on vol inside the loop: `do { vol /= 1; } while (0);` — a division by 1 → folded.

What about `do { vol = vol + 0; } while (0);` → folded.

Hmm, what if the loop body does something that keeps the value but is a real insn: e.g. `do { vol2 = vol; } while (0);` where vol2 is a new variable → an extra copy (maybe coalesced away → no instruction, but the RTL insn exists!). That gives an RTL insn (the copy) that might be coalesced to nothing. And vol2 would be dead → removed. Hmm.

OK, let me think about the actual difference in the ALLOCATION instead. The difference between the target and cand02 is which pseudo gets a0 vs v0.

Let me use alloc_table.py on the dumps to compare the allocation tables! That's the tool for this. But I'd need dumps for the tree's TU and cand02's TU.

Hmm, time. It's 01:25 now (started 00:31). Item 4 has taken ~20 min. Let me give it another ~20-30 min.

Let me try a few more spelling variants quickly:
- cand09: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` (same as cand04)
- cand09b: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with the multiplication as `(0xA0 - av) * 127` (decimal)
- cand10: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` + `vol2 = vol;` (a copy to a new var, dead) — an RTL insn?
- cand11: the division as `vol = ((0xA0 - av) * 0x7F) / 160;` (decimal 160 vs 0xA0) — the magic is the same.
- cand12: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` with `av` computed differently? no.

Hmm, what about the ORDER of the two divisions? In the target, the vol multiply (c70) comes before the pan multiply (c80) ✓ (both in cand02 and the target). The difference is just the regs.

Let me look at the diff once more:
```
insert mine[117:117] target[117:119]: lui a0,0x6666 / ori a0,0x6667   (the target's constant at 117-118)
replace mine[120:124] target[122:124]:
   mine 120: subu a1,v1,v0   |  target 122: subu v1,v1,v0
   mine 121: lui v0,0x6666  |  target 123: mult v1,a0
   mine 122: ori v0,0x6667  |  --
   mine 123: mult a1,v0     |  --
replace mine[125:126] target[125:126]: addiu v1,a2,160 | addiu v0,a2,160
replace mine[127:128] target[127:129]: mult v1,v0 | mult v0,a0 / sra v1,v1,0x1f
replace mine[129:132] target[130:132]: sra v0,a1,0x1f / subu a1,a0,v0 | sra v0,v0,0x1f / sra v1,v1,0x1f / --
replace mine[133:135] target[133:135]: sra v0,a2,0x3 / subu a2,v0,v1 | sra v1,a2,0x3 / subu a2,v1,v0
```
So: the target's division result ends in a1 (subu a1,a0,v1) and the pan result in a2; mine: the vol result in a1 (subu a1,a0,v0) ✓ same, and the pan result in a2 (subu a2,v0,v1) vs the target (subu a2,v1,v0) — operand order swapped!

So the real differences:
1. The magic constant: target a0, mine v0.
2. The dividend of the vol division: target v1, mine a1 (well, mine: `subu a1,v1,v0` = the ×127 result in a1; target: `subu v1,v1,v0` = in v1).
3. The pan's dividend: target v0 (`addiu v0,a2,160`), mine v1 (`addiu v1,a2,160`).
4. The pan's sign correction: target `sra v1,v1,0x1f` (of v0), mine `sra v1,v1,0x1f` (of v1) — different sources.
5. The pan's quotient operand order: target `subu a2,v1,v0`, mine `subu a2,v0,v1`.

So the two temporaries (the ×127 dividend and the pan dividend) swapped registers: target has the vol dividend in v1 and the pan dividend in v0; mine has the vol dividend in a1 and the pan dividend in v1.

And the magic: target a0, mine v0.

So in the target: [magic=a0, vol-dividend=v1, pan-dividend=v0]; mine: [magic=v0, vol-dividend=a1, pan-dividend=v1].

The allocation ORDER differs. This is local-alloc's qty/priority: which pseudo gets which reg.

Since the tree's asm adds an RTL insn (the copy of the vol result), the number of pseudos and their live ranges differ.

Hmm! IDEA: what if I add a copy in plain C that mimics the tree's asm (a copy of the division result into vol)?
```
s32 vq = ((0xA0 - av) * 0x7F) / 0xA0;   /* the division result pseudo */
vol = vq;                                  /* the copy (the asm's role) */
```
Then: the division result pseudo (vq) and vol (a copy of it). The copy is an RTL insn ✓ (like the asm). But vol has only 1 set (the copy) → no 2nd set → the boost isn't killed → the multiply order might break.

Hmm, but wait: in the tree, vol's 2 sets come from the asm being a tied output+input: `(set vol, vol)` — a copy of vol to itself! So the tree's RTL is: the division result → pseudo D; then `(set D, D)`? Hmm no: the asm's output is vol's pseudo and its input is vol's pseudo → `(set vol_pseudo, vol_pseudo)` — a self-copy! So the tree's RTL has the division result assigned to vol_pseudo (1st set) and then a self-copy `(set vol, vol)` (2nd set) — the second set being a self-copy that emits nothing ✓✓ and it's a real RTL insn ✓.

So the tree's structure: `vol` gets the division result directly (1 set) + a self-copy (2nd set).

In plain C: `vol = vol;` — cse removes the self-copy. BUT in a loop (do-while), cse might keep it! (cse is per-block; the loop body is a different block → the self-copy inside the loop is not merged with the outer one, and within the loop body, `vol = vol` — cse would remove it as a self-copy? Hmm, cse's "make_regs_eqv" would see the copy of vol to vol and delete it (a self-copy is removed by cse? I believe cse removes `x = x` copies).

Hmm, but earlier for item 3, `do { rgb = rgb; } while (0);` DID give a 2nd set (the boost was killed) ✓✓. So the self-copy inside a do-while survives as a 2nd set!

So for item 4:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
do { vol = vol; } while (0);   // !FAKE: do-while
```
This mimics the tree's asm exactly: vol gets the division result (1 set) + a self-copy in the loop (2nd set) — and the copy is a real RTL insn in the same place.

Let me try that! And also the variant `do { vol = (s32)vol; } while (0);`.

Let me try it.
