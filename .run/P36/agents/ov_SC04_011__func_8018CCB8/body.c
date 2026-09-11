void func_8018CCB8(s32 arg0) {
    s32 a0;
    s32 a1;
    u16 val;
    Blk8 sp10;

    sp10 = D_801ED9AC[0];

    func_8012AD80(arg0);

    a0 = *(s32 *)(arg0 + 0x20);
    *(u16 *)(a0 + 0x10) = *(u16 *)(a0 + 0x10) + (*(u16 *)(arg0 + 0x106));

    a1 = *(s32 *)(arg0 + 0x20);
    val = *(u16 *)(arg0 + 0x108);
    *(u16 *)(a1 + 0x14) = *(u16 *)(a1 + 0x14) + val;

    if ((*(s32 *)(arg0 + 0x1C) & 0x3) == 0) {
        func_8018B0B0((void *)arg0, &sp10, (void *)0, 8);
    }

    *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;

    if (*(s16 *)(arg0 + 0xA) >= -0x77F) {
        func_8012C218((void *)arg0);
    }
}
