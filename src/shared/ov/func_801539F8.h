/* func_801539F8 — shared body (overlay slot 0x80128158, h_exact c9a06d9f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern void *memcpy(void *dst, const void *src, u32 n);
s32 func_801539F8(s32 a0, void * a1)
{
    u8 buf1[8];
    u8 buf2[8];
    u8 buf3[8];
    s32 r1, r2, r3;
    memcpy(buf1, (void *)(a0 + 0xA0), 8);
    memcpy(buf2, a1, 8);
    *(s16 *)(buf1 + 2) -= 4;
    r1 = func_80133784(0, buf1, buf2);
    if (r1 != 0x2000) {
        return 1;
    }
    memcpy((void *)buf1, (void *)(s32)buf2, 8);
    *(s16 *)(buf2 + 2) += 8;
    r2 = func_80133784(0, buf1, buf2);
    if (r2 != r1) {
        return 1;
    }
    r3 = func_80133784(2, buf2, buf3);
    if (r3 != r2) {
        return 1;
    }
    *(s16 *)(a0 + 0x88) = *(s16 *)(buf2 + 0);
    *(s16 *)(a0 + 0x8A) = *(s16 *)(buf2 + 2);
    *(s16 *)(a0 + 0x8C) = *(s16 *)(buf2 + 4);
    memcpy((void *)(a0 + 0x90), (void *)(a0 + 0x88), 8);
    return 0;
}
