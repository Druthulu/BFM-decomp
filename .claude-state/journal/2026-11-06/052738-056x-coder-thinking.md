---
ts: 2026-11-06T12:27:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EUPDy92bWQeU6qv3J7Qt
---
It needs a spliced TU file (.c). I'd need to write a TU with my candidate body spliced in — that's what --try does internally. I could do it myself: take the raw TU and splice the body (same as delever_search does) into a scratch .c under my dir, then run cc1_dumps_tu.sh with DUMP_ROOT under my shard dir.

That's a decent investment: ~2 commands. But is it worth it for a 2-point ORDER? If I can crack the barrier here, item 2 becomes PARTIAL:keepalive (score 0) instead of WALL. Worth ~5 min.

But wait — disk: "Disk is capped (~4 GB free): cc1 dumps go under your item dir and are deleted as soon as read". OK.

Let me do it: create two spliced TUs (b0 = barrier removed, and orig) under my item dir, dump both, and compare the pass where the order flips. Actually comparing two dumps' .sched/.sched2 sections is a lot of reading. 

Alternative cheaper experiment: check whether the flip is in sched2 by trying to defeat sched2 differently... hmm.

Actually, let me reconsider the problem. In mine: [lui v1][ori v1][sh y]. In target: [sh y][lui][ori]. 

What if the sh's address (q-10) computation and the lui/ori are ordered by the register allocator? In mine, v1 is used for the constant; in target too (142-143 lui v1). So the constant is built into v1 in both.

The difference is only the position of the sh relative to those 2 insns.

What if `y`'s value is in v0 and the sh at 143 is delayed by the load-delay slot? No.

Honestly: maybe the simplest real-C move is to make the y store depend on a load that happens later. E.g. write `*(s16 *)(q - 10) = D_801BB632 + 1;` inline — same.

Or: move `q[-7] = 0x38;` and `y = D_801BB632 + 1;` AFTER `*(s16 *)(q - 10) = y;`? No.

Try: put the y store before `q[-7] = 0x38;`? Target has sb at 136 before sh at 141.

Let me try a couple of statement orders where the sh moves up:
- s1: `*(s16 *)(q - 10) = y;` immediately after `y = D_801BB632 + 1;` — already the case.
- s2: in the j==0 branch too (`y = D_801BB61E - 2;` then the sh is after the if/else).

Hmm! Important: the sh is OUTSIDE the if/else (common tail). Both branches set y then jump to the join. So the sh is at the join. The lui/ori come after in C.

What if I duplicate the y store into both branches (store per branch — a move that cracked barriers elsewhere!)? Then the sh is inside each branch, before the join, and the lui/ori in the join can't move above it (different blocks). That's the "barrier->store per if-arm" move from moves.md!

But duplicating changes the code (2 sh's instead of 1)... unless jump2 cross-jumps them back into one. Risky, but it's a known cracking move. Let me try it: in each branch, after setting y, store it. Hmm, but then the join has no store.

Actually wait: the branches end with `continue` for the skip cases. Structure:
```
if (j == 0) {
    if (D_80115140[k] == 0) continue;
    q[-7] = 0x30;
    y = D_801BB61E - 2;
} else {
    s32 k2 = k * 2;
    if ((...)[k] < 7) continue;
    q[-7] = 0x38;
    y = D_801BB632 + 1;
}
*(s16 *)(q - 10) = y;
```
Duplicating the store into both branches = 2 sh's in the source; gcc's jump2 (cross-jumping) could merge the common tail. The target has one sh at the join (141), right after the addiu in the else branch... 

Hmm, target 137-141: lui v0,0x0; lhu v0,0(v0); nop; addiu v0,v0,1; sh v0,-8(a1). This is in the else branch (fall-through path) — the j==0 branch jumps to a common label? Looking at 134: `addiu v0,t0,1` in the delay slot of bnez (the j==0 path's D_80115140[k] != 0 check?). Hmm hard to say.

Let me just try the duplicated-store variant and measure.

Actually — I realize there might be a much simpler explanation: maybe the barrier's real job here is to prevent the *store* `*(s16 *)(q-10) = y` from being moved LATER (sunk below the lui/ori), and the way to prevent sinking is to make the store's address or value depend on something later. 

I'll try the duplicate-store approach plus a "store y via a temp used later" approach.

Given time, let me limit to 3 more tries for the barrier, then decide:
s1: duplicate the y store into both branches.
s2: move the y store into the branches but keep one at the join too? no.
s3: reorder: put `*((u32 *)ot) = 0x4000000;` BEFORE the y store (o3 was 12).

Let me do s1.

Actually hold on. Let me reconsider the whole item: with the barrier at 2 and the keepalive at 19, and my time at ~30 min... The task says a WALL needs ≥30 tries. I have: v0, b0, k0, p1-p5 (5), o1-o6 (6), q1,q2 (2), r1,r2,r4,r5 (4), v1 = ~21 tries. I need ~10 more.

Let me do the duplicate-store + a few statement orders, reaching 30, then record.

Hmm, but is WALL the right call for item 2? Yes if neither kind is fully cracked. But I should also check: can I get a PARTIAL by keeping the barrier and dropping the keepalive if I can fix the 19? No, 19 is the keepalive's cost.

So item 2 = WALL, best 21 (lever-free), tag: which? The mechanism for the barrier is "pure constant build hoisted above a store; only an asm barrier stops it" → tag `sched1-load-order`? Better: `cse-store-forward`? Let me look at walls.txt more fully to pick the best tag. Let me read the whole walls.txt (38 lines, fine).
