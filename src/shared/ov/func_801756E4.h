/* func_801756E4 — shared body (overlay slot 0x80128158, h_exact 55dfa77c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80175DA8(s32 a0);
extern void func_80175AB8(s32 a0);
extern void func_80176144(s32 a0);
extern short D_800B9A02;
void func_801756E4(s32 arg0) {
    s32 a = arg0;
    short *p;
    s32 f5;
    s32 sum;
    s16 neg;
    s32 b6;
    p = &D_800B9A02;
    f5 = *(u8 *)(a + 5);
    sum = *(u8 *)(a + 6) + f5;
    neg = -(s16)(sum & 0xFF);
    *(u8 *)(a + 6) = sum;
    __asm__ __volatile__("" : : : "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1)
    b6 = *(u8 *)(a + 6);
    *(u8 *)(a + 5) = (u8)f5 + 0xFF;
    *(s16 *)(a + 0x10) = neg;
    *(s16 *)(a + 0xc) = neg;
    *(u16 *)(a + 0x16) = b6;
    *(u16 *)(a + 0x12) = b6;
    *(u16 *)(a + 0xe) = b6;
    *(u16 *)(a + 0x14) = b6;
    func_80175DA8(*p);
    func_80175AB8(*p);
    func_80176144(*p);
    if (*(u8 *)(a + 5) == 0) {
        *(u8 *)(a + 8) = 0;
        *(u8 *)(a + 1) = *(u8 *)(a + 1) + 1;
    }
}
