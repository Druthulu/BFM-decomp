---
ts: 2026-10-22T08:16:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vo4M16i20gNOuIQcSgHH
---
MATCH for 80182ED4! Score 0.

The mechanism: hoist the copy above the branch and route it through an s16 temp (`tmp = (s16)t; u = tmp;`), so the copy escapes cse's equivalence class and lands in the branch delay slot as `or v1,v0`.

Let me record it: win.c = c6.c, orig.c from src, results row, moves.md line.

Time check: it's been about 1h05m total. I have 2 items left: 8018302C and 8017E6EC.

Let me record 80182ED4 and move to 8018302C — which has the SAME pattern (`c = v + z` with the $0 pin)!

Target for 8018302C:
```
move v1,v0   (twice)
```
Let me get the target asm for 8018302C to see the exact shape. The score was 2 with `addu v1,v0,a1` → so the target has `move v1,v0` twice and mine has `addu v1,v0,a1` (the addend in a1).

So the same trick should apply: `c = v` where the copy must survive. But here the copy is `c = v + z` (twice, in two if-arms). And v is loaded from memory.

Per the note: "c = v + z" with z = $0 → `move v1,v0` (the target). And the lever-free `c = v` → cse propagates.

With the s16 trick: `tmp = (s16)v; c = tmp;`? Hmm, but here the structure is:
```
v = *(s16 *)(p + 0xC);
c = v + z;
if (v >= 0x801) { v = c - 0x200; *(s16 *)(p+0xC) = v; }
v = *(s16 *)(p + 0xD);
c = v + z;
if (v >= 0x801) { v = c - 0x200; *(s16 *)(p+0xD) = v; }
```
The copy `c = v` is in the entry block, and the use `v = c - 0x200` is inside the if-block → DIFFERENT BLOCKS ✓ (that's why the copy might survive if it's not a plain copy).

Hmm, but the note says `c = v` (plain) gives score 10 with "cse merges the loads into a copy and then propagates it". Hmm, the note says:
2. `c = v;` — score 10, 36 ins: combine folds the copy and cse propagates it, the two `move`s disappear and the load moves to $3.

So the plain copy died even across blocks. So I need the s16 trick.

But: v is loaded from `*(s16 *)(p+0xC)` → an s16 load → sign-extended → the same shape as our case! `tmp = (s16)v; c = tmp;` → the round trip is a no-op ✓.

Hmm, but wait: the target's `move v1,v0` — is v0 the loaded value? Let me check the target asm.

Let me get it.

Also note: the target has TWO `move v1,v0` (one per arm) — with the same v1? The note says "the target (52/38 ins)". Hmm, 52 ins target vs 38 mine? That's a big difference. Hmm, but the score was 2 with 38 vs 38. Hmm, the earlier note said "Target (52/38 ins)" maybe meaning (target 52 / lever-free 38)? But the diff showed "mine 38 ins, target 38 ins". OK, so both 38.

Let me look at the target asm for 8018302C.

Then apply the trick.

Let me record 80182ED4 first and get the 8018302C target.
