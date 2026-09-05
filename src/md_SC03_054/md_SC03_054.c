#include "common.h"

extern s32 func_80029504(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80029514(s32 a0);
extern void func_80029124(s32 a0, s32 a1);
extern s32 func_80029178(s32 a0);
extern s32 func_8018766C(s32 a0, s32 a1);
extern void func_800D0F4C(s32 a0);

extern s16 D_801F1480;
extern s16 D_801F1482;
extern s32 D_801F10C0;
extern s32 D_801F10E0;
extern s32 D_801F10F8;
extern s32 D_801F1118;
extern s32 D_801F1138;
extern s32 D_801F1158;

void func_801EF558(void *param_1) {
    s16 step;
    s32 v0;

    step = 6;
    *(s16 *)((s32)param_1 + 0x2) = step;
    D_801F1480 = 0;
    D_801F1482 = 0;
    v0 = func_80029504();
    if (v0 < 0x28) {
        func_8002D4C8(0x12, 0);
        func_80178CBC((s32)param_1, (s32)&D_801F10C0);
        func_80029514(0x28);
        func_80029124(0xE3, 1);
        *(s16 *)((s32)param_1 + 0x34) = 0;
    } else if (v0 < 0x32) {
        func_8002D4C8(0x12, 0);
        func_80178CBC((s32)param_1, (s32)&D_801F10E0);
        *(s16 *)((s32)param_1 + 0x34) = 1;
    } else if ((u8)func_80029178(0xE4) != 0) {
        func_8002D4C8(0x12, 0);
        func_80178CBC((s32)param_1, (s32)&D_801F10F8);
        *(s16 *)((s32)param_1 + 0x34) = 5;
    } else if (v0 < 0x3C) {
        func_8002D4C8(0x12, 0);
        func_80178CBC((s32)param_1, (s32)&D_801F1118);
        *(s16 *)((s32)param_1 + 0x34) = 2;
    } else if (v0 < 0x46) {
        if (func_8018766C(0, 5) != 0) {
            func_8002D4C8(0x12, 0);
            func_80178CBC((s32)param_1, (s32)&D_801F1158);
            func_800D0F4C(0x4D);
            *(s16 *)((s32)param_1 + 0x34) = step;
        } else {
            func_8002D4C8(0x12, 0);
            func_80178CBC((s32)param_1, (s32)&D_801F1138);
            *(s16 *)((s32)param_1 + 0x34) = 2;
        }
    }
}


INCLUDE_RODATA("asm/md_SC03_054/nonmatchings/md_SC03_054", D_801EF468);

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


extern void func_8012C588(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 D_801EB318;
extern s32 D_801F1468;

void func_801F0048(s32 a0) {
    s32 v1;
    s32 v0;

    func_8012C588(0x8D, a0);

    v1 = *(s32 *)(a0 + 0x20);
    v0 = (s32)&D_801EB318;
    *(s32 *)(v1 + 0x24) = v0;

    func_8012A828(a0, (s32)&D_801F1468);
}




extern s32 func_8012E544(s32 a0);

void func_801F0098(void) {
    s32 v0 = func_8012E544(0x11A);
    if (v0 != 0) {
        *(s16*)(v0 + 0xfc) = 1;
    }
}


extern s32 func_8012E544(s32 a0);
extern void func_800291A0(s32 a0, s32 a1);

void func_801F00C8(void) {
    s32 v0 = func_8012E544(0x11A);
    if (v0 != 0) {
        *(s16*)(v0 + 0xFC) = 2;
        func_800291A0(0xCC, 0x1);
    }
}




extern s32 func_8012E544(s32 a0);

void func_801F0104(void) {
    s32 v0 = func_8012E544(0x11A);
    if (v0 != 0) {
        *(s16*)(v0 + 0xfc) = 3;
    }
}



extern s16 D_801F1480;
void func_801F0134(void) {
    D_801F1480 = 1;
}

