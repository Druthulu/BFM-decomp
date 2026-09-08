/* func_8018B158 — shared body (overlay slot 0x80128158, h_exact d5ee5732). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012E8E0(s32 a0, s32 a1);
extern u8 D_801E04F8[];
void func_8018B158(s32 a0) {
    *(s16 *)(a0 + 0x2) = 1;
    func_8012E8E0(a0, (s32)&D_801E04F8);
    *(s16 *)(a0 + 0xFE) = 0;
    *(s16 *)(a0 + 0xFC) = 0x80;
}
