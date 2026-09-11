void func_801651B8(void * param_1)
{
    extern s32 D_80184398;
    Slot_80165140 *tbl = (Slot_80165140 *)&D_80184398;
    Slot_80165140 *p;
    int i;

    func_80165240(param_1, (u8 *)param_1 + 0x2c, (u8 *)param_1 + 0x50);
    for (i = 0; i < 8; i++) {
        p = &tbl[i];
        if (p->used != 0) {
            func_80165240(param_1, p, &p->b);
            p->used--;
        }
    }
}
