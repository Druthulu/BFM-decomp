/* func_8015795C — shared body (overlay slot 0x80128158, h_exact cc9c4578). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015795C(int param_1)
{
    int frame_pad[4]; /* dead 16-byte local: forces target's 0x30 frame (vars=16); never referenced */
    int iVar1;
    unsigned int uVar2;

    *(unsigned int *)(param_1 + 0x44) = *(unsigned int *)(param_1 + 0x44) | 2;
    ((int (*)(int, int))func_80147A10)(param_1, 0x400);
    if (*(int *)(param_1 + 0x2c) >= 0) {
        *(int *)(param_1 + 0x2c) = 0;
    }
    func_80147A84(param_1);
    ((void (*)(int))guess_ApplyVelocity)(param_1);
    guess_AddVertSpeed(param_1, 0x1a000);
    guess_ApplyVertSpeed(param_1);
    iVar1 = ((int (*)(int))func_8014ED28)(param_1);
    if (iVar1 != 0) {
        guess_ClearMoveVector(param_1);
    }
    uVar2 = ((int (*)(int))func_80161450)(param_1);
    if ((uVar2 & 5) != 0) {
        func_80157A8C(param_1);
        ((void (*)(int, int))guess_SetWaitTimer_2)(param_1, 8);
        ((void (*)(int))guess_NextStep)(param_1);
    }
    if (uVar2 == 0) {
        ((void (*)(int, int))func_80155FF8)(param_1, *(unsigned char *)(param_1 + 0x1aa));
        if (*(unsigned char *)(param_1 + 0x1c0) != 0) {
            guess_SetTexAnim(param_1, 0x17);
            ((void (*)(int, void *))guess_SetAnimScript)(param_1, &D_800D5178);
            ((void (*)(int, void *))guess_SetMoveVector)(param_1, &D_80181574);
            ((void (*)(int, int))guess_SetVertSpeed)(param_1, 0xfff40000);
            *(short *)(param_1 + 2) = 4;
        }
        ((void (*)(int))func_801725A4)(param_1);
    }
    return;
}
