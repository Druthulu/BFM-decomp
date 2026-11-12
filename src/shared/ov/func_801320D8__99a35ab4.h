/* func_801320D8 — shared body (overlay slot 0x80128158, h_exact 99a35ab4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801320D8(int param_1)
{
    int v0;

    v0 = ((int (*)(void))guess_AllocModelObject)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))guess_FreeActorDuringSpawn)(param_1);
    } else {
        guess_InitModelObject(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8017F7A8;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}
