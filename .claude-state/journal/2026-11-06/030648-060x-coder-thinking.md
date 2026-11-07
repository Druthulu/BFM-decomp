---
ts: 2026-11-06T10:06:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VXiiIxeaLQxmiwGWpHvJ
---
Key: `reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1` → local. So tb has reg_n_deaths == 1 → local. t has reg_n_deaths == 2 (dies at both defs? actually "dies in 2 places") → global.

To make tb global: give it reg_n_deaths == 2, i.e., two deaths. A pseudo dies at each set that is the last use before the next set. If tb is set twice, it has 2 deaths (or more).

Simplest: set tb twice with a use in between:
```
tb = s0->unk54;
s0->unkE = tb;
```
→
```
tb = s0->unk54;
s0->unkE = tb;
tb = 0;   // second set, but then tb is dead — would the set be eliminated?
```
A dead set `tb = 0` with no later use: dead code elimination (flow) removes it, then reg_n_deaths stays 1.

Need a live second set. What about:
```
tb = s0->unk54;
s0->unkE = tb;
```
and later reuse tb as another variable? The function later has `t = s0->unk50; s0->unkA = t - 8;`. If I use tb instead of t there:
```
tb = s0->unk54;
s0->unkE = tb;
...
tb = s0->unk50;
s0->unkA = tb - 8;
```
Then tb has 2 sets → global. And t is only used for unk4C (1 set, 1 use) → local (v0). Hmm, then local t gets v0, and global tb gets v1? Let's see:
- t: 1 def 1 use, local, pri 2/2=1 → v0.
- tb: 2 defs (unk54, unk50), global. Lives 53-59.
- Also the anti-dep: sh tb,14 at 58 before tb=unk50 at 55? Wait order: unk54 load, unkE store, then unk50 load, unkA store. tb reused for unk50. The store `sh tb,14` must precede the unk50 set → anti-dep keeps ordering. Good.

But wait, target: unk54→v1, unk50→v0. If tb (global) gets v1 for both, then unk50 would be v1, but target wants v0 for unk50. Mismatch.

Hmm. Target has unk4C=v0, unk54=v1, unk50=v0. So the unk50 value must be in v0, a different pseudo from tb(v1).

So: t (unk4C) → v0, tb (unk54) → v1, and the unk50 value → v0. In target, the unk50 value is the same `t` variable (reused) in v0.

So t must be reused for unk50 (giving the anti-dep and v0). And tb must be global to avoid taking v0.

So: give tb 2 deaths WITHOUT changing its register or code. Options:
- `tb = s0->unk54; s0->unkE = tb;` then a dead-but-surviving second set. What if the second set is used in a way that produces no code? E.g., `tb = tb;` — flow/cse removes.
- Use tb in a comparison whose result is... adds code.

Hmm, what if I make tb's second death come from a "use" that's free? A pseudo dies at a set when the old value's last use precedes. Actually reg_n_deaths counts the number of times the register dies (i.e., number of regions between sets where it's dead). If tb is set once and used once, it dies once (after the use). If set once and used in two different blocks, it dies once but reg_basic_block might be -1 (multi-block) → global.

So making tb used in another block would make it global! E.g., use tb in a later block (even in a way that's optimized out? no, it must survive).

Alternatively, use tb for the unk50 store too? But then register mismatch.

Wait, actually, let's reconsider: does it matter that t and tb are in the same block? If tb is global, global-alloc sees t (pri 10000, allocated first) then tb (pri 2500). But there's also the local t? no.

Hmm, but if tb is global with life 53-58 and t global life 52-59, they conflict, so tb gets the next free reg after t takes v0 → v1. 

So I need tb global. The cleanest real-C way: initialize tb at declaration (a second set) but make the initialization live... 

What if I declare `s32 tb = ((Unkstruct_800CD314 *)s0)->unk54;` at the TOP of the function (init at decl)? Then tb is set at function entry (block 0) and used in block 2 → multi-block → global! But the load would then happen at the top of the function, changing code order. No.

What if I set tb in block 2 before the `if ((cnt&7)==0)`? That's a different block, changes order.

Alternatively, make tb die twice by setting it twice where both sets are used. E.g.:
```
tb = s0->unk54;
s0->unkE = tb;
```
and then reuse tb for the `addiu`:
```
tb = s0->unk50;
s0->unkA = tb - 8;
```
But then unk50 is in tb's reg (v1), not v0. Target wants v0.

Unless after the first death, global-alloc can reuse... no, tb is one pseudo with one reg.

Hmm OK. Let me reconsider whether the target's unk50 really is v0. Target line 55 `lw v0,80(s0)`, 59 `addiu v0,v0,-8`, 61 `sh v0,10(s0)`. Yes v0.

And t (unk4C) v0 too (52 lw v0,76; 54 sh v0,6). So t is reused, v0.

So t is global v0; tb global v1. Both global, t first.

To make tb global with 2 deaths but only one actual def... reg_n_deaths counts deaths; a pseudo can die twice if it's live across a set? No.

Actually reg_n_deaths: number of times the register is "dead" (i.e., number of DEF-USE regions). For a register with 1 set and 1 use, n_deaths=1. With 2 sets and 2 uses, n_deaths=2.

So tb needs 2 sets. If tb has 2 sets and both values are used, and the second set's value goes to unk50, then tb=v1 for both → mismatch for unk50.

Unless the second set of tb is for a DIFFERENT purpose that's then dead? no.

Hmm, what if tb is set twice but the first set's value is used for unkE and the second set is for something that doesn't emit code? Like `tb = tb + 0;`? flow might remove.

Alternative: make tb global by making it live across a call (crosses a call). A pseudo that crosses a call is still local if single-block single-death? The condition is reg_basic_block>=0 && n_deaths==1. Crossing a call doesn't force global if in one block. Hmm.

Alternative approach: change the t/tb assignment by manipulating the local-alloc qty order so tb gets v1 instead of v0. Local-alloc assigns in priority order: higher priority gets the first free reg (v0). tb is the only local qty (r75) → gets v0. If there's another local qty with higher priority that wants v0 and overlaps tb, tb gets v1.

The local qtys in block 2 (from dispositions): r75 (v0), r79 (v0), r80 (v0), r87 (v0), r88 (v0), r89 (v0), r92-97 (v0), r100, r101 (v0). Wait many are in v0 — they don't overlap.

Hmm, the dispositions show which reg each got. r75 in v0. If I add a local qty that overlaps tb's range and has higher priority, tb → v1. But adding a qty adds code.

Wait — what about the other direction: make t NOT conflict v0 by making tb's local assignment v1. Local-alloc's find_free_reg for tb picks the first free reg in the class. At tb's birth (insn 74 in RTL), what's live? t (global, not yet allocated — global runs after local; but local-alloc considers hard regs live at that point). v0 might be live due to a hard-reg use.

Actually, local-alloc runs BEFORE global-alloc. So when local-alloc assigns tb, t is still a pseudo (not a hard reg), so no conflict. tb gets v0. Then global-alloc sees tb in v0 and t conflicts it.

So the fix must be at local-alloc: make tb get v1, or make tb not local.

Idea: make tb local but its qty priority lower than another local qty that takes v0 and overlaps. What local qty overlaps tb (53-58) and could take v0? Looking at the code, between insns 53-58 there are: the `li a0,2274` (hard reg), `sw zero,48(s0)` (constant store), and the addiu t-8 (result pseudo). The addiu result is used at 61; if it's a local qty born at 59, no overlap.

Hmm.

Different idea: make tb's value computed into a hard reg directly? Not possible in C.

Let me step back. Maybe I'm overcomplicating. Let me look at how OTHER shards cracked barrier,pin items — the moves.md has many. For a "pin $3" case, moves like func_80157BC8 used call-site return-type casts. For register assignment, a common move is "reuse the pointer" or "change width".

But actually, maybe the simplest: swap the roles — make `tb` the reused variable (2 defs → global) and `t` the single-def one, but arrange so the reused variable's second value is the one that should be in v1. Hmm target: unk54 v1, unk50 v0, unk4C v0.

What if:
- t = unk4C (1 def, local → v0)
- tb = unk54 (1 def, local → ?)
Both local: order by pri. t (2 refs, life 2, pri 1) vs tb (2 refs, life 5, pri 0.4). t first → v0. tb born at 53: t live till 54 → v0 taken → tb → v1. That matches! And unk50: reuse t → but t then has 2 defs → global. Hmm.

So use t for unk4C only (local v0), tb for unk54 (local v1), and a THIRD variable for unk50. The third variable should also get v0 (target). If third is local, born at 55 (after t's death at 54), it gets v0. 

But then no anti-dependency between the unk4C store and the unk50 load, so sched1 may group loads (as in v4). Hmm. Unless we can create a dependency.

Wait, in v4, why did sched1 group the loads? Because there's no dependency. But actually the load of unk54 (tb) and the load of unk50 (u) are independent; sched1 moved them together. The target has: lw 76, lw 84, sh 6, lw 80. So target also groups the first two loads but keeps sh 6 before lw 80.

Hmm, target order: 52 lw v0,76 (t); 53 lw v1,84 (tb); 54 sh v0,6 (store t); 55 lw v0,80 (u). So loads t and tb grouped, then store t, then load u.

In v4 mine: 52 lw v1,76 (t); 53 lw a1,84 (tb); 58 sh v1,6; 59 sh a1,14; then lw 80? Let me dump v4 fully. The issue is the stores got pushed after both loads AND after the unk50 load maybe.

Actually in v4 the diff showed mine 52,53 loads; 54 missing store; ... 58 sh v1,6; 59 sh a1,14. So the store t moved to 58. That's a big reorder.

Why? Without the anti-dep (t reused), sched1 has more freedom. The dependency chain in the source: load t; store t; load tb; store tb; load u; store u-8. sched1 groups the loads (52,53) and defers stores.

In the target (with pins), tb pinned to v1 makes... hmm, the pin shouldn't affect sched1. Actually sched1 runs before register allocation, so pins (hard regs in RTL) DO affect sched1: a hard reg reference creates dependencies. The pin on tb=$3 might force ordering!

Wait, but the original body has the pin, and sched1 sees `tb` as hard reg $3. The store `sh $3,14(s0)` etc. Hmm, would that change scheduling? Possibly.

Ugh. So the pin also affected scheduling, not just allocation.

OK. Given time (already ~20 min on this item?), let me count: I've spent a while. The budget is 20-30 min wall per item. Let me check the time.

Actually let me be pragmatic. Score 7 is decent but not 0. Let me try a couple more variants quickly, then if not, record PARTIAL? No — PARTIAL means win.c scores 0 keeping only some levers. Since we can't score 0, it's a WALL.

Wait, the kinds are barrier,pin. A PARTIAL would be "win.c scores 0 keeping only those levers". Since no lever-free body scores 0, we'd report WALL with best = 7.

But the requirement: WALL needs ≥20 min and ≥30 scored tries. I've done ~6 tries. I need ≥30. Hmm, that's a lot for 4 items. 30 tries × 4 = 120 compiles. Each compile ~2s → 4 min of compute. Plus my generation. That's feasible if I generate variants in bulk.

But honestly, the spirit is to make a genuine effort. Let me generate ~30 variants per item via a script that applies combinations of real-C moves, score them all, and take the best. That satisfies the try count and might crack.

Let me first check the time budget. Start time was 02:54. Let me check now.

Actually, let me focus: for CD314, the two problems are (a) t/tb register swap, (b) delay slot. Let me try to solve (a) by making tb global via a second def, and see the effect on scheduling. Actually the second def changes code.

Hmm, alternative for (b): the delay slot `move a0,s0` vs `nop`. This is reorg filling the call delay slot. In the target, `move a0,s0` is the arg setup and reorg puts it in the delay slot. In mine, the arg setup is missing entirely (weird). Let me investigate that separately — maybe with the call cast removed it appears.

Earlier v2 (plain call) still score 7. Let me check v2's diff — maybe the nop vs move persists.

Actually, let me reconsider the missing move. Could it be that in mine, `s0` is in $4 (a0)?? Let me check the final .s of nopin: the prologue `move s0,a0` means s0 var in $16. Hmm.

Wait — actually maybe the compiler passes the arg in a0 because the LAST call's argument pseudo got coalesced to a0, and the `move a0,s0` IS there but as part of the preceding instruction? No.

Let me look at the raw RTL for the call in the lreg dump. Search for func_80146C3C in the lreg section.
