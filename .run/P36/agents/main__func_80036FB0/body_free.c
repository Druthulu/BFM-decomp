void func_80036FB0(s32 arg0, s32 arg1) {
    extern s32 D_8006AEE8;
    extern s32 D_80078F10;
    f64 hole;
    s32 count;
    s32 i;
    s32 *p;

    if (D_8006AEE8 > 0) {
        i = 0;
        count = D_8006AEE8;
        p = &D_80078F10;
        do {
            if (*p == arg0) {
                *p = arg1;
            }
            p++;
            i++;
        } while (i < count);
    }
}
