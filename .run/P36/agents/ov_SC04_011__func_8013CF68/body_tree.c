void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_801F1558;
    extern u8 D_801F1559;
    extern u8 D_801F155A;
    extern u8 D_801F155B;
    extern u8 D_801F155C;
    extern u8 D_801F155D;
    extern u8 D_801F155E;
    extern u8 D_801F155F;
    extern u8 D_801F1560;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));  // !FAKE: instruction la — NEEDED DIFFERS (P36 rung B t3_tus1)

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801F1558; t1 = D_801F1559; t2 = D_801F155A;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801F155B; t1 = D_801F155C; t2 = D_801F155D;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801F155E; t1 = D_801F155F; t2 = D_801F1560;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}
