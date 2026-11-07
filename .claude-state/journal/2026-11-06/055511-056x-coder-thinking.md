---
ts: 2026-11-06T12:55:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yIa11OvBmb64piLDKEKY
---
One instruction differs: mine `lbu a0,0(s0)` vs target `lhu a0,0(s0)`. 

My c1 dispatch reads `*(u8 *)(p + 0xA)` — but the residual is at the *case 3* site? mine[55] lbu a0,0(s0) vs target lhu a0,0(s0). So the case-3 reload reads u8 instead of u16. Hmm — that means the case-3 read `tbl[((Unkstruct_80030CA4 *)p)->unkA]` used a u8 load?? 

Wait, `unkA` — what's its type in Unkstruct_80030CA4? Maybe `u8 unkA`? But the target's `lhu` suggests u16. Hmm, `idx` is u16 and `((Unkstruct_80030CA4 *)p)->unkA`... Let me check the struct.

Actually mine[55] is probably the dispatch load in case 2 (`func_8003D3B4(idx, 1)` where idx is u16). Hmm.

Let me just look: with c1 the dispatch is `idx = *(u8 *)(p+0xA)` so idx gets a byte → `lbu`. Then case 3's `tbl[p->unkA]` is a separate u16 read → `lhu`. The residual says mine has lbu at 55 where target has lhu.

So maybe the residual is in the *dispatch* path for the case-2/3 fold. Let me get more context: dump mine's insns 50-60.

Actually, simpler: try making the dispatch read a u16 at a *different* expression that cse still can't fold. Since c1's only diff is one load width at one site, maybe the u8 dispatch read propagated into a place where the target has u16.

Which site? mine[55] `lbu a0,0(s0)` — s0 is the biv p+0xA, and a0 is the func_8003D3B4 argument (case 2: `func_8003D3B4(idx, 1)`). In c1, idx was loaded as u8 → but idx is declared u16, so `idx = *(u8*)(p+0xA)` zero-extends into a u16. Then case 2 passes idx → the value in a0. Target's lhu.

Hmm, so the target's case-2 argument load is a u16 load at the case-2 site. In c1, the dispatch load became u8 and the case-2 use reuses it? mine has lbu a0,0(s0) — so it's reloading at the case-2 site as a byte.

So I need the dispatch read to be u8 (to break cse's fold for case 3) but case 2 to still read u16. Hmm, but the dispatch `idx` IS used in case 2.

Alternative: make the dispatch read a u16 but through a *different address spelling* that cse can't match, e.g. via a pointer that cse's table sees as a different alias. In cse, two addresses alias if their canonical forms are equal. `p + 0xA` and the struct field `((Unkstruct*)p)->unkA` — if unkA is at offset 0xA, they're identical.

What if the dispatch reads `*(u16 *)(p + 0xA)` (same address) — c2-style, which was 19 (folded). Hmm.

Wait, c1's dispatch read is `*(u8 *)(p + 0xA)` — a *byte* read at the same address. cse's memory table is keyed by address+mode? Apparently a byte read doesn't kill the u16 entry... but it did break the fold (score 1 vs 19). Interesting: cse stores entries by (mem, mode?) — a QImode entry at the address vs HImode. So case 3's u16 read missed the u8 entry → reload. 

Now the only residual: the case-2 arg load width. In the target, case 2's `func_8003D3B4(idx, 1)` uses `lhu a0,0(s0)` — a fresh u16 load at the case-2 site. In mine, the dispatch idx (u8-loaded) was reused, giving lbu.

Hmm, but why would mine reuse the u8 dispatch value as a u16 arg? Because idx is u16 and case 2 uses idx → same pseudo.

Hmm, actually maybe mine's `lbu a0,0(s0)` at 55 is the case-2 reload of idx as u16? No, lbu.

Let me look at the actual source: case 2 is `func_8003D3B4(idx, 1);`. `idx` is a u16 local assigned from the dispatch. So mine passes the dispatch value → but that value was loaded as a byte. gcc then... hmm, it emitted `lbu a0,0(s0)` which is a *reload* — meaning the dispatch value wasn't kept? 

Wait: in the dispatch block, `idx` is set and `dsp = sv[idx]`. Then case 2 uses idx → a0. If gcc reloads idx as `lbu` at the case-2 site, that's a re-materialization of the u8 load. Hmm.

Target: `lhu a0,0(s0)`. So target reloads idx as u16 at case 2. With the barrier, the dispatch's idx load was `lhu` (u16) and case 2 reuses it? The target at 55 has lhu a0,0(s0) which IS the dispatch load probably.

OK, so: I need the dispatch idx load to be u16 (`lhu`) AND the case-3 read to reload. c1 made the dispatch load u8 → the wrong width shows up.

Alternative: keep `idx = p->unkA` (u16) for the dispatch, and make the *case 3* read a different mode so cse misses it: e.g. case 3 reads `*(u8 *)(p + 0xA)`?? No, the target's case-3 reload is `lhu`.

Hmm, target case 3: `lhu v0,0(s0)`. So case 3 does a u16 load.

So both the dispatch and case 3 load u16 at the same address; the barrier makes cse forget. Without it, cse folds.

What if I make the dispatch read a u16 through a *different* base pointer variable whose address cse can't prove equal? E.g.:
```
u8 *p2 = p + 0xA;
idx = *(u16 *)p2;
...
case 3: mask = tbl[((Unkstruct_80030CA4 *)p)->unkA];
```
cse would still equate (p2 = p+0xA, canonicalized). 

Hmm, but what about the *mode* trick in reverse: dispatch reads u16 (correct width) at an address that's the same but via a *volatile* pointer... we saw volatile breaks the giv.

What about: dispatch `idx = p->unkA;` then a *byte* store somewhere that invalidates? A store to p[0x4E]... 

Actually — what about using `dsp = sv[idx];` where `sv` is declared `u8 *` but the *idx* is a u8 variable and the case-3 read uses the u16 field? c1 does that.

Alternatively: make the case-3 read use a different mode that still yields `lhu`: e.g. read through a `u16 *` pointer variable: `u16 *pidx = (u16 *)(p + 0xA);` at the top of the function? cse would canonicalize.

Hmm, what about making the dispatch load u16 but via a *struct field of a different struct type* at the same offset — cse doesn't care about types, only addresses.

OK, different approach: accept c1's score 1 and fix the case-2 width. In c1, the dispatch `idx` is loaded as u8. What if instead the dispatch keeps `idx = p->unkA` (u16) and I add a *separate* byte read to kill the cse entry? E.g.:
```
idx = ((Unkstruct_80030CA4 *)p)->unkA;
dsp = sv[idx];
dsp = dsp;  // no
```
A byte read that's used: e.g. `if (*(u8 *)(p + 0xA) == 0xFF) ...` — changes semantics.

Hmm what about:
```
idx = p->unkA;
dsp = sv[idx];
```
and in case 3:
```
mask = tbl[((Unkstruct_80030CA4 *)p)->unkA];
```
→ change to a *volatile* read only at case 3? That would add an insn (volatile u16 load = lhu? maybe fine!). Let me try: case 3 `mask = tbl[*(volatile u16 *)(p + 0xA)];` — a volatile u16 load = lhu, and it forces the reload. Does the volatile load break the giv? The header said the volatile *index* load at the dispatch breaks the giv (address stays biv-based). Here the case-3 site is inside the loop too... the address `p + 0xA` is the biv s0 (p+0xA is the giv). A volatile mem can't join a giv group → the load would be `lhu 10(s2)` instead of `0(s0)`.

Hmm. That's what a4 showed.

So: I need a non-volatile u16 load at case 3 that cse doesn't fold. The barrier does it. c1's u8 trick broke the fold but at the wrong site.

Wait — maybe I misread which site is 55. Let me dump c1's insns 45-60 and identify.

Let me do that.
