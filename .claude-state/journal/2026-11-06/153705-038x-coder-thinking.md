---
ts: 2026-11-06T22:37:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZhU7gxYUoPr3VuZjOmbJ
---
Interesting! In w3, r72 = s0 (4 refs, 8 live, block 0, crosses 1 call) — a block-local pseudo got $s0, and it's r72 (the arg0 copy? "Register 72 used 4 times across 6 insns in block 0" in w0). In w3 it's 4 refs/8 insns. Hmm. And r74 (divisor) conflicts s0 → s1.

Wait, in w3, s1ang raw is r75? "r75 v1 4000 2 5 0" — no. Let me map. Actually in w3, the reordering changed things: r72 = s0 (4 refs, 8 insns, block 0, crosses a call). Hmm, r72 is likely the arg0 copy or the pointer. In w0, r72 was v0 (4 refs/6). In w3, r72 gets s0 with 4 refs/8 insns crossing a call.

So the reorder made r72 (arg0-related) cross the call and take $s0. Interesting — so the s1ang load's live range changed.

Hmm, w3 score 45. Not better.

Let me think again about the original source. The decomp has the pin because the "natural" body gave d=$s1. But the original compiler gave d=$s0. What differs? Possibly the original source had `d` used in a way that raised its priority, OR the original had no separate s1ang raw local.

Wait — maybe the original source did NOT load s1ang before the call as a separate variable. Maybe the original source was:

```
u6 = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF;
```
i.e., no s1ang variable, just u6. Then the lh and andi would be adjacent: `lh $17,18($2); andi $17,$17,0x0fff` — but the target has them separated by the call. Sched1 would have to hoist the lh before the call. Since the andi is after the call (it depends on... nothing, just the lh), sched1 could hoist the lh above the call if allowed.

In the target, the lh is before the call and the andi after. This is consistent with the source `u6 = (*(...)) & 0xFFF;` placed after the u5 computation, with sched1 hoisting the load. But sched1 hoisting a load above a call — does it? Let me check sched.c for CALL handling.

Actually, the target's order: the lh $17 is the LAST pre-call load. That's exactly what sched1 would do if it hoisted the lh from after the call to just before the call (as early as its dependencies allow). Hmm, or it's just the source order.

If the original had `u6 = (*(...)) & 0xFFF;` after the call, then the pseudo for the load result would be born after the call and used immediately (andi) → not crossing the call → local-alloc gives it a caller-saved reg. But the target uses $s1 (callee-saved). Hmm, unless sched1 hoisted the load, making it cross the call in the scheduled RTL.

Wait — if sched1 hoists the lh above the call, then the load result crosses the call in the RTL that local-alloc sees → callee-saved → local-alloc gives $s0. Same problem.

Hmm, unless the lh result is a *global* pseudo. If u6 = (load) & 0xFFF and u6 is used in multiple blocks, then the whole chain might be global? No — the load result is used only by the andi in block 0.

OK here's the thing: the target's `lh $17,18($2)` + `andi $17,$17,0x0fff` uses $17 for BOTH the load result and u6 (in-place). That means the load result and u6 are the SAME pseudo (tied/coalesced). In our body, r75 (load) and r77 (u6) are separate pseudos, tied by local-alloc? The alloc table shows r75 (load) and r77 (u6) separately, and r77 "prefers s0" (from the tie with r75). In the target, they're coalesced into $s1.

Hmm, what if we write `u6 = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF;` directly, so there's ONE pseudo for the load+andi chain? Then the load result is used only by the andi, and u6 (global) is the andi result. The load pseudo would still be local. Same.

Hmm.

Let me approach from a different direction: what if the divisor d is allocated $s0 because it's a *local* pseudo? If the division happened in a single block, d could be local... no, d is live across the call.

Hmm, what if d is NOT live across the call because the division uses a *reload* of arg1 from the stack? E.g., if arg1 is spilled to the stack, the div would reload it. The target doesn't.

OK, let me look at the actual original disassembly target and think about what register allocator state produced it. Actually, maybe I should look at how the REAL original compiler allocated: the target is the original binary. The decomp's pinned build matches it. The question is whether a lever-free C body can produce it. The project has done this for many functions, so it's possible.

Let me look at the sibling func_8012BA10 more closely — it's the same code with different constants, and its notes say "globalising s1ang lifts its pri 6363 past d 5185 (G27x)". So for 8012BA10, the coder made s1ang global (via a do-while?) and it worked? The result was WALL though ("WALL lreg-qty-priority — ... (G27x)"). Hmm, so it didn't fully crack.

Wait, let me re-read: "keepalive,pin | func_8012BA10 | WALL lreg-qty-priority — block-local s1ang (2refs/7ins) takes $s0 in local-alloc before the global divisor d (7/27); globalising s1ang lifts its pri 6363 past d 5185 (G27x)". So they globalised s1ang (pri 6363) which then beats d (5185) for $s0 — the wrong direction, giving s1ang $s0 and d $s1. Hmm, but they said "WALL", best not MATCH.

For OUR function, d's pri is 10000 (capped) vs s1ang 2857, so if we globalise s1ang, d should win $s0! That's the direction we want.

So the plan: globalise s1ang raw. The challenge is cse2 merging the duplicate use. But in 8012BA10, they globalised s1ang somehow. How? Maybe via a do-while on the s1ang load block? A do-while creates a loop note and a new basic block! `do { s1ang = ...; } while (0);` splits the basic block (C0535: "do{}while(0) splits cse1 EBB"). If the s1ang load is in its own EBB (a loop block), then the value is live across the block boundary → global!

Yes! That's the trick: wrap the s1ang load (or the u6 computation) in a do-while(0), which creates a new basic block (loop_beg/loop_end notes), making the pseudo global. And a do-while with an empty body/condition compiles to nothing (no instructions) if the body is the load.

Wait, but the do-while(0) on the *cast* is already used as an anchor. We could add another do-while around the s1ang load:
```
do { s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12); } while (0);
```
This creates a loop block containing the load; s1ang is live out of the loop → global. The instruction stream should be unchanged (no extra instructions for do-while(0)).

Hmm, but does the loop block get optimized away (loop.c removes trivial loops)? The C0535 technique says do{}while(0) splits cse1 EBB and survives (used as a scheduling anchor). So it survives.

Let me test w5: wrap the s1ang load in do-while(0). Also keep the cast do-while.

Actually, wait: if s1ang is global with pri 2857, d (10000) wins $s0, then s1ang gets... it crosses a call, so it needs a callee-saved reg. Available: $s1 (if u6 doesn't take it first). u6 (r77) prefers s1ang's reg ($s1) → u6 gets $s1 too. And the target: s1ang raw and u6 both in $s1. 

But careful: global-alloc order: .greg order is by priority: r78 (30000), r80 (20000), r79 (17500), then r74 (d, 10000), r77 (u6, 10000), r76 (7142), r75 (s1ang, 2857). With s1ang global at pri 2857, it comes last. d gets $s0 (if no conflict). Then u6 (10000) gets... conflicts d ($s0), prefers s1ang's reg (which is not yet assigned). Hmm, u6 might get $s1 before s1ang, then s1ang prefers? s1ang has no preference; it would take the first free callee-saved: $s1 if u6 took something else, or $s2.

Order: r74 (d) → $s0. r77 (u6) → conflicts $s0, prefers s1ang's reg (unassigned) → gets first free: $s1? Then s1ang (r75) → conflicts? u6 (r77) conflicts r75? u6 is born from s1ang, so their live ranges overlap at the andi (s1ang dies there). So they conflict → s1ang gets $s2. That would be wrong (target $s1).

Hmm. Unless the tie/coalescing makes u6 and s1ang the same. In the target, `andi $17,$17,0x0fff` is in-place, so u6 = s1ang reg. That's local-alloc's tying (combine_regs) when both are local, or global-alloc's copy coalescing.

Hmm, in the target's pinned build, r75 (s1ang) was local (s1) and r77 (u6) global. u6 got $s1 because of the preference (r75 dies in the andi). So u6 took $s1 after local-alloc assigned r75 $s1.

If s1ang becomes global, the order matters. Let's just test it empirically. Maybe global-alloc's preference for u6 (prefer s1ang's reg) is resolved after s1ang is assigned if s1ang is allocated first. But s1ang pri 2857 < u6 10000, so u6 first. Hmm.

Unless we can raise s1ang's priority above u6 but below d. s1ang: 2 refs/7 → 2857. To get above 10000 (u6) but below d... d is capped at 10000 too. Hmm, priorities: d 10000, u6 10000, both at the cap. If s1ang > 10000... no, cap. Let me check the priority formula in global.c.

Actually, the "pri" in the table: d 9 refs/27 = 10000, u6 5/10 = 10000 (5*10000/10=5000, but shown 10000). Hmm, the formula must be different: pri = floor(10000 * refs * log2(refs) / live)? d: 9*log2(9)=9*3.17=28.5/27*10000 = 10570 → capped 10000? u6: 5*log2(5)=11.6/10*10000=11600 → cap 10000. s1ang: 2*1/7*10000 = 2857. Yes! Matches. So cap is 10000.

So d and u6 tie at the cap. Ties: "lower allocno wins" (global.c:607) — lower register number. d = r74, u6 = r77 → d wins. Good, d first.

Then u6 (r77, pri 10000): conflicts $s0 (d), prefers s1ang's reg. s1ang not yet assigned → u6 takes the first free: $s1. Then s1ang (r75) conflicts u6 → $s2. Bad.

To fix, s1ang must be allocated before u6. If s1ang's pri > u6's... but u6 is at the cap. Hmm. Could we raise s1ang to the cap too and rely on the lower-allocno tie-break? s1ang is r75 < r77, so it would win! If s1ang's pri reaches 10000, the tie goes to the lower allocno r75. But the .greg order is by priority then allocno? The table shows the .greg order: 78 80 79 74 77 76 — that's by pri descending (30000, 20000, 17500, 10000, 10000, 7142). Within the 10000 tie, r74 before r77 (lower allocno). So if s1ang (r75) is at 10000, the order would be ... 74 75 77 ... So d first ($s0), then s1ang (r75) gets $s1 (prefers? no, takes first free), then u6 (r77) prefers s1ang's $s1 → gets $s1 (if no conflict; but u6 conflicts s1ang? if they conflict, u6 gets $s2).

Hmm, does u6 conflict s1ang? u6 = s1ang & 0xFFF; s1ang dies at that insn. In global-alloc, live ranges: s1ang is live until the andi; u6 is born at the andi. They may be considered non-conflicting if the death and birth are at the same insn (the allocator allows the output to share the input's reg if the input dies). That's the copy/tying: local-alloc did it for r75/r77 in the target. In global-alloc, "conflicts" are computed per insn; an input dying at an insn and the output born at the same insn might still conflict unless there's a tie. Actually, global-alloc has `REG_DEAD` handling: the output can be in the same reg as a dying input if the insn allows (that's the `preferences`). The preference for u6 → 16 means it prefers s1ang's reg, and global-alloc checks if assigning u6 to that reg is legal (no conflict). In the target, u6 got s1ang's reg ($s1), so it's legal.

So if s1ang is global and gets $s1 first, u6 prefers $s1 and gets it legally. 

So I need s1ang's global priority ≥ u6's (10000) so that s1ang is allocated first (lower allocno r75 < r77 wins the tie). 

How to raise s1ang's priority? Priority = refs * log2(refs) / live * 10000. s1ang: 2 refs, 7 insns. To reach 10000: need e.g. 4 refs over ~... 4*2/8=1.0 → 10000. So 4 refs across 8 insns would give 10000. A do-while adds loop-depth weighting! Priority in global.c: `allocno_pri` uses `floor_log2(n_refs) * n_refs * size / live` and multiplies by loop_depth+1? Let me check global.c's `compute_reg_usage`/`allocno_priority`.

Actually the do-while trick (C0535) is used to raise refs: "div do-while (w5) lifts d's global-alloc pri 5185->12222". So a do-while adds refs (the loop back-edge test reads the variable). For s1ang, a do-while around the load might add refs.

But hold on: the do-while around the s1ang load: `do { s1ang = ...; } while (0);` — the loop condition is constant 0, so no refs added. Hmm, but the loop structure adds a loop_depth multiplier. Let me check global.c priority computation.

Let me look at global.c around line 607 and the priority function.
