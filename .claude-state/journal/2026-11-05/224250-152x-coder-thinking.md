---
ts: 2026-11-06T05:42:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CaHDip8PxfUvCoWkMkZG
---
Item 5: baseline 0; lever-free score? Let me get the score line. The diff shows:
1. Mine stores `sh a1,122(s0)` where the target has `nop` and then later `lhu v0,18(sp); nop; sh v0,122(s0)` — i.e., the target reloads from the stack (sp+18) and stores, while mine keeps the value in a register (a1) and stores directly.
2. The frame size differs: mine 72 vs target 56 bytes (3 extra saved regs: s1, s0, ra at different offsets).

So the barriers force a *reload* from the stack (`lhu v0,18(sp)`) instead of using the register. The memory clobber kills the cse equivalence of the stack value.

Let me see the source:
```
if ((r5 | r6) != 0) {
    if (*(s16 *)(a + 2) < *(s16 *)(b + 2)) {
        BARRIER
        *(s16 *)(e + 0x78) = *(u16 *)(a + 0);
        *(s16 *)(e + 0x7a) = *(u16 *)(a + 2);
        *(s16 *)(e + 0x7c) = *(u16 *)(a + 4);
        __builtin_memcpy((void *)(e + 0x80), out, 8);
    } else {
        BARRIER
        *(s16 *)(e + 0x78) = *(u16 *)(b + 0);
        ...
    }
}
```
The barriers are at the start of each arm. The target reloads `*(u16 *)(a + 0)` from the stack (sp+18) — the value was stored to a[0] earlier; cse would keep it in a register, but the barrier forces a reload.

So the barrier is a cse memory barrier again. Real-C: make cse reload the stack value. Options:
- Make the load go through a different MEM expression (alias class).
- The value is a local stack array `a` (u8 a[8], accessed as *(s16 *)(a + 0)).

The target reloads from sp+18. cse would normally forward the value stored earlier (a[0] = ...). The barrier prevents forwarding.

Hmm, the earlier store `*(s16 *)(a + 0) = *(s16 *)(b + 0) = *(u16 *)(e + 6)` — the value is in a register; cse forwards it to the later `*(s16 *)(e + 0x78) = *(u16 *)(a + 0)`.

To force the reload, we can make cse's memory equivalence fail: e.g., use different alias classes for the earlier store and the later load (struct vs scalar), or make the intervening calls invalidate... wait, there ARE calls in between: `r5 = func_8014FFDC(e, a, out); r6 = func_80150150(e, b);`. A call invalidates memory (calls clobber memory). But `a` is a local array whose address was passed to the call → the call could modify it! So after the call, cse MUST reload a[0]. But mine didn't reload — it kept the value in a register. That means gcc's cse treats `a` as unmodified by the call? No — the call takes `a` as an argument (a pointer), so it could modify *a. cse should invalidate.

Hmm, but the target reloads and mine doesn't. Let me look at the source more carefully:

```
*(s16 *)(a + 0) = *(s16 *)(b + 0) = *(u16 *)(((s32)e) + 6);
*(s16 *)(a + 2) = *(s16 *)(b + 2) = *(u16 *)(((s32)e) + 0xA) - 0x10;
*(s16 *)(a + 4) = *(s16 *)(b + 4) = *(u16 *)(((s32)e) + 0xE);
r5 = func_8014FFDC(((s32)e), a, out);
r6 = func_80150150(((s32)e), (s32)b);
...
if (*(s16 *)(a + 2) < *(s16 *)(b + 2)) {
    BARRIER
    *(s16 *)(e + 0x78) = *(u16 *)(a + 0);
```
So `a` is passed to func_8014FFDC (which could modify it). After the call, cse must reload a[0] — and the target does. Mine doesn't?? That would be a compiler bug unless... hmm, maybe mine reloads from a different location or the diff is elsewhere.

Wait, the diff shows:
```
mine[38] sh a1,122(s0)   | target[38] nop
insert mine[40:40] target[40:43]: lhu v0,18(sp); nop; sh v0,122(s0)
```
So mine has `sh a1,122(s0)` at 38, target has `nop` at 38 and then at 40-42 `lhu v0,18(sp); nop; sh v0,122(s0)`. The addresses: 122(s0) = e+0x7A. So the store of a[2] (offset 0x7A = a+2's value).

Mine uses a1 (a register) directly; the target reloads from sp+18 (which is a+2).

Hmm, but there are 3 stores: 0x78 = a[0], 0x7A = a[2], 0x7C = a[4]. The target reloads each from the stack. Mine keeps them in registers.

So gcc's cse *did* keep the values across the calls in mine. That seems wrong... unless the arrays `a`/`b` are local and their addresses passed to the calls, but gcc 2.7.2's cse doesn't invalidate memory across calls for stack slots? It does (`invalidate_for_call`).

Hmm, wait — maybe the calls are *before* the values are stored? No: the stores are before the calls.

Hmm, but the *first* store `*(s16 *)(a+0) = *(u16 *)(e+6)` — the value is loaded from e+6. Then func_8014FFDC(e, a, out) is called — it could modify a[0]. So after the call, `*(u16 *)(a+0)` must be reloaded. The target does. Mine uses a1.

Unless mine reordered the stores to after the call? No.

Wait, maybe I mis-identified. Let me look at the full candidate/target listings.

Let me get the score and the full diff first.
