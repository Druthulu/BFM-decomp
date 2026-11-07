---
ts: 2026-11-06T23:56:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RgWunSr76ekLpGkXnXwz
---
Interesting! The diagnostic's r73 still shows refs 5, live 83. So my added `if (mode != -2 && mode != -3) { }` did NOT add refs to r73. Why? Because the empty if body was optimized away before the .lreg dump (jump1 deletes the branch to the empty block, then the compare is dead). Right — an empty then-block: the branch has both targets equal, so jump1 removes the compare entirely. So no extra refs. That explains it.

So the diagnostic was invalid. To add refs to mode without changing the *final* code is hard.

Let me test with a real extra ref that survives to the .lreg stage. Hmm, but then it changes the final code.

Let me instead do a *structural* diagnostic: replace `if (mode == 0 && (res & 1))` with something that adds a ref. Actually, I don't need a valid body; I need to confirm the priority→reg mapping. Let me add `if (mode < -1) { func_8002F620(); }` — a real branch. That adds refs and code.

Actually, let me not burn more time on diagnostics. The mechanism is clear from the code (find_reg picks the lowest free reg in allocation order, order = descending pri). base r72 pri 1518 > mode r73 pri 1204. So base gets s3 before mode gets s4. To flip we need mode's pri above 1518, which needs a real change to refs or live that would change the emitted code.

Can I shorten mode's live range (83) to ≤65 without changing code? live_length is computed by flow from first to last reference. Hmm, what if I move the last use earlier in the RTL? `if (mode == 0 && (res & 1))` is near the end. Fixed.

What if I move the first set later? It's `mode = -1;` immediately before the if. Fixed.

Hmm, so live 83 is fixed. refs 5 fixed. pri 1204 fixed.

And base refs 8, live 158 fixed. pri 1518 fixed.

So lever-free, base always beats mode. WALL: global-pri-bank-order.

Wait, unless... the launder fix adds a pseudo that changes things? No.

Hmm, hold on. What if the target's real source doesn't have `base` as a variable at all but uses `D_800AF630` through a *different* register class? No.

Actually — wait. What if `base` is not u8* but the struct pointer `Unkstruct_80010178 *base`? The code casts `((Unkstruct_80010178 *)base)->...`. If base were declared as `Unkstruct_80010178 *base = (void *)D_800AF630;` the RTL would be the same. Refs same.

What if `base` were an `s32` and used as `((Unkstruct*)(s32)base)`? Same.

OK so the reg order is a WALL. But what about the copy? Both walls apply. If I can't fix either, this is a WALL with best = 14 (G_nopin) or 5 (H_nolau) — the lever-free best is 18.

Hmm wait, "best = lowest score of a lever-free body". Lever-free means NO pin and NO launder. So best = 18 for the lever-free win.c. The G_nopin (14) and H_nolau (5) keep one lever each, so they're PARTIAL candidates.

Hmm, "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So if I could make a body score 0 keeping only the pin, that's PARTIAL:pin. Can I? H_nolau (pin kept, launder removed) = 5. G_nopin (launder kept, pin removed) = 14. So neither scores 0. So no PARTIAL.

So item 1 → WALL, best 18.

But wait — before giving up, let me reconsider the copy problem once more, because if the copy is fixable, the best would be 14 (G_nopin) and then the remaining wall is just the reg order.

Actually, since both are needed for 0, and the reg order is a WALL, item 1 is a WALL regardless. Best lever-free = 18.

Hmm, but hold on: maybe I'm wrong that the reg order is unfixable. Let me think about `-1` and `0`...

AH WAIT. Here's an idea! What if `mode` is given a *second use* that already exists in the code but is currently attributed differently? Look: `move a2,s3` at 1268 passes mode to CdReadRequest. And `bnez s3` at 1278. And `bltz s3` at 1208.

Hmm what if the C used `mode` in the `file` computation... no.

Another idea: what if `mode`'s live range could be shortened by having the `mode >= 0` test use a *different* pseudo (a copy)? No.

OK, let me also consider: maybe the priorities are compared with `allocno_size`. size=1 for all (word). Fine.

Decision: item 1 = WALL, best 18, tag `global-pri-bank-order` (and the copy is `cse-copy-merge`).

But I need ≥30 scored tries. Let me batch-generate ~30 lever-free variants (varying statement order, decl order, types, temp spellings, the copy constructs) and score them all. That satisfies the try count and might surprise me.

Actually, wait. Let me reconsider the copy issue once more with fresh eyes, because it's the classic `cse-copy-merge` and maybe there's a documented crack. From moves.md: `func_8018C2D8 | MATCH — reuse m for next ptr (m = s1+0xD0; dv = m) and m1 for col: reassignment kills the cse sym class`. So a *reassignment* of the pointer kills the cse class. 

Here: if `q` is reassigned (a real 2nd set) BEFORE the copy... Let me think: `q = &D_800C7C60; p = q;` — if q is assigned twice *before* the copy, cse's qty for q is from the LAST set. Hmm.

What if q is a variable assigned in both arms of an if? e.g.:
```
s32 *q;
if (x) q = &D_800C7C60; else q = &D_800C7C60;
p = q;
```
jump1 merges. Hmm.

What about the C0414 dead-reset AFTER the copy — B_deadreset_after gave 160, no help.

Hmm, what if the dead reset is BEFORE the copy on a *different* variable? no.

Let me try: q assigned from p later, making q multi-set:
```
p = &D_800C7C60;
q = p;
*p = val;
q = 0;      // dead reset of q
```
The dead reset after doesn't affect the copy.

Hmm, what about making `p` itself multi-set so the copy survives? p is set to 0 in the else arm and to q in the then arm — already multi-set (cross-block).

OK here's another thought: the real issue is cse1 equating p and q within the same extended basic block. What if I make the copy happen in a *different* extended basic block by inserting a branch between? E.g.:

```
s32 *q = &D_800C7C60;
if (val == val) {}   // no
```

Hmm, what about using the existing structure: put `q = &D_800C7C60;` before the `if (func_8002F658() ...)` and the copy inside — A_hoist did that and got 160. So cse followed the branch. Because cse_main follows the taken path through a conditional branch when the block ends with a branch... Actually for a conditional branch, cse_end_of_basic_block may return the end and cse_basic_block processes up to there; the then-block is a new cse_basic_block with new_basic_block() clearing the table. But maybe the *frontend* folded p=q.

Hmm, let me test the frontend hypothesis: does `p = q` even generate a copy in the RTL? Let me check the .rtl or .lreg dump for the G_nopin body. In G_nopin (launder kept), there's the asm. Let me look at A_hoist's RTL... 

Actually, simpler: in the A_hoist dump, is there a copy insn? Let me check the .lreg for A_hoist. That would tell me whether the copy exists in RTL and gets coalesced by local-alloc, vs never existing.

Given time constraints, let me pivot: batch 30 tries now, then decide.

Actually, let me reconsider the value of continuing on item 1 vs moving to other items. There are 4 items; each needs ≥30 tries for a WALL. That's a lot. Let me be efficient: for each item, generate a broad batch of candidates in one go, score them, and if none hits 0, record the wall.

Let me build the batch generator for item 1 with ~30 variants covering:
- copy constructs: dead-resets in various positions, hoisting, u32 temp, void*, char*, struct field, const, two-step
- statement orders: swap D_800C7C64 store and *p=val
- decl orders

Let me write it.
