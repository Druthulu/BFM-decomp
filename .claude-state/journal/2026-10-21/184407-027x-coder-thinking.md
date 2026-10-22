---
ts: 2026-10-22T00:44:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_JNrMTydtmkvcQ7qS4s5h
---
The dead-reset pattern: `p = expr; f(..., p); p = 0;` — cse invalidates the equivalence at the second set, flow deletes the dead set before sched1.

So the pattern breaks the equivalence for the FOLLOWING use. But does it break it for all 6 uses, or only the immediately following one? In the pattern, the reset invalidates the pseudo's equivalence; the next use re-derives.

For our 6-use case, the safest approach: use the reset after EACH use, and re-name the address each time. But re-naming requires a live assignment `p = &buf;` before each use — that's a real store (or register).

Hmm. But maybe: the pattern `p = expr; f(p); p = 0;` repeated — the second iteration's `p = expr` is a NEW set of p, which is a "real 2nd set". Then `f(p)` uses that set. Then `p = 0` again.

Actually think about cse semantics: reg_equiv[p] is set to &buf at each `p = &buf`. At each use, cse forwards reg_equiv[p] → the address constant → the same address pseudo (from the hash table) is reused → all 6 uses share one pseudo again. Unless the resets invalidate the hash entries.

Hmm, but the cookbook says "cse's forward scan invalidates the equivalence at the second set". "at the second set" = when the variable is set the second time, the equivalence is invalidated. So a second assignment to p invalidates the old equivalence, and then the new set re-creates it. If the second assignment's value is the same address, cse would find the address in the hash table and reuse the same pseudo → same unification.

But the G10 example: use 1 via p1 (set &addr), then p1 = 0 (reset), then use 2 DIRECT (&addr spelled inline, not via p1). The direct spelling after the reset gets a FRESH pseudo (because the hash entry for that address was invalidated by the reset). So the reset invalidates the address's hash entry.

Why would `p1 = 0` invalidate the address hash entry? Because in cse.c's record_store: when storing to p1 (a stack slot), cse invalidates reg_equiv entries that are "pointers into" ... no. Hmm, alternatively: cse.c's `record_store` calls `invalidate_refs` and for the memory location, and there's the "rt_pointer" logic:

In GCC cse.c, there's this in `record_store`:
```c
	  /* If we are storing to a memory location, then any reg_equiv
	     that contains a pointer to that location is invalid... */
```
Hmm no, actually I now recall the relevant code in gcc/cse.c `record_store`:

```c
      /* If this is a store to a memory location, then invalidate
	 any reg_equiv that holds a pointer to that location... */
```
Actually here's the genuine snippet (gcc 2.7/4.x cse.c):

```c
	  /* If we are storing into a memory location, then invalidate
	     any reg_equivs that are pointers to that location... */
	  FOR_EACH_REG (reg)
	    if (REG_P (reg) && reg_equiv_contents[reg].rt_pointer)
	      ...
```
No.

I recall instead: cse.c has `check_dependencies`, `equivs`...

Honestly the mechanism detail doesn't matter much — empirically the project proved the pattern works. Let's just try it.

Plan for item 1 candidate 2:

```
void func_8018A180(s32 a0) {
    Prim_8018A180 prim;
    MtxBuf_8018A180 buf;
    s32 *pb;
    s32 iVar1;

    prim.rgb = 0x282828;
    prim.tag = 0x60000000;
    {
        s32 ang = 0xE;
        pb = (s32 *)&buf;
        func_8012EA90(a0, ang, pb);
        pb = 0;
    }
    pb = (s32 *)&buf;
    func_8012F14C(pb, (s32)&D_801921E8, (s32)&prim.v[0]);
    pb = 0;
    ...
```
Hmm, that's a lot of stores. But maybe gcc keeps pb in a register (then pb=0 → `move`/`li`), and the address assignment `pb = &buf` → `addiu pb,sp,56` — a register copy, not a memory store, if pb is a local whose address doesn't escape and gcc promotes it to a register (SRA). Then pb = &buf; call(pb) → gcc might coalesce pb into a1 directly.

Actually simpler: since gcc's RTL for `p = &buf` is `set p, &buf` and the use is `set a1, p` — copy propagation at RTL (flow) will forward, giving `set a1, &buf` → `addiu a1,sp,56`. And the `p = 0` becomes `set p, 0` which flow deletes (dead). So the whole thing collapses to the same as before, except cse sees the extra sets.

So maybe the pattern reduces to: `p = &buf; use(&buf); p = 0;` — where the use is spelled directly.

Key question: after `p = 0`, does a later direct `&buf` get a fresh pseudo?

In G10: `p1 = sp10 + 4; func(sp10, p1, 1); p1 = 0; func(sp10 + 4);` → result: address materialised twice, once per use. So yes: the reset broke the unification between use 1 (via p1) and use 2 (direct).

So in our case with 6 uses, we could do:

```
pb = (s32 *)&buf;
func_8012EA90(a0, ang, pb);     /* use 1 via pb */
pb = 0;                          /* dead reset */
func_8012F14C((s32 *)&buf, ...);  /* use 2 direct */
pb = 0;                          /* another reset? */
func_8012F14C((s32 *)&buf, ...);  /* use 3 direct */
```
Hmm, the second `pb = 0` is dead (pb already 0). Would a second reset invalidate the fresh equivalence of use 2? If the reset invalidates the address's hash entry, then yes, each reset breaks it.

But the first use is via pb (a register holding the address). In the target, use 1 (arg3 of func_8012EA90) is `addiu a2,sp,56`. If pb is used at use 1, gcc would forward to a2 anyway.

Alternatively all uses direct, with a reset before each:
```
pb = (s32 *)&buf;   /* the only set */
func_8012EA90(a0, ang, (s32 *)&buf);   /* use 1 direct */
pb = 0;   /* reset */
func_8012F14C((s32 *)&buf, ...);  /* use 2 direct */
pb = 0;   /* reset (dead) */
...
```
Hmm, but if the resets are dead, flow may delete them all → back to square one. In G10, the reset was deleted by flow but the cse effect persisted — meaning cse ran BEFORE flow? Or the deletion happened after cse.

GCC pass order (2.7/4.x): expand → ... → flow (pass_flow) → ... → cse. Hmm, actually in GCC's pass.def:
```
  NEXT_PASS (pass_expand);
  ...
  NEXT_PASS (pass_flow);   /* in the "flow analysis" group? */
```
Let me recall pass.def ordering:
```
  /* Flow analysis.  */
  NEXT_PASS (pass_flow);
  /* Loop analysis.  */
  NEXT_PASS (pass_loop);
  ...
  /* Some minor cleanups.  */
  NEXT_PASS (pass_cse); -- no
```
Actually pass.def order is roughly:
expand, fre, ..., jump, ..., cse, ..., flow, loop, ..., sched1, ...

Hmm. In GCC 4.x pass.def:
```
  NEXT_PASS (pass_expand);
  ...
  NEXT_PASS (pass_jump);
  ...
  NEXT_PASS (pass_cse);
  NEXT_PASS (pass_expand);
  ...
  NEXT_PASS (pass_flow);
```
I'm fairly sure `pass_flow` comes AFTER `pass_cse` in modern GCC? No...

GCC 4.7 pass.def excerpt:
```
  /* Perform CSE and PRE optimizations.  */
  NEXT_PASS (pass_cse);
  NEXT_PASS (pass_pre);
  ...
  /* Flow analysis.  */
  NEXT_PASS (pass_flow);
```
Hmm, I recall:
```
  /* Flow analysis to compute better flow for the scheduler.  */
  NEXT_PASS (pass_flow);
```
being near the end (before sched1). And cse is in the "expand/cse" group earlier. Actually here's GCC 4.x order:

expand, fre, ..., jump, ..., cse (in "local optimizations" group), ..., flow (in the "flow analysis" group: flow, loop, ..., sched1, sched2, local_alloc, global_alloc, reload).

Hmm no. Let me think about the actual pass.def from GCC 4.6:

```
  /* Perform global register allocation.  */
  ...
  /* Flow analysis.  */
  NEXT_PASS (pass_flow);
  /* Loop analysis.  */
  NEXT_PASS (pass_loop);
  ...
```
and earlier:
```
  /* Perform CSE and PRE optimizations.  */
  NEXT_PASS (pass_cse);
  NEXT_PASS (pass_pre);
  ...
```
Wait, but there's also `pass_expand` twice, and `pass_flow` appears twice: once as `pass_flow` in "Tree level flow" (early) and once as `pass_flow` RTL-level? In pass.def there's:
```
  /* RTL-level dead code elimination... */
  NEXT_PASS (pass_rtl_dce);  (in RTL dce group, near the end)
```
and
```
  /* Perform RTL-level CSE... */
```

The classic RTL `flow` pass does: copy propagation (CONSTANT_PROPOGATION), dead code elimination, jump threading, and "propagate_jumps". The classic `cse` pass does common subexpression elimination.

In pass.def (GCC 4.x):
```
  /* Perform the first scheduled pass... */
  ...
  NEXT_PASS (pass_flow);   /* RTL flow */
  ...
```
I'm now fairly convinced the RTL flow pass runs BEFORE cse in GCC 4.x. Hmm, no! Here's a snippet I'm more confident about, from gcc/pass.def:

```
  /* Perform CSE and PRE optimizations.  */
  NEXT_PASS (pass_cse);
  NEXT_PASS (pass_pre);

  /* Expand complex arithmetic.  */
  NEXT_PASS (pass_expand);

  /* Perform another round of global register allocation.  */
  ...
  /* Flow analysis to compute better flow for the scheduler.  */
  NEXT_PASS (pass_flow);
```
So order: cse → pre → expand → ... → flow → loop → ... → sched1.

But then the project's note says "flow deletes the dead set BEFORE sched1" — consistent with flow being after cse. And "cse's forward scan invalidates the equivalence at the second set" — cse sees the reset.

So the mechanism: cse sees `p = 0` (a new set of p) and invalidates the equivalence; but how does that affect the *address*? Because in cse.c, `record_store`/`invalidate_refs`...

AH WAIT. I bet I know: it's not about the address hash. It's that cse tracks reg_equiv[p] = &addr. The USE at the call gets the address. Then `p = 0` sets reg_equiv[p] = 0. Then the next direct use `&addr`: cse's `cse_find_best_addr`/`find_reg_in_set` looks up the address in the hash table `equivs` → finds the OLD pseudo (which had reg_equiv = &addr) → makes the new use equivalent to it → SAME pseudo reused. That's the problem.

But GCC's cse.c has in `record_store`:
```c
      /* If we are storing to memory, then invalidate any reg_equiv
	 whose value is a pointer to that memory... */
```
Hmm, alternatively, cse.c invalidates reg_equiv entries when the pseudo's *value* is a pointer into memory that is written to. `p = 0` writes to p's stack slot. The address pseudo's value is a frame address (sp+56), not related to p's slot.

Alternatively! Maybe the mechanism is in cse.c's handling of a *constant* value: when cse sees the new set `p = 0`, and later the direct `&addr` use, the difference is that the old pseudo (holding the address) is in the "equivs" hash, and cse's `cse_record_equiv`/`record_eq` for the address...

You know what? GCC's cse.c `record_store` contains this real code:

```c
	  /* If we are storing into a memory location, then any reg_equiv
	     that holds a pointer to that memory location is invalid... */
	  /* The following is the code that handles the case of storing
	     into a memory location: */
	  ...
	      if (reg_equiv_contents[reg].rt_pointer == 1
		  && ... )
```

I recall GCC cse.c has:

```c
/* Return true if we should perform a full array copy... */
...
	  /* If this is a store to a memory location, and the value stored
	     is a pointer, then ... */
```

I give up on the exact mechanism; empirically in this project it works for 2 uses. Let's just TEST it for 6 uses. Empirical loop is cheap-ish (each try ~10-30 s?).

Actually, wait. There's a much more important consideration: does the *whole* approach even work for 6 uses? The target has 6 addiu's. Let me test candidate 2 with the dead-reset pattern.

Let me be careful about what "dead reset" means concretely: `pb = 0;` where pb is a local pointer that is dead afterwards.

Design candidate 2:
```
void func_8018A180(s32 a0) {
    Prim_8018A180 prim;
    MtxBuf_8018A180 buf;
    s32 *pb;
    s32 iVar1;

    prim.rgb = 0x282828;
    prim.tag = 0x60000000;
    {
        s32 ang = 0xE;
        pb = (s32 *)&buf;
        func_8012EA90(a0, ang, pb);
        pb = 0;
    }
    func_8012F14C((s32 *)&buf, (s32)&D_801921E8, (s32)&prim.v[0]);
    pb = 0;
    func_8012F14C((s32 *)&buf, (s32)&D_801921F0, (s32)&prim.v[1]);
    pb = 0;
    func_8012F14C((s32 *)&buf, (s32)&D_801921F8, (s32)&prim.v[2]);
    pb = 0;
    func_8012F14C((s32 *)&buf, (s32)&D_80192200, (s32)&prim.v[3]);
    ...
```
Hmm wait, but the `pb = 0` after use 1 is what breaks the equivalence for use 2. But for use 3, we need another break — but pb is already 0 and dead; a second `pb = 0` is a no-op store (dead, deleted) — would cse still "invalidate"? If cse's invalidation is triggered by "a new set of pb", then `pb = 0` when pb is already 0 — gcc's cse would see a set of a pseudo to a constant 0 while reg_equiv[pb] is already 0 → it's a redundant set; cse might not record a new set (or it does, but the pseudo is the same).

Alternative: assign pb = &buf before each use (making a new set each time), and reset pb = 0 after each use:
```
pb = (s32 *)&buf;
func_8012EA90(a0, ang, pb);
pb = 0;
pb = (s32 *)&buf;
func_8012F14C(pb, ...);
pb = 0;
...
```
Each `pb = &buf` is a new set of pb with the same value → cse would forward the same address constant → same pseudo. Hmm.

Unless the *reset* to 0 invalidates the address's hash entry each time. If the mechanism is "the store p=0 invalidates the equivalence of the address pseudo", then after each reset, the next use re-derives a fresh pseudo, and the subsequent reset invalidates it again. That would work for N uses!

So the pattern per use:
```
pb = (s32 *)&buf;   /* set */
use(pb);            /* use */
pb = 0;             /* dead reset: invalidates */
```
And since `pb = &buf` after a reset is a new set, and after use the reset invalidates again... Each use gets its own pseudo with 1-2 refs → remat → each use emits `addiu aN,sp,56`.

But will `pb = (s32*)&buf` emit a separate `addiu pb,sp,56` + `move a1,pb`? At RTL, `pb = &buf` is `set pb, (frame addr)`, and the use `a1 = pb` — flow's copy propagation forwards → `set a1, &buf` → `addiu a1,sp,56`. If the pb set is dead afterwards (reset to 0), flow deletes it. So we get exactly one addiu per call.

But careful: does flow's copy propagation run before cse? No, flow after cse. cse itself does the forwarding. Fine — either way, one addiu.

So candidate 2 = the repeated pattern. Let's write it. But the `pb = 0` resets: after the last use, do we need one? Probably not.

Also: the `ang` launder removal may cause the ordering residual (key 4: the first call's `addiu a1,$zero,0xE` must come BEFORE `addiu a2,sp,0x38`). With the plain `s32 ang = 0xE;` the const move to a1 might be ordered after the a2 materialization. We'll see from the diff. Note the target order: at the first call, `addiu a1,zero,0xE` then `addiu a2,sp,56`? The comment says "the first call's addiu $a1,$zero,0xE must be emitted BEFORE addiu $a2,sp,0x38. The stmt-expr for arg3 forces arg3 to be pre-computed during argument evaluation, which lands its insn ahead of the plain constant's move-to-hardreg. Launder the constant too (ang) so it is likewise pre-computed, at an earlier textual position — the two empty asms cost 0 bytes and the order flips to match."

Hmm, so with the laundered `ang`, the `li a1,0xE` is emitted early (before the a2 addiu). Without it, gcc emits `li v0,0xE; move a1,v0`? or `addiu a1,zero,0xE`? The target has `addiu a1,$zero,0xE` — a direct constant into a1. In plain C, `func_8012EA90(a0, ang, &buf)` with ang a constant variable: gcc would emit `li v0,0xE` (or `addiu v0,zero,0xE`) then `move a1,v0`, unless it coalesces the constant into a1 (gcc does coalesce constants into the argument register sometimes: `addiu a1,zero,0xE`).

Note the target uses `addiu $a1,$zero,0xE` per the comment (not `ori`/`li`). GCC emits `li v0,0xE` as `addiu v0,zero,0xE`? For 0xE, gcc's `li` expands to `addiu reg,zero,14` (since it's a small constant that fits in addiu immediate). And if it's coalesced into a1 → `addiu a1,zero,14`.

OK, the ordering issue: in plain C with statement order (a0, ang, &buf), gcc evaluates args right-to-left typically (for MIPS, args are evaluated in reverse order to fill a0,a1,a2). So &buf (arg3) is evaluated first → addiu a2,sp,56 first, then ang → addiu a1,zero,14. Target wants the opposite. Hmm, but with the launder, the ordering flipped because the stmt-expr forces arg3 pre-computation... confusing.

We'll see from the diff output. Let's write candidate 2 and score.

Also note: the diff earlier for cand01 showed target lines like "addiu a0,sp,56" for the func_8012F14C sites — wait, target shows `addiu a0,sp,56` at mine[14] etc. (a0 = first arg of func_8012F14C). Yes so each of the 4 later calls has `addiu a0,sp,56`, and the first call has `addiu a2,sp,56` (arg3) plus `addiu a1,zero,0xE`.

Great, so the target materialises the address per call: 6 addiu's total (a2 once, a0 four times, and the last site func_80017274((s32)&prim, (s32)&buf) → a1 = &buf → `addiu a1,sp,56`).

So we need 6 separate address pseudos.

Let me write candidate 2 now.

One concern: the `pb` variable — its type must accept &buf. `(s32 *)&buf` — buf is MtxBuf_8018A180. Fine.

Let me write it.
