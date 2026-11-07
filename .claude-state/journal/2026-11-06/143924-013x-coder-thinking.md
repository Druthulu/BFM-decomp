---
ts: 2026-11-06T21:39:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_q1V9y9y0gDRcCuIQE0wP
---
Very informative. Line 341: `barrier,keepalive,pin | func_8017DEF0 | MATCH: empty do{}while(0) after the call arm (reorg fall-through scan stop) fills the beqz slot from the taken thread (addiu duplicated); 1-field struct alias of D_801151D0 (MEM_IN_STRUCT) keeps the tail store last (G31y)`.

That's a twin of our function! func_8017DEF0 — same family (HUD frame + panel loop). It cracked with:
- barrier[4] → empty do{}while(0) after the call arm (reorg fall-through scan stop)
- memory barrier → 1-field struct alias of D_801151D0 (MEM_IN_STRUCT) keeps tail store last
- pin → ? Not mentioned explicitly; maybe pin dropped via something.

Let me look at that item's win.c. Where is it? Probably .run/P40/T11/G31y/... Let me find. I can't ls outside project but inside .run is fine.

Let me look for func_8017DEF0 dirs.
