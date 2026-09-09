/* func_8014C6F4 — shared body (overlay slot 0x80128158, h_exact 1ac65d84). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8014C6F4(u8 *a) {
    extern u8 D_80078E78[];
    extern s32 D_8011F9D0;
    extern s32 func_8016F1AC(void);
    extern void func_80015978(s32 a0, s32 *a1);
    u8 *p = D_80078E78;
    u8 *e;
    register u8 *lim __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
    u8 *q;
    s32 want;
    u8 *src;
    if ((*(u32 *)(a + 0x44) & 2) != 0) {
        a[0x1C3] = 1;
    }
    if (((*(u32 *)(a + 0x44) ^ *(u32 *)(a + 0x48)) & *(u32 *)(a + 0x44) & 0x200) != 0) {
        a[0x1C3] = 0;
    }
    *(M8_8014C6F4 *)(a + 0x164) = *(M8_8014C6F4 *)(*(u8 **)(a + 0x20) + 0x10);
    if (func_8016F1AC() != 0
        || (((*(u32 *)(a + 0x44) & 0x200) != 0) && a[0x1C3] == 0)) {
        *(s16 *)(a + 0x162) = 1;
        goto tail;
    }
    if (p[0x49] == 0x17) {
        want = 0x22;
        q = (u8 *)&D_8011F9D0;
        lim = q + 0xC30;
        for (; q < lim; q += 0x68) {
            if (*(u16 *)q == want) {
                e = q;
                goto found;
            }
        }
        e = 0;
    found:
        if (e != 0) {
            src = e + 4;
            goto call;
        }
    }
    if (*(u16 *)a == 0x19) {
        goto done;
    }
    src = a + 4;
call:
    func_80015978((s32)src, (s32 *)(a + 0x15C));
done:
    *(s16 *)(a + 0x162) = 0;
tail:
    if (*(s16 *)(a + 0x15A) == 0) {
        *(u16 *)(a + 0x154) = *(u16 *)(a + 0x6);
        *(u16 *)(a + 0x156) = *(u16 *)(a + 0xA);
        *(u16 *)(a + 0x158) = *(u16 *)(a + 0xE);
    }
    *(s16 *)(a + 0x15A) = 0;
}
