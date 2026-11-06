---
ts: 2026-10-22T20:46:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R7BvPjqE4dMvsFUZFW0p
---
Confirmed: src def = 0, best lever-free = 4.

Time: 14:45; item started 14:36 → 9 min so far. I need ≥20 min for a WALL. Let me use the time productively: try a few more genuinely different ideas.

Idea: The fold happens because `it` is dead. What if I make the else branch's `it` live by *reordering* the blocks so the copy block is reached from the else block? The semantics: the copy path means "found a zero at the scan pointer". If I restructure the loop so that the scan pointer variable is `it` and the copy block is inside the loop body:

```
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) { p = it; goto found; }
    it += 0x10C;
    if (it != p) goto body;
```
That's semantically identical and simpler! Does it produce the same code? The target has the copy block as a separate block with `j found` and `move a1,v1` in the delay slot; the inline version would do `beqz v0, found` with `move a1,v1` in the delay slot — actually the target's `beqz v0,465c` (to copy) then copy jumps to found. Inlining would give `beqz v0, found` with `move a1,v1` in the delay slot — one fewer jump. The target has two jumps (465c j 4694). Hmm, but the target's copy block exists as a separate block, suggesting the source has a label (goto). So inlining changes the code (removes a jump) → score higher.

But wait — maybe this restructure makes `it` live? No: `it` in the loop is the reassigned one.

Idea: Make `it` live by using it in the else branch *after* the add in a way that matches the target: the target's `copy: p = it` — if the source wrote `copy: p = it;` and the compiler's CFG had a path from the else block to copy (fallthrough), then it would be live. The target's code shows the else block's jump goes to test, not copy. So no.

Idea: What if the source computes `p = it + 0x658C` with `it` being the *loop's* it (i.e., the add happens after the reassignment)? No.

Idea: Use a `register` declaration for `it`: `register s32 it;` — gcc might keep it in a register and not fold? cse still folds constants. But let me test it — cheap.

Idea: `s32 it = (s32)D_80120194;` declared with an initializer inside the else block, and the add right after. Test.

Idea: make `it` an `s32` but assign via `it = (s32)D_80120194;` where D_80120194 is accessed via a *different type*: e.g. `(s32)(u8 *)D_80120194` — same.

Idea: The fold might be prevented if the add's result `p` is used in a way that requires the base... no.

Idea: Use `it += 0x658C; p = it;`? Then it is reassigned (live?) — the value it+0x658C would be in it, and p = it. Then at test, it is reassigned. The target's register usage: p in a1, it in v1. If `it += K; p = it;`, gcc might emit `addiu v1,v1,K; move a1,v1` — target has `addiu a1,v1,K`. Different.

Idea: `p = it + 0x658C; it = p;`? Then it is live? no, reassigned.

Hmm, what about making the add *two uses* of it: `p = it + 0x658C; q = it;` where q is used later in a way that survives (e.g., q used in the found block?). The target doesn't have such a use.

I think we're done. Let me try the `register` and initializer variants (2 quick), then wall at 4.

Actually, let me reconsider the possibility that the target's C is the *if-branch style* for the else too, i.e.:
```
} else {
    s32 base = (s32)D_80120194;
    p = base + 0x658C;
    it = base;
    goto test;
```
Then base is live (used by it = base), so the add isn't folded! And it = base is a copy (move v1,v1 → coalesced away). Then test reassigns it. Let's see: the C would be:
```
else {
    s32 base = (s32)D_80120194;
    p = base + 0x658C;
    it = base;
    goto test;
```
gcc: base and it coalesce → same register v1; `addiu a1,v1,0x658C`; `it = base` is a no-op; then goto test. That gives EXACTLY the target's else block! And `base` is live because `it = base` uses it — a real use that survives coalescing? If they coalesce, `it = base` becomes a no-op move which gcc might delete... but the liveness for cse is computed before coalescing/flow. cse sees `p = base + K; it = base;` — base is used after the add → live → no fold! Then the move is coalesced/deleted later.

This is promising! Let me test:
```
} else {
    s32 base = (s32)D_80120194;
    it = base;
    p = base + 0x658C;
    goto test;
```
or the order p then it=base.

Actually, the simplest: `it = (s32)D_80120194; p = it + 0x658C;` — it dead. Add a second use of it that is a self-copy that gcc will eliminate: `p = it + K; it = it;`? A self-assignment might be removed at parse. `it = it + 0;`? folded to a move.

Use a second variable: `it = (s32)D_80120194; p = it + K; q = it;` where q is then used as... q must be used or flow deletes it. But flow runs after cse! cse sees `q = it` as a use → keeps it live → no fold. Then flow deletes the dead q assignment. That's gen_use2_dead (`q = it;` after the add) = score 4. Hmm, that was tried and gave 4. Why didn't it work? Maybe because cse's fold decision doesn't depend on liveness after all, or because `q = it` was deleted before cse (dead code elimination at expand?).

Hmm, gen_use2_dead = 4 means the fold still happened. So cse folded despite the use.

OK so the "live → no fold" theory fails for the else branch but holds for the if branch (base live in the loop). What's different? In the if branch, base is used in a *loop* after the add — the use is in a different BB and the value must be in a register. In gen_use2_dead, `q = it` is right after, in the same BB, and gets deleted before cse? gcc's cse1 runs after "flow" analysis? Order: expand → jump → cse1 → ... Actually dead code elimination (`delete_dead_insns`) runs after cse1? Hmm.

Let me test the `it = base` variant where the second use is *in a different block* — e.g. the copy path:
```
else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    p = it;
    goto found;
test:
    it = (s32)D_801202A0;
```
No.

What if the second use is in the `test` block before the reassignment? `test: if (it == p) goto zero; it = (s32)D_801202A0; ...` — that changes semantics (compares the first it with p).

Hmm, actually maybe that's the real source! Let's think: what would `if (it == p) goto zero` mean with the first it? p = it + 0x658C ≠ it, so it's never equal... unless. Hmm, the target's `beq v1,a1` at 466c is after `v1 = D_801202A0`, so the comparison uses the second it. OK.

Let me just test a few "second use in a different block" variants:
- `it = (s32)D_80120194; p = it + K; if (it == p) goto zero; goto test;` — the compare is folded (it != p always? p = it+K, so not equal unless K=0) — gcc folds to false → deleted.
- `it = (s32)D_80120194; p = it + K; goto test;` with `test: if (it == p) goto zero; it = D_801202A0; ...` — compare the FIRST it with p in the test block, then reassign. Semantics: at test, it is the first value; p = it+K; if equal → zero (never). Then reassign it. This adds a compare (2 insns) but might keep it live across the add (in a different BB) → no fold. Then the extra compare would show as 2 extra insns... unless gcc deletes it (it knows it != p? p = it+K with K != 0 → the compare is always false → deleted by cse/combine!). If gcc folds the compare away, we get the target code!

That's worth a try: 
```
it = (s32)D_80120194;
p = it + 0x658C;
goto test;
copy: p = it; goto found;
test:
    if (it == p) goto zero;      // extra, always false (p = it + K)
    it = (s32)D_801202A0;
    if (it == p) goto zero;
    ...
```
Hmm, but the fold of the first compare requires knowing it's a constant... which is the same knowledge that folds the add. Circular: if cse knows it's constant, it folds the add too. If it doesn't, the compare survives.

So this would add insns. Unless cse folds the add but not the compare? Unlikely.

I'll stop. This item = WALL at 4 (cse-const-addr). But wait, I want to make sure I've satisfied the "≥30 tries" and "≥20 min". Prior gen_* = 35 scored candidates; mine = 20 scored. Time will be ~15 min by the time I finish. Hmm, the requirement is ≥20 min AND ≥30 tries for a WALL. Tries are satisfied (55). Minutes: started 14:36, now 14:47; I'll write notes and rows → ~14:52 = 16 min. Let me spend a few more minutes trying ideas to reach 20 min honestly.

Let me try the "second use in a different block" and a couple of structural variants, then wall.

Batch:
p1: `it = (s32)D_80120194; p = it + 0x658C; if (it == p) goto zero; goto test;`
p2: two variables: `s32 base = (s32)D_80120194; it = base; p = base + 0x658C; goto test;`
p3: `it = (s32)D_80120194; p = it + 0x658C; it = it;` (self-assign)
p4: `s32 base = (s32)D_80120194; p = base + 0x658C; it = base; goto test;`
p5: `it = (s32)D_80120194; p = it + 0x658C; base = it;` (base declared, used in the if branch? no, base is scoped to the if block). Declare base at the top? The if branch declares `s32 base` inside. I could declare a top-level `base` used in both branches... but then the if branch's code changes. Hmm, p5: declare `s32 base;` at the top and use it in the else; but the if branch has its own `s32 base` (shadowing) — legal C.

Let me test p1-p4.
