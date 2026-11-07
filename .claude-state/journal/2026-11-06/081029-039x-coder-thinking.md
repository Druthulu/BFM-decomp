---
ts: 2026-11-06T15:10:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7NhUC9GPxDOw41Mlo56P
---
moves.md changed (other shards appending). Fine.

c_g1 gave 211 ins — that means my rep.py replaced the wrong region? c_g1 = a1.c with o_tail replaced... o_tail is the two lines; I replaced with the if + cast + shift — but the `sx = (sx + 0xA0) / 0x14; if...` were already there, so now duplicated if? Actually g1's snippet re-adds the if — so the file has the if twice? No: o_tail.txt was the shift+call lines. I replaced them with if+cast+shift — so now there are two ifs and no call! That's why 211. My mistake: g1 lost the call. c_g2 kept the call → 238/8.

OK. I'm at ~30 tries. Let me check the time and decide about item 1.

Actually, let me try ONE more structural idea: the C0414 dead-reset! `vol = 0;` after the call? No — vol is used in the call.

Hmm, what about the classic §373 dead-reset to break cse? Not relevant.

Another idea: `vol = (u16)vol;` but put it in a `do { ... } while (0)` that wraps ONLY the cast (c_u16dw: 236/18 — worse).

What about wrapping the whole vol computation + cast in a do-while?
`do { vol = ((0xA0 - av) * 0x7F) / 0xA0; vol = (u16)vol; } while (0);` — EBB split might place the andi before the branch.

Let me try that plus the time check.

Actually — wait. Big realization: maybe instead of casting vol, cast the value at the point where it's used in the arg, but as a separate statement that assigns to a NEW u16 var used in the arg. The andi would be on a new pseudo, and the target's final andi would be replaced... hmm, the target's final `& 0xFFFF` remains.

Let me think about what the target's jal-slot andi is: `andi a1,a1,0xffff` where a1 = or(vol|0x3000, sx<<8). That's the final mask. Fine.

So in target the fall-through block's insns after the branch: sll a2,a2,0x8 (speculated), li a2,15, sll a2,a2,0x8, li a0,2715, ori a1,a1,0x3000, or a1,a1,a2, jal, andi.

In mine: andi(cast), li a2,15, sll, li a0, ori, or, jal, andi.

So mine's fall-through has 8 insns, target's has 9? Both 237 total. Ugh.

The difference: target's branch target is 4b90 (after the sll) and mine's is 4b8c (the sll) — i.e. target speculated the sll for the fall-through and mine did not (mine's fall-through goes through the sll at 4b8c after branching there).

Both semantically fine.

Since the andi(cast) is in the fall-through block, reorg chose it as the delay fill instead of the sll.

What if I make the cast's andi NOT in the fall-through block but before the branch (in the if-block)? E.g. place the cast before the if:
```
vol = (u16)vol;   (right after the vol division - that's c_u16)
```
already before the if. Yet sched1 moved it after the branch.

Hmm, sched1 schedules each basic block. The block containing vol's division ENDS at... the if's condition is `sx == 0x10`; the vol division is in the same block as the branch (the whole `if` region). So the andi was in the branch block but sched1 placed it last, and then reorg moved it to the delay slot (reorg moves insns from before the branch into the delay slot only if they're after the branch... no — reorg fills delay slots with insns from the fall-through path, OR from before the branch for "backward" filling of annulled slots).

Hmm, actually reorg can fill a delay slot with an insn from *before* the branch only for annul-true (never on mips).

So the andi must be in the fall-through block. But it's before the if in source... unless sched1 moved it after the branch (sched1 works per block; the branch ends a block, so it can't move it across).

Unless... the `if (sx == 0x10)` is not a branch block boundary the way I think. cse1 might have converted... 

Hold on: maybe the andi in mine at 4b84 IS the *final mask* and the one at 4ba0 is the cast's! I.e. sched1 placed the final mask early (at the branch's fall-through start) and the cast's andi at the jal slot. Both are `andi a1,a1,0xffff` — indistinguishable! But the final mask must come after the `or`. If the or is at 4b98 and the andi at 4b84 — impossible.

OK so mine: andi at 4b84 = cast's (vol ready at 4b68), andi at 4ba0 = final.

So sched1 (or reorg) placed the cast's andi in the fall-through block. That means the cast's statement is in the fall-through block — i.e. AFTER the branch in the CFG. But in source it's before the if... 

OH WAIT. Maybe gcc's jump optimization reversed the if: `if (sx == 0x10) sx = 0xF;` becomes `bne a2,16, skip` where the fall-through is the ==16 path... In the listing: `bne a2,v0,4b8c` (mine) — branch if != 16, to 4b8c. So fall-through = ==16 path (li a2,15; sll), taken = !=16 path.

Target: `bne a2,v0,4b90` → taken path = !=16 goes to 4b90 (after the shift), and the ==16 path is the fall-through (4b84 delay=sll, 4b88 li 15, 4b8c sll).

So in target, the sll was speculated into the delay slot for the fall-through ==16 path, and the taken path (which branches to 4b90) needs the sll too — it gets it via the delay slot (executed always). Right! The delay slot is executed on both paths, so the sll at 4b84 serves both; then the taken path jumps to 4b90 (after the li/sll block), and the fall-through does li a2,15 then sll at 4b8c (redundant but harmless).

In mine: delay = andi, fall-through ==16 path: li a2,15; sll at 4b8c; taken path jumps to 4b8c (the sll) — so the sll is shared at 4b8c, and no sll is needed in the delay slot.

So mine is a *more efficient* arrangement (237 with 2 andis) and target has an extra sll.

So to match, I need the andi to NOT be available for the delay slot. Then reorg would speculate the sll instead.

The andi comes from the cast (a vol def). reorg's fill_simple_delay_slots: it tries to fill with insns after the branch; it will move an insn if `eligible_for_delay` and it doesn't conflict. It moved the andi.

Hmm, what if the andi were *needed on the fall-through path before the branch target*? No.

What if the andi's register a1 conflicts with the branch target's usage? 

Honest assessment: I'm at 30+ tries and ~35 minutes. Per the brief: "past 30 min stop and record a wall". Let me check the clock first.

Actually the brief also says a WALL needs ≥20 min and ≥30 scored tries. I have ~32 tries and >30 min probably. But before declaring a wall, note best = 2 (a lever-free body scoring 2) — the wall would be "best 2".

But wait — maybe I should try a couple more high-value ideas since we're at 2:

Idea: make the final mask a *different* instruction (not andi) so the delay slot choice changes? The final mask is required.

Idea: Make vol's 2nd set an insn that reorg won't speculate: e.g. `vol = (u16)vol;` → andi. What if instead `vol = (u8)vol;` → andi 0xff — same class.

What if the 2nd set is `vol = (u16)vol;` placed so it's in the TAKEN path? no.

Idea: use a *shift pair* as the 2nd set: `vol = (vol << 16) >> 16;` → sll+sra (2 insns). Would reorg speculate a 2-insn pair? It might put both in... no, only one slot. Then one of them stays in the fall-through and one in the slot. Count 239.

Idea: 2nd set via `vol = vol % 0x10000;` → andi.

Idea: make the 2nd set depend on a load? no.

Let me try one more thing that's cheap and plausible: **swap the roles** — give the pan (`sx`) the extra use and leave vol alone, i.e. keep the source order but add `sx = (u16)sx;` before `sx = sx << 8;`... tried (f4, 238).

Alternatively — what about `vol` declared as `u16` AND the arg `(vol | ...) & 0xFFFF`: c_hvol 238/9.

Let me check the time now and decide. If I'm past 30 min, I should record a WALL for item 1 and move on. But 5 items all launder-type... they may share mechanisms.

Hmm, wait. Before walling: one more idea that directly targets the delay slot — C0535 says do{}while(0) splits cse1's EBB, changing sched1's view. If I wrap the *cast* in a do-while it gave 236. What if I wrap the `sx = sx << 8;` + call in a do-while? Or wrap the if?

Let me try wrapping the if block:
```
vol = (u16)vol;
do { if (sx == 0x10) { sx = 0xF; } } while (0);  // !FAKE: do-while
sx = sx << 8;
```
Hmm.

Actually — better idea!! What if the andi is eliminated because the cast is folded into the *division*: `vol = (u16)(((0xA0 - av) * 0x7F) / 0xA0);` was e1 → 2. Same.

OK here's one more: what if we make vol's second set happen at the *declaration*: `s32 vol = ((0xA0 - av) * 0x7F) / 0xA0;` (init at decl — in the catalog!). Then vol has 1 set still. But init-at-decl changes allocation/scope. Then add the cast... hmm.

Let me try: move the vol declaration+init to the point of use and add the cast:
```
s32 vol = (u16)(((0xA0 - av) * 0x7F) / 0xA0);
```
That's init at decl (C0505 catalog: "init at decl").

And a variant with `vol` declared at the top but assigned via a temp.

I'll do 3 more tries then wall.

Actually, let me reconsider ONE more angle: the `if (sx == 0x10) sx = 0xF;` — what if I write it as `sx = (sx == 0x10) ? 0xF : sx;`? That changes the CFG entirely. Probably worse.

Let me do the batch: h1 (init at decl + u16 cast), h2 (do-while wrapping the if), h3 (vol = (u16)vol placed immediately after av computation? no, vol not set yet).

Hmm h3: what about giving vol a *first* set before the division: `vol = 0; vol = ((0xA0 - av)*0x7F)/0xA0;`? That's a dead store — flow deletes it (flow-dead-store). But if not deleted, it's a 2nd set. Actually flow would delete the dead 0 store. Unless vol is used... no.

h4: `vol = av; vol = ((0xA0 - av)*0x7F)/0xA0;` dead store deleted.

Let me run h1, h2 and then decide.

Time check first.
