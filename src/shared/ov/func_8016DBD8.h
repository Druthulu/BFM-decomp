/* func_8016DBD8 — shared body (overlay slot 0x80128158, h_exact 389779e8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149374(s32 a0, s32 a1);
extern void func_800D1FC8(s32 a0, s32 a1);
void func_8016DBD8(u8 *a0) {
    *(s32 *)(a0 + 0x4) = 0;
    *(s32 *)(a0 + 0x8) = 0;
    *(s32 *)(a0 + 0xC) = 0;
    func_80149374(*(s32 *)(a0 + 0x34), (s32)(a0 + 0x4));
    func_800D1FC8((s32)a0, 5);
}
