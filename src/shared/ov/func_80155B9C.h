/* func_80155B9C — shared body (overlay slot 0x80128158, h_exact fa7bd93a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_AddVertSpeed(s32 a0, s32 a1);
extern void guess_ApplyVertSpeed(s32 a0);
extern void guess_SetAnimScript(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern s32 D_800D4DB4;
void func_80155B9C(s32 a0) {
    *(s32 *)(a0 + 0x44) |= 2;
    guess_AddVertSpeed(a0, 0x30000);
    guess_ApplyVertSpeed(a0);
    if (*(s32 *)(a0 + 0x34) >= 0) {
        guess_SetAnimScript((s32 *)a0, (s32)&D_800D4DB4);
        func_80146CA0((void *)a0);
        func_80147324(0x447);
    }
}
