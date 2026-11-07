---
ts: 2026-11-06T11:45:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Kbp0ZIQ9g3JAiJFkMlNj
---
The residual is dominated by a register assignment swap: `otp` is in s2 in mine, s0 in target (and y is s0 in mine, s2 in target). Plus a few ordering bits.

This is a local-alloc/global-alloc priority issue: otp (the OT pointer) vs y. In target: otp = s0, y = s2, x = s1. In mine: otp = s2, y = s0, x = s1.

If I could swap which pseudo gets s0... That's regalloc, driven by ref counts/priorities. Real-C levers: declaration order! "decl order" is in the C0505 catalog. The callee-saved allocation order follows the order pseudos are born/registered. Target: otp=s0, y=s2, x=s1. Decl order in source: otp, p, mFF($7), vx, vy, pmask, tag2($6).

Target has s0 for otp, s1 for x, s2 for y. Mine has s0 for y, s1 for x, s2 for otp. So the order in which they're considered differs.

Local-alloc assigns hard regs to pseudos by qty priority (refs/live length). otp has 4 refs? It's used in the tag computations (many uses). y has few refs. Hmm, in target otp got the *lower* reg s0.

Idea: change declaration order — put `s32 otp;` after `s32 vx, vy;`? Decl order affects local-alloc's qty order (qty numbers follow pseudo numbers, which follow declaration order). Let me try permutations of the declaration order and see if the score drops.

Axes: order of {otp, vx, vy, pmask, p} declarations; also splitting `s32 vx, vy;` into separate decls. That's a real C move (decl order/scope).

Let me generate ~20 decl-order variants on top of the best base (d000 = p, inplace, first, plain, const before). Actually base v0 had the same 28? No, v0=30, d000=28 due to `tag2=const` before the ot store.

Let me generate variants:
- decl orders: (otp, p, mFF, vx, vy, pmask, tag2) [base], (vx, vy, otp, p, ...), (p, otp, ...), (otp, vx, vy, p, ...), (vx, otp, vy, p...), etc.
- Also try declaring vx,vy as separate lines vs combined.
- Also try `s32 otp; s32 p;` order.

Let me write gen3 with ~20 decl orders and score.
