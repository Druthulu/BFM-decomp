---
ts: 2026-11-06T12:55:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BMgvmxAFNCGmk6omJOw7
---
So insn 52 = `lbu a0,0(s0)` = the dispatch idx load (`idx = *(u8*)(p+0xA)`) at address 0(s0). Target has `lhu a0,0(s0)` there.

So the dispatch load itself is the residual: target loads u16 (`lhu`), c1 loads u8.

So I need the dispatch load to be `lhu` (u16) but still break cse's fold for case 3.

So: dispatch `idx = p->unkA` (u16 load → lhu) and case 3 must miss the cse entry.

Options:
(a) Make the case-3 read a different mode → but target's case-3 reload is `lhu`, so a u8 read there would be wrong.
(b) Make the dispatch read a u16 at a *different* address that's value-equal: no.
(c) Add a memory-invalidating construct at the dispatch point that doesn't emit code and isn't a barrier: none in C.
(d) Use a *different* expression for the case-3 read that cse treats as a different memory reference: e.g. read via a pointer variable that's been through a cast chain? cse canonicalizes.

Hmm... what about c1 but with the *dispatch* reading u16 and the *case-3* read being the u8?? Then case 3's lhu target... no.

Wait — maybe I can have BOTH: dispatch reads u16 for idx, and case 3 reads a *byte* which then... no, target case 3 is lhu.

Let me reconsider: what if the dispatch reads `idx = *(u16 *)(p + 0xA);` and case 3 reads `tbl[*(u16 *)(p + 0xA)]` — same, folds.

What if the case-3 read goes through a *different* pointer that cse can't canonicalize because it involves a value cse doesn't know: e.g. `u8 *pp = p; ... tbl[*(u16 *)(pp + 0xA)]` — same.

Hmm, what if the case-3 index read uses the *original* `p` after `p` was modified? No.

New idea: what if the dispatch load is u16 but from a *volatile* pointer and the giv issue only affects... a4 showed the volatile index load breaks the giv (lhu 10(s2) instead of 0(s0)). But what if the volatile load is at case 3 only? Then only that load can't be giv-based: target's case-3 load is `lhu v0,0(s0)` — giv-based! So no.

OK so the c1 trick is the only one that got 343 ins and a single width diff. Can I make the dispatch u8 load zero-extend into a u16 and have the *comparison* use lhu? The target's dispatch load is `lhu a0,0(s0)` — a u16 load into a0.

Hmm, what if I write the dispatch as:
```
idx = *(u8 *)(p + 0xA);
dsp = sv[idx];
```
→ lhu? no, u8 → lbu.

What if the dispatch reads a u16 but at a *shifted* address that's still equal: `*(u16 *)(p + 0xA)` = lhu. Same as p->unkA.

So the fold returns.

Unless... the *case-3* read is the one I make u8-in-a-way-that-still-emits-lhu? No.

Alternatively: make case 3 read a *u16 from a different base* that cse can't relate: e.g. `tbl[((Unkstruct_80030CA4 *)p)->unkA]` where `p` is `u8*`; cse canonicalizes `(plus (reg p) 10)`.

What if case 3 reads through the *biv pointer* `s0` equivalent: `((Unkstruct_80030CA4 *)(p))->unkA` vs dispatch `idx = ((Unkstruct_80030CA4 *)p)->unkA` — identical.

Hmm, what if the dispatch assigns `idx` from the struct but case 3 reads `*(u16 *)((u8 *)p + 0xA)` — identical canonical form.

OK, what about attacking from the other side: the target's dispatch load is `lhu a0,0(s0)` — what if in my c1 I make idx a `u8` variable instead of u16? Then the dispatch `idx = *(u8*)(p+0xA)` → lbu, and case 2 `func_8003D3B4(idx, 1)` passes a u8 → a0 = lbu. Target: lhu. No.

What if idx is u16 and the dispatch read is `*(u16*)` (lhu) but I ALSO add a byte read that cse registers, at zero cost? A byte read that's used... 

Hmm: what about `dsp = sv[idx]; ` where sv is `u8 *` — the table read is a byte read at a *different* address (sv+idx), unrelated.

OK here's another thought: cse's fold of case 3's load. What if the dispatch *stores* something in between? E.g. `p[0x4E] -= 1;` is before. The target's case-3 reload is needed because... the barrier.

Since c1 is at score 1 with only a width mismatch on the dispatch load, maybe I can make the dispatch load lhu while keeping the u8 read elsewhere. E.g.:

```
idx = ((Unkstruct_80030CA4 *)p)->unkA;   // lhu
dsp = sv[idx];
if (*(u8 *)(p + 0xA) == idx) { }         // byte read, folded away
```
The if with an empty body would be deleted. But if it's `if (...) {}` the condition may be deleted. Hmm.

What about making the byte read used in a way that folds to nothing:
```
u8 b = *(u8 *)(p + 0xA);
idx = b | (idx & 0xFF00);   // identity? that's a launder
```
No.

Alternatively, use the byte read to compute dsp's index: `dsp = sv[*(u8 *)(p + 0xA)];` and keep `idx = p->unkA` separately. Then:
- dispatch: `idx = p->unkA;` → lhu a0,0(s0) ✓
- `dsp = sv[*(u8 *)(p + 0xA)];` → a second lbu at the same address, and this byte read registers a QImode entry in cse's table. Would that invalidate the u16 entry? cse's table has one entry per address; inserting a QImode entry for the same address may *replace* the u16 entry (cse's insert uses the mem's address; different modes → different entries? In gcc's cse.c, `struct table_elt` is keyed by the full expression including mode? For MEMs, the expression includes the mode. Two MEMs with different modes are different expressions → both entries exist. So case 3's u16 read would still hit the u16 entry.

But c1 showed the u8 read *did* break the fold: the dispatch read u8, then case 3's u16 read reloaded. That means the u8 entry was inserted and the u16 entry was NOT (because the dispatch never did a u16 read). Right! In c1 there was never a u16 read of that address before case 3, so case 3's u16 read is a fresh load.

So the fix: do the u16 read *and* keep case 3's u16 read from folding. That's impossible without invalidation.

Unless: do the u16 read at the dispatch into `idx`, and then make case 3 read a *u8* value... no, target is lhu.

Hmm hold on, what does the target's case-3 `lhu v0,0(s0)` actually load? It's `p->unkA` at 0(s0). If the target's dispatch also loaded u16 at 0(s0), then without the barrier cse folds and case 3 reuses it. The target's case-3 reload exists because of the barrier.

So the target's behavior fundamentally needs memory invalidation.

Real C constructs that invalidate cse's memory table without emitting an insn:
1. `__asm__("" : : : "memory")` — the barrier (forbidden).
2. A `volatile` access — emits an insn or breaks the giv.
3. A function call — emits a call.

Hmm... What about a *volatile* access to something in the same loop that doesn't break the giv? The giv break happens because the volatile mem load's address can't be a giv. If the volatile access is to an address that is NOT part of the giv chain (e.g. a fixed global), it would emit an extra load/store though.

What if the volatile access is a *store* of a value already stored? E.g. `*(volatile u8 *)&p[0x4E] = p[0x4E];` — an sb (1 insn) — but the target doesn't have it. Count would be 344. Score would be > 0.

Hmm.

What about `__asm__` without the memory clobber? Not allowed.

What if a *call* already exists between? `func_8002EFF8` is called in case 3 after the mask load. No.

OK — what about using the *order*: put the case-3 mask load AFTER the `p[0x50] = 0;` store? Then the store invalidates memory and forces the reload! The header says at case 3 the source keeps the store first ("that site keeps `p[0x50] = 0;` FIRST"). But the current source has mask first. Wait, the current code:

```
case 3:
    mask = tbl[((Unkstruct_80030CA4 *)p)->unkA];
    p[0x50] = 0;
    func_8002EFF8(0, mask);
```
The header lever 8 says: "with the store AFTER the loads it can no longer fill the lhu's load-delay slot and dbr takes it for the jal's. At `case 3` the same rewrite instead lets cse reuse the switch's own `lhu $a0` (-2 insns), so that site keeps `p[0x50] = 0;` FIRST". 

Hmm, that suggests the case-3 site should be `p[0x50] = 0;` FIRST, then mask. But the code has mask first. Maybe the comment is about a different site (the 0x80031400 one).

Let me try c6 = `p[0x50] = 0; mask = tbl[p->unkA];` = score 2. Close! Let me look at c6's diff — with the store first, the store invalidates memory and case 3 reloads. Score 2, 343 ins.

Let me look at c6's diff.

Also maybe combine c6 with other tweaks. Let me check.
