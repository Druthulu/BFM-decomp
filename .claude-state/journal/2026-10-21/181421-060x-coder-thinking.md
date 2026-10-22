---
ts: 2026-10-22T00:14:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vSiiQkBiA7FEF0S3Rz8q
---
This is exactly the pattern from moves.md! The launder `__asm__ __volatile__("" : "=r"(pv));` is an out-only launder whose comment says "zero-byte 2nd SET: kills the sched1 birthing boost".

The moves.md recipe: "launder->pv=*p; pv&=0xFF000000 split (real 2nd set); pv $3 pin dropped; ang $4 pin kept".

Here the source is:
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (...);
```
The launder creates a 2nd set of pv (dead) to kill the birthing boost.

The "real 2nd set" version (per moves.md, e.g. G09's func_80184174): "launder->pv = *p; pv &= 0xFF000000 split (real 2nd set)". So:

```
pv = *(u32 *)p;
pv = pv & 0xFF000000;      /* real 2nd set */
*(u32 *)p = pv | (...);
```
But wait: does this add instructions? The original code is `(pv & 0xFF000000) | (...)`. If we split it as `pv = pv & 0xFF000000;` then `*(u32*)p = pv | (...)`, the generated code should be identical: the AND is computed then OR'd. The difference: with the split, pv has 2 sets → different cse/sched behavior.

That's precisely the recipe that worked in other shards ("launder->real 2nd set pv &= 0xFF000000 split (real 2nd set)"). Let me try it for func_8018AA98.

But careful: the target code for the AND might be `andi` on the value. If we split, gcc might emit the same andi then or. Should be identical.

Let me do this item now. First: extract the function def for func_8018AA98 from the src file, write orig.c, then create the candidate.

Let me find the function's start line. Let me grep for "void func_8018AA98" in that file.
