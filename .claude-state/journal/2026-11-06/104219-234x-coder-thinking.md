---
ts: 2026-11-06T17:42:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2W6MvZuUhZMMqnzXFuL6
---
q1 = 5 (same as p2: sh16=v0, order srl-first). q3/q4/q5 = 7.

Interesting: only the form with the named `lo` temp *before* the expression and `(sh16 >> 16)` inline gives sh16=v0.

The remaining issue is the shift order: mine srl then sra; target sra then srl. That's sched1 ordering (both depend on sh16; sched1 scheduled the srl first because of the source order?).

If I put the >>16 computation first (q3/q4), sh16 goes back to v1 (7).

So there's a trade-off: the named-lo form fixes the register but gives the wrong order.

What if I keep the named-lo form but reorder the *instruction* via source: e.g.:
```
s32 lo;
s32 hi;
lo = (s32)((u32)sh16 >> 31);
hi = sh16 >> 16;
p[0x79] = (u16)((hi + lo) >> 1);
```
That's still lo first (srl first).

What if I compute hi first but declare lo first:
```
s32 lo;
s32 hi;
hi = sh16 >> 16;
lo = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)((hi + lo) >> 1);
```
q3-like but declaration order swapped. q3 had hi,lo declared and hi assigned first → 7.

Hmm, the sh16=v0 outcome in q1 seems tied to the srl being first. Since sched1 schedules within the block, the source order may drive it.

Let me try to get sh16=v0 AND sra-first by using a different construct: maybe compute hi as a named temp too but assign lo first... no.

Let me think: in q1, the temps: lo = srl (first), then hi = sra inline in the sum. The registers: srl v1 (lo), sra v0 (hi, after sh16 dies at the sra). Wait, sh16 dies at the sra (its last use). So the sra's dest can reuse v0 (sh16's reg) — mine: `sra v0,v0,16`. Then addu v0,v0,v1.

The target: sra v1,v0,16 (dest v1), srl v0,v0,31 (dest v0, reusing sh16). So the target's FIRST temp is sra with dest v1 (not reusing v0), and the second is srl reusing v0.

In q1, the first temp is srl with dest v1 (not reusing v0), and the second is sra reusing v0. Symmetric!

So the target's order is sra-first with the same allocation pattern. If I write the source with hi first but keep lo as a named temp... q3 (hi first) gave 7 (sh16=v1).

Hmm, so the named-lo trick only works when lo is first.

Let me try: named-hi form with hi first and lo inline:
```
s32 hi;
hi = sh16 >> 16;
p[0x79] = (u16)((hi + (s32)((u32)sh16 >> 31)) >> 1);
```
q4 = 7 (sh16=v1).

So the "named temp" effect depends on which shift is named first.

What if we name BOTH but order hi first (q3) → 7.

Hmm, the register flip seems driven by the first temp's identity.

Let me look at q1's asm to see the exact sequence and registers:
mine[171]: srl v1,v0,0x1f; sra v0,v0,0x10; addu v0,v0,v1; sra v0,v0,1; sh v0.
So in q1: sh16=v0; lo=srl v1; hi=sra v0 (reusing sh16's reg).

Target: sh16=v0; hi=sra v1; lo=srl v0 (reusing sh16).

So both have sh16=v0; the difference is which shift is computed first and its dest.

If the source order were sra first (hi first) with the same allocation, we'd match. But making hi first flips sh16 to v1.

What if we compute hi first via a *named* temp and lo inline? q4 (7, sh16=v1).

Hmm, why does the first-named-temp choice flip sh16? Probably because the named temp's pseudo is created at the declaration (block start) and gets a lower regno/priority, changing the allocation order.

Let me try a form where BOTH shifts are named but the *declaration order* is lo,hi while the assignment order is hi,lo:
```
s32 lo;
s32 hi;
hi = sh16 >> 16;
lo = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)((hi + lo) >> 1);
```
Let me test this (r1).

Also:
r2: declare lo, hi at the function top (not the block) and assign hi first.

Let me test.
