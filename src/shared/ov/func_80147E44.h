/* func_80147E44 — shared body (overlay slot 0x80128158, h_exact 35af89dc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80147E44(s32 a0, s32 a1, s32 a2, s32 a3) {
    extern void func_80147928(int a0, int a1);
    extern void func_8014799C(int a0, int a1);
    extern void func_80147A10(int a0, int a1);
    extern void func_80013F3C(s32 a0);
    extern void RotMatrixX(s32 a0, void *a1);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void func_800484EC(s32 a0, s32 a1, s32 a2);
    extern s32 D_80127090;
    extern s32 D_80127094;
    extern s32 D_80127098;
    s32 r_a0;  /* $s1 = param_1 */
    s32 r_a2;  /* $s0 = param_3 */
    s32 r_a3;  /* $s3 = param_4 */
    s32 v;   /* $s2 = *(a0+0x20) */
    s32 out[3];
    s32 m[8];
    s32 *p0 = &D_80127090;
    s32 *p1 = &D_80127094;
    s32 *p2 = &D_80127098;
    r_a0 = a0;
    r_a2 = a2;
    r_a3 = a3;
    v = *(s32 *)(r_a0 + 0x20);
    func_80147928(r_a0, a1);
    func_8014799C(r_a0, r_a2);
    func_80147A10(r_a0, r_a3);
    func_80013F3C((s32)m);
    RotMatrixY(*(s16 *)(v + 0x12), (void *)m);
    RotMatrixX(*(s16 *)(v + 0x10), (void *)m);
    RotMatrixZ(*(s16 *)(v + 0x14), (void *)m);
    func_800484EC((s32)m, r_a0 + 0x24, (s32)out);
    D_80127090 = out[0];
    D_80127094 = out[1];
    D_80127098 = out[2];
    *(s32 *)(r_a0 + 0x10) = *p0;
    *(s32 *)(r_a0 + 0x14) = *p1;
    *(s32 *)(r_a0 + 0x18) = *p2;
    D_80127090 = 0;
    D_80127094 = 0;
    D_80127098 = 0;
}
