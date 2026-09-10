void func_8017ECEC(s32 a0, s16 a1, s16 a2) {
    u32 buf[4];
    register s32 hi __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
    s32 lo;

    func_8012B0B4(buf, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), a1 << 4);

    lo = *(s16 *)buf;
    hi = *(s32 *)buf;
    *(s32 *)(a0 + 0x10) = lo << 12;
    *(s32 *)(a0 + 0x18) = (hi >> 16) << 12;
    if (a2 != 0) {
        *(s32 *)(a0 + 0x1C) = a2;
    }
}
