s32 aF8018632C(s32 a0) {
    extern void func_8012BE54(s32 a0);
    extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
    extern u16 D_80126B62;
    extern u8 D_801A61DC[];

    s32 h;
    s32 h2;
    s32 ret;
    s32 s0;
    s32 r;
    s32 v;
    s32 g;
    s32 d;
    u16 arr[3];

    h = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18);
    ret = ((s32 (*)(s32))func_8012BE54)(a0);
    s0 = (s16)h >> 8;
    if (ret > s0 * s0) {
        return 0;
    }
    v = *(s16 *)(a0 + 0xA);
    h2 = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
    g = *(s16 *)&D_80126B62;
    r = (s16)h2 >> 6;
    d = v - g;
    if (d >= 0 ? r < d : r < g - v) {
        return 0;
    }
    arr[0] = *(u16 *)(a0 + 0x6);
    arr[1] = *(u16 *)(a0 + 0xA);
    arr[2] = *(u16 *)(a0 + 0xE);
    func_8012F568(1, 0x4201, 0, 0x1C, (s32)arr, (s32)D_801A61DC);
}
