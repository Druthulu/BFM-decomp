/* func_8018419C — shared body (overlay slot 0x80128158, h_exact 9b1d32bc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_800B99DC;
extern u8 D_8018B358[];
extern void func_8013C9C4(s32);
void func_8018419C(s32 a0) {
    s16 val16;
    u16 val;
    u16 temp;
    if (*(s16 *)(a0 + 0xDE) != 0) {
        val = *(u16 *)(a0 + 0xE0);
        val--;
        *(u16 *)(a0 + 0xE0) = val;
        val16 = (s16)val;
        if (val16 == 0) {
            func_8013C9C4((s32)D_8018B358);
            temp = D_800B99DC;
            temp = (temp & 7) + 3;
            *(u16 *)(a0 + 0xE0) = temp;
        }
        val = *(u16 *)(a0 + 0xDE);
        val--;
        *(u16 *)(a0 + 0xDE) = val;
    }
    val = *(u16 *)(a0 + 0xDC);
    val--;
    *(u16 *)(a0 + 0xDC) = val;
    val16 = (s16)val;
    if (val16 == 0) {
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}
