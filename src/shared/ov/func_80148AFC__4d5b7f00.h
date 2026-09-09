/* func_80148AFC — shared body (overlay slot 0x80128158, h_exact 4d5b7f00). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
int func_80148AFC(void *a0) {

    extern s32 D_801151D4;
    extern ActorFn D_80180D70[];
    s32 p = (s32)a0;
    s32 iVar5 = *(s32 *)(p + 0x20);
    register s32 tmp __asm__("$5") = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                        *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 sVar3;
    u8 bVar1;
    __asm__("" : "=r"(tmp) : "0"(tmp));
    sVar3 = tmp;
    bVar1 = *(u8 *)(p + 0xA9);

    switch (bVar1) {
    case 0x41:
        return D_80180D70[*(u16 *)(p + 0xAA) >> 12](a0) & 0xFF;
    case 0x53:
    case 0x73:
        {
            register u32 bb __asm__("$3");
            register s32 c80 __asm__("$2") = 0x80;
            register s32 lo __asm__("$4");
            register s32 hi __asm__("$2");
            bb = *(u16 *)(p + 0xAE);
            lo = bb & 0xFF;
            if (lo != c80 || (hi = bb >> 8) != 0x80) {
                s32 sVar4;
                __asm__ __volatile__("" : : : "memory");
                sVar4 = ratan2((*(u16 *)(p + 0xAE) & 0xFF) - 0x80, 0x80 - (*(u16 *)(p + 0xAE) >> 8));
                *(u16 *)(iVar5 + 0x12) = (sVar3 + sVar4) & 0xFFF;
                return 1;
            }
            return 0;
        }
    }
}
