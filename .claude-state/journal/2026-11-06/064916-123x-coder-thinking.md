---
ts: 2026-11-06T13:49:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4ETYTNmegbArwTfvLZ8r
---
f2/f3 added insns (152) — the pkt group can't move (it's used by the stores). f1 = 6.

Best remains 2. Let me try one more idea: the `&&`/`||` fold from the catalog? Hmm.

Actually, let me reconsider. Maybe the A barrier's role is not only about the lbu but also the *prologue store* `sw s0,16(sp)`. In the target, the prologue `sw s0,16(sp)` is at index 6, between lw t5 and lw s0. Hmm.

Let me count the score-2 diff: only ONE insn displaced (lbu t6 or t7). The rest matches.

What if we make the last lbu's use appear earlier so its priority rises? The uses:
- ww used in `pkt->u1 = pkt->u0 + ww;`
- hh used in `pkt->v2 = pkt->v0 + hh;`
These are ~40 insns later.

What if we swap which variable is loaded last? Both sink one at a time.

Hmm, what if we add a *third* assignment to a param-loaded variable so the scheduler has more to fill with? No.

What if we make the D_800A5E60 load's delay slot filled by something else that the target also has there? In the target, after `lw t0,0(t0)` comes `lui v1` (D_800B9A02). That's the delay slot fill. So in the target, the lw's delay slot is filled by the D_800B9A02 lui. In mine, the lbu goes there and the D_800B9A02 lui shifts.

So the scheduler in mine chose the lbu (from before) to fill the lw delay; in the target the barrier prevented the lbu from moving, so it used the lui.

To prevent the lbu from moving down, the lbu must be "pinned" by a dependence on something after it... 

IDEA: make the lbu depend on an insn that's scheduled before the D_800A5E60 load but after the other lbu. Hmm.

IDEA: what if we swap the source order: put `pkt = D_800A5E60; D_800A5E60 += 0x28;` BEFORE `ww = w; hh = h;`? Tested (f2) → 152 ins, because... hmm why 152? The pkt group moved before the inits might duplicate something? Let me check: f2 moved the pkt group and removed it from its place. 152 ins = +4. That suggests the move created extra code (maybe the compiler couldn't coalesce). Never mind.

Let me try yet another angle: `s32 hh = h;` as a *statement expression* inside the pkt assignment? No.

OK, given the time (06:50, item5 ~8 min), let me make a decision: A is a WALL (sched1-load-delay-fill). But the item as a whole: can I report PARTIAL? The result types: MATCH (win.c scores 0), PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers), WALL (best = lowest score of a lever-free body). Since A's barrier must remain to score 0, the best lever-free body is 2 → WALL.

Hmm wait, but PARTIAL is for when win.c scores 0 while keeping SOME levers of the row kinds. E.g., if a body scores 0 with 1 of the 3 barriers kept, that's PARTIAL:barrier (kept one barrier). The expert diffs orig→win: a win.c that keeps some barriers but not others, and scores 0, would be PARTIAL:barrier.

Do I have a body that scores 0 keeping A only? Yes: w_d_base = B,C fixed (do-while), A barrier kept → score 0. That's PARTIAL:barrier! It keeps one barrier (A) and scores 0.

The definition: "PARTIAL:<kept> (win.c scores 0 keeping only those levers)" and "PARTIAL:<kept> means every row kind not in <kept> is gone from win.c". So PARTIAL:barrier with win.c scoring 0 and keeping one barrier is legitimate — but it's better to try harder for a full MATCH.

Also the PARTIAL example in moves.md: "PARTIAL:keepalive greg-pri-refs — barrier: y store per branch (win.c 0, keeps keepalive+pins)". So yes, a body scoring 0 that keeps one of the levers is a PARTIAL.

But a MATCH is better. Let me spend a few more minutes on A.

New idea: the `lbu` loads are from the stack. What if we make the D_800A5E60 load and the lbu's ordered by *reusing the same register*? E.g., if the D_800A5E60 load's destination pseudo is the same as hh's? No.

New idea: what if hh's assignment is `hh = h;` and then hh is used in the very next statement in a way that's part of the target code? The next statement is the pkt group. No.

New idea: `s32 hh = h;` at declaration (f1=6, worse).

New idea: assign hh via a pointer: `hh = *(u8 *)((char *)&h);`? same load, maybe different RTL (a different MEM expression?) — the address would be a different expression (fp+48 vs the param's pseudo). Hmm, `h` is a parameter; `&h` might force a stack slot. The target loads 48(sp). If we write `hh = *(u8 *)((u8 *)&h + 0);` gcc may compute &h = fp+48 → same lbu. Might change scheduling. Worth one try.

New idea: make hh's value used by the *pkt pointer* computation in a way that folds: `pkt = (FT4_801857A4 *)(D_800A5E60 + (hh * 0));` — fold removes. But maybe fold at tree level doesn't remove `hh * 0` if it thinks hh might be... no, x*0 → 0 always (unsigned/signed, no overflow issue; side effects none).

New idea: use `&&`: `pkt = (FT4_801857A4 *)(D_800A5E60 + ((hh && 0) ? 1 : 0));` folds.

Hmm.

New idea: make the D_800A5E60 load part of a longer chain: `D_800A5E60 += 0x28; pkt = (FT4_801857A4 *)(D_800A5E60 - 0x28);` — this changes the code order: load, add, store, then subtract for pkt (extra addiu). No.

New idea: the target's lbu t6/t7 are both before the lui t0. What if we make the two lbu's part of a *single* statement so they're born together? e.g.:
```
ww = w;
hh = h;
```
→
```
ww = w, hh = h;
```
Same RTL.

What if the source used `ww = h; hh = w;` (swapped) then the values would be wrong. No.

OK, let me also try: move the `ot = ...` line between the lbu's and the pkt lines? The ot line is after pkt (it uses D_800A6610). Hmm, `ot` doesn't depend on pkt. Moving ot before pkt:
```
    ww = w;
    hh = h;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    pkt = (FT4_801857A4 *)D_800A5E60;
    D_800A5E60 += 0x28;
```
The target order: lbu t6, lbu t7, lui t0(D_800A5E60), lw t0, lui v1(D_800B9A02), lhu v1, addiu v0(t0+40), lui at, sw, li v0,9, sb... So the target has the D_800A5E60 load first, then D_800B9A02. Moving ot before pkt would change that.

Hmm.

What about the statement order WITHIN the group: the target's param loads order is cy, tp, zoff, w, h — while the source order is cy, zoff, tp, w, h. The scheduler reordered zoff/tp. That's fine.

Let me try one thing: `hh = h;` placed between `tpp = tp;` and `ww = w;` (e6 = 2). And after ww (current) = 2.

I think A is a genuine sched1-load-delay-fill wall. Let me do a couple more (the &h form and a do-while around the pkt group on top of B,C fixed) and then settle.

Actually, let me try the "do-while around the pkt group" on top of B,C fixed (with A removed): earlier v5 (A-only) gave 8 with 150 ins. With B,C fixed? Let me test a few placements:
- g1: do { pkt = ...; D_800A5E60 += 0x28; } while (0)
- g2: do { ot = ...; } while (0)
- g3: do { *((u8*)pkt+3) = 9; } while (0)

Let me run these three plus the &h form.
