---
ts: 2026-10-22T00:31:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_MjcCDkaroN2rAv4i6Nci
---
There's a gcc 2.7.2 build at tools/bin/gcc-2.7.2-psx/. The source might be under tools/bin/gcc-2.7.2-psx/ (a source tree). Let me check for cse.c there. Reading the compiler source to understand find_best_addr is legitimate research (it's not a project tool).

But careful about time. Let me first try a couple of empirical candidates; if they fail, look at cse.c.

Actually, let me reconsider the problem completely. What if the crack is NOT about the address at all, but about *how many times* the address is used, i.e. the fix is to make the *y* loads use a *different variable* that is *also* the base?

Hmm, here's a thought: what if the y load is expressed as a load from the *same* reg with a *different* base form such that cse's location tracking merges them...

Alternatively: what if the *x* and *y* loads are swapped in the source so that the *first* use is base+4 and the second is base+0? Then maybe cse would keep the reg for base+4 and rematerialize for base+0? The target has both via s1, so that wouldn't match either. But it's a diagnostic.

Let me think about cse's find_best_addr rules in GCC 2.7.2 (from memory):
- It looks for the best address for a memory location among the candidate regs.
- The cost of a reg address: it computes `reg_equiv` etc.
- Key: if the address is a constant (CONST_INT or a symbol+offset) and the reg holds it, cse may decide to *rematerialize* the constant if the reg is "not worth keeping" — the rule involves `cse->cost` and the number of times the reg is used.

In GCC 2.7.2's cse.c there's a function `find_best_addr` that, for each candidate reg, computes the "cost" of the address and prefers... and there's a special case: "if (GET_CODE (mem) == MEM ...)".

I recall that in cse.c, find_best_addr has:
```
	  /* If this is a constant address, and the reg is a pseudo that will be
	     loaded anyway, prefer the constant. */
```
and something like:
```
	      if (ce->eq == 0 && ... )
```

I really should look at the source. Let me check if the source is in tools/bin/gcc-2.7.2-psx/.

Let me look.
