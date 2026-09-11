s32 func_80185484_body(s32 a0) {
    extern void func_8012BE54(s32 a0);
    extern u16 D_80126B62;
    extern u8 D_801A31B0[];

    s32 ent;   /* $s1 */
    s32 p;
    s32 h;
    s32 h2;
    s32 ret;
    s32 s0;
    s32 r;
    s32 v;
    s32 g;
    s32 d;
    u16 arr[3];

    ent = a0;
    p = *(s32 *)(ent + 0x20);
    h = *(s16 *)(p + 0x18);
    ret = ((s32 (*)(s32))func_8012BE54)(ent);
    s0 = h >> 8;
    if (ret > s0 * s0) {
        return 0;
    }
    v = *(s16 *)(ent + 0xA);
    h2 = *(s16 *)(*(s32 *)(ent + 0x20) + 0x1A);
    g = *(s16 *)&D_80126B62;
    r = h2 >> 6;
    d = v - g;
    if (d >= 0 ? r < d : r < g - v) {
        return 0;
    }
    a0 = 1;
    arr[0] = *(u16 *)(ent + 0x6);
    arr[1] = *(u16 *)(ent + 0xA);
    arr[2] = *(u16 *)(ent + 0xE);
    func_8012F568(1, 0x4201, 0, 0x1C, (s32)arr, (s32)D_801A31B0);
}
