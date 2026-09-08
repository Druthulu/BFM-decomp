/* func_8012AF0C — shared body (overlay slot 0x80128158, h_exact b46ce263). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8012AF0C(s32 a0, s32 a1) {
    s32 s1 = a0;
    s32 s2 = a1;
    s16 spA[4];                /* sp+0x10 */
    struct M8012AF0C spB;      /* sp+0x18 (src) */
    struct M8012AF0C spC;      /* sp+0x20 (dst) */
    s16 spD[4];                /* sp+0x28 */
    spA[0] = *(u16 *)(s1 + 0x3A);
    spA[1] = *(u16 *)(s1 + 0x3E);
    spA[2] = *(u16 *)(s1 + 0x42);
    spB.a = *(u16 *)(s1 + 0x6);
    spB.b = *(u16 *)(s1 + 0xA);
    spB.c = *(u16 *)(s1 + 0xE);
    spC = spB;
    if (func_80135888(*(s32 *)(s2 + 0x20), *(s32 *)(s2 + 0x58), (s32)spA, (s32)&spC) != 0) {
        s32 r0, r1;
        spD[0] = *(u16 *)(s2 + 0x6);
        spD[1] = *(u16 *)(s2 + 0xA);
        spD[2] = *(u16 *)(s2 + 0xE);
        r0 = func_800132BC((s32)spD, (s32)spA);
        r1 = func_800132BC((s32)spD, (s32)&spB);
        if (r0 < r1) return 0;
        *(s32 *)(s1 + 0x4) = *(s32 *)(s1 + 0x38);
        *(s32 *)(s1 + 0x8) = *(s32 *)(s1 + 0x3C);
        *(s32 *)(s1 + 0xC) = *(s32 *)(s1 + 0x40);
        return 1;
    }
    return 0;
}
