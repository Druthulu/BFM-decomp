/* func_8018B7FC — shared body (overlay slot 0x80128158, h_exact 0297d880). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012E57C(s32 a0, s32 a1);
extern u8 D_80078EBA;
void func_8018B7FC(void *a0) {
    s32 v0;
    v0 = func_8012E57C(0x61, 0x8);
    *(s32 *)((char *)a0 + 0xCC) = v0;
    if (D_80078EBA == 3) {
        v0 = 0;
    } else {
        v0 = func_80184BAC(0x7, 0x13);
        v0 = (0U < (u32)v0) ? 1 : 0;
    }
    if (v0 != 0) {
        v0 = 1;
    } else {
        v0 = 2;
    }
    *(s16 *)((char *)a0 + 0x2) = v0;
}
