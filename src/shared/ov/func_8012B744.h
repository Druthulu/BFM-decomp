/* guess_YawToPoint — shared body (overlay slot 0x80128158, h_exact 6c580f8e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 x, s32 y);
/* guess_YawToPoint: returns the yaw (0-0xFFF) from position a0 toward point a1 in the x/z plane
 * Confidence medium, code inference: (ratan2(z delta, x delta) - 0x400) & 0xFFF between a0's x/z (+0x2, +0xA) and SVECTOR a1: a 4096-unit x/z angle
 * Names ledger: config/names.tsv guess_YawToPoint */
s32 guess_YawToPoint(void *a0, void *a1) {
    s32 ang;
    ang = ratan2(*(s16 *)((s32)a0 + 0xA) - *(s16 *)((s32)a1 + 0x4),
                 *(s16 *)((s32)a1 + 0x0) - *(s16 *)((s32)a0 + 0x2));
    return (ang - 0x400) & 0xFFF;
}
