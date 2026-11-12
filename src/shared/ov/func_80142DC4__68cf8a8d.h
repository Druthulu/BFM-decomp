/* func_80142DC4 — shared body (overlay slot 0x80128158, h_exact 68cf8a8d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80142DC4(int param_1)
{
    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))guess_AllocModelObject)();
    if (v0 == 0) {
        ((void (*)(int))guess_FreeActorDuringSpawn)(param_1);
    } else {
        ((void (*)(s32, s32))guess_InitModelObjectKind3)(v0, (s32)&D_8017FF00);
        *(short *)(v0 + 0x1a) = 0x1800;
        *(short *)(v0 + 0x18) = 0x1800;
        *(short *)(param_1 + 0xfc) = 0;
        ((void (*)(int))func_80142B2C)(param_1);
    }
}
