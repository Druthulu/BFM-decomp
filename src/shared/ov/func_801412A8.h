/* guess_DrawGaugeBar — shared body (overlay slot 0x80128158, h_exact 280fa04f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_DrawGaugeBar: adds four TILE prims to the ordering table: a bar filled a3 / a2 of 0x5E wide at (a4, a5 + 10) on a dark back, with two edge lines
 * Confidence medium, code inference: 4 TILE (0x60) prims at OT[2]: fill w = a3*0x5E/a2 (full, blinking colour when a1 or a2 == 0), back 0x5E, edges 0x60 at y+9/y+0xB
 * Names ledger: config/names.tsv guess_DrawGaugeBar */
Prim_1412A8 * guess_DrawGaugeBar(out, a1, a2, a3, a4, a5)
    Prim_1412A8 *out;
    int a1;
    int a2;
    int a3;
    u16 a4;
    u16 a5;
{
    extern Env_1412A8 guess_g_FrontOrderingTablesOrg[]; // Names ledger: config/names.tsv guess_g_FrontOrderingTablesOrg
    extern short guess_g_DoubleBufferIndex; // Names ledger: config/names.tsv guess_g_DoubleBufferIndex
    extern u16 guess_g_MenuFrameCounter; // Names ledger: config/names.tsv guess_g_MenuFrameCounter
    Prim_1412A8 *p = out;
    int y = a5;
    int color = 0xF800F8;
    int val;
    if ((short)a1) {
        val = 0x5E;
        if (guess_g_MenuFrameCounter & 1) { color = 0xF89C00; }
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
