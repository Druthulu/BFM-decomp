void func_80188A30(s32 a0) {
    extern u16 D_80194814;
    extern u16 D_80194816;
    extern u16 D_801F161E;
    extern s16 D_80126B98;
    s16 in[3];
    s16 out[3];

    in[1] = 0;
    in[0] = 0;
    out[1] = 0;
    out[0] = 0;
    in[2] = D_80194814;
    out[2] = D_80194816;
    if (func_8012DEB8((s32)a0, (s32)in, (s32)out) != 0) {
        D_80126B98 = 0x18;
        if (*(s16 *)((s32)a0 + 0x106) == 0) {
            u16 cnt = D_801F161E;
            *(s16 *)((s32)a0 + 0x106) = 1;
            D_801F161E = cnt + 1;
        }
    }
}
