---
ts: 2026-11-06T17:12:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vW5SOV6l1aPvJ8ur7BBG
---
All 21. The mask's register is stubbornly t7.

Let me reconsider: maybe the target's mask in t6 comes from the *original source* using a different expression that made the mask's priority higher. The pin comment says "Pinning the mask to $14 (cookbook §17) fixes all 20 affected instructions; it is byte-clean (constant computed straight into the hard reg...)".

Hmm, "constant computed straight into the hard reg" — with the pin, the constant is computed into t6 directly.

For lever-free, we need the constant pseudo to be allocated t6. Its priority must beat the 0x8E constant.

Key: the 0x8E constant's priority 0.67 vs the mask's 0.218 (after sched1 hoisting). What if we make the mask's live range shorter by *not* letting sched1 hoist it? The hoisting to insn 16 is what lengthens its life to 179.

Why does sched1 hoist the mask? Because it's a single-set insn (birth) and sched1's priority boost. In the target, the mask is also at insn 16-17 (hoisted). So both hoist.

But in the target, the mask's live range is also 179... and it's pinned, so no competition.

What if we could make the mask's *refs* higher? It has 13. Adding 3 more refs (16) → floor_log2(16)=4 → 4*16/179 = 0.357, still < 0.67. Need more: at life 179, to beat 0.67 we need refs*floor_log2(refs) > 120 → e.g., 32 refs → 5*32=160 → 0.89. That's 32 uses — not feasible.

Alternatively reduce the mask's lreg life: if the mask's def were NOT hoisted, life 61 → 39/61=0.64, still slightly below 0.67. With 14 refs: 3*14/61=0.69 > 0.67! So if we add ONE more use to the mask (14 refs) AND prevent the hoist, it would win.

Preventing the hoist: hmm.

Or reduce the constant's priority: if the constant's lreg life were longer, say 24 insns: 2/24=0.083 < mask 0.218. The constant's life is 12 because sched1 hoists it to insn 5 and uses it at 76? Wait, 12 insns — hmm, "used 10 times across 12 insns" for 117... that's not the constant's real stats.

I'm confused about the lreg stats. Let me directly inspect the sched1 dump (n3.i.sched) to see the mask and constant live ranges.

Actually, let me try a different, more promising angle: the target's allocation might come from the ORIGINAL source having the mask used in a *different pattern* that gives it a copy preference or a different qty. For instance, the original may have written:

```
p0->unk0 = (p0->unk0 & 0xFF000000) | (*ot & 0xFFFFFF);
```
with the mask inline, and the compiler CSE'd it into a register — with the cse pseudo allocated early (birth at the first use).

Let me try: use the literal `0xFFFFFF` inline in all 12 expressions (a1) — still 21.

Hmm, what if the mask is a *function argument*? no.

What if we reverse the operand order in the ands: `(m24 & *ot)`? The target's and is `and v0,v0,t6` — the mask is the second operand. If we swap, the and would be `and v0,t6,v0` — different bytes. No.

Let me look at the actual instruction where the mask is materialized in mine vs target and the exact diff count: 20 instructions affected (10 and + the lui/ori + others). The only difference is t6↔t7 for the mask and the 0x8E constant.

What if we can make the 0x8E constant take t5 or another reg by increasing register pressure? E.g., add another live value at that point? That would add instructions.

Hmm, what if we change the constant's *use order*: the constants are materialized in sched1's order: a2 (0x8A), t0 (0x8C), t6 (0x8E), s5 (0x9A), ... If the 0x8E constant were materialized EARLIER (before the mask's birth at 16), it could still take t6. If LATER, the mask (born at 16) might take t6 first, and the constant would take t7.

The constants are at insns 559-566 in the RTL (all together, before the stores). They're hoisted as a group to the top. The mask's def is at 571-572 (after them). So in RTL order, the constants come first → they take t6 (if allocated in insn order... but allocation is by priority, not order).

The priority of the constants: 2 refs, life 2 (in RTL before hoisting) → 1.0. The mask: 13 refs, life 61 (before hoisting) → 0.64. So the constants have higher priority and are allocated first (in priority order) → they take t6, then the mask takes t7.

Wait, but if priority is computed from the *pre-sched1* live ranges (flow), then constants 1.0 > mask 0.64 → constants first. That's consistent with the outcome.

To flip, the mask's priority must exceed the constants'. Increase refs to 16: 4*16/61 = 1.05 > 1.0! Or reduce the mask's life.

So adding 3 more uses of the mask (13→16) might flip it! How to add uses for free? Hmm, "free" is hard. But maybe we can restructure the 12 expressions to use the mask more times? Each `and` is one use. The unk0 store expression: `(p->unk0 & 0xFF000000) | (*ot & m24)` uses m24 once; the `*ot = (*ot & 0xFF000000) | (p & m24)` uses it once. 12 uses.

Could we write the expressions so the mask is used twice per statement? e.g., `(*ot & m24) | ((u32)p & m24)`? That would add instructions (extra and).

Alternatively reduce the mask's life: its life is from the first use to the last. It's already defined right before the uses; the flow dump says 61 insns — because the uses span 61 insns? The 12 ands span the last ~60 instructions. Can't shorten.

Hmm, what about the *size* factor: qty_size for the mask is 4 (SImode). Same for constants.

Alternatively, make the constants' life longer: if a constant's def is farther from its use, its priority drops. The 0x8E constant is used in the third packet store. If we could make sched1 place its materialization far from the use... sched1 controls that.

Hmm, what about making the constants *not* single-set: e.g., use each constant twice? `*q2 = 0xE100008E; ... = 0xE100008E` would need another use.

OK, empirical: try adding a 13th/14th use of the mask in a way that's *byte-free*: maybe in a `do {} while(0)` no. Or use the mask in an expression that already has an and with 0xFF000000? E.g., `p->unk0 = (p->unk0 & ~m24) | (*ot & m24);` — that replaces the 0xFF000000 constant with ~m24, adding a `nor`/`not` instruction (probably). Hmm, but maybe not: `& ~m24` requires computing ~m24 (one instruction) but could be shared. That would add 1-2 instructions and change the code. Not byte-identical.

What about writing the two mask uses per statement as `(p->unk0 & 0xFF000000) | (*ot & m24)` — one.

Hmm, the target has 12 `and`s with the mask; each statement has 2 ands: `and v0,v0,t6` (mask) and `and v0,t3,0xff000000`? Let me look at the target's tail to count mask uses.

Actually, the mask is used 12 times in mine too (the same instructions). So the source is right; only the allocation differs.

Since refs=13 both ways, the priority difference must come from life/ordering.

New idea: change *where* the mask is defined to alter its qty birth. What if `m24` is defined but the compiler hoists it; its birth in lreg is insn 16 (hoisted). The constant's birth is insn 5. If the mask's def were placed BEFORE the constants in the source (e.g., at the top), sched1 might still hoist it to 16. a2/a3 tried moving the source def — score 23 (slightly worse), so the RTL hoisting position changed.

Let me look at a2's mask materialization position: still t7.

Let me try yet another approach: make the mask a `s32` (signed) — the constant 0xFFFFFF as s32 is 16777215 (positive). Same.

Try: `m24 = 0xFFFFFF;` → `m24 = 16777215;` same.

What about making m24 a `u16`? no, wrong value.

Let me look at the problem from the other side: the constants. There are 6 E1 constants; the third (0x8E) gets t6. If we could make the constants be materialized in a different ORDER such that t6 goes to a constant that dies before the mask's birth... The mask's birth is insn 16 (hoisted). The constants are hoisted to insns 5-15. All 6 constants are before the mask. If a constant is live across insn 16 (its use is later), it conflicts with the mask. The 0x8E constant's use is at insn 76 — after the mask's birth (16). So they conflict, and the constant won t6.

If the 0x8E constant's use were BEFORE the mask's birth, no conflict. The mask's birth is at insn 16 due to hoisting. Hmm, the mask is hoisted to 16 (right after the constants). If we could make the mask NOT hoisted to 16 but later, then the constants (uses at 76+) would... still conflict.

Alternatively, if the constant's use were early (before 16), no conflict. The uses are at the packet stores (insn 76 etc.).

OK, one more idea: the mask could take t6 if the 0x8E constant preferred another register. Local-alloc has copy preferences; if the constant's value were copied from a register... e.g., `*q2 = m24_hi` no.

Let me try: change the 0x8E store to use a *variable* defined at the top: `u32 c2 = 0xE100008E;` at function scope, assigned before the packet. Then c2's birth is early and its life is long → lower priority → it might take a different register (maybe t7 or a s-reg). If c2's priority drops below the mask's, the mask takes t6 and c2 takes t7!

Let me try naming all six constants as variables declared/assigned at the top (or just the third). Adding `c2 = 0xE100008E;` before the stores adds no instruction (it's the same materialization). The variable's def/use positions change though: if defined early (top), the value is live longer → lower priority.

Try: add `u32 c2;` and `c2 = 0xE100008E;` right after `i = arg0*0x90;`, then `*q2 = c2;`.

Similarly for all six constants (c0..c5) defined at the top. That's a real C move (variable hoisting) and may fix the allocation.

Let me test.
