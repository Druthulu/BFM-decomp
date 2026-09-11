void func_801831FC(s32 arg0) {
    s32 s0 = arg0;
    s32 v0;
    s16 buf[4];
    s32 base;
    s32 s1;
    s16 v1;
    s16 a1;

    base = (s32)&D_80126B58;
    s1 = (s32)D_8018E8EC + (*(s16 *)(s0 + 0xFC)) * 8;
    if (*(s16 *)(s1 + 0x6) == 0) {
        return;
    }
    func_80015978(base + 4, (s32 *)buf);
    if (*(s16 *)(s0 + 0xFC) == 3) {
        if (buf[1] < -0xB00) {
            return;
        }
        buf[1] = *(u16 *)(s1 + 0x2);
    }
    v0 = func_80013294((void *)buf, (void *)s1);
    v1 = (s16)v0;
    if (v1 >= 0x800) {
        return;
    }
    v0 = (0x800 - v1) * 127;
    if (v0 < 0) {
        v0 += 0x7FF;
    }
    v0 = v0 >> 11;
    if (v0 < 0) {
        a1 = 0;
    } else {
        a1 = v0;
    }
    if (a1 >= 0x80) {
        a1 = 0x7F;
    }
    func_8002D4C8(*(u16 *)(s1 + 0x6), (u16)(a1 | 0x1000));
}
