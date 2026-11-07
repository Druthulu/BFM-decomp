---
ts: 2026-11-06T05:48:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RJ2970FThb1QltIOQtxY
---
Interesting! I see another coder's move in moves.md: `barrier | func_80150170 | MATCH — s16 a[4]/b[4] element reads (same stack layout as u8[8]): compare a[1]/b[1] stays lh, arm stores re-load HImode as lhu, tail keeps u16 lhu; frame 56; 0 on 141/141 includers (G21x)`.

That's a twin of my item 5 (func_8014FE60)! Another shard (G21x) cracked func_80150170 with a similar approach: "s16 a[4]/b[4] element reads ... arm stores re-load HImode as lhu". That suggests a cleaner move for item 5: declare a/b as `s16 a[4]` instead of `u8 a[8]`, which makes the comparison's load `lh` and the store's load `lhu` (different types → no cse forward).

That's a *real* C move (declaration width/type change) rather than a struct cast! Let me try it for item 5 — it might score 0 and be cleaner (avoiding the "identity address" concern).

The other coder's function is a twin (func_80150170). Let me apply: change `u8 a[8]; u8 b[8]; u8 out[8];` to `s16 a[4]; s16 b[4];` etc., and adjust the accesses.

Hmm, but the stack layout: a[8] u8 vs a[4] s16 — same 8 bytes. The accesses `*(s16 *)(a + 2)` would become `a[1]`, `*(s16 *)(a + 0)` → `a[0]`, `*(s16 *)(a+4)` → `a[2]`.

And the calls `func_8014FFDC(e, a, out)` take void* — fine with s16*.

Let me try:
```
s16 a[4];
s16 b[4];
s16 out[4];
*(s16 *)(a + 0) = ...  → a[0] = ...
```
Hmm, but `a[0] = *(u16 *)(e+6)` — assigning u16 to s16: the store is `sh`. The comparison `a[1] < b[1]` → `lh`. The store `*(u16 *)(a+0)` → `a[0]` (s16 load → `lh`), but the target uses `lhu` for the store! Per the other coder's note: "arm stores re-load HImode as lhu" — so the stores must be `(u16)` reads: `*(u16 *)(a + 0)` with a as s16? Hmm.

The target's arm store: `lhu v0,16(sp)` (zero-extend) and the comparison `lh v0,18(sp)` (sign-extend). So the same address is read as lhu for the store and lh for the comparison. With `s16 a[4]`, both reads would be `lh`. Unless the store uses a `u16` cast: `*(u16 *)&a[0]` — a cast again.

Hmm, the other coder's move: "s16 a[4]/b[4] element reads (same stack layout as u8[8]): compare a[1]/b[1] stays lh, arm stores re-load HImode as lhu". So with `s16 a[4]`, the comparison `a[1]` is lh, and the arm store `*(u16 *)(a+0)`... hmm, if a is s16*, then `*(u16 *)(a+0)` is a cast.

Maybe they declared `u16 a[4]`? Then the comparison `(s16)a[1]` → lh, and the store `a[0]` → lhu.

Let me try: declare `u16 a[4]; u16 b[4];` and write the comparison as `(s16)a[1] < (s16)b[1]` and the stores as `a[0]`, `a[1]`, `a[2]`.

That's clean real C (declaration width change, per the C0505 catalog "s16/u8 widths").

Let me test this variant (w4) and see if it scores 0. If yes, it's a cleaner win than the struct cast.

Also, the tail of the function uses `a` and `b` in the else arm and the final block. Let me transform the whole body.

Let me write w4 carefully:

```c
s32 func_8014FE60(void *e) {
    extern u8 D_801152A8[];
    extern s32 func_8014FFDC(s32 e, void *a1, void *a2);
    extern s32 func_80150150(s32 e, s32 a1);
    u16 a[4];
    u16 b[4];
    u16 out[4];
    s32 r5;
    s32 r6;
    a[0] = b[0] = *(u16 *)(((s32)e) + 6);
    a[1] = b[1] = *(u16 *)(((s32)e) + 0xA) - 0x10;
    a[2] = b[2] = *(u16 *)(((s32)e) + 0xE);
    r5 = func_8014FFDC(((s32)e), a, out);
    r6 = func_80150150(((s32)e), (s32)b);
    if (r6 == 0) {
        b[1] = 0x7fff;
    }
    if ((r5 | r6) != 0) {
        if ((s16)a[1] < (s16)b[1]) {
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
        t = a[0];
        c = 0x7fff;
        *(s16 *)(((s32)e) + 0x7a) = c;
        *(s16 *)(((s32)e) + 0x78) = t;
        t = a[2];
        *(s16 *)(((s32)e) + 0x7c) = t;
        *(u16 *)(((s32)e) + 0x7e) |= 1;
    }
    return 0;
}
```

Note the original uses `u8 a[8]` and byte offsets. The tail uses `*(u16 *)(a + 0)` and `*(u16 *)(a + 4)` → a[0], a[2].

Also `__builtin_memcpy((void *)(e+0x80), out, 8)` — with out as u16[4], `out` is u16* (8 bytes) — fine.

Let me test w4. If it scores 0, use it instead of w1 (cleaner).

Time: 22:48. Let me do it.
