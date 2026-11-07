---
ts: 2026-11-07T00:41:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tX0sxWo6E8LjcA49xPo3
---
Through combine, the order is 53, 56, ..., 65 — source order. So the flip happens in **local-alloc** (.lreg dump is after local-alloc? Actually .lreg = local-alloc output). Let me check: .lreg showed 65 → 53. So local-alloc (or the insn splitting there) reordered!

Hmm, local-alloc doesn't reorder... but it *splits* insns and can insert copies. Actually the .lreg dump is after local-alloc. Hmm, what about global-alloc (.greg)? The .lreg dump already has the flip.

Wait, local-alloc.c has a "birth/death" ordering? No.

Hmm, but there's `regmove`? Not in 2.7.2.

Let me double check the .lreg output: is the flip there? Yes: "(insn 65 62 53 ...)" and "(insn 53 65 68 ...)".

Hmm, and .combine has 53 before 56. So between combine and local-alloc... what pass runs? The order in toplev: ... combine, then `if (optimize > 0 && flag_schedule_insns) schedule_insns()` (sched1) — wait, the .lreg dump comes from local-alloc which runs BEFORE sched1? Let me get the actual pass order:

toplev.c rest_of_compilation:
```
  ...
  if (optimize > 0) { ... combine_instructions ... }
  ...
  if (optimize > 0 && flag_schedule_insns) { schedule_insns (insns, rtl_dump_file); }  /* sched1 */
  ...
  local_alloc ();
  ...
  global_alloc ();
  ...
  if (optimize > 0 && flag_schedule_insns_after_reload) sched2
```
Hmm, actually in 2.7.2: 
```
      if (optimize > 0)
	{
	  TIMEVAR (combine_time, { combine_instructions (insns, max_reg_num ()); });
	  ...
	}
      ...
#ifdef INSN_SCHEDULING
      if (optimize > 0 && flag_schedule_insns)
	{ schedule_insns (insns, rtl_dump_file); }
#endif
      /* Here we free the ... */
      ...
      /* Allocate the registers */
      ...
      local_alloc();
      global_alloc();
```
So sched1 runs BEFORE local-alloc. But then the .sched dump (sched1 output) should show the order... and the .lreg dump (after local-alloc) shows the same order. Hmm, but the .sched dump showed 53 after 65 and so did .lreg. And .combine (before sched1) shows 53 before 56. So the flip is in **sched1** after all — and .lreg preserves it.

I misread: .lreg is after local-alloc, which is after sched1. Right: sched1 output = .sched; local-alloc output = .lreg. Both show the flip. Good: sched1 moved it.

So sched1 moved 53 after the stores. Why? Priorities are all 1... let me look again at the priorities in the sched dump: "insn[53]: priority = 1, ref_count = 2" and the stores 56/59/62/65: priority 1.

Hmm, but wait — the dump prints priority for the *scheduled* insns. Let me look at insn 53's priority in the dump more carefully; and check `rank_for_schedule`'s class tie-break.

Class relative to last_scheduled_insn: after the call (50), the ready insns are 53, 56, 59, 62, 65. For each, `link = find_insn_list(tmp, LOG_LINKS(last_scheduled_insn))` — LOG_LINKS(50)? The dump shows LOG_LINKS of insn 53 includes "REG_DEP_ANTI 50". For the class computation, we look at LOG_LINKS(last=50) for an entry mentioning 53. Hmm, LOG_LINKS(50) would be the deps of 50 (the call's own deps).

Hmm, that seems backwards but it's the code.

Alternatively the class is computed with `find_insn_list (tmp, LOG_LINKS (last_scheduled_insn))` where tmp is the candidate. If not found → class 3.

So all candidates would be class 3 → tie → LUID → 53 first. Still contradicts.

Unless the priority of 53 is NOT 1 at scheduling time. The dump prints the final priority; maybe I misread which line. Let me look at the actual dump lines for insns 53/56/59/62/65 priorities.

From the earlier grep of the region:
```
;; insn[  53]: priority =    1, ref_count =    2
;; insn[  56]: priority =    1, ref_count =    1
```
Yes, 53 is priority 1.

Hmm, so why? Let me look at `sched_analyze` — maybe 53 is not *ready* after the call because of a dependence I'm missing: e.g., 53 depends on insn 45 (p = &D_801B7930) via REG_DEP_ANTI? The dump shows `(insn 53 65 68 (set (reg/v:SI 76) (mem...)) ... (insn_list:REG_DEP_ANTI 50 (nil))` — only a dep on 50.

Wait, maybe the ready list is not the issue: maybe the *birth* order matters via `INSN_LUID`. LUIDs are assigned at the start of sched1 in the *insn order* — which is 53 before 56. Unless sched1 assigns LUIDs differently (by UID?). In sched.c, `INSN_LUID` is assigned in `schedule_insns` iterating over insns in order. So 53 < 56.

Hmm, then rank_for_schedule(53, 56) = LUID diff = negative → 53 preferred (x preferred if negative: "Returns a positive value if y is preferred"). rank(x=53, y=56) = LUID(56) - LUID(53) = positive → y (56) preferred?! Let me re-read:

```
static int
rank_for_schedule (x, y)
     rtx *x, *y;
{
  rtx tmp = *y;      /* tmp = y */
  rtx tmp2 = *x;     /* tmp2 = x */
  ...
  if (value = INSN_PRIORITY (tmp) - INSN_PRIORITY (tmp2))
    return value;
  ...
  return INSN_LUID (tmp) - INSN_LUID (tmp2);
}
```
Returns INSN_LUID(y) - INSN_LUID(x). Positive means y is preferred. So a *later* LUID is preferred! That's the reverse of "stable" — hmm, but the comment says "sort by INSN_LUID (original insn order), so that we make the sort stable. This minimizes instruction movement".

Hmm, in qsort with this comparator, the array ends up sorted with... if rank(a,b) > 0 means b is preferred, then the sort puts larger LUID first?! That seems odd but it's what the code says. Let me look at how the ready list is used: the scheduler picks `ready[0]` as the highest priority. The array is sorted by rank_for_schedule in DESCENDING preference? If qsort with a comparator that returns positive when y is preferred, then... qsort sorts ascending by the comparator, so the array ends up with the *least preferred* first? That can't be.

Hold on: maybe the convention is that rank_for_schedule returns positive if x is preferred... The comment says "Returns a positive value if y is preferred; returns a negative value if x is preferred."

Hmm, but then with `return INSN_LUID (tmp) - INSN_LUID (tmp2)` = LUID(y) - LUID(x): positive (y preferred) when y has a LATER LUID. So later insns are preferred?! That contradicts "minimizes instruction movement".

Wait, maybe qsort is called such that the array is in reverse. Look at how READY is consumed: `ready[0]` or `ready[n_ready-1]`? Let me check.

This matters: if later LUIDs are preferred, then the *source order* isn't preserved — later insns get scheduled first, which would explain the stores (56,59,62,65) being scheduled before 53 (they're later than 53!). But then 65 (latest) would come before 56, contradicting the observed 56,59,62,65 order.

Hmm, so no.

Let me look at how the scheduler consumes the ready list.
