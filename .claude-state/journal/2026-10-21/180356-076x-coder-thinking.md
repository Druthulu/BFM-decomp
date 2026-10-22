---
ts: 2026-10-22T00:03:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_uSAAzXSdkxKTLzXYlSdm
---
Without the q pin: the store's base is s1 (not a0) → `sb v0,39(s1)` ✗. So the q pin IS needed for the store's base = a0.

So: keep the q pin. Score stays 4.

OK. So the residual is a pure scheduling difference of 4 insns in the else-arm, and the pin+launder combination is what produces the target.

Let me think about the launder's role once more: `__asm__ __volatile__("" : "=r"(q), "=r"(p), "=r"(e) : "0"(q), "1"(p), "2"(e));` — this forces q, p, e into registers. With the asm, gcc's p and e are assigned to HARD regs (the asm's outputs) — the asm's "=r" outputs with "0"/"1"/"2" matching inputs means the same reg. gcc allocates them: q → $4 (pinned), p → ?, e → ?.

The asm acts as a barrier/scheduler element: it's a real insn (with LUID) that the scheduler places. Since an asm has priority 1 (highest), it gets scheduled EARLY — before the store! And the asm's presence forces the arg setup to be computed before it (its inputs) → the arg setup is early ✓✓✓.

AH, that's the mechanism! The asm's inputs (q, p, e) must be ready before the asm, and the asm is scheduled with high priority → early. So the arg setup (p → a1, e → a2) is computed early, before the store.

Hmm, but the asm also forces the values into REGISTERS (hard regs), which is what makes the copies at the call unnecessary (the values are already in a0/a1/a2). Hmm — with the asm, p is in a1 and e in a2 (the asm's output regs are chosen to be the arg regs? no, the asm's outputs are hard regs chosen by gcc, and the call then copies them to a0-a2 — hmm, that would add moves).

Hmm, in the target, there's no extra move for the args. So the asm's output regs WERE a0/a1/a2 (gcc chose them to match the call's needs — gcc's "asm reg allocation" tries to match the surrounding uses ✓).

OK. So the lever's effect here is a SCHEDULING anchor. Without asm, can I anchor the arg setup early?

The C0505 catalog: "a statement moved several positions down its block (R42)" and "A `do{}while(0)` only with `// !FAKE: do-while`" (from the brief's constraint: "do{}while(0) only with // !FAKE: do-while" — so a do-while(0) is allowed if marked!).

Hmm! The moves.md line 4: "launder,pin | func_8017F584 | MATCH — field post-decrement per arm (f--; else f=(rand()&3)+8), spacer dropped (W01)".

And the T10 worked example: "pin removed; +1 loop-weighted ref on p via `do { r = p + i; } while (0);`" — so a do-while(0) is used as a dial (with the !FAKE marker).

Hmm! So maybe: use a `do { ... } while (0);` to anchor the arg setup early? Hmm, that would change the LUID order.

Hmm, what if the whole else-arm's arg setup is placed in a do-while(0) block? Like:

```
        do {
            p = (s32)((u8 *)ent + 0x24);
            e = (s32)D_801817B0;
        } while (0);
```
Hmm, that doesn't change the LUID order relative to the store (still before it, since the source order is the same).

Hmm, the problem is the opposite: I need the arg setup's LUID to be LOWER than the store's, which it already is in the source (q, p, e, store, call) — but gcc's SCHEDULER still scheduled the store early.

Hmm, so the LUID order IS right, and the scheduler still moved the store up. So the fix must be a priority thing.

Hmm! sched1's birth boost: the `li v0,51` "births" v0 → a high priority → scheduled early. In the target, the `li v0,51` is late (insn 40). Hmm, so in the target, the `li` did NOT get the birth boost.

The birth boost is demoted when a pseudo has "n_times_set > 1" (the C0505 note: "a second identical assignment demotes sched1's birthing boost"). Hmm! So if the value 0x33 were assigned to a variable that has 2 sets...

Hmm, the `li v0,51` is the constant 0x33 for the store. What if the store's value came from a variable assigned once but used twice? Hmm.

What if the store's value is a variable `t = 0x33` that's ALSO used elsewhere? Hmm, no other use.

Hmm, what if the value is assigned via `hw`? Hmm, hw is 0x1C in this arm.

Hmm! What about this: the target's else-arm has `li v0,44` (0x2C) in the IF-arm's delay slot and `li v0,28` (0x1C) in the else-arm. So both arms' `hw` values are `li`s. And the store's value 0x33 is `li v0,51` at 40 (late).

Hmm, in the if-arm, the store's value `li v0,156` (0x9C) is at 20 — EARLY (it's the first statement of the arm). Hmm! So in the if-arm, the `li` is early (the arm's first statement) and in the else-arm it's late (the arm's only statement before the call).

Hmm, that's consistent with "the first statement is scheduled early, the last statement goes into the delay slot".

In mine, the else-arm's single statement (the store) was scheduled EARLY (37-38) and the a1 setup took the delay slot.

Hmm! So in mine the store was treated as "the first statement" (scheduled early) and in the target as "the last statement" (delay slot). The difference: the a1 setup was interleaved.

Hmm, so in the target, the a1 setup (addiu a1,s0,36) was scheduled BEFORE the store → so the store is the last statement → the delay slot ✓.

In mine, the a1 setup was deferred → the store came before it.

Why was the a1 setup deferred in mine? Because... hmm, the a1 setup is `addiu a1,s0,36` where a1 is the call's 2nd arg reg. Hmm, and the call is at 41. The a1 setup in the delay slot is legal.

Hmm, the scheduler's choice: sched2 (the final scheduler) does the delay-slot filling. Before that, sched1 orders the block.

OK. Let me try a DIFFERENT lever: make the store's VALUE not a constant but a variable that's assigned earlier, so the `li` isn't the store's immediate value:

Hmm, in the target the `li v0,51` is right before the store, so the value IS materialized there.

Hmm.

Let me try: what if the store is written with an explicit temp:
```
        s32 t = 0x33;
        ((Unkstruct_800B5CB8 *)q)->unk27 = t;
```
Then: `li v0,51` (t's assignment) and then the store `sw`... hmm, the store's value would be a register copy → `move v0,v0`? Hmm, the store is `sb` (a byte) — the value 0x33 in a register → `sb v0,39(a0)` ✓. So: t = 0x33 → `li v0,51` (v0 = t's reg), then the store `sb v0,39(a0)` — but t and v0 might be the same reg → no copy ✓. And the LUIDs: the `li` is at the t assignment (before the store) — the same as now.

Hmm, that might change the birth boost (t's set is now a separate pseudo). Let me try it. Cheap.

Also, let me try: `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` → what if the value is `51` written differently (e.g. `0x33` vs `51`)? Same.

Let me try the temp variant (v9). And if that fails, I'll try moving the `hw = 0x1C` etc.

Actually, hmm, let me think about the DO-WHILE(0) dial from the T10 example: "do { r = p + i; } while (0);" — the do-while(0) adds a ref to a pointer inside a loop. Here, maybe a do-while(0) around the arg setup would make the arg setup a separate "region" with its own LUIDs (earlier)?

Hmm: if the arg setup is inside a `do { ... } while (0);` block placed BEFORE the store, the LUIDs of the arg setup are still before the store's. Hmm, no change.

BUT: a do-while(0) creates a LOOP → and the loop's structure changes the scheduling (loop.c, sched). Hmm! The do-while(0) would be a loop with one iteration; gcc's loop.c would optimize it away (jump.c deletes an empty do-while(0)) — the "do-while is a barrier" note.

Hmm, the R-family "R9" is "the run-split". Hmm.

Let me just try the temp-value variant and one with a do-while(0) around the arg setup. Both cheap. Actually, let me first try the temp variant since it's most likely.

Hmm, time check: it's late in my session. I have 2 more items to look at (80184828, 8017D81C) plus bookkeeping. Let me limit this item to 2 more tries.

Let me do both in one bash call (chained with &&).
