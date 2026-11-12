/* guess_IsDownHeld — shared body (overlay slot 0x80128158, h_exact 654c631e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_IsDownHeld: returns non-zero while down is held: D-pad down (0x4000 of the held word +0xAA) on a digital pad, left stick y above 0xC0 on an analog one
 * Confidence medium, xref chain: pad type +0xA9: 0x41 -> +0xAA & 0x4000; 0x53/0x73 -> (u16 +0xAE >> 8) >= 0xC1; 0 for other types
 * Names ledger: config/names.tsv guess_IsDownHeld */
s32 guess_IsDownHeld(u8 *a0) {
    u8 c;
    s32 v0;
    c = a0[0xA9];
    switch (c) {
    case 0x41:
        v0 = *(u16 *)(a0 + 0xAA) & 0x4000;
        break;
    case 0x53:
    case 0x73:
        v0 = ((u32)*(u16 *)(a0 + 0xAE) >> 8) < 0xC1;
        v0 = v0 ^ 1;
        break;
    default:
        v0 = 0;
        break;
    }
    return v0;
}
