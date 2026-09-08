/* func_8012B1B4 — shared body (overlay slot 0x80128158, h_exact 0019c45c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
void func_8012B1B4(s32 a0, s32 a1) {
    s32 sp10[4];
    func_800484EC(*(s32 *)(a0 + 0x20) + 0x34, a1, (s32)sp10);
    *(s32 *)(a0 + 0x10) = sp10[0];
    *(s32 *)(a0 + 0x18) = sp10[2];
}
