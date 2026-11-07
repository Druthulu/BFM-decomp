---
ts: 2026-11-06T11:52:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qkUcHWboBiGzqoKSBf5X
---
Still forwarding. The goto label didn't stop cse (probably the label was deleted as unreachable/redundant, or cse still processed the same EBB).

Hmm. Let me check the cse dump of w8 to see if the label survived.

Actually, let me check whether cse's `cse_basic_block` treats CODE_LABEL as a boundary. It should (it starts a new EBB at a label that's a branch target). But the goto was optimized away (jump to the very next insn is deleted), and the label may be removed by jump optimization.

Let me try a label that is a real branch target: e.g.,
```
if (temp_a0) goto L1;
L1:
```
That's an identity condition... might be optimized.

Alternative: use a `switch` with a case that falls through. Real C control flow:
```
switch (0) {
case 0:
    *(u8*)(arg0+6) = (u8)temp_v0;
    break;
}
temp_v0 = *(u8*)(arg0+6);
```
switch(0) is folded. Hmm.

What about a real loop that runs once? `for (i = 0; i < 1; i++) { store; }` — loop.c may unroll/remove. Could work but changes codegen.

Let me reconsider. The walls.txt entry says "only a barrier/volatile stops it". Maybe there's no real-C crack and it's a WALL. But our score is 1 — tantalizing.

Let me look at whether the ORIGINAL could have had a different form where cse doesn't see the store as forwardable. Idea: store via a **union/struct with a different alias set**. In gcc, alias sets are determined by the type. A store through `int*` (SImode) vs a load through `u8*` — different modes, but cse's invalidation uses alias sets. If the store is `*(u8*)` and the load is `*(u8*)`, same alias set → forward.

What if the store is through a **char*** and the load through a **struct field** marked MEM_IN_STRUCT_P? `note_mem_written` for a scalar store invalidates "variable addresses"? Let me look at note_mem_written / invalidate_memory logic.

From cse.c comments: "Pushing onto the stack invalidates only the stack pointer, writing at a fixed address invalidates only variable addresses, writing to a structure (MEM_IN_STRUCT_P) invalidates all but scalar variables". 

So if the STORE is a scalar (not in_struct) and the LOAD is in_struct, the store's invalidation might not kill the load's table entry? But the forwarding is for the exact same address; the store records the value at that address, so the load finds it regardless of in_struct.

Hmm, actually the table lookup for the load `(mem:QI addr)` — the entry created by the store is `(mem/s:QI addr)` with the same flags? The store's mem has MEM_IN_STRUCT_P false; the load's mem (struct field) has MEM_IN_STRUCT_P true. The hash includes the address and mode, not the in_struct flag? If the flags differ, `lookup` might still match (the rtx comparison may ignore flags). Hmm.

Let me try: store via a struct field (MEM_IN_STRUCT_P true) and load via a plain pointer (false), or vice versa. I tried the bit-field. Let me try a plain struct field (u8) for the store and plain pointer for the load:
```
((struct B*)arg0)->f6 = (u8)temp_v0;
temp_v0 = *(u8*)((u8*)arg0 + 6);
```
The store's mem is in_struct; the load's isn't. cse might still forward.

Let me test this quickly. Also the reverse.

Actually, let me look at `note_mem_written` and how cse handles a store to a MEM. In cse_insn, after computing dest, it calls `note_mem_written`. Then later, it inserts the set into the table (the `insert` for the destination). Let me look at the insert code around line 7355.

Let me read around 7300-7400.
