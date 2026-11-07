---
ts: 2026-11-06T10:24:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uL695I32N7ipNBbRelBn
---
Item 1: 21 more tries, all 15. Total item 1 tries: orig, w1, w2, w3, wk, wp, k0-k4 (5), m1-m3 (3), s0-s20 (21) = 33. ≥30 ✓.

Now the wall-clock: item 1 started 02:56, item 2 ~02:58, item 3 ~02:58, item 4 ~03:00. Current time ~03:35? Let me check. All items have ≥20 min by now.

Now, item 4's tries: ~35. Its 20-min window: started ~03:00, now 03:35 → 35 min. Fine (brief says past 30 min stop and record a wall).

Now let me finalize:

Results:
- Item 1: WALL, best 15, tries 33, wall expand-void-return, evidence.
- Item 2: WALL, best 23, tries 31, wall expand-void-return.
- Item 3: WALL, best 28, tries 35, wall expand-void-return.
- Item 4: WALL, best 7, tries ~35, wall greg-ref-count.

Hmm, wait. But the brief's DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0". For WALL rows, is a win.c needed? "For each item in list.tsv: write a lever-free body of func in G26x/<dir>/win.c (bare definition) that scores 0." So win.c should be the best lever-free body (even if it doesn't score 0). The DONE WHEN: "each MATCH/PARTIAL has its win.c scoring 0" — implying WALL's win.c need not score 0. So for WALL, win.c = the best lever-free body.

So:
- Item 1 win.c = the lever-free body scoring 15 (s0/w1).
- Item 2 win.c = n0 (23).
- Item 3 win.c = p0 (28).
- Item 4 win.c = v0 (7).

Hmm, but should I record PARTIAL instead, with win.c = orig (score 0)? The G26 parent's convention is WALL with the lever-free best. Let me follow the parent shard's convention: WALL.

Wait, but hold on. Let me re-read the brief's result spec: "result MATCH (win.c scores 0) | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers) | WALL (best = lowest score of a lever-free body)".

For WALL, win.c is the lever-free best body. Yes.

And the parent G26 rows: `WALL expand-void-return — void fn; ... lever-free found dead (49/54), 180 tries (G26)`. They used WALL. Good.

So I'll record WALL for all four, with win.c = the best lever-free body.

Hmm, but is that the most useful? The shard's goal is to crack; a WALL row says "couldn't". The expert banks it.

Hmm, but wait: for item 4, maybe a PARTIAL is better since the win.c (orig) scores 0 with both levers... but the parent shard recorded WALL greg-ref-count for similar. Let me follow the convention: WALL.

Now, the evidence field: "gcc pass + mechanism ≤ 140 chars".

Item 1: `flow/expand void-return: rv sets dead without the keepalive; target li v0,-1/d*2/31 are return values; s32 def conflicts with caller extern void (compile error)`
That's ~150 chars. Trim to ≤140.

Item 2: `expand void-return: ret dead; target move v0,zero/li v0,1 are return values; s32 def conflicts with caller extern void; param copy also coalesced`
Item 3: `expand void-return: else rv=0 dead; target move v0,zero; plus $2/$3 pins needed for obj=v0/chn=v1; s32 def conflicts with callers`
Item 4: `global-alloc ref priority: giv (7 refs) pri 15555 > f (4/16) 5000 takes v1; keepalive's +2 i1 refs flip i1/giv but f needs the $3 pin for v1`

Let me verify the numbers: from the lever-free dump, r234 (giv) pri 15555 refs7 live9; r75 (f) pri 5000 refs4 live16. Yes.

Now the notes.md per item and moves.md appends.

Moves.md format: `kind | func | MATCH: move / WALL tag — mechanism (G26x)`.
So:
```
keepalive,pin | func_8017F1F0 | WALL expand-void-return — rv sets dead without keepalive; target's li v0,-1/d*2/31 are return values; s32 def conflicts with caller extern void (G26x)
keepalive,pin | func_80180AC4 | WALL expand-void-return — ret dead; target move v0,zero/li v0,1 are return values; s32 def conflicts with callers (G26x)
keepalive,pin | func_801803D0 | WALL expand-void-return — else rv=0 dead (target move v0,zero); obj=$2/chn=$3 pins also needed; s32 def conflicts with callers (G26x)
keepalive,pin | func_80180E64 | WALL greg-ref-count — giv refs7/live9 pri 15555 > f refs4/live16 5000 takes v1; keepalive's +2 i1 refs reorder i1/giv but f needs the $3 pin (G26x)
```

Wait, the moves.md line format: `kind | func | MATCH: move / WALL tag — mechanism (G26x)`. So "WALL expand-void-return — mechanism (G26x)". Good.

Now, before finalizing, let me double check the FRESH requirement: at each item's start, diff <dir>/orig.c against the def in the current src. I extracted orig.c from src at the start (items 2-4) and item 1 from src. But the src might have moved during my run (other batches banking). Let me re-diff now: compare each orig.c to the current src lines. If they differ, regenerate and note.

Let me do that check now.
