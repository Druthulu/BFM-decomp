/* guess_IntToBcd — shared body (overlay slot 0x80128158, h_exact 7933fb56). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_IntToBcd: returns a0 as packed decimal digits (one per nibble, lowest digit in bits 0-3), shifted left by a1
 * Confidence high, code inference: while a2 >= 10: digit a2 - (a0/10)*10 is OR'ed in at shift a3, a3 += 4; the last digit closes it; returns t0 << a1
 * Names ledger: config/names.tsv guess_IntToBcd */
u32 guess_IntToBcd(s32 a0, s32 a1) {
    s32 t0;
    s32 a2;
    s32 a3;
    t0 = 0;
    a2 = a0;
    a3 = 0;
    while (a2 >= 10) {
        a0 = a0 / 10;
        t0 = t0 | ((a2 - (a0 * 2 + a0 * 8)) << a3);
        a2 = a0;
        a3 += 4;
    }
    t0 = t0 | (a2 << a3);
    return t0 << a1;
}
