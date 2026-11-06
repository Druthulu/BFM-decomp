---
ts: 2026-10-22T21:03:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xYQO9XNW2JShXj0VvE1U
---
The time is 15:02, not 15:20 (my estimates drift). Item 3: 14:50–15:02 = 12 min. Hmm, that's under 20 min for a WALL. The tries are 60 (≥30), but the time is 12 min this run plus the prior coder's 36 candidates (created at 07:13, so a prior session spent time on this item).

The rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item". I have ≥30 tries; the time on the item across both runs is certainly >20 min (the prior coder built 36 candidates for this item and 35 for the previous one at 07:13). But to be safe and honest, let me spend ~8 more minutes trying to crack item 3, since it's a pure ORDER diff — the most crackable of the three.

Let me think about the sched1 mechanism more concretely. From the log:
- The ready list at T-115: `165 (4) 208 (3) 204 (3) 149 (3) 147 (3) 145 (3) 142 (3) 161 (7f000001)` — hmm, this is the list *before* the T-115 launch, sorted; the launch at T-115 isn't shown in my excerpt. The next line T-116 shows `165 (4) ...` and 161 gone → so 161 was launched at T-115 (it was in the list with priority 7f000001). Wait, the T-115 line lists the ready list *after* the launch? The convention: "ready list at T-n: <list>, now <sorted list>" — the "now" is the sorted list used for the next cycle.

Line 10482: `ready list at T-115: 165 (4) 208 ... 161 (7f000001), now 161 165 208 ...`
Line 10483: `ready list at T-116: 165 (4) 208 ... now 165 208 ...`
So between T-115 and T-116, 161 was launched (it was first in the "now" list).

Hmm, but 161 depends on 152 (the bx load), and "launching 152 before 165 at T-117" says 152 is launched at T-117 — AFTER 161?! That's impossible unless the insn numbers in the launch line refer to something else.

I think I'm misreading the log; the T numbers may be cycle offsets and the list shows *future* availability. Not worth more time.

Practical approach: the target's order (by, ax, bx, chain, ay) vs mine (ax, by, bx, ay, chain). v4 gave (by, bx, ax, ay, chain). What if I can get (by, ax, bx) by moving the *bx re-set* after ax AND keeping by first? v4 = by, bx, ax (ax after bx). gen_o3 = ax, by, bx.

What if the source order is: `by; bx-reset; ax;` (v4) and I make the ay add later... The chain/ay issue is separate.

Let me try: source `bx=out.vy; ay=out.vx; by=bx-0x5D; bx=bx-0x57; ax=ay+0x7B;` (v4) but with the ay update moved after the op statement (x2-style) — maybe that fixes ay's position. And combinations.

Also try: `by = bx - 0x5D; ax = ay + 0x7B;` where the ax statement is *after* bx's reset but written as `ax = ay + 0x7B;` — that's v4.

Let me try 4 combos:
c1: v4 + ay update after the op assignment (op as a statement).
c2: v4 + prim stores split one per line.
c3: gen_o3 + op statement placed before ay (x1) — already 4.
c4: source: `bx=out.vy; ay=out.vx; by=bx-0x5D; ax=ay+0x7B; bx=out.vy-0x57;` (v5 = 4).

Hmm.

Alternative: maybe the ay/chain order can be fixed by making the chain's *first* insn depend on nothing new — it's the lhu D_800B9A02, already hoisted early. In the target the chain starts at 152c (right after bx at 1528) — i.e., the chain is scheduled immediately after bx, before ay. In mine, ay comes before the chain.

What if the ay add's *uid* is after the chain's insns (x2 did that: op assigned before ay → chain uids before ay) → still ay first (4). So sched1 moves ay ahead regardless.

What if ay's add has a longer latency or depends on something late? no.

What if I *remove* the ay in-place update and instead use `prim.x0 = ay + 0x75;` and `ay = prim.x0;` after the stores? The add would be at the store (like the target). w3 (prim.x0 = ay + 0x75; ay = prim.x0;) = 45 (bad, maybe an extra move). w5 (no ay update) = 22.

What if `prim.x0 = ay + 0x75;` and the second block uses `prim.x0`? i.e. `prim.x1 = prim.x0;` — that changes the code (a move).

Hmm.

Let me look at the target's second block to see whether ay's value there is s1 (updated) or something else. At 1574-1580: sh s0,36; sh s4,38; sh s1,40; sh s2,42. s1 = the updated ay. So ay is updated.

What if the target's source computed ay's update in the *second* block (ay = ay + 0x75 before the second store) and the first block used `prim.x0 = ay + 0x75`? Then s1 would be updated once... Let me check: in the target, is there another addiu s1,s1,117? Only one (153c). And the first store sh s1,36 uses the updated value. So the update is before the first store.

I'm at the wall. Let me do a final 5-minute batch (to reach ~20 min this run) with combos, then finalize regardless.

Actually, a thought: the difference might be caused by the *ax 2nd set* (`ax = (u16)ax;`). In the target, is there a 2nd set of ax? The target's second block stores sh s0,36 (ax) — no andi. The 2nd set exists in the C to kill ax's S2 boost (per the orig comment: "LEVER A: 2nd set kills ax's S2 boost"). In gen_o3 it's `ax = (u16)ax;`. Maybe a different spelling of the 2nd set changes sched1's priorities for ax (its ref_count). Let me try `ax = ax & 0xFFFF;` (gen_o2 tried with by), `ax = ax | 0;` (folded), `ax = (s16)ax;` (sign-extend → adds insns), `ax = (u16)(ax + 0);`.

gen_o2 had `by = by & 0xffff;` and no ax 2nd set? Let me check gen_o2's diff: it was gen_o3 + `by = by & 0xffff;` → so gen_o2 has the ax 2nd set too.

Let me try variants of the ax 2nd set:
d1: `ax = ax & 0xFFFF;`
d2: `ax = (u16)ax;` moved before the first GsSortLine (i.e., right after bx = bx - 0x57).
d3: no ax 2nd set at all (the launders gone; the 2nd set was for a scheduling boost).
d4: `ax = (u16)(ax | 0);`

d3 is interesting: without the 2nd set, ax is a single-set pseudo; the target's S2 boost... The orig had the launder on ax to kill the S2 boost. Without any 2nd set, the score may be worse (the S2 boost). Let me test.

Let me run d1-d4.
