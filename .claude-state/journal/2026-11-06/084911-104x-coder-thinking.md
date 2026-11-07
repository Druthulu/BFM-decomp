---
ts: 2026-11-06T15:49:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lFmMSDBYq3IKn8E3hE2J
---
In a1, cse deleted the second `(plus 82 24)` (insn 241 became `a0 = 140` — folded to the first expression's reg).

In the orig, the asm's opaque set of 82 makes insn 241 a fresh `(plus 82 24)` with no REG_EQUAL, and cse can't fold it to 140.

So the fix: after the first call, make 82's value unknown. A real second set of mb that is value-preserving.

Value-preserving 2nd set of a pointer to &D_800AF630... 

What about `mb = mb + 0;`? folds at tree level.
`mb = (u8 *)((s32)mb | 0);` folds.

Hmm. What about using a *different* variable that aliases? 

Wait — here's an idea based on the "dead-reset" pattern but with the restore done via a *recomputation from a saved base*:

```
u8 *base = (u8 *)&D_800AF630;
mb = base;
call1(mb + 0x18);
mb = 0;          // dead-reset: 82's class emptied
mb = base;       // 2nd set: mb = base
call2(mb + 0x18);
```
cse: `(set mb base)` then `(set mb 0)` then `(set mb base)`. After the last set, cse knows mb ≡ base (a register). fold_rtx for `(plus mb 24)` → substitutes base → `(plus base 24)`. Was `(plus base 24)` in the table? The first expression was `(plus mb 24)` (recorded when mb was a different qty? no, mb and base are in the same qty after the copy). Hmm: `(set mb base)` merges mb into base's qty (first = base). Then `(plus mb 24)` canon → `(plus base 24)` — recorded in the table with value reg 140. Then `mb = 0` invalidates the qty (all entries mentioning base/mb removed). Then `mb = base` re-merges. Then `(plus mb 24)` → `(plus base 24)` — the table entry was invalidated by the `mb=0`? invalidate(0-set) removes entries mentioning mb; since mb and base are the same qty, it removes all entries mentioning base too. So `(plus base 24)` is gone → recompute! 

And the codegen: `base` and `mb` would be the same register (coalesced); `mb = 0` is a dead store (removed by flow); `mb = base` is a self-move (removed). So the final code has no extra insns.

This is exactly the item-3 pattern (keep = n; n = 0; n = keep).

So:
```
u8 *base = (u8 *)&D_800AF630;   // or reuse mb
mb = base;
call1(mb + 0x18);
mb = 0;
mb = base;
call2(mb + 0x18);
```
Hmm, but in item 3 the pattern was `keep = n; ...; n = 0; n = keep;`. Here `base` plays keep.

But careful: in item 3 the reset/restore came *after* the first expression. Here the first call's arg is computed, then the reset, then restore.

Let me write it as:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
{
    u8 *keep = mb;
    mb = 0;
    mb = keep;
}
func_800491AC(mb + 0x18);
```
Hmm, but `keep = mb` is a copy; then mb = 0; mb = keep. cse: keep joins mb's qty; mb=0 invalidates; mb=keep → mb joins keep's qty. The expression `(plus mb 24)` → canon to keep or mb; the table's old entry `(plus mb 24)` was invalidated. So recompute. 

Let me test this for all three sites. Since the sites are identical, apply to all three.

Let me also try the simpler form without a block:
```
u8 *keep = mb;
mb = 0;
mb = keep;
```
declared as a temp inside the function? Use a block.

Let me test.
