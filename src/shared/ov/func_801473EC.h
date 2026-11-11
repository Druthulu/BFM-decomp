/* guess_ApplyVelocity — shared body (overlay slot 0x80128158, h_exact 90df300c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ApplyVelocity: adds an object's velocity (+0x10..+0x18) to its position (+0x4..+0xC) and flags it moved (bit 31 of +0x44) when the velocity is non-zero
 * Confidence high, code inference: a[1..3] += a[4..6] (s32 position += velocity); sets bit 31 of a[0x11] when any of a[4..6] is non-zero
 * Names ledger: config/names.tsv guess_ApplyVelocity */
void guess_ApplyVelocity(s32 *a0) {
    s32 *a2;
    a2 = a0;
    a2[1] += a2[4];
    a2[2] += a2[5];
    a2[3] += a2[6];
    if (a2[4] != 0 || a2[5] != 0 || a2[6] != 0) {
        a2[0x11] |= 0x80000000;
    }
}
