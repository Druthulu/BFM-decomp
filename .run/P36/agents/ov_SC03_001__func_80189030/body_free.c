void func_80189030(void) {

    extern s16 D_801EEB10;
    extern s16 D_80115118;
    extern s16 D_80115126;
    extern s32 D_80115134;
    extern u8  D_80115138[];
    extern u8  D_80115140[];
    extern u8  D_80115148[];
    extern u8  D_80115158[];
    extern u16 D_8011515A;
    extern s32 D_801C1648[];
    extern s32 D_801C1808[];
    extern s32 D_801C181C[];
    extern s16 D_801C1830[];
    extern s32 D_801C1838[];
    extern u8  D_801C1662;
    extern u8  D_801C1664;
    extern u8  D_801C166E;
    extern u8  D_801C1670;
    extern u8  D_801C167A;
    extern u8  D_801C167C;
    extern u8  D_801C1686;
    extern u8  D_801C1688;
    extern s32 D_801F0CC0;
    extern s32 D_801F0CEC;
    extern s32 D_801F10B0;
    extern s32 D_801F1374;
    extern u8  D_801EF1F4[];
    extern s32 D_801EF23C[];
    extern s32 D_801EF254[];
    extern u16 D_801EF26C;
    extern u16 D_801EF274;
    extern u8  D_801EF290[];
    extern u8 *D_801EB574[];
    extern u8  D_801EB56C[];
    extern u8  D_801EB572;
    extern u8 *D_801EB58C;
    extern u16 D_800B99D8;
    extern u16 D_800B99DA;
    extern s32 D_80078E8C;
    extern s16 D_80078E92;
    extern u8  D_80078EBA;

    extern s32  func_80029504(void);
    extern s32  func_80029178(s32 arg);
    extern s32  func_800291B4(s32 arg);
    extern void func_80029124(s32, s32);
    extern void func_8002AC00(s32 a0);
    extern s32  func_80029FE4(void);
    extern s32  func_801F2690(void);
    extern void func_801898E4(void);

    u8 *base;
    s32 iVar5;
    short i;
    short count;
    short flagCount;
    short found;
    short cnt;
    short k;
    short j;
    u8 *p;
    u8 *rec;
    s32 *fld;
    s32 kind;
    s32 *dst;

    D_801EEB10 = 0;
    base = (u8 *)&D_80115118;
    *(s16 *)base = 0;
    D_801EF274 = 0;
    iVar5 = func_80029504();

    D_80115134 = D_801C1648[D_80115126];
    count = 4;
    if (D_80115126 != 3) {
        count = 3;
    }

    i = 0;
    while (i < 8) {
        if (i < count) {
            u8 *q = base + 0x40;
            D_80115138[i] = *(u16 *)(D_80115134 + i * 0x20);
            *(u16 *)(q + i * 2) = *(u16 *)(D_80115134 + i * 0x20 + 2);
        } else {
            *(u16 *)(D_80115158 + (i << 1)) = 0;
            D_80115138[i] = 0;
        }
        *(u16 *)(D_80115148 + (i << 1)) = 0;
        D_80115140[i] = 0;
        i = i + 1;
    }

    if (D_80115126 == 3) {
        if ((u8)func_80029178(0x11D) != 0) {
            func_8002AC00(0x23);
            if (((u8)func_80029178(0x1D) != 0) &&
                ((u8)func_80029178(0x1E) != 0) &&
                ((u8)func_80029178(0x1F) != 0) &&
                ((u8)func_80029178(0x20) != 0) &&
                ((u8)func_80029178(0x21) != 0) &&
                (((u8)func_80029178(0x1B) != 0) ||
                 ((u8)func_80029178(0x1C) != 0))) {
                func_8002AC00(0x29);
            }
            if (func_80029FE4() >= 0x1B) {
                func_8002AC00(0x2A);
            }
            i = 0;
            cnt = 0;
            while (i < 0x2A) {
                if (func_800291B4((s32)i + 0x63) & 0x40) {
                    cnt = cnt + 1;
                }
                i = i + 1;
            }
            if (cnt >= 0x2A) {
                func_8002AC00(0x2B);
            }
        }

        flagCount = 0;
        for (i = 0; i < 7; i++) {
            D_801EF290[i] = 0;
        }

        for (k = 0; k < 4; k++) {
            if (iVar5 < D_801C1830[k]) {
                break;
            }
        }
        k = k + 2;
        if ((u8)func_80029178(0x11D) != 0) {
            k = 6;
        }

        for (i = 0; i < k; i++) {
            found = 0;
            p = D_801EB574[i];
            for (j = 0; j < D_801EB56C[i]; j++) {
                if (func_800291B4(*p++ + 0x62) & 0x80) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                D_801EF290[flagCount++] = i;
            }
        }

        found = 0;
        p = D_801EB58C;
        for (j = 0; j < D_801EB572; j++) {
            if (func_800291B4(*p++ + 0x62) & 0x80) {
                found = 1;
                break;
            }
        }
        if (found) {
            D_801EF290[flagCount++] = 6;
        }
        D_8011515A = flagCount | 0x100;
    }

    for (i = 0; i < 6; i++) {
        D_801EF254[i] = 0;
    }

    if (D_80115126 == 4) {
        rec = (u8 *)func_801F2690();
        if (rec != 0) {
            s32 *tbl;
            s32 *tbl2;
            i = 0;
            tbl = D_801EF23C;
            tbl2 = tbl + 6;
            fld = (s32 *)(rec - 0x10);
            do {
                kind = fld[6];
                if ((u32)(kind - 10) < 2) {
                    *(s32 *)(kind * 4 + (s32)tbl) = (s32)rec;
                } else {
                    *(s32 *)(i++ * 4 + (s32)tbl2) = (s32)rec;
                }
                fld += 4;
                rec += 0x10;
            } while (fld[0] != 0);
        }
    }

    if (D_80115126 == 5) {
        rec = D_801EF1F4;
        for (i = 0; i < 6; i++) {
            s32 *pp = (s32 *)(rec + 4);
            switch (i) {
            case 0:
                pp[1] = 9;
                if (iVar5 < 0x258) {
                    pp[0] = (s32)&D_801F0CC0;
                } else {
                    pp[0] = (s32)&D_801F0CEC;
                }
                D_801EF254[0] = (s32)rec;
                break;
            case 1:
                pp[1] = 0xB;
                if (((u8)func_80029178(0x11A) != 0) &&
                    ((u32)D_80078E8C >= 0x32)) {
                    pp[0] = (s32)&D_801F1374;
                } else {
                    func_80029124(0x11A, 0);
                    pp[0] = (s32)&D_801F10B0;
                }
                D_801EF254[1] = (s32)rec;
                break;
            case 2:
                *(s32 *)((s32)pp + 4) = 3;
                pp[0] = D_801C1808[(u16)((u32)D_800B99D8 % 5)];
                D_801EF254[2] = (s32)rec;
                break;
            case 3:
                pp[1] = 0x19;
                for (k = 0; k < 4; k++) {
                    if (iVar5 < D_801C1830[k]) {
                        break;
                    }
                }
                {
                s32 v3 = D_801C1838[k];
                if (v3 != 0) {
                    pp[0] = v3;
                    D_801EF254[3] = (s32)rec;
                }
                }
                break;
            case 4:
                if (iVar5 < 0x3B6) {
                    *(s32 *)((s32)pp + 4) = 0xC;
                    pp[0] = D_801C181C[(u16)((u32)D_800B99DA % 5)];
                    D_801EF254[4] = (s32)rec;
                }
                break;
            }
            rec += 0x10;
        }
    }

    D_801EF26C = 0;
    if (D_80115126 == 0) {
        s32 t2;
        if (D_80078EBA == 4) {
            D_801EF26C = 0x14;
        }
        if (iVar5 < 0x258) {
            t2 = 6;
            D_801C1686 = t2;
            D_801C167A = t2;
            D_801C166E = t2;
            D_801C1662 = t2;
            t2 = 8;
        } else {
            t2 = 7;
            D_801C1686 = t2;
            D_801C167A = t2;
            D_801C166E = t2;
            D_801C1662 = t2;
            t2 = 0x6D;
        }
        D_801C1688 = t2;
        D_801C167C = t2;
        D_801C1670 = t2;
        D_801C1664 = t2;
    }

    if ((D_80115126 == 1) && (D_80078E92 >= 0x438)) {
        D_801EF26C = 3;
    }

    func_801898E4();
}
