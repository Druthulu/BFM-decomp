void func_80188B64(s32 arg0) {
    s32 rv;
    s32 buf1[2];
    s32 buf2[2];

    ((void (*)(s32, s32, s32))func_8012F14C)((s32)D_80126B78 + 0x34, (s32)D_801AC098, (s32)buf1);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)D_80126B78 + 0x34, (s32)(D_801AC098 + 8), (s32)buf2);
    if (func_80135888(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58), (s32)buf1, (s32)buf2) == 0) {
        rv = 0;
    } else {
        func_8012F568(1, 0x201, *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), 0x23, (s32)buf2, (s32)D_801152A8);
        rv = 1;
    }
    __asm__ __volatile__("" : "=r"(rv) : "0"(rv));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
}
