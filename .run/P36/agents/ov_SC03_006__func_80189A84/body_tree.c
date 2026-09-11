void func_80189A84(s32 a0)
{
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
    register s32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus7)

    v0 = *(s32 *)(a0 + 0xDC);
    if ((v0 & 0x2) != 0) {
        v0 = *(s32 *)(a0 + 0x1C);
        if (v0 >= 0x15) {
            v1 = *(s32 *)(a0 + 0x20);
            v0 = *(u16 *)(v1 + 0x10);
            *(s16 *)(v1 + 0x10) = v0 - 0x28;
        }
    }

    v0 = *(s32 *)(a0 + 0x1C);
    if (v0 < 0x11) {
        v0 = *(s32 *)(a0 + 0x20);
        v1 = *(s32 *)(v0 + 0x4);
        v1 = v1 ^ 0x80000000;
        *(s32 *)(v0 + 0x4) = v1;
    }

    if (func_8012BEE8(a0) != 0) {
        func_8002AC00(0xB);
        func_80130D48(a0);
        func_8018A05C(a0);
    }
}
