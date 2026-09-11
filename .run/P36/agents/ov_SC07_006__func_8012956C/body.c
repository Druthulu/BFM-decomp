void func_8012956C(void) {

    extern s32 D_801F4D5C;

    extern s16 D_80114EE0;
    extern u8 D_800B9A78;
    extern u8 D_801F4D5D[];
    extern u8 D_801F4D5E[];
    extern u8 D_801F4D60[];
    extern u8 D_801F4D61[];
    extern u8 D_801F4D62[];
    extern u8 D_801F62E0;
    extern u8 D_800AF630[];
    extern u8 D_800A6518[];
    s32 *sp10;
    u8 *afbase;
    s32 *sp0;
    Ent_956C *base;
    s32 i;

    sp10 = (s32 *)0x1F800010;
    sp0 = (s32 *)0x1F800000;
    afbase = (u8 *)&D_800AF630;
    if (D_80114EE0 == 0) {
        return;
    }
    base = (Ent_956C *)&D_800B9A78;
    i = 0;
    do {
        s32 idx = i * 8 + 4;
        switch (base->f34) {
        case 0x7FFF:
            break;
        case 0x7FFD:
            if (i == 0) {
                func_801299C8(D_801F62E0, 1, base);
            }
            func_80015B6C(-0xA0, -0x74, 0x140, 0x8C,
                          D_801F4D60[0], D_801F4D60[1], D_801F4D60[2],
                          D_801F4D60[4], D_801F4D60[5], D_801F4D60[6]);
            func_80015B6C(-0xA0, 0x18, 0x140, 0x3C,
                          D_801F4D60[4], D_801F4D60[5], D_801F4D60[6],
                          D_801F4D60[8], D_801F4D60[9], D_801F4D60[0xA]);
            func_80015B6C(-0xA0, 0x54, 0x140, 0x28,
                          D_801F4D60[8], D_801F4D60[9], D_801F4D60[0xA],
                          D_801F4D60[0xC], D_801F4D60[0xD], D_801F4D60[0xE]);
            break;
        case 0x7FFE:
            func_801299C8(D_801F62E0, (s16)(i * 2), base);
            func_80015B6C(-0xA0, *(s16 *)&base->f3A, 0x140, base->f3E,
                          ((u8 *)&D_801F4D5C)[idx], D_801F4D5D[idx], D_801F4D5E[idx],
                          D_801F4D60[idx], D_801F4D61[idx], D_801F4D62[idx]);
            break;
        default:
            base->f1C = base->f40 + base->f38;
            base->f1E = base->f42 + base->f3A;
            func_801299C8(D_801F62E0, (s16)(i + 3), base);
            *(Blk16_956C *)sp0 = *(Blk16_956C *)base;
            {
                s32 *dst = sp10;
                s32 *src = (s32 *)((u8 *)base + 0x10);
                s32 *end = (s32 *)((u8 *)base + 0x30);
                do {
                    *(Blk16_956C *)dst = *(Blk16_956C *)src;
                    src += 4;
                    dst += 4;
                } while (src != end);
                *dst = *src;
                sp10[5] = (s32)sp0;
                if (base->f36 == 0) {
                    GsSortFastBg(sp10, &D_800A6518[(*(u16 *)(afbase + 0xA3D2)) * 0x14], base->f34, dst);
                } else {
                    GsSortBg(sp10, &D_800A6518[(*(u16 *)(afbase + 0xA3D2)) * 0x14], base->f34, dst);
                }
            }
            break;
        }
        base += 1;
        i += 1;
    } while (i < 2);
}
