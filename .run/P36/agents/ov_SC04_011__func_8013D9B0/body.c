void func_8013D9B0(int param_1)
{

    extern s16 *D_801EDABC;
    extern s32 D_801EDAD4;
    s16 rect[4];
    u8 buf[0x18];
    Cmd_8013D53C *p;
    u16 cmd;
    s32 flag;
    s32 any;
    s32 n;
    s32 i;
    u16 *src;
    u16 *img;
    u16 *dst;
    u32 r, g, b;
    u32 tr, tg, tb;
    u32 result;
    u32 pix;
    u32 out;

    p = (Cmd_8013D53C *)D_801EDABC;
    if (p != 0) {
        cmd = p->cmd;
        *(u32 *)(buf + 0) = (*(u32 * *)&D_801EDAB4)[param_1];
        D_801EDAD4 = -1;
        any = 0;
        while (cmd != 0xff) {
            i = 0;
            if (cmd == 9) {
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
                        *(u32 *)(buf + 4) = *src;
                        pix = *dst;
                        r = pix & 0x1f;
                        g = pix & 0x3e0;
                        b = pix & 0x7c00;
                        gte_ldIR0z();
                        gte_ldrgb(buf + 0);
                        gte_ldIRGB(buf + 4);
                        gte_dpcl();
                        gte_stORGB(buf + 8);
                        out = *(u32 *)(buf + 8);
                        tr = out & 0x1f;
                        tg = out & 0x3e0;
                        tb = out & 0x7c00;
                        if (r != tr) {
                            flag = 1;
                            if ((s32)r < (s32)tr) r = r + 1;
                            if ((s32)tr < (s32)r) r = r - 1;
                        }
                        if (g != tg) {
                            flag = 1;
                            if ((s32)g < (s32)tg) g = g + 0x20;
                            if ((s32)tg < (s32)g) g = g - 0x20;
                        }
                        if (b != tb) {
                            flag = 1;
                            if ((s32)b < (s32)tb) b = b + 0x400;
                            if ((s32)tb < (s32)b) b = b - 0x400;
                        }
                        result = r | g | b | (*(u32 *)(buf + 4) & 0x8000);
                        if (result == 0 && *(u32 *)(buf + 4) != 0) {
                            result = 0x8000;
                        }
                        *dst = result;
                        dst++;
                        i++;
                        src++;
                    } while (i < n);
                }
                if (flag != 0) {
                    ((void (*)(void *, u16 *))func_800599B8)(rect, img);
                }
                any |= flag;
            }
            p++;
            cmd = p->cmd;
        }
        D_801EDACC = any;
    }
}
