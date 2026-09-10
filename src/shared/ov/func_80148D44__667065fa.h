/* func_80148D44 — shared body (overlay slot 0x80128158, h_exact 667065fa). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80148D44(void) {

    extern s32 D_801151D4;
    extern u8 D_80126C01;
    extern u16 D_80126C02;
    extern u16 D_80126C06;
    extern s16 (*D_801805FC[])(s32);
    s32 p = D_801151D4;
    s32 tmp = (ratan2(*(s32 *)(p + 0x44) - *(s32 *)(p + 0x50),
                      *(s32 *)(p + 0x48) - *(s32 *)(p + 0x3C)) - 0x400) & 0xFFF;
    s32 ang = tmp;

    switch (D_80126C01) {
    case 0x41:
        return D_801805FC[D_80126C02 >> 12](tmp);
    case 0x53:
    case 0x73:
        if ((D_80126C06 & 0xFF) == 0x80 && (D_80126C06 >> 8) == 0x80) {
            return -1;
        }
        tmp = ratan2((D_80126C06 & 0xFF) - 0x80, 0x80 - (D_80126C06 >> 8));
        return (ang + tmp) & 0xFFF;
    }
}
