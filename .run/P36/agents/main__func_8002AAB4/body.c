s32 func_8002AAB4(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 avg;
    s32 i;
    s32 thr;

    a = func_8002A26C();
    b = func_8002A4B8();
    c = func_8002A728();
    d = func_8002A998();
    avg = (a + b + c + d) / 4;
    for (i = 0; (thr = D_800638A0[i * 2]) != 0; i++) {
        if (avg >= thr) {
            return D_800638A0[i * 2 + 1];
        }
    }
    return D_800638EC;
}
