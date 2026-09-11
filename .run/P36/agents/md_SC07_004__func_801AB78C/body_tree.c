void func_801AB78C(void *a0) {
    volatile u8 *p = &D_801F88BA;
    register s32 b __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    s32 t;
    if (*p == 0) {
        func_801292C8((u8 *)a0);
    } else {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) += 0x200;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
        b = *p;
        t = b - 0x10;
        if (b != 0) {
            b = t;
            if (t < 0) {
                b = 0;
            }
            *p = (u8)b;
        }
    }
}
