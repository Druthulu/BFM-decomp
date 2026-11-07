---
ts: 2026-11-06T08:56:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qjbQp79Yj45HvOn3Trlr
---
Item 2: stripping the keepalive gives score 6 with a pure v0/v1 swap in the else branch (positions 14-19). So the else branch's two values p (loaded u16) and g (loaded s32) have their registers swapped.

Target: lw v0,32(a1) [g? p?]; lw v1,220(a1); lhu v0,24(v0); ori v1,v1,0x80; sw v1,220(a1); sh v0,260(a1).

Let me map: p = ((*)self)->unk20; g = self->unkDC; p = *(u16*)(p+0x18); g |= 0x80; self->unkDC = g; self->unk104 = p.

- unk20 at offset 0x20 = 32; unkDC at 0xDC = 220; unk104 at 0x104 = 260.
Target: lw v0,32(a1) = p (pointer); lw v1,220(a1) = g; lhu v0,24(v0) = p reloaded; ori v1,v1,0x80 = g; sw v1,220 = g; sh v0,260 = p.

Mine: lw v1,32(a1) [p]; lw v0,220(a1) [g]; lhu v1,24(v1); ori v0; sw v0; sh v1. So mine assigns p→v1, g→v0; target p→v0, g→v1. The keepalive (3 extra uses of p) raised p's priority so p got v0.

So real C: give p more refs genuinely. In the else branch, p is used 2 times (load pointer, lhu dest, store) — actually 3 refs (set from lw, use in lhu address, set again, use in store). Hmm.

The else branch code:
```
p = self->unk20;      // 1
g = self->unkDC;      // 
p = *(u16*)(p + 0x18);
g |= 0x80;
self->unkDC = g;
self->unk104 = p;
```
p's refs: set (lw), use (lhu address), set (lhu dest), use (sh). That's 4 refs, live from first set to the store.

g: set, use in or, set in or, use in sw = 4 refs.

Target gives v0 to p and v1 to g. Priority: both similar; tie-break by qty number (p's qty vs g's). The keepalive gives p 3 extra uses → higher pri.

Real C options:
- Reorder statements: compute g first or p first. The loads' order in the target: lw v0,32 (p) then lw v1,220 (g). Mine same order. 
- Give p more genuine refs by using it in an expression: e.g., `self->unk104 = *(u16 *)(p + 0x18)` without the intermediate? That changes refs.

Let's look at the other branch (t==0) which matches: mask pinned a0, and f/q. It's fine.

What real C could give p higher priority? The keepalive's 3 uses are fake. Real: use p in the store address or in the g computation? For instance:
```
        p = ((Unkstruct_801896EC *)self)->unk20;
        g = ((Unkstruct_801896EC *)self)->unkDC;
        p = *(u16 *)(p + 0x18);
        g |= 0x80;
        ((Unkstruct_801896EC *)self)->unkDC = g;
        ((Unkstruct_801896EC *)self)->unk104 = p;
```
Maybe write the store as `*(u16*)((char*)self + 0x104) = p;` — same.

What if we use a pointer variable for self's fields? The struct has unkDC/unk104. Could write `((u16*)((char*)self + 0x104))[0] = p;`.

Alternatively, maybe restructure the branch as:
```
        p = *(u16 *)(((Unkstruct_801896EC *)self)->unk20 + 0x18);
```
(one statement) — this removes the intermediate p pointer ref. Let me try variants:
h1: p = *(u16*)(self->unk20 + 0x18); (single statement)
h2: swap the order: g loaded after p's lhu.
h3: use `p += 0x18` then load? no.

Let me look at the target's exact instruction sequence and think about which source produces it. Target 22 insns. Let me get the full listing for both w1 and target.
