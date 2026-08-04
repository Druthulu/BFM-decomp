void func_8017F2E8(s32 param_1)
{
    extern void func_801808B4(void *a0);
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
    u16 state;
    s32 uVar2;
    s32 pad[4];

    if (*(s16 *)(param_1 + 0xa) >= 0x10) {
        func_801808B4((void *)param_1);
        return;
    }

    sVar1 = func_8004787C((*(s32 *)(param_1 + 0xe4) << 6) & 0x7c0);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1a) = (sVar1 >> 1) + 0x800;

    state = *(u16 *)(param_1 + 0x34);
    switch (state) {
    case 0: {
        s32 iVar3 = 0x1000 - sVar1;
        s32 a1;
        if (iVar3 >= 0) {
            a1 = -0x8000 - (iVar3 << 4);
        } else {
            a1 = -0x8000 - ((sVar1 - 0x1000) << 4);
        }
        func_8012B178(param_1, a1);
        iVar1 = func_8012CBA4(param_1);
        if ((iVar1 & 0xff) == 0x1a) {
            goto EXIT_808B4;
        }
        if ((iVar1 & 0x6000) == 0) {
            goto MERGE_4C0;
        }
        if (--*(s32 *)(param_1 + 0xe8) != 0) {
            goto TAIL_5D8;
        }
        {
            s32 iVar2;
            s32 nVar;
            s32 sVar2;

            *(u16 *)(param_1 + 0x34) = 1;
            *(s32 *)(param_1 + 0x1c) = 0x20;
            iVar2 = rand();
            nVar = iVar2 % 1024;
            sVar2 = *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
            if (rand() & 1) {
                uVar2 = sVar2 + nVar;
            } else {
                uVar2 = sVar2 - nVar;
            }
        }
        goto MERGE_4E0;
    }

    case 1: {
        s32 ptr0 = *(s32 *)(param_1 + 0x20);
        s32 arg0 = *(s16 *)(ptr0 + 0x12);
        s32 ret = func_8012B608(arg0, *(s32 *)(param_1 + 0xe0), 0x14);
        s32 ptr1 = *(s32 *)(param_1 + 0x20);
        s32 sum;

        sum = *(u16 *)(ptr1 + 0x12) + ret;
        __asm__ __volatile__("" : "=r"(sum) : "0"(sum));
        ret = 0x1000 - sVar1;
        *(s16 *)(ptr1 + 0x12) = sum;
        if (ret < 0) {
            ret = sVar1 - 0x1000;
        }
        ret = ret << 4;
        ret = -ret;
        {
            s32 arg1 = ret - 0x4000;
            __asm__ __volatile__("" : "=r"(arg1) : "0"(arg1));
            func_8012B178(param_1, arg1);
        }
        iVar1 = func_8012CBA4(param_1);
        if ((iVar1 & 0xff) == 0x1a) {
            goto EXIT_808B4;
        }
        if ((iVar1 & 0x6000) != 0) {
            goto MERGE_4E8;
        }
    }
    MERGE_4C0:
        func_8012ADE4((u8 *)param_1);
        {
            /* §17 pin: the merge-block pointer must land in $v1 so reload's
             * scratch for the constant store takes $v0 (see .L8017F4C0). */
            register s32 ptr2 __asm__("$3");
            ptr2 = *(s32 *)(param_1 + 0x20);
            *(u16 *)(param_1 + 0x34) = 2;
            uVar2 = *(s16 *)(ptr2 + 0x12) + 0x800;
        }
    MERGE_4E0:
        *(s32 *)(param_1 + 0xe0) = uVar2;
        goto TAIL_5D8;
    MERGE_4E8:
        if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(param_1 + 0x34) = 0;
            *(s32 *)(param_1 + 0xe8) = 0x40;
        }
        goto TAIL_5D8;

    case 2: {
        s32 ptrA = *(s32 *)(param_1 + 0x20);
        s32 arg1 = *(s32 *)(param_1 + 0xe0);
        s32 arg0 = *(s16 *)(ptrA + 0x12);
        s32 ret = func_8012B608(arg0, arg1, 0xa);

        if (ret == 0) {
            *(u16 *)(param_1 + 0x34) = 0;
        }
        {
            s32 ptrB = *(s32 *)(param_1 + 0x20);
            *(s16 *)(ptrB + 0x12) = *(u16 *)(ptrB + 0x12) + ret;
        }
        goto TAIL_5D8;
    }

    case 3:
        iVar1 = func_8012CBA4(param_1);
        if ((iVar1 & 0xff) != 0x1a) {
            goto NOT_1A;
        }
    EXIT_808B4:
        func_801808B4((void *)param_1);
        return;
    NOT_1A:
        if ((iVar1 & 0x2000) == 0) {
            goto L8017F598;
        }
        func_8012B23C(param_1);
        func_8012B178(param_1, 0xFFFD8000);
        *(u16 *)(param_1 + 0x34) = 0;
        goto TAIL_5D8;
    L8017F598:
        if ((*(s32 *)(param_1 + 0x1c) & 3) != 0) {
            goto L8017F5B4;
        }
        func_80143B6C(param_1, 1);
    L8017F5B4:
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) < 0x3c) {
            goto TAIL_5DC;
        }
        func_80131E00(param_1, 0xd);
    }

TAIL_5D8:
TAIL_5DC:
    if (func_8012BD3C(param_1, 0x400, 0x24000) == 1) {
        *(s16 *)(param_1 + 2) = 3;
    }
    if (0x100000 < *(s32 *)(param_1 + 0x14)) {
        *(s32 *)(param_1 + 0x14) = 0x100000;
    }
    *(s32 *)(param_1 + 0xe4) += 1;
}
