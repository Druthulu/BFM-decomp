void func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4)
{
    extern s32 D_8011D030;
    extern unsigned char D_80184418[];

    int t2;
    int t3;
    int p2;
    int p3;

    unsigned short *puVar1;
    short iVar2;
    int eq;

    iVar2 = 0;
    puVar1 = ((unsigned short *)&D_8011D030);
    t2 = (short)param_2;
    p2 = (short)t2;
    t3 = (short)param_3;
    p3 = (short)t3;
    eq = (t2 == t3);
    do {
        if ((puVar1 != ((unsigned short *)param_1)) &&
            ((unsigned int)*puVar1 == p2 || (unsigned int)*puVar1 == p3) &&
            (!eq ||
             *(int *)(puVar1 + 0x16) == *(int *)(((unsigned short *)param_1) + 0x16))) {
            ((void(*)(unsigned short *))func_80146C3C)(puVar1);
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x2c;
    } while (iVar2 < 0x1e);
    ((void(*)(void *, int))func_80016714)(&D_80184418[((short)param_4) * 0xc4], 0xc4);
}
