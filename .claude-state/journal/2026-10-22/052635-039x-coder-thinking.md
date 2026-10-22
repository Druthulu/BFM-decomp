---
ts: 2026-10-22T11:26:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_w2H1rxljcCIuhEn8ZwmH
---
No sched1.c source. OK.

Let me take the pragmatic route: I've got 41 tries on item 2. Let me try a handful more targeted at "make the load's dest have 2 sets" and "make the li's priority lower", then move on.

Actually — NEW IDEA that I think is quite promising:

**Make the a1 argument's setup NOT a constant insn but a dependent one.** The target's `li a1,320` — hmm, what if instead we could make the CALL take the args in a way that the a1 setup is `li a1,320` but is emitted LATER?

What if the args are: `func_8001D0E8(t, 0x140, 0xF0)` → what if we write `func_8001D0E8(t, 0x140, 0xF0)` but with the call being to a variable function pointer? `((void(*)(s32,s32,s32))func_8001D0E8)(...)` — tried (e27) → 2.

Hmm.

**IDEA: change WHICH register the load's result goes to.** The target: `lw a0,32(s0)`. What if the load's result were used by the call as a1 instead of a0? No, semantics.

**IDEA: What if the load were `lw` from a different base so it becomes a "different" insn?** No.

Let me now try: **make the load's destination a pseudo that is live across the call** — i.e., `t` used after the call. Then the copy to a0 can't coalesce (t must survive the call in a callee-saved reg) → extra move. Unless... hmm.

Actually!!! Wait. Let's look at the target again:

```
3ad4: lw a0,32(s0)
3ad8: li a1,320
3adc: jal func_8001D0E8
3ae0: li a2,240
```
Then:
```
3ae4: j 3c60
3ae8: sb zero,117(s0)
```

Hmm, `sb zero,117(s0)` is the `*(u8 *)(p + 0x75) = 0;` — in the delay slot of the j.

OK. Now: in the TARGET, the load is `lw a0,32(s0)`. a0 is a hard reg. In the CANDIDATE (coalesced), the load is also `lw a0,32(s0)` but scheduled later.

**Let me test the hypothesis that the LOAD's position is determined by the `sh` before it**: in the target, the load is the delay slot of `sh v0,14(s0)`. In the candidate, `li a1,320` is the delay slot. GCC's `delayed.c` (the `dbr` pass) fills delay slots! The dbr pass runs AFTER scheduling (it's the last pass: greg → dbr). The `dbr` pass's `mips_fill_delay_slot` can MOVE an instruction into a delay slot if it's safe.

**THAT'S PROBABLY IT!** The `dbr` (delayed branch) pass reorders to fill delay slots. It picks the instruction to put in the delay slot based on `INSN_COST` and whether it's safe to move.

Hmm, but in the target the load was already first in the block. And in the candidate the li is first. If dbr moved things, the .sched dump would show the pre-dbr order... The .sched dump (after sched1) already showed [240, 238, 242, 244]. So sched1 produced it, not dbr.

Hmm OK.

Let me try ONE more thing which is very cheap and might be decisive: dump the candidate's RTL right before sched1 but I can't isolate.

FINE. Let me try a batch of "load dest has 2 sets" variants:

f01: `t = load; t = t;` (tried e16 → 2)
f02: `t = load; { s32 u; u = t; u = u; call(u,...); }` 
f03: `t = load; call(t, 0x140, 0xF0);` where t is used twice: `call(t, 0x140, 0xF0)` and `if (t == 0x7fffffff) { }` 
f04: use `p` twice: `t = ((Unkstruct_80126B58 *)p)->unk20;` with p assigned twice? `p = (u8*)arg0; p = p;` — that gives p 2 sets! And p is the base of the load. Hmm, does that change the load's priority? Maybe!

Hmm — actually THAT's interesting: give `p` a second set. `p = (u8 *)arg0; p = p;` → p has 2 sets. The load `lw a0,32(s0)` depends on p.

f05: `p = (u8 *)arg0;` then use `p` in the load as `*(s32*)((u8*)p + 0x20)`.

f06: Make the LOAD depend on the immediately-preceding store (so its priority is "late" but it can't move)... no, we want early.

Let me think about it as: we want the load EARLIER. The scheduler put it after li a1. To make it earlier we need HIGHER priority (sched1's priority = deps' priority sum). The load's deps: s0 (pseudo, defined in an earlier block → no in-block dep). The li: none.

So the load has priority 1 (base) and the li has priority 1. Tie → LUID → load first. But observed li first!!!

So the priorities must NOT be tied. Which means GCC's sched1 gives the li a HIGHER priority. WHY?

**AH — I BET I KNOW!** GCC's sched1 `compute_priorities` computes the priority as the number of insns that DEPEND on the insn (fanout), i.e., "how many insns will be delayed if I schedule this late". The load (a0) is used by the call → fanout 1. The li (a1) is used by the call → fanout 1. Hmm, tie again.

OR the priority = "the number of insns that must be scheduled after this one" — for the load, the call must come after → 1; for the li, the call must come after → 1.

Hmm.

OR the priority involves the call's "issue rate": GCC's sched1 tries to fill the delay slot, and for a call, the insns that SET UP the arguments must be scheduled before the call — but GCC's sched1 has a rule that the LAST argument setup should be as close as possible...

Hmm, what if the difference is the "hard reg" vs "pseudo" distinction: the load writes a0 (hard reg) → the call also uses a0 → the load has an ANTI-DEP with the call. The li writes a1 → also anti-dep with the call.

Argh.

**LET ME TRY THE OPPOSITE**: what if I can make the load have a HIGHER priority by making it feed MORE insns? E.g., the load's value used by 2 things. Not possible without extra instructions.

**OR** make the load's priority higher by making it depend on an insn with high priority... no, that makes it later.

Hmm, hold on! Maybe the priority works the OTHER way in sched1: GCC's sched1 `rank_for_schedule` returns `INSN_PRIORITY(tmp) - INSN_PRIORITY(tmp2)` and the caller picks the LARGER. If the priority = "number of predecessors in the block", then:
- load: 0 predecessors in-block → 0
- li a1: 0 → 0
- a2: 0 → 0
- call: 3 → 3
All the same except the call.

Hmm, and if the tie-break is LUID ASCENDING, the load (238) would be first.

BUT: what if the tie-break is LUID DESCENDING in GCC's sched1? Then a2 (242) would be first, then a1 (240), then load (238). Observed: a1 (240), load (238), a2 (242). Not that either.

So there IS a priority difference: a1 > load, and load > a2.

What distinguishes a1 from a2? a1 = 320, a2 = 240. Hmm! 320 = 0x140, 240 = 0xF0. Both `li`. Hmm.

What distinguishes the load from a2? The load has a data dep into the call (a0 is an INPUT), while a1/a2 are also inputs. Hmm, all three are inputs to the call.

Hmm, unless... the call's operands: `(use (reg:SI 6 a2)) (use (reg:SI 5 a1)) (use (reg:SI 4 a0))`. All three are uses.

But the DEPENDENCY LOG: for the call, the log links to 238 (a0), 240 (a1), 242 (a2) — as shown in the dump: `(insn_list 238 (insn_list 240 (insn_list 242 (nil))))`.

Hmm, so for the CALL, deps = [238, 240, 242].

In `compute_priorities`, the priority of the call = sum of its deps' priorities + 1. And each of 238/240/242 has priority 1 (base). So call = 4.

And the priority of 238/240/242 = 1 each. Then the tie-break LUID → 238 first. STILL contradicts.

Unless `compute_priorities` in GCC 2.7 sched1 computes priorities as "the number of insns that DEPEND on this insn" (fanout) and the call's fanout... The call has fanout 0 (nothing depends on it). The load has fanout 1 (the call). a1 fanout 1, a2 fanout 1. Tie.

Hmm, unless there's the `SCHED_GROUP_P` call-group logic: in sched1, when the scheduler encounters a call_insn, it schedules the "group" of insns that set up its arguments TOGETHER (in RTL order). But the observed order isn't RTL order.

Hmm, hold on — actually, let me re-read the observed order: [240: a1=320], [238: a0=mem], [242: a2=240], [244: call].

What if the SCHEDULER didn't reorder at all, and this order came from the RTL after some pass? The .cse2 dump showed [235: load→167], [238: a0=167], [240: a1=320], [242: a2=240], [244: call]. The .sched dump showed [240, 238, 242, 244] with 238 = `set a0 = mem`.

So between cse2 and sched, the load 235 and the copy 238 merged into one insn (uid 238, content = load into a0). The order became [240, 238, 242, 244]?? That means the insn 235 was DELETED and 238 kept, but 238 now sits AFTER 240. So the MERGE moved the insn's position!

That's a COMBINE artifact: combine replaced insn 235's pattern with the copy's and deleted 235... but then the order should stay [238, 240, 242, 244].

UNLESS: the merge happened in the COALESCE pass (local-alloc/register-alloc), where the copy `a0 = 167` was coalesced with 167, and then 167's definition (the load) was rewritten to write a0 and the copy deleted. Then the order would be [load(a0), a1, a2, call]. Still not matching.

Hmm, but the .sched dump shows the ORDER [240, 238, 242, 244]. So the reorder happened in sched1.

Wait, actually — maybe the .sched dump's insn ordering in the file isn't the block order! In GCC's RTL dump, insns within a block are printed in the order of the insn_list. The dump printed:
```
(insn 240 246 238 ...)
(insn 238 240 242 ...)
(insn 242 238 244 ...)
(call_insn 244 242 246 ...)
```
The prev/next fields: insn 240's prev=246, next=238. insn 238's prev=240, next=242. insn 242's prev=238, next=244. call 244's prev=242, next=246.

So the chain is: 246 → 240 → 238 → 242 → 244 → 246. So the ORDER is indeed 240, 238, 242, 244. Confirmed: sched1 produced it.

OK so GCC's sched1 picked 240 first.

Hmm! Let me look at the `dbr` dump to see if the delayed pass changed it. Actually, let me check whether the .sched dump is BEFORE or AFTER the final `.s`. The .s file would show the final order. Let me check the .s from the candidate dump (cand.s) around func_8001D0E8. If .s shows the load first, then a later pass (dbr) fixed it and my whole analysis is wrong!

Let me check cand.s.

Wait, but the final object (cand.o) showed `li a1,320` first. So no.

Hmm, OK.

Let me look at GCC 2.7's sched1 `compute_priorities` — I'll try to recall harder. From GCC 2.7 sched1.c:

```c
/* Compute the priority of each instruction in the block...  */

static void
compute_priorities (block, insns, n_insns)
     rtx block;
     rtx *insns;
     int n_insns;
{
  int i, j, n;
  rtx insn;

  /* First compute the number of insns in the block... */

  /* Set the priority of each insn to the number of insns that depend on it... */
  ...
  for (i = 0; i < n_insns; i++)
    {
      insn = insns[i];
      /* Set the priority of the insn to 1 (itself)... */
      INSN_PRIORITY (insn) = 1;
      /* Add in the priorities of the insns it depends on... */
      ...
    }
  /* Now, for each insn, add the priority of the insn to the insns
     that depend on it... */
  ...
}
```

Hmm.

And GCC 2.7 sched1.c ALSO has this important piece — the "call group":

```c
	  /* If this is a call, then all the insns that set up its arguments
	     must be scheduled before it, and we want to schedule them
	     as late as possible...  */
```

Hmm.

And there's this (from GCC 2.x sched1.c `compute_priorities`):
```c
      /* If this insn is a call, then it has a higher priority because
	 we want to schedule it early to fill the delay slot... */
```

OK. Let's try a totally different empirical approach to find what makes the load first: **try a version where the call's FIRST argument is not the load but something else, and see if the load's position changes.** E.g., if the load were the SECOND arg... semantics break.

Alternatively: try `func_8001D0E8(t, 0x140, 0xF0)` where `t` is loaded via `lhu`? no.

Hmm, let me try: what if the load's pseudo is used by the call DIRECTLY (no copy)? That's v03_inline = 2. Hmm, in that case the load would be `set 167 = mem` and the call would use 167 → the allocator assigns 167 to a0. So the load insn is `set 167 = mem` with uid lower. And it still went after li a1.

Hmm OK, so the load's RTL position (uid 235) is before the li (240), yet it got scheduled after. So the priority of the li IS higher.

**AH WAIT!!! I think I've got it!** GCC 2.7's sched1 has a rule: **the insn that sets up a call's arguments must be scheduled IMMEDIATELY before the call, and among them, GCC prefers...** no.

Hmm, alternatively: **the "issue rate" / latency model**: `insn_cost` — the cost of an insn in terms of the delay it causes. A `li` (movsi) has cost 1; a `lw` (load) has a LATENCY (the loaded value isn't available immediately). GCC's sched1 `insn_cost`:
```c
/* Return the cost of an instruction, given the dependence... */
static int
insn_cost (insn, link, used)
{
  ...
  if (REG_NOTE_KIND (link) == 0)  /* true dependency */
    return insn_costs[INSN_UID (insn)];   /* the latency */
  ...
}
```
And in `rank_for_schedule` (sched1's version), the class comparison uses `insn_cost(tmp, link, last_scheduled_insn) == 1` → class 3 (independent or latency 1).

Hmm, so a load (latency 2 on MIPS?) vs a li (latency 1) — but that's about the class relative to last_scheduled_insn.

**AH, but the FIRST pick has no last_scheduled_insn.** So the first pick is by priority then LUID.

Hmm, unless INSN_PRIORITY is computed as: priority = number of insns that depend on it, PLUS the "cost" of its own latency.

Let me look at GCC 2.7 sched1.c `compute_priorities` — I'm now fairly sure it looks like:

```c
static void
compute_priorities (block, insns, n_insns)
{
  ...
  /* Compute the dependency graph.  */
  ...
  /* Now compute the priorities.  The priority of an insn is the number
     of insns that must be scheduled before it (its "birth"), plus the
     priorities of its dependencies.  */
  for (i = 0; i < n_insns; i++)
    {
      insn = insns[i];
      priority = 1;
      for (dep = LOG_LINKS (insn); dep; dep = dep->next)
	if (dep->type == REG_DEP_TRUE)
	  priority += dep->insn->priority;
      INSN_PRIORITY (insn) = priority;
    }
}
```

Hmm — for the LOAD (a0=mem), it depends on s0 (a pseudo defined in a PREVIOUS block) — is that in LOG_LINKS? The log links are computed within the block. s0's definition is in another block, so no in-block dep. So priority 1.
For the li a1: no deps → priority 1.
Tie → LUID → load (235 or 238) first.

CONTRADICTION with observation. So either my reading of the .sched dump order is wrong, or there's something else.

Let me double check by looking at the .sched dump again around the block, including the code_label and notes. Earlier output for the candidate showed:

```
(note 232 230 235 "" NOTE_INSN_BLOCK_BEG)
(note 235 232 246 "" NOTE_INSN_DELETED)
(note 246 235 240 "" NOTE_INSN_BLOCK_END)
(insn 240 246 238 (set (reg:SI 5 a1) (const_int 320)) ...)
(insn 238 240 242 (set (reg:SI 4 a0) (mem/s:SI (plus:SI (reg/v:SI 73) (const_int 32)))) ...)
(insn 242 238 244 (set (reg:SI 6 a2) (const_int 240)) ...)
(call_insn 244 242 249 ...)
```

Hmm interesting: `(note 235 232 246 "" NOTE_INSN_DELETED)` — insn 235 was DELETED. And in the cse2 dump, 235 was the load `set 167 = mem`. And 238 was `set a0 = 167`.

So in the .sched dump, insn 238 has the CONTENT `set a0 = mem` — so the load's content was merged INTO insn 238 and 235 deleted. And the ORDER: 240 (a1) comes BEFORE 238 (a0).

But hold on — is the .sched dump the order after scheduling, or is the dump just printing the insn_list in LUID order? GCC's RTL dump prints the insn list in list order. The prev/next chain says 246 → 240 → 238 → 242 → 244 → 246.

Hmm, BUT: GCC's RTL dump prints `(insn uid prev next pattern)`. The prev/next are the actual list pointers. So order = 240, 238, 242, 244.

Hmm, so yes, sched1 reordered.

BUT WAIT — what if the .sched dump is printed in a different order because of how GCC dumps? Let me verify with the TARGET (orig) dump: the order there was 235 (load), 237 (asm), 240 (a0=167), 242 (a1), 244 (a2), 246 (call) — and the prev/next chain: 235's prev=248, next=237; 237's prev=235,next=240; etc. So the dump order = list order. ✓.

And in the candidate, the order 240, 238, 242, 244 vs RTL order 238, 240, 242, 244. So ONE swap: 240 and 238 swapped.

Hmm! So sched1 swapped just those two. Interesting: maybe it's the "class" comparison. When the scheduler picks the first insn, last_scheduled_insn is 0 so no class comparison → LUID ascending → 238 first. But 240 came first.

Unless the scheduler's first pick isn't "the minimum LUID" — maybe the ready list is built and the comparison `rank_for_schedule(x, y)` is called with a specific argument order, and the LUID tie-break is `INSN_LUID(tmp) - INSN_LUID(tmp2)` where tmp = *y. The caller might pass them such that the LARGER LUID wins. Let's test with the ORIG: the block's order was 235,237,240,242,244,246 — ascending LUID, consistent with "smaller LUID first".

For the candidate: 240, 238, 242, 244. If the rule were "smaller LUID first", we'd get 238, 240, 242, 244. So a priority difference exists: 240 > 238.

**WHY would `a1 = 320` have higher priority than `a0 = mem`?**

**OHHH!!! I think I've got it: the CALL's DEPENDENCY LOG ORDER!** Look at the call's insn_list: `(insn_list 238 (insn_list 240 (insn_list 242 (nil))))`. Hmm.

Hmm, what about `INSN_PRIORITY` being the "cost"? GCC 2.7's sched1 `compute_priorities` might set:
```c
      /* The priority of an insn is its "cost" (the number of delay slots
	 it consumes) plus the sum of its dependencies' priorities.  */
```
The cost of `movsi` (li) is 1; the cost of `movsi` (lw) is also 1 (both are movsi_internal2 in the dump!). Both have the same insn pattern number (159 {movsi_internal2}). So the same cost.

Hmm, so both are `{movsi_internal2}`.

OK so they're IDENTICAL in kind. The only difference: the load reads memory (has a longer latency to its consumer).

**AH — GCC's sched1 `insn_costs[]`!** `insn_costs[INSN_UID(insn)]` is the LATENCY of the insn's result for its consumer. For a `li`, the latency is 1. For a `lw`, the latency might be 2 (MIPS load delay) or more. In `rank_for_schedule`:

```c
      link = find_insn_list (tmp, LOG_LINKS (last_scheduled_insn));
      if (link == 0 || insn_cost (tmp, link, last_scheduled_insn) == 1)
	tmp_class = 3;
```
Only relevant with last_scheduled_insn.

Hmm, but also in sched1's MAIN loop:
```c
      /* Find the highest priority insn that is ready to be scheduled. */
      ...
	  if (rank_for_schedule (&best, &insns[i]) < 0) best = insns[i];
```

Hmm.

And **`compute_priorities`** might do:
```c
      /* The priority of an insn is 1 plus the sum of the priorities of
	 the insns it depends on, where a load's priority includes its
	 latency... */
```

Honestly: the LOAD has a HIGHER latency, which in a FORWARD scheduler should make it LATER (it's fine to schedule it earlier since the consumer is delayed). GCC's forward scheduler's `insn_cost` handles this in the class comparison only.

Hmm, so with last_scheduled_insn = 0 initially...

WAIT. Actually, maybe `last_scheduled_insn` IS set initially! In GCC's sched1 `schedule_insns`, `last_scheduled_insn` might be initialized to the FIRST insn of the block (to handle the delay slot). Hmm.

If last_scheduled_insn = 246 (the block-end note?) hmm.

OK: let's test empirically. If the load's LATER position is due to the load's latency being "expensive" relative to the last scheduled insn, then... hmm.

**PRACTICAL TEST**: make the load's result NOT go directly to a0 but through a copy, i.e. keep the copy alive: `set 167 = mem` + `set a0 = 167`. Then the load is a pseudo-write (maybe no latency cost?) and the copy is a `li`-like movsi. If the scheduler then picks [load, copy, li, ...] we'd get the load first! But the extra copy insn might produce an extra `move` instruction... unless the coalescer merges them (which it does — that's exactly what happened: the coalescer merged the copy INTO the load).

Hmm. But what if the coalescer CAN'T merge because the pseudo 167 is live across something? Then we'd get an extra `move a0,167` — but wait, then 167 would be allocated to a0 and no move. Hmm.

Hmm, actually: the coalesce merged them, giving `set a0 = mem`. Fine.

So: what if the load's result is used by TWO things so 167 can't be a0? Then we'd get `set 167 = mem; move a0, 167` — an extra instruction. Unless 167 gets allocated to a1 or a2... no.

OK. Let me try: **make the load's consumer be the call's a0, but ALSO make the load's result live across the call** (used after). Then 167 can't be a0 (a0 is call-clobbered) → 167 gets a callee-saved reg → `move a0,167` extra instruction → 201 ins. No good.

Alright. Let me now try the "sched2" angle: GCC 2.7's sched2 (backward) runs AFTER sched1? The dump order was: sched, sched2, lreg, greg, dbr. So sched2 runs after sched1. And sched2 (backward) might REORDER the block!

In backward scheduling, `adjust_priority` gives the "birthing boost" to insns that make a register live with reg_n_sets == 1 → they're scheduled FIRST in the backward pass → placed LAST in the forward order.

The load `set a0 = mem`: dest a0, is a0 live before the insn (bb_live_regs)? If yes and reg_n_sets[a0] == 1 → boost → placed last. Hmm, but the load is placed in the MIDDLE.

Hmm, and in the ORIG, the load `set 167 = mem`: dest is a pseudo → `bb_live_regs` only covers hard regs → 167 not in it → no boost → normal placement.

**THIS IS CONSISTENT!** The load's dest being a HARD REG (a0) vs a PSEUDO (167) changes the sched2 behavior!

In the no-asm candidate, the load was coalesced into a0 (hard reg) → gets the boost → pushed LATE. In the orig, the load writes pseudo 167 → no boost → stays.

But the boost is a MAX priority → scheduled FIRST backward → LAST forward. Observed: the load is in the middle (2nd of 4). Hmm, "last" would be after the call? The call is last. So the load can't be after the call. So the boost would place it just before the call. Observed order: a1, load, a2, call. The load is 3rd of 4 — before the a2 and the call. If the load had the max boost (scheduled first backward), it'd be at the very END of the block (just before the call) → order would be a1, a2, load, call. Observed: a1, load, a2, call. Hmm, not quite.

OK whatever. The KEY INSIGHT stands: **the load's dest being a pseudo vs a hard reg matters.** If we can keep the load writing a PSEUDO (not coalesced into a0) AND have the pseudo end up in a0 without an extra move...

Hmm: if 167 is a pseudo with 1 set and used only by the call's a0, the register allocator assigns 167 to a0 (local-alloc) — so the load writes a0 anyway. That's what happened (coalesce).

**SO: to keep the load writing a PSEUDO at sched time, the pseudo must not be a0.** But then we'd need a move.

Hmm, unless the pseudo IS a0 but with reg_n_sets[a0] != 1 — i.e., a0 has multiple sets in the function (it does! many calls set a0). So `reg_n_sets[a0] == 1` is false → no boost. So the boost isn't from a0.

OK, so that's not it either.

Alright, I've spent way too long on item 2. Let me make a decision: **item 2 = WALL** with tag `sched1-call-group` (or refine), and move on to the other items where there may be MATCHes. But first let me try ~10 more variants with genuinely different ideas, because a MATCH here would be valuable.

Actually — hold on. Let me try ONE more structural idea that could plausibly work and that I haven't tried: **move the load into the preceding block by putting the call's FIRST argument expression at the END of the previous `if` block**... no.

**IDEA: what if the load is done via a struct member read that GCC spells as a `load` with a different insn pattern?** Same.

**IDEA: What if we give the call a 4th argument?** No, changes the call.

**IDEA: what if the `t` variable is used to compute the SECOND argument in a way that yields 320 but with a dependency on t?** Like `0x140 + (t - t)`. The front end folds `t - t`? Let me check fold-const.c in the reference source! We have fold-const.c. Let me grep for the MINUS_EXPR self-fold.

That's a concrete check. If the front end does NOT fold `t - t` (because it can't prove t has no side effects — but t is a variable, so reading it has no side effects → fold SHOULD do it). GCC's fold.c:

```c
    case MINUS_EXPR:
      if (operand_equal_p (TREE_OPERAND (t, 0), TREE_OPERAND (t, 1), 0)
	  && ! TREE_SIDE_EFFECTS (TREE_OPERAND (t, 0)))
	return zero_node;
```
Hmm, I think GCC's fold does have this. Let me check the reference source.

Let me grep fold-const.c for MINUS_EXPR.

Actually, even better: what about `0x140 ^ t ^ t`? or `0x140 + (t * 0)`?

Hmm, GCC's fold for MULT_EXPR with 0 → 0 only if the other operand has no side effects.

But here's the thing: even if the front end folds it, the result is identical to the current code. If the front end does NOT fold it, the RTL would have a computation → extra instructions.

Hmm. Unless the fold happens LATE (in cse or combine, after sched1)! Then sched1 would see a non-constant a1 setup → different priority → the load might come first! And then combine folds it back to `li a1,320` AFTER sched1.

**That's a promising lever!** The question: which folds happen after sched1?

From the dump order: cse, cse2, jump, jump2, combine, sched, sched2... we don't know the exact order. But GCC's combine is known to run late. And `combine` definitely does constant folding.

So: write the second argument as an expression that GCC's FRONT END does not fold but combine does, so that at sched1 time the a1 setup is not a constant.

Candidate expressions:
(a) `0x140 + (t - t)` — front end may fold t-t.
(b) `0x140 ^ (t ^ t)` — front end may fold t^t.
(c) `0x140 + (t & 0)` — front end folds t&0 → 0? fold.c: `case BIT_AND_EXPR: if (integer_zerop (TREE_OPERAND (t, 1)) && !TREE_SIDE_EFFECTS(...)) return zero_node;` — likely folds.
(d) `0x140 + (t ? 0 : 0)` — a COND_EXPR; the front end creates a branch! Bad.
(e) `0x140 - 0` — front end folds.
(f) `0x140 * 1` — folds.
(g) `(0x140 + 0x100) - 0x100` — folds at front end (constant arithmetic).
(h) `0x140 + (t == t ? 0 : 0)` — hmm, `t == t` is not folded at front end? Then COND_EXPR → branch. Bad.

So the only hope is that the front end does NOT fold `t - t` or `t ^ t`. Let me check fold-const.c.

Let me grep.
