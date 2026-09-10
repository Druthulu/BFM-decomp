/* func_801651B8 — shared body (overlay slot 0x80128158, h_exact b905c751). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801651B8(void * param_1)
{
    Slot_80165140 *tbl = (Slot_80165140 *)&D_8018E960;
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
