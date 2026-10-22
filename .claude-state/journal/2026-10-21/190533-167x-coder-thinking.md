---
ts: 2026-10-22T01:05:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_wMr8r1YDCWRUoFeiOeSQ
---
I need to fix rows 2 and 4 (the WALL rows for func_8018656C and func_8017D73C which are now MATCHes). Let me rewrite the whole file with the corrected rows (the file is mine, so rewriting is fine — but the instruction says items that already have a results.tsv row are done: skip them. Hmm, that rule is for *other* shards/agents. I'm correcting my own rows.)

Let me rewrite results.tsv with:
1. header
2. func_8018656C: MATCH, best 0, tries ~50, wall -, evidence
3. func_80183098: WALL (still), best 10, tries → need ≥30 tries! I only did 3 + 8 combos + ... let me count: c1, c2, c3 (3) + 8 variants + 24 combos = 35 ✓. Let me count precisely later.
4. func_8017D73C: MATCH, 0, 44
5. func_8018CDEC: MATCH
6. func_8017D9D8: MATCH
7. func_8017EF0C: MATCH
plus the rows for the remaining items as I finish them.

Let me now rewrite the file with the corrected rows and continue with the remaining items: func_8017D96C (2), func_8017EA24 (3), func_801813B0 (1?), func_80183098 (5?), func_8018C730 (6), func_80191020 (2).

Let me check func_801813B0's best: the combos showed 1 (dowcastu16). Let me try the posgen for it (12 asm sites → the product would be huge; my posgen caps at 96 combos). For func_801813B0, the 12 asms are all on `v`. The "cast" replacement at all 12 sites... hmm, the combo "dowcastu16" (the do-while + a (u16) cast at all 12 sites) scored 1.

Hmm, the earlier diagnostic showed the *number* of asms matters (12 asms = the target). A do-while at each of the 12 sites adds 12 *statements* — each do-while(0) creates a loop → the refs... hmm.

Let me run posgen on func_801813B0 (12 sites → the product is 5^12; my cap takes the first 96 = mostly "none" for the later sites). Hmm, that's not useful. Let me instead write a targeted generator: for the 12 sites, the replacement can be "dow" or "cast" or "dowcast" *uniformly* (all sites the same) — plus a few mixtures. And the count of sites replaced matters (e.g. only the first k).

Let me write that: for k in 1..12, replace the first k sites with "dow" (or "cast"/"dowcast") and score. That's 12 × 3 = 36 variants. Let me do it for func_801813B0.

Also for func_80183098 (the address launder): the best is 5 (castu16). Hmm, the cast on `cam` (a pointer!) → (u16)cam truncates the pointer → NOT value-preserving. Hmm! But the score is 5, not 0, so it's not a match anyway.

For func_80183098, the address opacity is the blocker. Hmm, but let me think again: the target needs `lh v1,4(s1)` — the base reg with an offset. cse rematerializes the +4 address. Hmm, what if the *offset* were not constant? Hmm.

Hmm, what about the "pointer reuse" move: what if the y load went through a *different* pointer variable that is a *copy* of cam (so the address is reg+4 of a reg whose content is... the same constant). Hmm.

Hmm, what if the pointer were obtained by a *pointer-to-pointer* load? no.

Let me think about the do-while: does it block cse's find_best_addr? The do-while creates a block boundary; cse's find_best_addr works per basic block. Hmm! The target's y load is in the same block as the x load. Hmm.

Let me try: for func_80183098, a do-while placed between the x and y loads (in the guard section) + the cast... The combos gave 5 (castu16) and 10 (dow). Let me look at the residual of the dow variant to see what's left.

Let me first handle the results file rewrite, then continue with the items.

Actually, time check: it's ~00:15 now (started 18:20). I've been at this ~6 hours. 4 items left to finish (D96C, EA24, 813B0, 83098, C730, 91020 = 6 items). Let me be efficient.

Let me do the posgen/targeted generators for the remaining items in one batch, then record everything.

Plan:
1. func_801813B0: targeted generator (the number of replaced sites).
2. func_80183098: the do-while in the guard section between the loads; the cast on cam.
3. func_8017D96C / func_8017EA24: at score 2/3; try the posgen (done for D96C: best 2) and EA24.
4. func_8018C730: 6 (the dead constant) — the return-type trick doesn't work. Hmm.
5. func_80191020: 2 (the castu16 on vol — vol is a volume value (0..127?) → (u16)vol is value-preserving if vol ≥ 0! vol = ((0xA0 - av) * 0x7F) / 0xA0 → 0..127 → (u16) is a no-op ✓). Let me look at its residual.

Let me start with func_80191020 (score 2) — the residual was:
```
replace mine[136:138] target[136:138]
    136  bne a2,v0,cb0 | bne a2,v0,cb4
    137  andi a1,a1,0xffff | sll a2,a2,0x8
```
So the target has `sll a2,a2,0x8` where mine has `andi a1,a1,0xffff`. This is the "sx = sx << 8" (in place, so reorg can steal it into the bne delay slot) — the source comment says: "sx = sx << 8; /* in place, so reorg can steal it into the bne delay slot */".

So the target: `sll a2,a2,0x8` in the delay slot of the bne; mine: `andi a1,a1,0xffff` (the mask of the other operand). So the *order* of the two delay-slot candidates differs.

The source:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
sx = sx << 8;
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
Hmm, the `andi a1,a1,0xffff` is the mask of the call argument; the `sll a2,a2,0x8` is the sx<<8.

So the two delay-slot candidates are swapped. To flip: the "statement order" move! E.g. compute the mask earlier/later.

Hmm: `(vol | (0x3000 | sx)) & 0xFFFF` — the mask is applied at the end. The sx<<8 is a separate statement.

Hmm, what if the source were:
```
sx = sx << 8;
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
(the current). The delay slot of the *call* (jal) would be filled with one of the two. The target picks the sll; mine picks the andi.

Hmm, and the launder (on vol) is what made the difference: "sched1 otherwise hoists the PAN multiply ahead of this one". So the launder's effect is on the *scheduling* of the multiply (the vol computation) — and the delay-slot choice.

With the cast (u16) on vol, the residual is the delay-slot swap. Hmm.

Let me look at the wider context of the target vs mine to see where the multiply is. Let me dump both.

Actually, let me try a few statement-order variants for func_80191020:
- move the `sx = sx << 8;` after the call? no (the call uses it).
- change `(vol | (0x3000 | sx)) & 0xFFFF` to `((vol | (0x3000 | sx)) & 0xFFFF)` — the same.
- compute the mask into a variable first: `arg = (vol | (0x3000 | sx)) & 0xFFFF;` then `func_8002D4C8(0x9E5, arg);` — hmm, that changes the shape (an extra move).

Hmm. Let me look at the target's asm around 130-140 to understand.

Let me do that now.
