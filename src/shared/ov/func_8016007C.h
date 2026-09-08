/* func_8016007C — shared body (overlay slot 0x80128158, h_exact 624feab2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154A74(s32 a0, s32 a1);
extern u8 D_800B9A17;
extern u16 D_801270C0;
void func_8016007C(s32 a0) {
    *(s32 *)(a0 + 0x184) = 0;
    *(s16 *)(a0 + 0x18A) = 0;
    *(s16 *)(a0 + 0x188) = 0;
    *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) & ~0x10;
    D_800B9A17 = 1;
    func_80154A74(a0, 0x11);
    D_801270C0 = 1;
}
