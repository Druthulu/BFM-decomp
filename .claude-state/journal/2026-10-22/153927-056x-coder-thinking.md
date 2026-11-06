---
ts: 2026-10-22T21:39:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w41N27HKZckpQ5tLyXT3
---
The scheduler: insn 23 is `sw ra` (blocked 1 cycle each time, so it keeps getting pushed). "blocking insn 23 for 1 cycles" — the DBR hazard: sw ra is a store to the stack that conflicts with the loads? Actually "blocking" means insn 23 can't be launched because of a pending load hazard (it's blocked by the load at T-2?).

The key: "insn 18 has a greater potential hazard" — potential_hazard picks the MEM insn with unknown address.

insn 23 = sw ra. It's "blocked for 1 cycle" repeatedly — because it depends on a load? No, it's blocked by the load-delay machinery: on MIPS, after a `lw`, the next insn is blocked? No, sched2 handles load delays by inserting nops.

Hmm, actually "blocking insn 23 for 1 cycles" appears at T-3, T-4, T-6 — insn 23 is blocked each cycle, so it never launches until the end. Blocked by what? Probably by `insn 26` (the branch, priority max) which must launch at the end, and insn 23 has a dependence on... 

Wait: insn 23 is `sw ra,28(sp)`. In the dump it says "launching 23 before 18 with no stalls at T-3" — so 23 IS launched at T-3! Let me re-read:

T-1: 26 (the branch).
T-2: ready list 82, 4, 18, 25 → now 25 18 4 82 (sorted). "insn 18 has a greater potential hazard, now 18 25 4 82". "launching 23 before 18 with no stalls at T-3" — hmm, 23 isn't in the ready list at T-2... 

Actually the "ready list at T-2" line lists insns ready; then "launching 23" suggests insn 23 was chosen at T-3.

This dump is confusing without the insn table. Let me instead just accept the empirical result.

Time check: ~15:45. Item 2 has ~10 min. I've done 7 tries. This looks like a WALL (sched2-potential-hazard). Let me do a few more quick variants (maybe 8-10 more) to reach a defensible count, then WALL.

Actually, wait. Let me think about what "blocking insn 23 for 1 cycles" means — sched2's `schedule_block` has:
```
	  /* If the insn is blocked by a hazard, ... */
```
In gcc's sched.c:
```
	  /* Block the insn if it is a store and the previous insn was a load
	     from an address that may alias it (potential hazard). */
```
Hmm.

The note in src says: "sched2 finds no memory dependence and its potential_hazard rule promotes the prologue sw $ra over the ALU candidates, sinking it to just above the branch."

The barrier creates a memory dependence. A plain-C way to create a memory dependence between the sw ra and something: make a real memory op that must come before it... but sw ra is at the top.

Alternative: make sched2 not have the ALU candidates — no.

Alternatively: reduce the insns before the branch? no.

Honestly, let me look at what insn 23 is blocked by. Let me look at the insn dump before the schedule (the -dS output shows the insn numbers). Let me grep for "insn[ 23]" context in the sched2 dump — there might be a table listing each insn. Let me look at the section right before "basic block number 0".

Actually, sched2 dumps show per-block: ";; insn[ N]: priority..." lines. Let me grep for the insn list with patterns.
