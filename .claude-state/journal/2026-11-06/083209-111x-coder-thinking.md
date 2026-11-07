---
ts: 2026-11-06T15:32:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mrIyj8tmgZYxkhPdxS3M
---
c2 is score 2: only the `li a0,2715` position differs — mine has it one slot later (mine[222] vs target[221]). So the ori and the li are swapped in order.

Target:
```
5130: sll a2,a2,0x8
5134: li a0,2715
5138: ori a1,a1,0x3000
513c: or a1,a1,a2
```
Mine (presumably):
```
5130: sll a2,a2,0x8
5134: ori a1,a1,0x3000
5138: li a0,2715
513c: or a1,a1,a2
```
So the `ori` and `li a0` are swapped. That's a sched1 order (both independent). This is the "sched1-birth-order" family — C0535's do{}while(0) trick might fix it!

C0535: "wrap the two statements in do { ... } while (0) — the block boundary splits cse1's EBB, so sched1 sees them in source birth order."

Our two insns: `vol = vol | 0x3000;` (ori) and `func_8002D4C8(0xA9B, ...)`'s `li a0,2715`. In source order: `vol = vol | 0x3000;` comes before the call → the ori should be born before the li a0. In mine, the li a0 is born before the ori (swapped).

Hmm, the target has li a0 (5134) then ori (5138). So the target's order is li a0 BEFORE ori. Mine has ori before li a0? Let me verify by dumping c2.

The diff says: insert target[221] li a0,2715 before mine[221]; delete mine[222] li a0. So mine[221] = ori, mine[222] = li a0. Target[221] = li a0, target[222] = ori. So yes: mine has ori then li; target has li then ori.

So I need the li a0 (the call's first argument 0xA9B) to be born before the ori. In the source, the call is after the ori statement. But sched1's birth order can differ.

Options:
1. Move the `vol = vol | 0x3000;` AFTER the call? No, it's an argument.
2. Reorder the source so the constant 0xA9B is materialized first — it already is (the call's arg evaluation). Hmm.
3. Use do-while(0) to split the EBB (C0535) so sched1 keeps birth order.
4. Put the ori *inside* the call argument expression (as the original does: `(vol | (0x3000 | sx)) & 0xFFFF`), which gives the target's order? The original (with the launder) has the ori at 5138 after li a0 at 5134. So the original's expression form gives the right order. But without the launder, the expression form scored 30 (nolaunder) — because the birth boost hoisted the pan multiply.

Hmm. So we need the 2nd set of vol (to kill the boost) AND the expression form `(vol | (0x3000|sx)) & 0xFFFF` (to get the right ori/li order).

Idea: give vol a 2nd set that's *not* the ori, and keep the call expression as the original. E.g., `vol = vol & 0xFFFF;` (a2, score 2 with the andi/sll issue) or a 2nd set that folds away.

What about `vol = vol | 0x3000;` but keep the call as `(vol | (0x3000 | sx)) & 0xFFFF`? Then the ori would be applied twice (0x3000|0x3000 = same), and gcc would fold the two oris into one? Let me test: the 2nd set `vol = vol | 0x3000;` and the call `(vol | (0x3000 | sx)) & 0xFFFF`. gcc would see `((vol|0x3000) | (0x3000|sx))` → fold to `(vol | 0x3000 | sx)` with a single ori. And the ori's position might match. Worth a test.

d1: 2nd set `vol = vol | 0x3000;` (right after the vol computation) + original call expression.
d2: 2nd set `vol = vol | 0x3000;` (just before the call) + original call expression.
d3: 2nd set `vol = vol & 0xFFFF;` (just before the call) + original call (a2-like but late) = c1 (score 6, 238).

Let me also try the do-while split for c2:
d4: `do { vol = vol | 0x3000; } while (0);` before the call.
d5: `do { vol = vol | 0x3000; func_8002D4C8(0xA9B, (vol | sx) & 0xFFFF); } while (0);`

Let me test d1, d2, d4, d5.
