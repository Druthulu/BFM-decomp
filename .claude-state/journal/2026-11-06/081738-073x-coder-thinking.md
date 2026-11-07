---
ts: 2026-11-06T15:17:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fHuxSAbqYl4FvrEjHk1F
---
In a0, insn 476 has priority 12 too. The difference is the ready-list order: at T-7, "483 (7f000001) 484 (7f000001), now 484 483" — the ready list insertion order differs. In b4, at T-8: "478 (c) ..." etc.

The priorities are the same (1, 12). So the difference is the *ready list order* (which depends on uid/order and dependencies), not the boost.

Hmm, in a0 the ready list at T-7 has 483 before 484; at T-8 483 alone. Then "launching 472 before 483 at T-9" — wait, 472 appears at T-9 though it wasn't in the ready list? The log shows "launching 472 before 483 with 8 stalls at T-9" — meaning 472 became ready (a dependency was satisfied) and was inserted before 483.

In b4: T-7 "476 (c)" (c = REG_DEP... something), T-8 "473 474", T-10 "launching 484 before 473 with 7 stalls". So 484 launched at T-10; 472 at T-22.

So in b4, 484 (pan mult) is ready earlier than 472 (vol mult). In a0, 472 is ready at T-9 and 484 at T-7/T-8 (but 483 launched). Hmm.

The dependency: 472 depends on 469 (the multiply numerator) and 538 (the magic constant). 484 depends on 481 and 538. The ready times differ because of the DAG.

Honestly, the mask's presence changes the DAG (an extra insn 478 with a dependency on 476), which changes the ready-list ordering/timing. That's a scheduling artifact of the extra insn, not a semantic lever. So a real C change needs to alter the DAG equivalently.

Hmm OK. Let me consider: what natural C would put a *use* of vol between the vol division and the pan division? The launder is exactly such a use (a re-tie). A natural body might use vol in a comparison or store there. 

Idea: `if (vol < 0) vol = 0;` — clamps vol, a real computation (not identity!) if vol can be negative. It adds a branch though (+2 insns?).

Idea: compute the OR earlier: `vol |= (0x3000 | sx)`? sx isn't computed yet.

Idea: `vol = vol * 0x7F / 0xA0` — no.

Hmm, what about the real original C: maybe `vol` and `sx` were the same variable or the computation was `vol = ((0xA0 - av) * 0x7F) / 0xA0;` followed by `sx = ...` and then `func(0xA9B, (vol | (0x3000|sx)) & 0xFFFF)` — the dev says 9 spellings don't move it. 

Given the identity-launder rule, maybe this item is genuinely a WALL. The dev's note says the launder is "NEEDED DIFFERS" — a known lever needed for the bytes. The shard's purpose is to find lever-free bodies; some are walls.

But before declaring, let me try a few more REAL C ideas (not identity):
1. Clamp vol with a conditional (real C, changes semantics only for out-of-range av): `if (vol < 0) vol = 0;` — but that adds a branch.
2. Compute the pan BEFORE vol in source (maybe with the mask removed the compiler's ready-list order flips):
   ```
   sx = (sx + 0xA0)/0x14;
   if (sx == 0x10) sx = 0xF;
   vol = ((0xA0-av)*0x7F)/0xA0;
   sx = sx << 8;
   func(...)
   ```
   Source order pan-first — sched1 would then... the birth boost makes pan first anyway. Probably still pan-first.
3. Use a different expression for vol that changes the DAG: e.g., `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` (t1/t4).
4. `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then `sx = (sx + 0xA0) / 0x14;` but compute sx via a temp `s32 p = sx + 0xA0; sx = p / 0x14;` — a real split for sx (2 sets of sx? no, sx set once by p/0x14; p is new).

Hmm, what if I split the PAN computation into two statements (giving sx an extra set)? sx is already multi-set. Not the lever.

Let me test idea 2 and 4 quickly, plus a couple of real-C vol variants (t1 family with different splits), then decide.

Actually — wait. Let me reconsider the birth boost. In a0 vs b4, priorities are identical, so the boost isn't the mechanism. The mechanism is the extra insn 478's effect on the ready list timing. So ANY zero-cost insn inserted between the vol div and the pan div that uses/defines a value would change the timing similarly. But we need it to not be stolen by reorg.

What if the insn is a *use only* (no set) — e.g., a comparison whose result is used later? A USE insn in RTL would be deleted by flow. 

What if the second "set" is a set of a pseudo that dies immediately — dead, deleted.

What if the insn is a store to a stack slot that's already there? Not in the target.

OK, so the extra insn must be a real computation that ends up in the target's 237. The target has no such insn → impossible without removing another. So the only hope is a real C change that changes the DAG *without* an extra insn — i.e., a different expression structure.

The DAG difference between a0 and b4 is just the extra 478 node. Without an extra node, we need a different DAG shape. What real C changes the DAG shape? Different association/order of the vol computation:
- `((0xA0 - av) * 0x7F) / 0xA0` → the DAG: subu(0xA0,av) → sll/subu (*0x7F) → mult(magic) → shifts/subu.
- Maybe `(0xA0 - av) / 0xA0 * 0x7F` — different (and wrong).
- `((0xA0 - av) * 0x7F) / 0xA0` vs `(0xA0 - av) * 0x7F / 0xA0` same.

Hmm, what about the pan: `(sx + 0xA0) / 0x14` vs `sx / 0x14 + 8`? Different DAG (and semantics differ slightly for negatives).

What if the pan is computed as `(sx + 0xA0) * 0xCCCD >> ...`? That's what the compiler does.

Let me try: `sx = (sx + 0xA0) / 20;` (decimal 20 = 0x14) — same.

What about `vol = ((0xA0 - av) * 127) / 160;` (decimal) — same.

Hmm.

Another thought: the launder could be replaced by a real second set of vol that IS in the target's code: what if the target's `andi a1,a1,0xffff` at 5a8 (the outer mask) is actually the *vol* set? In the target's RTL, the arg temp and vol might be the same pseudo if the source wrote `vol = (vol | ...) & 0xFFFF; f(vol)`. But c1 showed cse collapses it. What if the call is written to prevent cse forwarding: e.g. `func_8002D4C8(0xA9B, (vol = (vol | (0x3000 | sx)) & 0xFFFF));` — an assignment inside the expression. cse might still forward. Or use a comma expression.

Let me test the assignment-in-expression form and a couple of others (f-series), including:
- f1: `func_8002D4C8(0xA9B, (vol = (vol | (0x3000 | sx)) & 0xFFFF));`
- f2: `vol = (vol | (0x3000 | sx)) & 0xFFFF; func_8002D4C8(0xA9B, (vol, vol));`
- f3: with a `s32` cast: `func_8002D4C8(0xA9B, *(volatile s32*)&vol = ...)` no.

Honestly c1's collapse is cse: the set of vol is dead because vol's only use is the call, and cse forwards the temp. To keep the set, vol must be used somewhere that cse can't forward, e.g. a memory store or a second call.

Wait — c1's RTL: insn 476 sets vol (the div), and the ior uses vol; the result is a temp used by the call. The tree `vol = (vol|..)&0xFFFF; f(vol)` should produce: temp = or; vol = temp; f(vol) → the copy vol=temp then f(vol). cse would replace f(vol) with f(temp) and delete the copy. To prevent that, the call could take `&vol`? No.

Hmm.

What if vol is used AFTER the call too? E.g., the last block `if (unkFC == 0x18) { unkFC = 0; }` — no.

What if the argument is `vol` and there's also a use in the `if (unkFC == 0x18)` condition? That changes code.

OK, let me try a completely different real-C idea: make vol an `s32` that's computed with a `+=` accumulation, e.g.:
```
vol = 0;
vol += ((0xA0 - av) * 0x7F) / 0xA0;
```
The `vol = 0` is a real set; is it dead? vol is used later (the or), so `vol = 0` is dead (overwritten by +=). flow deletes dead stores... but flow's DCE might keep it if it can't prove. Actually flow does dead-store elimination only for simple cases. `vol = 0; vol += expr;` — the first is dead; flow deletes it. Likely.

What about `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then `vol += 0;`? fold.

Hmm.

Let me take yet another angle: maybe the launder's replacement can be a real second set that lands in the target's code because the target ALREADY has a second set of a DIFFERENT variable that I can repurpose. For instance, `av` is set twice (`av = sx; if (sx<0) av = -sx;`) — already 2 sets. `sx` many. `vol` once. What if vol were declared as the same variable as `sx`? No.

What about making `vol` the same variable as `t`? Let me check the target's registers for t: in the target disassembly, let me find the func_8004787C block. t is probably in v1 or a1. If t dies before the tail block and vol is born there, reusing the C variable could be free (same pseudo, different live ranges — but gcc has no live-range splitting, so ONE pseudo for both → the allocator assigns one hard reg for the whole range, which may differ from $a1). Risky.

Let me look at the target around the t block to see t's register.

Actually, let me step back and consider the time budget. It's been ~35 min on item 1. Per the brief, past 30 min stop and record a wall. But the wall requires ≥30 scored tries. I have 20. Let me do 10-15 more quick tries, then record WALL for item 1 and apply the same to items 2-5 (they're identical bodies but different TUs; I need ≥30 tries per item — that's a lot. Hmm, but I can reuse the same candidate set per item: each scored try on that item counts. If I generate 30 candidates for item 1, I can run the same 30 on items 2-5, giving 30 tries each.)

Actually, if I find a MATCH for item 1, I can test the same body on items 2-5 (they're the same function). Let me push a bit more.

Let me reconsider the problem completely. The target's 237 insns with the launder: the launder is an empty asm (0 insns) yet the body without it is 236. So the launder changes the schedule such that ONE extra insn appears (the duplicated sll from reorg). In b4 (mask), we get 237 with the andi but only one sll. So b4 is "one insn different" in a fundamental way: target = {2 sll}, b4 = {1 sll, 1 andi}.

For a real crack, we need a body whose schedule naturally produces the duplicated sll AND 237 insns. The duplicate sll comes from reorg copying it into the delay slot. In a0 (no launder), is the sll duplicated? Let me check a0's final disassembly around the branch. If a0 has the sll duplicated but pan-first... Let me look.

From the earlier a0 diff:
```
mine[216:220]: bne a3,v0,594; sll a3,a3,0x8; li a3,15; sll a3,a3,0x8
```
YES! a0 (no launder) DOES have the duplicated sll (2 slls) — exactly the target's tail shape, just with pan-first and different regs (a3 vs a2). And 236 insns (one less than target 237). So a0's tail is right but the overall schedule/registers differ.

So the extra insn in the target (237 vs 236) comes from somewhere else (the `nop` after the pan addiu? In the target: `addiu v0,a2,160; nop; mult v0,a0` — the nop is a hazard filler inserted because of the mult ordering; in a0 there might be no nop).

So a real crack needs the DAG/allocation to produce the target's order. The launder's presence changes sched1's ready-list timing → allocation → sched2. 

Since the launder is an empty asm, its only effect is as a scheduling node (an insn with a use and a set of vol). A real C statement that creates a *use* of vol at that point, without adding an insn to the final code... impossible, unless the use is folded into an existing insn.

What if the vol value is used in the *pan* computation? E.g., `sx = (sx + 0xA0) / 0x14 + (vol & 0);` — fold removes. 

What if the pan computation reads vol in a way that's genuinely needed? No, they're independent.

What if the OR is moved earlier: `vol = vol | (0x3000 | (sx = (sx + 0xA0)/0x14));` — the or uses vol after the div, before the clamp/shift. Then vol has 2 sets (div, or) and the or is before the sll. The target's `ori a1,a1,0x3000; or a1,a1,a2` are AFTER the sll. Moving them earlier changes the order. No.

Hmm, but what if the or is before and combine/fold reorders? Unlikely.

Let me try the following real-C restructure: swap the order so that vol's use (the or) happens where the launder is:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol = vol | (0x3000 | sx);   // uses sx before it's recomputed! 
```
No, sx isn't computed yet.

What about computing the pan first, then vol, then the or:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
sx = sx << 8;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol = (vol | (0x3000 | sx)) & 0xFFFF;
func(0xA9B, vol);
```
Here vol's 2nd set is the or, after the sll. And the source order is pan-first. The birth boost would make pan first anyway. Let me test this (g1). Also g2 with `vol |= ...; vol &= 0xFFFF;`.

Also g3: compute vol AFTER the sll but keep the mask:
```
sx = ...; if; sx <<= 8;
vol = ((0xA0-av)*0x7F)/0xA0;
func(0xA9B, (vol | (0x3000|sx)) & 0xFFFF);
```
This moves the vol computation after the pan. The target's DAG has vol first. Hmm.

Let me just test a batch of structural variants and see if anything scores 0.

Batch (g):
- g1: pan-first source, vol second, call with the expression as-is.
- g2: pan-first, vol, `vol = (vol | (0x3000|sx)) & 0xFFFF; func(0xA9B, vol);`
- g3: vol-first but with the or assigned to vol, then mask, at the call position (e-series was 245).
- g4: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then `sx = (sx + 0xA0) / 0x14;` with the division written as `sx = (sx + 0xA0) * 0xCCCD >> 19`? No, that's not equivalent (the compiler does the exact magic).

Hmm, g3/e-series gave 245 because vol's live range/allocation changed.

Let me test g1, g2 quickly.

Actually, maybe a better idea: the launder re-tie exists because sched1's ready list order is sensitive. The ready list order depends on the *uid* (insn order) of the nodes. A real C change that reorders the DAG nodes slightly (e.g., computing `0xA0 - av` differently) could flip the ready list.

What about `vol = (0xA0 - av) * 0x7F / 0xA0;` — combine does the *0x7F as sll+subu. What if written `vol = ((0xA0 - av) << 7) - (0xA0 - av); vol /= 0xA0;`? Different DAG (two subtractions), but combine might re-merge. And semantics differ for overflow? No.

Or `vol = ((0xA0 - av) * 0x7F) / 0xA0;` vs `vol = (0xA0 - av) / 0xA0 * 0x7F;` (different).

Let me try a handful. Time-box: 10 more tries, then wall.

Let me also reconsider: maybe there's an entirely different approach — replace the launder with a `do {} while(0)` (C0535)? The moves say do-while splits cse1's EBB and cracked a sched1-birth-order item. But our mechanism isn't the birth boost. Still, a do-while around the vol computation might change the insn order/LUIDs. And a do-while(0) is plain C (allowed with the `// !FAKE: do-while` marker). Let me try:
```
do { vol = ((0xA0 - av) * 0x7F) / 0xA0; } while (0);
```
That's a real C construct that changes the block structure (cse1 EBB) without adding insns. Worth testing!

Also `if (1) { vol = ...; }` — probably deleted.

Let me test:
- h1: `do { vol = ((0xA0 - av) * 0x7F) / 0xA0; } while (0);`
- h2: `do { vol = ((0xA0 - av) * 0x7F) / 0xA0; sx = (sx + 0xA0) / 0x14; } while (0);` (both in the do)
- h3: `do { vol = ((0xA0 - av) * 0x7F) / 0xA0; } while (0);` + normal rest.

Let me run these.
