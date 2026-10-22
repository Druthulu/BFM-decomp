---
ts: 2026-10-22T11:09:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_JcCnszX8ncR1Vk6huwk9
---
Target at 3ad4:
```
3ad4: lw a0,32(s0)     <- index ?
3ad8: li a1,320
3adc: jal func_8001D0E8
3ae0: li a2,240        (delay slot)
```

So the load `lw a0,32(s0)` comes BEFORE `li a1,320`. The candidate (without the asm) had it at index 97 — i.e., after `li a1,320`? Let's check: the notes said "the target has it at index 96, the candidate at 97".

Hmm, "li a1,320" is in a delay slot at 3ad8? No: 3ad8 is `li a1,320` and 3adc is `jal`. On MIPS, the instruction after jal is the delay slot. So 3ae0 `li a2,240` is the delay slot of the jal. So the sequence is:
- 3ad4: lw a0,32(s0)
- 3ad8: li a1,320
- 3adc: jal
- 3ae0: li a2,240 (delay)

Candidate probably:
- 3ad4: li a1,320
- 3ad8: lw a0,32(s0)
- 3adc: jal
- 3ae0: li a2,240

Hmm, but wait — the diff counts masked mismatches; a swapped pair of instructions gives 2 mismatches → score 2. And count stays 200.

So we need the load to be scheduled BEFORE `li a1,320`.

Why does the asm cause this? The asm `__asm__ __volatile__("" : "=r"(t) : "0"(t));` is placed between the load and the call. With the volatile asm, sched1 can't move the `li a1,320` (arg setup) before the asm — wait, actually it prevents the arg setup from being hoisted above the asm. Without the asm, sched1 hoists `li a1,320` up to fill the delay slot after the previous instruction (3ad0: sh v0,14(s0) — hmm, there's a delay slot there).

Let's look:
```
3acc: addu v0,v0,a3
3ad0: sh v0,14(s0)      <- the store
3ad4: lw a0,32(s0)
```
The `sh v0,14(s0)` is at 3ad0 and 3ad4 is in its delay slot! So the load fills the delay slot of the store.

And the candidate: `sh v0,14(s0)` at 3ad0, then `li a1,320` at 3ad4 (delay slot), then `lw a0,32(s0)`.

So: sched1 puts `li a1,320` in the delay slot of the store. With the asm present, the li can't go there because the asm is a barrier between... hmm.

Actually, wait: in the ORIGINAL (with asm), the target has lw in the delay slot. The asm is between the load and the call. So the sequence in the source is: load t; asm; call(t, 0x140, 0xF0).

With the asm: the call's arg setup (li a1, 320; li a2, 240) can't be hoisted above the asm (the asm is a scheduling barrier for the call group). And the load is before the asm. So the load is available, and sched1 puts it in the delay slot.

Without the asm: sched1 can hoist `li a1,320` above the load (the load only feeds a0, li a1 is independent) → li a1 goes into the delay slot.

So how do we prevent `li a1,320` from being hoisted above the load without an asm?

Option: make the load's value needed EARLIER too? No.

Option: reorder the C source so the load comes after? No, we need the load earlier in the schedule.

Option: **make the load's destination register a0 conflict**... hmm.

Option: Make the call argument order such that `a1` and `a2` are set before... no.

Key insight: sched1 groups the call with its arg setup (SCHED_GROUP_P). The load feeding a0 is part of that group too. The group's instructions are placed together. But the target has the load in the previous block's delay slot — i.e., the load was scheduled EARLIER, in a different block/group!

Ahh — that's the key: the load must be scheduled in the PREVIOUS block (before the branch/asm boundary). In the target, the load `lw a0,32(s0)` is at 3ad4 which is the delay slot of `sh v0,14(s0)` at 3ad0 — the same basic block as the store (before the asm).

So the asm creates a basic block boundary! The asm splits the block: block A ends with the store+load, block B has the call. Without the asm, the load and the call are in the same block, and sched1's group puts them together, with `li a1,320` in the delay slot.

Hmm, so without the asm we need a real basic-block boundary between the load and the call, in plain C. That means a control-flow construct! Like a `goto` or an `if` — but a branch would add an instruction.

Hmm, but what about `do { ... } while(0)`? That's optimized away but might create a block boundary early on. Actually, GCC's `do{}while(0)` is removed in the front end (jump threading) and doesn't create a block boundary.

What creates a block boundary without extra instructions? A `goto` to a label that's... hmm, a goto always adds a jump instruction unless it's the last thing.

What about a conditional with a constant condition? `if (1) { ... }` → removed in front end.

Hmm. What about restructuring so that the load is in a different block naturally — e.g., the load happens BEFORE the `if ((func_80029178(0xB3) & 0xFF) != 0) { ... }` block? No — the load's position is fixed by the target.

Wait, actually: let's reconsider. In the target, the load is in the delay slot of the store at 3ad0. The store `sh v0,14(s0)` is the last statement of the `if (func_80029178(0xB3)...)` block. Then the load + call are after the block.

In C:
```c
if ((func_80029178(0xB3) & 0xFF) != 0) {
   ... lots ...
   ((Unkstruct_80126B58 *)p)->unkE = ...;   // sh v0,14(s0)
}
{
    s32 t;
    t = ((Unkstruct_80126B58 *)p)->unk20;
    asm(...);
    func_8001D0E8(t, 0x140, 0xF0);
}
```

Hmm wait — in the target, is the load inside or outside the `if` block? Looking at the flow: `beqz v0,3ad4` at 3ae0... no. Let me re-read:

```
39dc: andi v0,v0,0xff
39e0: beqz v0,3ad4     <- if the &0xFF == 0, jump to 3ad4
39e4: li a1,832        (delay)
... (the &0xFF != 0 body: MoveImage, unkFC, unk6, unkA, unkE)
3acc: addu v0,v0,a3
3ad0: sh v0,14(s0)     <- end of the != 0 body
3ad4: lw a0,32(s0)     <- JOIN POINT (both paths)
3ad8: li a1,320
3adc: jal func_8001D0E8
```

So 3ad4 is the JOIN of the `beqz` branch and the fall-through. The `lw a0,32(s0)` is at the join — shared. It's in the delay slot of the fall-through's `sh v0,14(s0)`. That's normal MIPS scheduling: the join block's first instruction fills the delay slot of the preceding branch's delay slot / fall-through.

Hmm, so actually the load is the first instruction of the join block (the block after the if). Without the asm, why would it be placed after `li a1,320`?

Because the join block contains: lw a0,32(s0); li a1,320; jal; li a2,240. sched1 schedules within the block. The block's first instruction goes into the delay slot of the preceding instruction if it's in the same "scheduling region"... Actually on MIPS, the delay slot of the branch at 39e0 is `li a1,832` — so the branch's delay slot was filled with something from the fall-through path.

The instruction at 3ad0 `sh v0,14(s0)` is followed by 3ad4 `lw a0,32(s0)`. So 3ad4 is in the DELAY SLOT of 3ad0 (the sh). Since 3ad0 is not a branch, its delay slot can hold any instruction from the same block (the fall-through block).

So the join block starts at 3ad4 and it got scheduled into the delay slot of the previous block's last instruction.

Now, with the asm: the block structure is different! The asm splits: block A = [store sh] ... hmm no.

Hmm, wait. Let's think about where the asm is. In the source, the asm is INSIDE the `{ s32 t; ... }` block after the if. So the blocks are:
- if-block body (ends with sh v0,14(s0))
- join block: t = load; asm; call

With the asm, the join block becomes two blocks: [load] then [asm, call]. sched1 can then schedule the `load` into the delay slot of the previous block's last instruction (3ad0's delay slot), since the load is now in its own block with no other instructions competing... hmm, actually the delay slot filling happens at the RTL level after scheduling.

Without the asm, the join block is [load, call-args, call]. sched1 groups the call + arg setup together (SCHED_GROUP_P), so the load is scheduled relative to that group: it must be right before the group (a0 setup). And the `li a1,320` is part of the group. So the order within the group region: the group is [li a1, li a2, jal] with a0 = load. So load must come before the group. Hmm, but then the order would be load, li a1, li a2, jal — the target order is load, li a1, jal, li a2 (delay).

Candidate order (without asm) per notes: index 96 vs 97 — the load is at 97 instead of 96. So candidate: li a1,320 at 96? then load at 97? then jal, then li a2,240? Hmm, that would be 4 instructions: li a1, lw a0, jal, li a2. Wait, that has li a1 at 96 and lw at 97.

Hmm. But `li a1,320` at 96 would be in the delay slot of sh v0,14(s0) at ... wait no, the sh is at 3ad0 and the delay slot is 3ad4. If the candidate has li a1,320 at 3ad4 and lw a0,32(s0) at 3ad8 then jal at 3adc and li a2 at 3ae0 — yes, exactly a swap of the first two.

So: without the asm, GCC chose to put `li a1,320` in the delay slot and the load after. Why? Because `li a1,320` (setting the second arg) is independent of everything and the delay slot prefers... hmm. With the asm present, `li a1,320` cannot be moved before the asm (barrier), so it must be after the load. And the load gets the delay slot.

So: how do we make GCC not hoist `li a1,320` above the load, in plain C?

The load feeds a0 of the call; `li a1,320` is the 2nd arg. GCC's sched1 for a call: the arg-setup instructions are in the same group as the call (SCHED_GROUP_P) and are scheduled as a unit with the call. The a0 setup (the load) is also part of the group.

Actually, the difference must come from the block boundary created by the asm. With the asm, the group [call + args] is in a block whose predecessor is [load]; sched1 places the group after the load. The load, being alone at the end of its block, gets scheduled into the delay slot of the previous block's last insn.

Without the asm: the load is in the SAME block as the call group. sched1 might prefer to put li a1,320 into the delay slot (since the delay slot of the previous block's last instruction can be filled from the current block's instructions) — and it prefers the "li" over the load because of birth-boost/priority.

Hmm, so how to make the load preferred for the delay slot? Make the load's value needed EARLIER? Hmm.

Actually here's a cleaner idea: **make the load have a higher scheduling priority / earlier birth**. Or: make the call's first argument come from something that isn't a plain load.

Alternatively: **put the load into the previous block**. I.e., in C, evaluate the load BEFORE the if-block? No — the load must come after the store `sh v0,14(s0)` in the target (it fills the delay slot after it). Wait, does it? The load at 3ad4 is in the delay slot of sh at 3ad0, so the load executes after the store. If we moved the load earlier in C (before the if), it would be scheduled elsewhere → wrong.

Hmm, what if we move the load to just after the `if` block ends, but ALSO reorder so that the `li a1,320` has a dependency? E.g.:

```c
t = ((Unkstruct_80126B58 *)p)->unk20;
func_8001D0E8(t, 0x140, 0xF0);
```
The `li a1,320` is independent. To make it not hoistable above the load, we could make the load's value feed the delay... no.

**Idea**: what if the first argument is not the loaded value directly but the loaded value plus something computed? No, changes code.

**Idea**: what if we make the load appear TWICE in C (two separate loads from the same address) so that GCC must keep one before the group? No, GCC CSEs.

**Idea**: What if the load is in a block that ends right there, e.g. inside a nested block `{ s32 t; t = ...; }` — that's just a scope, no block.

**Idea**: use a `goto` to create a real block boundary:
```c
{
    s32 t;
    t = ((Unkstruct_80126B58 *)p)->unk20;
    goto call_t;
}
call_t:
    func_8001D0E8(t, 0x140, 0xF0);
```
Hmm — the goto would create a jump instruction, adding an instruction (unless the goto is at the end of a block and jump threading removes it). Actually GCC's jump threading removes a goto that jumps to the immediately-following block. But here the goto is the last statement in the block and the label follows... GCC would just merge the blocks. Hmm.

What if the goto creates a genuine branch? Like:
```c
if (cond) goto L;
...
L: call
```
But we need no extra instructions.

Hmm, what about a `switch` with one case? Or a `for` loop with 0 iterations? A loop creates blocks (loop.c). E.g.:

```c
{
    s32 t;
    t = ((Unkstruct_80126B58 *)p)->unk20;
    do { func_8001D0E8(t, 0x140, 0xF0); } while (0);
}
```
Notes said the do-while wrapper gave the same score 2. Hmm, because do-while(0) is removed early.

What about `while (0) {...}`? Also removed.

What about a REAL loop that executes once? `do { ... } while (0);` is removed. But:
```c
do {
    func_8001D0E8(t, 0x140, 0xF0);
    break;
} while (1);
```
That's a real loop → extra jump/branch instructions. No.

Hmm.

**Different approach**: make the load's destination register NOT a0 directly. E.g., pass `t` through a variable that gets copied to a0: `func_8001D0E8(t, ...)` where t is a variable — GCC will put t in a0 directly. But if we write the call as taking a different expression...

What if we make the first argument `t` but t is assigned from the load AND t is also used elsewhere? Extra use = extra instruction.

**Approach**: change which arg slot the load goes into. If the load fed a1 instead of a0:
```c
func_8001D0E8(0x140, t, 0xF0);
```
No — that changes the semantics of the call (arg order matters).

**Approach**: The delay-slot choice. In the target, the load is in the delay slot. sched1 picks the delay-slot instruction. The `li a1,320` beat the load. Why? Because the load is part of the call's group (must be adjacent), while the li is a "birth" instruction (li has birth boost priority). Hmm.

In the target (with asm), the load is in its own block, so it's not competing with the li at the same priority.

Hmm, what if we make the load have a HIGHER priority than the li? E.g. by making the load's result used by something with higher priority... no.

**Alternative**: maybe we can get the load into the delay slot by making the preceding instruction's delay slot "need" something. Hmm.

Let's think about MIPS delay-slot filling in GCC 2.7: `mips_fill_delay_slot` in final.c? Actually delay slot filling happens in `mips_final_prescan_insn` / `delay_slot_filling` pass (delayed.c). The pass `delay_slot_filling` decides which instruction goes into a branch's delay slot, based on `delay_slot_filling` rules and the "priority" of instructions in the block.

Actually for a NON-branch instruction (like `sh`), the delay slot is filled by the scheduler — the instruction after it in the same block. So the ordering within the block after scheduling is what matters. sched1 orders the block's instructions; the block is [.., sh v0,14(s0)] and then the next block [lw a0,32(s0), li a1,320, jal, li a2,240]. When GCC lays out blocks, the next block's instructions get scheduled; the first instruction of the next block can be placed in the delay slot of the previous block's last instruction only if there's no branch in between.

Wait — but the branch `beqz v0,3ad4` at 39e0 jumps to 3ad4 which IS the load. So the load is at the join point. The fall-through path from 3ad0 (sh) also reaches 3ad4. So the join block's first instruction is at 3ad4, and it's simultaneously in the delay slot of the sh (for the fall-through path) and at the branch target (for the branch path). Clever.

So the join block = [lw a0, li a1, jal, li a2]. Its first instruction goes at 3ad4.

Now: without the asm, GCC scheduled [li a1, lw a0, jal, li a2] instead. So sched1 chose li a1 first.

Why? Because of the call group: the call `jal` needs a0 = t (the load) and a1 = 320. The group is [li a1, jal] (and li a2 in delay). The load must precede the group. So within the block, sched1 places the group at the end and the load before it. But the block order became li a1, lw a0, jal? That contradicts "load before group".

Hmm, unless: the delay slot of the `sh` is filled by a different block's instruction... Let me not over-theorize.

Let me just get the candidate's actual disassembly to see. I can compile the candidate and objdump it. Is there a tool for that? `tools/cc1_dumps_tu.sh` gives cc1 dumps. Let me check if there's a way to compile a TU and dump.

Actually easier: use dt.sh with a candidate and see the diff tail. dt.sh's tail gives the diff. Let me run dt.sh with the "both re-ties removed" version (v1.c) to see the diff output format.

Let me check what v1.c/v2.c are and run dt.sh.

Actually, better: let me create a candidate that removes the asm and see the diff. Let me look at v1.c.

Let me set up a working approach:
1. Copy orig.c to a candidate file, edit out the asm.
2. Run dt.sh to get score + diff tail.

Let me check dt.sh's tail output format first with a 40-line tail.
