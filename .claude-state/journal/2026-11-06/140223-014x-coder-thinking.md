---
ts: 2026-11-06T21:02:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_m67c1MozEzj31SllG9i4
---
Line 316 is very relevant: func_8012BB3C "keepalive,pin WALL lreg-qty-priority — C0535 do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0) and a 2nd do-while on the cast block replaces the keepalive ang anchor". So `do{}while(0)` is a known technique for keeping refs (C0535). But note: "do{}while(0) only with // !FAKE: do-while". That's allowed as a move (cookbook C0535). It's not a "lever kind" (not pin/launder/barrier/keepalive asm). So using do-while(0) is a legitimate real-C move.

But our problem is combine folding the andi into ang. Hmm.

Also line 289: func_80187988 MATCH: "hoist rand() to a temp c and put val=nudge before the test (if (!(c&1)) val=-val) so the copy is in the pre-branch block; combine cannot fold it into negu". This is analogous! The copy must be in a place where combine can't fold it. Here we need the copy `ang = a` to not be folded into the andi.

Let me think about combine's fold: `(set ang (and a 0xfff))` where a = $4 hard reg. combine may see `ang = $4` then `$4 = and(...)`; it can substitute $4's value into the copy: ang = and(...,0xfff) and retarget the andi dest to ang. To prevent, the copy must not directly follow / be in the same block, or `a` used elsewhere.

Line 289 approach: move the copy to the pre-branch block so combine cannot fold it into the negu. Here the copy is already right after the andi in the same basic block. Hmm.

Alternatively: use do-while(0) to split the EBB (cse1 EBB split) — C0535: do{}while(0) splits cse1 EBB. That might prevent the fold! Since `do { } while(0)` creates a basic block boundary? Actually it creates a NOTE or barrier for cse1.

Wait — C0535: "do{}while(0) splits cse1 EBB". Let me read C0535.

Let me read the cookbook entries C0535 and C0414.
