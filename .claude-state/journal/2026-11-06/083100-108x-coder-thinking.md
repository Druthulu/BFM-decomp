---
ts: 2026-11-06T15:31:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_N1w3GtmSsaHO86m9Se2V
---
nolaunder = 30 (236 ins, one short). a2 = 2 (237 ins). So a2's andi restored the count and nearly everything.

Let me look at a2's full diff more carefully — maybe there's a variant where the andi lands in the right slot.

The a2 diff:
- mine[217] bne a2,v0,5130 vs target bne a2,v0,5134
- mine[218] andi a1,a1,0xffff vs target sll a2,a2,0x8

So in mine, at 5128 there's `andi a1,a1,0xffff` and the target has `sll a2,a2,0x8`. The branch target differs: mine's bne goes to 5130, target's to 5134. So mine's `li a2,15` / `sll a2,a2,0x8` / `li a0,2715`... layout differs by one slot.

Let me dump a2's tail.

Actually, let me think: a2 = `vol = vol & 0xFFFF;` after the vol computation, with the call unchanged `(vol | (0x3000|sx)) & 0xFFFF`.

gcc merges the two masks? The final `& 0xFFFF` applies to the OR result. `vol & 0xFFFF` then `| ...` then `& 0xFFFF` → the first mask is redundant (AND before OR doesn't preserve). Hmm, actually `((vol & 0xFFFF) | X) & 0xFFFF` = `(vol & 0xFFFF | X) & 0xFFFF` — the first mask is redundant since the final mask covers it. gcc may have removed the redundant mask and instead the andi we see is the final one, but scheduled early.

The `andi a1,a1,0xffff` at 5128 operates on a1 — in the target, a1 is the vol value (the OR result is in a1). So the andi at 5128 in mine is `a1 = a1 & 0xFFFF` where a1 = vol? Let me check: at 510c `subu a1,a0,v1` — a1 = vol. So `andi a1,a1,0xffff` masks vol early (that's our `vol & 0xFFFF`), and then the final `& 0xFFFF` (the call's) must have been removed (merged). Then at 5138 `ori a1,a1,0x3000` and 513c `or a1,a1,a2` — the OR result isn't masked (the final mask was merged into the early andi). Hmm, but that's incorrect? `(vol & 0xFFFF | 0x3000 | sx) & 0xFFFF` vs `(vol & 0xFFFF) | 0x3000 | sx` — the sx part is `sx << 8` where sx ≤ 0xF → ≤ 0xF00, so no high bits. And 0x3000 is within 0xFFFF. So the final mask is redundant given vol is masked. gcc merged them correctly.

But the target keeps the final mask at the jal delay slot (5144). So the target's code is `((vol | 0x3000 | sx) & 0xFFFF)` with the andi after the or. Mine moved the andi before the ori. That's a scheduling/allocation difference.

To match, the andi must apply to the final OR result. So the 2nd set of vol should NOT be a mask that merges. 

What if the 2nd set is a mask that does NOT merge with the final mask, e.g. `vol = vol & 0xFF00;`? That changes the value (clears low bits) — not equivalent. No.

What about `vol = vol ^ 0x10000;`? That changes bit 16, which is masked out by the final `& 0xFFFF` → equivalent! And it would emit an `xori`/`lui`... Actually `vol ^ 0x10000` requires a 32-bit constant → lui + xori? Or since 0x10000 needs lui: `lui at,1; xor a1,a1,at` — 2 insns. Bad.

What about `vol = vol + 0x10000;`? also 2 insns.

What about `vol = vol ^ 0x8000;`? changes bit 15 → NOT equivalent after masking.

Hmm.

What about giving vol a 2nd set that is a *copy to a new variable* and back? e.g. `{ s32 v2 = vol; vol = v2; }` — gcc would fold the copy chain to nothing.

What about using the fact that the final mask makes vol's upper bits irrelevant: `vol = vol << 0;`? folds.

Hmm. What if the 2nd set is `vol = vol | (sx & 0)`? folds.

Let me think about a2's near-miss differently: maybe a different *mask width* or placement gives the right schedule. E.g., `vol = (u16)vol;` — same as & 0xFFFF (a2). 

What about applying the 2nd set to a *different expression* that gcc keeps as a separate andi at a different place? E.g., `vol = vol & 0xFFFF;` placed *after* the pan computation (before the call) instead of right after the vol computation? Then the 2nd set wouldn't kill the birth boost (it's after the pan multiply)... hmm, actually sched1's birth boost is about the *first* set's birth. A 2nd set anywhere before the use would make vol multi-set, killing the boost. But the position affects scheduling.

Wait — in a2, the 2nd set is right after the vol computation (line 88), which is what kills the boost. If I move the mask to just before the call, does the boost still die? The boost is a priority boost applied to the insn that births a value; if the value has multiple sets, sched1 doesn't boost. The set can be anywhere in the block. Let me try moving `vol = vol & 0xFFFF;` to just before the call.

Also try `vol = vol | 0x3000;` moved around.

Let me create:
c1: vol &= 0xFFFF just before the call.
c2: vol = vol | 0x3000 just before the call, call with (vol|sx)&0xFFFF. (a1 had it right after the computation; moving it may change the schedule.)
c3: vol = vol & 0xFFFF right after the vol computation AND the call unchanged (a2) — already.

Hmm, a2 is score 2. Let me first dump a2's full tail to see exactly what's where.

Let me dump a2.
