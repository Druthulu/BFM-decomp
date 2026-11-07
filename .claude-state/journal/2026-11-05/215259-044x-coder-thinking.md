---
ts: 2026-11-06T04:52:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wTj58VTo4kFVzMezWhHv
---
141 includers (some are MAIN too). Baseline orig.c scores 0 on includer 0. Now remove the barrier and see.

The barrier is in the middle:
```
*(s16 *)(D_80127524 + 0x1A) = 1;
__asm__ __volatile__("" : : : "memory");
((void (*)(s32))func_80138C30)(*p);
```
So the barrier between the store and the indirect call. Why? The call `func_80138C30(*p)` — the argument *p is loaded. The store to D_80127524+0x1A is independent. Maybe the barrier prevents cse from reusing the *p load or from moving the store after the call, or prevents the call's argument load from being hoisted above the store (aliasing: the call may read the stored field). Actually a call is a memory clobber itself, so the store can't move past it. The barrier's effect: prevents the *p load (call arg) from being hoisted above the store `*(s16*)(D_80127524+0x1A) = 1;`? Hmm, the call arg *p = *(D_80127524) — a load from D_80127524. The store is to D_80127524+0x1A. Different offsets, no alias. So without the barrier, the load *p could be hoisted above the store. That would change register allocation/order.

Let me just test a1 (barrier removed) on includer 0, then all.
