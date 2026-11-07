---
ts: 2026-11-06T08:56:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FfaIerpvVDg5jdxRNKK8
---
Now clear. In the else branch:
- Target: p (the pointer load from 32) → v0; g (load from 220) → v1.
- Mine: p → v1; g → v0.

Also note the t==0 branch matches: f (220) → v0, q/p (32) → v1. So in the if branch, the 220 load is in v0 and the 32 load in v1; in the else branch, swapped. Interesting: target has the two branches using opposite registers.

In the if branch: `f = self->unkDC` (220) → v0; `q = self->unk20` (32) → v1; then q = *(u16*)(q+0x18) → v1; f &= mask; store f→v0; store q→v1.
In the else branch: `p = self->unk20` (32) → v0; `g = self->unkDC` (220) → v1.

So the else branch assigns the first-loaded value (p, from 32) to v0. Mine gives the 220 load v0.

The priority: with the keepalive, p has 3 more refs → higher pri → v0. Real C must give p more refs or g fewer.

What if the else branch's statement order is: `g = ...; p = ...;` (g loaded first)? Then target's load order is lw v0,32 (p) first — so p is loaded first in target. Mine loads p first too.

What if we write the else branch using a pointer variable for the struct? E.g.:
```
        p = ((Unkstruct_801896EC *)self)->unk20;
        g = ((Unkstruct_801896EC *)self)->unkDC;
        ((Unkstruct_801896EC *)self)->unkDC = g | 0x80;
        ((Unkstruct_801896EC *)self)->unk104 = *(u16 *)(p + 0x18);
```
Here p has 2 refs (set, use), and the lhu result is stored directly. The target's code: lhu v0,24(v0) then sh v0,260. With p's refs 2 and live short, its pri... Let's test variants:

h1: `p = *(u16 *)(((Unkstruct_801896EC *)self)->unk20 + 0x18);` (one line)
h2: `self->unk104 = *(u16 *)(p + 0x18);` with p refs 2.
h3: reorder g after p.
h4: use the struct-typed pointer variable `s = (Unkstruct*)self;`.

Let me test h1-h4.
