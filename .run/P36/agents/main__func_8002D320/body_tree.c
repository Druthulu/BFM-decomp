void func_8002D320(void)
{
    /* TU-absent names, block scope */
    extern Slot D_800A4C28[];
    extern void func_8003D3B4(s32, s32);
    extern void func_8003C23C(s32, s32);
    extern void func_8003BE74(s32, s32);
    extern void func_8003B250(s32, void *);

    register u8 *p __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    u32 mask;
    register s32 i __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus9)

    i = 0;
    mask = 0x60000;
    p = D_800A4C6D;
    do {
        if (*p != 0) {
            if (p[-1] == 0 || (*(u32 *)(p - 0x41) & mask) == 0) {
                func_8003D3B4(*(s32 *)(p - 5), 1);
            }
            *p = 0;
        }
        i++;
        p += 0x48;
    } while (i < 8);

    if ((D_800A2B98 & 0xFF0000) != 0) {
        func_8003C23C(0, D_800A2B98 & 0xFF0000);
        D_800A2B98 = *(u16 *)&D_800A2B98;
    }
    if ((D_800A2BA0 & 0xFF0000) != 0) {
        func_8003BE74(0, D_800A2BA0 & 0xFF0000);
        D_800A2BA0 = *(u16 *)&D_800A2BA0;
    }

    mask = (u32)D_800A4C28;
    i = 0;
    p = (u8 *)mask + 4;
    do {
        if (p[0x40] != 0) {
            Slot *b2 = (Slot *)mask;
            s32 id = *(s32 *)(p + 0x3C);
            p[0x40] = 0;
            func_8003B250(id, b2);
            *(s32 *)p = 0;
        }
        p += 0x48;
        i++;
        mask += 0x48;
    } while (i < 8);

    if ((D_800C7D20 & 0xFF0000) != 0) {
        func_8003C23C(1, D_800C7D20 & 0xFF0000);
        D_800C7D20 = *(u16 *)&D_800C7D20;
    }
    if ((D_800C7D2C & 0xFF0000) != 0) {
        func_8003BE74(1, D_800C7D2C & 0xFF0000);
        D_800C7D2C = *(u16 *)&D_800C7D2C;
    }
}
