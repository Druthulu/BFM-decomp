void func_801842E0(void) {
    s32 t;
    s32 a0;
    s32 v0;
    s32 a1;
    s32 a1p;

    t = D_800B99DA;
    if (t != D_8018EF88) {
        a0 = (s16)D_80126B62;
        D_8018EF88 = t;

        if (a0 >= -0x7FF) {
            t = D_8018EF84;
        } else if (a0 < -0xC00) {
            t = D_8018EF84;
        } else {
            SV3_8012CC88 sp10;
            SV3_8012CC88 sp18;

            sp10.vx = D_80126B5E;
            sp10.vy = 0;
            sp10.vz = D_80126B66;
            sp18.vx = 0x11;
            sp18.vz = -0x3AA;
            sp18.vy = 0;

            t = func_800132BC((s32)&sp10, (s32)&sp18);
        }

        a0 = D_8018EF84;
        if (t >= a0) {
            func_8002D4C8(4, 0x5E5);
        } else {
            t = a0 - t;
            t -= 0x10000;

            if (t >= 0) {
                v0 = t << 7;
            } else {
                t = -t;
                v0 = t << 7;
            }
            v0 = v0 - t;
            t = v0 / a0;

            if (t <= 0) {
                t = 0;
            } else if (t >= 0x80) {
                t = 0x7F;
            }

            if (D_801270C8 != 0) {
                a1 = (u32)t >> 31;
                v0 = t + a1;
                t = v0 >> 1;
            }

            a0 = 0x5E5;
            a1p = t | 0x1000;
            a1p = (u16)a1p;
            func_8002D4C8(a0, a1p);
        }
    }
}
