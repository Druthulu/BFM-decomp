/* guess_OpenTextWindowCenteredAt — shared body (overlay slot 0x80128158, h_exact 7529ad8f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_OpenTextWindowCenteredAt: starts text a0 in record 0 of guess_g_TextBoxes (flags 0x6200) and centres the window on the point a1 when given
 * Confidence medium, xref chain: func_801377B4(a0, 0x6200, &guess_g_TextBoxes); +0x24 = a1[0..1]; func_80139BE0; +0x30 = x + 0x28 - (w + 0x28)/2, +0x32 = y - h/2
 * Names ledger: config/names.tsv guess_OpenTextWindowCenteredAt */
s32 aF801376E8(int a0, int a1) __asm__("guess_OpenTextWindowCenteredAt");
s32 aF801376E8(int a0, int a1)
{
    extern s32 guess_g_TextBoxes; // Names ledger: config/names.tsv guess_g_TextBoxes
    extern u8 D_801269FD;
    extern u16 D_80126A14[];
    extern s16 D_80126A1C;
    extern s16 D_80126A20;
    extern s16 D_80126A22;
    extern s16 D_80126A24;
    extern u16 D_80126A26;
    u16 *p = (u16 *)a1;
    s32 obj = (s32)&guess_g_TextBoxes;
    func_801377B4(a0, 0x6200, obj);
    D_80126A1C = 0x1C;
    D_801269FD = 0;
    if (p != 0) {
        D_80126A14[0] = p[0];
        D_80126A14[1] = p[1];
    }
    func_80139BE0(obj);
    D_80126A20 = (D_80126A14[0] + 0x28) - ((D_80126A24 + 0x28) >> 1);
    D_80126A22 = D_80126A14[1] - ((s16)D_80126A26 >> 1);
    return obj;
}
