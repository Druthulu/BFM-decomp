/* func_80147364 — shared body (overlay slot 0x80128158, h_exact 813729d8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 currentLocationId;
extern s32 guess_g_PlayerActor;
extern void guess_CopyVec3HighHalves(s32, s32*);
extern s32 aF8012E5CC(s32, s32, s32) __asm__("func_8012E5CC");
extern void guess_RequestSound(s32 a0, s32 a1);
void func_80147364(u16 param_1, u16 param_2)
{
    s32 sp10[2];
    s32 *p = &guess_g_PlayerActor;
    if (currentLocationId == 0x308d) {
        ((void (*)(void *, void *))guess_CopyVec3HighHalves)(p + 1, sp10);
        ((void (*)(void *, s32, s32))aF8012E5CC)(sp10, param_1, param_2);
    } else {
        guess_RequestSound(param_1, param_2);
    }
}
