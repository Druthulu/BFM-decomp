/* func_80149F2C — shared body (overlay slot 0x80128158, h_exact 6d45bcfe). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80144A04(s32 *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8016EDEC(s32 a0, s32 a1);
s32 func_80149F2C(s32 a0, s32 a1)
{
    void *s1 = a0;
    s32 *s0;
    if (*(u16 *)a1 == 0x83 || *(u16 *)a1 == 0x61) {
        s0 = (s32 *)((s32 (*)())func_80144A04)((s32 *)a1);
        if (s0 != 0) {
            func_801599A4(s1);
            func_80159B3C(s1);
            func_8016EDEC((s32)s0, 0x1000000);
            return 1;
        }
    }
    return 0;
}
