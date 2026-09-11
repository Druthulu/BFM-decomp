void func_80181D98(void *a0) {
    s32 *p;
    SpotDef_8018A278 *t;
    s32 e;
    s32 s;
    u16 v;

    p = &D_801270CC;
    switch (*p) {
    case 0:
        *p = 1;
        D_801C7548 = 0;
        D_801C754C = 1;
        break;
    case 1:
        s = D_80126D50;
        *p = 1;
        if (s == 0) {
            if (D_801C7548 == 0x34) {
                func_80180174();
            }
            D_801C7548++;
            if (D_801C7548 >= 0x3C && (s16)D_80126B66 >= -0x500 &&
                (D_80126B9C & 0x8000000) != 0) {
                D_801C7548 = 0;
                func_8012C588(0x36, 0);
            }
        }
        break;
    case 2:
        func_80181CA4();
        p += 15;
        t = D_8018A278;
        if (D_80127188 == 4) {
            while ((s16)t->dist != -1) {
                if (*p == 0 && D_801270D0 >= (s16)t->dist) {
                    e = func_8012C658(0x2C, t->kind, 0);
                    if (e != 0) {
                        v = t->dist;
                        *(s32 *)(e + 0xCC) = (s32)p;
                        *(s16 *)(e + 0xFC) = v + 0x500;
                    }
                    *p = 1;
                }
                t++;
                p++;
            }
        }
        break;
    }
}
