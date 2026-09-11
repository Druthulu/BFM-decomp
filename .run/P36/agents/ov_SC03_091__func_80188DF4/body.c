s32 func_80188DF4(s32 a0)
{
    s32 *p;
    s32 t;

    t = *(s32 *)(a0 + 0xE0);
    if (t == 0) {
        return 1;
    }
    t -= 1;
    *(s32 *)(a0 + 0xE0) = t;
    if (t > 0) {
        return 0;
    }

    p = *(s32 **)(a0 + 0xD0);
    p += 2;
    if ((*p & 0x40000000) != 0) {
        p = *(s32 **)(a0 + 0xCC);
    } else if (*p < 0) {
        *(s32 *)(a0 + 0xE0) = 0;
        return 1;
    }
    t = p[0];
    *(s32 **)(a0 + 0xD0) = p;
    *(s32 *)(a0 + 0xE0) = t;
    func_800183E0(p[1]);
    return 0;
}
