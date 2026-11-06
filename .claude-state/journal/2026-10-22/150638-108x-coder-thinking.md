---
ts: 2026-10-22T21:06:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tKltk9ZYCbpbEFjD7zRK
---
Still the ax/by swap. f1 (source by, bx, ax) got by first; the others (by, ax, ...) get ax first.

So the sched1 tie-break between by and ax favors ax when the source has by before ax and bx's re-set after ax. In f1 (by, bx, ax), by came first.

What if the source is (by, ax, bx) but with something between by and ax that changes the priority? E.g., a store between them:
```
by = bx - 0x5D;
prim.y0 = by;     // store by immediately
ax = ay + 0x7B;
bx = bx - 0x57;
prim.x0 = ay + 0x75; ...
```
But the store order in the target is x0 first, so prim.y0 can't be stored before prim.x0.

What about an unrelated statement between by and ax, e.g. `prim.attr = 0;`? That's before. Or move `prim.r = white; prim.g = 0; prim.b = 0;` between by and ax? Those stores (sb) come earlier in the target (1514-151c) — they're already scheduled before the adds.

Hmm, what if I move the `prim.attr = 0;` statement between by and ax in the source? sched1 would schedule it earlier anyway (it's independent).

Let me think about the tie-break: sched1's `rank_for_schedule` in gcc 2.7 compares:
1. priority
2. ... `INSN_UID`? Actually in gcc 2.7's sched.c, rank_for_schedule compares:
   - `priority` (INSN_PRIORITY)
   - `tie_breaker` = ...
   - the insn's "birth" (INSN_LUID?)
   
The log's ready list for equal priorities is sorted by... the "now" list order. In the T-115 line: `now 161 165 208 ...` — 161 before 165. But the final order has 165 before 161! So the ready-list order isn't the launch order, or the launch at T-115 was 161 and at T-116 was 165, meaning 161 was launched first — but the dump shows 165 first. Contradiction. Unless the .sched dump prints the insns in the *original* order (not the scheduled order) — the insn chain fields (insn 165 149 161) are the *post-scheduling* links, which show 165 before 161.

Hmm, maybe the .sched dump is printed before scheduling (the pass prints its input, then schedules)? The dump's format `(insn 165 149 161 ...)` is the linked list at the time of printing. If printed before scheduling, the order is the original RTL order — but the original .rtl dump had -93 (by) at 8006 before 123 (ax) at 8019, i.e., by (161) before ax (165). In the .sched dump, 165 comes before 161 → so it IS post-scheduling (or the list was reordered).

So sched1 did put ax (165) before by (161), contradicting the log's "now 161 165". 

Maybe the log's T numbers are the *reverse*: T-115 is later than T-116 (the log counts down to the end). Then at T-116 the ready list has 165 first → 165 launched; at T-115 (earlier) 161 was in the list. No...

Let me not fight this. Empirical: (by, bx, ax) → by first. So put ax after bx in the source AND get ax before bx in the output... contradiction.

Wait — f1's residual: by at 72 correct, ax at 74 (bx at 73). Target: by 72, ax 73, bx 74. So I need to swap ax and bx in the output while keeping by first.

f1's source: by, bx, ax. sched1 preserved that. So sched1 preserved the source order in f1. Then to get by, ax, bx I need the source (by, ax, bx) — which sched1 reorders to (ax, by, bx).

Why does sched1 reorder (by, ax, bx) but preserve (by, bx, ax)? Maybe because of the anti-dependency: in (by, ax, bx), by must precede bx (anti-dep), and ax is between them. Sched1 might see ax as "free" and schedule it first, then by, then bx. In (by, bx, ax), the anti-dep chain by→bx is adjacent, so sched1 keeps them together.

What if the source is (by, ax, bx) with the ax statement *after* bx but written to look... no.

What if I add a third independent add between? no.

What if I make `ax`'s add depend on the bx load (not just ay)? e.g. `ax = ay + 0x7B;` unchanged... I could write `ax = ay + 0x7B + (bx & 0);`? folded.

Hmm, what about making the *bx re-set* not an anti-dependency: `bx = out.vy - 0x57;` (h1) — still ax first.

What if `by` is computed from the load *before* the ay load (h2) — still ax first.

What if the source order is (by, ax) with bx's re-set *before* by? Impossible semantically.

What if I use a different variable for the bx re-set (e.g., compute the new bx into a temp and store it in the prim directly)? The prim.y1 = bx must be the new value. If I write `prim.y1 = bx - 0x57;` and `prim.y0 = by;`... then bx isn't updated in place; the target's s2 = bx - 0x57 (in place). Let me check: target 1528 `addiu s2,s2,-87` — in place. If the source wrote `prim.y1 = bx - 0x57`, gcc might still use s2 in place (same register) if bx is dead after. But bx is used later (the second block's prim.y1 = bx — the new value). So bx must hold the new value.

Hmm, what if the second block uses `bx` (new) and I write:
```
bx = out.vy;
ay = out.vx;
by = bx - 0x5D;
ax = ay + 0x7B;
prim.x0 = ay + 0x75; prim.y0 = by; prim.x1 = ax; prim.y1 = bx - 0x57;
bx = bx - 0x57;
```
That duplicates the add (cse merges).

I'm at 15:12 (22 min on item 3). Let me try a couple of final ideas and then decide: score 2 is a WALL (best = 2) unless I crack it.

Final ideas:
i1: source (by, ax, bx) with the bx re-set written as `bx -= 0x57;` (same).
i2: move the ay load between by and ax but keep bx's re-set at the end: (bx load, by, ay load, ax, bx re-set) = f2 = 2 (ax first).
i3: put the `prim.r/g/b` stores between by and ax.
i4: make ax's add use a *new* variable: `s16 t = ay + 0x7B; ax = t;` — a copy might change sched1's priority (the add's result feeds a copy). Then the copy could be coalesced. Let me test i4.

i4 is plausible: the add's consumer becomes a move, which sched1 might prioritize differently. Let me try i4 and i5 (by via a temp too).
