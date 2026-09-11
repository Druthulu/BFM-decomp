s32 func_8017DD70(void) {

    extern u32 D_801A3458;
    extern u16 D_8011511A;
    extern u16 D_80115120;
    extern u16 D_80115122;
    extern u8  D_80115138[];
    extern u8  D_80115140[];
    extern u8  D_80115142;
    s32 flags;
    s32 val;
    u16 *p11a;
    register s32 c __asm__("$19");  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B tus8)
    s16 ret;
    s32 changed;
    u8 *pb;
    u8 *pe;
    s32 d;
    s32 nz;
    s32 c3;
    s32 off;

    changed = 0;
    flags = func_80014ED4(0);
    if ((flags & 0xFFFF) != 0) {
        D_801A3458 = 0;
    }
    val = func_80015018(0);
    p11a = &D_8011511A;
    ret = func_8014168C(*(s16 *)p11a);
    c = D_80115138[*p11a];

    if ((flags & 0x40) != 0) {
        ret = func_8017EC68(c, ret);
        nz = ret != 0;
        return ret & -nz;
    }

    if ((flags & 0x10) != 0) {
        __asm__ ("" : "=r"(c3) : "0"(c));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus8)
        if (c3 < 6) {
            if (c3 != 1) {
                return -1;
            }
        } else {
            func_8002D4C8(0x473, 0);
            *p11a = *p11a - 1;
        }
        return 0;
    }

    off = (s32)(*p11a) * 2;
    {
        u8 *base1 = (u8 *)p11a + 0x2E;
        pb = base1 + off;
    }
    {
        u8 *base2 = (u8 *)p11a + 0x3E;
        pe = base2 + off;
    }

    if ((val & 0xFFFF) != 0) {
        if ((val & 0xFFFF) == D_80115120) {
            D_80115122 = D_80115122 - 1;
            if (D_80115122 == 0) {
                flags = val & 0xF000;
                D_80115122 = 3;
            }
        } else {
            D_80115120 = val;
            D_80115122 = 8;
        }
    } else {
        D_80115120 = 0;
        D_80115122 = 0xC;
    }

    if ((flags & 0x1000) != 0) {
        u8 b2 = *pb;
        *pb = b2 - 1;
        changed = 1;
        if ((u8)(b2 - 1) > 0x7F) {
            if (c < 6) {
                *pb = *pe - 1;
            } else {
                *pb = 0;
                changed = 0;
            }
        }
    }

    if ((flags & 0x4000) != 0) {
        u8 b2 = *pb;
        u8 b4 = b2 + 1;
        *pb = b4;
        changed = 1;
        if (*pe <= b4) {
            if (c < 6) {
                *pb = 0;
            } else {
                *pb = b2;
                changed = 0;
            }
        }
    }

    {
        u8 b2 = *pb;
        s32 result;
        d = (s16)((s8)b2 - (s8)D_80115140[D_8011511A]);
        if (d >= 6) {
            D_80115140[D_8011511A] = b2 - 5;
            result = changed;
        } else {
            if (d < 0) {
                D_80115140[D_8011511A] = b2;
            }
            result = changed;
        }

        if (result) {
            func_8002D4C8(0x45A, 0);
            if (D_8011511A != 1) {
                return 0;
            }
            __asm__ ("" : "=r"(c3) : "0"(c));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus8)
            if (c3 == 9) {
                D_80115142 = 0;
            }
            func_8017D890();
        }
    }

    return 0;
}
