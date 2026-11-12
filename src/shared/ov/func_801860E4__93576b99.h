/* func_801860E4 — shared body (overlay slot 0x80128158, h_exact 93576b99). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void guess_StartActorSequence(s32 a0, void *a1);
extern s32 D_801DF700;
extern s32 D_8018EFDC;
void func_801860E4(void *a0) {
    s32 s1;
    s32 v0;
    v0 = ((s32 (*)(void))guess_AllocModelObject)();
    s1 = v0;
    *(s32 *)((s8 *)a0 + 0x20) = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn((void *)a0);
    } else {
        guess_InitModelObject(s1, (s32)&D_801DF700);
        func_8001D0E8(s1, 0x800, 0x800);
        guess_StartActorSequence(a0, &D_8018EFDC);
        *(s32 *)((s8 *)a0 + 0x14) = 0xFFFC0000;
        *(s32 *)((s8 *)a0 + 0x48) = 0x20000;
        *(s32 *)((s8 *)a0 + 0x44) = 0;
        *(s32 *)((s8 *)a0 + 0x4C) = 0;
        *(s16 *)((s8 *)a0 + 0xDC) = 0x40;
        *(u16 *)((s8 *)a0 + 0x2) = *(u16 *)((s8 *)a0 + 0x2) + 1;
    }
}
