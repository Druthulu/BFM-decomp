/* func_8015E288 — shared body (overlay slot 0x80128158, h_exact 0f1950ec). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800D5098[];
extern u8 D_800D5060[];
extern s32 func_80161208();
extern s32 func_8014A850(s32 a0);
extern void guess_SetAnimScript(s32 *a0, s32 a1);
extern void func_8015E40C(s32 a0);
extern void func_8015E588(void);
extern void func_8015E4B0(s32 a0);
extern s32 guess_SpawnSmallObjectAtOrigin(s32 a0, s32 a1, s32 a2, s32 a3);
extern void guess_NextStep(void *a0);
extern void guess_SetStep(s32 *a0, s16 a1);
void func_8015E288(s32 a0) {
    if (func_80161208() != 0) {
        return;
    }
    if (func_8014A850(a0) != 0) {
        guess_SetAnimScript((s32 *)a0, (s32)D_800D5098);
        func_8015E40C(a0);
        ((void (*)(s32))func_8015E588)(a0);
        func_8015E4B0(a0);
        guess_SpawnSmallObjectAtOrigin(5, a0, 0xB, 0);
        guess_NextStep((void *)a0);
        return;
    }
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        guess_SetAnimScript((s32 *)a0, (s32)D_800D5060);
        guess_SetStep((s32 *)a0, 3);
    }
}
