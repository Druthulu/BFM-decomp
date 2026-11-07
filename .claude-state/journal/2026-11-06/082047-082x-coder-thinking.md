---
ts: 2026-11-06T15:20:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_duYkyjhAqEzwPrAii7ul
---
No luck. Item 1 is a WALL: 35 scored tries, best 2 (b4 identity mask, which doesn't count as a crack), real-C best 16 (h1) / 18 (k1) / 30.

Hmm wait, actually the WALL best should be "the lowest score of a lever-free body". h1 (do-while) is a real-C lever-free body scoring 16; k1 scores 18; b4 scores 2 but with an identity statement. I'll record best 2 and note in evidence that it's an identity mask (not a crack); the best real-C body is 16 (do-while, h1).

Wall tag: what fits? The mechanism: the launder's second set changes sched1's ready-list timing → allocation → the vol/pan multiply order. A tag: `sched1-ready-order` or `sched1-uid-order`. From walls.txt there's `sched1-birth-order` (sched1 orders two independent insn births opposite to source; reorder moves the other). Our case: the re-tie's set node changes the ready-list order/timing. Close to `sched1-birth-order`? Not exactly (it's not the birth boost; it's the ready-list insertion order influenced by the extra node). I'll use a new tag `sched1-relist-timing` or reuse `sched1-birth-order`. The instruction says "wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". Let me define a new one: `sched1-node-timing` — the re-tie's extra set node shifts the ready-list order (insn 478's presence), flipping vol/pan multiply order. Actually, let me phrase: `sched1-relist-order`.

Hmm, but wait. Before finalizing, let me reconsider one more time whether the mask variant b4 might actually be acceptable. The rule says identity-statement launders do NOT count as a crack. `vol = vol & 0xFFFF` is an identity *in context*. So no.

But hmm — is it really identity? The expression `(vol | (0x3000 | sx)) & 0xFFFF` — the compiler emits `ori a1,a1,0x3000; or a1,a1,a2; andi a1,a1,0xffff`. With `vol & 0xFFFF` first, the result is the same. Yes identity.

OK. Now, before moving on, let me reconsider whether there's a *natural* body that the dev missed. The dev swept 9 spellings for the re-tie. The item is in the shard because it's a launder-only body. It may well be a genuine wall.

Given the time budget (I'm ~50 min in on item 1), let me now:
1. Write notes.md for item 1.
2. Append a results.tsv row for item 1.
3. Run the candidate set on items 2-5 (30+ tries each), record WALLs.
4. Append moves.md lines.
5. Write the log.

For efficiency, I'll run sc.sh on each item with the same ~35 candidate files. But the candidate files were generated from item 1's orig.c with item-1-specific symbol names (D_801B84C4, V8_80188498, func_80188498). Each item's body differs in: the function name, the V8 struct name, and two D_ symbols. So I must regenerate the candidates per item from that item's orig.c.

I'll generalize the generator: a single script that takes orig.c, out dir, and applies a list of transformations (the same ones). The transformations reference generic patterns (vol/sx/av lines) that are identical across items. The mk scripts use only generic patterns except mk2 (fine), so they work on any item's orig.c.

Let me write a single driver script that generates all candidate variants from an orig.c into the item dir, then score them all. I'll reuse the transformation definitions.

Let me create gen_all.py that writes ~36 candidates (a0,a1,a2,b1-b8,c1,c2,d1-d5,e1-e4,h1-h4,i*,j*,k*,l*) using the same patterns. Then for each item: generate + sc.sh.

Wait — but I must be careful: the constraint says "every file you write goes under .run/P40/T11/<shard>/" — yes, item dirs are under the shard.

Also the per-item FRESH step: diff orig.c against the current src def. I extracted orig.c from the current src just now, so they match. Good — note that.

Let me write the driver. It must handle each item's own orig.c. All patterns are generic (vol, sx, av, the call line `func_8002D4C8(0xA9B, ...)` — same across items? Yes, the function body is identical except the extern symbol names and the V8 name, which don't appear in my patterns). Good.

Let me write gen_all.py.
