---
ts: 2026-11-06T11:04:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hyoKdnrWKZuHcwWaCKZc
---
No improvement (best 4). The delay-slot fill is a reorg behavior that needs the asm fence.

Let me try a do-while or another construct at the head of the if-body to see if reorg stops. Actually, reorg's stop_search_p stops at CALL_INSN, JUMP_INSN, and insns with side effects. A do-while emits no insn (only notes). Notes don't stop reorg.

What about a `volatile` read? That emits an insn (a load) — extra instruction.

Hmm.

What if we split the basic block with a label/goto? E.g.:
```
do {
    if (D_80115158[i].h != 0) {
        goto body;
    }
    goto next;
body:
    ot = call(...);
next:
    i++; w++;
} while (i < cnt);
```
That adds jumps.

Given time, let me record a wall for item 3 (best 4) and do item 4 similarly.

Actually, wait. Let me reconsider the delay-slot issue. Maybe a different loop structure can make reorg fill the slot with the addiu naturally. In the target, the slot has `addiu v0,s1,1` — the i++ computation. The i++ is `v0 = s1 + 1` (i is s16: sll/sra). reorg fills the beqz slot with the addiu because the target's forward scan was stopped by the asm.

Without the asm, reorg fills the slot with an insn from the fall-through. In mine, the slot is... let me look at my listing around fe0.

Let me dump x_ns16's loop region.
