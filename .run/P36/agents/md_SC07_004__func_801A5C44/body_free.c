void func_801A5C44(void) {
    s32 a0;
    s32 s0 = a0;
    s32 s2;
    s32 s1;
    s32 temp;

    temp = *(s16 *)(s0 + 0x100);
    s2 = *(s32 *)(s0 + 0xCC);
    s1 = *(s32 *)(s0 + 0xD4);
    temp = func_8004787C(temp) >> 4;
    *(s16 *)(s2 + 0x18) = *(u16 *)(s1 + (*(s16 *)(s0 + 0x70) * 4)) + temp;
    temp = func_8004787C(*(s16 *)(s0 + 0x100) + 0x800) >> 4;
    *(s16 *)(s2 + 0x1A) = *(u16 *)(s1 + (*(s16 *)(s0 + 0x70) * 4) + 2) + temp;
    *(u16 *)(s0 + 0x100) += 0x40;
}
