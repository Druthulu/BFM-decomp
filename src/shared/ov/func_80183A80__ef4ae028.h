/* func_80183A80 — shared body (overlay slot 0x80128158, h_exact ef4ae028). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_8018EDD0[];
extern u8 D_801A7CB0;
extern s32 func_8013767C(s32 a0);
extern void func_80147324(s32 a0);
void func_80183A80(s32 a0) {
    s16 v;
    s16 d;
    v = D_8018EDD0[*(u8 *)(a0 + 0x20C)];
    if (v != 0) {
        d = v - *(u16 *)(a0 + 0xE);
        v = d;
        if (d < 0) {
            v = -d;
        }
        if (v < 0x180) {
            *(s32 *)(a0 + 0x198) = func_8013767C((s32)&D_801A7CB0);
            switch (*(u8 *)(a0 + 0x20C)) {
            case 0:
                func_80147324(0x5A1);
                break;
            case 1:
                func_80147324(0x5F1);
                break;
            case 2:
                func_80147324(0x5F2);
                break;
            }
            *(u8 *)(a0 + 0x20C) += 1;
        }
    }
}
