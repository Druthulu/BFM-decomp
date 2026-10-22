---
ts: 2026-10-22T00:42:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Xko7qotq1FXDdY6vhUGD
---
Confirms the analysis: target has `addiu aX,sp,56` at each site (no parked register), mine parks in s0 (frame 112 vs 104).

So the target: 6 sites each materialize `addiu aN,sp,56` (sp+0x38). The lever-free plain-C version unifies → parked in s0.

So we need each of the 6 sites to have its own address pseudo with ≤2 refs so local-alloc rematerializes.

Key insight from comment: cse unifies all six into one pseudo. We need to prevent that.

Idea A: Use different expressions for the address that cse can't fold to the same constant but gcc still emits `addiu a1,sp,56`. Hmm, gcc would emit the same instruction if the expression is e.g. `(s32)&buf.mt` (offset 0 of mt). Would cse treat `&buf` and `&buf.mt` as different? `&buf.mt` = (plus &buf, 0) → folded by combine to &buf probably.

Idea B: Use a *pointer variable* whose value is the address, with the variable assigned at each site in a way that creates "real 2nd sets":

```
s32 *pb;
pb = (s32 *)&buf;   // set1
func_8012EA90(a0, ang, pb);
pb = (s32 *)&buf;   // set2 (real 2nd set)
func_8012F14C(pb, ...);
...
```
Each assignment is a distinct set of pb. But cse: the value assigned is the same constant &buf each time; cse's reg_equiv for pb would be set to the const each time. When pb is used at the call, cse forwards the const into the use → same unification problem. Hmm. But cse's "real 2nd set" mechanism — in the pv &= 0xFF000000 case, the value changed (pv = pv & mask), so cse couldn't forward the original load's value.

So we need the assigned value to differ each time yet produce the same address. Impossible in C without asm... unless the difference is in a way gcc folds but cse doesn't. E.g. `(s32)((char*)&buf + 0)` — folded.

Hmm! What about this: cse's forwarding of a constant into a use happens only if the reg_equiv is still valid. A store to memory invalidates reg_equiv for registers whose value is a *pointer into that memory*? In GCC's cse.c, there's `record_store`:

```c
	  /* If we are storing to a memory location, invalidate any reg_equiv
	     that contains a pointer to the location ... */
```
Actually I recall in cse.c:
```c
	  else if (GET_MODE (reg) == Pmode
		   && (reg_equiv_contents[reg].rt_pointer || ...))
```
Hmm, real code from gcc/cse.c (record_store):

```c
      /* If we are storing into a register, see if we have a memory location
	 that is aliased ... */
      ...
      /* Invalidate any memory equalities ... */
      if (MEM_VOLATILE_P (mem)) ...
```
and there is:
```c
	  /* If this is a store to a memory location, then any reg which
	     holds a pointer into that location is no longer valid... */
```
Actually yes! GCC cse.c has in `record_store`:
```c
	  /* If we are storing into a memory location, then invalidate
	     any reg_equiv that is a pointer to that location... */
```
Hmm, I believe the relevant code is in `cse.c` `record_store()`:

```c
      /* If we are storing a pointer to the location, ... */
```
I'm not certain. But there IS a known mechanism: the moves.md entry "launder | func_8018CDB0 | WALL sched1-argcopy-hoist" and "barrier | func_80182268 | WALL cse-plusstore-scalar — cse: sh to (plus reg K) treated as array store, fixed scalar D_801BFCDC load kept; volatile reload shares one lui/addiu addr".

Hmm, and another: "func_80180D54 | MATCH: the §373 dead-reset p1 = 0; between the two calls invalidates cse's equivalence, so the second &sp10+4 use is re-derived (addiu a0,sp,24 in the delay slot) and the address never enters a register (G10)".

That's EXACTLY the mechanism I need! A dead reset (`p1 = 0;`) between uses invalidates cse's equivalence so the address is re-derived at each use!

So the trick: between the uses of &buf, do something that invalidates the equivalence — e.g. assign 0 to a variable that holds the address, or store something into memory that might alias.

From func_80180D54: `p1 = 0;` — assigning to the pointer variable invalidates cse's reg_equiv for the pseudo holding the address? Hmm, actually in that case p1 was the pointer variable and it was reset to 0, so the address is re-derived from a different source.

In our case, if we hold the address in a variable pb and reset it to 0 between uses... but then we'd need to re-derive &buf each time, which is the same constant → cse would unify again? Hmm, but maybe not: the point in func_80180D54 was that the second &sp10+4 use got re-derived rather than held.

Let me think about GCC's cse.c more concretely. In cse.c, `record_store` invalidates reg_equiv entries:

```c
	  /* If we are storing to a memory location, then any reg_equiv
	     whose value is a pointer to that memory (or to a part of it)
	     must be invalidated ... */
```
Actually here's the real code (gcc/cse.c, record_store):

```c
      /* If this is a store to a memory location, then invalidate
	 any reg_equiv that holds a pointer to that location... */
      FOR_EACH_REG (reg) ...
```
Hmm.

I recall in cse.c:
```c
	  /* If we are storing into a memory location, then any equivalent
	     registers that hold a pointer to that location must be
	     invalidated.  */
```
There is a mechanism "rt_pointer" in reg_equiv_contents: `rt_pointer` is set when the reg's value is a pointer (Pmode) that points into memory. Then on a store to memory, cse invalidates those. In cse.c:

```c
/* Return true if we should perform a full array copy... */
...
static void
record_store (regset eqs, rtx mem, rtx val, bool call_preserved,
	      struct cse_env *cse_env)
{
  ...
      /* If this is a store to a memory location, invalidate any reg_equiv
	 which contains a pointer to that location.  */
```
I'm fairly confident something like this exists:
```c
	  if (MEM_VOLATILE_P (mem)) ...
	  else
	    {
	      ...
	      /* Invalidate the equivalence for a register that holds a pointer
	         to the stored location. */
```
Hmm, this is the mechanism that makes `&buf` re-derived after a store to buf? Not stores elsewhere.

Actually here's the key real code from gcc/cse.c (I've seen it):

```c
	  /* If we are storing into a memory location, then any memory
	     equalities for that location are invalidated... */
```
and separately in `cse.c`'s `record_store`:

```c
      if (GET_CODE (mem) == MEM && GET_MODE (mem) == Pmode ...)
```

Honestly, the more reliable known trick from this project's own findings (moves.md): a *dead reset* of a variable between uses invalidates cse's equivalence. E.g. "the §373 dead-reset p1 = 0; between the two calls invalidates cse's equivalence".

Hmm, but that was about p1 (the pointer variable) being reset to 0. In that case the "address" was `&sp10+4` — a stack address computed each time? Let me look at that example's actual code to learn the mechanism. It's in G10's item dir: .run/P40/T11/G10/func_80180D54/... Let me read its notes.md and win.c. That's a great template.

Let me look at that.
