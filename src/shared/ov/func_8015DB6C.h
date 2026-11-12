/* func_8015DB6C — shared body (overlay slot 0x80128158, h_exact c7b8ee4e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetAnim(s32 a0, s32 a1);
extern void guess_SetTexAnim(s32 a0, s32 a1);
extern void func_8015DCB8(s32 a0);
extern void func_80147300(u16 arg0);
extern void func_801553A8(s32 *a0);
extern void func_8014BD60(s32 a0, s32 a1);
extern void guess_NextStep(void *a0);
void func_8015DB6C(s32 a0) {
    guess_SetAnim(a0, 0x1C);
    guess_SetTexAnim(a0, 0x19);
    *(s32 *)(a0 + 0x234) = 0;
    func_8015DCB8(a0);
    func_80147300(0x5F5);
    func_801553A8((s32 *)a0);
    func_8014BD60(a0, 4);
    guess_NextStep((void *)a0);
}
