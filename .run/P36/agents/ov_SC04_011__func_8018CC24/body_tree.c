void func_8018CC24(s32 a0) {
    s32 s0;
    s32 a0_ptr;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 v1;
    s32 v1_sign;

    s0 = a0;

    func_8012AD80(a0);

    a0_ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x106);
    v0 = *(u16 *)(a0_ptr + 0x10);
    v0 = v0 + v1;
    *(u16 *)(a0_ptr + 0x10) = (u16)v0;

    a0_ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x108);
    v0 = *(u16 *)(a0_ptr + 0x14);
    v0 = v0 + v1;
    *(u16 *)(a0_ptr + 0x14) = (u16)v0;

    v0 = *(s32 *)(s0 + 0x1C);
    if ((v0 & 0x3) == 0) {
        func_8018A7E8(a0);
    }

    v0 = *(s32 *)(s0 + 0x1C);
    v1_sign = *(s16 *)(s0 + 0xA);
    v0++;

    *(s32 *)(s0 + 0x1C) = v0;

    if (v1_sign >= -0x3FF) {
        func_8012C218((void *)a0);
    }
}
