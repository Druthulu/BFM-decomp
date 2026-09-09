/* func_8017A4AC — shared body (overlay slot 0x80128158, h_exact 2a8590dc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017A4AC(void) {
    u16 sp18[4];
    u16 sp20[4];
    u16 sp28[4];
    u16 sp30[4];
    struct S126B58 *w = &(*(struct S126B58 *)&D_80126B58);
    s16 cmd;

    if (D_8018F908 == D_8018F90C) {
        if (func_80174754() != 0) {
            D_8018F910 = 0;
        } else {
            D_8018F910 = 1;
        }
        return;
    }
    D_8018F910 = 1;
    if (func_80174754() == 0) {
        return;
    }
    cmd = D_8018F508[D_8018F908];
    D_8018F908 = (D_8018F908 + 1) & 0x1FF;
    switch (cmd) {
    case 0:
        func_80172738();
        return;
    case 1:
        sp18[0] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp18[1] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp18[2] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172780)(sp18);
        return;
    case 28:
        sp18[0] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp18[1] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp18[2] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp18[3] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172894)(sp18);
        return;
    case 2:
        { s16 arg = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        ((void (*)(s16))func_801729B0)(arg);
        return; }
    case 3:
        { s16 arg = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        func_80172B14(arg);
        return; }
    case 4:
        { s16 arg = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        { s32 t = w->unk20->unk12 + arg;
        func_80172B14(t & 0xFFF); }
        return; }
    case 5:
        sp18[0] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp18[1] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp18[2] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        func_80172C50(sp18);
        return;
    case 6:
        { s16 arg = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        ((void (*)(s16))func_80172D68)(arg);
        return; }
    case 7: func_80172E94(); return;
    case 8: func_80172ED4(); return;
    case 27: ((void (*)())D_8018F954)(); return;
    case 9: func_80172EFC(); return;
    case 10: func_80172F24(); return;
    case 11: func_80173174(); return;
    case 12: func_80172F4C(); return;
    case 33: func_80172F9C(); return;
    case 34: func_80172FEC(); return;
    case 13: func_801745DC(); return;
    case 14:
    case 15: func_8017329C(); return;
    case 16: func_8017334C(); return;
    case 17: func_801733A4(); return;
    case 18:
        { s16 arg = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        func_801738DC(arg);
        return; }
    case 19: {
        s16 a, b;
        s32 ea, eb;
        a = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF; ea = a;
        b = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF; eb = b;
        func_801736B0(ea, eb);
        return;
    }
    case 20:
        { s16 arg = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        ((void (*)(s16))func_801734BC)(arg);
        return; }
    case 23:
        sp20[0] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp20[1] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp20[2] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        { s16 arg = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        ((void (*)(s16, u16 *))func_80173460)(arg, sp20);
        return; }
    case 29:
        sp28[0] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp28[1] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp28[2] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        { s16 arg = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        func_801733FC(arg, sp28);
        return; }
    case 32:
        sp30[0] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp30[1] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp30[2] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        sp30[3] = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172310)(sp30);
        return;
    case 25: func_8017452C(); return;
    case 30: func_80174584(); return;
    case 26: func_8017427C(); return;
    case 24: func_80174438(D_8018F950); return;
    case 21:
        ((void (*)(s32, s32, s32, s32, void *, s32))func_80173A28)((*(struct S734 * *)&D_8018F92C)->unk0, (*(struct S734 * *)&D_8018F92C)->unk4, (*(struct S734 * *)&D_8018F92C)->unk8,
                      (*(struct S734 * *)&D_8018F92C)->unkC, (*(struct S734 * *)&D_8018F92C)->unk10, (*(struct S734 * *)&D_8018F92C)->unk18);
        return;
    case 22:
        (*(struct S734 * *)&D_8018F92C)->unk1C((*(struct S734 * *)&D_8018F92C)->unk4, (*(struct S734 * *)&D_8018F92C)->unk10, (*(struct S734 * *)&D_8018F92C)->unk18);
        return;
    case 31:
        { s16 arg = D_8018F508[D_8018F908]; D_8018F908 = (D_8018F908 + 1) & 0x1FF;
        func_801737B8(arg);
        return; }
    }
}
