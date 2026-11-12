/* func_8015FD74 — shared body (overlay slot 0x80128158, h_exact ad91f4fb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015FD74(int param_1)
{
    ((int (*)(int))guess_PlaySoundUnlessSkipped)(0x18);
    *(int *)(param_1 + 0x198) = guess_OpenTextWindow(D_801814BC[*(unsigned char *)(param_1 + 0x1a0)]);
    ((int (*)(int))guess_NextStep)(param_1);
}
