/* guess_FadeOutColorPair — shared body (overlay slot 0x80128158, h_exact c24c1e19). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_FadeOutColorPair: lowers the two RGB triples a1 and a2 by 10 each (clamped at 0), stores them as bytes 0-2 and 4-6 of a3, returns non-zero until a2 is black
 * Confidence medium, xref chain: each s16 of a1[0..2], a2[0..2] -= 0xA, min 0; a3[0..2] = a1, a3[4..6] = a2; returns a2[0]|a2[1]|a2[2]
 * Names ledger: config/names.tsv guess_FadeOutColorPair */
s32 guess_FadeOutColorPair(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 v;
    *(u16 *)(a1 + 0x0) = *(u16 *)(a1 + 0x0) - 0xA;
    if ((s16)*(u16 *)(a1 + 0x0) < 0) {
        *(u16 *)(a1 + 0x0) = 0;
    }
    *(u16 *)(a1 + 0x2) = *(u16 *)(a1 + 0x2) - 0xA;
    if ((s16)*(u16 *)(a1 + 0x2) < 0) {
        *(u16 *)(a1 + 0x2) = 0;
    }
    *(u16 *)(a1 + 0x4) = *(u16 *)(a1 + 0x4) - 0xA;
    if ((s16)*(u16 *)(a1 + 0x4) < 0) {
        *(u16 *)(a1 + 0x4) = 0;
    }
    *(u16 *)(a2 + 0x0) = *(u16 *)(a2 + 0x0) - 0xA;
    if ((s16)*(u16 *)(a2 + 0x0) < 0) {
        *(u16 *)(a2 + 0x0) = 0;
    }
    *(u16 *)(a2 + 0x2) = *(u16 *)(a2 + 0x2) - 0xA;
    if ((s16)*(u16 *)(a2 + 0x2) < 0) {
        *(u16 *)(a2 + 0x2) = 0;
    }
    *(u16 *)(a2 + 0x4) = *(u16 *)(a2 + 0x4) - 0xA;
    if ((s16)*(u16 *)(a2 + 0x4) < 0) {
        *(u16 *)(a2 + 0x4) = 0;
    }
    *(u8 *)(a3 + 0x0) = *(u16 *)(a1 + 0x0);
    *(u8 *)(a3 + 0x1) = *(u16 *)(a1 + 0x2);
    *(u8 *)(a3 + 0x2) = *(u16 *)(a1 + 0x4);
    *(u8 *)(a3 + 0x4) = *(u16 *)(a2 + 0x0);
    *(u8 *)(a3 + 0x5) = *(u16 *)(a2 + 0x2);
    *(u8 *)(a3 + 0x6) = *(u16 *)(a2 + 0x4);
    v = *(u16 *)(a2 + 0x4) | (*(u16 *)(a2 + 0x0) | *(u16 *)(a2 + 0x2));
    return (s16)v;
}
