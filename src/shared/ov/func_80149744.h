/* guess_IsChargedSquarePressed — shared body (overlay slot 0x80128158, h_exact 13b4f28e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EBF;
/* guess_IsChargedSquarePressed: returns 1 when Square is newly pressed (+0xAC & 0x80) while +0x44 bit 2 is clear and the charge byte D_80078EBF has reached 0x80
 * Confidence low, xref chain: (+0x44 & 4) == 0 && D_80078EBF >= 0x80 && (+0xAC & 0x80); func_8014A59C fills D_80078EBF by 3 (6) a frame while 8 is held, cap 0x80
 * Names ledger: config/names.tsv guess_IsChargedSquarePressed */
s32 guess_IsChargedSquarePressed(struct S_80149744 *a0) {
    if ((a0->w44 & 0x4) == 0 && D_80078EBF >= 0x80) {
        if (a0->h_AC & 0x80) {
            return 1;
        }
    }
    return 0;
}
