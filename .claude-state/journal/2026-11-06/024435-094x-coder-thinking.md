---
ts: 2026-11-06T09:44:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h2gLCNBqrGyJmTYFJwHS
---
All 2. Time 02:44:14. I need until ~02:53 for 20 min. Let me keep exploring with more substantive ideas.

New thought: maybe the fix isn't about the store at all but about the *copy*. In the target, `move a0,s0` at 38 — what if the original C had `func_801553C0(s0)` where the arg copy is created at the call, and the RMW's base rewrite to a0 happened because local-alloc's copy propagation uses the copy only if it *dominates*; the scheduler placed the copy before the RMW but after the store.

Our build has the same, except the copy is before the store. So it's a scheduling-order issue.

What if we can make the store's insn have a *dependent* (raising priority) without changing the output? An insn that depends on the store's memory: a later load from the same address would be eliminated by cse (REG_EQUAL). Hmm, what if the source had `*(u16 *)(s0 + 0x188) = 0; ... *(u16 *)(s0 + 0x188)` read? No.

What if the store's *value* 0 is loaded from a variable that's set by... no.

What if the RMW's load address depended on the store's base? It does (same s0).

What if we make the store a *set* of a pseudo: e.g., `u16 z = 0; *(u16*)(s0+0x188) = z;` (z2/z8 = 2). The store's value z is a constant, folded.

What if the store's value were a variable that's live later? e.g., `u16 z = 0; *(u16*)(s0+0x188) = z; ... use z later`? The target stores 0; using z later would need a use. E.g., `*(u16*)(s0+0x188) = z;` and later `*(u16*)(s0+0x18A) = z;`? No, 0x18A is at the top.

Hmm, what if the original C stored the same zero variable to both 0x18A and 0x188? The target has both stores. If a variable `z = 0` were used for both, the first store at 15 and the second at 37; z would be a constant. The store's priority would still be 1.

OK. Another angle: what if the *store* insn in the original RTL had a REG_DEAD or REG_EQUIV note that changed the scheduling? 

I think this is genuinely a wall. Let me use the remaining ~8 minutes to run a final couple of batches with a struct-based rewrite (which changes the RTL shapes) — maybe the struct access produces a different order.

Struct idea: define a local struct pointer:
```
struct S { u8 pad[0x44]; u32 f44; u8 pad2[0x140]; u16 f188; };
```
Hmm, 0x44 = 68, 0x188 = 392. Define:
```
typedef struct { u8 p0[0x44]; u32 f44; u8 p1[0x188-0x48]; u16 f188; } T;
```
Then `((T*)s0)->f188 = 0; ((T*)s0)->f44 &= ~4;`. The address computations would be identical; the RTL is the same. Unlikely to change scheduling.

Let me instead try a couple of *ordering* variants with the store at different positions relative to the RMW and call, and also the RMW's load split:
- y3: `*(u16 *)(s0 + 0x188) = 0;` placed *between* the RMW's load and store (split): 
```
u32 v = *(u32*)(s0+0x44);
*(u16*)(s0+0x188) = 0;
*(u32*)(s0+0x44) = v & 0xFFFFFFFB;
```
w1 did this = 2.

- y4: the store placed before the `*(u32*)(s0+0x184)=0` else branch? no.

Let me try the split with the store FIRST and the load after? that's the current.

Let me try: make the RMW use `s0` but with the load *before* the store and the store *before* the RMW-store, i.e. w1. Done.

I'll do one more batch (y4-y8) with:
y4: struct-based (skip, complex)
y4: `*(u16 *)(s0 + 0x188) = 0;` then `s0 = (s32)((u8 *)s0);` (real-ish cast, may fold)
y5: store, then a *volatile read* of 0x188? adds an insn.
y6: store, then `if (s0 == 0) return;`? adds a branch.
y7: use `register s32 s0`? s0 is a local; making it register could change allocation.
y8: declare `s0` as `u32` instead of s32.

Let me try y7/y8 and a couple of types.
