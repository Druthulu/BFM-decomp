---
ts: 2026-11-06T05:20:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4pfoT3838bIMG0FF8SDm
---
Both score 30 and mine 49 ins. So `__asm__("")` without clobber produces the same as no asm: mine has no frame. So the memory clobber is what creates the 16-byte frame? But wait, noasmclob still has the asm statement (empty), and its score is 30 same as nobar (49 ins). So the empty asm contributes nothing. The clobber → 16-byte frame? But with clobber, the orig body scores 0 (mine=target=55). So the clobber gives 6 extra insns: the 3 reload nops + reloads + sp adjust.

Wait: with clobber the orig body is 55 ins (target). Without the clobber, mine is 49. The difference: 2 extra reload pairs + 2 nops + sp adjust pair = 6. Yes.

So the memory clobber forces: (a) reloads of `*q` (the global) after the ptr store — 2 reloads (at the p2 use and the acc block) plus nops, and (b) a 16-byte frame?

Hmm, but the reloads: the nobar body DOES reload `lhu v0,0(t1)` after the store (at 3d44). Let me compare more carefully:

target (clobber):
```
3d24: lhu v0,0(a2)      # reload *q after store
3d28: nop
3d2c: sll v0,v0,2
3d30: lui at, D_8011F7A8
3d34: addu at,at,v0
3d38: lw v1,24(at)
3d3c: addiu sp,sp,-16
...
3d54: lhu v0,0(a2)      # reload *q again
```
candidate (nobar):
```
3d28: lw v1,24(a0)      # a0 = D_8011F7A8 + *q*4, computed BEFORE the store
```
Ah — in the candidate, the `D_8011F7A8 + *q*4` address is computed BEFORE the ptr store (using the *q value loaded at 3cec), and reused after. In the target, after the store, `*q` is reloaded (3d24) and the address recomputed.

Why? In the candidate, the compiler hoisted `*q` load and address computation before the store, because... it knows the store `ptr[2] = ...` doesn't alias D_800B9A02? No — it can't know. Unless `ptr` is derived from `D_800AE7BC[*q].f0` and the store writes through ptr; the compiler must assume it may alias the global D_800B9A02. But in the candidate it reuses the pre-store value of *q for the address — that's WRONG semantically? No wait: the target reloads *q after the store, which means the target compiler assumed the store could change D_800B9A02. The candidate compiler... also must. Hmm, but the candidate uses the value loaded before the store to compute the address `D_8011F7A8 + v*4`, then loads `24(a0)`. If the store changed D_800B9A02, that address would be stale — a miscompile? No! The candidate's `lw v1,24(a0)` uses the old *q, but the source says `p2 = *(u32**)(p + *q*4 + 0x18)`, which should reload *q. Unless the compiler proved the store can't alias D_800B9A02 — it can't.

Hold on, let me re-read the candidate asm:
```
3cec: lhu v0,0(t1)    # *q
3cf4: sll a0,v0,2
3cf8: addu v0,a0,v0
3cfc: sll v0,v0,2
3d00: addu a0,a0,t2   # a0 = D_8011F7A8 + *q*4
...
3d24: sw v1,8(a2)     # store
3d28: lw v1,24(a0)    # p2 = *(a0+0x18)
```
So the candidate computes `p + *q*4` before the store and reuses after. That's a *different program* than the source? No — cse can forward the load of `*q` past a store only if it can prove no alias. It can't. So how did it?

OH WAIT. Look at the source: `q = (u16 *)&(*(u16 *)&D_800B9A02);` — `q` is a pointer to the global. `*q` is the value. cse might treat `*q` as a load from a constant address. The store is through `ptr` (unknown). cse's memory alias analysis: after a store to an unknown address, it invalidates all memory... unless the store's address is `(mem/s:SI (plus:SI (reg) 8))` and cse can't prove no alias, so it should invalidate. But the candidate reused the *address computation* (a0) across the store, not necessarily the *load*. The address a0 = D_8011F7A8 + old*q*4 — using old *q. So the candidate DID forward the *q load past the store. Hmm.

Unless: the target's reload of *q is due to the asm clobber, and without it, GCC considers the store `ptr[2] = ...` to NOT alias D_800B9A02 because of type-based alias analysis? GCC 2.7.2 has no TBAA. Hmm.

Wait, maybe the store is through `(mem/s:SI ...)`, and `s` = struct. cse's `cse_insn` for a store invalidates memory only for addresses that "might alias". In GCC 2.7.2 cse, `invalidate_memory` clears the whole table on an unknown store unless it's a `(mem/s)` with a known base? Let me check: in cse.c, `cse_insn` handles a store: it calls `invalidate_memory`? Let me look.

Actually, cse1 processes each basic block; a store through a pointer is `(set (mem/s:SI (reg)) ...)`. cse's `cse_insn` for SET_DEST being MEM: it records the value stored and *invalidates* other memory? In GCC 2.7.2, cse does NOT do memory-based value numbering with alias analysis; it invalidates all memory entries on any store (`invalidate_memory (insn)`)? Let me check the source.

Hmm, but this is the crux: with the barrier, the *q load is after the store (target). Without, it's before (candidate). This is a scheduling/cse difference.

Let me look at the target .s again:
```
4123: sw $3,8($5)        # store ptr[2]
4124: #APP #NO_APP
4126: lhu $2,0($6)       # *q
4128: sll $2,$2,2
4129: lw $3,D_8011F7A8+24($2)
```
and candidate:
```
3d24: sw v1,8(a2)
3d28: lw v1,24(a0)       # a0 from old *q
```
Both are after the store in the *candidate too*! The `lw v1,24(a0)` is after the store at 3d24. The difference is that `a0` was computed before. So the candidate reused the *address* (which embeds *q), not the load. The address computation `D_8011F7A8 + *q*4` was hoisted before the store, which is legal only if *q is not changed by the store. GCC hoisted it (sched1 or cse) — maybe because the *q load was CSE'd with the earlier one and the address is a constant+value, and the compiler moved it.

The target recomputes `*q` after the store because the asm clobber prevented hoisting the *q load above the asm (the asm is a scheduling barrier and memory clobber).

So the essential difference is: **the asm memory clobber prevents the compiler from moving/hoisting the `*q` load and its address computation across the asm**. Pure C has no equivalent barrier. Could we achieve it by *statement order*? If the source wrote the `*q` load after the store in a way that cse/sched can't hoist... but sched1 can hoist loads freely if no dependency. The dependency is: store to ptr[2] (unknown memory) vs load *q. sched1 must treat the store as possibly aliasing, so it should NOT hoist the load above the store. But it did (in the candidate, the address computation was hoisted; the load itself was before the store at 3cec anyway — it was already there for the first use).

Right! The *q load at 3cec is before the store (needed for `ptr = D_800AE7BC[*q].f0`). The second use after the store reuses that same value via cse. The asm clobber prevents the reuse. In pure C, cse will always reuse the earlier load unless there's a store that might alias. But there IS a store (ptr[2]) between them! Why doesn't cse invalidate? Because the store is `(mem/s:SI ...)` through a pointer and cse's invalidation...

Let me check GCC 2.7.2 cse: `cse_insn` for a store to memory: it calls `invalidate_memory`? Let me look at cse.c.
