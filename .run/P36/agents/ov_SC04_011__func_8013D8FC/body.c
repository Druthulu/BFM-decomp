void func_8013D8FC(void)
{

    extern s16 *D_801EDABC;
    Cmd_8013D53C *p;
    s16 buf[4];

    p = (Cmd_8013D53C *)D_801EDABC;
    if (p != 0) {
        while (p->cmd != 0xff) {
            if (p->cmd == 9) {
                u16 *data = p->data + p->w;
                buf[0] = p->pad4;
                buf[1] = p->pad6;
                buf[2] = p->w;
                buf[3] = p->h;
                ((void (*)(s16 *, u16 *))func_800599B8)(buf, data);
            }
            p++;
        }
    }
}
