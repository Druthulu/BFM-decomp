---
ts: 2026-10-22T11:17:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_QKMeHmyvK8kLEHrTjHx4
---
C0434 "THE BIRTHING BOOST: A SINGLE-SET LOCAL IS SCHEDULED LAST; GIVE IT A SECOND SET" — very relevant! And C0391: "A ZERO-BYTE RE-TIE SETS reg_n_sets=2, WHICH KILLS sched1's birthing_insn_p LAUNCH_PRIORITY BOOST".

So: the launder asm gives the register a second SET, which kills the birthing boost. In our case, the load's pseudo has 1 set → gets the birth boost → scheduled LAST? Hmm, but the li got scheduled first.

Wait — in the no-asm case: the coalesced load insn writes a0 directly. `birthing_insn_p` — a "birthing insn" is one whose operands are all ready at block start. The li a1,320 is a birthing insn (constant). Hmm.

Let me read cookbook C0434 and C0391.

Actually, key insight from C0434: "A SINGLE-SET LOCAL IS SCHEDULED LAST; GIVE IT A SECOND SET". So the load's pseudo (single set) is scheduled last. Giving it a second set makes it scheduled earlier!

But we need the second set to produce no extra instruction. Hmm. That's what the asm re-tie does (reg_n_sets=2 with zero bytes emitted).

In plain C, a second set of a local usually means an extra instruction... unless the second set is a copy that coalesces.

Hmm! But wait: in our case, the li a1,320 is scheduled FIRST and the load SECOND. The li is the "birthing" one. Hmm, the C0434 rule says single-set locals are scheduled LAST. So the load (single-set) went last. Consistent!

So: if the load's pseudo had 2 sets, it would be scheduled earlier (before the li). How to give it a second set without an extra instruction?

Options:
- `t = load; t = t;` — the second set is a copy of t; combine would coalesce it away but might still count as 2 sets! Hmm, the second set `t = t` is a no-op copy that GCC removes early (front end or cse), so reg_n_sets might still be 2 at the RTL level when sched1 runs... Actually `t = t;` in the front end: GCC's `c_expand_assign` might not remove it. In RTL, `set 167 = 167` — cse/combine would remove it. cse runs before sched. So by sched time, reg_n_sets would be back to 1. Hmm, but does cse decrement reg_n_sets? `reg_n_sets` is computed in `combine`/`local_alloc`. Actually `reg_n_sets` is set in `combine.c` during RTL simplification.

Hmm, but the C0434 trick says "give it a second set" — presumably a second set that survives to scheduling.

- `t = load; t = load;` — two loads → cse removes one → 1 set.
- `t = load; u = t; call(u, ...)` — the copy `u = t` might survive as a separate insn (an extra move). Unless coalesced.

Hmm. But actually: the ASM case has the load `set 167 = mem` and the asm `set 167 = asm_operands(...)` — that's a second set of 167! And that's exactly the C0391 mechanism: "A ZERO-BYTE RE-TIE SETS reg_n_sets=2, WHICH KILLS sched1's birthing_insn_p LAUNCH_PRIORITY BOOST".

Hmm, wait, that says the second set KILLS the boost (so the insn is NOT boosted → scheduled normally/earlier?). Confusing. Let's read C0391 and C0434.

Let me read those cookbook files.
