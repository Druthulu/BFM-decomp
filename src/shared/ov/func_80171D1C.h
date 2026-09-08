/* func_80171D1C — shared body (overlay slot 0x80128158, h_exact 8f6725ed). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80171FFC(short *a0, short *a1, s32 a2);
extern int func_8017250C(short *a0, short *a1);
extern void func_80146D90(s32 a0);
s32 func_80171D1C(void * a0, void * a1, s32 a2)
{
    s32 ret;
    ret = func_80171FFC(a0, a1, a2 & 0xFF);
    if (func_8017250C(a0, a1) != 0) {
        func_80146D90((s32)a0);
    }
    return ret;
}
