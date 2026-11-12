/* func_8018B388 — shared body (overlay slot 0x80128158, h_exact 0db09bbf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void guess_SetObjectPosAndYaw(s32 a0, s32 a1);
extern s32 D_801B6418[];
extern s32 D_801E052C[];
void func_8018B388(s32 a0) {
    s32 v0;
    v0 = ((s32 (*)(void))guess_AllocModelObject)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn((void *)a0);
        return;
    }
    guess_InitModelObject(v0, (s32)D_801B6418);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);
    guess_SetObjectPosAndYaw(a0, (s32)D_801E052C);
    *(s16 *)(a0 + 0x2) = 1;
}
