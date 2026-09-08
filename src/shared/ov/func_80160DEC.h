/* func_80160DEC — shared body (overlay slot 0x80128158, h_exact 8215bf05). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);
void func_80160DEC(u8 *a0) {
    *(s32 *)(a0 + 0x1AC) = 0;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
    func_801553C0((s32)a0);
    *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) & -0x181;
    func_80154A74((s32)a0, 0x11);
}
