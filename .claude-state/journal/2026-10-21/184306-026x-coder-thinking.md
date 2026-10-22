---
ts: 2026-10-22T00:43:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_cLIsxxy8DpCmXbxxhC4M
---
So `p1 = sp10 + 4;` then call with p1, then `p1 = 0;` (dead reset), then direct `sp10 + 4`.

The result: the address is materialised twice, once per use, no register holds it.

Interesting: so `p1 = sp10+4` + `p1 = 0` — flow deletes the `p1 = 0` store (dead). And cse's equivalence is broken.

Hmm, but wait: why does the reset break the equivalence? Because cse's reg_equiv for the address pseudo was recorded when p1 was set. The reset `p1 = 0` is a new set of p1 → cse invalidates the equivalence chain of p1 (the pseudo). Then at the second use, the direct `sp10+4` address is re-derived as a new pseudo.

Hmm, but that only affects the use of the *pseudo* — does it affect a *later* direct use (use 3)? Possibly cse would then re-unify use 3 with use 2 (both direct, same expression).

In our case with 6 uses, maybe we need a reset between each use. Let's think about what's cheap:

Option 1: a pointer variable pb, assigned &buf at each site, then dead-reset:
```
s32 *pb = (s32 *)&buf;      // set 1
func_8012EA90(a0, ang, pb);
pb = 0;                      // dead reset
pb = (s32 *)&buf;             // set 2 (real 2nd set)
func_8012F14C(pb, ...);
pb = 0;
...
```
Each `pb = &buf` is a live assignment (pb used at the next call) → gcc emits either a register copy (if pb stays in a reg) or a stack store. If pb stays in a register, the address is in a register → bad.

Hmm, but hold on: maybe not! If pb = &buf is a *constant* assignment, gcc will emit `addiu a1,sp,56` for the call arg directly if it can coalesce. Since the value is a constant address, gcc's RTL will be `addiu a1,sp,56` with the "set" being that constant — no separate register needed. The register allocator can coalesce. In the plain-C version (cand01), gcc chose to park the address in s0 because the pseudo had 6 refs. With per-use resets, each use is a separate pseudo with 1-2 refs → local-alloc remat fires → each use gets its own addiu.

The problem: `pb = 0;` resets are dead but flow removes them BEFORE cse? The G10 note says "p1 is dead after the reset, so flow deletes the store BEFORE sched1: zero bytes, zero LUID disturbance (§373)". But does flow run before cse? Order in gcc: flow (expand) → cse → ... So if flow deletes the dead store, cse never sees it! Then how does it break the equivalence?

Hmm, but the note says it worked. Maybe flow doesn't delete it because the reset makes p1's value 0 which is... hmm, p1 is dead after the reset, so the store is dead. Unless gcc keeps it because p1's address is taken? No.

Wait — maybe the mechanism is different: maybe cse runs BEFORE flow in this gcc? In GCC the pass order is: expand, ..., flow, ..., cse (which is after flow? no). GCC pass order: `expand` → `gate_debugging` → `flow` (actually flow2?) → `cse` → `sched1` → `sched2` → `local_alloc` → `global_alloc` → `reload`. Hmm: the standard order is:

1. expand
2. ...
3. flow (gcse? no)
4. cse / gcse
5. ...

Actually `pass_flow` runs early (before cse). Hmm, but "flow" in this project's terms might be `pass_flow` = "flow analysis" (the classic flow pass) which does copy propagation and dead store elimination? The classic `flow` pass (expand's sibling) does dead-code elimination at RTL? The RTL `flow` pass is `pass_flow` which runs after `pass_expand`? Hmm, in GCC: `NEXT_PASS (pass_flow);` is in the "Flow analysis" group, after expand, before CSE. And it does "Delete redundant instructions" and propagates constants? Actually pass_flow is the RTL-level flow analysis: it does copy propagation, dead code elimination, and "propagate_constant" — and it has the "PROPAGATE" behaviour.

So flow (pass_flow) runs before cse, and it would delete the dead store `p1 = 0`. Then cse sees the original body... so how does the reset break the equivalence?

Unless flow does NOT delete the store because it can't prove p1 is dead — p1's address... p1 is a local variable; after `p1 = 0;` p1 is never read. Flow's DSE (dead store elimination) at RTL: pass_flow does do dead store elimination ("delete_dead_store"). Hmm.

But the note says "p1 is dead after the reset, so flow deletes the store BEFORE sched1" — maybe it means flow deletes it later than cse? The note says "zero bytes, zero LUID disturbance". Hmm, if flow deletes it before cse, cse wouldn't see it.

Alternatively, maybe the mechanism is: cse's reg_equiv for the address pseudo. Let's think again: cse processes the store `p1 = sp10+4` → reg_equiv[p1] = address constant. Then at the call, the arg is p1 → forwarded. Then `p1 = 0` → cse sees a new set of p1 → reg_equiv[p1] = 0 (not a pointer). Then the second use `sp10 + 4` — cse computes the address again; it finds the previous pseudo (from p1's first set) has reg_equiv = the address... and since p1's current value is 0 (not the address), cse would... hmm, cse's `cse_find_best_addr`/`equivs` handling: the address constant is remembered in the hash table keyed by the address. When cse sees `sp10+4` again, it looks up the hash table for that address and finds the old pseudo → makes them equivalent again. That's exactly what "cse-const-addr" walls describe.

Unless the store `p1 = 0` invalidates the hash entry: in cse.c, `record_store` for a store to p1 (a stack slot) — since p1 holds a *pointer* (rt_pointer = 1?), cse invalidates reg_equivs of registers that point into the stored location? No, that's the reverse.

Hmm, actually GCC's cse.c `record_store` has:

```c
	  /* If we are storing into a memory location, then invalidate
	     any reg_equiv that holds a pointer to that location... */
```
Hmm.

Let me look at it from a different angle: GCC cse.c contains this (I'm fairly confident):

```c
/* Return true if we should perform a full array copy... */
...
/* Record that we are storing the value VAL into the memory location specified by MEM.  ... */
static void
record_store (regset eqs, rtx mem, rtx val, bool call_preserved, struct cse_env *cse_env)
{
  ...
      if (MEM_VOLATILE_P (mem))
	{
	  ...
	}
      else
	{
	  ...
	  /* If we are storing into a memory location, then any reg_equiv
	     that is a pointer to that location must be invalidated.  */
	  ...
```
Hmm, GCC cse.c has `rt_pointer` in `reg_equiv_contents`:
```c
typedef struct
{
  rtx reg;
  rtx eq_reg;
  int reg_qty;
  bool rt_pointer;
  bool rt_scalar;
  ...
```
and in `record_store`:
```c
	  /* If this is a store to a memory location, then any equivalence
	     that involves a pointer to that location must be invalidated. */
```
Yes! I'm now quite sure GCC's cse.c contains this code in record_store:

```c
	  /* Invalidate any memory equalities ... */
	  ...
	  /* If we are storing to a memory location, then we must invalidate
	     any reg_equiv that is a pointer to that location, because the
	     store might have changed the value there. */
```
Hmm, that would invalidate reg_equiv of the *pointer* p1 when storing to *sp10+4*? no.

OK whatever the exact mechanism, empirically the project found this works (cookbook §373). Let me check the cookbook entry §373 for the precise recipe and its scope (does it work for N uses?).

Let me grep cookbook/INDEX.md for 373.
