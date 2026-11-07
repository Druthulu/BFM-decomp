---
ts: 2026-11-06T13:00:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VX9gvX5jIz9XesHR6kjK
---
Only 05:59! So item 2 took 7 minutes. I have plenty of time. Let me push harder on item 2 before recording — maybe I can get 0.

Current best c1 = 1 (only the dispatch load width). Let me think again.

The target: `lhu a0,0(s0)` for the dispatch idx, and case 3 reloads `lhu v0,0(s0)`.

c1: dispatch `lbu a0,0(s0)` and case 3 reloads `lhu v0,0(s0)` ✓ (the reload happens!). So c1 has the case-3 reload correct; only the dispatch load is lbu instead of lhu.

So: I need a u8 read at the dispatch that ALSO loads the full u16. What if the dispatch reads a u16 but stores it into a variable declared u8? `u8 b = p->unkA;` → lbu (truncation known). 

What if the dispatch reads `*(u16*)` into idx (lhu ✓) and case 3 reads `*(u8*)`... then case 3 would be lbu (target lhu). No.

What if BOTH: dispatch `idx = *(u16*)(p+0xA)` (lhu) and case 3 `mask = tbl[*(u8*)(p+0xA)]`? Then case 3 is lbu — mismatch, but maybe cse... no.

Hmm, what about the reverse trick: make the dispatch read a *u16 at a different mode*: read it as `s16` (lh, sign-extend) — target has lhu. No.

What about making the dispatch read a u32? `*(u32*)` = lw. No.

So the target's dispatch load is exactly u16/lhu.

New idea: what if the case-3 reload is caused not by mode but by *cse's* handling of a different base? c1's mechanism: the QImode entry doesn't satisfy the HImode read. 

What if I make the dispatch read `idx = p->unkA` (lhu) and add a *QImode store* to the same address that's a no-op? e.g. `*(u8 *)(p + 0xA) = (u8)idx;` — that's a store (sb) → extra insn. And it would invalidate the memory table, forcing the reload. But +1 insn.

Hmm, target has 343 and c1 has 343. If I add an sb I'd be at 344.

What if I *replace* an existing store with one at that address? No.

OK — what about making the dispatch idx load u16 and making case 3's read *volatile* but through a giv-compatible address? a4 showed the volatile index load breaks the giv. But wait — a4's volatile load was the *dispatch* load, and the giv issue was `lhu v0,10(s2)` instead of `0(s0)`... 

Hold on, in a4 the address `10(s2)` — s2 is the biv p, so p+0xA. The target's case-3 reload is `0(s0)` where s0 = p+0xA (the giv). So a volatile load can't use the giv → 10(s2).

So no.

What if the case-3 read is `*(volatile u16 *)&((Unkstruct_80030CA4 *)p)->unkA` — same.

Alright, what about a different *source* mechanism for the reload: make case 3 read from a *copy* of p that cse can't prove is the same. E.g.:

```
u8 *pp = p + 0xA;   // declared at function top? or inside the loop
...
case 3:
    mask = tbl[*(u16 *)pp];
```
cse knows pp = p+0xA and the dispatch read is at p+0xA → folds.

Unless pp is assigned *inside* the else block after the dispatch load... still known.

Hmm, what if the pointer is passed through a function? No.

What if `p` is modified between? No.

OK here's another thought: what if I make the dispatch idx read a u16 but from the *struct* while case 3 reads a u16 via `*(u16 *)(p + 0xA)` AND I put a *conditional* between them whose condition is a real test that cse can't fold... The switch itself is a conditional but cse handles it.

What about making the dispatch `idx` assignment happen *before* the `if (p[0x4E] >= 2)` store? Then the store `p[0x4E] -= 1;` is between the idx load and case 3 → invalidates memory → reload! And the store is a real existing insn (sb), no extra cost!

Currently the dispatch is in the else branch of `if (p[0x4E] >= 2)`. The idx load happens inside the else. If I hoist `idx = p->unkA;` (and maybe dsp) before that if, then the store in the then-branch happens after the idx load... but the then-branch and else-branch are exclusive: on the else path, no store happens between. Hmm, cse works on the CFG; the store is on the other branch, so it doesn't invalidate the else path.

But wait — cse's memory table is global across the function with invalidation at block boundaries? cse (cse1) processes EBBs; the store in another BB doesn't invalidate.

Hmm, but what if I hoist the idx load to *before* the `if (p[0x4E] >= 2)` and the store is inside the then-branch, with the else containing the switch? The else's path has no store.

Alternatively, hoist the idx load *above* `p[0x4E] &= 0x7F;`? That store is unconditional at the top of the loop body → it's between the idx load and case 3 → invalidates memory → case 3 reloads! And it's a real, existing store (sb). But the dispatch load would then happen before `p[0x4E] &= 0x7F;` — would that change the target's instruction order? The target's dispatch load is inside the else, deep in the loop. Hoisting it would move it in the emitted code → likely a big diff.

Unless... the load could be hoisted by gcc anyway? No.

Hmm.

OK, what about the `p[0x4E] -= 1` store in the then-branch: what if I move the idx load into the then-branch too? No.

Let me try one thing: in the else block, before the dispatch, there's `p[0x4E] -= 1;` in the *then* branch. What if I restructure:
```
if (p[0x4E] >= 2) {
    p[0x4E] -= 1;
} else {
    idx = ...;
    dsp = sv[idx];
    switch...
}
```
The store is not on the else path.

What if the source were:
```
idx = p->unkA;               // hoisted above the if
if (p[0x4E] >= 2) { p[0x4E] -= 1; } else { dsp = sv[idx]; switch... }
```
Then on the else path: idx load, then no store. Folds again.

Hmm, but the *emitted* order: the idx load would be before the `lbu p[0x4E]` / compare. Target has the idx load inside the else. Different order → many diffs.

OK. Let me try yet another angle: make the case-3 read a *different object* that aliases. E.g. read through a global pointer `g = p;`? cse would know.

What if the case-3 read uses `sv`'s value... no.

Let me try a couple of quick experiments around c1 to see if the width can be fixed:

m1: `idx = *(u16 *)(p + 0xA); dsp = sv[idx & 0xFF];` — andi (extra). No.
m2: declare `idx` as u16 and dispatch `idx = *(u8*)(p+0xA);` with case 2 using a fresh `p->unkA`: i.e. `func_8003D3B4(((Unkstruct_80030CA4 *)p)->unkA, 1);` — then the dispatch lbu is only for the table. Target's dispatch is lhu though.

Hmm hold on! Maybe in the target, `lhu a0,0(s0)` at 52 IS the dispatch, and it's u16 because the source reads the u16 field. In c1 the source reads a u8 at the same address. What if I keep the source reading the u16 field for idx (so lhu) but ALSO make `dsp` read a u8 *at a different address* that's not the table... no.

Let me try: `dsp = sv[*(u8 *)(p + 0xA)];` and `idx = ((Unkstruct_80030CA4 *)p)->unkA;` where `idx` is only used in case 2. Then:
- lbu (for the byte) + lhu (for idx) = 2 loads. Target has 1 (lhu) + the case-3 reload. Hmm, target total loads at 0(s0): dispatch lhu, case-3 lhu = 2. Mine would have lbu, lhu, case-3 lhu = 3. One extra.

Unless case 2's use of idx folds with the lhu... it would.

What if the dispatch u8 read is used for BOTH the table index and case 2? Then idx is a byte → case 2 passes lbu. Target's case-2 arg is lhu (from the dispatch lhu). So mine would be lbu there → 1 mismatch (same as c1).

OK so c1's single mismatch is unavoidable with the u8 trick.

Let me now consider: is the target's case-2 argument load a *separate* lhu or the dispatch's? Target: dispatch lhu a0,0(s0) at 52; then `beq v1,v0,...`; case 2 body `func_8003D3B4(idx,1)` would use a0 (already loaded). So one load serving both.

With c1: lbu a0 at 52 serving both → the only diff.

So the width is the whole difference.

Hmm, what if I make the dispatch read `*(u16 *)(p + 0xA)` (lhu ✓) and then *invalidate* memory before case 3 by... the switch's own compare? no.

What about making case 3's read a *pointer dereference through a value cse can't track*, e.g.:
```
u16 *pidx = (u16 *)(p + 0xA);   // local declared at function scope
...
case 3:
    mask = tbl[*pidx];
```
cse: pidx is a pseudo holding p+0xA; the load *pidx is at the same address. cse's memory table is address-based; `(plus (reg pidx) 0)` vs `(plus (reg p) 10)` — cse canonicalizes using the equivalence class of pidx (known equal to p+0xA) → same expression → folds. Unless cse's `canonicalize` doesn't chase multi-insn equivalences... Actually cse does fold `(plus (reg X) const)` when X has a REG_EQUAL note. pidx would have a REG_EQUAL note (p+0xA). So it folds.

What if pidx is assigned inside the loop from a *volatile* read? no.

What if pidx is a `u16 *` and I read `pidx[0]` — same.

Hmm, what if I make the dispatch read from `p` and case 3 read from `sv - 0x576 + 0xA`? cse would relate them via... sv = D_800A4988+0x576 and p = D_800A4988. cse's get_related_value could relate `(plus (reg sv) (-0x576+0xA))` to `(plus (reg p) 0xA)`? The header says cse CAN relate offsets from the same symbol. Since sv is derived from p (sv = D_800A4988 + 0x576), cse may know sv = p + 0x576 → `sv - 0x576 + 0xA` = p + 0xA. It would fold.

OK. I'm fairly convinced this is the wall. c1 = 1 is the best.

Actually, wait! One more idea: what if I use a *union* or a different struct field type so the *dispatch* read is a u16 but the *case-3* read is a u16 through a `u16 *` cast that cse treats as a different mode... no, same mode.

What about making the case-3 read go through `sv[idx]`... no, that's the table.

Hmm, what if the case-3 index read is `idx` (the local) but the target's reload is of `p->unkA`... The target reloads the memory. If I write `mask = tbl[idx];` then cse uses the register → no reload → but the target has a reload. So no.

OK, let me also quickly test whether the *dispatch* can be u16 while case 3 gets a reload via the `p[0x4E]` store being placed on the else path. E.g.:

```
} else {
    idx = p->unkA;
    dsp = sv[idx];
    p[0x4E] = p[0x4E];        // real self-store on the else path -> invalidates
    switch (dsp) { ... }
}
```
That's c4-like (self-store) = 14/344 (one extra sb). No.

Alright: WALL best 1, tag cse-load-forward.

Hmm, but hold on: is c1's residual really "cse forwards a loaded value the target reloads"? c1's residual is the load *width*, i.e. the u8 trick. The underlying wall is: without the memory clobber, cse folds the case-3 index load (the target reloads). The u8 trick breaks the fold but changes the dispatch load's width. So the wall tag `cse-load-forward` fits.

Let me record item 2 and move on. Actually, let me first try 2-3 more variants with fresh ideas since I have time:

n1: dispatch `idx = ((Unkstruct_80030CA4 *)p)->unkA;` and case 3 `mask = tbl[((Unkstruct_80030CA4 *)(p + 0))->unkA];` — same.
n2: dispatch reads idx via the biv: `idx = *(u16 *)(sv - 0x576 + 0xA);` hmm, sv - 0x576 = p. cse relates → folds.
n3: Make `idx` volatile? `volatile u16 idx;` — a volatile local! `idx = p->unkA;` then `dsp = sv[idx];` — the local's storage is volatile → loads/stores of idx can't be optimized, but idx would live on the stack (frame change). Bad.
n4: `dsp = sv[(u16)((Unkstruct_80030CA4 *)p)->unkA];` same.

Let me just try n2 and n4 quickly (2 more tries → 32).

Actually, let me try something smarter: what if the *case 3* read uses `p[0xA]` and `p[0xB]`... no.

I'll do n2, n4, and one more: n5 = c1 with the dispatch reading `*(u16 *)(p + 0xA)` and the case-3 read `*(u8 *)(p + 0xA)` — no.

Let me just record. Time is fine but the wall is well-evidenced (and the header documents it).

Actually, let me do 2 more cheap tries to be thorough, then record.
