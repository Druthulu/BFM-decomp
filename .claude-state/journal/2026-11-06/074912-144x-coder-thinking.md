---
ts: 2026-11-06T14:49:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RhPCe9ezQnHQALFIirql
---
`record_jump_equiv` is called with `taken` (0 for fall-through, 1 for the branch target). It records the equivalence on both paths. So cse records t==5 on the fall-through of `bne t,5,...`.

Now, `record_jump_cond` adds a REG_EQUAL note to the register. Then the next `t != 3` gets folded via `fold_rtx`.

So cse is the pass. To prevent, I need a set of t between the branch and the check. But as established, any real set changes the value or folds.

Hmm, but wait — `record_jump_cond` only records if the register is not already known? Let me look at `record_jump_cond`. It might refuse if the register has conflicting equivalences. Let me read it.

Actually, the key insight: cse's equivalence is stored in `reg_eqv_table`/`table`. A subsequent SET of t deletes the equivalence. So if I can get a SET of t that cse sees but that doesn't change the value at runtime, I win. The C0414 dead-reset is exactly that: a set that cse sees and flow deletes. But the set must be dead (flow deletes it) AND not affect the check.

Wait — here's the trick: put the dead set AFTER the check! 
```
if (t == 5) {
    if (t != 3) goto sel_094;   // cse needs to NOT fold this
    ...
}
```
No, the dead set must be before the check to invalidate the equivalence.

Hmm, but the C0414 pattern is `p = expr; use(p); p = 0;` — the dead set is AFTER the use. For our case, the "use" is the branch. The dead set would be after the branch, which doesn't help the branch's fold.

Unless... the equivalence is established on the fall-through of the `t==5` branch, and the check is later. A dead set of t anywhere between the branch and the check invalidates. But the check uses t, so the set must preserve t's value.

What if the dead set is on a different register that cse thinks is equivalent to t? Hmm.

OK, what about this: the C0414 "dead-reset" sets p=0 and p is not used after. What if I use it to break the equivalence and then re-establish t via the ORIGINAL expression that cse can't equate to 5:
```
if (t == 5) {
    s32 u = t;      // u = t (cse: u == t == 5)
    t = 0;          // cse: t = 0; invalidates t==5
    t = u;          // cse: t = u; and u == 5? cse knows u's value is 5 (from u=t when t==5). So t == 5 again. Fold.
}
```
Hmm, cse tracks u's value. Unless u is not tracked (e.g., u is assigned from a memory read).

What if:
```
if (t == 5) {
    s32 u;
    u = t;          // u = 5 (cse knows)
    t = 0;          // invalidate
    t = u;          // t = u = 5 (cse knows u==5) -> fold
}
```
Same.

What if the restore uses a value cse lost track of? E.g., pass t through a call? No call.

Hmm. What if I use the `mode` variable (a local that cse doesn't know)? No.

Let me look at record_jump_cond — maybe it only records if the register has no other equivalence, and I can pre-load t with a different equivalence to prevent the record.

Let me read record_jump_cond.
