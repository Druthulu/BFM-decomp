/* func_80147C30 — shared body (overlay slot 0x80128158, h_exact 33569688). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147CC8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern s32 D_80127090;
extern s32 D_80127094;
extern s32 D_80127098;
void func_80147C30(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 out[3];
    s32 *p0 = &D_80127090;
    s32 *p1 = &D_80127094;
    s32 *p2 = &D_80127098;
    func_80147CC8(a0, a1, a2, a3, (s32)out);
    D_80127090 = out[0];
    D_80127094 = out[1];
    D_80127098 = out[2];
    *(s32 *)(a0 + 0x10) = *p0;
    *(s32 *)(a0 + 0x14) = *p1;
    *(s32 *)(a0 + 0x18) = *p2;
    D_80127090 = 0;
    D_80127094 = 0;
    D_80127098 = 0;
}
