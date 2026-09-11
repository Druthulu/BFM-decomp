void func_801823BC(a0, a1)
s32 a0;
s32 a1;
{
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_8017EF68(s32 a0, s32 a1, s32 a2);
    extern s16 D_801AEB52[];
    extern s32 D_801B20E0;
    extern s32 D_801A158C;
    extern s32 D_801AEB1C;
    s16 *q;
    s32 *r;

    q = D_801AEB52;
    *q = a0;
    func_80049CAC((s32)q - 2, (s32)q - 78);
    D_801AEB1C = (s16)a1;
    r = (s32 *)((s32)q - 82);
    *r = 0;
    func_8017EF68((s32)&D_801B20E0, (s32)&D_801A158C, (s32)r);
}
