/* func_8015EE7C — shared body (overlay slot 0x80128158, h_exact b34f471c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015EE7C(s32 param_1)
{
    ((int (*)(void))guess_ClearStoodOnActor)();
    ((int (*)(int))guess_ClearTiltVectors)(param_1);
    ((int (*)(int, void *))guess_SetAnimScript)(param_1, &D_800D4C48);
    ((int (*)(int, void *))guess_SetMoveVector)(param_1, &D_801818F8);
    ((int (*)(int, int))guess_SetVertSpeed)(param_1, 0xFFF40000);
    ((int (*)(int))guess_NextStep)(param_1);
}
