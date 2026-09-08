/* func_8014A850 — shared body (overlay slot 0x80128158, h_exact 962e53b5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80029AF4(void);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
extern u8 D_801202A0[];
s32 func_8014A850(s32 param_1) {
    s32 i;
    s32 cnt;
    s16 buf[3];   /* 0x18, 0x1A, 0x1C */
    s16 out[4];   /* 0x20 .. 0x27 (s2) */
    s32 x;
    s32 uVar2;
    s16 *po;
    cnt = 0;
    po = out;   /* anchors &out ($s2) materialization between cnt=0 and i=0 (scheduler LUID) */
    i = 0;
    do {
        s32 e = (s32)&D_801202A0 + i;
        if (*(u16 *)(e + 0) != 0 && *(s32 *)(e + 0x58) != 0 &&
            (*(u16 *)(e + 0x5C) & 0x8000) != 0 && *(u8 *)(e + 0xC1) == 7) {
            x = *(u16 *)(param_1 + 6) - *(u16 *)(e + 6);
            buf[0] = x;
            buf[1] = *(u16 *)(param_1 + 0xA) - (*(u16 *)(e + 0xA) + 0x40);
            buf[2] = *(u16 *)(param_1 + 0xE) - *(u16 *)(e + 0xE);
            if ((((s16)x < 0) ? -(s16)x : (s16)x) < 0x40) {
                if (((buf[2] < 0) ? -buf[2] : buf[2]) < 0x40) {
                    if (((buf[1] < 0) ? -buf[1] : buf[1]) < 0x40) {
                        *(s32 *)(param_1 + 0x18C) = e;
                        func_80015978(param_1 + 4, (s32 *)po);
                        out[3] = 0;
                        uVar2 = func_80029AF4();
                        func_8014C4AC(e, 0x1B, uVar2, po,
                                      (s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12));
                        return 1;
                    }
                }
            }
        }
        cnt += 1;
        i += 0x10C;
    } while ((u32)cnt < 0x60);
    return 0;
}
