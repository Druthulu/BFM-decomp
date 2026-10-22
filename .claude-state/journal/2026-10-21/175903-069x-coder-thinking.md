---
ts: 2026-10-21T23:59:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_r8xrfjQPjP6k90gMATm6
---
Excellent! Score 4, and the insn count matches (63 vs 63). The residual is a SCHEDULING difference: the `li v0,51` and `sb v0,39(a0)` vs the `addiu a1,s0,36` order — the target has:
```
39 lui a2,0x0 ; D_801817B0
40 li v0,51
41 jal func_80128EA8
42 sb v0,39(a0)
...
37 addiu a1,s0,36
```
Wait, the target:
```
36 move a0,s1
37 addiu a1,s0,36
38 lui a2,0x0 ; HI16 D_801817B0
39 addiu a2,a2,0
40 li v0,51
41 jal func_80128EA8
42 sb v0,39(a0)
```
and mine:
```
36 move a0,s1
37 li v0,51
38 sb v0,39(a0)
...
41 ...
42 addiu a1,s0,36
```
So in mine, the `li v0,51` / `sb v0,39(a0)` come BEFORE the `addiu a1,s0,36` (the call arg setup), while in the target they come after (the `li v0,51` is in the delay slot region: `li v0,51` at 40 and `sb v0,39(a0)` at 42 = the delay slot of the jal at 41).

So this is a scheduling/ORDER issue: the target has the call's arg setup (a0, a1, a2) first, then `li v0,51` and the `sb` in the delay slot.

In the C:
```
        q = sub;
        p = (s32)((u8 *)ent + 0x24);
        e = (s32)D_801817B0;
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        func_80128EA8(q, p, e);
```
and the `sb v0,39(a0)` is `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` → hmm, wait: `sb v0,39(a0)` — offset 0x39? Hmm, unk27 → 0x27? Hmm, the target has `sb v0,39(a0)` = offset 0x27 ✓ (0x27 = 39 decimal ✓).

So the `sb` (the unk27 = 0x33 store) is scheduled into the call's delay slot in the target, while in mine it comes before the arg setup.

This is a scheduling difference: in the target, the store is moved AFTER the arg setup (into the delay slot). In mine, the store is before.

Why? Because in the target, the store's value (0x33) is loaded (`li v0,51`) and the store is scheduled into the delay slot of the jal. In mine, the store happens before the call setup.

Hmm, the ORDER class: "statement order IS the schedule among equal-priority insns (rank_for_schedule's LUID tie-break); do-while is a barrier".

So: the ORDER of the statements in the C affects this. In the source, the store `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` comes BEFORE the call `func_80128EA8(q, p, e);`.

In the target, the store is in the delay slot of the call — i.e., AFTER the arg setup. So the target's original source probably had the store AFTER the call! Let me try swapping:

```
        func_80128EA8(q, p, e);
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
```
Hmm, but the `sb v0,39(a0)` is in the delay slot of the jal — the delay slot executes BEFORE the call. So the store happens before the call in the target's execution order. But in the source, the store could be written after the call statement (the compiler schedules it into the delay slot, which is before the call executes).

So yes! Swapping the statements: put the store AFTER the call in the source. Then the scheduler can move it into the delay slot ✓.

Hmm, but is that semantically OK? The store to q->unk27 before/after the call — the call might read it. In the target's execution, the store happens before the call (delay slot). If the C puts the store after the call, the compiler moved it before (into the delay slot) — semantically it's a reordering, but the target's binary has it in the delay slot, so the original source had it after the call.

Also note: in the FIRST branch (the `if` arm), the pattern is:
```
        ((Unkstruct_800B5CB8 *)sub)->unk27 = 0x9C;
        ...
        func_80128EA8(sub, (s32)((u8 *)ent + 0x24), (s32)D_800D3888);
```
and the target's first branch:
```
20 li v0,156
21 sb v0,39(a0)
22 lw v0,4(a0)
...
27 jal func_80128EA8
28 sw v0,4(a0)
```
So in the first branch the store is BEFORE the call in the target (insn 21, the call at 27). And the source has it before the call ✓.

So the two branches differ! In the else branch the store is in the delay slot (after the arg setup), so the source likely has it after the call.

Let me try: swap the store and the call in the else branch.

Wait, careful: in the else branch the source is:
```
        func_8001CC3C(sub, (s32)D_801817A4, 0, 0);
        q = sub;
        p = (s32)((u8 *)ent + 0x24);
        e = (s32)D_801817B0;
        <LAUNDER>
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        func_80128EA8(q, p, e);
        hw = 0x1C;
```
New:
```
        func_8001CC3C(sub, (s32)D_801817A4, 0, 0);
        q = sub;
        p = (s32)((u8 *)ent + 0x24);
        e = (s32)D_801817B0;
        func_80128EA8(q, p, e);
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        hw = 0x1C;
```
Hmm, but that changes the semantics (the store after the call). The target's binary has the store before the call (in the delay slot). Since the compiler reorders it into the delay slot, the C's order (after) is consistent with the target's code. It's a legitimate "statement order" move (in the C0505 catalog: "a statement moved several positions down its block (R42)").

Let me test it!

Also, hmm: the "li v0,51" (0x33) — the value 0x33 = 51 ✓.

Let me write v2 with the swap.
