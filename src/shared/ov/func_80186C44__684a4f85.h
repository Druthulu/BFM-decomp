/* func_80186C44 — shared body (overlay slot 0x80128158, h_exact 684a4f85). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32, s32);
extern void guess_StartActorSequence(s32, void*);
extern u8 D_801DCA30[];
extern M2C_UNK D_8018AF28;
void func_80186C44(void *a0) {
    s32 v0 = ((s32 (*)(void *))guess_AllocModelObject)(a0);
    *(int *)((char *)a0 + 0x20) = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn(a0);
    } else {
        ((void (*)(s32, u8 *))guess_InitModelObject)(v0, D_801DCA30);
        ((void (*)(void *, u8 *))guess_StartActorSequence)(a0, ((u8 *)&D_8018AF28));
        *(short *)((char *)a0 + 0x2) = 1;
    }
}
