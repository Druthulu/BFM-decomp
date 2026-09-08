/* func_8014F24C — shared body (overlay slot 0x80128158, h_exact 9687d3e3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014F2E0(s32 a0, s16 *a1, s16 *a2);
s32 func_8014F24C(struct SubF24C *a0) {
    s16 g1[3];
    s16 g2[3];
    if (a0->f44 & 0x80000) {
        return 0;
    }
    if (a0->f1F8 & 0x4000000) {
        return 0;
    }
    g1[0] = a0->f88;
    g1[1] = a0->f8A - 0x10;
    g1[2] = a0->f8C;
    g2[0] = a0->f6;
    g2[1] = a0->fA - 0x10;
    g2[2] = a0->fE;
    func_8014F2E0((s32)a0, g1, g2);
}
