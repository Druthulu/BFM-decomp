---
ts: 2026-11-06T21:28:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hszJhz0ODp3JfnTodwMa
---
Item 2 done at 14:28-14:29 (20 min). Now item 3 fully.

Item 3: header, kinds keepalive, best 2 (w1: pin kept, keepalive dropped). The wall tag: sched1-ready-order (the li 3072 vs the move are independent, all priority 1; the ready-list tie puts the li first).

But before declaring the wall, let me try more C variants to crack the scheduling. Let me think about what could make the move scheduled first.

From the .sched log, the then-block RTL order is: 58 (li 3072), 60 (store q), 55 (move), 63 (li 1), 65 (store a), 70 (call). The scheduler's final order: 58, 60, 55, 63, 65, 70.

Target order: 55, 58, 60, 63, 65, 70.

The scheduler is a *backward* list scheduler (from the log: "ready list initially: 70"). It picks from the ready list; the ready list order determines ties.

At T-6 (last scheduled, i.e., first in the final order), only 58 is ready. So 58 is forced to be first! Wait: the final order is the reverse of the scheduling order: T-1 = last insn (70), ..., T-6 = first (58). So 58 is scheduled LAST (T-6) and appears FIRST.

Hmm, so the scheduler builds the list backwards: it picks 70 first (T-1), then 65, 63, 55, 60, 58. The final order is 58, 60, 55, 63, 65, 70.

To get the move first, 55 must be picked last (T-6). Why is 58 picked at T-6? Because at that point only 58 is ready (all its dependents scheduled). 55's dependents: 65 (store a) — scheduled at T-2; after that, 55 becomes ready at T-3 (it's in the ready list at T-3). So at T-3 the ready list is {60, 55, 63} and it picks 63; T-4 picks 55; T-5 picks 60; T-6 picks 58.

So the final order is determined by the ready-list picks at T-3..T-6: 63, 55, 60, 58 (reverse: 58, 60, 55, 63).

For the target order (55, 58, 60, 63), we'd need the picks at T-3..T-6 to be 63, 60, 58, 55 → i.e., pick 55 last.

The picks are by priority (all 1) and then the ready-list order. The ready-list order is affected by the order insns are added (`add_dependee` adds when a dependent is scheduled, and `schedule_insn` inserts by priority).

Hmm, this is deep in sched.c. C-level steering: change the dependencies so the scheduler's choices differ.

Idea: make the move (55) depend on something scheduled early (in the final order), i.e., its *source* must be available late? No — 55 has no dependencies (it's a copy of s0, which is live).

Hmm, the scheduler schedules 55 at T-4 because it's ready at T-3 and picked after 63.

What if we make 55 have a *dependent* that is scheduled even later (T-1 or T-2)? Its dependents: 65 (store a, T-2) and 70 (call, T-1). If 55 also fed something at T-3... no, later = closer to the end.

Hmm, actually to be scheduled at T-6 (first in the final order), 55 must become ready only at T-6. It becomes ready when all its dependents are scheduled. Its dependents are 65 (T-2) and 70 (T-1). So it's ready from T-3 onward. To delay it to T-6, we'd need... hmm, the scheduler picks from the ready list each step; it doesn't have to pick 55 last. It picks by priority.

So we need 55's priority to be LOWER than the others so it's picked later. Priorities are all 1. Priority is computed from the dependence depth (`priority = 1 + max(dependent priorities)`, roughly, plus ref counts). Let me look at sched.c's priority computation:

```
static void
priority (insn)
{
  ...
  for each dep
    this_dep = ...;
  /* Add the priority of the most urgent dependency */
  ...
  /* Try to be a bit more intelligent ... */
}
```
Let me read it.

Actually, a simpler C lever: make the move's *ref_count* lower or higher. The log shows "insn[55]: priority = 1, ref_count = 2". The ref_count is the number of insns depending on it (2: the store and the call).

Hmm, all priorities are 1.

What if the move were merged with something? no.

What if we add a dependency so the move is scheduled even later (picked later)? The scheduler picks the *highest* priority first in the backward pass, i.e., the last in the final order. To make 55 appear FIRST, it must be picked LAST, so it should have the LOWEST priority... but all are 1.

Hmm, the tie-break: the ready list order. From the log: "ready list at T-3: 60 (1) 55 (7f000001) 63 (7f000001), now 63 55 60". The "(7f000001)" vs "(1)" — the 0x7f000001 might be a "scheduled" marker or a priority with flags. 55 and 63 have 7f000001, 60 has 1. The pick is 63 (first among 7f000001 ones).

I think 0x7f000001 is `INSN_PRIORITY` with a flag bit set for "not yet scheduled". Hmm.

This is very deep. Let me instead try empirical C variants:

1. Reorder the C statements: `a = arg0;` before/after; store order.
2. Change `a` to be used in the q-store's address somehow.
3. Use a *second* variable that aliases a.
4. Make the call's argument a *different* expression, e.g., `func_80146CA0(arg0)` while `a` is used only for the store.

Let me think about the dependencies the scheduler sees:
- 58: li 3072 (no deps)
- 60: store q (depends on 58, 48/50? the q load)
- 55: move a0=s0 (no deps)
- 63: li 1 (no deps)
- 65: store a (depends on 55, 63)
- 70: call (depends on 55)

The final order: 58, 60, 55, 63, 65, 70.

Target: 55, 58, 60, 63, 65, 70.

So the target's order is: move first, then the rest in source order.

Since the scheduler is a backward list scheduler, the "first" insn is the one scheduled last. To schedule the move last, it must remain in the ready list until the end. The scheduler picks the highest priority; all are 1; ties by ready-list position.

What if we make the move have *fewer* dependents (ref_count)? Its ref_count is 2 (store + call). If `a` were used only for the call (not the store), ref_count = 1. Then its priority might be lower... priority = 1 + max over dependents? Let me read sched.c priority.

Let me look at the priority function in sched.c.
