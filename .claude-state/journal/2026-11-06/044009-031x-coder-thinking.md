---
ts: 2026-11-06T11:40:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WlRT1jX1fVWYKWV6hMOD
---
w1 has u16 sVar3 but bb is u32, so `andi a2,a0,0xffff` extra. And one load.

The main structural difference: 1 load vs 2. So the double load needs the launder (or barrier).

Hmm wait — but the target's 2 loads: maybe they're not from cse at all. Let me think about `bb`. In the C: `bb = *(u16 *)(p + 0xAE); lo = bb & 0xFF; if (lo != c80 || (hi = bb >> 8) != 0x80) { sVar4 = ratan2((*(u16 *)(p + 0xAE) & 0xFF) - 0x80, 0x80 - (*(u16 *)(p + 0xAE) >> 8)); ... }`.

The second read is a fresh load expression. cse would forward it. To prevent forwarding, the launder/barrier do it.

So without any lever, cse forwards → 1 load. Is there real C that prevents forwarding? 

Options:
1. A store between the two reads that flow deletes — but cse runs before flow.
2. Make the second read not cse-equal: e.g., different mode (but then different insn).
3. Make the first read not in cse's table: e.g., if the first load's result is used in a way that cse marks the memory expr as not recordable? cse's `do_not_record` is set for volatile mem.

Hmm, what about the *first* read being through a `volatile`-free but `RTX_UNCHANGING`? no.

4. Make the first read happen inside a `do{}while(0)` block? C0535 says do-while splits cse1 EBB. But the first read is before the if; splitting the EBB might clear the memory table! Actually cse1 operates on EBBs (extended basic blocks). A do-while(0) creates a barrier in the CFG (a jump), splitting the EBB, so cse doesn't carry the memory table across. That's the C0535 technique: "do{}while(0) splits cse1 EBB".

The constraint says `do{}while(0)` only with `// !FAKE: do-while`. And C0535 is a sanctioned move (cookbook). Is do-while a lever? The brief's MOVES+ explicitly recommends C0535 (do{}while(0) splits cse1 EBB). So it's allowed with the comment.

But where to put the do-while? Between the first read and the second read. The first read `bb = ...` is before the if. If I wrap the `bb` read + compare in a do-while block, the EBB splits after the block... Actually, the second read is inside the if body. Let me think about the CFG: 

```
bb = load;
lo = bb & 0xFF;
if (lo != 0x80 || (hi = bb>>8) != 0x80) {
    sVar4 = ratan2(load1, load2);
    store;
    return 1;
}
return 0;
```
EBBs: [bb=load; lo; cond] → then body. The body is a separate basic block already (after a branch). cse1 works per EBB and keeps a table across EBBs? cse1 processes the whole function with a table that persists across EBBs but invalidates at labels? In cse.c, `cse_basic_block` resets at `NOTE_INSN_LOOP_BEG`? Actually cse uses `next_qty` and processes each EBB, with the table persisting unless a label/jump requires invalidation. The `do{}while(0)` inserts a jump/label pair, which cse treats as a block boundary → table reset? Let me check cse_basic_block: at a CODE_LABEL, it flushes.

Hmm. Let me just try: wrap the bb-read + compare in `do { ... } while (0);` and see if it yields 2 loads.

Actually the natural place: the second read is in the if body. The EBB boundary at the if is already a branch. But cse keeps the table across the branch into the fall-through path... The if body is entered when the condition is true; cse's table from before the branch is still valid (no writes). So it forwards.

A do-while around the if body would create a label/jump inside. Hmm.

Let me try wrapping the whole if in do-while(0), or wrapping the compare part.

Alternatively, C0414's "dead-reset" for memory: store to the same location? e.g. `*(u16*)(p+0xAE) = *(u16*)(p+0xAE);` — a self-store. That would be a real store, appearing in the code (sh) unless cse/flow deletes it. cse would likely delete a self-store? It records the store... risky but could produce the reload AND be deleted. Actually cse might turn `x = x` into nothing (store of the same value to the same address — cse doesn't know the value is the same unless it forwards the load; it would generate sh).

Hmm. But wait: the target's store to iVar5+0x12 happens AFTER. What if the source actually had a store before the read that got deleted? Unlikely.

Let me try the do-while approach first. C0535 is explicitly recommended.

Try: 
```
do {
    bb = *(u16 *)(p + 0xAE);
    lo = bb & 0xFF;
    if (lo != c80 || (hi = bb >> 8) != 0x80) {
        ...
        return 1;
    }
} while (0); // !FAKE: do-while
return 0;
```
Hmm, but a `return 1` inside a do-while is fine.

Let me also try wrapping just `bb = ...` read.

Actually, the cleanest: the EBB split must occur between the first load and the second load. The first load is at `bb = ...`, the second in the if body. If I write:

```
bb = *(u16 *)(p + 0xAE);
lo = bb & 0xFF;
do { ... } while(0)   // around the if
```
The do-while creates a jump to the end label. cse's table: at the label, `cse_basic_block` is called; in cse.c, at a CODE_LABEL it may flush the table if the label is a loop start or if it has multiple predecessors. Let me check the code.

Let me look at cse_basic_block / the main loop for how labels are handled.
