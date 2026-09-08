/* func_8016B448 — shared body (overlay slot 0x80128158, h_exact 163199bd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_8014C050(s32 a0, s32 a1);
extern void func_8016B984(void *a0);
extern s32 D_80126B58;
s32 func_8016B448(s32 arg0, s32 arg1)
{
    s32 temp_v0;
    temp_v0 = func_8014C050(&D_80126B58, 0x1E);
    if (temp_v0 != 0) {
        func_8016B984(temp_v0);
    }
    func_80146A6C(0x1E, arg0, M2C_FIELD(arg0, s16 *, 0x7C), M2C_FIELD(arg0, s16 *, 0x7E), (s32) M2C_FIELD(arg0, s16 *, 0x80), arg1, 0);
}
