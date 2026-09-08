/* func_80139A8C — shared body (overlay slot 0x80128158, h_exact a66e14d1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80014E80(s32 a0, s32 a1);
extern void func_8001931C(void);
extern s16 D_8012752C;
void func_80139A8C(s32 a0) {
    s32 s0 = a0;
    s32 v0;
    s32 v1;
    v0 = *(s32 *)(s0 + 0x8);
    if ((v0 & 0x2021) != 0) {
        return;
    }
    if ((s16)func_80014E80(0, 0x20) == 0) {
        return;
    }
    v0 = *(s32 *)(s0 + 0x8);
    v1 = v0 | 0x20;
    *(s32 *)(s0 + 0x8) = v1;
    if ((v1 & 0x10000) == 0) {
        return;
    }
    *(s32 *)(s0 + 0x8) = (v1 & 0xFFFEFFFF) | 0x20000;
    func_8001931C();
    D_8012752C = 0;
}
