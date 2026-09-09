/* func_8013CF68 — shared body (overlay slot 0x80128158, h_exact 94315c4c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_8018F9D0;
    extern u8 D_8018F9D1;
    extern u8 D_8018F9D2;
    extern u8 D_8018F9D3;
    extern u8 D_8018F9D4;
    extern u8 D_8018F9D5;
    extern u8 D_8018F9D6;
    extern u8 D_8018F9D7;
    extern u8 D_8018F9D8;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_8018F9D0; t1 = D_8018F9D1; t2 = D_8018F9D2;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_8018F9D3; t1 = D_8018F9D4; t2 = D_8018F9D5;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_8018F9D6; t1 = D_8018F9D7; t2 = D_8018F9D8;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}
