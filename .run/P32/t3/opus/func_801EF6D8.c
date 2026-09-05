extern s32 func_801789AC(s32 a0);
extern s32 func_80178970(s32 a0);
extern void func_80178D18(s32 a0);
extern void func_80186890(s32 a0);
extern void func_8012C218(s32 a0);
extern s32 func_800D0F8C(s32 a0);
extern s32 func_800D0CA0(s32 a0);
extern s32 func_800D0CE0(void);
extern s32 func_8001AAA0(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80029514(s32 a0);
extern void func_80029124(s32 a0, s32 a1);
extern void func_800D0F4C(s32 a0);

extern s16 D_801F1480;
extern s32 D_801F11D0;
extern s32 D_801F12A8;
extern s32 D_801F12C0;
extern s32 D_801F12E0;
extern s32 D_801F1300;
extern s32 D_801F1310;
extern s32 D_801F1338;
extern s32 D_801F13C8;
extern s32 D_801F13F8;

void func_801EF6D8(s32 a0) {
    s32 t0;
    s32 u0;
    s32 t1;
    s32 u1;
    s32 t3;
    s32 t4;
    s32 t3b;
    s16 *p;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (func_801789AC(a0)) {
            t0 = func_800D0F8C(0xD)    ? 0xD
              : func_800D0F8C(0xE)    ? 0xE
              : func_800D0F8C(0xF)    ? 0xF
              : func_800D0F8C(0x10)   ? 0x10
              : 0;
            u0 = func_800D0F8C(0x4C);
            if (t0) {
                if (u0) {
                    func_80178CBC(a0, (s32)&D_801F1300);
                    *(s16 *)(a0 + 0x34) = 3;
                } else {
                    func_80178CBC(a0, (s32)&D_801F12E0);
                    *(s16 *)(a0 + 0x34) = 2;
                }
            } else {
                if (u0) {
                    func_80178CBC(a0, (s32)&D_801F12C0);
                    *(s16 *)(a0 + 0x34) = 2;
                } else {
                    func_80178CBC(a0, (s32)&D_801F12A8);
                    *(s16 *)(a0 + 0x34) = 2;
                }
            }
        }
        break;
    case 1:
        if (func_801789AC(a0)) {
            t1 = func_800D0F8C(0xD)    ? 0xD
              : func_800D0F8C(0xE)    ? 0xE
              : func_800D0F8C(0xF)    ? 0xF
              : func_800D0F8C(0x10)   ? 0x10
              : 0;
            u1 = func_800D0F8C(0x4C);
            if (t1) {
                if (u1) {
                    func_80178CBC(a0, (s32)&D_801F1300);
                    *(s16 *)(a0 + 0x34) = 3;
                } else {
                    func_80178CBC(a0, (s32)&D_801F12E0);
                    *(s16 *)(a0 + 0x34) = 2;
                }
            } else {
                if (u1) {
                    func_80178CBC(a0, (s32)&D_801F12C0);
                    *(s16 *)(a0 + 0x34) = 2;
                } else {
                    func_80178CBC(a0, (s32)&D_801F12A8);
                    *(s16 *)(a0 + 0x34) = 2;
                }
            }
        }
        break;
    case 2:
        if (func_80178970(a0)) {
            func_80178D18(a0);
            func_8002D4C8(0x13, 0);
            func_80186890(a0);
        }
        break;
    case 3:
        t3 = func_801789AC(a0);
        if (t3) {
            if (t3 == 2) {
                func_80178CBC(a0, (s32)&D_801F1310);
                *(s16 *)(a0 + 0x34) = 2;
            } else {
                func_80178CBC(a0, (s32)&D_801F1338);
                *(s16 *)(a0 + 0x34) = 5;
                if (func_800D0F8C(0xD)) {
                    t3b = 0xD;
                } else if (func_800D0F8C(0xE)) {
                    t3b = 0xE;
                } else if (func_800D0F8C(0xF)) {
                    t3b = 0xF;
                } else if (func_800D0F8C(0x10)) {
                    t3b = 0x10;
                } else {
                    t3b = 0;
                }
                func_800D0F4C(t3b);
                func_800D0F4C(0x4C);
            }
        }
        break;
    case 4:
    case 5:
        t4 = func_801789AC(a0);
        if (t4) {
            if (t4 == 2) {
                func_80029514(0x32);
                func_80029124(0xE4, 1);
                func_80029124(0xE5, 0);
                func_80178CBC(a0, (s32)&D_801F13C8);
                *(s16 *)(a0 + 0x34) = 2;
            } else {
                func_80029514(0x32);
                func_80029124(0xE4, 0);
                func_80029124(0xE5, 1);
                func_80178CBC(a0, (s32)&D_801F13F8);
                *(s16 *)(a0 + 0x34) = 2;
            }
        }
        break;
    case 6:
        p = &D_801F1480;
        switch (D_801F1480) {
        case 0:
            break;
        case 1:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 2;
            func_8002D4C8(0x13, 0);
            break;
        case 2:
            if (++p[1] >= 0x1E) {
                if (func_8001AAA0(0x1B)) {
                    p[0] = 3;
                }
            }
            break;
        case 4:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 5;
            break;
        case 5:
            if (++p[1] >= 0x1E) {
                if (func_800D0CE0() == 1) {
                    p[0] = 6;
                }
            }
            break;
        case 6:
            break;
        }
        if (func_801789AC(a0)) {
            *(s16 *)(a0 + 0x34) = 7;
        }
        break;
    case 7:
        p = &D_801F1480;
        switch (D_801F1480) {
        case 0:
            break;
        case 1:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 2;
            func_8002D4C8(0x13, 0);
            break;
        case 2:
            if (++p[1] >= 0x1E) {
                if (func_8001AAA0(0x1B)) {
                    p[0] = 3;
                }
            }
            break;
        case 4:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 5;
            break;
        case 5:
            if (++p[1] >= 0x1E) {
                if (func_800D0CE0() == 1) {
                    p[0] = 6;
                }
            }
            break;
        case 6:
            break;
        }
        if (D_801F1480 == 3) {
            func_80178CBC(a0, (s32)&D_801F11D0);
            *(s16 *)(a0 + 0x34) = 8;
        }
        break;
    case 8:
        p = &D_801F1480;
        switch (D_801F1480) {
        case 0:
            break;
        case 1:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 2;
            func_8002D4C8(0x13, 0);
            break;
        case 2:
            if (++p[1] >= 0x1E) {
                if (func_8001AAA0(0x1B)) {
                    p[0] = 3;
                }
            }
            break;
        case 4:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 5;
            break;
        case 5:
            if (++p[1] >= 0x1E) {
                if (func_800D0CE0() == 1) {
                    p[0] = 6;
                }
            }
            break;
        case 6:
            break;
        }
        func_801789AC(a0);
        break;
    case 9:
        p = &D_801F1480;
        switch (D_801F1480) {
        case 0:
            break;
        case 1:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 2;
            func_8002D4C8(0x13, 0);
            break;
        case 2:
            if (++p[1] >= 0x1E) {
                if (func_8001AAA0(0x1B)) {
                    p[0] = 3;
                }
            }
            break;
        case 4:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 5;
            break;
        case 5:
            if (++p[1] >= 0x1E) {
                if (func_800D0CE0() == 1) {
                    p[0] = 6;
                }
            }
            break;
        case 6:
            break;
        }
        D_801F1480 = 4;
        *(s16 *)(a0 + 0x34) = 0xA;
        break;
    case 10:
        p = &D_801F1480;
        switch (D_801F1480) {
        case 0:
            break;
        case 1:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 2;
            func_8002D4C8(0x13, 0);
            break;
        case 2:
            if (++p[1] >= 0x1E) {
                if (func_8001AAA0(0x1B)) {
                    p[0] = 3;
                }
            }
            break;
        case 4:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 5;
            break;
        case 5:
            if (++p[1] >= 0x1E) {
                if (func_800D0CE0() == 1) {
                    p[0] = 6;
                }
            }
            break;
        case 6:
            break;
        }
        if (D_801F1480 == 6) {
            *(s16 *)(a0 + 0x34) = 0xB;
        }
        break;
    case 11:
        p = &D_801F1480;
        switch (D_801F1480) {
        case 0:
            break;
        case 1:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 2;
            func_8002D4C8(0x13, 0);
            break;
        case 2:
            if (++p[1] >= 0x1E) {
                if (func_8001AAA0(0x1B)) {
                    p[0] = 3;
                }
            }
            break;
        case 4:
            func_800D0CA0(1);
            p[1] = 0;
            p[0] = 5;
            break;
        case 5:
            if (++p[1] >= 0x1E) {
                if (func_800D0CE0() == 1) {
                    p[0] = 6;
                }
            }
            break;
        case 6:
            break;
        }
        if (func_80178970(a0)) {
            if (D_801F1480 == 6) {
                func_80178D18(a0);
                func_8002D4C8(0x13, 0);
                func_80029514(0x46);
                func_80029124(0xE7, 1);
                func_8012C218(*(s32 *)(a0 + 0xD4));
                func_8012C218(a0);
            }
        }
        break;
    }
}
