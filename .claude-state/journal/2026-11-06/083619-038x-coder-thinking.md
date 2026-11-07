---
ts: 2026-11-06T15:36:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_niUgDQhkd2smY2Q1mGOb
---
Key: dead-reset must be "immediately after" the use. The classic case: `&local` passed to two calls:
```
p = expr;
f(..., p);
p = 0;
g(..., p);  -- no wait, second call needs p
```
Hmm, the classic case is `f(&local); p = 0; g(&local)`? Let me re-read: "To stop cse merging two computations of the same address/expression (the classic case: `&local` passed to two calls)":
```
p = expr;        /* name it            */
f(..., p);       /* use it             */
p = 0;           /* DEAD-RESET, immediately after */
```
Then presumably the second call is `g(..., &local)` or `g(..., p)` after reassigning p. Wait if p=0 then g(p) is wrong. So the second call must use the expression again, not p:
```
p = &local;
f(p);
p = 0;
g(&local);
```
That's the shape: name the first use, dead-reset after, then use the raw expression for the second. In our case:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
func_800491AC((u8 *)&D_800AF630 + 0x18);
```
The dead-reset kills the cse equivalence of mb, and the second use is the raw constant expression. But the raw constant expression `&D_800AF630+24` would still be constant-folded and could be materialized once... but the first use `mb+0x18` — mb is a constant, so it also folds to the same expression. Hmm. Unless the first use being through mb creates a register equivalence and the second raw use is separate.

Let me just try: variant k:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
func_800491AC((u8 *)&D_800AF630 + 0x18);
```
Also variant l with `func_800491AC((u8 *)D_800AF630 + 0x18)`.

Actually, in the C0414 example, `p = &local` — the local address isn't a constant; it's sp+offset, a runtime value. So p's reg_equiv is (plus sp K) which cse merges across calls. Here &D_800AF630 is a symbolic constant, so cse might handle it differently.

Let me test k and l.
