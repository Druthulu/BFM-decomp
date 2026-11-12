/* func_8015B6F4 — shared body (overlay slot 0x80128158, h_exact f543534a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_IsSquarePressed(s32 *a0);
extern void func_80156648(s32 *a0);
extern void guess_SetAnim(s32 a0, s32 a1);
extern void guess_SetTexAnim(s32 a0, s32 a1);
extern s32 guess_SpawnSmallObjectAtOrigin(s32 a0, s32 a1, s32 a2, s32 a3);
extern void guess_PlaySoundUnlessSkipped(s32 arg0);
extern void guess_PlaySound(u16 arg0);
extern s32 D_800D4A9C;
int func_8015B6F4(int param_1)
{
    unsigned int f44;
    unsigned int bc;
    if (((int (*)(void))guess_IsSquarePressed)() == 0) return 0;
    ((void (*)(int))func_80156648)(param_1);
    *(unsigned char *)(param_1 + 0x1aa) = 6;
    f44 = *(unsigned int *)(param_1 + 0x44);
    bc = *(unsigned char *)(param_1 + 0xbc);
    *(unsigned int *)(param_1 + 0x44) = f44 | 2;
    *(int *)(param_1 + 0x23c) = (*(int *)(param_1 + 0xb4));
    *(unsigned char *)(param_1 + 0x244) = bc;
    if (*(int *)(param_1 + 0xb4) == (int)&D_800D4A9C) {
        guess_SetAnim(param_1, 0xb);
    } else {
        guess_SetAnim(param_1, 0xc);
    }
    guess_SetTexAnim(param_1, 0x22);
    *(unsigned char *)(param_1 + 0xda) = 0;
    ((void (*)(int, int, int, int))guess_SpawnSmallObjectAtOrigin)(4, param_1, 5, 0);
    guess_PlaySoundUnlessSkipped(0x400);
    ((void (*)(int))guess_PlaySound)(0x5f3);
    return 1;
}
