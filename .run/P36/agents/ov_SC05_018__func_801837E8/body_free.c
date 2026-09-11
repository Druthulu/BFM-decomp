void func_801837E8(s32 a0) {
    s32 state;
    s32 fv;

    state = *(u16 *)(a0 + 0x34);
    if (state == 1) {
        goto case1;
    }
    if (state < 2) {
        if (state == 0) {
            goto case0;
        }
        goto tail;
    }
    if (state == 2) {
        goto case2;
    }
    if (state == 3) {
        goto case3;
    }
    goto tail;

case0: {
    if (func_8012BEE8(a0) == 0) {
        goto tail;
    }
    *(u16 *)(a0 + 0xFC) = 0;
    *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    fv = rand();
    fv = (fv & 0x1F) + 0x1E;
    goto store1c;
}

case1: {
    s32 v0;
    s32 p;
    v0 = *(u16 *)(a0 + 0xFC);
    p = *(s32 *)(a0 + 0x20);
    v0 = v0 + 6;
    *(u16 *)(a0 + 0xFC) = v0;
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + v0;
    if (func_8012BEE8(a0) == 0) {
        goto tail;
    }
    *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    goto randtail;
}

case2: {
    s32 p;
    s32 v0;
    v0 = *(u16 *)(a0 + 0xFC);
    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + v0;
    if (func_8012BEE8(a0) == 0) {
        goto tail;
    }
    *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    goto tail;
}

case3: {
    s32 v0;
    s32 p;
    v0 = *(u16 *)(a0 + 0xFC);
    p = *(s32 *)(a0 + 0x20);
    v0 = v0 - 3;
    *(u16 *)(a0 + 0xFC) = v0;
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + v0;
    if (*(s16 *)(a0 + 0xFC) >= 9) {
        goto tail;
    }
    *(u16 *)(a0 + 0x34) = 0;
}

randtail:
    fv = rand();
    fv = (fv & 0x3F) + 0x3C;

store1c:
    *(s32 *)(a0 + 0x1C) = fv;

tail:
    if (!((u32)func_80029504() < 0x492)) {
        func_8012C218((void *)a0);
    }
}
