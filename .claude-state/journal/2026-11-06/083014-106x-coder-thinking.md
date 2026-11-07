---
ts: 2026-11-06T15:30:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IpN3snQ25WL7ud4Ycjsn
---
a1: mine is one instruction short (236 vs 237) and the ori a1,a1,0x3000 got hoisted into the bne delay slot (mine[218]), while the target has it at 5138 (after the branch). So the ori's early placement broke the layout.

Hmm. In the target, the `ori a1,a1,0x3000` is at 5138, after the branch target. The launder's 2nd set keeps vol's quotient birth boost off, so the scheduler doesn't hoist the ori.

Interesting: the target's ori is part of the call arg computation at 5138, not a separate statement.

So we need a 2nd set of vol that:
1. Kills the sched1 birth boost of the vol quotient.
2. Doesn't emit an extra instruction (or folds into the existing ones).
3. Doesn't get scheduled into the delay slot.

a2's `vol & 0xFFFF` gave an andi that got scheduled into the bne delay slot, displacing the sll.

What if the 2nd set is a *compound assignment that folds into the final ori*? The target's final op is `ori a1,a1,0x3000`. If we set `vol = vol | 0x3000;` and the call uses `(vol | sx) & 0xFFFF`, gcc might fold the ori into the call arg — but a1's diff shows the ori got hoisted early (to the bne delay slot). Hmm, the launder's effect was to keep the ori late.

Hmm, wait. Let me re-read the target: the vol quotient's magic multiply at 5100-510c, then the pan magic at 5110-511c. The launder's 2nd set kills sched1's birth boost so the VOL multiply stays first. In a2, the residual is only the andi/sll swap — so a2 DID kill the boost correctly! The remaining issue is just the extra andi's scheduling.

So a2 is the right idea; I need to make the mask not add an instruction (or fold it into the final andi without changing the schedule).

In a2, gcc merged `(vol & 0xFFFF)` with the call's `& 0xFFFF` into one andi, but placed it early (bne delay slot) instead of the jal delay slot. The final andi in the target is at the jal delay slot (5144). Mine has the andi at 5128 (bne delay slot) and the sll a2,a2,0x8 displaced.

Hmm, so mine's andi is *early*. The scheduler put it early because the masked value (a1) is ready. In the target, the andi is late (in the jal delay slot) because... the `& 0xFFFF` applies to the OR result.

Wait, in a2, the mask `vol & 0xFFFF` applies to vol BEFORE the ori/or. So the andi result feeds the ori → it must be early. But gcc merged the two masks? If it merged, the andi would apply to the final OR result → late. But the diff shows mine's andi at 5128 in the bne delay slot — that's early, applying to... hmm, `andi a1,a1,0xffff` — a1 is the OR result? If the andi is on a1 (the final result), then it's the merged mask, placed early (but a1 isn't ready until after the ori at 513c...). Confusing.

Let me just dump a2's tail to see.

Actually, let me think differently: maybe use a 2nd set that folds to nothing at the RTL level but still counts as a set. What about `vol = vol + 0;`? The front end folds. `vol = vol * 1;` folds.

What about `vol = (vol);`? folds.

What about `vol = -(-vol);`? maybe not folded? For vol = -(-vol) → gcc might keep `negu` twice (2 insns). Bad.

What about a *bitfield* assignment? no.

What about `vol = (s32)(s16)vol;`? Let me test — it might emit sll+sra or fold to nothing. If it folds to nothing, no 2nd set. If it emits 2 insns, worse.

What about `vol = vol | 0;`? folds.

Hmm, what about using a *different variable* as the 2nd set target that cse/sched treat as vol? No.

Let me look at the actual sched1 mechanism: the "birth boost" is a priority boost for the insn that births a value. A 2nd set makes the value multi-set, so no single birth. The launder's asm set does that. Any plain-C set of vol (even a no-op that survives to RTL) would work.

Does a no-op set survive? `vol = vol;` — the front end may keep it as a self-set in RTL? Let me test: `vol = vol;` after the computation.

If it survives to RTL, sched1 sees two sets → no birth boost. Then flow/cse delete the self-set. That's the C0414-style dead-reset but with the same value.

Let me test:
b1: `vol = vol;`
b2: `vol = vol + 0;`
b3: `vol = (s32)vol;`
b4: `vol = (s16)vol;`
b5: `vol = vol & -1;`
b6: `vol = vol | 0;`

Let me test these.
