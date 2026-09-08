/* func_8017742C — shared body (overlay slot 0x80128158, h_exact eb5a3490). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_8011F837;
extern u8 D_8011F7F0;
extern u8 D_8011F7AB;
u32 *func_8017742C(u32 *param_1, s32 param_2, s32 param_3) {
    s16 sVar1;
    u32 uVar2;
    s32 a3 = (s32)param_1;
    register s32 t1 __asm__("$9") = param_2;
    s32 t0 = a3;
    u8 *base = &D_8011F7F0;
    *(u32 *)a3 = (a3 - 0x14) & 0xffffff | 0x3000000;
    *(u8 *)(a3 + 7) = 0x60;
    if (D_8011F837 < 0x80) {
        *(u8 *)(a3 + 4) = 0xff;
        *(u8 *)(a3 + 6) = 0x10;
        *(u8 *)(a3 + 5) = 0x10;
    } else if (D_8011F837 == 0x80) {
        switch (D_8011F7AB) {
        default:
            D_8011F7AB = 0;
        case 0:
            *(u8 *)(t0 + 4) = 0xff;
            *(u8 *)(t0 + 6) = 0x30;
            *(u8 *)(t0 + 5) = 0x30;
            break;
        case 1:
            *(u8 *)(a3 + 5) = 0xff;
            *(u8 *)(a3 + 6) = 0x30;
            *(u8 *)(a3 + 4) = 0x30;
            break;
        case 2:
            *(u8 *)(a3 + 6) = 0xff;
            *(u8 *)(a3 + 5) = 0x30;
            *(u8 *)(a3 + 4) = 0x30;
            break;
        }
        {
            u8 *p = &D_8011F7AB;
            *p = *p + 1;
        }
    } else {
        *(u8 *)(a3 + 5) = 0xff;
        *(u8 *)(a3 + 6) = 0x10;
        *(u8 *)(a3 + 4) = 0x10;
    }
    a3 += 0x14;
    *(u16 *)(t0 + 8) = t1;
    uVar2 = (u32)base[0x47];
    *(u16 *)(t0 + 0xc) = 8;
    sVar1 = (s16)((s32)(uVar2 * 3) >> 3);
    {
        s32 d = param_3 + 0x48;
        *(s16 *)(t0 + 0xa) = d - sVar1;
    }
    *(s16 *)(t0 + 0xe) = sVar1;
    *(u32 *)a3 = (a3 - 0x14) & 0xffffff | 0x3000000;
    *(u8 *)(a3 + 7) = 0x60;
    *(u8 *)(a3 + 5) = 0x40;
    *(u8 *)(a3 + 4) = 0x40;
    t0 = a3;
    if (base[0x47] != 0) {
        *(u8 *)(a3 + 6) = 0xa0;
    } else {
        *(u8 *)(a3 + 6) = 0x40;
    }
    *(u16 *)(t0 + 0xc) = 8;
    *(u16 *)(t0 + 0xe) = 0x48;
    *(u16 *)(t0 + 8) = t1;
    *(s16 *)(t0 + 0xa) = param_3;
    return (u32 *)(a3 + 0x14);
}
