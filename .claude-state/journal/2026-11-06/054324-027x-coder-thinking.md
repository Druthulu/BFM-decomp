---
ts: 2026-11-06T12:43:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pgdOXgLlT4wHt2KuYGn8
---
Excellent! c4a (do-while(0) around `ott = ott;`) scores 0 — barrier 4 cracked. c4b also 0 (do-while around ott computation). c3b (swapped arms) score 3, count matches — progress.

Now combine: barriers 1 removed (free), 4 cracked via do-while. Remaining: 2 and 3.

Let me build a combined base: orig - b1 - b4(do-while). Then work on 2 and 3.

For b3, c3b gives score 3 with 408 ins. Let me see its diff.

For b2, all variants stay at 28 — the allocation issue. Let me look at the actual mechanism. The diff showed mine uses a0 where target uses v1 in the `ua = ub = ...` block. Since barrier 2 sits *before* the ua/ub block, its removal changes what block boundary exists. Hmm.

Wait — maybe barrier 2's real purpose is not scheduling but allocation: it splits the live range so that ua/ub get v1? Hmm.

Let me look at what "target" does exactly around there. Let me dump target's insns 240-300. But target object — where is it? delever_search compares against build/ object. There might be a way to get target dump. tools/cc1_dumps_tu.sh? Let's see if there's a target disassembly available. Actually the diff shows target lines directly, which is enough.

Let me get the full diff for c2a with more lines and for c3b.

Alternatively, think about what real-C change flips a0/v1: the difference is which pseudo gets which reg. Target: v1 holds ua/ub base, a0 holds ... hmm.

Actually from the b2 diff:
```
mine 248: move v1,a0        | target: move a0,v1
mine 249: addu a0,a0,v0     | target: addu v1,v1,v0
mine 250: addiu a0,a0,-1    | target: addiu v1,v1,-1
mine 251: andi v0,a0,0xffff | target: andi v0,v1,0xffff
mine 255: li a0,255         | target: li v1,255
mine 257: move v0,v1        | target: move v0,a0
mine 260: move v0,a0        | target: move v0,v1
```
So it's a pure a0<->v1 swap of the ua/ub pseudos. Interesting: `move v1,a0` in mine means `ub = ua` copy? and target `move a0,v1` means... the *direction* of the move is swapped, so it's not just register renaming — mine has `move v1,a0` where target has `move a0,v1`, i.e. different source/dest assignment. That's the chained assignment `ua = ub = E;`: one of ua/ub gets E directly, the other gets a copy. Mine copies E into v1 then a0, target copies into a0 then v1. So it's which one gets the copy.

Hmm, that's a local-alloc copy preference difference. To flip: swap the roles? But the code uses ua and ub differently later.

Actually maybe the fix: change `ua = ub = E;` to `ub = ua = E;` (swap order in the chain) — then ub is the copy and ua the direct, flipping which reg gets what. Let me test that: `ub = ua = (sx - ...) << sh;`.

Hmm but that changes which pseudo gets the E value. Target wants a0 = copy result? Let's test a few:
- `ub = ua = E;`
- separate: `ua = E; ub = ua;`
- `ub = E; ua = ub;`

I already tried `ub = E; ua = ub;` (c2a) → 28. Try `ua = E; ub = ua;` and `ub = ua = E;`.

Let me also get the c3b diff.

Let me build the combined base first: take orig, remove barrier 1 line, remove barrier 4 line and insert the do-while. Then variants for 2 and 3.

Actually simpler: apply edits to c4b.c (which has b4 cracked, others present) then remove b1 and b3/b2 as needed.

Let me create a generator that builds from orig:
- combo base = orig - b1 - b4(with do-while ott) - b3(with c3b swap) = then only b2 left.

Let me write gen2.py.
