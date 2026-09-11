void func_801842E0(void) {
    s32 t;
    s32 y;

    t = D_800B99DA;
    if (t != D_8018EF88) {
        y = (s16)D_80126B62;
        D_8018EF88 = t;

        if (y >= -0x7FF) {
            t = D_8018EF84;
        } else if (y < -0xC00) {
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

        if (t >= D_8018EF84) {
            func_8002D4C8(4, 0x5E5);
        } else {
            t = D_8018EF84 - t - 0x10000;
            if (t < 0) {
                t = -t;
            }
            t = t * 127 / D_8018EF84;

            if (t <= 0) {
                t = 0;
            } else if (t >= 0x80) {
                t = 0x7F;
            }

            if (D_801270C8 != 0) {
                t /= 2;
            }

            func_8002D4C8(0x5E5, (u16)(t | 0x1000));
        }
    }
}
