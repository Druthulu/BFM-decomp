---
ts: 2026-10-22T08:56:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZKoJ61Zm2RYtaYt7o9kh
---
Still optimized away (the whole thing folded). The .greg dump shows the function with no insns — because the dump prints the *post-allocation* RTL and the function was fully optimized (the if-conversion). Hmm, the RTL shows only the block notes — the function body was simplified to a multiply.

Let me make the test function resist optimization: use volatile-ish or an opaque call. E.g.:

```c
extern s32 op(s32);
s32 tf(s32 a, s32 b)
{
    s32 p;
    s32 q;
    if (op(a) > 0) { p = a; q = b; } else { p = b; q = a; }
    return op(p) * q;
}
```

Let me try that.
