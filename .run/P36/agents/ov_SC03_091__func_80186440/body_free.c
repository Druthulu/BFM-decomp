void func_80186440(s32 param_1) {

    s32 unused[2]; /* dead 8-byte local — frame padding (cookbook idiom 6) */
    s32 obj;
    s16 raw;
    s32 r;
    s32 sgn;
    s32 v;
    s32 q;
    s32 w;
    /* The `register ... __asm__("$4")` pin on the tail's +2-field counter is
     * load-bearing (matching-cookbook idiom 9 / L-lever family): unpinned, gcc
     * puts the 0x50000000 OR-mask constant in $a0 and the field value in $v1
     * (register-swapped vs. the target) and schedules the field's `lhu` right
     * before the `or` instead of hoisting it ahead of the 0xFC/FD/FE `sb`
     * stores. Pinning $4/$a0 to this value AND folding the `+1` into the same
     * statement as the load (`cnt = *(u16*)(param_1+2) + 1;`, store separate)
     * reproduces both the register choice and the exact schedule position. */
    s32 cnt;

    obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    *(s32 *)(param_1 + 0x20) = obj;
    func_8001C214(obj, 0);

    raw = rand();
    r = raw;
    *(u16 *)(obj + 0x2C) = *(u16 *)(obj + 0x2C) | 0x10;
    v = r % 384 + 0x400;
    *(s16 *)(obj + 0x1C) = v;
    *(s16 *)(obj + 0x1A) = v;
    *(s16 *)(obj + 0x18) = v;
    sgn = -1;
    if (raw & 1) {
        sgn = 1;
    }
    *(s16 *)(obj + 0x10) = sgn * (r % 128) - 0x300;
    *(s16 *)(obj + 0x12) = r % 4096;
    *(u16 *)(obj + 0x14) = 0;

    *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x19;
    func_8012B2CC(param_1);
    func_8012B23C((void *)param_1);
    func_8012B178(param_1, -0xC0000 - ((r % 8) << 16));

    *(s32 *)(param_1 + 0x1C) = 0x5A;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xDC) = w;
    *(s16 *)(param_1 + 0xDE) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xE0) = w;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xE4) = w;
    *(s16 *)(param_1 + 0xE6) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xE8) = w;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xEC) = w;
    *(s16 *)(param_1 + 0xEE) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xF0) = w;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xF4) = w;
    *(s16 *)(param_1 + 0xF6) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xF8) = w;

    cnt = *(u16 *)(param_1 + 2) + 1;
    *(u8 *)(param_1 + 0xFC) = 0x80;
    *(u8 *)(param_1 + 0xFD) = 0x80;
    *(u8 *)(param_1 + 0xFE) = 0x80;
    *(u32 *)(param_1 + 0x100) = *(u32 *)(param_1 + 0x100) | 0x50000000;
    *(u16 *)(param_1 + 2) = cnt;
}
