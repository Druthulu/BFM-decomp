/* func_801741EC — shared body (overlay slot 0x80128158, h_exact 6d4886d5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
extern s16 D_80126B3C;
extern s16 D_8011F9C8;
void func_801741EC(u8 *a0) {
    s32 v0;
    s32 s1;
    s32 t;
    v0 = *(s32 *)(a0 + 0x20);
    s1 = func_80012B04(*(s16 *)(v0 + 0x12), D_80126B3C, 4);
    if ((s16)s1 == 0) {
        D_8011F9C8 = 1;
        func_80171A1C(a0);
        func_80174650((s32)a0);
    }
    t = *(s32 *)(a0 + 0x20);
    *(u16 *)(t + 0x12) = (*(u16 *)(t + 0x12) + s1) & 0xFFF;
}
