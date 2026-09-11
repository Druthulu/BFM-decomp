void func_80185214(s32 a0)
{
    extern s32 D_801EFC48;
    extern u8 D_80194724[];
    extern void func_80185A18(s32 idx, s32 val);
    register s32 s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 s1;
    s32 s2;
    s32 c;

    s2 = a0;
    s0 = *(s32 *)(D_801EFC48 + 0xCC);
    s1 = s0 + 0x28;
    do {
        c = *(u8 *)(s0 + 6);
        if (c < 0x15 && D_80194724[c] == 0) {
            func_80185A18(c, (s16)(*(u16 *)(s0 + 2) + s2));
        }
        if (*(s16 *)(s0 + 6) & 0x8000) {
            break;
        }
        s0 += 8;
    } while (s0 < s1);
}
