---
ts: 2026-11-06T15:59:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zWCijgG3B6GWfkLKBWxB
---
m1: 39 (same as c3) — the copy didn't prevent the unification. m2: worse (369 ins).

Hmm, m1 gave 344 ins, same as c3, so the n2 copy was coalesced but cse still unified? Or the replace didn't work as intended (the second occurrence might be inside a different context). Score 39 same.

Time: 09:00. Item 4 ~13 min. Tries: 31+2 = 33. Need 20 min. Let me do a few more.

Let me reconsider the arg launder one more: the vh1 approach fixed the la position but broke the spill order (score 12). What if I combine vh1 with a different arrangement to fix the spill order? The spills' order in the target: s4, s3, s7, s2, s5, s6 — this corresponds to the *register allocation* order, not source order. In vh1 the allocation order changed because the call moved. Hmm.

Actually, the target's prologue spills are emitted by the compiler in a fixed order based on the registers used. The interleaving of `sw sX` with `lui sX` is the scheduler's placement. In vh1, s7/s2/s6 spills moved later because their definitions moved after the call. The target has them before the call. So moving the call early is wrong.

So the arg launder can't be replaced.

I'll wall item 4. Let me spend the remaining ~6 min on a final check of the wall evidence and then write everything. Actually, I can also just wait by doing useful verification. Let me count tries precisely and prepare the WALL row.

Best lever-free = c1 = 43. Wall tag: the two mechanisms are different:
- arg launder: combine-argcopy-sink / sched1-argcopy-hoist.
- 2-output: jump2-crossjump-arms / flow-known-value.

The brief says a WALL gets ONE tag from walls.txt or a new `<pass>-<what>`. I'll pick `combine-argcopy-sink` (defined in moves line 69) — but is it in walls.txt? No. walls.txt has `sched1-argcopy-hoist`. For the 2-output, `jump2-crossjump-arms` is in walls.txt.

The dominant residual (c1 score 43) is the cross-jump merge (39 of the 43 points?) plus the la position (4). I'll use `jump2-crossjump-arms` as the tag and mention both mechanisms in evidence? Evidence ≤140 chars.

Hmm, actually the best lever-free body c1 (all launders gone) scores 43: the 2-output removal accounts for 39 and the arg for 4. The tag `jump2-crossjump-arms` describes the main one.

Let me verify the c1 score breakdown: c2 (arg removed) = 4; c3 (2-output removed) = 39; c1 (both) = 43. 39+4=43. Consistent.

Let me also check: is there a tag combining? I'll use `jump2-crossjump-arms` and note the argcopy in evidence.

Wait — the brief says "wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". `jump2-crossjump-arms` is in walls.txt. Good.

Evidence: "jump2 cross-jump shares the two if(n<4) tails (344 vs 346 ins); asm 2nd-set of n/otz was the only split; arg la also combine-argcopy-sink (la late)" — ≤140 chars. Let me count later.

Now, the results row for a WALL: `dir file func kinds result best tries wall evidence`; result WALL; best = 43 (lowest lever-free score); tries = number of scored tries; wall = tag; evidence = gcc pass + mechanism.

Let me count the tries exactly. Variants scored:
c1, c2, c3 = 3
va1, va2, va3 = 3 (6)
vb1..vb4 = 4 (10)
vc4, vc5, vc6 = 3 (13)
vd1, vd2, vd3 = 3 (16)
ve1, ve2, ve3 = 3 (19)
vf1 = 1 (20)
vg1 = 1 (21)
vh1 = 1 (22)
vi1, vi2, vi3 = 3 (25)
vj3, vj4, vj5, vj6 = 4 (29)
vk2, vk3 = 2 (31)
vm1, vm2 = 2 (33)
Plus orig baseline (not a try). So 33 tries.

Time now ~09:01; started item 4 at 08:47 → 14 min. Need 20 min. Let me do a few more genuine attempts while waiting.

Let me try the 2-output crack via a *different* mechanism: what if the two tails' `if (n<4)` blocks are made non-identical by using a different *call result* handling in one? e.g. in the LINE tail, `q = func_80010A08(8);` vs `qt`... no.

What about the `#line 900` placement: what if we put `#line 900 "p.c"` only on the first tail and `#line 901 "p.c"` on the second? Without asm, no effect (tested vf1 removal).

What if we add a *zero-byte* real statement that produces a NOTE? no.

Let me try: in the LINE tail, swap the order of two independent statements, e.g. `otp = (u32 *)(otz << 2); otp = (u32 *)((u32)otp + ot);` — the target has this order. If swapped, the code might still fold to the same (combine). Probably same.

Let me try swapping the `tp` chain statements in the LINE tail: `*(u32 *)(q + 4) = tp;` before `qt = *(u32 *)q;`. That changes the RTL order (a store before a load) → different block → maybe no cross-jump, but the target's LINE tail has the same order as POLY (qt load then store). If the order differs, the LINE tail's code differs from the target. Unless combine/sched reorders back. Risky but let me test: it might be that the target's LINE tail differs in some subtle way we haven't noticed.

Actually, let me diff the target's two tail bodies directly. Let me extract the target's two `if(n<4)` blocks and compare their insns. The first at ~287, the second at ~299. Let me look at target insns 287-340 and find both blocks.
