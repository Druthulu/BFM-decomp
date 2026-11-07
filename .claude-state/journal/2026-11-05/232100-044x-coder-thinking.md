---
ts: 2026-11-06T06:21:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zRnbBvXX1oHzvtqGJv31
---
Item 1: PARTIAL:pin, best 0, wall tag `global-pri-bank-order`, tries ~8.

Now append the results row and a moves.md line. Then item 2.

results.tsv row format: `dir file func kinds result best tries wall evidence` (tabs).

dir = func_801804A0__ov_SC03_029_jr_8017FF7C, file = src/ov_SC03_029/ov_SC03_029_jr_8017FF7C.c, func = func_801804A0, kinds = launder,pin, result = PARTIAL:pin, best = 0, tries = 8, wall = global-pri-bank-order, evidence = "global-alloc: lever-free loop-ptr pri 7714 > ent 2500 so it takes $17 (target $18); launder cracked by dead-reset p=0 (§373)".

Wait — careful about the "best" column semantics: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So best = 0. Good.

Let me write the row. I must use tabs. Use python script or printf. The rule "One action per command: a results.tsv fix is its own step". Let me append with a small python script (not inline -c... hmm, "Scripts, not inline python -c". I'll use a heredoc script file? That's overkill; but the rule is about scripts. Let me write a tiny helper script under my shard dir that appends a row, and call it. Actually simpler: use printf with tabs in bash. That's one command.

Let me do: printf '...\t...\n' >> results.tsv.

Also append to moves.md: `kind | func | MATCH: move / WALL tag — mechanism (G22x)`.

For item 1: `launder,pin | func_801804A0 | PARTIAL:pin global-pri-bank-order — launder -> p=&D_801C00D0; call(p); p=0 (§373 dead-reset rematerialises the addr); lever-free loop-ptr pri 7714 beats ent 2500, takes $17 (target $18) (G22x)`

Let me append both.
