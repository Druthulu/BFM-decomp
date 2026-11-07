---
ts: 2026-11-06T06:47:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_deCAwTtbt8WBh0jYLXnO
---
Still 45 best (v2/w3/w4). 

I'm at ~23:58 with item 4 started 23:45 → 13 min, ~28 tries. Let me check the target asm quickly to see if there's an obvious difference, then decide.

Actually, let me reconsider the whole thing. The pins are 4: var_t7=$3, k50=$20, kF0=$18, k100=$19. Removing them changes the allocation of the constants and var_t7.

The residual (54) is a full v0/v1 swap in the first computations and s7/s8 in the tail. That smells like the constants' allocation shifting the whole bank.

Given the pattern from my other items, this is likely a wall. But let me try one thing: the target's k constants are in $18-$20 (s2,s3,s4) — callee-saved. Lever-free, do they still get callee-saved? Let me check the alloc table: r73 (5 refs, live 24, crosses 2 calls) is a callee-saved candidate. Only ONE callee-saved allocno crosses calls in mine (r73), while the target has k50, kF0, k100 in $18,$19,$20 plus var_fp/var_s7 in s7/s8.

Hmm, that's suspicious: in the target, k50/kF0/k100 are live across calls (they're stored into sp10 between the func_80017738 calls). In mine (lever-free), are they? The constants are re-materialized (li) at each use instead of being held in registers! Because they're constants, gcc's cse/reload rematerializes them.

In the target, the pins force them into registers. Lever-free, `sp10.w[4] = k40;` becomes `li v0,-0x40; sw v0,64(sp)` at each use.

So the target's whole structure relies on the pinned constants being in registers.

Hmm! That's a big structural difference: with the pins, the constants are loaded once into callee-saved regs and reused; without, they're rematerialized per store.

But mine has 162 insns vs the target's 163 — so mine is NOT rematerializing more (it'd be more insns). Hmm.

OK, let me look at the actual target asm to understand. Time is short but this is the last item. Let me dump and look at the head of the function.

Actually, let me first check: does the lever-free body have the constants in registers? Let me grep my candidate's asm for "li v" or the k constants... Let me look at the .s of the candidate (from the dump I made earlier? I removed dmp). 

Let me do a quick dump of both and diff the two functions' asm.

Hmm, time. Let me just do it — it's the most informative.
