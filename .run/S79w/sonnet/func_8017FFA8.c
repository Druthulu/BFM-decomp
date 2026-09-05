void func_8017FFA8(s32 param_1)
{
    extern volatile s32 D_801C7E30;
    extern volatile s32 D_801C7E4C;
    extern s32 D_801C7E60;
    extern u8 D_80192478[];
    extern u16 D_801922B8;
    extern u16 D_80126B62;
    extern s32 D_8019231C;
    extern s32 func_8012C588(s32 a0, s32 a1);
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern void func_801746DC(void);
    extern s32 func_80178970(s32 a0);
    extern void func_80178D18(s32 a0);

    s32 found;
    s32 i;
    s32 *tbl;
    s16 *b62;
    s32 q;
    s32 sub;
    s32 a;
    u16 b;
    u16 lookup;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        found = 0;
        i = 0;
        tbl = (s32 *)&D_801C7E30;
        b62 = (s16 *)&D_80126B62;
        for (; i < 6; i++) {
            q = tbl[D_80192478[i]];
            sub = *(s32 *)(q + 0x6C);
            if (*(u8 *)(sub + 0x74) != 0) {
                a = *(s16 *)(sub + 0x70);
                b = *(u16 *)(sub + 0xA);
                lookup = *(u16 *)((u8 *)&D_801922B8 + (a << 4));
                found = 1;
                *(s32 *)((u8 *)b62 + 0xA) = 0;
                *b62 = b + lookup;
            }
        }
        if (!found) {
            break;
        }
        func_80178B18(param_1, (s32)&D_8019231C);
        func_801746DC();
        goto tail_inc;
    case 4:
        D_801C7E60 = func_8012C588(0x27C, param_1);
        /* fallthrough */
    case 2:
    tail_inc:
        *(u16 *)(param_1 + 0x34) += 1;
        break;
    case 1:
    case 3:
    case 5:
        break;
    }
    if (func_80178970(param_1)) {
        func_80178D18(param_1);
        *(u16 *)(param_1 + 2) = 1;
        *(u16 *)(param_1 + 0x34) = 0;
        *(s32 *)(param_1 + 0x1C) = 0x1E;
        *(s32 *)(D_801C7E4C + 0xE0) = 0;
    }
}
