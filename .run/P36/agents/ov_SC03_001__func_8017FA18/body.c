void func_8017FA18(s32 param_1) {
    s32 speed;
    s32 step1;
    s32 step3;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if (func_8012BEE8(param_1) == 0) {
            return;
        }
        *(s32 *)(param_1 + 0x1c) = 0x40;
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        speed = rand();
        speed &= 0x3fff;
        speed += 0x7800;
        if ((rand() & 1) == 0) {
            speed = -speed;
        }
        *(s32 *)(param_1 + 0xe0) = speed;
        *(s32 *)(param_1 + 0xe4) = 0;
        break;
    case 1:
        step1 = *(s32 *)(param_1 + 0xe4) + *(s32 *)(param_1 + 0xe0);
        *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + step1;
        *(s32 *)(param_1 + 0xe4) = step1;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
        if (func_8012BEE8(param_1) == 0) {
            return;
        }
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        *(s32 *)(param_1 + 0x1c) = (rand() & 0x3f) + 0x40;
        break;
    case 2:
        *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + *(s32 *)(param_1 + 0xe4);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
        if (func_8012BEE8(param_1) == 0) {
            return;
        }
        *(s32 *)(param_1 + 0x1c) = 0x40;
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        *(s32 *)(param_1 + 0xe0) = -*(s32 *)(param_1 + 0xe0);
        break;
    case 3:
        step3 = *(s32 *)(param_1 + 0xe4) + *(s32 *)(param_1 + 0xe0);
        *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + step3;
        *(s32 *)(param_1 + 0xe4) = step3;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
        if (func_8012BEE8(param_1) == 0) {
            return;
        }
        *(u16 *)(param_1 + 0x34) = 0;
        *(s32 *)(param_1 + 0x1c) = (rand() & 0xff) + 0x40;
        break;
    }
}
