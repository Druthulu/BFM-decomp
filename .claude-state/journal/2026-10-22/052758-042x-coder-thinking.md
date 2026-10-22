---
ts: 2026-10-22T11:27:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_lCoay0TqbEQnnLDjTFC2
---
f07 gave score 4 (COUNT but same count 200) — interesting, `0x140 + (t & 0xFFFFFFFF)` produced a different instruction sequence (maybe `and` then `add`). Not helpful.

All the self-folding expressions get folded at the front end (score 2 unchanged). Confirms the front end folds.

OK. Item 2 is very stubborn. Total tries so far: 15 + 26 + 16 = 57 scored tries. Time: started 04:59, let me check the time.

Let me now decide: item 2 → WALL. Best lever-free score 2. Tag: `sched1-call-group` — but let me refine the mechanism description based on what I learned:

Mechanism: the launder's asm output creates a REG_DEP_OUTPUT on the a1/a2 arg-setup insns (the asm may clobber caller-saved regs), so the whole call-arg group is pinned after the asm and the load (which feeds the asm) is pinned before it → the load lands first. Without the asm, the load's pseudo coalesces into the hard reg a0 and sched1 orders the block [a1=320, load, a2=240, call] — the load is always after the li, in 57 tried bodies.

That's a solid wall. Let me record it.

Actually wait — before I finalize, let me try ONE more family that could work: **make the load's destination NOT a0** so the coalesce doesn't happen, using a different formulation where the value is loaded into a variable used by the call via a pointer:

Hmm.

And another family: **change the ORDER of the call's arguments in the source using a temporary for the constant**:
```c
s32 t;
s32 c;
t = load;
c = 0x140;
func_8001D0E8(t, c, 0xF0);
```
GCC copy-propagates c → 320 before sched. Likely same.

Let me try that plus a few more, then move on. Actually let me be efficient — I'll batch these with the NEXT item's work.

Now let me move to the other items. Let me start with item 4 (func_801832A8, best 14, count exact) and item 5 (func_80185380, best 4 with only-v6-removed... but both must go).

Actually, let's re-evaluate item 5: "only the v6 re-tie removed (p10's kept): 4 (111 ins — count exact)". Both removed → 39.

Item 5's two launders both have a "memory" clobber: `__asm__ __volatile__("" : "=r"(v6) : "0"(v6) : "memory");`. The memory clobber makes it a BARRIER (memory scheduling barrier). So the "memory" clobber is what keeps the loads/stores ordered.

Hmm — for item 5, "lever-free" means removing both asm statements including the memory clobber.

Let me look at item 5's orig.c and the target.

Let me also reconsider: the items' `kinds` are all "launder". The lever is the `__asm__` re-tie.

Let me now work on item 5 (func_80185380) and item 4 (func_801832A8).

Actually, let me reconsider item 1 (func_8017DE84): best 13 with both removed; 6 with only-e removed; 3108 with only-v1 removed. The v1 copy problem is the same "copy merge" class. Hmm.

Let me look at item 4 first (best 14, exact count) — the residual was "the shared 0x66666667 magic constant is materialised right before its mult instead of at the top of the tail, plus a v0/v1 transposition".

Let me read item 4's orig.c and the target.

Time check first.
