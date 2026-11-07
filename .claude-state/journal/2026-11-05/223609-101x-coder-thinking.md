---
ts: 2026-11-06T05:36:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_X0N9meuPnxtv4afH8EKq
---
MATCH on the first includer! But this is a header item: MATCH only if score 0 on every includer. Let me check how many includers there are and run tryinc.py for k=0..n-1.

Let me first count includers. The tryinc wrapper rotates. I can run tryinc.py with increasing k until it wraps or errors. Better: look at how delever_search finds includers — `inc.get(tu, [])`. Let me write a small script to list includers. Or just run tryinc for k=0..N and check each prints a different includer until it repeats.

Let me run k=0..10 and see.

Also, I need to make sure the body is semantically equivalent. Let me review v_fix2:

```c
s32 func_80150170(void *e) {
    s16 a[4];
    s16 b[4];
    u8 out[8];
    s32 r5;
    s32 r6;
    a[0] = b[0] = *(u16 *)(((s32)e) + 6);
    a[1] = b[1] = *(u16 *)(((s32)e) + 0xA) - 0x10;
    a[2] = b[2] = *(u16 *)(((s32)e) + 0xE);
    r5 = func_801502EC(((s32)e), a, out);
    r6 = func_80150460(((s32)e), (s32)b);
    if (r6 == 0) {
        b[1] = 0x7fff;
    }
    if ((r5 | r6) != 0) {
        if (a[1] < b[1]) {
            *(s16 *)(((s32)e) + 0x78) = a[0];
            *(s16 *)(((s32)e) + 0x7a) = a[1];
            *(s16 *)(((s32)e) + 0x7c) = a[2];
            __builtin_memcpy((void *)(((s32)e) + 0x80), out, 8);
        } else {
            *(s16 *)(((s32)e) + 0x78) = b[0];
            *(s16 *)(((s32)e) + 0x7a) = b[1];
            *(s16 *)(((s32)e) + 0x7c) = b[2];
            __builtin_memcpy((void *)(((s32)e) + 0x80), D_801152A8, 8);
        }
        *(u16 *)(((s32)e) + 0x7e) &= 0xfffe;
        return 1;
    }
    {
        s32 c;
        s32 t;
        t = *(u16 *)(a + 0);
        c = 0x7fff;
        *(s16 *)(((s32)e) + 0x7a) = c;
        *(s16 *)(((s32)e) + 0x78) = t;
        t = *(u16 *)((u8 *)a + 4);
        *(s16 *)(((s32)e) + 0x7c) = t;
        *(u16 *)(((s32)e) + 0x7e) |= 1;
    }
    return 0;
}
```

Semantics check vs original:
- Original `*(s16*)(a+0) = *(s16*)(b+0) = *(u16*)(e+6)`: a[0]=b[0]=(u16)(e+6) truncated. New same.
- `*(s16*)(a+2) = ... = *(u16*)(e+0xA) - 0x10`: new `a[1] = b[1] = *(u16*)(e+0xA) - 0x10`. Same.
- `*(s16*)(a+4) = ... = *(u16*)(e+0xE)`: new a[2]=b[2]=... Same.
- calls: `func_801502EC(e, a, out)` — original passes `a` (u8*); new passes `s16* a` — the function is declared `void *a1`, so the pointer value is the same address. Fine.
- `func_80150460(e, (s32)b)` — same address.
- `if (r6 == 0) *(s16*)(b+2) = 0x7fff;` → `b[1] = 0x7fff;` same.
- `if (a[1] < b[1])` vs `*(s16*)(a+2) < *(s16*)(b+2)` — same.
- then-arm stores: `*(s16*)(e+0x78) = a[0]` — original `= *(u16*)(a+0)`. a[0] is s16, value bits same. The store is `sh` of the 16-bit value — same bits. ✓.
- `*(s16*)(e+0x7a) = a[1]` — same bits. ✓
- `*(s16*)(e+0x7c) = a[2]` — same. ✓
- memcpy same.
- `*(u16*)(e+0x7e) &= 0xfffe` same.
- tail: `t = *(u16*)(a+0)` same; `c=0x7fff`; stores; `t = *(u16*)((u8*)a+4)` = a+4 bytes = a[2] (offset 4) — same as original `*(u16*)(a+4)`. ✓
- `*(u16*)(e+0x7e) |= 1;` same.

One subtlety: `s16 a[4]` vs `u8 a[8]` — the original's `a+2`/`a+4` are byte offsets; the new `a[1]`/`a[2]` are element offsets (2 bytes each) — same memory. ✓

Alignment: u8 arrays are aligned 1; s16 arrays aligned 2. On the stack, the offsets in the target were 16,18,20 (a) and 24,26,28 (b) — even. The new layout gives a at 16,18,20,22 and b at 24,26,28,30. Matches the target's offsets. ✓

The `out` array: `u8 out[8]` at 32..39? In the target, out at 32. In the new body, out is declared after b — s16 a[4] (8 bytes), s16 b[4] (8), u8 out[8] → a=16, b=24, out=32. ✓

Great, the body is semantically equivalent.

Now, the header has many includers. Let me check the number and run tryinc for each. The TU is src/shared/ov/func_80150170.h — let me count includers.
