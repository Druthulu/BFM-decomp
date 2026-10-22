---
ts: 2026-10-22T11:21:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_xvcrBsJLA1PQw8Nm1FiX
---
Line 985: `#ifndef INSN_SCHEDULING` ... line 1299 `#endif` — that's the backward scheduler (sched2) section? And 3235-3969 is the forward one? Let me check: at line 2732 and 2862/2865 there are #endif's.

Actually in GCC 2.7's sched.c:
- Lines ~985-1299: the "backwards" scheduler (sched2) under `#ifndef INSN_SCHEDULING`? Hmm, that's inverted logic.

Let me look at the forward scheduler's `rank_for_schedule`. The one I read at 2385 uses `last_scheduled_insn` and `LOG_LINKS` — that's the forward one (sched1) actually! In sched1, `rank_for_schedule` compares with `last_scheduled_insn`... Hmm, "last_scheduled_insn" is set in the forward scheduler too.

And `adjust_priority` with `INSN_PRIORITY(prev) >>= 3` — the shift suggests backward.

OK. Let me find `compute_priorities` in this file.

Hmm, honestly this is a rabbit hole. Let me step back and think about the PRACTICAL solution.

**PRACTICAL INSIGHT**: The core difference between the orig and the no-asm candidate is:
1. orig: load → pseudo 167 (1 set), then asm sets 167 (2nd set), then copy to a0.
2. no-asm: load → pseudo 167, then copy to a0 → coalesced into a hard-reg a0 load.

The scheduling difference: in the no-asm version, the load writes a HARD REG (a0) — and hard-reg definitions are handled differently.

Hmm, what if the load's result could NOT be coalesced into a0? Then we'd have `set 167 = mem` (pseudo) + `set a0 = 167`. Would the scheduler then put the load first? In the orig, the order was load first. But that was due to the asm.

Hmm, let me think about `birthing_insn_p` again (that's sched2 though).

For sched1, GCC 2.7's `compute_priorities`:
```c
/* Compute the priority of each instruction in the block... */
static void
compute_priorities (block, insns, n_insns)
{
  ...
  for (i = 0; i < n_insns; i++)
    {
      rtx insn = insns[i];
      ...
      /* Add in the priority of the insn's dependencies. */
      ...
    }
}
```
and in `rank_for_schedule` for sched1:
```c
static int
rank_for_schedule (x, y)
{
  rtx tmp = *y;
  rtx tmp2 = *x;
  rtx link;
  int tmp_class, tmp2_class;
  int value;

  /* Choose the instruction with the highest priority, if different.  */
  if (value = INSN_PRIORITY (tmp) - INSN_PRIORITY (tmp2))
    return value;

  if (last_scheduled_insn)
    {
      /* Classify the instructions into three classes:
	 1) Data dependent on last schedule insn.
	 2) Anti/Output dependent on last schedule insn.
	 3) Independent of last schedule insn, or has latency of one.
	 Choose the insn from the highest numbered class if different.  */
      ...
    }
  /* If insns are equally good, sort by INSN_LUID ... */
  return INSN_LUID (tmp) - INSN_LUID (tmp2);
}
```

So the priority comes from `INSN_PRIORITY`. In sched1's `compute_priorities`:
```c
      /* Compute the priority of this insn: the number of insns that
	 depend on it, plus ... */
      for (dep = LOG_LINKS (insn); dep; dep = dep->next)
	{
	  ...
	  if (dep->type == REG_DEP_TRUE)  /* data dep */
	    {
	      ...
	      dep->insn->priority += ...
	    }
	}
```

Hmm.

The class-based tie-break: "Data dependent on last scheduled insn" (class 1) is preferred over "Anti/Output dependent" (class 2), which is preferred over "independent" (class 3)!

**AH HA!** That's it!

In the no-asm block, the insns are: [238: a0=mem], [240: a1=320], [242: a2=240], [244: call].
- The `a1=320` (240) and `a2=240` (242) are ANTI-DEPENDENT on the call? No — the call READS a1, a2 (data dep call→a1). So a1 has an anti-dep with the call (call reads a1 which a1 writes). Hmm, "anti-dependency" = the insn writes a reg that the other reads.
- The load (238) writes a0, and the call reads a0 → also anti-dep.

Hmm, all three have anti-deps with the call. So they're all class 2 relative to the call.

But relative to `last_scheduled_insn`: initially, no insn is scheduled. The scheduler picks the first insn by priority.

Hmm. Let's think about the actual order chosen: a1(240), a0/load(238), a2(242), call(244).

If the scheduler picks by priority and all have equal priority, then by class relative to last_scheduled_insn (none yet), then by LUID ascending: 238 (load), 240, 242 → that would give load first! But we got 240 first.

So the priorities differ: a1=320 has HIGHER priority than the load.

Why? `compute_priorities` in sched1: the priority of an insn is based on its dependencies AND on the number of insns that depend on it (fanout). Hmm.

Actually here's a likely mechanism from GCC's sched1 `compute_priorities`:
```c
  /* Compute the priority of each insn: the priority of an insn is the
     number of insns that depend on it (its "fanout") ... */
  for (i = 0; i < n_insns; i++)
    {
      rtx insn = insns[i];
      int priority = 1;
      for (dep = LOG_LINKS (insn); dep; dep = dep->next)
	{
	  if (dep->type == REG_DEP_TRUE)
	    priority += dep->insn->priority;   /* data dep: must come after */
	  ...
	}
      INSN_PRIORITY (insn) = priority;
    }
```

Hmm, that's the dependency-based priority.

Alternatively, GCC's sched1 has a specific "call group" concept where the arg-setup insns are given a priority boost.

Hmm, actually! Let me look at the sched.c we have — line 1441 and 1833 mention SCHED_GROUP_P. Let's look at line 1820-1860 and 2140-2160 to see the group logic (this may be sched2's).

Hmm, I realize the file might contain BOTH: lines 985-2732 = backward (sched2) and 3235-3969 = ... hmm.

You know what — let me look at the file around line 987 to see which scheduler it is.

Actually, let's take a totally different practical approach: **brute-force many C variants** for item 2 and look for a score < 2. Since each test is ~1s, I can do 50-100 quickly. Let me generate a large set of variants mechanically (different spellings of the load and the call, different orderings, extra statements) and score them all.

Let me write a generator with ~40 variants.

Actually, hold on. Let me reconsider one specific idea that is very likely: **the "second set" of the loaded pseudo**.

In the no-asm case, the pseudo 167 has 1 set and the coalesce merged it into a0. In the orig, pseudo 167 has 2 sets (load + asm) and the copy to a0 survived.

What if we give the pseudo a second set via a self-assignment `t = t;`? If combine doesn't remove it before sched, then:
- 167 = mem (set 1)
- 167 = 167 (set 2) — a no-op copy
- a0 = 167

combine might remove `167 = 167`. GCC's combine has in `do_combine` case SET:
```c
	  /* If the source and destination are the same register, ... */
```
Hmm, combine's `reg_move` handling: `if (REGNO (src) == REGNO (dst) && ...)`. There's code in combine.c: "/* Handle the case of a no-op move: set x, x */". I believe combine does handle `set x,x` by turning it into a no-op... but maybe only for hard regs.

Also the front end might fold `t = t`. In GCC's `c_expand_assign`? Actually the front end's `expand_expr` for MODIFY_EXPR calls `expand_assignment` which builds `set lhs rhs`. There's a check in `c-typeck.c`/`expr.c`: `if (operand_equal_p (lhs, rhs))`. Hmm.

Let's just TEST. Cheap.

Another idea: give the pseudo a second set with a DIFFERENT value that's then overwritten... no.

Another: make the load's pseudo have a second set via a conditional assignment:
```c
s32 t;
t = load;
if (t == 0) t = load;   /* second set, but only on one path */
```
Adds a branch. no.

Let me now write a big variant generator for item 2 and run it.

Variants (all replacing the OLD region):
01-15 done.
New:
16. `t = t;` after the load.
17. `t = load; t = load;`
18. `u = t;` with u used in the call.
19. `t = load; call(t + 0, ...)`
20. `t = load; call((s32)t, ...)`
21. `t = load;` then `call(*(s32 *)&t, ...)` — no.
22. Use `p` directly: `call(*(s32*)((u8*)p+0x20), ...)` (v03 variant with cast).
23. `t = load; t = t | 0;`
24. `t = load; t &= 0xFFFFFFFF;`
25. `t = load; if (t) { }` (dead test — GCC removes).
26. `t = load; t = t ? t : t;`
27. `do { t = load; call(t,...); } while(0);`
28. `while (1) { t = load; call(t,...); break; }`
29. `switch (t) { default: call(t,...); }` — hmm switch on t → jump table? bad.
30. `{ s32 t; t = load; call(t,...); }` with the block moved before the `if`? no.

Also try modifying the SURROUNDING code:
31. Change the `if ((func_80029178(0xB3) & 0xFF) != 0) {` to `if ((func_80029178(0xB3) & 0xFF) == 0) { ... } else { ... }` with swapped bodies — this changes the branch structure.
32. Move the `*(u8 *)(p + 0x75) = 0;` before the call? That changes the order.

Also:
33. Make the load address use `p` vs `arg0`: `t = ((Unkstruct_80126B58 *)arg0)->unk20;`
34. `t = ((Unkstruct_80126B58 *)p)->unk20;` with p being `u8 *` → the offset is 0x20 (same).

Let me also try:
35. Change the call's prototype spelling: `func_8001D0E8((s32)t, 0x140, 0xF0)`.
36. `func_8001D0E8(t, (s32)0x140, (s32)0xF0)`.

And:
37. Declare t at function scope and assign inside.
38. Reorder: `func_8001D0E8(t, 0x140, 0xF0);` then `t = load;`?? No, wrong.

Let me generate and run.

Also a KEY one:
39. Put the load in the PREVIOUS statement position so it merges with the store's block:
Actually — what about moving the load+call BEFORE the `if ((func_80029178(0xB3) & 0xFF) != 0)` block? That changes the order of the load relative to the body → wrong code.

40. What about the `if` condition: `if ((func_80029178(0xB3) & 0xFF) != 0) { ... }` — the body's last statement is the unkE store. Then the join. What if we make the join block's content be inside an `else` of a restructured if? E.g.:

```c
if (cond != 0) {
   ...body...
} else {
   t = load;
   call(t, ...);
}
```
Then the else arm has the load+call and the !=0 arm falls through to... the join after the if. But then the !=0 path would ALSO need the load+call. No — the target has the call on both paths (the beqz goes to the call). So no.

Hmm right, the target's structure: `beqz v0, 3ad4` where 3ad4 = the load+call. So BOTH paths execute the load+call. So the join block.

OK let me run the batch.

Actually, one more high-value idea: **the `p` variable**. `p = (u8 *)arg0;` at the top. The load is `32(s0)`. What if the load were spelled through a copy of p? e.g. `t = ((Unkstruct_80126B58 *)p)->unk20;` — same.

And: what if `t` is declared `s32` but the struct member is `s32`? `((Unkstruct_80126B58 *)p)->unk20` — what's the type of unk20? Let me check the struct. If unk20 is `s32 *` (a pointer!), then `t` would be a pointer. Hmm! `t = ((Unkstruct_80126B58 *)p)->unk20;` and then `func_8001D0E8(t, 0x140, 0xF0)` — the function takes (s32, s32, s32). So unk20 might be s32.

Let me check the struct definition to be sure of types — maybe using a different type for `t` (e.g. `void *`) changes the RTL (no).

Let's just run the batch and see.

Let me also reconsider: maybe I'm over-focusing. Let me check the other items' potential first, and come back. Actually no — item 2 has the best score (2). Let me push on it with a big batch.

Let me write the batch generator.
