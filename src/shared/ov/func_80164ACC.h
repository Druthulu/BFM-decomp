/* func_80164ACC — shared body (overlay slot 0x80128158, h_exact 60a8185e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
extern u8 D_80126720[];
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
void func_80164ACC(s32 a0) {
    u8 *p;
    s16 buf[4];
    p = D_801202A0;
    if (p < p + 0x6480) {
        do {
            if (func_8014C308(a0, (s32)p, 0xB, 2) != 0) {
                if (func_8014C278(a0, (s32)p, 0x50) != 0) {
                    func_80015978((s32)(p + 4), (s32 *)buf);
                    buf[3] = 0;
                    func_8014C3A4((void *)a0, (s32)p, 0xB, (s32)buf);
                    *(s16 *)(p + 0x60) = (s16)(*(s16 *)(p + 0x60)) / 2;
                }
            }
            p += 0x10C;
        } while (p < D_80126720);
    }
}
