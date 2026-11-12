/* func_80160F00 — shared body (overlay slot 0x80128158, h_exact 5957f663). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void guess_SetAnim(s32 a0, s32 a1);
extern void guess_SetTexAnim(s32 a0, s32 a1);
extern void func_80129248(s16 a0);
extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
extern void guess_NextStep(void *a0);
extern u16 D_801270C0;
extern u8 D_800B9A17;
void func_80160F00(void* arg0) {
    ((void (*)(void*))func_80149020)(arg0);
    ((void (*)(void*, s32))guess_SetAnim)(arg0, 4);
    ((void (*)(void*, s32))guess_SetTexAnim)(arg0, 0x11);
    D_801270C0 = 2;
    ((void (*)(s32))func_80129248)(0);
    D_800B9A17 = 0;
    ((void (*)(void*, s32))guess_SetWaitTimer_2)(arg0, 0x10);
    guess_NextStep(arg0);
}
