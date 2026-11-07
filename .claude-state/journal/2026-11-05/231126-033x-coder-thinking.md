---
ts: 2026-11-06T06:11:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7VidKxqT6KAT5Ab7X5cd
---
So each reference adds 1 + loop_depth. And live_length is counted per insn where the reg is live.

For a pseudo in a loop, live length counts static insns. pp: set before loop (live_length +=1 at set), and live across the loop body from the set... Actually live_length counts the number of insns the reg is live in, statically. pp: live from its def to its use in the loop: since the use is inside the loop and the def outside, pp is live across the loop header and body → roughly 20-30 insns.

zpush: live from def to last use in loop2 → ~120.

Refs: pp = 2 refs: def (loop_depth 0) +1, use in loop1 (depth 1) +2 → 3.
zpush = 3 refs: def +1, use loop1 +2, use loop2 +2 = 5.
pp priority: floor_log2(3)=1 → 3/len_pp.
zpush: floor_log2(5)=2 → 10/len_zp.

len_pp ≈ ? pp def at 16, last use at 3010 (insn 51ish) but live_length is static count of insns where live. pp is live from 16 through 51, but in a loop, is live_length counted per insn once or weighted by loop? Let me check: live_length computed in `flow_analysis` per block using reg_next_use; for loops it's static (each insn once). Actually there's also `REG_LIVE_LENGTH` incremented in loops... Let me check lines 2100-2200 maybe "loop_depth" weighting for live length.

Given both mine and target produce nearly the same structure, I need pp's priority to exceed zpush's.

Compute: suppose len_pp = 30, len_zp = 120: pp=3/30=0.1; zpush=10/120=0.083 → pp wins. But observed zpush wins, so len_pp must be > 3*120/10 = 36. Hmm. pp's live length maybe includes the loop counted once but spans from 16 to 51 = ~35 insns + the block... 

So pp needs +1 ref → 4 refs: floor_log2(4)=2 → 8/len_pp. If len_pp=38: 8/38=0.21 > 0.083. Wins decisively. 

So: add ONE ref to pp (any depth) — but it must not add an instruction.

Where can a ref be free? A use that folds into an existing instruction's addressing. pp is a pointer to s32; `*pp` is `p` (a scalar local). Hmm, what about `*pp = *pp` — cse kills.

What if instead we reduce pp's live length: pp's live length is long because it's live across the entire loop. If pp were set *inside* the loop each iteration (pp = &p in the loop), it'd be local-alloc, and the insn would repeat (target has one addiu).

Hmm, what about making `pf` absorb... no.

Another idea: change `zpush` to be computed from `arg0` *inside* each loop with a separate variable, but the target has one lh. No.

OK so let's find a free ref for pp. Think about how expand handles `RotTransPers4(v0p,v1p,v2p,v3p, &q->xy0, ..., pp, pf)`. Args 5-8 are stack: sw at 16..28; args 9-10: sw at 32, 36. Those are the arg values.

What if the call took `pp` twice? no.

Alternative: use pp in a dead-but-not-deleted computation that folds. E.g.:

```
s32 *tmp = pp;
... use tmp?
```
Copy → coalesced (same pseudo), no new ref for pp but tmp gets refs... Actually a copy `tmp = pp` creates a new pseudo tmp with a ref; cse/combine may coalesce, but at flow time both exist: pp gets +1 ref (the copy's source)! And tmp gets refs. If tmp is used in the same place as pp (e.g. pass tmp to the call instead of pp), then pp: def + use(copy) = 2 refs, tmp: def + use(call) = 2 refs. Hmm that splits, not adds.

But what if tmp is used somewhere that folds into an existing insn? E.g. `s32 *t2 = pp;` then pass `t2`? Then pp has 2 refs (def, copy) and t2 has 2 (copy, call use). Both lower than 3. Worse.

What about `pp` used in an expression that folds: e.g., in the loop, `v0p = (s32)pa;` → could write `v0p = (s32)(pa + (pp - pp))`? cse folds.

Hmm.

Different approach: give zpush *more* refs so it gets a higher priority and takes a *different* reg... no, we want zpush in fp ($30) which is allocated LAST (fp is the last callee-saved). Wait, actually allocation order: regs $16..$23, then $30(fp)? In gcc 2.7.2, the callee-saved set is s0-s7 then fp. The allocno order is by priority: highest priority gets the first available register. The order of assignment: iterate allocnos by sorted priority; for each, pick best available reg.

Mine: pf got s6, zpush s7, pp fp. Target: pf s6, pp s7, zpush fp. So pf highest, then the next highest gets s7.

Wait, but why does pf get s6 and not s7? Because when pf is allocated first, s0-s5 are taken (by s0..s5 pseudos) so s6 is the first free → pf=s6. Then the next allocno gets s7. So we just need pp to be allocated *before* zpush.

So: increase pp priority above zpush, or decrease zpush's below pp.

Ways to decrease zpush without changing insns:
- Make zpush's refs at depth 0? Can't; uses are in loops.
- Lengthen zpush's live length: live_length counts insns where the reg is live. If zpush's def moves earlier (more insns before the loop where it's live), live grows. But its def is at 22 and the loop starts at 22. Could we move the `lh` earlier — e.g. before `func_8012E32C()`? The load from arg0 could be hoisted: `zpush = ((Unk*)arg0)->unk6;` before the call. But target has it after the call... and that would change insn order (mismatch).

Hmm! But wait: what about *splitting* zpush's use in loop 1 to a different variable? `zp1 = zpush;` used in loop1, zpush in loop2? That adds a copy insn unless folded. If `zp1 = zpush` is a move, it might be coalesced by cse/combine... and then no change.

Alternatively: could we make zpush a **s16** so the `lh` result is HImode and gets a SUBREG? no.

Let me try the empirical batch: several cheap variants, score each. Let's list:

v1: `pp = &p;` written as `pp = (s32 *)&p;` — same.
v2: declare `s32 *pp = &p;` at decl (init at decl) — changes order.
v3: wrap `pp = &p;` in do-while(0).
v4: add a dead-reset `pp = 0;` after loop1? (C0414)
v5: `zpush` computed as `((Unkstruct*)arg0)->unk6` into `s16 zpush` (width change).
v6: use `*pp` somewhere free? Hmm.
v7: make the loop-1 `func_8012E28C(otz, zpush)` use `(s32)zpush`? no.
v8: reorder: set `pf` before `pp`? changes order (target s7 then s6). no.

Another thought: what if we add a **third** pointer variable that folds? e.g. `s32 *pq = &p;` unused → dead code deleted.

Hmm, what about the trick where a variable is used in an address computation that folds into an existing offset: e.g. in loop 2, `(s32)&pa[i]` — target: `sll a0,s2,3; addu a0,s5,a0`. If we wrote `(s32)(pp - 5 + i)`? no.

OK here's a cleaner idea: **shorten pp's live length** by moving its def later — but target order is addiu s7,sp,40 at position 16. What if pp's def moves later but the *insn position* stays? Not possible.

Alternatively **lengthen pp's live range at lower cost**? That lowers priority.

Alternatively **increase pp's refs** by adding a second use that folds: `pp` is `s32*` pointing to `p`. What if we pass `pp` as the arg for `&q->xy0`? no.

Hmm, what about making the *stack stores* of args 9/10 use `pp`/`pf` naturally: they already do.

Let me look at this from a different angle: maybe I can restructure so that pp/pf aren't needed as separate variables at all — e.g. declare `s32 *pp` and `s32 *pf` but pass `&p, &flag` directly and use pp/pf for something else? Then the addresses would be rematerialized.

Alternatively: merge pp and pf into one variable? Target has both.

What if the *live length* difference comes from where pp's def sits relative to pf's? Both same.

Let me just get the numbers. I'll create a spliced TU and dump. Actually simpler: `delever_search.py --try --keep` prints the candidate object path; then I can... no, dumps need cc1.

Plan: build a scratch TU by copying src TU and replacing the function text with my candidate. Then run cc1_dumps_tu.sh on it with DUMP_ROOT under my item dir. Then alloc_table.py. Then delete the dump dir.

But note: the TU is 7213 lines; copying is fine (small).

Actually — does the TU include the function more than once? The extract found the definition at 4904. I'll splice by line range.

Let me write a splice script.

Actually, maybe there's an easier path: `tools/cc1_dumps_tu.sh` accepts "the first argument may also be a .c FILE (an agent's spliced TU, a --try scratch copy)". So I need a .c file with the function replaced.

Let me write splice.py under my shard: given src TU, func name, body file, out .c: replace the definition lines with body content.

Then run cc1_dumps_tu.sh with DUMP_ROOT=.run/P40/T11/G23/<itemdir>/dumps? The script: d=${DUMP_ROOT:-.run/P32/t4e}/dumps_$tag. So set DUMP_ROOT=.run/P40/T11/G23/<dir>/dump and it creates dump/dumps_<tag>.

Then alloc_table.py <tag> [fn] [dump_root].

Let's do it. But first — is this worth it? The alternative is 10 blind tries. The dump gives exact numbers. Let's do the dump once for w0.c (or for orig.c to see the pinned baseline) — better: dump orig (target structure) and w0 to compare priorities. But orig has pins (hard regs), priorities differ.

Let me just dump w0 and see pp vs zpush numbers, then decide the delta needed.

Actually — important: I realize there might be a much simpler explanation. In target, pp is set with `addiu s7,sp,40` — but wait, pp is pinned to $23 and pf to $22. In the target build, the pins force these. The target's *unpinned* structure isn't known; we're matching the pinned build. So we need pp to win $23 naturally.

Let me do the dump.

Time check: started 23:05. Now maybe 23:20. Budget 20-30 min per item. I've used ~15 on item 1 (including reading). Let me be efficient.

Let me write splice.py and dump.
