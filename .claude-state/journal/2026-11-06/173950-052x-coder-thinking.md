---
ts: 2026-11-07T00:39:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V1cQq1IZR3UMj2MNQb3K
---
With the barrier kept and the pin dropped: the *order* is right (load at 32) but the registers swap: mine uses v1 for val and v0 for the constant 1; the target uses v0 for val and v1 for the constant 1.

So the two levers address two independent aspects:
1. Barrier → keeps the val load above the stores (scheduling).
2. Pin $2 → val in v0, constant 1 in v1.

Both need real-C replacements.

For (2): the register choice. In the target, `val` (a load) is in v0 and the constant 1 (for D_801B7988=1) is in v1. Without the pin, local-alloc gives the load v1 and the constant v0. Classic local-alloc priority/tie.

The "lreg-qty-priority" wall tag: local-alloc qty priority (refs/live length) gives the hard reg to the other pseudo.

How to influence: give `val` more references or a longer live range, or make the constant's pseudo have lower priority. The constant 1's pseudo (the `li v1,1`) is a separate pseudo with 1 ref. `val` has 2 refs (load + addiu use)? Both have short lives.

local-alloc assigns in order of qty_compare: priority = (refs * length)... Actually `qty_compare_1`: compares by `qty_n_refs[q] / (qty_death - qty_birth)` or something. Let me recall: in local-alloc.c, `qty_compare_1` sorts by `qty_phys_reg`... The relevant function:

```
static int
qty_compare_1 (q1, q2)
{
  ...
  /* Consider quantity's qty_n_refs to be a "weight"... */
  if (qty_n_refs[q1] * qty_size[q2] < qty_n_refs[q2] * qty_size[q1]) ...
```
Something like refs/size. So making `val` have more refs or a shorter live range would raise its priority.

Hmm. The target: val in v0 (the first free reg). Mine: val in v1.

What real-C moves change the local-alloc order?
- More uses of val (e.g., use val twice) — but the code must stay identical.
- Declaration order of the temporaries (the "decl order" catalog move).
- Changing the scope of the variables.

Actually wait — maybe the register choice is decided by *global-alloc* since the block is in a switch inside a function with s0 used. The v0/v1 choice for two short-lived pseudos is local-alloc.

Let me think about the second aspect (1) first: the barrier. What real C keeps the val load above the three stores?

Since the sched1 priority of the load appears to be 1 (all costs 1) and the order is source order... but mine's source order IS load-then-stores. Unless the RTL order at sched1 differs because of *jump_optimize* or *combine*.

Hmm, actually! Maybe the difference is that in w3 (barrier kept) the order is right, and the barrier is an insn in the stream that blocks reordering. Without it, sched1 moves the load down. That means sched1's priority for the load is LOWER than the stores' — the load is not ready at the start.

Wait, the load is `lui v0,0x0; lw v0,0(v0)`. In mine (w1), the lui+lw are at 8424. Why would the lui not be ready first? sched1 computes the schedule from the top of the block; all insns are ready except through dependencies. The lui at the top of the block would be picked first if its priority were highest.

Let me compute priority: everything has priority 1 (costs all 1) except the load: the load's dependent addiu has priority 1, so the load = 1 + 1 - 1 = 1. And the lui = 1.

With equal priorities, sched1 keeps the ready-list order, which is... `ready` list sorted by priority; ties broken by "the insn that was added first" (LUID order). The lui is first in source → should be picked first.

Unless the LUID order differs: LUIDs are assigned in insn order at the start of sched1, which is the RTL order = source order. So the lui is first.

So sched1 would keep the load first — but mine has it last. So the reordering is NOT sched1. It must be sched2 (after reload), or `reorg`, or `local-alloc` spilling... Hmm, sched2 also schedules but uses the same priority scheme.

OR: the reorder is from **combine**? No.

OR: the val load was *not* at the top of the block in the RTL: maybe cse/jump moved it? Actually! Maybe the front end's `expand` emitted the load late because the statement `val = D_801B7A84;` — hmm.

Let me check by dumping. I'll do the dump properly now — it's the decisive tool. Let me run cc1_dumps_tu.sh on the --keep TU for w1 with DUMP_ROOT under my item dir, then grep the sched1/sched2 dumps.

Disk risk: the TU is 365 KB with many functions; -dr -ds -dj -dl -dg -df -dc -dS -dL -dR -dt -dJ -dd on a 14k-line TU → the dumps are per-function; total maybe 50-200 MB. Then I delete. The shard limit is 200 MB; a transient dump is risky but I'll delete immediately.

Hmm, alternatively, I can dump with fewer flags by calling cc1 directly with just -ds (sched1) — but the rule says use the tools. The tool takes DUMP_ROOT; it's the sanctioned route.

Actually, there might be a lighter option: `.run/P40/T10/hdump.sh` is for headers. There's `tools/alloc_table.py` for the alloc table (useful for the register question).

Let me try: run cc1_dumps_tu.sh with DUMP_ROOT=.run/P40/T11/P1/<item>/dumps on the --keep TU copy, then grep. Time cost ~30-60 s.

Wait — the --keep TU is the spliced TU for the *candidate*. It's at .run/P36/engine/score/ov_SC02_031__func_801831B4/p3/ov_SC02_031_jr_8017AE2C.c. Good.

Let me do it.
