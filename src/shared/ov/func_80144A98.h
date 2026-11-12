/* func_80144A98 — shared body (overlay slot 0x80128158, h_exact 6109627b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
void func_80144A98(u8 *a0) {
    s32 v0;
    v0 = ((s32 (*)(void))guess_AllocModelObject)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn(a0);
    } else {
        guess_InitModelObject(v0, 0);
        *(s16 *)(a0 + 0x2) = 1;
    }
}
