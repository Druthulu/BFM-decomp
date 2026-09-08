/* func_80172BC8 — shared body (overlay slot 0x80128158, h_exact 13280ca2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
extern s16 D_80126B32;
void func_80172BC8(void *a0) {
    s32 v0p = *(s32 *)((s32)a0 + 0x20);
    s32 r = func_80012B04(*(s16 *)(v0p + 0x12), D_80126B32, 4);
    s32 v1;
    if (((r << 16) >> 16) == 0) {
        func_80171A1C((u8 *)a0);
        func_80174650((s32)a0);
    }
    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)(v1 + 0x12) = (*(u16 *)(v1 + 0x12) + r) & 0xFFF;
}
