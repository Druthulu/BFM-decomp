---
ts: 2026-11-06T10:16:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zpGQqvgN9Cm8sDKOfRiR
---
Item 4 pin-only = 7 (same as lever-free). So the keepalive is what matters (it changes the i1/giv allocation), and the pin forces f=v1.

- Lever-free: 7
- keepalive-only: 10
- pin-only: 7
- both: 0

So both levers needed → PARTIAL:keepalive,pin.

Now, let me try a bit more to crack item 4: I need f to get v1 without the pin. The keepalive gives i1 a higher priority and makes it take v1... wait, with keepalive-only, the order was i1→v1, giv→a0, f→a1. Target: f→v1, i1→a0, giv→a1.

Hmm, in keepalive-only, i1's priority (22500) is highest. If i1 could conflict with v1, it would take a0, then giv (14000) conflicts v1? It did in the pinned version. Circular.

What if we add a *second* keepalive-like real use to f... no asm allowed.

What if f is read inside the loop such that its refs rise above i1's 22500? f needs refs such that pri > 22500. live ~16. floor_log2(r)*r/16*10000 > 22500 → floor_log2(r)*r > 36. r=9: 3*9=27 <36. r=12: 3*12=36 → not >. r=13: 3*13=39 >36 → pri = 3*13/16*10000 = 24375. So f needs ≥13 refs (with live 16). That's a lot.

Alternatively, reduce f's live length: if f's live were 8 with refs 8: 3*8/8*10000=30000 > 22500. So a shorter-lived f with more refs could win. But f's live spans the loop.

Hmm, what if the `f != 1` test is moved INTO the loop region? No.

What if the flag is computed in the loop and read immediately after, but f's live length is the loop length (~10 insns)? f is live from `f=0` (before the loop) to the read after. If we remove the `f = 0` before the loop and instead initialize f inside... e.g.:

```
for (i1 = 0; i1 < 5; i1++) {
    if (i1 == 0) f = 0;
    if (cond) f = 1;
}
```
That adds code.

Hmm.

What if we use `s32 f;` and set it to 0 via the loop: no.

OK, let me try a different angle: reduce the *giv's* priority below f's 5000 by extending its live range. The giv r234 live 9. If its live were 30, pri = 2*7/30*10000 = 4666 < 5000. But also i1 (22500 with keepalive, or 12727 without) would still beat f.

Without the keepalive (lever-free), order: giv(15555) > i1(12727) > f(5000). If the giv's pri drops below 12727, i1 takes v1, then giv a0, f a1. Still not target.

We need BOTH i1 and giv out of v1. If i1 and giv conflict with v1, they skip it. The conflict arises only if something occupies v1 across the loop.

What if f is *not* the v1 occupant but a *local* temp is? If a local temp in v1 is live across the loop, i1 and giv conflict with v1. Then i1→a0, giv→a1, and f (last)→v1. That's the target!

How to get a local temp in v1 across the loop? Local-alloc assigns block-local pseudos within a block. A value computed in the loop block before the loop's first use and used inside... Hmm, the loop body is one block? The loop is: label, lw, lhu, bne, li, addiu, slti, bnez. Block-local temps: r174 (lw), r176 (lhu), r169 (slt). All in v0 sequentially.

If we add a temp that's live from the block start to the block end, local-alloc might put it in v0 (first free). To force v1, v0 must be taken by another temp at the same time.

Hmm, what if the loop body computes two things that are both live: e.g., `s32 a = *(u16*)(p+2); s32 b = a + 1; if (b == 6) f = 1;` — the temp a would be in v0, b in v1? That adds instructions though.

This is really the greg-pri wall.

Let me now consider: is 7 the best lever-free score? Yes among what I tried.

Decision: item 4 → WALL or PARTIAL? Since win.c=orig scores 0, PARTIAL:keepalive,pin is valid. But hmm, the "best" column for PARTIAL should be the lever-free best (7).

Hmm, actually, wait. Let me reconsider the results format: `dir file func kinds result best tries wall evidence`. For MATCH, wall `-`. For PARTIAL/WALL, wall = a tag. So PARTIAL:keepalive,pin with wall tag e.g. `greg-pri-refs` or `lreg-v0-local-first`.

For items 1-3: wall tag `expand-void-return` (from walls.txt? let me check).

Let me read walls.txt to get the tags.
