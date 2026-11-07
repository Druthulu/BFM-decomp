---
ts: 2026-11-06T05:01:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oqmI6IcKvRdlONOLazBU
---
Interesting: without the memory clobber, score 14, 111 ins (same as q1). So the memory clobber is what forces the reload and the ordering; the bare asm only fixes the ordering partially (score 14 vs 38).

So the memory clobber is essential.

OK, for a real-C crack I need:
1. The store→load ordering (achieved by do-while, 38).
2. The reload after the store (cse memory barrier).
3. The register assignment.

For (2), I need a real store that cse thinks may alias EA6. 

Hmm, wait. What if I reorder the source so that the *load* happens after the store in a way that requires a fresh load? E.g.:

```
if ((s16)D_80078EA6 < 0x80) {
    D_80078EA4 += a1;
    if ((s16)D_80078EA6 >= 0x81) ...
}
```
The load for the inner if is after the store. cse reuses the earlier load. To force a reload, the earlier load must be *killed* — i.e., a store that may alias. 

Idea: make the store write through a pointer that the compiler can't disambiguate, but keep the reloc. What if I declare `s32 *p;` and assign `p = &D_80078EA4;` and then `*p += a1;`? The store's address is a register (p) → unknown alias → cse must reload EA6. But the generated code: `lui v1, D_80078EA4; ...` — the reloc is D_80078EA4 (same symbol!) and the address materialization might be `lui v1; addiu v1` or the macro. Earlier p1 gave 103 ins / 76 — worse, but maybe with the right combination it works.

Let me look at p1's disassembly to see how the pointer store was generated. Actually, p1's score 76 with 103 ins suggests the address computation changed a lot.

Alternatively: keep the store direct but add a *fake* store through an unknown pointer that cse can't remove. That adds an instruction. No.

Hmm, what about the *load* being through a pointer? `s16 *q = &D_80078EA6; ... if (*q >= 0x81)`. The load's address is a register → cse can't prove it doesn't alias the store → reload. And the address materialization: gcc would compute q once (`lui v1; addiu v1`) and use `lh v0,0(v1)` — that's 3 insns instead of 2 (lui v0; lh v0). Target has 2. Mismatch.

Unless gcc folds the address into the load with the macro: for `*(s16 *)&D_80078EA6`, gcc might emit `lui v0; lh v0,%lo(...)` — let me test a minimal variant: keep everything else, change only the *inner* load (the one after the store) to go through a pointer q, and see what it generates.

Actually p2 changed ALL the (s16)D_80078EA6 uses to *q and scored 134. Let me instead change only the inner (>= 0x81) load in the third block. That's one load. If it produces `lui v0; lh v0` with reloc D_80078EA6, we win.

Let me test that: in v1, replace only the `(s16)D_80078EA6 >= 0x81` with `*(s16 *)q >= 0x81` and add `s16 *q = (s16 *)&D_80078EA6;`.

But q's assignment would be a `lui v1, D_80078EA6; addiu v1` — extra insns. Unless gcc optimizes `*(s16*)&sym` to a direct load.

Let me test quickly.

Actually, a cleaner idea: use a *union* or a cast that makes gcc emit the load through a computed address but with the macro. Hmm.

Let me just test a few things empirically:
t1: inner load through `*(s16 *)&D_80078EA6` (direct, no variable).
t2: inner load through a variable q.
t3: v1 + do-while stores + inner load direct-cast.

Let me generate.
