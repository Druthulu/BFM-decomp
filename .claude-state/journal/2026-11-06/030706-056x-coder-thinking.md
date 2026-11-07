---
ts: 2026-11-06T10:07:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zdHeaVFsg1HacnQ7yTKC
---
All score 7 (the same f/giv swap). None changed the allocation.

I need a move that changes the priority of f vs giv. The keepalive added refs to i1; that changed something. Let me try to understand better by experimenting with adding refs to i1/f via real C.

Real-C ways to add a reference to i1 in the loop without changing codegen:
- `i1 = i1;` — dead, eliminated (v9 still 7).
- Use i1 in the compare: `if (*(u16 *)(D_801AECD8[i1] + 2) == 5 && i1 >= 0)` — adds code.
- `*(u16 *)(D_801AECD8[i1] + 2)` uses i1 once for the address.

Hmm. The keepalive's effect: it's an insn in the loop body that USEs i1. In flow.c, that adds loop_depth (=2) to i1's n_refs and extends its live length. i1's priority goes up. But target's i1 is in a0 both ways...

Wait, maybe the effect isn't on i1's register but on the *giv's* creation. The asm use of i1 may prevent loop.c from deleting the original i1 usage, changing which pseudo is the giv.

Let me look at how the giv is created. In loop.c, the biv i1 has uses; the giv is created for `D_801AECD8[i1]` (base + i1*4). With an extra use of i1 (the asm), loop.c might still create the giv.

Hmm, what if the asm use changes the *order* of pseudos (allocno numbering)? The allocno_compare tie-break is `*v1 - *v2` (allocno index order). If f and giv have EQUAL priority, the lower allocno index wins the better reg. Adding an insn changes allocno creation order/numbering.

So maybe the fix is a tie-break flip: if we can change the order in which f and the giv pseudos are created, the tie-break flips. The giv is created by loop.c after the loop is scanned; f is created from the source. Hmm.

Alternatively, since priority = floor_log2(nrefs)*nrefs/live_length, if we can make f's priority slightly higher...

Let me look at the actual computed priorities. Can I dump global-alloc's decisions? There's `-dg` (dump global alloc) maybe. The project has cc1 dump tools. Let me check tools/cc1_dumps_tu.sh and hdump.sh usage.

Actually, a more direct experiment: add a real reference to f inside the loop that generates no extra instruction. For example, use f in a condition that's already evaluated: `if (*(u16 *)(D_801AECD8[i1] + 2) == 5) f = 1;` — f is set but not read in the loop.

What if we restructure so f is read in the loop: `f = f | (cond);` → v2 gave 220 ins (2 fewer) — different codegen. Hmm, v2 was score 22.

What about `if (f == 0 && *(u16 *)(D_801AECD8[i1] + 2) == 5) f = 1;`? Semantically equivalent (once f=1, skip), but adds a compare per iteration — codegen changes (extra insns).

Hmm.

What about changing `f = 1;` to `f = 1; i1 = i1;`? dead.

What about making the loop counter used in a second place that's already computed, e.g., `i1 < 5` vs `5 > i1`? Same.

Let me think about the priority formula with numbers. Let me actually dump the RTL/global alloc info. Use cc1 dumps. Let me check the tools.
