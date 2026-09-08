/* func_80146D30 — shared body (overlay slot 0x80128158, h_exact 42f2f95e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80127090;
extern s32 D_80127094;
extern s32 D_80127098;
void func_80146D30(s32 a0) {
    s32 *p = &D_80127090;
    *(s32 *)(a0 + 0x10) = *p;
    *(s32 *)(a0 + 0x14) = D_80127094;
    *(s32 *)(a0 + 0x18) = D_80127098;
    *p = 0;
    D_80127094 = 0;
    D_80127098 = 0;
}
