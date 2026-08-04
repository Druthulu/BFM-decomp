extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012C1B8(void);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 rand(void);

extern u8 D_801B1BC4[];
extern u8 D_801B2FF4[];
extern u8 D_801B1C98[];
extern u8 D_801B1C64[];
extern u8 D_801B9898[];
extern u8 D_801B1BF8[];
extern u8 D_801B1C04[];
extern u8 D_801B1C0C[];
extern u8 D_801B1C1C[];
extern u16 D_801B1C20;
extern u8 D_801B1C24[];
extern u8 D_801B1C30[];
extern u8 D_801B1C38[];
extern u8 D_801B1C5C[];
extern u16 D_801B1C60;
extern u8 D_801B1C48[];
extern u8 D_801B1C54[];
extern u8 D_801B98D9;
extern u8 D_801B98DA;
extern u8 D_801B98DC;

void func_80181CE4(void *a0v)
{
    s32 e;
    s32 r;
    s32 o;
    s32 cc;
    s32 sv;
    u8 *p;
    u8 *q;

    e = (s32)a0v;

    switch (*(s16 *)(e + 0x70)) {
    case 0:
        if (func_8012C354(e, (s32)D_801B1BC4) == 0) {
            return;
        }
        *(u8 *)(e + 0xC0) = 1;
        *(s32 *)(e + 0xB4) = -1;
        *(s32 *)(e + 0xBC) = (s32)D_801B1C98;
        func_8012A828(e, D_801B2FF4);
        *(s16 *)(e + 0x2) = 1;
        *(s16 *)(e + 0x34) = 1;
        func_8012B23C(e);
        func_8012B1B4(e, (s32)D_801B1C64);
        *(s32 *)(e + 0xCC) = (s32)(D_801B9898 + *(s16 *)(e + 0xFC) * 8);
        o = func_8012C658(0x1EA, 1, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        return;

    case 1:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801B1BF8);
        func_8012A828(e, D_801B1C04);
        *(s16 *)(e + 0x2) = 2;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801B1C0C | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801B1C1C;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801B1C20;
        cc = *(s32 *)(*(s32 *)(e + 0x64) + 0xCC);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) | 0x80;
        *(s32 *)(*(s32 *)(e + 0x20) + 0x80) = cc;
        *(s32 *)(e + 0xCC) = cc;
        o = func_8012C658(0x1EA, 2, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        return;

    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801B1C24);
        func_8012A828(e, D_801B1C30);
        *(s16 *)(e + 0x2) = 0xF;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801B1C38 | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801B1C5C;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801B1C60;
        return;

    case 7:
        if (func_8012C354(e, (s32)D_801B1BC4) == 0) {
            return;
        }
        p = &D_801B98D9;
        q = p - 1;
        D_801B98DA = 0xFF;
        *q = 0xFF;
        *p = 0;
        D_801B98DA = 0;
        D_801B98DC = 0;
        func_800233CC(q, 0x20);
        *(u8 *)(e + 0xC0) = 1;
        *(s32 *)(e + 0xB4) = -1;
        *(s32 *)(e + 0xBC) = (s32)D_801B1C98;
        func_8012A828(e, D_801B2FF4);
        *(s16 *)(e + 0x2) = 8;
        *(s16 *)(e + 0x34) = 0xB;
        func_8012B23C(e);
        sv = *(s16 *)(e + 0xFC);
        *(s16 *)(e + 0xFC) = 0;
        *(s32 *)(e + 0xCC) = (s32)(D_801B9898 + sv * 8);
        o = func_8012C658(0x1EA, 8, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        return;

    case 8:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801B1BF8);
        func_8012A828(e, D_801B1C04);
        *(s16 *)(e + 0x2) = 2;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801B1C0C | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801B1C1C;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801B1C20;
        cc = *(s32 *)(*(s32 *)(e + 0x64) + 0xCC);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) | 0x80;
        *(s32 *)(*(s32 *)(e + 0x20) + 0x80) = cc;
        *(s32 *)(e + 0xCC) = cc;
        o = func_8012C658(0x1EA, 9, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801B1C24);
        func_8012A828(e, D_801B1C30);
        *(s16 *)(e + 0x2) = 0xF;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801B1C38 | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801B1C5C;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801B1C60;
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 14:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801B1C48);
        func_8012A828(e, D_801B1C54);
        *(s16 *)(e + 0x2) = 0xC;
        *(u16 *)(*(s32 *)(e + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(*(s32 *)(e + 0x64) + 0x20) + 0x10);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(e + 0x64) + 0x20) + 0x12);
        *(s32 *)(e + 0x14) = func_8004787C(*(s16 *)(*(s32 *)(e + 0x20) + 0x10)) << 9;
        {
            s32 t1 = func_8004787C(*(s16 *)(*(s32 *)(e + 0x20) + 0x12));
            *(s32 *)(e + 0x10) = -((t1 * func_80047948(*(s16 *)(*(s32 *)(e + 0x20) + 0x10))) >> 3);
        }
        {
            s32 t2 = func_80047948(*(s16 *)(*(s32 *)(e + 0x20) + 0x12));
            *(s32 *)(e + 0x18) = -((t2 * func_80047948(*(s16 *)(*(s32 *)(e + 0x20) + 0x10))) >> 3);
        }
        *(s32 *)(e + 0x10) = (*(s32 *)(e + 0x10) * 2) / 3;
        *(s32 *)(e + 0x1C) = 0x12C;
        *(s32 *)(e + 0x14) = (*(s32 *)(e + 0x14) * 2) / 3;
        *(s32 *)(e + 0x18) = (*(s32 *)(e + 0x18) * 2) / 3;
        return;

    case 15:
        if (func_8012C354(e, (s32)D_801B1BC4) == 0) {
            return;
        }
        *(u8 *)(e + 0xC0) = 1;
        *(s32 *)(e + 0xB4) = -1;
        *(s32 *)(e + 0xBC) = (s32)D_801B1C98;
        func_8012A828(e, D_801B2FF4);
        *(s16 *)(e + 0x2) = 0xD;
        *(s16 *)(e + 0x34) = 0xD;
        func_8012B23C(e);
        *(s32 *)(e + 0xCC) = (s32)(D_801B9898 + *(s16 *)(e + 0xFC) * 8);
        o = func_8012C658(0x1EA, 0x11, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
            *(s32 *)(e + 0x6C) = o;
        }
        *(s16 *)(e + 0xFC) = 0xA;
        return;

    case 16:
    case 24:
        *(s16 *)(e + 0x2) = 0xE;
        *(s32 *)(e + 0x1C) = 6;
        return;

    case 17:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801B1BF8);
        func_8012A828(e, D_801B1C04);
        *(s16 *)(e + 0x2) = 0x11;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801B1C0C | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801B1C1C;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801B1C20;
        cc = *(s32 *)(*(s32 *)(e + 0x64) + 0xCC);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) | 0x80;
        *(s32 *)(*(s32 *)(e + 0x20) + 0x80) = cc;
        *(s32 *)(e + 0xCC) = cc;
        o = func_8012C658(0x1EA, 0x12, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
            *(s32 *)(e + 0x6C) = o;
        }
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801B1C24);
        func_8012A828(e, D_801B1C30);
        *(s16 *)(e + 0x2) = 0x10;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801B1C38 | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801B1C5C;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801B1C60;
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 25:
        *(s16 *)(e + 0x2) = 0x13;
        return;
    }
}
