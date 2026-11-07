---
ts: 2026-11-06T05:00:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_c8Pu6AsTUxEbBhQ4pJRk
---
s1/s2 still 38/111. The inner do-while didn't restore the reload. Hmm.

Maybe cse isn't the one reusing; maybe it's `combine`/`cse` after loop.c... The value v1 is loaded once and reused. If the do-while splits the EBB, cse can't reuse... unless the split doesn't happen.

Let me look at the actual diff of s2 to see if anything changed vs q1. Let me check the insn count: still 111.

Maybe the issue is the *order*: the third block's first load is hoisted before the store in the source? No — in the source, the load is before the store (outer if condition), and the second load is after. In the target, both loads exist. In mine, one load is used for both.

Hmm, maybe the reuse happens in a pass before cse1 (like `combine` or the initial RTL expansion?). No, it's a global load.

Wait — maybe the do-while(0) is being removed before cse1. Let me check: C0535 says do-while(0) splits cse1's EBB, so it survives to cse1. But maybe with `-O2` and this compiler, `do{}while(0)` around an `if` is removed early.

Let me test the do-while's presence with a cc1 dump. Use hdump.sh on the includer with body s2, dump, and grep the loop notes.

Actually, let me first check whether the third block's reload is really a cse thing. Let me look at the target's third block vs mine in detail. In mine (q1), the first load is in v1 and the second comparison uses v1 (slti v0,v1,129). So the value is reused. If I make the second load's *source* different — e.g., `(s16)D_80078EA6 >= 0x81` vs `(u16)D_80078EA6 >= 0x81`? cse's MEM equivalence doesn't depend on the comparison. But the load's *mode* (HImode) is the same.

What if the second load is written as a *different-sized* access that produces the same instruction? E.g., `(s16)(D_80078EA6 + 0)` — combine folds.

What if I use a temp: 
```
if ((s16)D_80078EA6 < 0x80) {
    s16 t = D_80078EA6;   // reuse?
    D_80078EA4 += a1;
    if (t >= 0x81) ...
}
```
No.

Hmm, what about making the store a *volatile* store? lever.

OK, let me check whether the target's reload is actually forced by the asm or by something else. Let me test: put the barrier back but with a *non-memory* asm (no clobber): `__asm__ __volatile__("");`. If the score stays 0, then the memory clobber isn't needed for the reload (the asm alone, being an unmovable insn, might stop sched1 and cse?). If the score changes, the memory clobber is essential.

Actually, more useful: let me test variants of the barrier to understand what's needed:
- barrier1: `__asm__ __volatile__("");` (no clobber) at all 6 sites.
- barrier2: memory clobber (original) = 0.

If barrier1 scores 0, then the reload/order is not from the memory clobber but from the asm insn itself. Interesting.

Let me test.
