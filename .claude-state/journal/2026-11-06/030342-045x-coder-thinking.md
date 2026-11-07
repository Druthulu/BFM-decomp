---
ts: 2026-11-06T10:03:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4TAbxHU3Ndw0VT3UUXOY
---
Note: `reg_n_refs[regno] += loop_depth;` — if loop_depth is 0 (outside loops), this adds 0! Hmm, but there's also the "minimum 1"? Let me look at how n_refs is used... Actually in flow.c, there's an earlier adjustment: "if (reg_n_refs[i] == 0) reg_n_refs[i] = 1"? Let me check. Also note loop_depth inside a loop body is >= 1.

Anyway, the priority formula uses floor_log2(n_refs)*n_refs/live_length.

The giv pseudo is in the loop (depth 1), so each ref adds 1 (or more with nested loops). f is partly outside the loop (f=0 before, f!=1 after) and partly inside (f=1).

Now, the keepalive use of i1 inside the loop adds 1 to i1's n_refs. How does that flip giv vs f? Maybe it doesn't directly; maybe the mechanism is that the keepalive asm insn makes i1's live range span and changes local-alloc's qty assignment, which then changes global-alloc's conflicts.

Actually wait — maybe the mechanism is simpler: `__asm__("" :: "r"(i1))` is an insn that USES i1 and is in the loop. This makes i1 live from its definition to that point, and adds a ref. It may also affect loop.c's strength reduction: the giv is derived from i1; with the extra use, loop.c might not reduce, or the giv gets different refs.

Given the target's loop is exactly strength-reduced (addiu a1,a1,4), the giv exists.

Hmm, the source comment says: "the zero-byte `"r"(i1)` keepalive adds the 5th reference to the loop counter, which lifts its global_alloc priority above the strength-reduced pointer giv's -- that is what puts the counter in $a0 and the giv in $a1 (without it they swap)."

So target: counter in a0, giv in a1. Without keepalive: counter in v1?? But our mine shows i1 in a0... wait, let me recheck mine. Mine at 2ea4-equivalent: `move a1,zero` (f=0). Then `move a0,zero` — that's i1=0. Hmm, so i1 in a0 in mine too. And giv in v1 in mine.

Wait, maybe I misread which is which. Let me carefully dump mine's case-1 loop region.
