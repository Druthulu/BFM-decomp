---
ts: 2026-10-22T10:12:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_RdVdfMqaTPbQX4SbhewH
---
Consistent residual: the target has [addiu a1,s0,36] at 37 and [li v0,51] at 40 and [sb] in the delay slot; ours has [li v0,51][sb] early and [addiu a1] in the delay slot.

Key: in the target, the "addiu a1,s0,36" is EARLY (right after "move a0,s1"). So the p value was computed at the top of the arm.

Since the launder forced q/p/e into registers before the asm (which is placed right after the assignments), the values were computed early.

Lever-free idea: make the *p* value's computation not sinkable. What if p's value is used by something else BEFORE the call? E.g. if the source had:

```c
q = sub;
p = (s32)((u8 *)ent + 0x24);
e = (s32)D_801817B0;
((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
func_80128EA8(q, p, e);
```

Hmm, that's v1.

What if the ORDER of the assignments changed: e.g. `p = ...` FIRST, then q, then e? The scheduler might then order the addiu early. Worth testing! The scheduler's order depends on the source order of the statements (sched respects dependencies but orders independent insns by their birth order).

Hmm, in ours the order was [move a0,s1][li v0,51][sb][lui a2][addiu a2][jal][addiu a1 delay]. The "move a0,s1" is the q→a0 copy (q = sub, in s1). The addiu a1 was last.

Hmm, what if the source order were: p = ...; q = sub; e = ...? Then the addiu a1 would be born first → scheduled early ✓ maybe!

Let me test a batch:
b1: reorder the assignments: p, q, e
b2: reorder: q, e, p
b3: reorder: e, q, p
b4: p computed before q: p = ...; q = sub;
b5: the store moved to the very beginning of the arm (before q = sub)
b6: the store moved after the call but the "li" hoisted...

Also:
b7: `func_80128EA8(q, p, e)` with the args in a different spelling.
b8: the store as `*(u8 *)((u8 *)q + 0x27) = 0x33;`
b9: `hw = 0x1C;` moved before the call?
b10: the call's result used: `func_80128EA8(q, p, e);` → the target's call has no return value used.

Let me also consider: the target's arm order [move a0,s1][addiu a1,s0,36][lui a2][addiu a2][li v0,51][jal][sb delay] — the arg setup is in the natural order a0,a1,a2 and the "li v0,51" after. This looks like the arg setup was created as a *block* (all at once) — consistent with the launder's asm outputs being set up together.

Hmm! Another idea: what if the three values q, p, e are passed to the call in a way that forces them to be computed together? E.g. if the call took a struct? no.

Hmm, what about making the store's value depend on p? no.

Let me try the reordering batch — cheap and plausible.

Let me write the variants. The base for this item: v1.c (launder removed, pins kept).

Anchors in v1.c:
```
        func_8001CC3C(sub, (s32)D_801817A4, 0, 0);
        q = sub;
        p = (s32)((u8 *)ent + 0x24);
        e = (s32)D_801817B0;
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        func_80128EA8(q, p, e);
        hw = 0x1C;
```
Let me check the exact text of v1.c aroundthere.
