---
ts: 2026-11-06T11:55:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_J6QMMbAZ4xnIW0QQh3UJ
---
Best lever-free so far: 45. Let me try a few more variants targeting the *slider* (mechanism 1): the slider is in the `if (lim >= g.otz)` block and shifts live lengths. Without it, the global-alloc tie breaks wrong → 2 extra insns (the spill reload). Maybe a real-C change can shift the live lengths: e.g., moving a statement into/out of the loop, changing the order of gte_stsz3 args, etc.

The header says: "The shipped workaround permuted the stsz3 operand list (creation sz0,sz2,sz1) which fixed allocation but transposed the preheader emission (close=2). TRUE FIX: natural operand order restored + ONE zero-byte asm". So with natural order + slider → 0. Without the slider → the tie breaks wrong → 2 extra insns (the `lw v1,0(s7)` spill reloads?).

Hmm, v1's diff (45): let me look at what's wrong. Earlier v3 (barrier removed only) showed the s7/s8 swap (addiu s8,sp,236 vs s7,sp,236) — the &g.sz0 vs &g.sz1 grant. That's mechanism (1): &g.sz0 should win $fp.

Idea: can a real-C change shift the live lengths by 1? The header says int(140000/L) ties for N in {1,3,4} and splits wrong for N=2. So N=1 (one zero-byte insn) also works! But that's still a lever.

Real C: make one of the two address pseudos live 1 longer/shorter. E.g., reorder statements so that &g.sz0 is defined later. Hmm.

The mechanism: two loop-invariant address pseudos (&g.sz0, &g.sz1) hoisted to the preheader. L = live length. With N extra loop insns, L grows by N.

A real-C way to change L: move a use of one of them earlier/later within the loop. E.g., gte_stsz3(&g.sz0, &g.sz1, &g.sz2) — the address pseudos are created at that call. Their live ranges extend to... hmm.

Alternatively: introduce a real C statement that lengthens the loop body by 1 insn (a real insn) — but that adds an insn to the output (which must not).

Hmm, what if the extra insn is *outside* the loop? The comment says the sliders must be inside the loop (they lift L by N).

OK, this is a genuine wall. The header documents 470+ orderings tried.

Let me try 2-3 quick ideas on mechanism (1) with real C:
- r1: reorder the gte_stsz3 args (the "shipped workaround"): `gte_stsz3(&g.sz0, &g.sz2, &g.sz1)`.
- r2: swap the declaration order of sz0/sz1? They're in a struct `g`.
- r3: change `g.sz0 > g.sz1` comparisons order.

These change semantics subtly (gte_stsz3 writes to the given addresses, so the operand order matters!). `gte_stsz3(&g.sz0, &g.sz1, &g.sz2)` writes sz0,sz1,sz2 in order. Permuting would swap values — but the code only takes max/min of sz0..sz2 in the FT3 arm (`za = max(sz0,sz1,sz2)`), so permuting sz1/sz2 is harmless? In the FT3 arm: `if (g.sz0 > g.sz1) {za=g.sz0; if (za<g.sz2) za=g.sz2;} else {za=g.sz1; if (za<g.sz2) za=g.sz2;}` — that's max(sz0,sz1,sz2). Permuting sz1 and sz2 gives the same max. So `gte_stsz3(&g.sz0, &g.sz2, &g.sz1)` is semantically equivalent for this code path (and for FT4, gte_stsz4 writes sz0..sz3 and the code takes max of all four).

Hmm, but the header says the permuted version transposed the preheader emission (close=2). So it fixes allocation but breaks emission.

Let me try r1 and see. It's one try.

Given time, let me do a few and then finalize item 2 as WALL best 45.

Actually, hold on. The header says the slider is in the `if (lim >= g.otz)` block — a different basic block from the loop head, so it doesn't perturb (2). Without it, mechanism (1) breaks.

Is there a real-C equivalent of a zero-byte insn that lengthens the loop body? No.

So item 2 is a WALL: tag `global-pri-bank-order` (the tie) or `sched1-birth-order`. The primary blocker for lever-free: both. Best 45.

Hmm, but wait: what about keeping the barrier and removing only the launders → v2 = 3. That's PARTIAL:barrier with score 3 (not 0) — not a PARTIAL (needs 0). So WALL.

Hmm, but actually — maybe I should reconsider: is the *barrier* (slider) removable if I use the "permuted stsz3" real-C workaround? The header says that fixes allocation but transposes the preheader emission (close=2). Combined with removing the launders, maybe... Let me try: permuted stsz3 + both launders gone + slider gone.

Let me try r1 (permute stsz3) with all levers gone, and with launders gone + slider kept.

Let me look at the gte_stsz3 call sites: lines 2931 and 3003 (gte_stsz4). Let me try permuting both.

Let me generate a few.
