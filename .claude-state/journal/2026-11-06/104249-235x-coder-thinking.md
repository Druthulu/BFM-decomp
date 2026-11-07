---
ts: 2026-11-06T17:42:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_D4d58vziH9qhbfACFXOf
---
r2 = 5: lo declared first, assigned first (lo=srl), hi second — same as q1 (srl first).

r1 = 7: lo declared first but hi assigned first → sh16=v1.

So the "sh16=v0" requires the srl (lo) to be computed FIRST. The target has sra first.

The register flip seems tied to the first temp being the srl. Why? Maybe because the srl's result is used in the addu as the *second* operand (v0 = hi + lo) and sched1's order...

Let me think about what determines sh16's register: global-alloc preferences. With the named temp `lo`, the RTL becomes:
```
lo = (lshiftrt sh16 31)   ; a real variable (pseudo created at decl)
hi = (ashiftrt sh16 16)
sum = hi + lo
```
The temp `lo` is a named variable → pseudo created at declaration → block-local? It's used in the join block; the declaration is in the join block → local.

The preference for sh16: set_preference(75, src of its setters) — unchanged.

Hmm, but the *local-alloc* assignment of the named `lo` pseudo may differ from the unnamed temp: the named lo has a lower pseudo number (created at block entry) → allocated earlier in the qty order.

The key: with the named-lo form, sh16 ends up v0. So the local temps' registers changed such that global-alloc gave 75 v0.

Since the target's order is sra first, maybe there's a form where the named temp is hi (computed first) that also gives v0. q4 (named hi, hi first) → 7 (v1). Hmm.

What if BOTH are named and hi is first: q3/r1 → 7.

So only the lo-first form gives v0.

Can I make the *instruction* order sra-first while keeping the source order lo-first? sched1 determines the final order. The sra and srl both depend on sh16 and are independent; sched1 schedules them. The source order influences the insn UIDs. If I put the lo computation first but with a *higher UID* for hi... e.g., compute lo first but write the hi expression inline in the sum (q1/p2: `(sh16 >> 16)` inline) — the RTL has the srl insn before the sra. Sched1 kept that order.

Could sched1 reorder them? It schedules by dependencies; both depend on sh16; the order in the final asm is by the scheduler's priority. The srl (first) gets an earlier slot.

Hmm. What if we compute lo first but make hi's expression depend on lo? Then hi must come after → no.

What if we compute hi inline *before* lo in the same statement: `p[0x79] = (u16)(((sh16 >> 16) + (lo = (s32)((u32)sh16 >> 31))) >> 1);` — the hi shift appears first in the expression; the assignment expression `lo = ...` is second. The RTL order: hi's sra first, then lo's srl. And lo is a named temp (assignment expression). Would that give sh16=v0? Let me test.

Also: `s32 lo; p[0x79] = (u16)(((sh16 >> 16) + (lo = (s32)((u32)sh16 >> 31))) >> 1);`

Let me test this (s1) and a variant with hi named too.
