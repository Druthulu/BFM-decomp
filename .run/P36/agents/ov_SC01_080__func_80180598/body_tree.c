void func_80180598(s32 arg0)
{
    register s32 param_1 __asm__("$16") = arg0;  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus7)
    register s32 iVar1 __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus7)
    s32 ret;
    s32 v0;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = ret;
    iVar1 = ret;
    if (ret == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        extern s32 D_801ACC1C;
        func_8001C810(iVar1, (s32)&D_801ACC1C);
        func_8001D0E8(iVar1, 0x800, 0x800);
        func_8012A828(param_1, D_80189D04);
        *(s32 *)(param_1 + 8) = 0;
        v0 = *(s16 *)(param_1 + 0xA);
        *(s32 *)(param_1 + 0xC) = 0;
        *(s32 *)(param_1 + 4) = 0;
        D_80127190 = v0;
        *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x40000040;
        *(u16 *)(param_1 + 2) += 1;
    }
}
