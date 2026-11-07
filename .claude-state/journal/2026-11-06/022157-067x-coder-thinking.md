---
ts: 2026-11-06T09:21:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y3E54BwZMh18PQsxHkjY
---
Yes: dest must be a pseudo (>= FIRST_PSEUDO_REGISTER). So in target, `v0 = base` with v0=$2 is NOT a giv. In mine, v0 is a pseudo → it IS a giv (add_val 0) and participates in combine_givs, changing which giv is canonical.

So to match lever-free, we need v0's assignment to not be a pseudo giv. But v0 must be a normal variable in the lever-free version... unless we can restructure so that the "return" value isn't a separate pseudo assignment in the loop.

Idea: make the return value flow from `base` itself without a copy: the target has `move v0,s1` at the goto — a copy from base. If instead we write `goto epilogue` and at epilogue do something... the value must be base.

Alternative: declare v0 but assign it from a non-pseudo-giv expression, e.g. `v0 = (u32 *)base + 0;` still giv. `v0 = (u32 *)((u8 *)base);` giv.

What if v0 is assigned *outside* the loop? E.g.:
```
u8 *found;
...
found = base;  // in the if
goto epilogue;
...
epilogue:
v0 = (u32*)found;
```
But `found = base` inside the loop is still a copy (giv). Hmm.

What if the loop uses a pointer `base` and the found value is `base` itself, and we return via a *different* path: e.g. put the epilogue inside the loop? No.

Alternatively, make `v0` a global? no.

Hmm, what if we eliminate the `i` counter and use `base` as the loop variable (compare against end pointer)? That changes the loop structure entirely — target has `slti v0,v1,64` so i is there.

What if the copy `v0 = base` is replaced by `v0 = (u32 *)base;` where base is a `u8*` — a cast is a nop copy, still a giv.

What about assigning `v0 = e - 1`? Different codegen (addiu -4). No.

OK here's another thought: what if `v0` is assigned from `D_801DA130 + i*0x18`? That's a different expression (not a copy of base), e.g.:
```
v0 = (u32 *)(D_801DA130 + i * 0x18);
```
That would be a multiply giv — expensive and different codegen.

Hmm. What if the found value is stored in a *global* temp? no.

OK, maybe item 4 is a wall too: "loop-giv-combine" or use the existing tag `loop-extra-iv`? The wall here: the lever-free pseudo `v0` becomes a giv that combine_givs merges the address givs into, folding e's +4; the pin (hard reg) keeps the address giv canonical. Hmm, but target has the extra IV (e) — mine loses it. The existing tag `loop-extra-iv` says "loop.c adds an extra induction variable: one more callee-saved reg, frame and bank order change". Here it's the reverse: lever-free loses the +4 in the biv.

Let me try one or two variants for item 4 quickly:
(a) `func_80016714((u8 *)e - 4, 0x18);` — forces e's address use as a DEST_ADDR? No, it's an argument (DEST_REG giv). Might keep e as a giv.
(b) Assign v0 outside the loop via a flag variable... e.g.:
```
s32 found = 0;
...
if (e->flag == 0) { ...; found = 1; goto epilogue; }
...
epilogue:
v0 = found ? (u32*)base : 0;
```
No, extra codegen.

Let me try (a).
