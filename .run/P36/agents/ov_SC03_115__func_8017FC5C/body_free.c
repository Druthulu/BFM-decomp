void func_8017FC5C(s32 *a0, s32 a1, s32 a2) {

    extern s16 D_80126CBA;
    s32 sp10[4];
    s32 sp20;
    s16 *q;
    u16 *p;
    s16 t;
    s32 rv;

    q = &D_80126CBA;
    if (*q == 0) {
        p = (u16 *)(q - 3);
        *(s32 *)(a1 + 0xE0) = 0;
    } else {
        p = (u16 *)(a1 + 0x88);
        *(s32 *)(a1 + 0xE0) = 1;
    }
    *(s16 *)((s32)sp10 + 0x2) = p[0] + *(u16 *)a2;
    t = p[1] + *(u16 *)(a2 + 2);
    *(s16 *)((s32)sp10 + 0x6) = t;
    *(s16 *)(a1 + 0x100) = t;
    *(s16 *)((s32)sp10 + 0xA) = p[2] + *(u16 *)(a2 + 4);
    func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10);
    rv = sp20;
    *a0 = rv;
    rv = (s32)a0;
}
