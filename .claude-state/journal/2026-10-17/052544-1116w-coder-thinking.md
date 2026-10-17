---
ts: 2026-10-17T11:25:44.398Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm trying to figure out why r ends up in v0 rather than v: it seems to come down to global allocno priority, which depends on floor_log2 of the reference count, with v0's compare temp pinned by the tree structure.

Thinking about r's refs (set, used in expr, used in return copy) versus v's refs (copy, test) — v has a short live range so should have a much higher priority, unless it's actually allocated locally first. Then I'm wondering if there's no separate v pseudo at all — maybe expand_call returns the hard register v0 directly for the comparison target in this GCC 2.7 codegen, and CSE propagates that hard reg straight into the comparison, which would explain why the "move v1,v0" shows up as something other than a normal spill.

I'm trying to match this against the actual disassembly pattern: a function where v0 gets set to the negation of some computed condition while the call's return value goes into v1, matching jump.c's store-flag conversion where constant returns get folded into direct hard-register assignments. For our case, the sequence of conditional branches before computing the expression would need the expression's inputs already available before the second branch, which scheduling can't rearrange — so I'm considering whether the expression is computed from a variable set earlier instead.

The other possibility I'm chasing is that `return (a-0x48 <= t)` expands through do_store_flag into a pseudo via slt followed by an xor that lands in the return register directly — but that xor result isn't a plain register or constant, so it can't satisfy the "x = b" requirement for the second move; it could still work for the first move "x = a" since that one allows any single_set, as long as the previous active insn before it is the actual conditional jump, though the slt instruction sits in between and complicates that.

I'm around 35 minutes in now, so I should stop chasing this variant and just log where things stand: the best result so far is 20 mismatches using c1/f1, compared to the initial 28 mismatches (34 vs 36) from free.c. Time to write that down and move forward.
