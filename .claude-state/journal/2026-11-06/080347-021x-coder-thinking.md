---
ts: 2026-11-06T15:03:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RC3fEzkx57UJ5awZjEJl
---
Only two lines differ, so the rest is identical: meaning in mine, the `sll a2,a2,0x8` appears elsewhere (at 219?) identical to target's 219? And target's andi appears at... hmm, if mine's 219 == target's 219 and mine has an extra andi at 218 and target an extra sll at 218, then at 219+ they align. That means both have both instructions but swapped between 218 and 219? No, then diff would be 2 regions or the aligner would show 217:220.

Whatever: the net is that the andi sits one slot earlier than the sll. In target the delay slot gets the sll; in mine it gets the andi. So I need the andi to not be available for the delay slot, or to be scheduled later.

Idea: put the u16 cast where it can't be hoisted... e.g. make vol's mask part of the call expression instead: `func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);` — the andi is already there.

Alternative: make the 2nd set of vol be a real computation that produces an insn far from the tail... but count must stay 237.

Hmm. Alternative: use a 2nd set of `sx` instead? The lever's purpose is to stop sched1 hoisting the PAN multiply ahead of VOL's. A 2nd set of vol is one way; another is to reorder statements: compute pan (sx) first, then vol — but then target's order... target has vol first then pan (per comment). Actually target: the vol multiply (mult v0,a0 at 211) before pan (mult v1,a0 at 207?) no.

Let me think about what actually differs in the schedule: With u16 (237, score 2) the ONLY difference is one slot's content. So the schedule is otherwise perfect. Good candidate.

How to get the sll into the delay slot instead of the andi? The andi is `vol = (u16)vol` → andi a1,a1,0xffff. In target, the corresponding position has sll a2,a2,0x8 which is `sx = sx << 8`.

If the andi were not there at all we'd be at 236 (a1 case). So we need an insn that's a real 2nd set of vol but NOT available before the branch... hmm, everything before the branch is available.

Alternatively: make the 2nd set of vol be something scheduled later — e.g. `vol = vol & 0x7F;` (vol ≤ 0x7F always, since ((0xA0-av)*0x7F)/0xA0 ≤ 0x7F when av≥0). andi a1,a1,0x7f — still same insn type, same position likely.

Different approach: what if the 2nd set is of the *pan* value, i.e. sx? Then the andi-like insn applies to a2 and might merge with the sll? e.g. `sx = sx << 8;` already. Hmm.

Another approach: avoid the extra insn by making the 2nd set be a value-preserving no-op that gcc can't delete but that emits no insn... The andi is the problem because it's an insn. What about `vol = (s32)(u16)vol;` same thing.

What about using the *other* direction: make the vol division emit a 2nd set naturally: split `vol = ((0xA0 - av) * 0x7F) / 0xA0;` into `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` — c_split gave 236/30. Hmm, no.

What about making vol's computation into a compound: `vol = ((0xA0 - av) * 0x7F); vol /= 0xA0;` same.

Let me reconsider: maybe the extra insn isn't needed at all; instead the 236-ins body needs the hazard nop. The missing insn in a1 is the `nop` after a mult (mfhi hazard). GCC inserts those automatically. In mine (236), the mult/mfhi sequence differs so no nop needed.

The real goal is the exact schedule. With u16 we're 1 slot off — very close.

Options to try:
1. `vol = (u16)vol;` placed AFTER `sx = (sx + 0xA0) / 0x14;` (i.e. later) — the andi then can't be in the delay slot... but it must be before the use. Let's try moving the cast down just before the call: `vol = (u16)vol;` right before func_8002D4C8. Then sched1 may still hoist it.

2. Instead of casting vol, cast the whole expression at the call: `(vol | (0x3000 | sx)) & 0xFFFF` is already there.

3. `vol &= 0xFFFF;` compound — same andi.

4. Use `do { vol = (u16)vol; } while (0)` — splits EBB; maybe the andi then isn't hoisted into the delay slot.

Let's try: c_u16dw (do-while around cast), c_u16late (cast after pan), and maybe c_u16_7f (mask 0x7F).

Also consider `sx` 2nd set: `sx = (s16)sx;`?

Let me generate a few. I need to place the cast at different spots — mk.py replaces the launder block, so I can put multiple lines there including the pan computation reordered.

Candidate "u16dw": `do { vol = (u16)vol; } while (0);  // !FAKE: do-while`
Candidate "u16x2": `vol = (u16)vol; sx = (s16)sx;`? no, sx 2nd set may add insns.

Candidate "u16b": cast vol AFTER the pan block, i.e. replace the launder with nothing and insert cast before the call. That requires two edits; mk.py replaces one region. I can put in the snippet: the launder replacement = `sx = (sx + 0xA0) / 0x14; if...; sx = sx << 8;` reordered... messy.

Simpler: write candidate c_u16late by editing a copy of c_u16.c: move `vol = (u16)vol;` line down. Let me do that with a small python script or Edit.

Let's first try cheap variants: u16dw, and mask 0x7F, and `vol = (u16)vol | 0;`.

Actually here's a thought: the andi taking the delay slot means sched1/reorg considered it a better fill. If we make the andi *not dead* on the fall-through... In target the sll goes in the delay slot because it's dead on fall-through (reorg steals only if the insn's effect is safe). The andi a1,a1,0xffff is also safe.

What if instead we use a 2nd set that is NOT safe to speculate, e.g. a division? That would add insns though.

Alternatively, maybe target's actual mechanism is that the andi is *after* the call arg or... 

Let me look at target's listing to see where its andi is. I can dump the target object? The target is build/... the banked object. delever_search --explain? Hmm.

Maybe simpler: run dt with a candidate that's the orig (control) — score 0, no diff. To see the full listing I'd need --keep and objdump.

Is there a tool to dump both? tools/cc1_dumps_tu.sh + hdump.sh give rtl dumps. The brief mentions `.run/P40/T10/hdump.sh` (header pass dumps). For body-level RTL, delever_search --keep prints the candidate object path.

Let me consider the time budget: 20-30 min per item, 5 items. Item 1 started 08:00. It's ~08:07 now. I have time.

Let me try a handful more variants quickly.

Variant ideas that add a zero-insn 2nd set:
- `vol = (u16)vol;` → andi (score 2) ✓ near
- `vol = (s32)(u16)vol;` → same
- `vol = (u16)(vol);` same
- `vol = vol & 0xFFFF;` same
- `vol = vol & 0x7F;` → andi 0x7f
- `vol = vol % 0x10000;`? no.
- `sx = (s16)sx;` before pan division: sx is s32; (s16) cast adds sll/sra? probably.

Better idea: make the *pan* multiply the one that's affected. The comment says sched1 hoists PAN first. With u16 we got the right order (only 1 slot off). The remaining issue is just the delay-slot fill. Perhaps a different real 2nd set of vol will produce an insn that is NOT a valid delay fill, e.g. `vol = vol / 1;`? folds. `vol = vol * 2 / 2;` adds insns.

What about making vol's 2nd set be a *use* that must stay after the branch? Hmm.

Alternative: change what fills the delay slot by making the sll come earlier in the source so it's more attractive? Actually reorg picks the first eligible insn from the block end. If both andi and sll are eligible, order matters.

What if we move the pan shift `sx = sx << 8;` to be the LAST statement before the call (it already is, after the if). The andi from the cast is before it in source, so reorg's backward scan finds the sll first... but it found the andi. Because the andi is *later* in RTL? The cast line is before `sx = (sx + 0xA0) / 0x14;`. Hmm, but the vol division's mfhi comes late, so the andi may be emitted after in the schedule.

Try: put the cast immediately after the vol division but as the LAST thing before the call? i.e. move the cast to right before func_8002D4C8: then in RTL the andi is last, reorg scans from the end: andi is last → even more likely to fill. Hmm, bad.

Try the opposite: put the cast earlier — right after `vol = ...` it already is.

OK, alternative: mask on the call arg instead of vol: `func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);` already.

Hmm, what about making vol u16 *declared* as u16? `u16 vol;` — then the assignment `vol = ((0xA0-av)*0x7F)/0xA0;` stores into HImode, and the arg uses it. That's a width change (C0505 catalog: s16/u8 widths). Then no explicit andi needed? The value is truncated at the store: gcc would emit andi or just use the low half. Let's try `s16 vol;`/`u16 vol;` — HImode pseudo; the division computed in SImode then truncated. Might emit the same andi.

Let me just batch: u16dw, u16_7f, hvol (u16 vol declared), and also "u16 + sx shift moved before the if"? 

Also: maybe reverse — put the 2nd set on the *pan* (sx) side, which is what the target's delay slot contains. If sx gets a 2nd set (e.g. `sx = (s16)sx;` before `sx << 8`), sched1's birth boost on the pan multiply dies and maybe the order works with no extra insn... but the sll then...

Let me just try a batch of 6.
