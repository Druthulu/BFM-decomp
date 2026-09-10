int func_80178970(void)
{

    extern s16 D_80185C08;
    int r;
    int v;

    v = ((s32 (*)(void))func_801789AC)();
    r = 0;
    if (v != 0)
        r = D_80185C08 == 0;
    return r;
}
