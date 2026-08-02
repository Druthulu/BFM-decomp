extern s32 func_80178B18(s32 param_1, s32 param_2);

void func_8017CB68(s32 a0) {
    s32 ptr1 = *(s32 *)(a0 + 0xD0);
    s32 ptr2 = *(s32 *)(a0 + 0xDC);
    s16 val = *(u16 *)(ptr1 + 0x1A) - 0xC0;

    *(s16 *)(ptr1 + 0x1A) = val;
    *(s16 *)(ptr1 + 0x18) = val;

    if (val < 0) {
        *(s16 *)(ptr1 + 0x0) = 0;
        func_80178B18(a0, *(s32 *)(ptr2 + 0xC));
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}
