---
ts: 2026-11-06T16:31:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l3R0FXL0fL3gVLcKjazz
---
For unconditional jumps: find_cross_jump(insn, JUMP_LABEL(insn), 1) — compares insns before the jump with insns before the label. Then tries other jumps to the same label.

In our case, both blocks end with `j ret_label` (jump to 0x554). find_cross_jump(jumpA, ret_label, 1): i1 = prev_nonnote(jumpA) = move a0,zero; i2 = PREV before ret_label = prev of 0x554... ret label 0x554 is preceded by `j 554` from block B (0x1b8) or by other jumps. Hmm.

Anyway, empirically the merge happens without the asm and not with it. So the asm is load-bearing via being an RTL insn.

Real C replacement that emits a zero-byte RTL insn... Actually, wait: maybe a *different* real-C structure prevents the merge, e.g., writing the second block's `goto ret` as a *fallthrough* to a different label, or reordering so the two blocks are not both followed by jumps.

Alternative real-C: make the two call blocks genuinely different in bytes but compensate elsewhere? No, must be byte-identical to target.

Alternative: make the first block end by falling through (no jump) into `ret:` while the second jumps. Then blocks differ (one has j, one doesn't) but the target has both j's. No.

Hmm, what about using `switch`/`case` fallthrough? no.

Let me step back. Maybe the barrier isn't the only way: cross-jump compares hard registers after reload. What if we make one block use a different hard register for an argument that is 0? Impossible with constants.

What if one block calls a *different but equivalent* function? No.

Therefore the barrier's role (block jump2 merge) has no plain-C spelling → this is the wall. Combined with keepalive (expand-void-return) and pin (register), item 1 is a WALL.

But before declaring, I must do ≥30 scored tries and ≥20 min. Let me construct ~30 real-C variations and score them in batches. The variations can combine:
- barrier removal variants: reorder calls, split statements, do-while, structured if/else, goto placement, duplicate tails, etc.
- keepalive: (void)v0r, if(v0r), v0r = 1 then use in comparison, return-type cast, etc.
- pin: decl order, scope, i/v0r reuse.

But honestly the item will end WALL. The best score lever-free is what matters. Let me aim to lower w1's score. The 19 from the barrier dominates. If we can't crack the barrier, the best lever-free is ~20 (w1). Actually we can also keep the pin? No — lever-free means all three gone. w1 = all three gone, score 20. Maybe we can improve the pin residual and keepalive to get 19 or 20.

Wait: w1 = 20 = barrier(19) + keepalive(1) roughly. Can we get the register right without the pin in the lever-free body? In w1, v0r=1 is dead so no register issue. Score 20 = 19 (merge) + 1 (missing li). So best lever-free = 20 unless we crack the barrier.

Let me still try a bunch of real-C moves to reduce. If the merge can be prevented by a real-C construct, score would drop to 1.

Ideas to prevent jump2 merge with real C:
(a) Reorder the two call blocks so they're not identical: e.g., in the second block, move `func_8002D8D4();` before `func_800468FC();`? That changes byte order → target differs. No.
(b) Put a label between the calls in one block that is actually referenced by a *backward goto that jumps to it* — emits j. No.
(c) Use `if (func_800D2454(...) != 0) { ... } else { ... }` restructure. Hmm.
(d) Use a `for(;;)` with break? no.
(e) Make one of the calls' return value used: e.g., `i = func_800D2D44(0);` — func_800D2D44 returns void per decl. No.
(f) Use different zero spellings that differ in RTL: `func_800D2AA0(0)` vs `func_800D2AA0((u8*)0)` — both const0. But what about `func_800D2AA0((u8*)(0L))`? same.
(g) Different but equivalent argument for func_800D2AA0: it takes u8*, 0. Could pass `p - p`? That computes p-p → 0 but emits instructions (subu). No.
(h) `func_800D2AA0(&D_800EC9A4[0] - ...)` no.

So no.

Alternatively, could cross-jump merge be prevented by the *preceding* conditional jump structure? find_cross_jump for unconditional jump A compares backwards from A's j and from the ret label. The "give up if we find a label in stream 1" — stream 1 is the insns before jump A. If there were a referenced label *inside block A*, it stops. Can we place a referenced label in block A without emitting a jump? Yes! A label referenced by a `goto` that is *optimized away*... e.g., a `goto L` where L is the next statement gets deleted by jump1 (jump to next insn removed). But then LABEL_NUSES drops to 0 and the label is deleted. Hmm.

What about a label referenced from a `switch` that jump1 collapses? Same.

What about a label whose address is taken (`&&L` GNU extension / computed goto)? Address-taken label → emits `lui/addiu` of the label (bytes). No.

Hmm, what about a label used by a `goto` from a *dead* branch that fold removes? Same deletion.

OK, barrier is a genuine wall: jump2-crossjump (existing tag! "jump2-crossjump-arms — cross-jump merges byte-identical switch/if arms"). Great, that tag fits exactly.

So item 1 WALL tag: jump2-crossjump-arms for the barrier; but the WALL line records one tag. Hmm, the item has three levers; the WALL tag should be the dominant mechanism. I could use `jump2-crossjump-arms` or `expand-void-return`. Which is the binding one? Even if we cracked the barrier, the keepalive remains. The "best" body has all three gone; the wall is the combination. The results.tsv has one wall column. I'll use `jump2-crossjump-arms` if the barrier is the biggest residual (19 vs 1), and mention the keepalive in evidence. Actually maybe better: `expand-void-return` since that's a fundamental non-C (park) signal. But the barrier also has no C spelling. Hmm.

Let me continue experimenting; maybe I can get the barrier merge prevented by something unexpected. Also let me check: does the barrier's absence affect anything else besides merging? w3 score 19 = 11 insns missing + j target shifts. The 10-ins difference is the merged block. So yes.

Let me now run ~30 tries for item 1. I'll write a script to generate candidates? The brief says scripts under .run, not inline python -c. I can use a bash loop with sed. Let me create candidate files and score them in one sc.sh call (one line per candidate).

Candidates for item 1 (all lever-free, i.e., no pin/barrier/keepalive):
1. w1 (baseline lever-free): 20
2. v0r as `volatile s32` — no, volatile changes code. Try anyway? It'd add a store.
3. `(void)v0r;` instead of keepalive: v0r = 1; (void)v0r;
4. `if (v0r == 1) {}` 
5. `i = v0r;` then use i in the loop? changes.
6. `v0r = func_80010A98();` — no.
7. Remove v0r entirely (just no assignment): score 20 presumably (same).
8. Reorder the 4 calls in block 1 (to try to make it non-identical with block 2 — but target order matters; if I reorder block1, target order breaks → worse but let's see if merge stops; the score would include the reorder cost).
9. Make block1's func_800D2AA0 arg `0` and block2's `0u`? same.
10. do-while around block1's calls (C0535 EBB split) — jump2 is post-reload, CFG-level; unlikely but try.
11. Split the first block into two statements groups with an `if (p[1] || 1)`? no.
12. Write block1 as an if/else with the calls in the else arm? no.

Also for the pin residual (w4, 1): try real C to get v0. E.g., declare `s32 v0r` and assign it from a *call* — no. Or make v0r the last loop-carried? Hmm.

Honestly, item 1 WALL. Let me spend the required effort: 30 tries. But 4 items in 2 hours... Let me timebox: item1 25 min, then others.

Actually, let me reconsider the overall task: 4 items, each needing ≥30 tries for a WALL. That's a lot. But maybe some are crackable quickly (MATCH). Let me look at item 2 (launder only), item 3 (pin only), item 4 (keepalive,launder) — single-kind items are more promising.

Let me peek at items 2-4 targets and current scores quickly to plan. Actually the brief says don't stop between items; work sequentially. But planning helps.

Let me first finish item 1's required effort. I'll generate candidates systematically.

Actually, wait. Let me reconsider the barrier. The barrier `__asm__ __volatile__("")` is an empty asm. What real-C emits a zero-byte RTL insn? A `volatile` read of a memory location... emits a load. What about `__builtin_...`? Not available.

Hmm — what about a *label* at the end of block A that is referenced by the target of the second `if`? No.

What about making the second block a `goto` target used by both ifs? That would merge them in source → one copy in target? No.

What if the two blocks differ in *source line* only? Line notes don't affect cross-jump (they're notes, skipped).

OK so barrier wall confirmed.

But hold on — maybe the real source didn't have identical blocks; maybe the two `func_800D2AA0(0)` calls differ in the source as `func_800D2AA0(0)` vs `func_800D2AA0((u8*)0)` and gcc's `rtx_renumbered_equal_p` treats `(const_int 0)` vs `(const_int 0)` same. Yes same.

What if one block's `func_800D468FC()` call is spelled via a different prototype (K&R with extra args)? Same RTL.

OK. Let me do the 30 tries. I'll build a set of candidate files programmatically with sed from w1.

Plan candidates (each all-levers-gone):
c01: w1 (done, 20)
c02: no v0r at all (delete declaration + assignment)
c03: v0r = 1; (void)v0r;
c04: v0r = 1; if (v0r) {}
c05: v0r = 1; i = v0r; (i declared; dead)
c06: v0r = 1; i = v0r; ... use i nowhere
c07: v0r = 1; if (v0r != 0) {}
c08: v0r = 1; switch(v0r){case 1: break;}
c09: do{v0r=1;}while(0)
c10: i = 1; (use i instead of v0r, i is used in loop! `i = (D_800EC9CC == 0);` in loop — after loop i unused; assigning i=1 at end is dead)
c11: block1 wrapped in do{}while(0)
c12: block2 wrapped in do{}while(0)
c13: both blocks wrapped
c14: block1 calls reordered (8002D8D4 before 800468FC)
c15: block2 calls reordered
c16: block1 with func_800D2AA0(0) written as func_800D2AA0((u8 *)0)
c17: block2 with func_800D2AA0((u8 *)0)
c18: block1: separate declaration of calls? 
c19: first if written as `if (!(func_800D2454(...) == 0))`
c20: second if `if (!(func_800D2704(...) == 0))`
c21: first if with `!= 0` and second with `> 0`
c22: use a temp for func_800D2454 result
c23: use a temp for func_800D2704 result
c24: block1's goto ret → fallthrough into ret? (remove goto, reorder)
c25: convert the two ifs into if/else chain
c26: swap blocks order
c27: v0r declared after i
c28: v0r declared inside a block scope at the end
c29: p declared as s32* vs s32 array
c30: i/v0r reuse: use `i = 1;` at end and delete v0r
c31: `v0r = 1, v0r;` comma
c32: `return;` at end (no v0r)
c33: label ret with `v0r=1` before label
c34: `v0r=1; goto ret2; ret2:`

Let me create these. Many will be identical scoring. Let me write a bash script under .run to generate them. Since each candidate is a small edit from w1, I'll use sed/awk carefully.

Actually simpler: write a python script under .run/P40/T11/W47/<item>/gen.py that emits candidates. Python scripts are allowed (tools/run.sh not needed for small output; but "Scripts, not inline python -c"). Let me write gen.py.

Hmm, but careful: the rule "write only under .run/P40/T11/W47/" — yes.

Let me write gen.py for item 1.

Actually, maybe more efficient: I'll hand-write the variants as separate files using a here-doc via Write tool? That's many writes. A generator script is better.

Let me get w1 content to build variants. I have it. Let me write gen1.py.

Actually, let me reconsider time. 4 items × 30 tries = 120 compiles ≈ 5-8 min of compute if batched. The time is dominated by my thinking/editing. I should be systematic and fast.

Let me write gen1.py producing ~30 variants from w1 (which is lever-free). All variants must remain lever-free (no asm/register).

I'll structure w1 as text and do replacements.

Let me view w1 to know exact text.
