---
ts: 2026-11-06T18:41:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_avqr5a3w90EVMgPvcrLY
---
The orig RTL: insn 55 (77 = symbol), 57 (asm using 77), 60..., 94 (a0 = a0), 96 (a1 = 77), ...

The asm is a volatile insn. In sched1's backward pass, the asm is a barrier: sched1 has special handling — `sched_analyze` treats volatile asm as using all memory; and there's the `SCHED_GROUP_P`? Also, importantly, in `sched_analyze_1/2`, for a volatile ASM, it adds dependencies on all pending memory operations.

Why did the asm end up at position 6 in the final order (right after 55)? Because sched1 must keep the memory operations' order: the asm is a memory barrier; the memory ops before it (none in this block? the first block has the unkFC store) and after it (66, 88, 91, the call). Hmm, sched1 schedules backward: the last memory op is the call (100), then 91, 88, 66, then the asm 57. Since memory ops must stay in order, the asm is scheduled after (in the backward pass) the memory ops that follow it, i.e., at T-17 (after 88, 91, 66 are scheduled). That forces 55 (the asm's input) to be ready at T-18 → scheduled early in the final order.

So the asm's role: it's a memory barrier in the middle of the block, forcing the a1 materialization before it.

Real-C equivalent of a memory barrier: a memory access that may alias. Hmm — but the target's code has stores at 66 (unk14) and 88/91 (unk2/unk58). The a1 load is between the pin move (52) and the first store (66). In the final target order: 52 (move), 55 (a1), 60 (v0), 63 (s0=4), 66 (store unk14), ...

Hmm, without the asm, the a1 materialization folds into the call arg (96), which has no memory deps, so sched1 is free.

What if the a1 value were used in a memory operation? E.g., if the call's a1 argument setup involved memory... 

What if we make the call's a1 arg NOT foldable by using the value in a store address? No.

Hmm, what about the *first* call: its a1 arg is a symbol (insn 47, folded). Not helpful.

New idea: **prevent combine from folding 77 into the call arg by making the call arg an expression involving 77 twice**? e.g., `func_8012D5E4(a0, a1 + 0, a2, a3)`? The `a1 + 0` folds to a1.

What if the call takes `(s32)&D_801A15AC` directly and we assign a1 elsewhere? no.

OK, let me consider the possibility that the *original* source (the real one from the game) is exactly the orig.c minus the levers, and the target's schedule was achieved naturally because the original compiler run had... the same body. But our compile of w1 gives a different schedule. That means the levers ARE needed for this item → WALL. The shard's premise: try to crack; if not, WALL.

But wait: maybe there IS a real-C move: the target's schedule has the a1 materialization early. What if we make the a1 value used by a memory store, so that combine can't fold it and sched1 has a dependency? For example, what if the a1 value is stored somewhere? Not in the target.

Hmm, what about making a1's value the *same as* a0's? No.

Let me look at the a1 usage in the target's source semantics: a1 = (s32)&D_801A15AC is the second arg to func_8012D5E4. Nothing else.

So the only real-C lever is scheduling. sched1's order for the a1 materialization depends on it being folded into the call arg (combine). To prevent the fold, the value needs 2 uses. Without a second use, no.

BUT: what if the a1 value is used in the *same* call twice? Like `func_8012D5E4(a0, a1, a2, a3)` — no.

What if the call is made through a function pointer? `s32 (*fp)(s32,s32,s32,s32) = func_8012D5E4; if (fp(a0,a1,a2,a3) == 1)` — adds a load.

Hmm.

What if a1 is assigned from a *variable* that also has another use? E.g.:
```
s32 t;
t = (s32)&D_801A15AC;
a1 = t;
```
Combine folds t into a1 and then into the call arg.

What if t is used twice: `a1 = t; a2 = t;`? changes args.

OK, let me try a different tack: maybe the *comparison* `== 1` can be restructured so the call's result is used differently, changing the schedule. E.g., `v1 = func_8012D5E4(a0,a1,a2,a3); if (v1 == 1)`. Hmm, the target has `li v1,1; bne v0,v1` — the comparison uses v1! In the source, the comparison is `== 1` (a constant). The target's asm: `li v1,1; bne v0,v1`. Our build matches (51 insns, only the a1 order differs).

Hmm.

Let me try yet another idea: **make a1's value depend on the pin a0** so that sched1 must schedule it after the move a0=s0 and before... e.g., `a1 = (s32)&D_801A15AC;` — no dependency. If a1 were `(s32)(&D_801A15AC) + (a0 - a0)` — launder.

What about making a1's value *loaded from a table indexed by a0*? no.

Hmm, let me look at the .combine dump to see where the fold happens: in w1, combine folded `(set 77 (symbol))` + `(set (reg 5 a1) (reg 77))` into one insn. What if the *order* of the two statements made combine's fold different? E.g., if the a1 assignment were closer to the call, the fold is the same.

What if a1 is assigned *twice* (the second assignment kills the first)? e.g.:
```
a1 = (s32)&D_801A15AC;
...
a1 = a1;   // dead
```
Dead code removed.

What if a1 is assigned in the if-block and used in the if-body — same.

OK. Let me consider the possibility that the *expected* crack is the pin-related one: the item's kinds file says "keepalive" only. The pin ($4 for a0) may stay. Hmm, so the expert expects a lever-free body (keepalive gone) that scores 0. The keepalive was needed for the a1 schedule. Maybe the intended crack: remove the keepalive AND change the code so the schedule is right — e.g., the moves.md item func_801810F8's trick: "obase set right after pbase and used for the first load too".

In our case, what if we make the a1 assignment part of the *first* call's argument? Hmm.

Wait — what about the possibility of *reordering the source statements* so that the a1 assignment comes AFTER the stores but before the call? Then the natural order (without sched1 reordering) would be: ... stores, a1, call. Target: a1, v0 chain, stores, call. No.

What if the a1 assignment is placed *before* the v0 const but *after* the pin move, and sched1's tie-break keeps it there? We tested: w1 has it there in the source, and sched1 moved it late.

Hmm, the sweep included all orders and none gave 0.

Let me try the `volatile` route? Not allowed (barrier lever).

What about a `switch` or a loop? no.

What about making the a1 value used in a *second call*? no.

Hmm, let me look at the sched1 source for the specific rule that made the asm a barrier: `sched_analyze_2` for ASM_OPERANDS sets `pending_mem` deps. So any volatile asm is a memory barrier.

What about a *non-volatile* asm? Not allowed anyway.

What about a *store* that acts as the barrier? In the target's code, the store unk14 is at insn 66, after the a1 (55). If the a1 materialization were folded into the call arg (late), the store order wouldn't matter.

Hmm, unless... the call arg insn (96 in orig, 94 in w1) — in w1 it's `(set (reg:SI 5 a1) (symbol_ref D_801A15AC))`. Its position in the final schedule: after 77 (the second or). Why not earlier? Because sched1's ready-list order.

What if we add a dependency that forces 94 before the v0 chain? The v0 chain is 58..77. If 94 were scheduled before 58... 

Hmm, in the target, the a1 (55) is before 58. In w1, 94 is after 77. Both are legal.

Since sched1 schedules backward from the block end, the insns scheduled LAST (T-1..) are the block's early insns. The a1 materialization (94) became ready only when the call (100) was scheduled at T-3. So it can't be scheduled before T-4 at the earliest. The final order position of 94 = block_end - (T-4) ... The block has ~20 insns; T-4 → position ~17. To get 94 at position 5, the call must be scheduled at T-18, i.e., the call must be one of the LAST insns scheduled in the backward pass = one of the FIRST insns in the final order. That's impossible: the call must come near the end of the block (it's the last memory op).

Wait, that's not right: in the orig, the a1 insn 55 is scheduled at T-18 and the call at T-3. The a1 became ready at T-18 because of the ASM (57), not the call. The asm was scheduled at T-17.

So without a barrier before the v0 chain, the a1 materialization can't be early. Unless the a1 materialization is NOT folded into the call arg: if insn 55 (the symbol_ref) exists as a separate insn, it still has only the call-arg use (96), so it becomes ready when 96 is scheduled (T-5) → scheduled at T-6ish. Still late.

So the target's early a1 REQUIRES the asm barrier. Without any barrier, sched1 will always place it late. Therefore this item is a WALL unless a real-C barrier exists.

Is there a real-C barrier that isn't a lever? A function call is a barrier — but there's no call at that point in the target.

Hmm, wait: what about the *first* call (func_8012B1B4)? It's before the a1 assignment. No.

What if we restructure so that the a1 value is used by the first call? The target's first call uses D_801A1590. Hmm.

I'm now fairly convinced item 1 is a WALL: `sched1-barrier` / `sched1-const-hoist`. The keepalive asm was the only thing pinning the a1 materialization before the v0 chain; lever-free, combine folds it into the call-arg move and sched1 places it late (score 4).

Wall tag: something like `sched1-argcopy-hoist`? walls.txt has "sched1-argcopy-hoist sched1/reload_cse arg-copy hoisted/sunk across the call setup (T10 S01)". Hmm, that's close: the a1 arg copy is sunk to the call setup. But the mechanism here is combine folding + sched1. Let me use `sched1-callarg-sink` (new tag: `<pass>-<what>`).

Before declaring, let me try a few more creative real-C ideas:

1. Make the a1 value used by the unk58 store's *value*? no.
2. Split the v0 chain into a do-while (w2 gave 9).
3. Make the a1 value used in the condition of the first if? no.
4. Make the call's a1 argument a *variable that is live across a store*: e.g., assign a1 before the first store and use it after → same.
5. **Use the a1 variable in the first call as well** — let me test this: assign a1 = &D_801A1590 before the first call and pass a1; then a1 = &D_801A15AC. Maybe the reuse creates a different pseudo structure (a1 live across... no).

6. **Make the a1 value an argument to func_8012B1B4 too**? no.

7. **Compute a1 earlier and store it in a stack slot**? adds insns.

8. What if we make a1 an s32 variable assigned inside the if, but *also* referenced in the first call's second argument: `func_8012B1B4(s0, (void *)a1)` where a1 is assigned &D_801A1590 just before? Then the a1 variable has two defs and two uses (both calls). The second def's value is used only at the second call → still foldable.

Hmm, what if the second call's a1 arg uses a *different* variable that is live across the first call? E.g.:
```
a2 = (s32)&D_801A15AC;   // a2 live across the first call
func_8012B1B4(...);
...
func_8012D5E4(a0, a2, a2b, a3)
```
That changes which register gets the symbol. No.

9. What about making the a1 symbol_ref *not* foldable by using it in an address calculation that stays: e.g., `s32 a1p = (s32)&D_801A15AC;` then `func_8012D5E4(a0, a1p, a2, a3)` — combine folds a1p into the call arg.

10. What if we pass the address of a *local*? no.

Let me try #5 and a variant where the a1 value is used in the first call's delay... no.

Actually, let me look at this from the angle of: what if the a1 materialization is *hoisted* by cse to the top? cse's constant propagation: `(set 77 (symbol_ref))` — cse might hoist the symbol_ref to the function's entry (cse hoists loop-invariant/constant expressions?). No, cse doesn't hoist.

OK, one more idea: **make the a1 value's insn have a dependency on the pin move (52)**. E.g., if a1 = (s32)&D_801A15AC + (s32)a0 * 0? launder. Or if the address expression involves a0 legitimately? The address D_801A15AC is absolute.

I'll accept the WALL. But before that, let me try one experiment: does a *volatile-free* memory store before the a1 assignment help? E.g., moving the unk14 store BEFORE the a1 assignment (source order): the sweep included those orders (C before B) and none scored 0. But the sweep kept the a1 assignment in the RTL position; combine still folds.

Hmm, what if the a1 assignment is placed *after* the first store and the store is a memory barrier for sched1? In the sweep, orders with C before B (store before a1) — e.g., A,C,B,... — scored 4 or worse. So no.

Let me also try the "two calls" idea quickly and then finalize the WALL.

Actually, let me reconsider the problem statement: the item's kind is "keepalive" — the goal is a win.c scoring 0 with no keepalive. If it's a WALL, I record it. The expert's list.tsv has "keepalive" and "38" (maybe a priority/attempt count?). Fine.

Let me do a couple more tries (5-10) with:
- a1 reused across the first call
- the a1 value assigned via a temp used at the call
- the call result comparison restructured (v1 = call; if (v1 == 1))
- the call split: `v0 = func_8012D5E4(...); if (v0 == 1)` — the target has v0 directly.

Then WALL. Time: 11:41. Started item 1 at 11:30 → 11 min. The WALL needs ≥20 min and ≥30 tries. I have 186 tries; I'll continue until 20 min (11:50) with meaningful attempts.

Let me try the call-result restructure and the a1-reuse.
