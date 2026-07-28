extern s32 ratan2(s32, s32);
extern s32 D_801151D4;
/* derived from asm: lui/addu/lw %lo(D_80188694) indexed by (u16>>12)*4, then jalr with no args;
 * the result is sign-extended from 16 bits => the table's functions return s16. */
extern s16 (*D_80188694[])();

s32 func_80148E54(s32 arg0) {
    register s32 tmp __asm__("$4") = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                                             *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 ang;
    __asm__("" : "=r"(tmp) : "0"(tmp));
    ang = tmp;

    switch (*(u8 *)(arg0 + 0xA9)) {
    case 0x41:
        return D_80188694[*(u16 *)(arg0 + 0xAA) >> 12]();
    case 0x53:
    case 0x73:
        if ((*(u16 *)(arg0 + 0xAE) & 0xFF) == 0x80 && (*(u16 *)(arg0 + 0xAE) >> 8) == 0x80) {
            return -1;
        }
        return (ang + ratan2((*(u16 *)(arg0 + 0xAE) & 0xFF) - 0x80,
                             0x80 - (*(u16 *)(arg0 + 0xAE) >> 8))) & 0xFFF;
    }
}
