/* func_801412A8 — shared body (overlay slot 0x80128158, h_exact 280fa04f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
Prim_1412A8 *aF801412A8(Prim_1412A8 *out, int a1, int a2, int a3, u16 a4, u16 a5) __asm__("func_801412A8");
Prim_1412A8 *aF801412A8(Prim_1412A8 *out, int a1, int a2, int a3, u16 a4, u16 a5) {
    extern Env_1412A8 D_800AE7BC[];
    extern short D_800B9A02;
    extern u16 D_80115116;
    Prim_1412A8 *p = out;
    int y = a5;
    int color = 0xF800F8;
    int val;
    if ((short)a1) {
        val = 0x5E;
        if (D_80115116 & 1) { color = 0xF89C00; }
    } else if ((short)a2) {
        val = (short)a3 * 0x5E / (short)a2;
    } else {
        val = 0x5E;
        color = 0xF89C00;
    }
    p->tag = 0x03000000;
    p->w1 = color | 0x60000000;
    p->w2 = a4 | (((short)y + 0xA) << 16);
    p->w3 = val | 0x20000;
    addPrim_1412A8(&OT_1412A8[2], p);
    p++;
    p->w1 = 0x60080808;
    p->tag = 0x03000000;
    p->w2 = a4 | (((short)y + 0xA) << 16);
    p->w3 = 0x2005E;
    addPrim_1412A8(&OT_1412A8[2], p);
    p++;
    p->w1 = 0x60FFFFFF;
    p->tag = 0x03000000;
    p->w2 = (((short)y + 9) << 16) | (u16)(a4 - 1);
    p->w3 = 0x20060;
    addPrim_1412A8(&OT_1412A8[2], p);
    p++;
    p->tag = 0x03000000;
    p->w1 = 0x60E0C0A0;
    p->w2 = (((short)y + 0xB) << 16) | (u16)(a4 - 1);
    p->w3 = 0x20060;
    addPrim_1412A8(&OT_1412A8[2], p);
    return p + 1;
}
