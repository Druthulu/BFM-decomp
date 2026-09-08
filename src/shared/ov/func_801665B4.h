/* func_801665B4 — shared body (overlay slot 0x80128158, h_exact 883ec57a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
extern void func_800D22E4(s32 a0);
void func_801665B4(s32 *a0)
{
    if (func_80128ED8((void *)a0[8], (void *)(a0 + 9))) {
        func_80146C3C((s32)a0);
    } else {
        func_800D22E4((s32)a0);
        a0[5] -= a0[5] >> 3;
    }
}
