---
ts: 2026-11-06T09:04:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nMKC61cBrKvhEVvUw3Ot
---
v18: mine has `mflo t1; sw t1,72(sp)` at 88-89 (product + store to otz). The target has `mflo t1` at 87 and nothing at 88. So the product destination t1 matches! Only the store is extra.

So if we could make the store to otz be deleted, we'd have a MATCH. The store `sw t1,72(sp)` is at insn 89, and gte_stszotz's `sw` to 72(sp) happens much later (~insn 160). flow didn't delete it because there are intervening memory ops (lwc2, swc2 with memory clobber).

Idea: place the `otz = product` assignment right before `gte_stszotz(&otz)` AND compute the product at the right place into a temp tt:

```c
tt = (a[2]-z)*buf[5];     // right after the call: mult/mflo t1 (tt used later → temp)
...
otz = tt;                  // right before gte_stszotz
gte_stszotz(&otz);
```
Then flow sees: store otz = tt at insn X, and the next memory op is gte_stszotz's asm with "memory" clobber. Between the store and the asm there's nothing → `last_mem_set` is set to otz's slot by the store; then the asm (memory clobber) — does flow reset last_mem_set at an asm? Let me check flow.c: `last_mem_set` is cleared on a CALL_INSN or at a LABEL? Let me grep.

Actually, the store `sw t1,72(sp)` followed immediately by the asm gte_stszotz (which stores to the same slot in its asm text — flow can't see that). flow would consider the store to otz dead only if it sees a later store to the same MEM. The asm's internal store is invisible to flow (only the "memory" clobber). So the store won't be recognized as redundant → kept.

Hmm. So flow can't delete it. Unless the store is to a *register* instead of memory. otz's address is taken by gte_stszotz (asm "r"(&otz)), forcing it to memory.

What if the temp tt is assigned to otz *and* otz's slot is... no.

Alternative: make the product's destination a temp that is dead but whose set is kept because the temp is **live at a code label / needed by an asm**? No.

Hmm, what about using the product in a **store to the stack slot of `v[]` or `buf[]` that the target's own code writes anyway**? E.g., if the product were stored into a v[] slot that's written later with the same value... no.

Wait, here's a cleaner idea: the target has `mflo t1` — the destination t1 is a *dead temp*. In v18 the destination is also t1 (because otz's store is the use). If we can make the use disappear *after* register allocation? No, flow runs before allocation.

What if the use is a store to a **dead stack slot** that the compiler allocates but the target doesn't have? Any store adds an insn.

What if the use is a **store that gcc itself emits for a struct copy**? no.

Hmm, so a real use always adds at least one insn (a store) unless it's a branch (adds a branch).

Unless the use is... **the value is returned in a path that's unreachable**? If the function had an unreachable branch, gcc would delete it.

OK, but wait: v22 (`z = product`) gives `mult; mflo s3` with 512 insns and score 2 — only the destination differs. What if we make z's register be t1? No, z is s3 (callee-saved, live across calls). 

What if we assign the product to a **new variable** whose register happens to be t1 and which is dead but kept? Dead → deleted.

Hmm, what if the assignment target is a variable that is *used later* but whose later use is in a **dead branch**... no.

What if the variable is used later in a way that gets optimized to the same code as the target? Let's look at the target: after the product, `addiu v0,sp,16` and the GTE ops. t1 is not used.

So the original source had a dead result kept by something flow can't delete. What does flow not delete? `global_regs` sets, frame/arg pointer sets, and MEM stores. Also insns with `REG_UNUSED`? no.

**global_regs!** A set to a global register is never deleted. Global registers in GCC are fixed registers declared with `-ffixed-` or variables declared `register ... asm("...")` at *file scope*? Let me check: in GCC, `global_regs[]` is set in `regs.h`/`varasm.c` for variables declared `register` with an asm spec at file scope (i.e., `register int foo asm("$9");` at file scope) — those are global register variables. At function scope, `register int x asm("$9")` is a local register variable (used in the pins!). The pins in this project are function-scope `register s32 idx __asm__("$4")` — those are *local* register vars, not global_regs.

Hmm, but wait: the pins' sets — are they deleted by flow if dead? The pin `idx` is used later.

But the constraint says we may not ADD a pin (new lever). So no.

OK. What about the **FRAME_POINTER/ARG_POINTER**? no.

What about a MEM store that flow can't prove redundant? Any store shows in the target. No.

So the dead product cannot be produced by real C. This is a WALL: flow-unused-result.

Hmm, but wait — v22 gives score 2 with 512 insns: `z = product` — the 5 insns are there, just `mflo s3` instead of `mflo t1`. Since z (s3) is live (used later), the value isn't dead. That's a *semantic change* (z is modified), so it's not valid — the function's behavior changes (z is used in the loop). But delever_search only compares code shape, not semantics! However, a change that alters behavior isn't a legitimate crack (and the score is 2, not 0).

So the wall is: best lever-free = 20 (v18: product kept + extra store) or 22 (deleted). Actually "best = lowest score of a lever-free body" — the lowest is v22 at 2, but v22 is semantically wrong (it modifies z). Hmm, the score is a code-shape metric; the search doesn't check semantics. But we shouldn't claim a wrong body as "best". The honest best is v18 at 20 (the product kept with an extra store) — or maybe we can do better.

Wait, let me reconsider: can we get the product kept with the store deleted by placing the store where flow can prove redundancy? flow's `last_mem_set` mechanism: within a basic block, a store to the same MEM as the previous store (with no intervening loads/calls?) is dead. The GTE asm has a memory clobber, but flow's `propagate_block` handles asm... Let me look at flow.c around line 1479 (where insn_dead_p is called) and how last_mem_set is set/cleared.

Let me look at the code that calls insn_dead_p at 1479.
