/* func_80168BDC — shared body (overlay slot 0x80128158, h_exact 0964d4c6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800D2318(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4)
{
    short mtx[16];
    short vec[4];
    int r;
    register int i __asm__("$17");     /* loop counter, survives the call -> $s1 */
    register int tmp __asm__("$2");    /* increment temp -> $v0 (the split-IV) */
    func_800D2318();
    vec[0] = *(short *)(param_1 + 0x12);
    vec[1] = *(short *)(param_1 + 0x16);
    vec[2] = 0;
    RotMatrixYXZ(vec, mtx);
    vec[0] = 0;
    if (*(int *)(param_1 + 0x2c) < 0) {
        vec[2] = -8;
        vec[1] = -4;
    } else {
        vec[2] = 2;
        vec[1] = -2;
    }
    ApplyMatrixSV(mtx, vec, vec);
    *(short *)(param_1 + 6) = *(short *)(param_1 + 6) + vec[0];
    *(short *)(param_1 + 0xa) = *(short *)(param_1 + 0xa) + vec[1];
    *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + vec[2];
    i = 0;
    if ((short)param_4 > 0) {
        do {
            r = func_80146A6C((unsigned short)param_2, (void *)param_1,
                              (short)*(short *)(param_1 + 6),
                              (short)*(short *)(param_1 + 0xa),
                              (short)*(short *)(param_1 + 0xe),
                              (short)param_3, 0);
            if (r != 0) {
                *(short *)(r + 0x12) = *(short *)(param_1 + 0x12);
                *(short *)(r + 0x16) = *(short *)(param_1 + 0x16);
                *(short *)(r + 0x1a) = *(short *)(param_1 + 0x1a);
            }
            tmp = i + 1;
            i = tmp;
            __asm__ __volatile__("" : "=r"(i) : "0"(i));
        } while ((short)tmp < (short)param_4);
    }
}
