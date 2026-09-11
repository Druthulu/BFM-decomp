void func_8017E9CC(s32 arg0) {
    s32 v0;
    register s32 flag __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus10)

    func_8017EEFC(arg0, 0xD, 0, &D_80195614);
    flag = D_8019F708;
    *(s32 *)(arg0 + 0x1C) = 0x11;

    if (flag == 1) {
        extern u16 D_80126B5E;
        extern u16 D_80126B66;

        v0 = ((s16)D_80126B5E < 1) ? 2 : 0;
        if ((s16)D_80126B66 < 0x218) {
            v0 = v0 + 1;
        }
        D_8019F7B0 = (s16)v0;
        func_8012E8E0(arg0, (s32)(D_80188B74 + (v0 << 3)));
    } else {
        v0 = D_8019F7B0 * 3 + rand() % 3;
        v0 = D_80188B94[v0];
        func_8012E8E0(arg0, (s32)(D_80188B74 + (v0 << 3)));
    }
    func_8012B2CC(arg0);
    func_8017ECE0(arg0);
    func_8002D4C8(0xA94, 0);
}
