/* guess_ClearVelocityAndSetGravity — shared body (overlay slot 0x80128158, h_exact dbbaaf68). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ClearVelocityAndSetGravity: zeroes the velocity (+0x10/+0x14/+0x18) and the x/z acceleration (+0x44/+0x4C) and sets the y acceleration +0x48 to 0x18000
 * Confidence medium, code inference: +0x10/+0x14/+0x18/+0x44/+0x4C = 0, +0x48 = 0x18000; func_80142C84 pairs vy -0xC0000 with +0x48 = 0x20000 (a hop)
 * Names ledger: config/names.tsv guess_ClearVelocityAndSetGravity */
void guess_ClearVelocityAndSetGravity(s32 a0) {
    *(s32 *)(a0 + 0x18) = 0;
    *(s32 *)(a0 + 0x14) = 0;
    *(s32 *)(a0 + 0x10) = 0;
    *(s32 *)(a0 + 0x4C) = 0;
    *(s32 *)(a0 + 0x44) = 0;
    *(s32 *)(a0 + 0x48) = 0x18000;
}
