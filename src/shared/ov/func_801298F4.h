/* func_801298F4 — shared body (overlay slot 0x80128158, h_exact 66d5a6ea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern unsigned short D_800B99F0;
void func_801298F4(void *arg0) {
    register u8 *a __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B headers1)
    s32 base4C;
    register u32 b __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
    register u16 f38 __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B headers1)
    register u16 f3E __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B headers1)
    u32 sh;
    u8 *p;
    a = (u8 *) arg0;
    base4C = *(s32 *)(a + 0x4C);
    p = *(u8 **)(a + 0x50);
    f38 = *(u16 *)(a + 0x38);
    f3E = *(u16 *)(a + 0x3E);
    base4C += 8;
    p += 4;
    b = *p++; *(s16 *)(a + 0x2) = (u16) b;
    b = *p++; *(s16 *)(a + 0x4) = (u16) b;
    b = *p++; *(u8 *)(a + 0x0) = b;
    b = *p++; *(s32 *)(a + 0x8) = base4C;
    *(s32 *)(a + 0xC) = (s32) p;
    *(u8 *)(a + 0x1) = b;
    sh = ((u32)(u8) *(u8 *)(base4C + 0x6) >> 7) << 0x18;
    base4C = *(u16 *)(a + 0x3A);
    b = *(u16 *)(a + 0x3C);
    *(s16 *)(a + 0x14) = f38;
    *(s16 *)(a + 0x1A) = f3E;
    *(s16 *)(a + 0x16) = base4C;
    *(s16 *)(a + 0x18) = b;
    *(s32 *)(a + 0x10) = sh | 0x08000000;
    if (D_800B99F0 == 0) {
        *(s16 *)(a + 0x1E) = 0;
        *(s16 *)(a + 0x1C) = 0;
    }
    *(u8 *)(a + 0x22) = 0x80;
    *(u8 *)(a + 0x21) = 0x80;
    *(u8 *)(a + 0x20) = 0x80;
    *(s16 *)(a + 0x28) = 0xA0;
    *(s16 *)(a + 0x2A) = 0x78;
    *(s32 *)(a + 0x24) = (s32) a;
    *(s16 *)(a + 0x2E) = 0x1000;
    *(s16 *)(a + 0x2C) = 0x1000;
    *(s32 *)(a + 0x30) = 0;
}
