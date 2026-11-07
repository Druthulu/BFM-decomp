---
ts: 2026-11-07T00:52:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R7xjE2T6bjvNS7gJd3pF
---
The banked sibling func_8018F060 solved the SAME residual with a REAL-C move:

```
mb = (u8 *)&D_800AF630;
a = mb + 0x18;
func_8004914C(a);
a = 0;                       /* DEAD RESET — C0414! */
func_800491AC(mb + 0x18);
```

That's exactly the dead-reset move: a named temp `a` for the first sum, used, then `a = 0;` (dead reset) — which kills cse's equivalence for the first `mb+0x18`, and the second `mb+0x18` becomes a distinct expression computed from mb.

Let me apply this to our function: in item 3, the current shape is:
```
    mb = (u8 *)&D_800AF630;
    func_8004914C(mb + 0x18);
    func_800491AC(mb + 0x18);
```
Replace with:
```
    mb = (u8 *)&D_800AF630;
    a = mb + 0x18;
    func_8004914C(a);
    a = 0;
    func_800491AC(mb + 0x18);
```
with `u8 *a;` declared. The sibling declares `u8 *a;`.

Note the sibling has `mb` and `a` declared as `u8 *`. Our function declares `u8 *mb;` only — I can add `u8 *a;` to the declarations (inside the body — allowed, it's a body-local decl).

Let me try it.
