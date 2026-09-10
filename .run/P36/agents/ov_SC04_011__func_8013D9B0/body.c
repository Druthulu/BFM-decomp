void func_8013D9B0(int param_1)
{
    extern s16 *D_801EDABC;
    extern s32 D_801EDAD4;
    s16 rect[4];    /* LoadImage rect: x, y, w, h */
    u32 gte[6];     /* [0] fog colour (RGB), [1] source pixel (IRGB), [2] DPCL result (ORGB) */
    Cmd_8013D53C *p;
    u32 *fc;
    u16 cmd;
    s32 flag;
    s32 any;
    s32 n;
    s32 i;
    u16 *src;
    u16 *img;
    u16 *dst;
    s32 r, g, b;
    s32 tr, tg, tb;
    u32 pix;
    u32 out;
    u32 result;

    p = (Cmd_8013D53C *)D_801EDABC;
    if (p != 0) {
        cmd = p->cmd;
        gte[0] = (*(u32 **)&D_801EDAB4)[param_1];
        D_801EDAD4 = -1;
        any = 0;
        if (cmd != 0xff) {
            fc = gte;
            do {
                if (cmd == 9) {
                    i = 0;
                    rect[0] = p->pad4;
                    rect[1] = p->pad6;
                    rect[2] = p->w;
                    rect[3] = p->h;
                    n = p->w * p->h;
                    flag = 0;
                    src = p->data;
                    img = src + n;
                    dst = img;
                    if (n > 0) {
                        do {
                            gte[1] = *src;
                            pix = *dst;
                            r = pix & 0x1f;
                            g = pix & 0x3e0;
                            b = pix & 0x7c00;
                            gte_ldIR0z();
                            gte_ldrgb(fc);
                            gte_ldIRGB(&gte[1]);
                            gte_dpcl();
                            gte_stORGB(&gte[2]);
                            out = gte[2];
                            tr = out & 0x1f;
                            tg = out & 0x3e0;
                            tb = out & 0x7c00;
                            if (r != tr) {
                                if (r < tr) { flag = 1; r += 1; } else flag = 1;
                                if (tr < r) r -= 1;
                            }
                            if (g != tg) {
                                if (g < tg) { flag = 1; g += 0x20; } else flag = 1;
                                if (tg < g) g -= 0x20;
                            }
                            if (b != tb) {
                                if (b < tb) { flag = 1; b += 0x400; } else flag = 1;
                                if (tb < b) b -= 0x400;
                            }
                            result = r | g | b | (gte[1] & 0x8000);
                            if (result == 0 && gte[1] != 0) {
                                result = 0x8000;
                            }
                            *dst = result;
                            dst++;
                            i++;
                            src++;
                        } while (i < n);
                    }
                    if (flag != 0) {
                        ((void (*)(s16 *, u16 *))func_800599B8)(rect, img);
                    }
                    any |= flag;
                }
                p++;
                cmd = p->cmd;
            } while (cmd != 0xff);
        }
        D_801EDACC = any;
    }
}
