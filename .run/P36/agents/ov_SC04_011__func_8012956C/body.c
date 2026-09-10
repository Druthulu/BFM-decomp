void func_8012956C(void) {

    extern s16 D_80114EE0;
    extern u8 D_800B9A78;
    extern u8 D_801ED9C5[];
    extern u8 D_801ED9C6[];
    extern u8 D_801ED9C8[];
    extern u8 D_801ED9C9[];
    extern u8 D_801ED9CA[];
    extern u8 D_801F1620;
    extern u8 D_800AF630[];
    extern u8 D_800A6518[];
    s32 *sp10;
    u8 *afbase;
    s32 *sp0;
    Ent_956C *base;
    s32 i;
    s16 a1;
    u32 temp_a3;
    u32 arg0;
    u32 s;
    u32 s2;
    s32 code;

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
        code = base->f34;
        if (code == 0x7FFE) {
            goto case_7FFE;
        }
        if (code < 0x7FFF) {
            a1 = i + 3;
            if (code == 0x7FFD) {
                goto case_7FFD;
            }
            goto do_default;
        }
        a1 = i + 3;
        if (code != 0x7FFF) {
            goto do_default;
        }
        goto next;
    case_7FFD:
        if (i == 0) {
            func_801299C8(D_801F1620, 1, base);
        }
        func_80015B6C(-0xA0, -0x74, 0x140, 0x8C,
                      D_801ED9C8[0], D_801ED9C8[1], D_801ED9C8[2],
                      D_801ED9C8[4], D_801ED9C8[5], D_801ED9C8[6]);
        func_80015B6C(-0xA0, 0x18, 0x140, 0x3C,
                      D_801ED9C8[4], D_801ED9C8[5], D_801ED9C8[6],
                      D_801ED9C8[8], D_801ED9C8[9], D_801ED9C8[0xA]);
        func_80015B6C(-0xA0, 0x54, 0x140, 0x28,
                      D_801ED9C8[8], D_801ED9C8[9], D_801ED9C8[0xA],
                      D_801ED9C8[0xC], D_801ED9C8[0xD], D_801ED9C8[0xE]);
        goto next;
    case_7FFE:
        func_801299C8(D_801F1620, (s16)(i * 2), base);
        func_80015B6C(-0xA0, *(s16 *)&base->f3A, 0x140, base->f3E,
                      ((u8 *)&D_801ED9C4)[idx], D_801ED9C5[idx], D_801ED9C6[idx],
                      D_801ED9C8[idx], D_801ED9C9[idx], D_801ED9CA[idx]);
        goto next;
    do_default:
        arg0 = D_801F1620;
        temp_a3 = base->f38;
        s = base->f40 + temp_a3;
        base->f1C = s;
        s2 = base->f42 + base->f3A;
        base->f1E = s2;
        ((void (*)(s32, s32, void *, s32))func_801299C8)(arg0, a1, base, temp_a3);
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
    next:
        base += 1;
        i += 1;
    } while (i < 2);
}
