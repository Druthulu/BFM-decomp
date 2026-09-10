/* func_8013D8FC — shared body (overlay slot 0x80128158, h_exact 392f2627). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013D8FC(void)
{

    extern s16 *D_8018E774;
    Cmd_8013D53C *p;
    s16 buf[4];

    p = (Cmd_8013D53C *)D_8018E774;
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
