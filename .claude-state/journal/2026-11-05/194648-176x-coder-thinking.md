---
ts: 2026-11-06T02:46:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zGHSc1KXaUG6puzt7oh8
---
Still 105 ins (missing the 3). The do-while doesn't split the cse EBB here (g1/g6 worse score).

We need to force the reload. Let me think about cse's store-to-load forwarding: cse1 records the store's value for the memory location; the load gets replaced if the address rtx matches. To break it, make the addresses differ in a way cse can't equate: e.g., store via `((Unk*)arg0)->unk1C` (address: arg0 + 28, where arg0 is a pseudo/reg) and load via a *different base register* that cse can't prove equal, e.g., `((Unk*)(arg0 + 0))->unk1C`. The address expression would be `(plus (plus (reg arg0) 0) 28)` simplified to `(plus (reg arg0) 28)` → same.

What if we use a pointer variable `p = arg0;` and access via p? cse's value numbering: p and arg0 are different pseudos but cse may know p == arg0 (a copy propagation), making the addresses equivalent. Hmm.

What if the second access goes through a pointer that cse can't equate, e.g., `u8 *q = (u8*)arg0;` then `*(s32*)(q + 0x1C) -= 1;`? cse knows q = arg0? A copy propagation in cse might. The generated code target uses s1 for both.

Alternatively, force a reload by making the two accesses in different *alias sets*: e.g., store via a `u16*` and load via `s32*`? Different modes — the target requires s32 both.

Hmm, what about the "dead reset" C0414 trick? Let me read it.
