---
ts: 2026-10-22T11:09:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IT9r4wsj6O5KjdscvUCB
---
Confirmed: it's a pure ORDER swap of 2 instructions.

Now, how to make the load come first?

The candidate block: [li a1,320; lw a0,32(s0); jal; li a2,240]. Wait — hmm, that's interesting: `li a1,320` before the load. Actually maybe the order in the candidate is:
- 96: li a1,320
- 97: lw a0,32(s0)
- 98: jal
- 99: li a2,240

So the load is between li a1 and jal. Since the jal needs a0, and the delay slot of jal is li a2.

Hmm so in the candidate, sched1 placed li a1 first, then the load, then the call. In the target: load, li a1, jal, li a2.

So the difference: in the target the load precedes li a1.

Why would the load come after li a1 in the candidate? Because sched1 sorted by "birth" priority: li a1 (a constant birth, no deps) can be hoisted anywhere. The load depends on s0.

Hmm, actually in the target the load comes first because it's at the START of the block (it's the first instruction of the block, the join). In the candidate, the block starts at... hmm.

Wait — maybe the block structure differs! Without the asm, maybe GCC merged the join block with the fall-through block differently, so the load is not the first instruction of the join.

Hmm. Think: the join block in the target = [lw a0, li a1, jal, li a2]. In the candidate = [li a1, lw a0, jal, li a2].

The difference is just the order within the block, decided by sched1.

sched1 sorts by priority. The load has a "birth" priority... Actually, delay slot filling (delayed.c) is a separate pass that can REORDER within blocks to fill delay slots! The `delay_slot_filling` pass picks instructions for delay slots based on their `INSN_COST` and priority, and can move them from the block.

Hmm, but here the delay slot of `sh v0,14(s0)` at 3ad0 is filled by 3ad4. Both target and candidate have the same preceding instructions.

OK here's another thought: the difference might come from the *dependency* structure. In the target, the load feeds a0 of the call. In the candidate, the load also feeds a0.

Hmm, so what if in the candidate, GCC decided the load is a0 setup and grouped [load, jal] together as the call's "operands"? While li a1 is a separate "birth" instruction.

I'm going around in circles. Let me get empirical: try several C variants and see.

Variants to try for item 2:
(a) Move the load before the `if` block? No.
(b) Assign the load to a variable used elsewhere.
(c) Put the call args in different order in C (e.g. `func_8001D0E8(t, 0x140, 0xF0)` — what if we write it as `func_8001D0E8((s32)t, 0x140, 0xF0)`)? Cast might change.
(d) Use a comma expression: `func_8001D0E8((t = ((Unkstruct_80126B58 *)p)->unk20), 0x140, 0xF0);`
(e) Split: `t = ...; a0 = t;` no.
(f) Make the load's address expression use a different spelling so the load is "born" earlier (higher priority): e.g. `t = *(s32 *)((u8 *)p + 0x20);` vs `((Unkstruct_80126B58 *)p)->unk20`.
(g) Give the load a use in the same expression as another arg.

Hmm — here's a promising one: what if the load result is used in an expression that includes the constant? Like `func_8001D0E8(t, 0x140, 0xF0)` where 0x140 and 0xF0 are constants. If instead the constant were computed from t... no.

Let me think about it as: we want the load to be scheduled before li a1,320. The load must be "ready" earlier. sched1's priority: an instruction's priority = its "birth" (number of predecessors) plus dependencies. The load depends on s0 (available) → low birth. The li is a constant → birth 0? Constants have the highest birth priority in GCC (they're "ready" immediately and sched1 boosts them).

Actually in GCC's sched1, `rank_for_schedule` gives constant/birth priority: an instruction whose operands are all constants gets a boost.

Hmm, but the target has the load FIRST. So in the target, the load had priority over li a1. Why? Because of the block boundary! The load was in its own block (after the asm), and blocks are scheduled in order; the load's block precedes the call's block. Within a block, order is preserved from the RTL. So the load came first because it was in an earlier block.

Without the asm, load and call are in one block, and sched1 reorders them.

So the question becomes: **can we create a block boundary between the load and the call in plain C, without adding instructions?**

Options:
- A `goto` that GCC's jump threading can remove but which still splits the block during scheduling? Jump threading happens in jump.c, AFTER scheduling? Order of passes in GCC 2.7: flow, expand, ..., sched (sched1), jump, ... So jump threading happens AFTER sched1. So a `goto` would create a real jump at sched1 time.

Hmm, but a goto that jumps forward to the immediately following code... GCC's flow pass might merge. Actually, the front end emits a goto to a label; the label's block follows. CFG cleanup (flow) merges blocks where possible but a goto followed by a label creates a real edge.

Hmm, but actually: if the goto is the LAST instruction of the block and the target is the next block, GCC's `flow` might notice. Actually GCC's CFG cleanup does "jump threading" for `goto` to a label in the next block? No.

- `if` with a runtime condition: adds a branch.
- A `switch`: adds a jump table or branches.

Hmm what about `break`/`continue` inside a real loop? Adds loop overhead.

What about `return`? The function returns after; the `*(u8*)(p+0x75) = 0; return;` after.

**Hmm!** What about restructuring the C so the load naturally ends a block? For instance, the whole `{ s32 t; ... }` is inside `if ((CAST_SIGN(u16,p,0x70) & 0xF0) != 0) { ... }` — and the code after the if-block is at the join.

What if we put the load inside the `if` block (the != 0 branch) and duplicate it in the else path? Then... hmm, the load would be in two blocks, and the join would have a phi. The target has ONE load at the join.

**What about making the load the LAST thing before the call, with the call in a nested scope?** Scope doesn't create blocks.

Let me reconsider: maybe the block-splitting isn't the mechanism. Let me actually check the RTL/blocks. I have tools/cc1_dumps_tu.sh and tools/alloc_table.py. Let me look at those, and at hdump.sh.

Let me check the T10 helper scripts.
