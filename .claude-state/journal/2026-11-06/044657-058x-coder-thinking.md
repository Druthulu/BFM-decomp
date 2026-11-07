---
ts: 2026-11-06T11:46:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V0uHAzqpxTqrvfRs6uA6
---
All decl orders give 28 — no effect. So decl order isn't the lever for the otp/y swap here (local-alloc qty order is by ref count, not decl).

The residual: mine otp=s2, target otp=s0; y=s0 vs s2. This is global-alloc (callee-saved) assignment. Tags: `global-pri-bank-order`, `greg-ref-count`.

otp refs: used 8 times? y: used in vy=y, then y+=h_, stores. In the target otp gets s0. In mine y gets s0.

Maybe the fix: change how often otp is referenced? Can't (semantics). Or use a temp for the OT pointer? Hmm, e.g. `s32 ot = otp;`? That adds a copy.

Alternatively: this is exactly the sort of thing a wall tag covers: "global-pri-bank-order" (global-alloc priority order assigns the hard regs in a different order than the target).

Given the time (we're ~40 min on item 1), and the budget says 20-30 min per item, I should stop and record WALL with best=28, evidence global-alloc priority order (otp/y callee-saved swap), tag `global-pri-bank-order`.

But wait — the brief says the wall row needs a tag from walls.txt or a new one, and evidence = gcc pass + mechanism. Fine.

Hmm, but hold on. Before declaring a wall, maybe one more idea: the launders in the original also had a role: they split x and y's live ranges. Without them, x/y have longer ranges. But the residual is about otp/y.

Actually — wait. Maybe I should reconsider whether the do-while middle wrap is the right direction at all. The score 28 with a 10-register swap is a COUNT diff of 10. Without the wrap it's 30 but with a different pattern (mine 119 ins).

Let me consider one more experiment: the target's `move a0,s1` (vx copy) and `move v1,s2` (vy copy) — mine has `move v1,s1` and no a0 copy, i.e. vx stays in s1 and the store sh s1,8. Target copies vx into a0 and vy into v1.

Why does target copy? Because vx is used twice (0x8 and 0x18) and x is modified in between: s1 = x is modified by addu at 389c; the vx use at 38a8 (sh a0,24) needs the old x → must be a copy. In mine, the add happens at 76 (after sh s1,8 at 67), so s1 still holds x for the first store; only the later use needs a copy → one move instead of two.

If mine scheduled the add after both vx stores like the target, we'd get both copies. The do-while wrap of the middle group made... hmm.

So the root issue remains scheduling order.

Let me look at the middle-wrap candidate's diff again (the one from dd.txt): mine has sh s1,8 (vx) and sh s0,10 (vy) then lw t1 then sh s0,18 (vy at 0x12) then addu s0...

Target: move a0,s1; move v1,s2; ... sh a0,8; sh v1,10; lw t1; sh s1,16; sh v1,18; sh a0,24; ...

So in target, the copies happen before the c stores; in mine the stores use the original regs directly.

What if I make vx and vy copies explicit at the top of the first group (they are: vx = x; vy = y) — but the compiler coalesced them away where possible (vx = s1 for the first store). The `move a0,s1` in target exists because vx's pseudo got a different register than x? vx is a separate variable; local-alloc gave vx = a0 ($4, caller-saved!) while x = s1. Interesting: in the target, vx lives in a0 and vy in v1 (both caller-saved, cheap since no calls after). Mine assigned vx=s1 (same as x, coalesced) and vy=s0.

So a lever-free move to force vx into its own register: make vx's live range overlap x's longer... e.g., if the add x += w_ were scheduled before the first vx store, vx couldn't share s1. That's the scheduler again.

Alternatively, use vx more often so local-alloc prefers a separate reg: e.g. use vx in a third place? That changes code.

I think this is a wall. We have ~50 scored tries on item 1 (36+8+16+16+4 = 80). Time well over 20 min. Let me record the WALL row for item 1 and move on. I'll pick the best lever-free body as win.c? No — WALL means best = lowest score of a lever-free body; win.c is only for MATCH/PARTIAL. But the brief says "each MATCH/PARTIAL has its win.c scoring 0". For WALL, no win.c needed. I'll keep the best body file and note it.

Wait, but DONE WHEN says "every item of G30/list.tsv has exactly one results.tsv row". And PARTIAL: "<kinds still kept>" — for a WALL, we just record best.

Hmm, should I consider PARTIAL? PARTIAL = win.c scores 0 keeping only some levers. E.g. if keeping the barrier but removing the launder gives 0, that's PARTIAL:barrier. Is that useful? The original scores 0 with all levers. Maybe removing only the launders (keeping barriers) scores 0! That would be PARTIAL:barrier. Let me test quickly — cheap and informative: orig with launders removed (barriers kept).

Actually the brief: result MATCH | PARTIAL:<kinds still kept> | WALL. A PARTIAL row is better than WALL (it shows progress). Let me test:
- p1: barriers kept, launders removed.
- p2: launders kept, barriers removed.

Let me create those two bodies by editing orig. orig.c is lines 2432-2487 of src. I'll generate with a script or sed deleting specific lines: body lines 26,27 (launders) and 24,34,40,47 (barriers).

Let me create p1 (barriers kept, launders removed): delete body lines 26-27.
p2 (launders kept, barriers removed): delete body lines 24,34,40,47.

Careful with line numbers after deletion. Use python.
