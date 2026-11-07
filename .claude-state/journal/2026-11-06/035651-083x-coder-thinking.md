---
ts: 2026-11-06T10:56:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Xw0RIAvQyzhwomkSQaHu
---
In the twin, the `v1 = 0x4000;` variable got a0 (!!) — because a0's pseudo is dead after the calls, so local-alloc reuses a0 for v1? That's the "lreg-v0-local-first" class. The target has v1 = 0x4000 in v1.

Interesting: the target's v1 = 0x4000 is a real variable in the source (the author used it). In the target it got $3 (v1). In my base it got a0 ($4) — because a0 is dead and local-alloc reuses it.

Wait, but the orig scores 0 with v1 in v1 — because the pins force it? The pins are s0 ($16) and t ($2). v1 is unpinned in the orig too. Hmm, but the orig has the barrier and the pins; maybe the barrier affects the block structure so that v1's qty is allocated in a block where a0 is live? 

Hmm, actually in the orig, `v1 = 0x4000;` comes AFTER the barrier, in a block where a0 (the pseudo) is... a0 is the parameter, used before; after the calls, a0 is dead. So local-alloc could reuse $4 for v1. But the target has v1 in $3.

Wait, the target IS the orig (score 0). So in the orig, v1 = 0x4000 got $3. In my base it got $4. The difference: the barrier/pins.

Hmm, but the register pair report says "a0->v1 x3" meaning mine uses a0 where the target uses v1. So mine: li a0,16384 and sh a0,... — yes.

Why would the pin/barrier make v1 get $3? If the barrier splits the block, v1's qty is in the block after the barrier, where a0 is still... no, a0 is dead.

Hmm, unless in the orig the parameter a0 is *pinned*? No, only s0 and t.

Wait, in the orig, `s0` is a hard reg $16, so the parameter a0 is copied to $16 early. Then a0 ($4) is dead after the copy. So in the block after the barrier, $4 is free → v1 could get $4 in the orig too. But the target has v1 in $3.

Hmm, maybe local-alloc's qty ordering: within the block, the first qty gets the first free reg. The register order preference: local-alloc's find_free_reg scans from a preferred register. For a qty with no preference, it starts at... `reg_preferred_class` → GR_REGS; find_free_reg scans the register file from `regno` (some order). The MIPS local-alloc ordering might prefer v1 over a0 for non-call-crossing pseudos? Actually $4 (a0) is a caller-saved arg reg; local-alloc's `find_free_reg` starts from a "preferred" register derived from the insn's hard reg usage.

The difference in mine: the whole block contains the load etc.; in the orig, the barrier split the block, so v1's qty is in a *different* block where the register allocation order differs.

This twin is harder because of the extra v1 variable.

Let me try: make the do-while split around the load (w_dw) — that's what I did; score 7. The issue now is v1→a0.

What if I also wrap `v1 = 0x4000;` in the do-while block with the load? Then v1 is in the load's block, and its allocation might differ.

Let me try a few variants:
- w_dw_v1: do { v1 = 0x4000; t = unkC4; } while(0);
- w_dw_v1b: do { v1 = 0x4000; } while(0); do { t = ... } while(0);
- and maybe move `v1 = 0x4000;` to before the barrier position (i.e., before the calls?). The target's li v1,16384 is at position 35 (after the RMW).

Hmm, the target's `li v1,16384` is at f50 (position 35), i.e., after the RMW and the lw32. So the v1 assignment is scheduled late, near its first use.

Let me test a couple.

Also, importantly: maybe in this twin the best structure differs. Let me first check: does the base + barrier (no pins) score 0? That tells whether the pin is needed at all here.

Let me test base with the barrier re-inserted in the original position (before v1 = 0x4000).
