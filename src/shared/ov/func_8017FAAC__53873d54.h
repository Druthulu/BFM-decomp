/* func_8017FAAC — shared body (overlay slot 0x80128158, h_exact 53873d54). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80184BD0(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_80184CB8(s32 *a0, s32 a1);
extern s16 D_80191570;
void func_8017FAAC(void *a0) {
    s32 *v1;
    s32 result;
    v1 = *(s32 **)((s32)a0 + 0xCC);
    *(s32 *)((s32)v1 + 0xB0) = 0x2;
    result = func_80184BD0(0xE, 0xF, 0x17, 0);
    if (result == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_80184CB8((s32 *)a0, (s32)&D_80191570);
    }
}
