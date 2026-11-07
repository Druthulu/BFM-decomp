---
ts: 2026-11-06T16:56:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OhiWKgYXww8hugnUf6D8
---
Mine: n = v1, m = s0 (sll s0,v0,0x10). Target: n = s0, m = s0 (sll s0,s0,0x10).

So the only difference is n's register: v1 vs s0. And consequently `subu v0,v0,v1` vs `subu s0,v0,s0` and `sll s0,v0,0x10` vs `sll s0,s0,0x10`.

So we need n in s0. If n is in s0 and dies when m is born, local-alloc ties m to s0 (m is live across calls → s0 anyway).

How to get n → s0 with real C? The allocator picks v1 because it's a free caller-saved reg and the qty has low priority. s0 is also free at that point. local-alloc's choice among free registers: it has a preferred order. For a quantity that's not live across a call, local-alloc can use any register; it tends to prefer... Let me look at local-alloc.c's register preference: it computes `qty_phys_reg` by scanning `qty_order`? Actually local-alloc has a "reg_alloc_order"? Hmm.

Alternatively, make n live across a call so it *must* be callee-saved. The sign rand call: if n's use extends past it, n → s0.

Idea: rewrite the computation so n is used after the sign call:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
if ((rand() & 1) != 0) {
    m = (q - n) << 16;
} else {
    m = -((q - n) << 16);
}
```
Hmm, that duplicates the expression; the compiler would compute it once before the branch. RTL: the sub might be computed before the call anyway (cse).

Better: 
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
s32 r = rand() & 1;
m = (q - n) << 16;
if (r == 0) m = -m;
```
Here n's last use (`q - n`) is after the rand call in source order. The RTL would use n after the call → n is live across the call → callee-saved. But will the target's instruction order still match? The target has `subu s0,v0,s0` before the jal. If the RTL has the sub after the call, sched1 might hoist it before (it's a pure ALU op with operands available). Let's test.

Note: `s32 r = rand() & 1;` — the target has `andi v0,v0,0x1` after the jal (8eb0), which matches `rand() & 1` computed after. Fine.

Let me try this variant. Also the sign condition: `if ((rand() & 1) == 0) m = -m;` → with r: `if (r == 0) m = -m;`.

Actually, careful: the target's `sll s0,s0,0x10` is in the delay slot of the jal (8eac), i.e. sched1 moved the shift before the call. If the RTL has m = (q-n)<<16 after the call, sched1 would move both sub and sll before the call... but then the target has the sub before the call too, so both before = matches! Target: `subu s0,v0,s0` at 8ea4, `jal` at 8ea8, `sll s0,s0,0x10` at 8eac (delay slot). So sub before, sll after. If we hoist the whole expression before the call, we'd get sub, sll, then jal — the sll wouldn't be in the delay slot. That would differ (sll before vs in delay slot).

Hmm, risky. Let's just try it.

Alternative approach: make n a value that's live across a call *without* moving the computation: e.g. use n after the call in a dead-but-not-deleted way? A dead reset! `n = 0;` after the call? No — a dead reset would keep n live until then, making it callee-saved! But then n's value must survive the call, and the allocator gives it s0. And the dead set is deleted by flow (before sched1), so no instruction. But wait: the dead reset after the call means n is live across the call (the value is used by the reset? no — a set doesn't use). Hmm, `n = 0;` is a *definition*, not a use. For n to be live across the call, we need a USE of n after the call.

What about using n in the next computation's... no, it's redefined.

Hmm, what if we merge the two computations' n into one variable and use it? No.

Let me think about local-alloc's register choice more. Maybe there's a simpler move: the register chosen for n depends on the qty order (birth order). The catalog says: "A block with exactly THREE quantities is allocated in BIRTH order, not sorted (local-alloc.c:1486-1507)". If we change the number/order of quantities, n's register may change to s0.

Let me look at local-alloc.c:1486-1507 to understand.
