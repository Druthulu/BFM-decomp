---
ts: 2026-10-22T10:10:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ODRbJdf2ehz0wowgfLkv
---
Item 8017DA30: the else arm has a launder with 3 outputs (q, p, e) and 2 pins ($16 on ent, $4 on q).

The kinds file says "launder" only. The pins are "other rows' levers" (per the notes) — hmm, but the pins are in the same body. The brief: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." — and "CONSTRAINTS: MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added".

Hmm, the kinds file says "launder" for this item. But the notes say "plus two pins, $16 on `ent` and $4 on `q` — other rows' levers, they stay". Hmm — the pins are declared with `register s32 ent __asm__("$16")` — that's a register-asm pin. The kinds file lists only "launder" — but the pins ARE in the body. Since the kinds file says only "launder", and the note says the pins stay (they're "other rows' levers"), I should treat the pins as allowed to stay.

Hmm, but the brief's CONSTRAINTS say "no pin (register-asm/__asm__ reg steer)" as part of the lever-free definition for the kinds in the row. Since the row's kind is "launder" only, the pins may stay. The notes explicitly say they stay. OK.

So the goal: remove the 3-output launder asm and still score 0.

The residual (best 4): ORDER — the target has the call's arg setup at the top of the arm and the store in the delay slot; ours has `li v0,51`/`sb v0,39(a0)` early and `addiu a1,s0,36` in the delay slot.

Wait, `sb v0,39(a0)` — the store's base is a0?? Hmm, the target's store `sb v0,39(a0)` — hmm, but the call's first arg is q (in $4 = a0). So the store is through q (a0) at offset 39 = 0x27 → `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` ✓ (unk27 is at offset 0x27).

So the target:
```
move a0,s1        ; q → a0
addiu a1,s0,36    ; p = ent+0x24
lui a2,%hi(D_801817B0)
addiu a2,a2,0
li v0,51
jal func_80128EA8
sb v0,39(a0)      ; delay slot: store 0x33 to q->unk27
```
Interesting! The store `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` comes BEFORE the call in our source but the target has it in the delay slot of the call (i.e. scheduled after the call setup).

Hmm, our version: the store is scheduled early (before the call setup) and the `addiu a1,s0,36` goes into the delay slot.

So the difference is the SCHEDULING of the store and the arg setup.

The launder's asm (with priority 1) anchors the values q/p/e in registers before the asm, which forces the arg setup to the top of the arm.

Lever-free ideas:
1. Change the statement order: put the store AFTER the call in the source: `func_80128EA8(q, p, e); ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` — the notes' v2 tried "the store moved AFTER the call" → 4 (same).
2. Use a temp for the store value: `s32 t = 0x33; ((Unkstruct_800B5CB8 *)q)->unk27 = t;` — the notes didn't try this! With a temp, the store's value comes from a reg (v0) → the scheduler might place the store in the delay slot ✓.
   Hmm, but the target's store uses v0 which holds 0x33 = 51 ✓ ("li v0,51" then "sb v0,39(a0)"). With `li v0,51` before the call and the store in the delay slot, the value must be materialized before the call. With a temp variable, gcc would put the temp in a callee-saved reg (s3?) → different asm ✗. Hmm, unless the temp is used once (then it's a pseudo → v0).
   Hmm: `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` → the constant 0x33 is stored directly: "li v0,51; sb v0,39(a0)" — the constant needs a reg anyway. So the value is already in v0.
3. The key difference: in the target, the store's BASE is a0 (=q, the call's first arg) and the store happens in the delay slot; the arg setup (a0/a1/a2) is at the top of the arm.

Hmm, the ORDER: the target's arm is:
```
[arm start]
move a0,s1
addiu a1,s0,36
lui a2,0x0
addiu a2,a2,0
li v0,51
jal func_80128EA8
sb v0,39(a0)     ; delay slot
```
So everything is set up at the top of the arm, and the store is in the delay slot.

Ours (per the notes): "ours emits `li v0,51` / `sb v0,39(a0)` EARLY (37-38) and puts `addiu a1,s0,36` in the call's delay slot".

So in ours, the store happens right after the "li v0,51" and before the arg setup. This suggests our source's statement order (store before call) leads to that scheduling.

Ideas:
- Since the store is `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` and q is pinned to $4 (a0), the store's base is a0. The call also uses a0. The scheduler must keep a0 = q for both.
- What if the store is expressed differently so that the scheduler prefers the delay slot? E.g. writing the store as `*(u8 *)((u8 *)q + 0x27) = 0x33;`? The notes' v3/v4 tried "the call's args spelled as expressions" and "the store after the call with expression args".
- What if the store is moved to the END of the else arm (after hw = 0x1C)? Hmm, that changes the order relative to the call... The target's store is in the delay slot of the call, so it's "just before" the call in program order? No — the delay slot executes AFTER the call. So the store executes AFTER the call in the target! Interesting: so in the original source, the store came after the call (or the scheduler moved it there, which is legal since it doesn't alias the call's args... hmm, but the store is to q->unk27 and the call's args are q, p, e — the call could modify q->unk27! So moving the store after the call is NOT legal unless gcc can prove no aliasing. gcc 2.7 without TBAA might still do it if the call is known not to write... hmm, gcc assumes calls may write any global memory, but q is a pointer to a heap object — gcc 2.7's alias analysis might allow it.

Hmm, actually maybe the store is NOT after the call: the delay slot of the jal executes after the call. So the store happens after the call. For that to be legal, gcc must believe the call doesn't modify *q. With the pin $4 on q, hmm.

Wait, maybe the store is to a *global*? No: "sb v0,39(a0)" — the base is a0.

Hmm, so the target's store is after the call. Our version has the store before the call (early). So we need to move the store after the call in the source, and the scheduler must keep it there (in the delay slot).

The notes' v2: "the store moved AFTER the call — 4 (the store stays after the call)". Hmm! So v2 has the store after the call but still scores 4. Let me look at v2's diff to see what differs now.

Let me run the diff forv2.
