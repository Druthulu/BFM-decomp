void func_8018CCB8(s32 arg0) {
    s32 s0;
    s32 ptr;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 v1;
    s32 v1_sign;
    Blk8 sp10;

    s0 = arg0;

    sp10 = D_801ED9AC[0];

    func_8012AD80(arg0);

    ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x106);
    v0 = *(u16 *)(ptr + 0x10);
    v0 = v0 + v1;
    *(u16 *)(ptr + 0x10) = (u16)v0;

    ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x108);
    v0 = *(u16 *)(ptr + 0x14);
    v0 = v0 + v1;
    *(u16 *)(ptr + 0x14) = (u16)v0;

    v0 = *(s32 *)(s0 + 0x1C);
    if ((v0 & 0x3) == 0) {
        func_8018B0B0((void *)arg0, &sp10, (void *)0, 8);
    }

    v0 = *(s32 *)(s0 + 0x1C);
    v1_sign = *(s16 *)(s0 + 0xA);
    v0++;
    *(s32 *)(s0 + 0x1C) = v0;

    if (v1_sign >= -0x77F) {
        func_8012C218((void *)arg0);
    }
}
