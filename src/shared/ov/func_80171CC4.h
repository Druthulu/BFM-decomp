/* func_80171CC4 — shared body (overlay slot 0x80128158, h_exact 5f5df581). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80171D78(s32 a0, s32 a1);
extern int func_8017250C(short *a0, short *a1);
extern void func_80146D90(s32 a0);
s32 func_80171CC4(void * a0, void * a1)
{
    s32 ret;
    ret = func_80171D78(a0, a1);
    if (func_8017250C(a0, a1) != 0) {
        func_80146D90((s32)a0);
    }
    return ret;
}
