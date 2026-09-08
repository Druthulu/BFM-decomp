/* func_801723C4 — shared body (overlay slot 0x80128158, h_exact 6fc8c3eb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801599A4(void *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8014A1B0(s32 a0, s32 a1);
void func_801723C4(s32 param_1, s32 param_2)
{
    ((void (*)(void))func_801599A4)();
    ((void (*)(int, int))func_80147078)(param_1, 0xd);
    *(int *)(param_1 + 0x178) = param_2;
    func_8014A1B0(param_1, param_2);
}
