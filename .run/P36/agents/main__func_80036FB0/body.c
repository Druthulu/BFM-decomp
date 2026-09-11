void func_80036FB0(s32 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < D_8006AEE8; i++) {
        if ((&D_80078F10)[i] == arg0) {
            (&D_80078F10)[i] = arg1;
        }
    }
}
