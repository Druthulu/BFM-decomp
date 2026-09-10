int func_80178970(void)
{
    register int r __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    int v;

    v = ((s32 (*)(void))func_801789AC)();
    r = 0;
    if (v != 0)
        r = D_801F1638 == 0;
    return r;
}
