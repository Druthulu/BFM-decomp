---
ts: 2026-11-06T12:30:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2PezcuHj0RIhZhiidVOS
---
Item 1 done. Only symbol-name asm aliases remain (not codegen levers, present in orig).

Now append the results row and moves line, write notes. Then move to item 2.

results.tsv row format (tabs): `dir file func kinds result best tries wall evidence`
- dir: func_8017DEF0__ov_SC01_009_jr_8017BE9C
- file: src/ov_SC01_009/ov_SC01_009_jr_8017BE9C.c
- func: func_8017DEF0
- kinds: barrier,keepalive,pin
- result: MATCH
- best: 0
- tries: count my scored tries: c1,c2,c3,c4,c5,c6 = 6 (+baseline orig which is score 0 but that's the baseline). Let's say 6.
- wall: -
- evidence: gcc pass + mechanism ≤140 chars. E.g. "reorg: empty do{}while(0) after the call stops the fall-through scan so the beqz slot is filled from the taken thread; struct alias keeps the tail store (MEM_IN_STRUCT)". Count chars... ~150. Trim.

Let me write these appends with a script to avoid tab mistakes. Use python via heredoc? "Scripts, not inline python -c". A heredoc python is still an inline script... The brief says one action per command and no folding. I'll use a small python heredoc to append — earlier I used heredocs fine (they're allowed apparently). To be safe, use printf with \t via bash? That's allowed but echo/printf... Let me use a heredoc python which worked.

Actually simpler: use `printf '...\t...\n' >> results.tsv`. Bash printf is fine.

Let me compute evidence string ≤140: "reorg: empty do{}while(0) after the call stops the fall-through scan, beqz slot filled from the taken thread (addiu duplicated); 1-field struct alias for D_801151D0 (MEM_IN_STRUCT) keeps the tail store last" — count: let me count later, keep under 140.

Let me write it.
