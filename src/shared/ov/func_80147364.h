/* func_80147364 — shared body (overlay slot 0x80128158, h_exact 813729d8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 currentLocationId;
extern s32 D_80126B58;
extern void func_80015978(s32, s32*);
extern s32 aF8012E5CC(s32, s32, s32) __asm__("func_8012E5CC");
extern void func_8002D4C8(s32 a0, s32 a1);
void aF80147364(u16 param_1, u16 param_2) __asm__("func_80147364");
void aF80147364(u16 param_1, u16 param_2) {
    s32 sp10[2];
    s32 *p = &D_80126B58;
    if (currentLocationId == 0x308d) {
        ((void (*)(void *, void *))func_80015978)(p + 1, sp10);
        ((void (*)(void *, s32, s32))aF8012E5CC)(sp10, param_1, param_2);
    } else {
        func_8002D4C8(param_1, param_2);
    }
}
