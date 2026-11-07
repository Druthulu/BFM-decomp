---
ts: 2026-11-06T21:20:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NtN2U8WsSX5TKd42RJob
---
141 includers (not 136; the grep count was different — maybe some include it indirectly).

Score 2: the `move a0,s0` is in the wrong position: mine has it at 25 (after the `li v0,3072; sh`?) while target has it at 24 (in the beqz delay slot).

So the keepalive's role: it makes `a = arg0` happen *early* (before the `li v0,3072; sh v0,16(v1)`), i.e., in the branch delay slot. Without it, the move is scheduled after the store.

Target order:
```
68bc beqz v0,68d8
68c0 move a0,s0     <- delay slot
68c4 li v0,3072
68c8 sh v0,16(v1)
68cc li v0,1
68d0 jal func_80146CA0
68d4 sh v0,184(a0)
```
Mine:
```
... beqz with ? in delay slot
24? ...
```
Let me see the full mine assembly. The diff says: insert `move a0,s0` at mine[24] (target 24) and delete mine[25]. So mine has the move at index 25, target at 24 — one slot later.

So I need the `a = arg0` copy to be scheduled into the beqz delay slot. The keepalive asm was doing that (a barrier preventing the move from sinking). Lever-free, how? This is a sched1/sched2 ordering thing.

Hmm. Let me look at the actual instructions around. Let me score with more tail to see the context. Actually the diff already shows: target 24 = move a0,s0; mine 25 = move a0,s0. So mine has something else at 24. Let me see mine's assembly.

Let me dump or use the dt diff with more context. I'll run tryinc with a bigger tail... tryinc doesn't take a tail. Let me just run delever_search --try directly on that includer? Simpler: use tryinc.py 0 and capture more lines (tail -30).

Wait, the output format shows "insert mine[24:24] target[24:25]" then "delete mine[25:26]". So mine[24] is something else; mine[25] is the move. Let me get the full residual.
