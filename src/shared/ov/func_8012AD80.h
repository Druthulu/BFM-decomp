/* guess_ApplyAccelAndVelocity — shared body (overlay slot 0x80128158, h_exact ff418149). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ApplyAccelAndVelocity: adds the acceleration (+0x44/+0x48/+0x4C) to the velocity (+0x10/+0x14/+0x18), then the velocity to the position (+0x4/+0x8/+0xC)
 * Confidence high, xref chain: +0x10.. += +0x44..; +0x4.. += +0x10..; the position/velocity words of guess_ApplyVelocity
 * Names ledger: config/names.tsv guess_ApplyAccelAndVelocity */
void guess_ApplyAccelAndVelocity(s32 a0) {
    *(s32*)(a0 + 0x10) += *(s32*)(a0 + 0x44);
    *(s32*)(a0 + 0x14) += *(s32*)(a0 + 0x48);
    *(s32*)(a0 + 0x18) += *(s32*)(a0 + 0x4C);
    *(s32*)(a0 + 0x4) += *(s32*)(a0 + 0x10);
    *(s32*)(a0 + 0x8) += *(s32*)(a0 + 0x14);
    *(s32*)(a0 + 0xC) += *(s32*)(a0 + 0x18);
}
