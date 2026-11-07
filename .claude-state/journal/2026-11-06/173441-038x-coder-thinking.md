---
ts: 2026-11-07T00:34:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_c6XxCQW70DAdUkYuN8kb
---
Interesting! In w2 (do-while around the second use), the pointer is loaded ONCE into a0 (18-19), used at 28 (lhu a1,18(a0)) and at 33 (lhu v0,18(a0)) — still merged. And the do-while added a nop/extra insn (69 ins). So the do-while did NOT split cse here.

Hmm. So the do-while(0) doesn't always split.

Let me now go back to the core: how can real C force the pointer reload?

Let me test the QImode theory properly with a store at a *varying* address that is dead. Hmm.

WAIT. What about the store `*(u32 *)(obj + 4) ^= 0x80000000;` in the else branch — that's PLUS with HI... SI mode, not QI.

What about the possibility that the invalidation comes from the *call* in the else branch (func_801292C8)? No, that's after.

Hmm, hold on. Let me reconsider the target: maybe the second load isn't a reload of the same value but a *fresh computation of the address* because the original C used a *different global symbol* — no, relocations say D_80126B78 twice.

Alternatively: maybe in the original C, the two uses read through *different variables* and the first one's value was stored to a *local variable* (not a register): e.g. `s32 cam = (s32)D_80126B78; ...` — no.

Hmm, what if the original C has the second use *before* the first in source, and the target's order... no.

Let me look at this from the "what does the original decomp look like" angle: this is a decompiled function from a real game. The original C source (from the actual game's code) would be something like:

```
SVECTOR sp10, sp18;
s32 *cam = D_80126B78;   // or the global used directly
...
```

Hmm, the barrier in our src was added as a fake. What did the previous author (T10 S11) try? notes.md says "T10 S11 cse-const-addr best 11, 6 tries" — the same wall.

Since the barrier is a `memory` clobber, its effect is cse's all-invalidation. In real C the equivalent is a *call* or a genuinely aliasing store.

IDEA: What if the store to obj+0x14 in the original is through a **QImode**... no.

IDEA 2: What if the invalidation comes from a **store to a variable of a different type via a cast that makes it QImode**, e.g. the `sh` at obj+0x14 is HI in the target... 

IDEA 3: **The `all` invalidation can also come from a store with a non-PLUS, non-REG address**: e.g. `(mem (symbol_ref))` — a store to a global scalar: `cse_rtx_addr_varies_p` false → no. What about a store at `(plus (symbol_ref) (const))`? varies? rtx_addr_varies_p of a plus of a symbol and a const → the address is constant → false.

So a store to a global doesn't invalidate anything.

IDEA 4: **BLKmode store** — a struct assignment of an aggregate whose size is not known at compile time? Only via memcpy call.

IDEA 5: A call. Could the original source have a *call* between the two uses that got... no, the target has no call there.

Hmm, unless the call is *conditional* and the block is... no.

OK, let me question my assumption that the target's second load is due to cse. Maybe it's due to **local-alloc's copy preference** or a **reload**. Let me look at the RTL: In w1, the merged value lives in a pseudo (say r95) used twice; local-alloc assigns it a2. In the target, there are two separate loads → two pseudos.

What if the target's source reads the pointer via TWO DIFFERENT expressions that are cse-unequal because one is `(mem:SI (symbol_ref))` and the other is `(mem:SI (reg))` where the reg holds the address `&D_80126B78` computed as `lui/addiu`? Hmm: `*(&D_80126B78)`? That's the same MEM (symbol_ref).

Hmm, what about the second use reading the pointer through a *struct field of a struct placed over the symbol*: e.g. `((struct {s32 *p;} *)&D_80126B78)->p` — the MEM address is `(plus (symbol_ref) (0))` → folded to symbol_ref.

I keep coming back to needing `all`.

Let me look at whether the target's second load pair might be a **sched1 duplication**? No.

NEW IDEA: What if the source has a **second set of the variable holding the pointer, with a different value, that is then used**? E.g.:
```
s32 *cam = D_80126B78;
... use1: (u16*)((u8*)cam + 0x12) ...
a0->unk2A = *(u16 *)((u8 *)D_80126B78 + 0x12);
```
cse merges the second load into cam (copy). Yes merged.

What if cam is *killed* by a store through a pointer that might alias cam? cam is a local pointer variable — stores to memory don't kill it.

What if cam is a **hard register via a local register variable**? That's a pin — not allowed.

Hmm hm. What about **the second use reading the pointer value through a call-result-like expression**? no.

Let me try the experiment that will settle it: does a QImode store at a VARYING address (e.g. `*(u8 *)obj = 0;`) force the reload? If yes, I know the mechanism works; then I need to make it dead or accept +1 insn. Let's test: candidate w4 = w1 + `*(u8 *)((u8 *)obj + 0x1E) = 0;`? Hmm, that's a real store (changes semantics — the object's byte). Not acceptable as a match? It would change the function's behavior — a semantic change. The target has no such store. So the match would fail on insn count anyway.

But as a *diagnostic* it's useful: if the pointer reloads, the mechanism is confirmed and I can look for a dead variant.

Actually, hold on! There's a much better idea: a **dead byte store to the local `svec_in` through a POINTER VARIABLE whose value is unknown to cse**. E.g.:

```
u8 *p = (u8 *)&svec_in;
...
p = (u8 *)obj;        /* 2nd set: cse no longer knows p's value */
*(u8 *)p = 0;         /* dead? no — obj points to real memory */
```
Not dead.

Alternatively: make the *store address* vary by using an unknown base but pointing at a dead local: `u8 *p = (u8 *)&svec_in; ... ; p += 0;`? The address is `(plus (reg p) (const 0))` with p's qty_const known → doesn't vary.

Hmm, what if p's value is known but we do `p = p + 0` where 0 is a variable? Then cse can't fold → varies. But flow's dead-store: the store `(mem:QI (plus (reg p) (const)))` — p is a pseudo with a known value? flow's insn_dead_p can't trace it → not deleted.

Hmm, but flow's dead store elimination uses `last_mem_set` and compares rtx_equal... Actually the wall tag "flow-dead-store — flow.c insn_dead_p (last_mem_set + rtx_equal_p) deletes the repeated b[0]/b[2] stores" suggests flow deletes repeated stores to the same memory. Hmm.

Let me look at flow.c's insn_dead_p to see what stores it deletes.
