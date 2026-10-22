---
ts: 2026-10-22T11:23:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_PO8lfP27BBwYfxlB1pEX
---
All stuck at 2. The load always ends up after li a1.

This is very robust: the scheduler always puts the li first. This suggests the priority mechanism strongly prefers the constant li.

Let me look at GCC's sched1 source. It's not in tools/reference. But maybe I can find it online knowledge: GCC 2.7's sched1.c `compute_priorities`:

```c
/* Compute the priority of each instruction in the block... */

static void
compute_priorities (block, insns, n_insns)
{
  rtx insn;
  int i, j, n;
  ...
  /* Compute the priority of each instruction as the number of instructions
     that must be scheduled before it... */
  
  /* First, compute the dependency graph... */
  ...
  for (i = 0; i < n_insns; i++)
    {
      insn = insns[i];
      /* The priority of an insn is the number of insns that depend on it,
	 plus 1 for itself... */
      ...
    }
}
```

Hmm, in GCC 2.x sched1.c:

```c
/* Compute the priority of each instruction in the block.  ... */

static void
compute_priorities (block, insns, n_insns)
{
  int i, j, n;
  rtx insn;

  /* Compute the number of insns in the block... */

  /* Set up the dependency lists... */
  for (i = 0; i < n_insns; i++)
    {
      insn = insns[i];
      ...
    }

  /* Now compute the priority of each insn... */
  for (i = 0; i < n_insns; i++)
    {
      insn = insns[i];
      /* Priority = number of insns that must be scheduled before it */
      ...
    }
}
```

I recall in GCC's sched1.c there IS a specific rule about calls:

```c
	  /* If this insn is a call, then all the insns that set up its
	     arguments must be scheduled before it.  */
```

and

```c
      /* Return the priority of an insn: the number of insns that
	 depend on it.  */
```

OK — but here's the thing that matters: the ORDER was li-a1(240), load(238), li-a2(242), call(244). If priority were "number of dependents", the load (a0) has 1 dependent (call), a1 has 1, a2 has 1. All equal.

Hmm, but the LUID tie-break (ascending) would give 238 first. So the priorities aren't equal: a1 (240) > load (238) > a2 (242)?! That's odd — a1 got picked first, a2 last.

Hmm, unless the class-based tie-break matters: `rank_for_schedule` compares tmp (the new candidate) vs tmp2 (the current best). "Choose the insn from the highest numbered class" where class 3 = independent, class 1 = data-dependent, class 2 = anti/output dependent.

Order of preference: class 3 > class 2 > class 1 (highest numbered wins). Wait: "tmp_class - tmp2_class" returned → so a HIGHER class wins. Class 3 (independent of last scheduled insn) beats class 2 (anti-dep) beats class 1 (data dep).

After scheduling li-a1(240) first:
- load(238): vs last_scheduled = 240. The load writes a0; li-a1 writes a1. Independent → class 3.
- li-a2(242): writes a2, independent of a1 → class 3.
Tie → LUID: 238 < 242 → load first. ✓ That matches (238 before 242).

And the FIRST pick: initially last_scheduled_insn is null, so the tie-break is LUID: 238 (load) should be first! But it wasn't.

So the initial pick must be by priority: a1 (240) had a higher INSN_PRIORITY than the load (238).

Why would `li a1,320` have a higher priority than the load? In GCC's sched1 `compute_priorities`, the priority of an insn is computed as:

```c
      /* Compute the priority: the number of insns that depend on it
	 (its "fanout"), plus the priority of its dependencies... */
```

Hmm, if priority = fanout, both have fanout 1 (the call).

Hmm, but there's a special rule for CALLS in GCC's sched1: the call's arguments setup insns are given a priority boost. And another special rule: an insn that is a "constant birth" (all operands are constants or ready regs) gets a boost.

Look at `birthing_insn_p` in sched2: `reg_n_sets[i] == 1` and the dest reg is live before the insn → birthing. For sched1, GCC 2.7's sched1.c has an analogous function. Let me recall GCC 2.7's sched1.c:

```c
/* Return true if PAT is the pattern of an instruction which makes
   a register live.  */

static int
birthing_insn_p (pat)
     rtx pat;
{
  int j;

  if (GET_CODE (pat) == SET
      && GET_CODE (SET_DEST (pat)) == REG)
    {
      rtx dest = SET_DEST (pat);
      int i = REGNO (dest);
      int offset = i / REGSET_ELT_BITS;
      REGSET_ELT_TYPE bit = (REGSET_ELT_TYPE) 1 << (i % REGSET_ELT_BITS);

      /* It would be more accurate to use refers_to_regno_p or
	 reg_mentioned_p to determine when the dest is not live before this
	 insn.  */

      if (bb_live_regs[offset] & bit)
	return (reg_n_sets[i] == 1);

      return 0;
    }
  ...
}
```

and in sched1's `adjust_priority`... no, that's sched2.

Hmm, in GCC 2.7's sched1.c `compute_priorities`:
```c
      /* If this is a call, then the insns that set up its arguments
	 must be scheduled before it.  */
```

I'm going in circles without the source. 

**PRACTICAL DECISION**: item 2's residual is a stubborn ORDER swap that all my plain-C variants fail to fix. The previous agent reached the same wall. I've now done 41 scored tries. To declare a WALL I need ≥30 tries and ≥20 min. Let me do a few more high-value experiments (aiming at the block-boundary hypothesis), then record the wall.

Actually — WAIT. Let me reconsider one BIG thing: the asm's REG_DEP_OUTPUT on the li a1. That is: the asm clobbers a1, so the li a1 must come after the asm. In plain C, what clobbers a1? A CALL. 

**IDEA**: What if there were a call between the load and our call? No, extra instructions.

**IDEA 2**: What if the load's value were passed to a call in a way that... no.

Hmm, hold on, let me reconsider the problem completely differently:

What if we REVERSE which instruction is the "load"? The target's `lw a0,32(s0)` at 3ad4 vs candidate's `li a1,320` at 3ad4. What if we could make the candidate produce `li a1,320` at a DIFFERENT index and the load at 3ad4? I.e., the candidate has 200 ins, same as the target, and only these two are swapped. If we could shift the li a1 later by one... e.g., if the a2 li were moved earlier: `li a2,240; lw a0,32(s0); li a1,320; jal`? No, the target has li a2 in the delay slot AFTER the jal.

Hmm what if the CALL were `jal` with the args set in a different order? The target: `li a1,320` before jal, `li a2,240` in the delay slot. Candidate: `li a1,320`, `lw a0,32(s0)`, `jal`, `li a2,240`.

So both have jal at the same position (3adc). Only the load and li a1 swapped.

**IDEA**: what if the a0 setup were a "move" instead of a load? No.

**IDEA**: What if the load were `lw a0,32(s0)` but scheduled as part of the delay slot of the PREVIOUS instruction? It IS the delay slot (3ad4 is the delay slot of sh at 3ad0).

Hmm — what if the li a1,320 could be placed in the delay slot of some OTHER instruction? Like the delay slot of the `beqz` at 39e0? That's taken by `li a1,832`.

**IDEA**: The `sched2` (backward) pass! Note the final code order might be determined by sched2 (backward scheduling). The target's order was produced by the original compile. Since sched2 works backward, the LAST instruction of the block gets scheduled first. The block ends with the call (244) then the store (249). Hmm.

Hmm, the sched2 pass in GCC 2.7 might be what put the li a1 first! In backward scheduling, the priority is computed via `birthing_insn_p` + `adjust_priority`: "Defer scheduling insns which kill registers" (INSN_PRIORITY >>= 3 for n_deaths != 0). And `birthing_insn_p` gives max_priority to insns that MAKE a register live with reg_n_sets == 1.

**AH — this is it!** In sched2 (backward), `birthing_insn_p(pat)` returns true if the insn's dest is a REG that is live before the insn AND `reg_n_sets[reg] == 1`. Such an insn gets `max_priority` → scheduled FIRST in the backward pass → which means it ends up LAST in the forward order!

So: the load `set a0 = mem` — dest a0 is a hard reg... is a0 "live before the insn"? a0 is call-clobbered; bb_live_regs would include a0? And `reg_n_sets[a0] == 1` → the load is a "birthing insn" → gets max priority → scheduled first in the backward pass → placed LAST in the final order.

In the ORIG (with asm): the load's dest is the pseudo 167 (not a hard reg). Is pseudo 167 live before the insn? Hmm, `bb_live_regs` is about HARD regs. Pseudo 167 isn't in bb_live_regs → `birthing_insn_p` returns 0 for the load → no boost → the load is scheduled LAST in the backward pass → appears FIRST in the forward order.

**THAT'S THE MECHANISM!** (Consistent with C0434: "A SINGLE-SET LOCAL IS SCHEDULED LAST; give it a second set" — and C0391: "A ZERO-BYTE RE-TIE SETS reg_n_sets=2, WHICH KILLS sched1's birthing_insn_p LAUNCH_PRIORITY BOOST".)

Wait, C0391 says the re-tie KILLS the boost. Hmm, in our case the re-tie is what we want to REMOVE.

Hmm, let me redo: in the no-asm candidate, the load's dest is a0 (a hard reg) after coalescing. `birthing_insn_p` → dest a0 is a REG; is a0 live before the insn (bb_live_regs)? a0 is a call-clobbered hard reg; at the start of the block, a0 is dead (it's set by this insn). `bb_live_regs` is the set of regs live at the block start. If a0 is not live at block start, birthing_insn_p returns 0. Hmm.

Hmm, but the load writes a0 and the call reads a0. So a0 IS live after the load. Is it live BEFORE? bb_live_regs = regs live at the beginning of the block. a0 is not live at block start (the call's a0 input is set by the load). So bb_live_regs[a0] = 0 → birthing_insn_p = 0 → no boost.

Hmm, that contradicts. But wait, maybe bb_live_regs is computed per-insn? No, it's per basic block.

Hmm, so if the load writes a0 and a0 isn't live at block start → no boost. Then the load isn't boosted. But the li a1: dest a1, is a1 live at block start? No. → no boost either.

Hmm. So neither is boosted.

OK. Then why was the li scheduled first?

Let's think about the backward pass. The block (backward) is: [store zero(249)], [call(244)], [a2=240(242)], [a1=320(240)], [load/a0(238)]. Backward scheduling starts from the END of the block (the store) and schedules predecessors.

Wait — but the final order was a1(240), load(238), a2(242), call(244). Backward from the end: call(244) is scheduled first (it's last in the block). Then its predecessors: a1(240), a2(242), load(238) — all ready. The backward scheduler picks the highest priority.

`rank_for_schedule` in backward mode: prefers class 3 (independent of last scheduled) etc.

Hmm, in the ORIG backward pass, the order was: store(249), call(246), a2(244), a1(242), a0=167(240), asm(237), load(235).

Backward: call first, then a2, a1, a0, asm, load. Note a2 before a1 — LUID descending? 244 > 242. Hmm, in the orig the order after the call is a2(244), a1(242), a0(240). That's DESCENDING LUID. And in the candidate: a1(240), load(238), a2(242) — not monotonic.

Hmm, whatever. Backward scheduling's `adjust_priority`:
```c
	  /* Defer scheduling insns which kill registers, since that
	     shortens register lives.  Prefer scheduling insns which
	     make registers live for the same reason.  */
	  switch (n_deaths)
	    {
	    default: INSN_PRIORITY (prev) >>= 3; break;
	    case 3: INSN_PRIORITY (prev) >>= 2; break;
	    case 2: case 1: INSN_PRIORITY (prev) >>= 1; break;
	    case 0:
	      if (birthing_insn_p (PATTERN (prev)))
		{ int max = max_priority; if (max > INSN_PRIORITY (prev)) INSN_PRIORITY (prev) = max; }
	      break;
	    }
```
Note: "This code has no effect, because REG_DEAD notes are removed before we ever get here." — so n_deaths is always 0! Then the birthing check applies: `birthing_insn_p` → if the insn's dest is a reg live before it with reg_n_sets == 1 → boost to max_priority → scheduled FIRST in the backward pass → appears LAST in the final order.

So the "boost" makes an insn appear LATE. 

Now: which insn is boosted in the candidate? The one scheduled LAST in the final order = a2=240 (242)? The final order is a1(240), load(238), a2(242), call(244). The LAST insn in the block (excluding the call which is last) is a2(242). So a2 was scheduled first in the backward pass → a2 got the boost → a2's dest a1?? no, a2's dest is a2 (reg 6).

Hmm, `bb_live_regs`: a2 (reg 6) — is it live before the insn? Hmm.

OK, alternatively the load was boosted: the load's dest is a0 (reg 4). Is a0 live at block start? YES! Because a0 is... hmm, in this function `p = (u8*)arg0` and arg0 is in a0 at entry, but at this block a0 is dead.

Hmm, `bb_live_regs` is the set of hard regs live at the beginning of the block. Hmm.

OK, this is really deep. Let me try to settle it EMPIRICALLY: the C0434 recipe says "give the pseudo a second set" to kill the boost. If the boost is what's pushing the load LATE, then giving the load's pseudo a second set would fix the order!

In the no-asm candidate, the load's dest is a0 (hard reg) after coalescing — reg_n_sets[a0]... hmm.

Hmm, let me instead test directly: does `t = t;` (self copy) change the order? It gave score 2. Hmm, so no change — maybe combine removed it, or the self-copy didn't create a second set.

Let me try a DIFFERENT way to give a second set: **`t = load; t = load;`** → two loads; cse removes the second. Also 2.

What about a second set that ISN'T redundant: e.g.
```c
s32 t;
t = load;      /* set 1 */
...            /* something that changes the loaded value? */
t = load;      /* set 2 */
```
No.

Hmm, what about giving the LOAD's DEST a second set through the call: `set a0 = 167` (the copy) is a second set of a0! If the copy survives (not coalesced), a0 has 2 sets → `reg_n_sets[a0] == 2` → the birthing boost is killed → the load is not pushed late!

**So: PREVENT THE COALESCING of the load into the a0 copy!** In the orig, the copy survived (because the asm broke the chain). If we can keep the copy as a separate insn, we'd get `lw 167,32(s0); move a0,167` — but that's an EXTRA instruction (the target has no move). Hmm, but the coalesce would put 167 in a0 directly, giving `lw a0,32(s0)` — 1 instruction, no move! And a0 would have... hmm, if coalesced, a0 has 1 set.

Argh.

OK, alternatively: the ORDER issue is about the load vs li a1. Let's test the hypothesis differently: if the boost applies to the load (making it late), then giving the load's dest a second set would help. The load's dest is a0 after coalescing. a0's sets in the function: many (other calls). Hmm, reg_n_sets is per-function for hard regs? `reg_n_sets` is computed per function for all regs (hard and pseudo). For a0, reg_n_sets would be large. So the birthing check `reg_n_sets[i] == 1` would fail for a0 → no boost → the load wouldn't be pushed late.

Hmm, but then what pushed it late?

OK. Let me get the DEFINITIVE answer by dumping the candidate's sched2 output and looking at the order there, plus checking `bb_live_regs`. Too deep.

**PRACTICAL PLAN**: I've spent a lot on item 2. Let me now:
1. Do a few more experiments for item 2 focused on the "second set" idea (which the cookbook says is THE mechanism).
2. Then move to the other items.

Experiments for "second set":
- Make the loaded value's pseudo have a genuine second set by using it in a way that requires a copy: e.g.
```c
s32 t;
t = load;
t = t + 0;   /* front end folds */
```
- `t = load;` then `func_8001D0E8(t, 0x140, 0xF0);` and ALSO use t in a way that's dead but creates a second set:
```c
s32 t;
t = load;
if (t == 0) { t = load; }   /* 2 sets, but a branch */
```
- **Use `t` in TWO call args?** No.

Hmm, what about this: the copy to a0! If we make the call take `t` where `t` is assigned from a DIFFERENT pseudo, e.g.
```c
s32 t;
s32 u;
t = load;
u = t;
func_8001D0E8(u, 0x140, 0xF0);
```
That's e18_extra → score 2.

Hmm.

OK let me try the LAST structural idea for item 2: **give the load a dependency so it must be early**. Hmm, no.

**FINAL IDEA for item 2**: What if the ORDER of the two is fixed by making the a1 value NOT a constant at RTL level, using a value GCC computes with the SAME instruction but different priority? The target's `li a1,320`. There's no other instruction that produces 320 in a1.

Hmm, unless... `li a1,320` vs `ori a1,zero,320` — same.

OK. Let me look at this from the "instruction count" angle: what if we ADD an instruction elsewhere so the total stays 200 and the load lands at the right index? E.g., if we could make the compiler emit the load at 3ad4 and li a1 at 3ad8 by making the load part of the DELAY SLOT of the sh... 

AH WAIT!!! Here's an idea: **what if the load is placed in the delay slot of the `beqz` branch at 39e0?** No, that's taken by li a1,832.

Hmm, what about the delay slot of the jal at 39f0 (MoveImage)? etc.

OK, let me try the completely different tack: **maybe the a1=320 should be scheduled after the load because in the target the load is in the DELAY SLOT of the preceding `sh`**. The delay slot of a non-branch instruction is filled by the block layout, which places the next block's first instruction there. The next block's first instruction is determined by the scheduler.

Hmm, here's a thought: GCC's sched1 has a special feature to fill the delay slot of the block's first branch/insn. In `sched1`, `compute_dep_list` and then in the main loop there's `if (flag_sched2 ... )`.

I'll stop. Let me now consider that item 2 might be a genuine WALL (the previous agent said so) and move on to the other items where there might be easier MATCHes. But first, let me spend a few more tries on item 2 with a couple of genuinely new ideas:

NEW IDEA A: **Make the load's pseudo be assigned TWICE by using the "in-place" trick**: the cookbook's successful launder cracks used "a real 2nd set" like `pv = *p; pv &= mask; *p = pv | ...`. Here we want the loaded value to have a second set. What about:

```c
s32 t;
t = ((Unkstruct_80126B58 *)p)->unk20;
t = t;   /* no */
```

NEW IDEA B: **use the `p` pointer copy**: `s32 t; t = ((Unkstruct_80126B58 *)p)->unk20;` where the load is written via a *different* pointer variable that has 2 sets:
```c
u8 *q;
q = p;
t = ((Unkstruct_80126B58 *)q)->unk20;
```
That adds a move (unless copy-propagated).

NEW IDEA C: **Change the STRUCTURE of the surrounding if**: the join block's first instruction is the load. In the target, the join block's first insn is the load; in the candidate it's the li. What if we make the join block's first instruction be something else that GCC schedules first, and the load gets pushed to the front?

Hmm, what if we add a statement BEFORE the load in the join block that produces NO instruction but changes the block's first insn? Like `;`? no.

NEW IDEA D: **Make the `li a1,320` not the first insn of the block by putting the load FIRST in RTL.** In RTL, the load IS first (uid 235 < 240). The scheduler chose otherwise. So the priority differs.

Let me actually check GCC's sched1 source. Maybe I can find it in the cc1 binary's source... no. But maybe pip has a copy? Or the gcc 2.7.2 source tarball is somewhere in the project: `tools/bin/gcc-2.7.2-psx.tar.gz` — that's a binary. `.run/t7/fable/gcc-2.7.2.tar.gz` — binary too.

Hmm, what about `docs/gcc-2.7.2-map`? Let me check if it has sched1 info. And the cookbook mentions "sched.c:7440", "cse.c:840", "cse.c:7440" — so the project has cse.c line references.

Let me look for sched1 references in the project docs.

Actually — hold on! Let me reconsider: is the FINAL order determined by sched1 or by sched2? The `.sched` dump is after sched1 and showed [240, 238, 242, 244] — the wrong order. And the final assembly has the wrong order. So sched1 produced it.

In sched1 (forward), GCC's `rank_for_schedule`:
```c
  /* Choose the instruction with the highest priority, if different.  */
  if (value = INSN_PRIORITY (tmp) - INSN_PRIORITY (tmp2))
    return value;
```
and `INSN_PRIORITY` is computed in `compute_priorities`:
```c
/* Compute the priority of each instruction in the block...  The priority
   of an instruction is the number of instructions that depend on it... */
```

Hmm, in GCC's sched1.c, I recall:
```c
      /* Compute the priority of this insn: the number of insns that
	 must be scheduled before it.  */
      ...
      /* Add in the priority of the dependencies of the insn. */
```

and there's this specific code in GCC 2.7 sched1.c `compute_priorities`:
```c
	  /* If this insn is a call, then all the insns that set up its
	     arguments must be scheduled before it.  */
```

Hmm.

Also important: GCC 2.7 sched1.c has:
```c
/* Return the priority of an insn ... */
static int
compute_insn_cost (insn, link, used)
```
no.

OK, ANOTHER IDEA: GCC 2.7 sched1.c has this (I'm fairly confident):
```c
/* Compute the priority of each instruction in the block.  We do this
   by finding the dependency graph and then computing the longest path... */
```
For the candidate: the load(238), a1(240), a2(242) all feed the call(244). Longest path to the call = 1 for each. Equal.

Then INSN_PRIORITY ties → class comparison → LUID.

But observed: a1 (240) was chosen FIRST, i.e., the scheduler's first pick was 240 not 238. If priorities tie and last_scheduled_insn is NULL, the tie-break is LUID ascending → 238. Contradiction!

UNLESS: the initial "last_scheduled_insn" is not NULL but set to something. In sched1, `last_scheduled_insn` is set as we go; initially it's 0.

Hmm, so with priority tie → LUID → 238 first. But observed 240 first. So the priorities are NOT tied: a1 has higher priority.

Why? **BECAUSE OF THE "CONSTANT BIRTH" RULE!** In GCC 2.7's sched1.c `compute_priorities`:

```c
      /* If this is a call, ... */
      ...
      /* Set the priority of the insn to the number of insns that
	 depend on it ... */
```

Hmm, OR: GCC's sched1 has `insn_cost` and the "issue rate" model where an insn with fewer operands is cheaper.

OR!!! Maybe: the load's dest is a0 and a0 is ALSO used by... no.

WAIT. Maybe it's about the DELAY SLOT. In the candidate block, the first instruction goes into the delay slot of the `sh` (the previous block's last insn). GCC's sched1 tries to maximize the number of insns in delay slots. There's a rule: the insn that goes into the delay slot must not have a dependency on the branch. Both qualify.

Hmm, hmm. But here's a REAL possibility: GCC's sched1 `compute_priorities` includes:

```c
	  /* If this instruction has a dependency on a previous instruction,
	     it must be scheduled after it.  */
```

and the "priority" for an insn = `1 + sum over dependencies of dep priority`. The load depends on s0 (a pseudo defined in an earlier block) — no in-block dep → priority 1. The li a1 has no deps → priority 1. TIE.

Then class comparison with last_scheduled_insn=0 → skipped → LUID ascending → 238 first.

So the observed 240-first contradicts... UNLESS the load has priority 0 or the li has priority 2.

Hmm! What if the li a1 has priority 2 because of the CALL? GCC's sched1 might give the call's arg-setup insns a priority boost so they're scheduled close to the call. And the a0 setup (load) is ALSO an arg setup...

OK, radical idea: what if the priority difference comes from the fact that the load writes a HARD REG (a0) that is ALSO the destination of the call's operand? no.

You know what? Let me just look at GCC 2.7's sched1.c source. Maybe I can fetch it... no network probably. 

Hmm, but wait: maybe the project has a copy in .run somewhere. Let me search within the project for "sched1.c" or for the string "birthing_insn" in .run.

Let me do a project-scoped search.
