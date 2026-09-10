s32 func_80148E54(s32 arg0) {

    extern s32 D_801151D4;
    extern s16 (*D_80191FA4[])();
    s32 ang = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                      *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;

    switch (*(u8 *)(arg0 + 0xA9)) {
    case 0x41:
        return D_80191FA4[*(u16 *)(arg0 + 0xAA) >> 12]();
    case 0x53:
    case 0x73:
        if ((*(u16 *)(arg0 + 0xAE) & 0xFF) == 0x80 && (*(u16 *)(arg0 + 0xAE) >> 8) == 0x80) {
            return -1;
        }
        return (ang + ratan2((*(u16 *)(arg0 + 0xAE) & 0xFF) - 0x80,
                             0x80 - (*(u16 *)(arg0 + 0xAE) >> 8))) & 0xFFF;
    }
}
