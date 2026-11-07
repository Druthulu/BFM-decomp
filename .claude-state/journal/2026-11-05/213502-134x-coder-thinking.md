---
ts: 2026-11-06T04:35:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R3z9ZBAFJuny6qSa160G
---
Same score 6. The sched still puts add before p. Hmm.

Now the diff: mine has `addiu; lw; nop; sh` and target has `lw; addiu; sh`. So I need the p load before the addiu. The p load writes p (the reused pseudo). The addiu writes v (the chain result). Both are ready after the sll. The scheduler picked add first.

Why? The addiu's priority: addiu → store (sh) = 2. The p load → store = 2. Equal priority. Tie-break: maybe by birth order. The addiu's birth vs the p load's birth: in z8's RTL, which is born first? If the addiu is born before the p load (source: p then add → p born first; source: add then p → add born first). In z9 (add then p), the add is born first → scheduled first. In z8 (p then add), p is born first → should be scheduled first, but it wasn't (add first). Hmm.

Wait, maybe the p load is not "ready" as early because of the WAW with the obj->1C value (p reused). The p reload writes p; p's previous value (obj->1C) is read by the sll at 4940. So the p reload can't issue until after the sll (4940). The addiu (v+0x600) depends on the sll at 4940 too (v is the sll result). Both ready after 4940. Equal priority.

The scheduler's ready list at T after the sll: addiu (priority 2) and lw p (priority 2). It picks by... the ready list sort uses priority then insn UID? Let me check `schedule_insn`'s sort. If it sorts by priority and then by UID (higher UID first?), the p load (born later in z8) would be picked first. But the add was picked. Hmm.

Actually, the target has lw p before addiu. In z8/z9 the add is first. Let me try to make the p load's priority HIGHER: give the p value more refs or a loop-depth boost. E.g., use p twice after the load? The merge store uses p once. 

What if the store value depends on p? no.

Alternatively, make the addiu's priority LOWER: e.g., `v = v + 0x600;` is used by the store. If the addiu were not on the store's critical path... it is.

Hmm, what if we compute the addiu earlier (in the chain) so it's not competing? E.g., `v = p * 3 * 32 + 0x600;` — then the chain includes the addiu, and the p load is after the whole chain. The target: sll, addu, sll, lw, addiu, sh. The addiu is separate. If folded into the chain, the order would be sll, addu, sll, addiu, lw, sh — not target.

What if we make the addiu depend on the p load? E.g., `v = v + 0x600;` where the constant is loaded via p? no.

What if we reorder the merge store to use `v + 0x600` directly: `((Unk*)p)->unk18 = v + 0x600;` and remove the `v = v + 0x600;` statement. Then the addiu is part of the store's value computation, born after the p load (since the store needs p). The RTL: chain, p load, addiu, store. sched: chain, then p load and addiu both ready; the addiu's birth is after the p load (it's part of the store expression, expanded after the address p). Actually the store's address p is evaluated first, then the value v+0x600. So the p load is born before the addiu → the p load might be scheduled first! Let me test (z10).

But careful: the merge store is shared; `v + 0x600` would apply to all arms. Only the `<0x11` arm needs +0x600. So I can't change the shared store.

Unless I duplicate the store in the `<0x11` arm (z1 style) with the value inline:
```
} else if (< 0x11) {
    store 0x1A raw;
    p = *(s32*)(obj+0x1C);
    v = p * 3 * 32;
    p = model;
    ((Unk*)p)->unk18 = v + 0x600;
    goto call;
}
```
Then the shared store remains for the other arms. Let me test this (z10). The `<0x11` arm's store is duplicated but that's what the target has (the arm's own store at 494c is the shared one, but duplicating it produces the same instruction). The count might match.

Let me build z10 from z8: replace the arm body (store, p=obj, v=p*3*32, p=model, v+=0x600) with store, p=obj, v=p*3*32, p=model, `((Unk*)p)->unk18 = v + 0x600;`, `goto call;`.

z8 lines: 55 store, 56-58 comments, 59 p=obj, 60 v=p*3*32, 61 p=model, 62 v+=0x600. Let me replace 55-62.
