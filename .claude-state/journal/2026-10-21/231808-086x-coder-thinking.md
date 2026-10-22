---
ts: 2026-10-22T05:18:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_cOCgorZIZMDBsYHmDFRZ
---
The item's orig.c is STALE: the current src has `*(u16 *)(q - 0x2)` (not `*(u16 *)q`) in the second pair. So all my candidates (based on orig.c) used the wrong source!

I must regenerate the candidates from the CURRENT src. The brief says: "Start from the current def in src (copy to <dir>/orig.c)" — so orig.c should be the current def. The previous shard's orig.c is stale.

This is a significant finding! Let me redo the item-4 candidates from the current src (with the pins removed = nopin).

Let me create a fresh nopin from the current src (removing the register-asm declarations) and re-run the promising variants.

The current src:
```
void func_8017849C(void) {
    u8 *p;   /* $s1 base */
    register u8 *q __asm__("$16");   /* $s0 = base + 0x54 */
    s32 i;   /* $s2 counter */
    p = (u8 *)D_801202A0;
    func_801787D4();
    i = 0;
    func_8012A908();
    q = p + 0x54;
    do {
        if (*(u16 *)p != 0 &&
            (*(s16 *)&D_801270C0 == 1 || (*(u16 *)(q + 0x1E) & 0x1000) != 0)) {
            register s32 tbl __asm__("$3"); register s32 c6c __asm__("$2");
            func_8017869C((s32)p);
            *(s32 *)(q - 0x1C) = *(s32 *)(q - 0x50);
            c6c = *(u8 *)(q + 0x6C);
            *(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
            tbl = D_8011DB08;
            *(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);
            if (c6c != 0 && *(u8 *)(q + 0x6D) != 0) {
                func_80130D0C((s32)p);
            } else {
                (*(void (**)(s32))(tbl + *(u16 *)p * 4))((s32)p);
            }
            if (*(s32 *)(q - 0x34) != 0) {
                *(s16 *)(*(s32 *)(q - 0x34) + 8) =
                    *(u16 *)(q - 0x4E) + *(u16 *)(q - 0x4);
                *(s16 *)(*(s32 *)(q - 0x34) + 10) =
                    *(u16 *)(q - 0x4A) + *(u16 *)(q - 0x2);
                *(s16 *)(*(s32 *)(q - 0x34) + 0xC) =
                    *(u16 *)(q - 0x46) + *(u16 *)q;
            }
        }
        i++;
        q += 0x10C;
        p += 0x10C;
    } while (i < 0x60);
    if (*(s16 *)&D_801270C0 == 1) {
        func_8013E370();
    }
}
```

Also I should check items 1-3 for stale orig.c! Item 1 (func_8014FD54) and item 3 (func_801536DC) — let me diff those too. Ugh, if they're stale, my results are wrong!

Let me check all three.

This is important. Let me diff now.
