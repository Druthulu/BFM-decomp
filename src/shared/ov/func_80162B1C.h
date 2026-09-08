/* func_80162B1C — shared body (overlay slot 0x80128158, h_exact 433ff414). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80162CC4(void);
extern s32 D_80126D40;
extern s32 D_8011F9D0;
void func_80162B1C(void) {
    s32 s3 = *(s32 *)&D_80126D40;
    s32 s2 = 0;
    s32 s1 = 0;
    s32 s0;
    s32 a0;
    s32 p;
    s32 fp;
    void (*f)(s32);
    do {
        s0 = s1 + (s32)&D_8011F9D0;
        *(s16 *)(s0 + 0x44) = *(u16 *)(s0 + 0x6);
        *(s16 *)(s0 + 0x46) = *(u16 *)(s0 + 0xA);
        *(s16 *)(s0 + 0x48) = *(u16 *)(s0 + 0xE);
        if (*(u16 *)(s0 + 0x0) != 0) {
            fp = *(s32 *)((*(u16 *)(s0 + 0x0) << 2) + s3 - 4);
            if (fp != 0) {
                f = (void (*)(s32))fp;
                f(s0);
            } else {
                ((void (*)(s32))func_80162CC4)(s0);
            }
            a0 = *(s32 *)(s0 + 0x20);
            if (a0 != 0) {
                if (*(u16 *)a0 == 1) {
                    s32 b0 = *(u16 *)(s0 + 0x6);
                    *(s16 *)(a0 + 0x8) = b0;
                    *(s32 *)(a0 + 0x48) = (s16)b0;
                    b0 = *(u16 *)(s0 + 0xA);
                    *(s16 *)(a0 + 0xA) = b0;
                    *(s32 *)(a0 + 0x4C) = (s16)b0;
                    {
                        s32 m = *(u16 *)(a0 + 0x2C) | 1;
                        s32 c0 = *(u16 *)(s0 + 0xE);
                        *(s16 *)(a0 + 0xC) = c0;
                        *(s16 *)(a0 + 0x2C) = m;
                        *(s32 *)(a0 + 0x50) = (s16)c0;
                    }
                } else if ((p = *(s32 *)(a0 + 0x34)) != 0) {
                    s32 b0 = *(u16 *)(s0 + 0x6);
                    *(s16 *)(a0 + 0x8) = b0;
                    *(s32 *)(p + 0x14) = (s16)b0;
                    b0 = *(u16 *)(s0 + 0xA);
                    *(s16 *)(a0 + 0xA) = b0;
                    *(s32 *)(*(s32 *)(a0 + 0x34) + 0x18) = (s16)b0;
                    b0 = *(u16 *)(s0 + 0xE);
                    *(s16 *)(a0 + 0xC) = b0;
                    *(s32 *)(*(s32 *)(a0 + 0x34) + 0x1C) = (s16)b0;
                } else {
                    *(s16 *)(a0 + 0x8) = *(u16 *)(s0 + 0x6);
                    *(s16 *)(a0 + 0xA) = *(u16 *)(s0 + 0xA);
                    *(s16 *)(a0 + 0xC) = *(u16 *)(s0 + 0xE);
                }
            }
        }
        s2 += 1;
        s1 += 0x68;
    } while (s2 < 0x14);
}
