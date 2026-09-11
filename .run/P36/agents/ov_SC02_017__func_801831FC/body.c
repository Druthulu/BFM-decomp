void func_801831FC(s32 arg0) {
    s16 buf[4];
    s32 base;
    s32 s1;
    s16 dist;
    s32 q;
    s16 vol;

    base = (s32)&D_80126B58;
    s1 = (s32)D_8018E8EC + (*(s16 *)(arg0 + 0xFC)) * 8;
    if (*(s16 *)(s1 + 0x6) == 0) {
        return;
    }
    func_80015978(base + 4, (s32 *)buf);
    if (*(s16 *)(arg0 + 0xFC) == 3) {
        if (buf[1] < -0xB00) {
            return;
        }
        buf[1] = *(u16 *)(s1 + 0x2);
    }
    dist = func_80013294((void *)buf, (void *)s1);
    if (dist >= 0x800) {
        return;
    }
    q = (0x800 - dist) * 127 / 0x800;
    if (q < 0) {
        vol = 0;
    } else {
        vol = q;
    }
    if (vol >= 0x80) {
        vol = 0x7F;
    }
    func_8002D4C8(*(u16 *)(s1 + 0x6), (u16)(vol | 0x1000));
}
