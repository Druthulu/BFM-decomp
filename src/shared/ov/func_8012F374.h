/* func_8012F374 — shared body (overlay slot 0x80128158, h_exact 40cefd72). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s16 D_80126CB4;
extern s16 D_80126CB6;
extern s16 D_80126CB8;
void func_8012F374(s32 a0, s32 a1) {
    s32 s0 = a1;
    s32 in[3];
    s32 out[3];
    s32 mtx;
    mtx = *(s32 *)(a0 + 0x20);
    in[0] = D_80126CB4 - *(s32 *)(mtx + 0x48);
    in[1] = D_80126CB6 - *(s32 *)(mtx + 0x4C);
    in[2] = D_80126CB8 - *(s32 *)(mtx + 0x50);
    ApplyTransposeMatrixLV((void *)(mtx + 0x34), in, out);
    *(s16 *)(s0 + 0x0) = out[0];
    *(s16 *)(s0 + 0x2) = out[1];
    *(s16 *)(s0 + 0x4) = out[2];
}
