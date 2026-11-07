---
ts: 2026-11-06T04:59:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n54QPCS8F1XBPK4vCg2N
---
q3 is worse (extra s3, frame 40).

Let me go with r1 (wrap the if in do-while) and r2 (wrap only the first two stores). Let me also try wrapping the store in a do-while *without* the loop-weight side effect: is there another block splitter? 

Actually, maybe the s0/s1 swap in q1 is fixable by a small real-C change (e.g., a dead-reset or a temp) — the moves catalog has "greg-pri-refs" issues. But let's first find a variant that keeps the register assignment.

Let me generate:
r1: `do { if (cond) {...} } while (0);` at each of the 3 first-half sites.
r2: `do { D_80078EA4 += a1; } while (0);` only at sites 1 and 2 (the first two).
r3: `do { D_80078EA4 += a1; if (cond) {...} } while (0);` = q2 (already 78).
r4: wrap only the third site's store (the one inside the `< 0x80` if).
r5: q1 but wrap only sites 1 and 3.

Let me write them.

Note: the do-while wrapper around an `if` requires the if inside braces.

Let me write a more careful generator using the original source text. Let me first print v1.c with line numbers to identify sites.
