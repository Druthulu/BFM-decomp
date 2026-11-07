---
ts: 2026-11-06T18:46:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MAj4L8bGHBcaL06MTFtJ
---
Score 3: mine uses v1 for the base address ($3) and a3 ($7) for the moving pointer? Let me parse: "v1->a3 x4, a3->v1 x1": mine[1..3] = lui v1; addiu v1; move a3,v1. Target: lui a3; addiu a3; move v1,a3.

So in mine: the base address is materialized in v1 ($3) and then copied to a3 ($7); in target: materialized in a3 ($7) and copied to v1 ($3).

Both use $7 and $3 — just swapped! The target has a7 (the return pointer) in $7 (a3) and v1 in $3. Mine has the base in $3 and the copy in $7? Wait: mine: `lui v1; addiu v1; move a3,v1` — so v1 = &D_8011FD10 ($3), a3 = v1 ($7). Then presumably the loop uses v1 as... hmm, mine has v1->a3 x4: in 4 places mine uses v1 where target uses a3. And a3->v1 x1: in 1 place mine uses a3 where target uses v1.

So mine: v1 is the return pointer (a7's role) and a3 is the loop pointer (v1's role). The target: a3 = a7 (return pointer), v1 = loop pointer.

Wait, target: a3 = &D_8011FD10; v1 = a3; loop: v0 = v1 (lhu v0,0(v1)); nonzero: a3 += 0x68; v1 += 0x68; a2++; a1 += 0x68. Else: stores; return a3 (v0=a3 at f04: move v0,a3).

So the target's a7 = $7 = a3 and v1 = $3.

In mine (no pin): the *base* pseudo (a7) got $3 and the loop pointer v1 got $7. So global-alloc gave the two equal pointers swapped registers.

The fix: get a7 into $7 and v1 into $3 without the pin. The mechanism: a7 and v1 are two pseudos that are copies of each other; cse may merge them... but here they survived (score 3 = register naming only, same insn count). So cse did NOT merge them (they're both live and used). Actually the target keeps both (a3 and v1), and mine also keeps both — just assigned oppositely.

Global-alloc order/prefs: a7 is initialized from the symbol (a copy from a hard... no, a symbol_ref), then v1 = a7 (a copy). Global-alloc gives copy preferences: v1 prefers a7's reg. The order determines who gets $7.

Let me dump the .greg for w1 to see the order and prefs. Then find a real-C move to swap them.

Ideas: swap the initialization order (`v1 = &D_8011FD10; a7 = v1;`) — the target's first insn is `lui a3` (a7), then `move v1,a3`. So the source order is a7 first, v1 second. If we swap to v1 = &...; a7 = v1, the asm would be lui v1; move a3,v1 — which is exactly MINE. So no.

What about the return: the target returns a7 (the pointer that advances). Both a7 and v1 advance identically; the difference is which is returned.

Register assignment: target a7=$7, v1=$3. Mine a7=$3, v1=$7 (i.e., swapped). Hmm wait, let me double check mine's diff: mine[1] lui v1 vs target lui a3 → in mine, the symbol goes into v1 ($3); mine[3] move a3,v1 vs target move v1,a3 → mine copies to a3. So mine: a7 (the returned pointer) = $3? Which pseudo is mine's v1? The diff's "mine" column uses the target's instruction text? No — dt.sh's diff shows the actual asm lines from both. The register names in the "mine" column are mine's actual registers. So mine: the symbol is in $3 (v1), then moved to $7 (a3). Which pseudo is the symbol's destination? In the source, `a7 = &D_8011FD10;` then `v1 = a7;`. So the symbol goes into a7 and is copied to v1. In mine, the symbol went into $3 = v1's register? That means a7 got $3 and v1 got $7.

And the 4 "v1->a3" mismatches: mine uses v1 where target uses a3 — so mine's a7 is in $3 (v1) in 4 places, and mine's v1 is in $7 (a3) in 1 place.

So the allocation is exactly swapped: a7=$3, v1=$7 (mine) vs a7=$7, v1=$3 (target).

To swap: global-alloc's order/prefs. Let me dump and see. Let me get the .greg.
