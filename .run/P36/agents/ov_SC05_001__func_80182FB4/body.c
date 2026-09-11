void func_80182FB4(s32 param_1)
{
    extern void func_80184580(s32);
    extern void func_8012B178(s32 a0, s32 a1);
    extern s32 func_8012CBA4(s32 a0);
    extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
    extern s32 func_8012BEE8(s32 a0);
    extern void func_8012ADE4(u8 *a0);
    extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
    extern void func_8012B23C(s32 a0);
    extern s32 func_80143B6C(s32 a0, s32 a1);
    extern void func_80131E00(s32 a0, s32 a1);

    s32 sVar1;
    s32 iVar1;
    s32 pad[4];

    if (*(s16 *)(param_1 + 0xa) >= 0x10) {
        func_80184580(param_1);
        return;
    }

    sVar1 = func_8004787C((*(s32 *)(param_1 + 0xe4) << 6) & 0x7c0);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1a) = (sVar1 >> 1) + 0x800;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0: {
        s32 d = 0x1000 - sVar1;
        s32 arg1;

        if (d >= 0) {
            arg1 = -0x8000 - (d << 4);
        } else {
            arg1 = -0x8000 - ((sVar1 - 0x1000) << 4);
        }
        func_8012B178(param_1, arg1);
        iVar1 = func_8012CBA4(param_1);
        if ((iVar1 & 0xff) == 0x1a) {
            func_80184580(param_1);
            return;
        }
        if ((iVar1 & 0x6000) == 0) {
            func_8012ADE4((u8 *)param_1);
            *(u16 *)(param_1 + 0x34) = 2;
            *(s32 *)(param_1 + 0xe0) = *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + 0x800;
        } else if (--*(s32 *)(param_1 + 0xe8) == 0) {
            s32 nVar;
            s32 sVar2;
            s32 uVar2;

            *(u16 *)(param_1 + 0x34) = 1;
            *(s32 *)(param_1 + 0x1c) = 0x20;
            nVar = rand() % 1024;
            sVar2 = *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
            if (rand() & 1) {
                uVar2 = sVar2 + nVar;
            } else {
                uVar2 = sVar2 - nVar;
            }
            *(s32 *)(param_1 + 0xe0) = uVar2;
        }
        break;
    }

    case 1: {
        s32 ret = func_8012B608(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), *(s32 *)(param_1 + 0xe0), 0x14);
        s32 ptr = *(s32 *)(param_1 + 0x20);
        s32 d = 0x1000 - sVar1;
        s32 arg1;

        *(s16 *)(ptr + 0x12) = *(u16 *)(ptr + 0x12) + ret;
        if (d >= 0) {
            arg1 = -(d << 4) - 0x4000;
        } else {
            arg1 = -((sVar1 - 0x1000) << 4) - 0x4000;
        }
        func_8012B178(param_1, arg1);
        iVar1 = func_8012CBA4(param_1);
        if ((iVar1 & 0xff) == 0x1a) {
            func_80184580(param_1);
            return;
        }
        if ((iVar1 & 0x6000) == 0) {
            func_8012ADE4((u8 *)param_1);
            *(u16 *)(param_1 + 0x34) = 2;
            *(s32 *)(param_1 + 0xe0) = *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + 0x800;
        } else if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(param_1 + 0x34) = 0;
            *(s32 *)(param_1 + 0xe8) = 0x40;
        }
        break;
    }

    case 2: {
        s32 ret = func_8012B608(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), *(s32 *)(param_1 + 0xe0), 0xa);
        s32 ptr;

        if (ret == 0) {
            *(u16 *)(param_1 + 0x34) = 0;
        }
        ptr = *(s32 *)(param_1 + 0x20);
        *(s16 *)(ptr + 0x12) = *(u16 *)(ptr + 0x12) + ret;
        break;
    }

    case 3:
        iVar1 = func_8012CBA4(param_1);
        if ((iVar1 & 0xff) == 0x1a) {
            func_80184580(param_1);
            return;
        }
        if ((iVar1 & 0x2000) != 0) {
            func_8012B23C(param_1);
            func_8012B178(param_1, 0xFFFD8000);
            *(u16 *)(param_1 + 0x34) = 0;
            break;
        }
        if ((*(s32 *)(param_1 + 0x1c) & 3) == 0) {
            func_80143B6C(param_1, 1);
        }
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) >= 0x3c) {
            func_80131E00(param_1, 0xd);
        }
        break;
    }

    if (func_8012BD3C(param_1, 0x400, 0x24000) == 1) {
        *(s16 *)(param_1 + 2) = 3;
    }
    if (0x100000 < *(s32 *)(param_1 + 0x14)) {
        *(s32 *)(param_1 + 0x14) = 0x100000;
    }
    *(s32 *)(param_1 + 0xe4) += 1;
}
