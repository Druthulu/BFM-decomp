---
ts: 2026-11-06T03:40:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_c6W0vyw2BRd0YkkQ74xx
---
I understand the format now. The body file is the function definition only.

Approach note (X1) — write it now, before first edit:

"These four functions are byte-exact only with an opaque asm barrier (or pins in one). I'll strip each lever, then re-derive the same instruction order from real C: for the barrier cases the barrier exists to stop sched1/cse/reorg moving one statement; my job is to find a real-C dependency (a second set, a temp, a width cast, statement order) that reproduces the same placement. Each item gets orig.c, a lever-free nopin.c baseline, then candidate bodies scored with dt.sh; MATCH = score 0 with no lever of the listed kinds."

Now item 1: func_8017D7B4, kinds barrier, 47 lines. It's a straight-line function with two memory barriers. Let me copy orig.c and create a lever-free baseline by removing the asm barriers.

Let me determine exact line ranges. func_8017D7B4 starts at line 3733 `void func_8017D7B4(void) {` and ends at the `}` after `D_801151D4 = (s32)D_80126948;`. From the output, lines 3733-3782 approx. Let me get precise via grep.
