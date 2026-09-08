/* func_8016AFB0 — shared body (overlay slot 0x80128158, h_exact fa06c035). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016B234();
extern void func_800D22E4(s32 a0);
void func_8016AFB0(s32 a0) {
    s32 s0 = a0;
    s32 s1 = *(s32 *)(s0 + 0x20);
    s32 v1;
    s32 v0;
    if ((u32)*(s32 *)(s0 + 0x2C) < 6) {
        func_8016B234();
    }
    v1 = *(s32 *)(s0 + 0x2C);
    if (v1 == 5) goto L9C;
    if ((u32)v1 < 6) {
        if (v1 == 1) goto L9C;
        goto LB8;
    }
    if (v1 == 6) goto L38;
    if (v1 != 7) goto LB8;
    if (*(s32 *)(s0 + 0x1C) & 0x1) {
        v1 = 0xAE;
    } else {
        v1 = 0xB4;
    }
    *(s8 *)(s1 + 0x27) = v1;
L38:
    v0 = *(u8 *)(s1 + 0x26) - 0x8;
    *(s8 *)(s1 + 0x26) = v0;
    *(s8 *)(s1 + 0x25) = v0;
    *(s8 *)(s1 + 0x24) = v0;
    v0 = *(s32 *)(s0 + 0x1C) - 1;
    *(s32 *)(s0 + 0x1C) = v0;
    if (v0 != 0) goto LFC;
    *(s8 *)(s1 + 0x26) = 0x70;
    *(s8 *)(s1 + 0x25) = 0x70;
    *(s8 *)(s1 + 0x24) = 0x70;
    *(s32 *)(s1 + 0x4) = *(s32 *)(s1 + 0x4) | 0x50000000;
    *(s32 *)(s0 + 0x1C) = 0x7;
    *(u16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1;
    goto LFC;
L9C:
    func_800D22E4(s0);
    *(s32 *)(s0 + 0x14) = *(s32 *)(s0 + 0x14) + 0x18000;
LB8:
    v0 = *(u16 *)(s0 + 0x24) - 0x8;
    v1 = *(s32 *)(s0 + 0x1C) - 1;
    *(u16 *)(s0 + 0x24) = v0;
    *(s32 *)(s0 + 0x1C) = v1;
    if (v1 != 0) goto LFC;
    *(u16 *)(s0 + 0x24) = 0x70;
    *(s32 *)(s0 + 0x1C) = 0x7;
    *(u16 *)(s0 + 0x26) = *(u16 *)(s0 + 0x26) + 1;
    *(u16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1;
LFC:
    return;
}
