void func_80185214(s32 a0)
{
    extern s32 D_801EFC48;
    extern u8 D_80194724[];
    extern void func_80185A18(s32 idx, s32 val);
    s32 p;
    s32 i;
    s32 c;

    p = *(s32 *)(D_801EFC48 + 0xCC);
    for (i = 0; i < 5; i++) {
        c = *(u8 *)(p + i * 8 + 6);
        if (c < 0x15 && D_80194724[c] == 0) {
            func_80185A18(c, (s16)(*(u16 *)(p + i * 8 + 2) + a0));
        }
        if (*(s16 *)(p + i * 8 + 6) & 0x8000) {
            break;
        }
    }
}
