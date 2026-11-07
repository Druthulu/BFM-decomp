---
ts: 2026-11-06T05:28:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TfZtWgFA8X3kKCaaqdUY
---
1.1s per score. 30 candidates ≈ 35 s. Good.

Let me write the item-5 variants. First, let me re-read the source body (I have it). Let me create a generator with ~30 variants.

Base (nobar):
```c
extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);
extern s16 D_801E7010;
extern s16 D_801E7012;
s32 func_80180D38(void *a0)
{
    void *p;
    u16 st;
    if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) > 0x4000) {
        return 0;
    }
    p = *(void **)((s32)a0 + 0x64);
    st = *(u16 *)((s32)p + 0x2);
    switch (st) {
    case 3:
        *(s16 *)((s32)p + 0x2) = 8;
        break;
    case 2:
        if (*(u16 *)((s32)p + 0x34) != 1) {
            return 0;
        }
        goto hit;
    case 4:
        if (*(u16 *)((s32)p + 0x34) != 0) {
            return 0;
        }
    hit:
        D_801E7010 = st;
        D_801E7012 = *(u16 *)((s32)p + 0x34);
        *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 10;
        break;
    default:
        return 0;
    }
    func_80178BF8();
    return (s32)func_80172710;
}
```

Variants:
1. invert early return with if/else.
2. early return `<= 0x4000` inverted: `if (func(...) <= 0x4000) { ... } return 0;` — but then the body's `return (s32)func_80172710;` inside.
3. `s32 r = func_8012BD14(...); if (r > 0x4000) return 0;`
4. `switch` → if/else if chain.
5. `st` declared u16 vs s16 vs s32.
6. `p = *(void**)...` before the call? No, must be after (the call may change a0->0x64).
7. Reorder `case 3` and others.
8. `hit:` label as a separate if.
9. return 0 → `return 0;` vs `goto fail;` with a fail label.
10. Use `*(u16*)((s32)p+2)` etc.

Let me write the generator. I'll write each variant body as a template string. That's verbose but fine.

Actually, to be efficient, let me write a script that emits variants from a base with substitutions. Let me write ~30 explicit variants using a compact approach: a list of (name, body) where body is the full function text.

Let me write it.
