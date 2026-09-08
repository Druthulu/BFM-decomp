/* func_80188478 — shared body (overlay slot 0x80128158, h_exact 82a7b589). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BD14(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8012BA10(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern u8 D_801E7BB8[];
void func_80188478(s32 a0) {
    s32 v1;
    if (*(u16 *)(a0 + 0x34) != 0) {
        if (*(u16 *)(a0 + 0x34) == 1) {
            if (func_8012BD14(a0) >= 0x4001) {
                if (*(s16 *)(a0 + 0xFC) == 0) {
                    func_8012A828(a0, D_801E7BB8);
                    *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
                }
                *(s32 *)(a0 + 0x10) =
                    -(func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 7);
                *(s32 *)(a0 + 0x18) =
                    -(func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 7);
            } else {
                *(s16 *)(a0 + 0xFC) = 0;
                *(s32 *)(a0 + 0x10) = 0;
                *(s32 *)(a0 + 0x18) = 0;
            }
            v1 = func_8012CBCC(a0);
            if ((v1 & 0x8000) && (v1 & 0x6000)) {
                *(s16 *)(a0 + 0x16) = -0x14;
            }
        }
    }
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012BA10(a0, 4);
}
