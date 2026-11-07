---
ts: 2026-11-06T18:26:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zjqRHODPJWBqgG3eAhfy
---
Best is 3 (the pure register residual). No structural spelling changes it. This strongly suggests the global-alloc preference is unavoidable by statement order.

Let me check one thing: is $3 perhaps occupied in our build by something that would block it? The dispositions showed hard regs used: 2 4 5 6 (v0, a0, a1, a2). $3 is free. The target uses 2,3,4,5,6 (v0,v1,a0,a1,a2). So $3 is the free one and the pref steals it.

Given the analysis, the only real-C route would be to change 76's preference or priority. I've tried structural variants.

One more idea: what if we make 76 conflict with 72 by making 72 live across the load in the *same* block? Consider a structure where the load happens BEFORE the inner branch:
```
v0 = D_80078EB1;
if (!(v0 < a1)) {
    v1 = ((Unk*)a0)->unkCC;
    if (v0 < a2) { v0 = 1; }
    else { v0 = 2; }
} else {
    v1 = ((Unk*)a0)->unkCC;
    v0 = 2;
}
```
Here, in the first block, the load is followed by the inner if — but 72 is still dead after the load (the inner if doesn't use a0). Hmm.

What if the inner if's *condition* used a0? No.

What about a structure where a0 is used after the load in the same block: e.g., load twice?
```
v1 = ((Unk*)a0)->unkCC;
v1 = ((Unk*)a0)->unkCC;  // dead, removed
```
No.

What if the second use of a0 is in the store: `*(s32 *)(v1 + 0xB0) = v0;` — no.

Hmm, what about `((Unkstruct*)v1)->unkB0 = v0;` where the struct type's unkB0 is a pointer... no.

What about storing to `*(s32 *)(v1 + 0xB0) = v0;` and also making v0 depend on a0? no.

Let me consider: maybe use a0's value in a *comparison* after the load that combine folds. E.g.:

```
if (!(v0 < a1)) {
   v1 = load;
   if ((s32)a0 == 0) { }  // dead
```
dead code removed.

OK. Alternative: make 72 NOT die at the load by making the load base a *different* pseudo whose REG_DEAD is harmless. E.g., compute `s32 base = (s32)a0;` ONCE before the branches (adds a move in the prologue? It's just the param copy 72 itself — no).

What if we make the base `(char *)a0 + 0xCC` computed ONCE before the branches as a temp `base`, and the loads read `*(s32*)base`? Then:
- `base = (s32)a0 + 0xCC;` → addiu base, a0, 0xCC (one insn before the branches). The target has no such insn. But combine might sink/fold the addiu into each load (it's used 2-3 times, so combine can fold it into each use? combine can fold a PLUS into a load if the temp is used once; with 2 uses it stays). So an extra insn — score ≥1.

Hmm, but if `base` is used 2 times, the addiu stays → 16 insns vs 15.

What if we compute `base` and the loads use `*(s32 *)(base)` — 1 extra insn. Not a match.

Let me look at the .lreg of the target-equivalent (pinned) to see the RTL: the pin makes 76 a hard reg. In the target's RTL, the load is `(set (reg 76 = $3) (mem (plus 72 204)))` with REG_DEAD 72 — same structure. So the target's compiler ALSO merged prefs, but the pin preassigned 76.

Conclusion: no real-C spelling of this structure avoids the pref, since the pref is a property of the param copy + the load.

Unless we remove the param copy from global allocation: what if a0 is used only ONCE in the source? Then the param copy 72 would have refs 2 (copy + 1 use) and live... still an allocno. Hmm.

What if the param is used in only one basic block? Then 72 would be block-local (local-alloc) and not a global allocno → expand_preferences wouldn't merge (reg_allocno[72] < 0)! 

So: if all uses of a0 were in ONE basic block, 72 is local, no merge → 76 gets $3.

Our structure has a0 used in 2-3 blocks. Can we restructure so all a0 uses are in one block while keeping the target's insns? The loads are in different blocks (arms). Unless... the load is hoisted into a single block (w5/w6: 1 load, wrong count).

Hmm, but what about a0's *param copy* 72: if the loads all used a single precomputed pointer that is computed in block 0 (from a0) and used in the arms, then a0 (72) is used only in block 0 → block-local! The precomputed pointer p = a0 would then be the global (used in the arms). But p = a0 is a copy → coalesced → the RTL might become the same as using a0 directly (72 becomes the base again, used in all blocks). Hmm, unless p is `(char*)a0 + 0xCC` (an addiu) which stays as one insn.

That adds 1 insn. Not a match.

OK, item 3 looks like a WALL: global-alloc's expand_preferences merges the param copy's $4 preference into the load result at the REG_DEAD point; the pinned version was the only way to get $3.

But wait — maybe I should test whether a `do{}while(0)` (C0535) changes anything, or other catalog moves. Given the time (item 3 at ~45 min), let me now apply the discipline: I have ~30 tries. Let me count: w1-w8 (8) + s001-s020 (20) = 28, plus baseline = 29. Need ≥30 scored tries for a WALL. Let me do a couple more targeted tries (do-while, u8/s16 widths) to reach 30+, then record a WALL and move on.

Quick extra candidates:
w9: do{}while(0) around the load+store? 
w10: `u32 v0; u32 v1;`
w11: `s16 v0`? no.
w12: the `&&` fold with the load hoisted in the then-arm (w8 was that) — done.

Let me do w9 (do-while around the whole body) and w10 (u32) and w11 (s32 v1 = 0 init? adds insn).

Actually, one more idea worth a try: **make the store block use a0** by storing to `v1` where v1 is derived from a0 in the store: no.

And: **make v0 and v1 swap roles**? no.

Let me also try: `if (!(v0 < a1)) { if (v0 < a2) {...} else {...} } else {...}` but with the *load* replaced by a function-like macro? no.

Let me try 3 more: 
w9: `s32 v0; s32 v1;` with `v1 = (s32)((Unkstruct_80184B70 *)a0)->unkCC;` (cast to s32) — probably same RTL.
w10: store via `((Unkstruct_80184B70 *)v1)->unkB0 = v0;`
w11: `do { ... } while (0);` around the two ifs.

Then WALL.

Actually hold on. One more idea that could work: **change the type of v1 to a pointer** (`Unkstruct_80184B70 *v1;`) and store via `v1->unkB0 = v0;`. Then the load `v1 = (Unkstruct*)a0->unkCC`... the field unkCC's type matters. If unkCC is declared as s32 in the struct, the load into a pointer variable would be a pointer-typed load — same mode SImode. The store `v1->unkB0` = `sw v0,0xB0(v1)`. Same RTL. But the *mode* of the pseudo changes? No, both SImode. The struct's unkCC field type: let me check the struct definition to see. If unkCC is s32, assigning it to a pointer needs a cast? In C, s32 → pointer is allowed with a warning. Not a lever.

Hmm, what about making v1 a pointer and the *load* a pointer load from a pointer field? If unkCC is `s32`, then `v1 = (Unkstruct*)p->unkCC;` — same.

OK let me do the last tries.
