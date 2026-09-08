/* func_8017C5A0 — shared body (overlay slot 0x80128158, h_exact 348e565c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017C218(int);
void func_8017C5A0(void *a0) {
    s32 t;
    s32 p;
    t = *(s32 *)((s32)a0 + 0x1C);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    p = *(s32 *)((s32)a0 + 0x34);
    if (t < 0xC) {
        *(u16 *)((s32)a0 + 0x12) += 0xE0;
    } else {
        *(s16 *)(p + 0x64) = 0;
        *(s16 *)(p + 0x60) = 0;
        *(s16 *)(p + 0x62) = 0x3000;
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(u16 *)((s32)a0 + 0x2) += 1;
    }
    ((void (*)(void *))func_8017C218)(a0);
}
