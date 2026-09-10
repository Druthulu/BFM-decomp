void func_8017FA18(s32 param_1) {
    s32 uVar1;
    s32 iVar2;
    register s32 iVar3 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus7)
    register s32 iVar4 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus7)
    u32 uVar3;

    uVar1 = *(u16 *)(param_1 + 0x34);
    if (uVar1 == 1) {
        goto case1;
    }
    if (uVar1 < 2) {
        if (uVar1 == 0) {
            goto case0;
        }
        return;
    }
    if (uVar1 == 2) {
        goto case2;
    }
    if (uVar1 != 3) {
        return;
    }
    goto case3;

case0:
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(s32 *)(param_1 + 0x1c) = 0x40;
    *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
    uVar3 = rand();
    iVar4 = uVar3 & 0x3fff;
    iVar4 = iVar4 + 0x7800;
    uVar3 = rand();
    if ((uVar3 & 1) == 0) {
        iVar4 = -iVar4;
    }
    *(s32 *)(param_1 + 0xe0) = iVar4;
    *(s32 *)(param_1 + 0xe4) = 0;
    return;

case1:
    iVar3 = *(s32 *)(param_1 + 0xe4);
    iVar3 = iVar3 + *(s32 *)(param_1 + 0xe0);
    *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + iVar3;
    *(s32 *)(param_1 + 0xe4) = iVar3;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
    uVar3 = rand();
    uVar3 = uVar3 & 0x3f;
    goto tail;

case2:
    *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + *(s32 *)(param_1 + 0xe4);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(s32 *)(param_1 + 0x1c) = 0x40;
    *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
    *(s32 *)(param_1 + 0xe0) = -*(s32 *)(param_1 + 0xe0);
    return;

case3:
    iVar3 = *(s32 *)(param_1 + 0xe4);
    iVar3 = iVar3 + *(s32 *)(param_1 + 0xe0);
    *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + iVar3;
    *(s32 *)(param_1 + 0xe4) = iVar3;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(u16 *)(param_1 + 0x34) = 0;
    uVar3 = rand();
    uVar3 = uVar3 & 0xff;

tail:
    *(u32 *)(param_1 + 0x1c) = uVar3 + 0x40;
}
