/* func_80165140 — shared body (overlay slot 0x80128158, h_exact 2718b2e5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80165140(s32 param_1) {
    extern Slot_80165140 D_8018E960[8];

    int i;
    Slot_80165140 *p;
    for (i = 0; i < 8; i++) {
        p = &D_8018E960[i];
        if (p->used == 0) {
            p->used = 8;
            p->a = *(B8_80165140 *)(((u8 *)param_1) + 0x2c);
            p->b = *(B4_80165140 *)(((u8 *)param_1) + 0x50);
            return;
        }
    }
}
