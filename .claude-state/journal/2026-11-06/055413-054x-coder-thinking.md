---
ts: 2026-11-06T12:54:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rw8cNPZ5PI0JCnGmCu00
---
a4's residual: mine[55] `lhu v0,10(s2)` vs target `lhu a0,0(s0)` — so the volatile index load makes the address biv-based (`10(s2)`) instead of giv-based (`0(s0)`), exactly as the header said (loop.c's DEST_ADDR giv rewrite fails for volatile mem). Plus an andi.

So a4 is the documented failure.

a5/b3: the volatile *table* read keeps the giv but adds andi+nop and the case-3 reload still folds.

Hmm. Let me look at a5's remaining issues:
1. `lbu v0,0(v0); nop; andi v1,v0,0xff` vs `lbu v1,0(v0)`.
2. missing `lhu v0,0(s0)` reload in case 3 + the a0 argument.

Wait, actually looking at a5's diff again: target has `move a0,zero; lhu v0,0(s0); nop; sll v0,v0,0x2` and mine has `sll v0,a0,0x2` — hmm mine's case 3 uses a0 (the folded idx) and target reloads.

So a5's volatile table read didn't force the case-3 reload? It should have invalidated memory... Actually the volatile read is `sv[idx]` BEFORE the switch; cse invalidates memory at that point, but then `idx = p->unkA` was read BEFORE the volatile read... The case 3 read of p->unkA after the volatile read should be a fresh load. Unless cse re-validates.

Hmm, the ordering in the source: `idx = p->unkA; dsp = volatile sv[idx]; switch`. The volatile read kills the memory entry for p->unkA. Then case 3's `p->unkA` must reload. But the diff shows mine folds. Maybe the fold is `idx` itself (the local), not p->unkA: case 3 uses `((Unkstruct_80030CA4 *)p)->unkA` directly — a load. Hmm.

Wait, mine[55] `lhu v0,10(s2)` in a4 was the volatile index load. In a5, mine[?]... the diff for a5 showed mine[71] `bne v1,v0` then `sll v0,a0,0x2`. Hmm, `a0` there is the call arg for func_8002EFF8(0, mask)? No, `sll v0,a0,0x2` is the table index scaling for `tbl[...]`. So mine uses a0 which holds the dispatch idx (the fold).

So the volatile table read didn't stop the fold. Because `sv` and `tbl`/`p` are different objects and cse's memory table tracks per-object? Actually gcc's cse memory table is invalidated wholesale by a volatile read? Maybe not — `invalidate_memory` is called for volatile *writes* and calls; for volatile reads maybe not.

OK. So the a5 path: the volatile read changes the load's codegen but doesn't invalidate.

Given the header's detailed ruling-out, this really is a wall. But I need 30 scored tries. Let me try a set of other real-C ideas that might invalidate memory legitimately:

Idea A: make the case-3 read go through a *pointer* that cse can't relate: e.g. `mask = tbl[((Unkstruct_80030CA4 *)p)->unkA];` → `mask = tbl[idx2];` where idx2 is read after a real store.

Idea B: move a real store between: `p[0x50] = 0;` before `mask = tbl[...]`? The header says case 3 keeps the store after the lw because the store's varying address forces cse to invalidate and force the reload. Wait — re-read lever 8: "with the store AFTER the loads it can no longer fill the lhu's load-delay slot... At case 3 the same rewrite instead lets cse reuse the switch's own lhu (-2 insns), so that site keeps `p[0x50] = 0;` FIRST: the store's varying address makes cse invalidate_memory and forces the target's reload."

Hmm, so at case 3 the source is `mask = tbl[p->unkA]; p[0x50] = 0; func(...)`. Wait no — the current source at 3685-3687 is:
```
mask = tbl[((Unkstruct_80030CA4 *)p)->unkA];
p[0x50] = 0;
func_8002EFF8(0, mask);
```
So mask is loaded first, then the store. The header says "that site keeps p[0x50] = 0; FIRST" — but the code shows it after. Confusing (maybe the comment refers to a different site).

Anyway: the dispatch-block memory clobber is needed for case 3's reload. Since the reload is `lhu v0,0(s0)` reading p->unkA, and the dispatch already loaded it into idx...

What if I write case 3's index read differently so cse can't fold it even without invalidation: e.g. read via a different type/pointer:
```
mask = tbl[*(u16 *)(p + 0xA)];
```
vs the struct field. cse's memory table is address-based; `*(u16*)(p+0xA)` and `((Unkstruct*)p)->unkA` are the same address → same entry. Hmm.

What about reading it through a *different base pointer* with a different offset? cse canonicalizes addresses, so `p+0xA` vs `(p+0xA)` same.

What if case 3 re-reads from `s0`-style: the target's `lhu v0,0(s0)` where s0 is the biv (p+0xA)? So target's read is `((Unkstruct*)p)->unkA` = 0(s0).

Idea: make the dispatch read a *different* expression than case 3's so cse can't equate them: e.g. dispatch reads `*(u8 *)(p + 0xA)` (byte) and case 3 reads the u16 field. Different modes → cse's table is mode-sensitive? Actually cse does have mode checks in some cases. Worth a try.

Let me also try: dispatch `idx = p->unkA;` and case 3 `idx = p->unkA;` (re-assign the local) before the mask — a second load; cse would fold it.

Hmm.

Let me just run a batch of ~12 more variants (to reach 30+ tries) and then record the wall.

Variants:
- c1: dispatch reads u8 at p+0xA, case 3 reads the u16 field.
- c2: case 3 reads the index via `*(u16 *)(p + 0xA)`.
- c3: case 3 reads `idx` after assigning `idx = ((Unkstruct_80030CA4 *)p)->unkA;` inside case 3.
- c4: put `p[0x4E] = p[0x4E];` (a real self-store → invalidates memory) in the dispatch block.
- c5: put the `p[0x50] = 0;` store in the dispatch block before the switch.
- c6: swap the two statements in case 3.
- c7: dispatch via a temp u8 variable.
- c8: dispatch `dsp = sv[idx];` where sv is `u8 *` but read as `*(u8*)(sv+idx)` and idx is s32.
- c9: move `p[0x4E] -= 1;` after the dispatch load.
- c10: read idx twice in the dispatch: `idx = p->unkA; dsp = sv[idx]; idx = p->unkA;` (already b4=19).

Let me try c1-c9.

Also, an important one: c4 `p[0x4E] = p[0x4E];` is a real store (self-assignment) — gcc might delete it as a no-op. Hmm.

What about `p[0x4E] |= 0;`? deleted.

A store that can't be deleted: `p[0x4E] = p[0x4E];` — gcc keeps self-stores to memory (it's a real store, not redundant since memory may be volatile-ish? no, gcc can delete a self-assign? Usually it keeps it: `x = x` is a real store unless the value is known). Actually gcc's jump/flow may remove it. Let's test.

Let me generate c1..c10.
