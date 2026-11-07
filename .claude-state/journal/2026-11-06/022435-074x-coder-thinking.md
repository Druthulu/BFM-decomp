---
ts: 2026-11-06T09:24:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AKTzYkrAPsQboYmJBNFp
---
b6 is 59 vs 58, and the epilogue structure differs (j 3284 with move a0...). Not it.

Hmm, `move a0,zero` / `move a0,s1`? That's the goto label handling — weird.

Let me reconsider. The original source with the pin gives score 0. The lever-free difference is loop.c's giv combining. To match, we need loop.c to behave as if v0 is a hard reg. Since we can't pin...

What if v0's set is inside a nested function call argument... no.

What if the copy is `v0 = (u32 *)base;` but placed in a *different basic block* such that loop.c doesn't record it as a giv? loop.c records givs for sets of pseudos in the loop regardless of block. But `record_giv` has conditions: the giv must be `dest_reg` set in the loop and the source a biv; it records all.

What if v0 is set *conditionally* (inside the if) — it already is.

Hmm what if v0 is set twice in the loop (e.g., also `v0 = 0` before the if)? Then it's not a simple giv? It would still be a giv maybe.

Actually — what if `v0` is set via a *memory* store/load, e.g. a local array? no.

What if we make v0's source `base` but through a cast that becomes a different pseudo: `u32 *t = (u32 *)base;` then `v0 = t;` — two copies, more givs.

OK item 4 = wall, best 8. Wall tag: `loop-giv-combine`? The mechanism: lever-free the `v0 = base` copy is a DEST_REG giv (add 0) that loop.c's combine_givs uses as the base for all address givs, folding e's +4; the pin makes it a hard-reg set (not a giv) so the address givs keep their own biv. That's a new tag `<pass>-<what>`: `loop-giv-combine`. Hmm, or existing `loop-extra-iv` is close but describes the opposite. I'll define `loop-giv-combine`.

Wait — actually, hold on. Is it possible that the *original* source really had the pin because the function returns void*? Yes, the comment says "the function RETURNS the slot". So the true fix is a signature change, forbidden. The wall is real.

Now items 5 and 3. Let me test item 5 keepalive-only. Extract def 7514-7539.

Item 5 def:
```
void func_80183E68(s32 *a0, s32 a1, s32 a2) {
    s32 sp10[4];
    s32 sp20;
    s16 *q;
    u16 *p;
    s16 t;
    register s32 rv __asm__("$2");
    q = &D_80126CBA;
    ...
    rv = sp20;
    *a0 = rv;
    rv = (s32)a0;
    __asm__ __volatile__("" : : "r" (rv));
}
```
Target likely: `move v0,a0` at end. With keepalive-only, rv = sp20 then *a0 = rv (rv used) then rv = a0; asm(rv). rv's last set is a copy of a0 and the asm uses it → could coalesce with a0 (a0 is a param, in a0 reg at entry but it's a hard reg... params are pseudos that may be assigned). If rv coalesces with a0, no move. Target has `move v0,a0`? Let me check the target dump.
