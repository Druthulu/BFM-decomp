---
ts: 2026-11-06T11:58:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iMDMp2MvjnMzj1tWSybe
---
e0 (all levers gone, dead resets in) = 53, 741 ins. Same as v3 (barriers gone, launders kept) — so the launders are fully cracked and the barrier removal costs 53.

Now let me look at e0's diff to understand the barrier's effect. v3's diff showed a2/a3 swaps in the FT3/FT4 arms. Let me get e0's diff around the y region.

The target's register grant: mny → $a2, my → $a3 (per the comment). Mine (no slider): swapped.

Idea: since the slider adjusts live lengths to force a tie, maybe a real-C change to the *declaration order* or *usage order* can flip the creation order. The comment says: "exact allocno tie -> global.c allocno_compare falls through to creation order -> mny (created first) takes $a2". 

Wait — creation order: mny created first? The declarations are `s16 my, mny, mx, mn;` — my is declared first. Hmm, "mny (created first)". Maybe the allocnos are created by first *use*/set in the RTL: in the then-branch, `my = y0` comes first, so my's allocno is created first... but the comment says mny is created first. Hmm, maybe in the else branch order. Whatever.

If the tie is exact, creation order decides. So if I can make the tie exact via a real-C live-length change, it works.

Real-C options to change L_my by 2:
1. Move the `my = y0;` assignment two insns earlier (e.g., before the if). But the if condition uses the loaded values.
2. Add a use of `my` 2 insns after its set.

What about restructuring:
```
if (((XFT3 *)pkt)->y0 > ((XFT3 *)pkt)->y1) {
    my = ((XFT3 *)pkt)->y0;
    mny = ((XFT3 *)pkt)->y1;
}
```
→
```
s16 t = ((XFT3 *)pkt)->y0;   /* extra live value */
if (t > ((XFT3 *)pkt)->y1) {
    my = t;
    mny = ((XFT3 *)pkt)->y1;
}
```
This changes the code (extra load/copy). Hmm.

What about lengthening my's range by using it in the mny assignment: `mny = ((XFT3 *)pkt)->y1;` → 
```
mny = ((XFT3 *)pkt)->y1;
my = my + 0;
```
no.

Hmm, what about the *other* arm (the else)? The slider is only in the then-branch. The live range of my spans from the then-branch assignment to the later uses; in the else branch, my is set later. global.c uses the *maximum* over the flow graph? Liveness is per-insn.

Real C idea: move the `if (y2 > my) my = y2;` line? It's after.

Let me look at what the two extra insns do in the target. The target has 2 extra zero-byte insns → L_my is 2 longer. A real-C way to extend my's live range by 2 insns *without emitting code*: 

What if `my` is used in the *comparison* `if (my >= -0x6E && mny < 0x6F)` — that's the next use (after y2 handling). To extend, the value must be used between.

What if we compute `my` from a slightly different expression that keeps it live: e.g. `my = ((XFT3 *)pkt)->y0;` then `mny = ((XFT3 *)pkt)->y1;` — the load of y1 is between. So L_my includes the y1 load.

Hmm, what if we load y1 into a temp first:
```
s16 t1 = ((XFT3 *)pkt)->y1;
my = ((XFT3 *)pkt)->y0;
mny = t1;
```
That's an extra copy (but maybe coalesced).

Alternatively: make the then-branch compute mny via a *different* expression that's 2 insns longer? No, adds code.

Hmm, what about using `my` in the y2 comparison earlier? 

Honestly, this looks like another global-alloc tie that needs zero-byte padding. Let me try a few real-C permutations quickly and see if any hits 0.

Let me look at the target's code first to know what we need. Let me dump the target region: search the target disassembly for the FT3 y-handling. The target function is 741 insns. Let me find `-0x6e` (0xffffff92) in the disassembly.

Actually, easier: let me get e0's diff (the region with a2/a3 swaps) and see how many insns differ.

From v3's diff: the swaps start at mine[76] (move a3,v1 vs move a2,v1) and run through mine[94]. That's ~10 insns of register swaps, then at [380] swc2 s5/s6 swap, then [425] some reordering.

That's a lot of differences from a single register grant.

Hmm, but the comment says the slider fixes exactly this ("+2 here lands int(K/L_my) on int(K/L_mny) -> exact allocno tie").

Let me try real-C moves that extend my's live range by 2:
1. Move the y2 update `if (y2 > my) my = y2;` before the mny assignment? Semantically wrong? No: the y2 max is applied after both. Moving it before mny's assignment... it depends only on my and y2, so it's fine. But it would add the y2 load before mny's — changing code order.

2. Compute mny first, then my:
```
if (y0 > y1) { mny = y1; my = y0; }
```
This extends... my is set last, so its live range is shorter. No.

3. `my = y0; mny = y1;` → `my = y0; if (my == 0x7FFF) mny = 0; mny = y1;` — adds a branch.

4. Use a comma expression: `mny = ((XFT3 *)pkt)->y1, my = my;` no.

5. Change the type: `my = (s16)(((XFT3 *)pkt)->y0);` — an extra cast might add insns.

6. Make the load of y1 go through a variable: `s16 t; t = ((XFT3 *)pkt)->y1; mny = t;` — probably coalesced, no extra insn, but adds a pseudo with a live range that might change the allocno priority of *t*, not my.

Hmm, what about the liveness of `my` being extended by the *else* branch? In the else, my = y1 is set after mny = y0. Hmm.

Let me look at the actual target code. Let me find the region in the target disassembly: search for the "y0 > y1" compare in the FT3 arm. The FT3 arm is after the switch on code 6/7. Let me find `slt`/`beq` patterns... 

Simpler: use the diff from e0 with a big tail to see all mismatches, and pick the register-swap region. Then map to the C.

Given time, let me try a batch of real-C ideas and score. I'll do ~8.

Idea list for the FT3 arm:
- f1: swap the two assignments in the then-branch (mny first, my second).
- f2: hoist the y0/y1 loads into temps before the if.
- f3: compute my = y0; mny = y1; with a temporary for my used later.
- f4: reorder the else branch.
- f5: use `my` in the y2 comparison expression order.
- f6: change the declaration order of my/mny in the function (s16 mny, my;).
- f7: same for the FT4 arm.
- f8: reorder `if (my >= -0x6E && mny < 0x6F)` → `if (mny < 0x6F && my >= -0x6E)`.

Let me apply these to e0 (all levers gone + dead resets) and score.

Note: the two barriers are in both arms (FT3 and FT4). Let me handle both.

Let me write the generator carefully.
