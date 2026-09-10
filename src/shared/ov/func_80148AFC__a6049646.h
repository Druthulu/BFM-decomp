/* func_80148AFC — shared body (overlay slot 0x80128158, h_exact a6049646). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
int func_80148AFC(void *a0) {

    extern s32 D_801151D4;
    extern s32 (*D_801805BC[])(void *, s32);
    s32 p = (s32)a0;
    s32 iVar5 = *(s32 *)(p + 0x20);
    s32 tmp = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                      *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 ang = tmp;

    switch (*(u8 *)(p + 0xA9)) {
    case 0x41:
        return D_801805BC[*(u16 *)(p + 0xAA) >> 12](a0, tmp) & 0xFF;
    case 0x53:
    case 0x73:
        if ((*(u16 *)(p + 0xAE) & 0xFF) == 0x80 && (*(u16 *)(p + 0xAE) >> 8) == 0x80) {
            return 0;
        }
        tmp = ratan2((*(u16 *)(p + 0xAE) & 0xFF) - 0x80, 0x80 - (*(u16 *)(p + 0xAE) >> 8));
        *(u16 *)(iVar5 + 0x12) = (ang + tmp) & 0xFFF;
        return 1;
    }
}
