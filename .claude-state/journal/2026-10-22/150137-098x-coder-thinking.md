---
ts: 2026-10-22T21:01:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8LGY6Ofxyqc0hGmuRvdN
---
The initial RTL (expand) order is already: -93 (by) at 8006, 123 (ax) at 8019, -87 (bx) at 8024, 117 (ay) at 8078 — the source order (by, ax, bx, ay). And the target's final order is by, ax, bx, chain, ay.

So sched1 in mine moved ax before by and ay before the chain. In the target, sched1 preserved the source order. So it's a sched1 decision driven by the RTL details (priorities/ref counts).

The sched1 log: at T-115 161 (by) has the birth priority; 165 (ax) priority 4. Both priority 4. The birth boost applies to the insn whose operands just became available. In mine, by's operand (bx load, 152) is scheduled late (T-117?) — no wait, "launching 152 before 165 at T-117" means 152 is launched at T-117, after 165 (T-116). So the bx load (152) was scheduled AFTER ax (165) and after by (161)?? That can't be — 161 depends on 152.

I'm misreading the log. The "ready list at T-n" lines show the state *before* the launch at that cycle, and the launch decision line names the insn launched. Ugh.

Let me stop analyzing. The practical question: can the C change the schedule? The prior coder's 36 variants and my 24 all land at 4. The mechanism is sched1's reordering of independent adds; the target's order matches the source order, so the target's sched1 had no reason to swap — perhaps because the target's *register pressure/assignment* differs (sched1 runs before local-alloc though).

Hmm, one thing: sched1 runs BEFORE local-alloc. The priorities depend on the insn lengths and dependencies only. In mine, insn 161 (by) writes s4 (a pinned hard reg!) while 165 (ax) writes a pseudo. Wait — the pin makes by's set target the hard reg $20 directly. In the RTL dump: `(set (reg/v:SI 20 s4) (plus ...))`. And ax: `(set (reg/v:SI 74) ...)`. Sched1's priority might treat hard-reg sets differently? Both priority 4.

The target also has by in s4 (pinned in the src def). So same.

OK. Wall at 4 ORDER.

Hmm, but before walling, let me try one more idea: the `ref_count` differs (161 ref_count 3, 165 ref_count 3). The birth boost...

What if I add a *second use* of `by` earlier so its priority rises? E.g., use by in the prim stores of the second block? The second block's prim.y0 = by uses it (already). So by has 2 uses (both stores) → ref_count 3.

What if I compute `by` via `out.vy` instead of `bx` (u4 = 34)? no.

What about making `ax`'s add depend on `bx`'s re-set? No.

Let me try the reverse of the birth boost: make the ay load later so ax's birth is later. v3 moved the ay load after by's add (still 4). What if the ay load moves after bx's add (v4-like)? v4 = 4.

I'm done. Wall at 4, tag sched1-birth-order.

Wait, actually — one more idea: the residual's `insert at 72` suggests the target has one MORE insn at position 72 and mine one fewer, but the total is equal (207 both), so it's a pure permutation. The diff tool reports insert/delete pairs.

Since all my variants produce the identical residual, the sched1 decision is robust to source order (because the RTL's dependency graph is the same). To change it, I'd need to change the dependency structure — e.g., make `bx`'s load later/earlier in a way that changes the birth order. The birth order is determined by the loads' schedule: the ay load (155) vs the bx load (152). The target schedules the bx load first (14fc) then ay (1500) — source order. Mine schedules ay first? Let me check mine's disasm: 14fc lhu s2? In the disasm I printed earlier: `1500: lhu s1,24(sp)` and 14fc? Let me check: the gen_o3 disasm showed at line 78 `1500: lhu s1,24(sp)` — and the line before (not shown) would be 14fc lhu s2,26(sp). Both match the target.

So the loads are in the same order; only the adds are swapped.

Hmm, what if the adds' order is driven by the *s4 pin*: in the RTL, by's set is `(set (reg/v:SI 20 s4) ...)` — a hard reg. Sched1's `priority` might add a bonus for insns that set a hard register? Both are priority 4.

What if I drop the by pin (y4 = 4 ORDER)? Same.

So sched1 consistently puts ax first. The target's source must have had something different — maybe the target's `ax` was computed *after* the bx re-set (i.e., `ax = ay + 0x7B;` later in the source), which would change the uid order and thus the tie-break. v4/v6 tried moving ax later → still 4. Hmm, but v4/v6's residual — I checked v3 and y4, not v4/v6. Let me check v6's diff: v6 has ax after by in source (`ay load, ax, by, bx`). Let me look at v6's diff to see if the residual changed.
