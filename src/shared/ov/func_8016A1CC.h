/* func_8016A1CC — shared body (overlay slot 0x80128158, h_exact d4c8dd1e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EBF;
extern void guess_PlaySoundUnlessSkipped(s32 arg0);
extern void func_80147364(u16 param_1, u16 param_2);
extern s32 guess_FreeSmallObject(u8 *a0);
void func_8016A1CC(int param_1)
{
    int iVar1;
    if (D_80078EBF != 0) {
        iVar1 = *(int *)(param_1 + 0x30) = D_80078EBF - 0x18;
        if (iVar1 >= 0) {
            iVar1 = *(int *)(param_1 + 0x1c) + 1;
            *(int *)(param_1 + 0x1c) = iVar1;
            if (iVar1 == 4) {
                guess_PlaySoundUnlessSkipped(0x44c);
            }
            if (D_80078EBF >= 0x80) {
                if (*(short *)(param_1 + 0x2a) == 0) {
                    *(short *)(param_1 + 0x2a) = 1;
                    *(int *)(param_1 + 0x1c) = 0x100;
                }
                if ((*(unsigned int *)(param_1 + 0x1c) & 0x1f) == 0) {
                    guess_PlaySoundUnlessSkipped(0x44d);
                }
            }
        }
    } else {
        ((void (*)(int, int))func_80147364)(4, 0x44c);
        ((void (*)(int))guess_FreeSmallObject)(param_1);
    }
}
