---
ts: 2026-10-22T08:56:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_VriyAVGXLS8zFRt0dF2Z
---
The tiny function was optimized away (no globals). Let me make a test with a global pseudo that has a copy from a hard reg and survives. E.g.:

```c
s32 tf(s32 a, s32 b)
{
    s32 p;
    s32 q;
    if (a > 0) { p = a; q = b; } else { p = b; q = a; }
    return p * q;
}
```
Here p and q are globals (defined in 2 blocks). The copy p = a: a is a param in a0 → the copy (set (reg p) (reg a0)) → "p prefers 4"?

Let me build a test with such a function plus padding.
