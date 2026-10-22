---
ts: 2026-10-22T00:28:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_W0wNOebuQe6gayTICkHM
---
Same score 2 — the do-while didn't change the order (or the do-while was optimized away identically).

Let me try the other direction: make the load's dest have 2 sets. Idea: use the value twice — e.g. pass it to the call AND compare it? Changes the code.

Hmm, what about this: the load's dest is t. What if we make t a *struct member* or a *pointer deref*? E.g. `t = *(s32 *)((u8 *)p + 0x20);` — same.

Hmm, what if the load is written as a compound assignment on a variable that already has a value? E.g.:

```
            s32 t;
            t = ((Unkstruct_80126B58 *)p)->unk20;
```
→
```
            s32 t = 0;      /* 1st set */
            t = ((Unkstruct_80126B58 *)p)->unk20;   /* 2nd set */
```
The first set (t = 0) is dead → flow removes it → 1 set. Unless the "= 0" is used... hmm, but flow's dead-store elimination: `t = 0; t = load; use(t);` → the t=0 store is dead → removed ✓ (the doc's "flow dead-store-eliminates does NOT kill the boost").

Hmm! But wait: the doc says "REG_N_SETS is counted after cse/flow" — so a dead first assignment doesn't count.

What if the first assignment is USED? E.g.
```
            s32 t;
            t = ((Unkstruct_80126B58 *)p)->unk20;   /* set 1 */
            ...
            t = t;  /* no */
```

Hmm, what if the load is split into two loads of halves? no.

What about: the value t is used by the call AND stored somewhere else? no.

Hmm, what about the "re-tie" being replaced by a *pointer* indirection: e.g. `func_8001D0E8(t, ...)` where t is `*(s32*)&t`? Silly.

OK, different idea: what if the *call* is what moves? The target's call is at 98 with li a2 in the delay slot. In mine, the call is at 98 too? The diff shows only the load's position differing → so the rest matches. The load is at 97 in mine, 96 in the target. So mine has ONE extra instruction before the load (at 96) that the target has after.

What is at mine[96]? Let me dump my candidate to see. Let me score with --keep and dump. Actually, the diff says "insert mine[96:96] target[96:97]" and "delete mine[97:98] target[98:98]" — so mine[96] == target[97] (equal) and mine[97] = the load = target[96]. So mine[96] = target[97] = "li a1,320" ✓ (as I guessed).

So mine = [96: li a1][97: lw a0][98: jal] and target = [96: lw a0][97: li a1][98: jal].

So exactly the group order issue.

Hmm, what if the a0 setup is NOT a load but a copy from another register? I.e. if the loaded value were in a register and the call's a0 were set by a "move" — the move would be a different insn (not a load) and the group order might differ! E.g.:

```
            s32 t;
            s32 u;
            u = ((Unkstruct_80126B58 *)p)->unk20;   /* the load */
            t = u;                                   /* hmm, coalesced */
            func_8001D0E8(t, 0x140, 0xF0);
```
The copy would be coalesced away.

Hmm, what if we force the copy to survive by using t twice? The call uses t once.

Hmm, what if the value is passed through a *volatile* variable? No.

What if the call's first arg is an expression that requires the value in a specific register? e.g. `func_8001D0E8(t, 0x140, 0xF0)` vs `func_8001D0E8(t + 0, ...)`. no.

OK, alternative: make the load's dest have 2 sets by loading it TWICE (two loads of the same address)! E.g.:
```
            t = ((Unkstruct_80126B58 *)p)->unk20;
            t = ((Unkstruct_80126B58 *)p)->unk20;   /* 2nd load: CSE'd away */
```
CSE removes the 2nd load → 1 set. Hmm. But what if the 2nd load is spelled differently so CSE can't merge it? E.g. `t = *(s32 *)((u8 *)p + 0x20);` — same address → CSE merges (the alias analysis knows it's the same).

Hmm, unless the 2nd spelling goes through a `u8*` arithmetic that gcc can't fold? E.g. `t = *(s32 *)((u8 *)p + 0x20);` vs `t = ((Unkstruct_80126B58 *)p)->unk20;` — both are p+0x20 → CSE merges them (gcc's CSE works on the address expression after simplification).

Hmm, what if the 2nd load is from a *different* pointer expression that gcc can't prove equal, e.g. `t = *(s32 *)(p + 0x20);` where p is u8* → p+0x20 = the same address → CSE merges.

OK. What about making the second set a *store* of the value? e.g. `*(s32*)somewhere = t;` — extra store → count mismatch.

Hmm.

Let me reconsider: maybe the load's position is controlled by something else: the load feeds the call; the call is in a group. What if the *call* is not in a group because the args are set up differently? E.g. if the args were computed by a nested expression:
```
func_8001D0E8(((Unkstruct_80126B58 *)p)->unk20, 0x140, 0xF0);
```
Then the load IS the a0 setup (same).

Hmm. What if the value is loaded into a variable that is used by TWO calls? Then the load wouldn't be in either call's group (it'd be before both). E.g.:

Hmm, the function has one call with t.

OK, let me consider the "birth boost" kill via a *different* mechanism: the doc says the boost applies when REG_N_SETS(dest)==1. What if the load's dest is a HARD register (pinned)? Then... the boost applies to hard regs too (per the correction). Hmm.

What if the load's dest is a pseudo with 2 sets because the value is loaded and then *stored to memory*? no.

Hmm, let me look at this from the "what if the score-2 residual is acceptable as PARTIAL?" angle: PARTIAL requires the win.c to score 0. Score 2 ≠ 0. So no.

Time check: I need to wrap up. Let me try 2 more quick variants for item 7 and then move on:

V2: Make the load's dest a variable that is assigned in two places: e.g. hoist the load to the top of the function where t is also assigned? no.

V3: Swap the roles: use a *pointer* to the value: e.g.
```
            s32 t;
            t = ((Unkstruct_80126B58 *)p)->unk20;
            func_8001D0E8(t, 0x140, 0xF0);
```
→ what if the call's arg is `*(s32 *)&t`? no.

V4: What if the value is loaded via a *volatile* pointer? no (new lever).

V5: What if the second arg is a variable instead of a constant? Then the arg setup order might change... e.g. if 0x140 were a variable, its setup would be a different kind of insn. Hmm, that changes the code (the target has "li a1,320").

Hmm, V6: What if the call is `func_8001D0E8(t, 0x140, 0xF0);` but with t declared as `s32 t = 0;` at the top of the block and the load assigned to a DIFFERENT variable that's used in the call? E.g.:

```
            s32 t;
            s32 u;
            t = 0;                       /* set 1 (dead → removed) */
            u = ((Unkstruct_80126B58 *)p)->unk20;
            t = u;                       /* hmm */
```
no.

Let me try the simplest thing that could kill the boost: give the load's dest a 2nd set via a compound assignment on t where the operation is REAL but the value is preserved. Hmm: `t &= -1;`? For an s32, `t & -1` = t → folded.

What about `t = t | 0;`? folded.

Hmm, what about a *shift* by 0? folded.

So any no-op folds. The only real ops change the value.

=> The 2nd set must be a *copy* that survives: `u = t;` where u is used later. But u's use must exist.

Hmm! What if u is used by the call as the SECOND argument? No (semantics).

Hmm, what about the "ref boost" trick from the T10 example: "do { r = p + i; } while (0);" — a do-while containing a real assignment, which adds a ref to p and creates a loop shape. In our case:

```
            t = ((Unkstruct_80126B58 *)p)->unk20;
            do { t = t; } while (0);   /* !FAKE: do-while */
```
Hmm, `t = t` inside a do-while: the loop's body assigns t = t (a self-copy) → gcc would remove it (no-op) → hmm, but inside a loop, flow might keep it? "t = t" is a no-op copy → gcc's cse removes it.

What about:
```
            do { u = t; } while (0);
```
where u is a fresh variable that's otherwise unused → the assignment is dead → removed.

Hmm.

What about the ref-boost trick on a *different* variable to change the priorities? E.g. boost the priority of the load's chain? Hmm.

Let me try a different tactic for item 7: what if the ORDER of the two statements (the load and the call) is changed so that the load is not immediately before the call? E.g., move the `t = ...` assignment to BEFORE the `if ((func_80029178(0xB3) & 0xFF) != 0) {` block? Then the load is far from the call → definitely not in the call's group → and it might be scheduled early (but the target has it at 96, right before the call).

Hmm, but if it's not in the group, its position = its source position (or boosted → just before its consumer = the call's a0 setup). Hmm, the boost makes it sink to just before the consumer — the consumer is the call's arg setup → the same place. Hmm.

But if the load is boosted, it sinks to just before the call's arg-setup group. In the target, the load IS right before the group (li a1 at 97, jal at 98) — hmm, and the li a2 in the delay slot.

So the target's load is exactly "just before the group" ✓ = the boosted position, but the group starts at li a1 (97). In mine, the load is INSIDE the group (as the a0 setup) at 97, after li a1.

So the difference is whether the load is counted as part of the call's arg-setup group. The group = "a call + its immediately-preceding USE argreg insns". The load sets a0 = a "USE argreg" insn → part of the group.

In the target, the asm sits between the load and the call → the load is not "immediately preceding" → not in the group ✓.

So in plain C, we need SOMETHING between the load and the call that is an RTL insn (but emits no machine code) OR we need the load to not be a "USE argreg".

Hmm! What if the load's destination is NOT a0 but another register, and the a0 setup is a COPY? E.g. if the call's arg were a copy of the loaded value:
```
            s32 t;
            t = ((Unkstruct_80126B58 *)p)->unk20;
            func_8001D0E8(t, 0x140, 0xF0);
```
The arg setup = the load (a0 = the loaded value). If instead the value were in a pseudo and the a0 setup were a "move", the move would be the USE argreg insn (in the group) and the load would be before it — but the copy would be coalesced (the load's dest and the arg reg are the same pseudo) → the load IS the arg setup.

Hmm, unless the copy can't be coalesced: e.g. if the loaded value is needed later (2 uses) → the copy survives? Hmm: if t is used by the call and also later, then the arg setup would be a copy from t's reg to a0 → the copy is a "USE argreg" insn in the group, and the load (t's def) is before the group ✓✓.

But t isn't used later in the source... Hmm! But WAIT: what if I restructure so that the value is used twice in a way that's free? Hmm, the function after the call: `*(u8 *)(p + 0x75) = 0; return;`.

Hmm.

What if the call is made with a *different* argument order... no.

OK, what about making the a0 setup a copy by passing the value through a function that returns it? no.

Hmm, what about this: the value t is a *pointer-sized* value loaded from p->unk20 — what if the source loads it as `(s32)` from a *different* address spelling that yields a 2-instruction sequence? no.

Let me try yet another angle: the group membership is determined by the RTL "USE" insns of the arg registers before the call. What if the a0 setup is a "move" from a pseudo because the loaded value is used TWICE (once by the call, once elsewhere)? We could make the "elsewhere" use free: e.g. the value could be stored to a location that's already stored? no.

Hmm, what if the value is used in the *return*? The function returns void.

What about: `func_8001D0E8(t, 0x140, 0xF0);` and later `*(u8 *)(p + 0x75) = 0;` — hmm.

OK. Time to cut losses on item 7? It's at score 2, so close. Let me try ONE more idea: the "USE argreg" insn is the load. What if the load is a *volatile* load? Then it's not a USE argreg?? Hmm, a volatile load IS still a USE of a0. But volatile loads can't be moved/merged — and the census would flag the volatile cast.

Hmm, alternatively: what if the loaded value is used by the call in a way that requires a *different* register, e.g. the arg is `t` but t is u32 and the call expects s32 → a conversion? no-op.

Hmm, what about: `func_8001D0E8(t + 0, 0x140, 0xF0);` — gcc folds.

What about making the a0 setup come from a *conditional*? e.g. `func_8001D0E8(t, ...)` where t is assigned in two branches? That changes the control flow.

Hmm, hmm. What about: the value is loaded into a variable, and the call is given a value that's the *same* but through a different variable that is ALSO used (so the copy survives)?

```
            s32 t;
            s32 u;
            t = ((Unkstruct_80126B58 *)p)->unk20;
            u = t;
            func_8001D0E8(u, 0x140, 0xF0);
```
cse: u = t (a copy) → u's use (the call arg) → cse propagates t → the copy is removed → the load is the a0 setup. Hmm. UNLESS cse doesn't propagate because... cse propagates a copy when the source is not modified between. Yeah it propagates.

So the only way to keep the copy is to have the source live afterwards. Since t's value isn't needed after...

Hmm, unless we make it needed: e.g. store t into a location that the target also stores? The target stores `*(u8*)(p+0x75) = 0` after the call. Hmm, what if we changed the order: store first, then call? That changes the target's order (the store is after the call in the target: 101 "sb zero,117(s0)" comes after the call at 98-100? Let me check: the target has 100 "j 3c60", 101 "sb zero,117(s0)" — hmm, the sb is at 101, after the jump at 100? That's the delay-slot weirdness. Actually the target: 98 jal, 99 li a2,240 (delay slot), 100 j, 101 sb zero,117(s0)?? Hmm, that means the sb is after the j — that can't be. Let me re-read:

```
 96 lw	a0,32(s0)
 97 li	a1,320
 98 jal	0 <func_8017AE2C>
 99 li	a2,240
100 j	3c60 <func_8017E780+0x30c>
101 sb	zero,117(s0)
```
Hmm, that's weird: the j at 100 with the sb at 101 as its delay slot? No: 101 would be the delay slot of the j at 100 — but the delay slot must be the instruction right after the j → 101 ✓ = "sb zero,117(s0)". Hmm, but that would execute the store AFTER the jump — in a delay slot, the store executes before the jump takes effect ✓ (that's fine, delay slots execute).

OK so the target's store is in the j's delay slot. Fine.

So there's no free use of t.

DECISION for item 7: I'll record it as a WALL with best=2 (the base, lever-free) and the tag "sched1-call-group" (a new tag: `<pass>-<what>`) — the load is inside sched1's call+arg-setup group; only an asm between the load and the call keeps it out (the target's re-tie), and no C construct does that without adding instructions.

Hmm, but score 2 is SO close. Let me try one more variant: what if the call's arguments are set up so that the load is not the a0 setup — e.g. by passing the value through a variable that is loaded in a way that produces a *different* pseudo...

Hmm, actually! What about making the load's destination a variable that is ALSO used by the *second* call in the function? Let me look at the whole function: is there another call after? The function has func_80029178, MoveImage, func_8001D0E8, func_8012C218, func_801788B8. The t load is only used by func_8001D0E8.

Hmm, what if we DUPLICATE the load for the call: e.g.
```
            s32 t;
            t = ((Unkstruct_80126B58 *)p)->unk20;
            func_8001D0E8(t, 0x140, 0xF0);
```
→
```
            func_8001D0E8(((Unkstruct_80126B58 *)p)->unk20, 0x140, 0xF0);
```
(the load inline in the call) — that's the same RTL.

OK. Let me also consider: maybe the fix is to make the load NOT the a0 setup by having the call take the value in a register that must be set up earlier...

Let me try the "1 more" variant: what if we use a temporary with a *wider* type to force a copy? E.g.
```
            s32 t;
            t = ...;
            func_8001D0E8((s32)(long)t, ...);
```
no.

I'll try one variant: put the load in a do-while(0) block (so the load is inside a loop and not "immediately preceding" the call):
```
            do {
                t = ((Unkstruct_80126B58 *)p)->unk20;
            } while (0);   /* !FAKE: do-while */
            func_8001D0E8(t, 0x140, 0xF0);
```
Hmm, that makes the load a loop → gcc would unroll/remove the loop → the same RTL. Hmm.

Alternatively, wrap BOTH in a do-while(0) — the call inside a loop → the call group... hmm, the call's arg setup would still be inside the loop.

Let me try the variant where the load is in a do-while and the call outside (V2). Quick test.

Actually, hmm, the previous do-while test (around the call) gave the same result, suggesting gcc's output was identical (the do-while was fully optimized away). So V2 would likely also be identical.

Let me think about the group differently: the doc says the group = "a call + its immediately-preceding USE argreg insns". Hmm, so what if the a0 setup is NOT a USE argreg insn but part of the call's own insn? E.g. if the arg were a *constant*... no.

What if the call is made through a function pointer variable? E.g.
```
    ((void (*)(s32, s32, s32))func_8001D0E8)(t, 0x140, 0xF0);
```
Hmm, the doc's "bb0 head-skip" and the group detection: the group is formed by the CALL insn and the USE insns of the arg regs. A call through a pointer is still a call. But the *indirect* call might have its args set up differently. Hmm, but the target's code is "jal 0 <func_8017AE2C>" (a direct call). If we use a function pointer, gcc would emit a call to the pointer (a register call) → different code. NO.

OK, let me just accept item 7 as a WALL (score 2) — actually, hmm, wait. Let me reconsider the "birth boost" for the load once more, because the fix would be exactly right if the load's dest had 2 sets.

What if the load's dest is a variable that is ALSO assigned at the top of the function with a *live* value? E.g. if the function had a variable `t` assigned earlier and used later... it doesn't.

Hmm, what if we add a use of t that is FREE in the target's code? Hmm: the target's instruction at 96 is the load; is there any target instruction that uses the same value again? The target's 96 "lw a0,32(s0)" — a0 is then used by the call. Only one use.

So in the target, the value has 1 use too. So the boost difference isn't about 2 sets of the dest — hmm! In the target, the load's dest (a0) has 1 set → boosted → priority max → placed last in the group. But the target has it FIRST in the group!

Hmm!! So in the target the load is boosted and placed FIRST? That contradicts "boosted → placed last".

Unless the group is scheduled as a unit: the group [load, li a1, jal, li a2] is placed as a whole, and the internal order is the RTL order (the group members keep their relative order?). Then in the target, the internal order = the source order (load, li a1, li a2) ✓, and in mine the internal order is (li a1, load, li a2) ✗.

So the difference is the group's internal order. In mine, the load is inside the group and got reordered within it; in the target, the load is outside the group (because of the asm) so it keeps its position.

Hmm, so in mine the group = [li a1, load(a0), jal, li a2] — the load is the a0 setup and it's placed after li a1 (the load has a higher pri due to its latency → placed later in the backward scheduler).

To fix in plain C: the load must not be the a0 setup, i.e. the a0 setup must be a COPY (a move) from another register. For the copy to survive, the loaded value must be live after the call. It isn't...

UNLESS: the copy is to a variable that's used later in a way that's free. Hmm.

Hmm, what if the value is loaded into a variable and the CALL is given a *different* register's value that happens to be equal? no.

OK, alternative: what if the load's destination register is a *hard* register (pinned)? Then the load isn't a pseudo that can be the arg setup... hmm, the call's a0 must be $4. If the loaded value were pinned to, say, $5 and then copied to $4 — the copy is a "USE argreg" ✓ and the load is separate ✓! But the copy would be a move → an extra instruction (the target has no move there). Hmm: the target's 96 is the load directly into a0. So no.

Alright: item 7 = WALL (best 2). Hmm, it's painful to leave a score-2 item as a wall, but the mechanism is clear: sched1's call+arg-setup group (SCHED_GROUP_P) puts the load inside the group; the target keeps it outside via the asm re-tie. No C construct can insert a "no-code but RTL-visible" insn between the load and the call...

Hmm, hold on! What about the C0505 catalog: "statement order"! What if the load statement is moved to a place where it's not immediately before the call — e.g. what if we move the CALL earlier and the load later? Semantics change (the call's arg needs the load).

What if we split: `func_8001D0E8(t, 0x140, 0xF0);` where t is loaded...

WAIT. What about making the *value* be loaded EARLIER (before the big block of assignments) so that at the call site the a0 setup is a COPY (because the value is still live)? No — if the value is loaded earlier and only used at the call, it's still dead after the load → the copy is coalesced.

Hmm, unless the value is live across the call because it's used AFTER the call too. The only candidate: hmm.

OK, decision: item 7 = WALL with tag "sched1-call-group" and best 2.

Hmm, hmm. But hold on. Let me reconsider the target's group: [96 lw][97 li a1][98 jal][99 li a2]. The li a2 (the 3rd arg) is in the delay slot ✓. So the group = [li a1, jal, li a2] with the load just before it. In mine: [96 li a1][97 lw][98 jal][99 li a2] — the group = [li a1, lw, jal, li a2].

What if the source order of the arg setup were different? E.g. if the call were written as `func_8001D0E8(t, 0x140, 0xF0);` the expansion order is a0, a1, a2 (left to right) — hmm, but gcc's expand_call puts the args in a specific order (often right-to-left or by the arg order). Hmm! What if we swapped the *source* order of the args: `func_8001D0E8(t, 0xF0, 0x140)`? That changes the semantics (the args are positional) — the target has a1=320 (0x140) and a2=240 (0xF0) ✓ so the source order must be (t, 0x140, 0xF0) ✓.

What if the a1/a2 constants were loaded via variables? e.g. `func_8001D0E8(t, c1, c2)` where c1 = 0x140, c2 = 0xF0 — the setup would be the same "li" insns but their source position earlier → the group order might change! Hmm: the li a1 and li a2 would be hoisted before the call (they're constants → the "constant pool" placement). Hmm, gcc puts the constants in the group.

Hmm, what if the SECOND arg were a variable that's assigned 0x140? Then the setup for a1 = "li a1,320" (a constant) — the same instruction, but its RTL position is at the variable's assignment (earlier). Then the group = [load(a0)?, li a1, jal, li a2]... hmm, the same.

OK. Let me try 2 quick experiments for item 7 and then move on:
E1: `s32 c1 = 0x140; s32 c2 = 0xF0; func_8001D0E8(t, c1, c2);`
E2: the load assigned to a variable that is used twice: hmm, no free use.

Let me do E1. Cheap.

Actually, better idea for E2: what if the load is done with a *pointer* indirection so that the "load" is a "lw" into a different pseudo and the a0 setup is a move? E.g.
```
            s32 t;
            t = *((s32 *)((u8 *)p + 0x20));
```
Same.

Let me do E1 and then move on to items 6, 1, 2 (I still have those).

Actually, let me reconsider the time budget. I've done 2 MATCHes, and I'm at ~2.5 hours. Items remaining: 1, 2, 3 (WALL likely), 4 (WALL likely), 6, 7. Let me allocate ~15 min each and be done in ~1.5 hours, then write the log.

Let me do E1 for item 7 now, and simultaneously prepare item 6 (func_80180054).
