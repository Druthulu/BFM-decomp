---
ts: 2026-11-06T11:48:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NwCZziIRFjq1srYLsRvm
---
Score 6: only the vx/vy register assignment differs. Target: vx in a0, vy in v1. Mine: vx in s1 (shared with x), vy in s2 (shared with y) for the first stores, and v1 = s1 (a copy of x) for the later 0x18 use.

Wait: mine[54] move v1,s1 — that's a copy of x for the later use; target[55] move v1,s2 = copy of y (vy). So target: vx=a0 (copy of x), vy=v1 (copy of y). Mine: vx=s1 (x itself, first store), later a copy v1 = s1 for 0x18; vy=s2 (y itself).

So in mine, the compiler used x and y directly for the early stores and made one copy of x (v1) for the post-add use. In target, both copies are made up front: a0 = x (vx), v1 = y (vy).

Interesting: in mine, v1 is used at 0x18 (sh v1,24) and s2 for vy at 0x12/0x1A? Hmm.

The difference: which variable gets a copy. Target copies both; mine copies only x (into v1) and uses s2 (y) for vy.

Why? Because vx = x and vy = y are declared as variables; local-alloc coalesces vx with x (they're copies, same value, non-overlapping? no, overlapping). Actually with barriers, the copies are "born" at the barrier: vx = x before the barrier; the asm barrier makes x's value fixed.

Hmm, the launder `__asm__("" : "=r"(x) : "0"(x))` creates a new pseudo for x after the barrier. Without it, x's pseudo flows through.

Now, the residual is a register assignment: vx->a0, vy->v1 in target. Since these are caller-saved regs and there are no calls after, local-alloc would pick... hmm.

What real C move forces vx and vy into their own registers? Making their live ranges overlap x/y's more: e.g., if vx were used at 0x18 BEFORE x is modified — no.

Alternatively: make vx and vy be used in the *same* statements as x/y? They are.

Idea: what if we swap the roles: instead of `vx = x; vy = y;` early, compute the later stores from vx/vy and the early ones from x/y directly. Already so.

Hmm, score 6 is close but the residual is 6 COUNT.

Since a PARTIAL requires score 0 keeping only some kinds, p1 is 6 not 0. So PARTIAL isn't achieved yet.

But maybe I can crack the last 6 with real-C moves on top of p1! The barrier stays (allowed as PARTIAL:barrier). Real C moves on the vx/vy copy handling:

1. Declare vx/vy as u16? They're stored to s16 fields; x,y are s32. `s16 vx = x;` would introduce truncation insns. No.
2. Assign vx = x and vy = y at different places.
3. Use a temp for the first stores: `*(s16*)(p+8) = x;` directly and later `*(s16*)(p+0x18) = vx;`. Hmm, target stores vx at both 0x8 and 0x18.
4. Reorder: `vy = y;` before `vx = x;`? Source order: vx=x at 2453, p[7] at 2454, barrier, vy=y. If I move vy=y before vx=x, the copies' birth order changes → local-alloc order changes. Try it!
5. Make vx/vy declarations s32 but use them in a way that prevents coalescing: e.g., assign `vx = x + 0;`? no.

Let me try a small sweep on top of p1 (barriers kept, launders gone):
- a: swap vy=y before vx=x (and adjust the barrier position accordingly: the barrier is between p[7] and vy=y in orig; if I move vy=y up, the barrier goes after both).
- b: move `vx = x` after the barrier.
- c: move both copies after the c stores.
- d: declare vx,vy as separate decls in different order.
- e: replace `vx = x` with `vx = x; vy = y;` adjacent (barrier moved after them).
- f: remove the barrier at line 34 (between vx/vy stores and tag2) — no, keep barriers.

Actually careful: the item's kinds are barrier,launder. For PARTIAL:barrier, win.c must keep at least the barrier kind (all 4 barriers). Any real-C change is fine.

Let me generate ~12 variants of p1 and score. Also consider moving the two launders' effect via "real 2nd set" tricks: e.g. `x = x + 0` no.

The launders were: after vy=y, launder x and y. Their purpose: force x and y into registers at that point? Actually `__asm__("" : "=r"(x) : "0"(x))` ties x to itself in a register; it's a launder to stop cse/regalloc from coalescing x with vx? Hmm: since vx = x and vy = y are copies, without the launder local-alloc coalesces vx with x (same reg) and vy with y. The launder creates a new pseudo for x, so vx (=old x) and x (new pseudo) can't coalesce? No, coalescing happens on copies... Actually the launder kills the copy relationship.

So to prevent coalescing lever-free: make vx and x's live ranges overlap at a point where they must differ. If vx's live range extends past the point where x is modified, they can't share. Currently vx is used at 0x8 (before x += w_) and 0x18 (after). x is modified at x += w_. So vx and x DO overlap... but the compiler scheduled the first store before the add, so the interval split allowed sharing for the early part.

Target: vx gets a0 (separate). Mine: vx coalesced with s1 for the early part, and a copy v1 for later (so the variable is split).

The "split live range" happens at sched2/local-alloc... Actually local-alloc works on the RTL after sched1? sched1 runs before local-alloc, so scheduling determines live ranges. In p1, sched1 (with barriers) put the add... let me see: mine[67] sh s1,8 before the add, so the split.

Hmm, target: with the launders, x becomes a new pseudo after the barrier, so vx (old x) is live until 0x18 and new x is born at the launder; the copy vx = old x can't coalesce with new x. 

Lever-free equivalent: make the add use a *different* pseudo than x's first use... e.g.:

```
vx = x;
vy = y;
...
x += w_;
```
Here x is modified in place. What if we use a temp for the sum instead: 
```
s32 x2 = x + w_;
*(s16*)(p+0x10) = x2;
...
*(s16*)(p+0x20) = x2;
```
Then x's live range ends at `vx = x`? No, vx uses x... x is read by the add x2 = x + w_ and by vx = x (already copied). x's last use is in x2 = x + w_. vx's live range: from vx = x to 0x18. They overlap in [vx=x, x2=x+w_]. Still overlapping.

But wait, mine already keeps vx in s1 = x for the first store (67) which is before the add. So the interval from vx=x to sh 8 overlaps x's... yes but coalescing can still merge them if vx is a copy (register allocator can coalesce copies even with overlap? No — coalescing is only for non-conflicting).

Hmm, actually if vx = x is a copy and vx is live across x's modification, they conflict, so they can't share. But mine shows sh s1,8 (vx from s1) then later v1 = s1 (copy). That means the compiler *split* the copy: it used x directly for the first store and inserted a new copy for the later use. That's the "copy propagation" (flow/cse) eliminating the vx copy and rematerializing later. This happens before sched1.

So the lever to prevent that: make vx's value not equal x? No.

What about making the second use of vx (at 0x18) appear BEFORE the modification in source? It already does: source order is vx=x; ...; sh 8=vx; sh 0x18=vx; then x += w_ comes after! Wait, source:
```
*(s16 *)(p + 8) = vx;
*(s16 *)(p + 0xA) = vy;
[barrier]
tag2 = *(u32 *)p;
x += w_;
*(s16 *)(p + 0x10) = x;
*(s16 *)(p + 0x12) = vy;
*(s16 *)(p + 0x18) = vx;
y += h_;
```
Yes! The 0x18 use of vx comes AFTER x += w_. So vx must survive across the add.

But the compiler decided to use x itself for the first store (sh s1,8) and a fresh copy v1=s1 for the 0x18 use. That's equivalent since vx == x at both points... but no: at 0x18, x has been modified (x += w_), so vx != x. So it can't use x at 0x18; it made a copy at the barrier point (move v1,s1 at 54). Fine, that's the v1 copy.

Target instead copies vx up front (move a0,s1 at 53) and uses a0 at both 0x8 and 0x18, and copies vy (move v1,s2) for 0xA/0x12/0x1A.

So target = both copies made explicitly; mine = x and y used directly for the early stores, and one copy of x made at the barrier.

Why does target copy y into v1 even though y is modified later (y += h_)? Same reason.

The difference is WHERE the copy is born: target at the barrier (before the c stores), mine just before the use at 0x18 (sched1 sinking the copy to its use — the birthing boost!).

A real-C move to prevent the sinking: use vx/vy more times before the modification? Or make the copy have multiple uses earlier.

Hmm: in target, the copy `move a0,s1` is at 53, right after the barrier and before the c stores. In mine the copy `move v1,s1` is at 54 — same position! Wait, mine[54] move v1,s1 vs target[55] move v1,s2. And target has an extra `move a0,s1` at 53 (the insert). So target has TWO copies (a0=x, v1=y) and mine has ONE (v1=x).

Mine uses s1 (x) directly at sh 8 and s2 (y) directly at sh 10, sh 18. Target uses a0 (vx) at sh 8 and sh 24(0x18), and v1 (vy) at sh 10 and sh 18(0x12).

So target's vx is a0, vy is v1; mine's vx is effectively x(s1) for the early store, and v1 for 0x18; vy is y(s2).

If I could force vx and vy to be distinct pseudos from x/y... The compiler eliminated the copies because it can. In target, the launder created new pseudos for x and y after the barrier, so vx = old_x couldn't be coalesced with new_x — forcing the copy.

Lever-free equivalent: create a new pseudo for x/y after the barrier by a real computation. E.g., `x = x + 0`? folded. `x = x | 0`? folded. Hmm.

What if the add is written as `x = x + w_;` vs `x += w_`? Same.

What about using a different variable for the sum: 
```
s32 x2 = x + w_;
...
*(s16*)(p+0x10) = x2;
*(s16*)(p+0x20) = x2;
```
Then x is not modified at all; x's last use is in x2 = x + w_. vx = x. Since x dies there, and vx's live range ends at 0x18 which is before x2=x+w_? No: source order has sh 0x18 = vx before y += h_, and x2 = x + w_ is before the stores of x2. Hmm, order:

```
tag2 = *(u32 *)p;
x2 = x + w_;
*(s16*)(p+0x10) = x2;
*(s16*)(p+0x12) = vy;
*(s16*)(p+0x18) = vx;   <- vx use after x2's def
```
vx's live range [vx=x, sh 0x18] overlaps x2's def which reads x. So vx and x conflict (both live at the add). Thus coalescing vx with x is impossible → vx must get its own register (a0)! That's exactly the target shape!

And for y: y2 = y + h_; the use of vy at 0x12 comes before y2's def? Order: sh 0x12 = vy; ... ; y2 = y + h_ later. Hmm, vy's last use (0x1A) comes after y2 = y + h_. So vy and y conflict at the add too → vy gets its own reg (v1).

This looks very promising! The move: use explicit sum temporaries instead of modifying x/y in place. That's the C0505 "temps" move. I tried "direct" (x + w_ inline) but that makes cse compute the add once and the stores... Actually direct wrote `*(s16*)(p+0x10) = x + w_;` and `*(s16*)(p+0x20) = x + w_;` — the add is computed (probably sunk) but x isn't modified. Hmm, in the direct variant the add's position is at the first store; the vx use at 0x18 is after the add → conflict, so vx should get its own reg. But direct scored 75 (bad) with 121 insns — because it reordered things.

The difference: explicit temp `s32 x2 = x + w_;` declared/assigned at the right place. Let me try:

p3 (barriers kept, launders gone, explicit sum temps):
```
vx = x; ... vy = y; c stores; sh vx; sh vy;
BARRIER
tag2 = *p;
x2 = x + w_;
sh 0x10 = x2;
sh 0x12 = vy;
sh 0x18 = vx;
y2 = y + h_;
sh 0x1A = y2;
sh 0x20 = x2;
sh 0x22 = y2;
```
with `s32 x2, y2;` declared (or in a block).

But careful: the target computes `addu s1,s1,t1` (in-place x += w_) and uses s1 at 0x10 and 0x20. With x2, the add writes x2's pseudo; same instruction. Register allocation may differ but let's test.

Let me generate variants on p1 with:
- x2/y2 temps (block-scoped, decl at top, init at decl)
- with/without the barrier retained (keep barriers → PARTIAL if 0)
- also without barriers (MATCH if 0!) — since temps might fix the scheduling too.

Let me first test the temps WITH barriers (p1 base) — if 0, PARTIAL:barrier. Then also without barriers to try MATCH.

Let me write p3 and p4.
