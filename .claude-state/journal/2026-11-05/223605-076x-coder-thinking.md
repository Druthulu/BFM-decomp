---
ts: 2026-11-06T05:36:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zO1xBmIm9P9pvkamz429
---
All 8. I'm at ~32 tries for item 2 (n1, a1-a4, b1-b4, d1-d6, e1,e2,e3,e5, h1-h5, k2(failed), k4,k5, l1,l2,l3 = 1+4+4+6+4+5+2+3 = 29... plus d1 recheck. Let me count precisely:
- n1 (1)
- a1,a2,a3,a4 (4) =5
- b1,b2,b3,b4 (4) =9
- d1,d2,d3,d4,d5,d6 (6) =15
- e1,e2,e3,e5 (4) =19
- h1,h2,h3,h4,h5 (5) =24
- k4,k5 (2) =26
- l1,l2,l3 (3) =29
- orig baseline (not a try)
Plus I re-scored some (d2, b1). Hmm, 29 scored lever-free tries. I need ≥30. Let me do 2 more distinct tries, then WALL.

Actually, let me use my remaining effort more wisely: let me try the "iVar1 gets more refs" idea concretely with a foldable extra use. 

Idea: `tmp = iVar2 + (iVar1 != 0) - (iVar1 != 0);`? That's real code (comparisons + arithmetic) → extra instructions.

Idea: make the two arms share a `iVar1` use before the branch... e.g., `((Unkstruct_800B5CB8 *)iVar1)->unk10 = 0;` before the branch? That's a store (extra).

Hmm.

OK, what about the *opposite* approach: make iVar2's qty *smaller* by loading it into a variable that dies quickly, and compute tmp from a *second* load? Extra lh.

I'll do 2 more tries: 
m1: `iVar2` declared `s32`, `tmp` `s32`, copy `tmp = iVar2;`, and the *second test* uses `tmp` while the *first* uses iVar2 (h4 was `if (tmp < 0)` → 8).
m2: the copy as `tmp = iVar2;` where tmp is declared inside the if block (scope) — might change qty numbering.

Actually, block scope could change the qty numbering (regno). If tmp is declared inside the if block, it might get a different regno — but the priority dominates.

Let me try m2 and m3 (declare iVar1 after tmp in the decl list, i.e., tmp first). h5 did the decl order swap → 8.

Let me try:
m2: tmp declared inside the if block:
```c
if (iVar2 != 0) {
    s32 tmp = iVar2;
```
Hmm, C89 requires declarations at block start — that's fine inside the if block. But then both blocks need their own tmp (the second block too).

m3: `iVar1` declared as the last variable (after pad).

Let me run these 2 and then record the WALL with best 8.

Actually, let me reconsider ONE more time whether the WALL is right. The evidence: a1/h1 keep the copy but swap iVar1/iVar2. The pin is load-bearing: it reserves $3. Lever-free, the s16 test value (iVar2, pri 9.6-12) outranks the pointer (iVar1, pri 5.33). This is exactly the "lreg-qty-order" class. 

Hmm, but the brief says "WALL (best = lowest score of a lever-free body)" and wall = a tag from walls.txt or a new `<pass>-<what>`. "lreg-qty-order" is a new tag (not in walls.txt). Evidence: "local-alloc qty: iVar2 (8 refs/10 insns, pri 9.6) outranks iVar1 (8/18, pri 5.3) for $3; the pin reserved it; best 8".

Actually wait, walls.txt has "lreg-v0-local-first", "lreg-qty-priority", "lreg-qty-order"? Let me check: walls.txt tags include:
- lreg-tie-dying-pin
- lreg-v0-local-first
- lreg-qty-priority
- lreg-slt-tie
- local-alloc-const-qty
- lreg-qty-order (from moves.md line 143: "WALL lreg-qty-order" — but is it in walls.txt? The walls.txt list I saw doesn't include "lreg-qty-order". The brief says a tag from walls.txt or a new `<pass>-<what>`. moves.md uses lreg-qty-order but walls.txt doesn't list it. Hmm, walls.txt is the canonical list; "lreg-qty-order" is not there. I'll use a new tag "lreg-qty-order" as `<pass>-<what>` (pass=lreg? The format is <pass>-<what>, lowercase). Maybe "local-alloc-qty-priority". Let me use "lreg-qty-order" since moves.md precedent exists (line 143 uses it). But the brief says "a tag from .run/P40/T11/walls.txt or a new <pass>-<what>". So a new tag is fine; I'll define it in the evidence.

Before finalizing, let me do the 2 extra tries.

Hmm, actually, let me try something I haven't: what if we make the *copy* be a real instruction by using a `s16` *pointer* read? No.

One more idea worth trying: **make iVar1's live range shorter by moving the second block's `iVar1 = ...unk20` reload INTO the first block's end**? It's already right after the if.

Actually — here's a thought: what if the *reload* is what makes iVar1's live range 18? The reload is a new def. The first iVar1's live range is from insn 21 to the last use in the arms. If we could make the last use earlier... the else arm's store.

What if the two arms are ordered so the then-arm's store is the last? No, the else arm is last in layout.

OK, let me do the final 2 tries and record.
