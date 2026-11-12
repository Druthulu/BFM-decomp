/* func_80180954 — shared body (overlay slot 0x80128158, h_exact 9759cc1e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetObjectPosAndYaw(s32 a0, s32 a1);
extern void guess_ShowObjectModel(s32 a0);
extern void guess_StartActorSequence(s32*, s32);
extern void func_80184C90(s32);
extern void func_80184ED4(s32, s32, s32, s32);
void func_80180954(void *arg0) {
    extern short D_801919E8;
    extern s32 D_801B9AA8;
    extern u8 D_801B6620[];
    void *v1;
    *(short *)((char *)arg0 + 0x2) = 0x4;
    guess_SetObjectPosAndYaw((s32)arg0, (s32)&D_801919E8);
    v1 = *(void **)((char *)arg0 + 0x20);
    *(short *)((char *)v1 + 0x12) = *(short *)((char *)v1 + 0x12) + 0x800;
    guess_ShowObjectModel((s32)arg0);
    ((void (*)(s32 *, s32))guess_StartActorSequence)((s32 *)arg0, (s32)&(*(short *)&D_801B9AA8));
    func_80184C90((s32)arg0);
    *(short *)((char *)arg0 + 0x34) = 0;
    func_80184ED4((s32)arg0, (s32)&(*(short *)D_801B6620), 0x1, 0x40);
}
