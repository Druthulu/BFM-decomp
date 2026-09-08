/* func_80165E90 — shared body (overlay slot 0x80128158, h_exact 3b09d941). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801484B0(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern void func_80148534(s32 a0, s32 a1);
extern s32 func_80167AE0();
extern s32 D_80126B9C;
extern s32 D_80126B58;
extern s32 *D_80126B78;
void func_80165E90(void) {
    s32 s1 = (s32)&D_80126B58;
    s32 buf1[2];
    s32 buf2[2];
    s32 v1;
    if ((D_80126B9C & 0x10000400) == 0x10000000) {
        v1 = (s32)D_80126B78;
        if (*(s32 *)(v1 + 0x4) >= 0) {
            if (*(s32 *)(v1 + 0x20) != 0) {
                func_801484B0((s32)buf1, (s32)buf2);
                func_80165FA4(s1, (s32)buf1, (s32)buf2);
                func_80167DBC(s1, (s32)buf1, (s32)buf2);
            }
        }
    }
    if ((*(s32 *)(s1 + 0x44) & 0x20020400) == 0x20000000) {
        v1 = *(s32 *)(s1 + 0x20);
        if (*(s32 *)(v1 + 0x4) >= 0) {
            if (*(s32 *)(v1 + 0x20) != 0) {
                func_80148534((s32)buf1, (s32)buf2);
                func_80165FA4(s1, (s32)buf1, (s32)buf2);
                func_80167AE0(s1, (s32)buf1, (s32)buf2);
            }
        }
    }
}
