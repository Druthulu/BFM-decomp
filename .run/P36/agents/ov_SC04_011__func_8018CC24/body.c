void func_8018CC24(s32 arg0) {
    s32 a0;
    s32 a1;
    u16 val;

    func_8012AD80(arg0);

    a0 = *(s32 *)(arg0 + 0x20);
    *(u16 *)(a0 + 0x10) = *(u16 *)(a0 + 0x10) + (*(u16 *)(arg0 + 0x106));

    a1 = *(s32 *)(arg0 + 0x20);
    val = *(u16 *)(arg0 + 0x108);
    *(u16 *)(a1 + 0x14) = *(u16 *)(a1 + 0x14) + val;

    if ((*(s32 *)(arg0 + 0x1C) & 0x3) == 0) {
        func_8018A7E8(arg0);
    }

    *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;

    if (*(s16 *)(arg0 + 0xA) >= -0x3FF) {
        func_8012C218((void *)arg0);
    }
}
