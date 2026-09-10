/* func_8016A08C — shared body (overlay slot 0x80128158, h_exact cc17e4fe). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EBF;
extern void func_80148534(s32 a0, s32 a1);
extern void func_8016A290();
extern void func_80147324(s32 arg0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147364();
extern void func_80146C3C();
void func_8016A08C(s32 param_1) {
    s32 s0;
    void *s1;
    u8 buf20[8];
    u8 buf18[8];
    s32 iVar4;
    s16 sVar2;
    if (D_80078EBF != 0) {
        s1 = buf18;
        ((void (*)(void *, void *))func_80148534)(buf20, s1);
        *(s32 *)(param_1 + 0x30) = (s32)(u32)D_80078EBF - 0x18;
        if ((s32)((u32)D_80078EBF - 0x18) >= 0) {
            func_8016A290(param_1, buf20, s1);
            iVar4 = *(s32 *)(param_1 + 0x1C) + 1;
            *(s32 *)(param_1 + 0x1C) = iVar4;
            if (iVar4 == 4) {
                func_80147324(0x44C);
            }
            if (D_80078EBF < 0x80) {
                sVar2 = 0;
                do {
                    sVar2 = sVar2 + 1;
                } while (sVar2 < 2);
                ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x17, param_1, (s32)*(s16 *)(param_1 + 6), (s32)*(s16 *)(param_1 + 0xA),
                              (s32)*(s16 *)(param_1 + 0xE), 0, 0);
            } else {
                if (*(s16 *)(param_1 + 0x2A) == 0) {
                    *(s16 *)(param_1 + 0x2A) = 1;
                    *(s32 *)(param_1 + 0x1C) = 0x100;
                }
                if ((*(u32 *)(param_1 + 0x1C) & 0x1F) == 0) {
                    func_80147324(0x44D);
                }
            }
        }
    } else {
        ((void (*)(s32, s32))func_80147364)(4, 0x44C);
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}
