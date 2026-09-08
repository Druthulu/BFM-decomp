/* func_80164864 — shared body (overlay slot 0x80128158, h_exact de5b1632). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80164ACC();
extern void func_80146CA0(void *a0);
void func_80164864(void *a0) {
    s32 s = (s32)a0;
    s32 p = *(s32 *)(s + 0x20);
    s32 sum;
    s32 v;
    s32 w;
    s32 limit;
    sum = *(u16 *)(s + 0x60) + *(u16 *)(s + 0x62);
    *(u16 *)(s + 0x60) = sum;
    *(u16 *)(p + 0x1A) = *(u16 *)(p + 0x1A) + sum;
    if (*(s32 *)(s + 0x50) == 0) {
        limit = 0x4000;
        v = *(u16 *)(p + 0x1C) + 0x100;
        w = *(u16 *)(p + 0x12) + 0x71;
        *(u16 *)(p + 0x1C) = v;
        *(u16 *)(p + 0x18) = v;
        *(u16 *)(p + 0x12) = w;
        func_80164ACC();
    } else {
        limit = 0x2000;
        v = *(u16 *)(p + 0x1C) + 0x200;
        w = *(u16 *)(p + 0x12) - 0x71;
        *(u16 *)(p + 0x1C) = v;
        *(u16 *)(p + 0x18) = v;
        *(u16 *)(p + 0x12) = w;
    }
    if (limit < *(s16 *)(p + 0x1A)) {
        func_80146CA0(a0);
    }
}
