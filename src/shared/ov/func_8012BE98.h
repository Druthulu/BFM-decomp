/* guess_DistSqXZToPoint — shared body (overlay slot 0x80128158, h_exact 63eedc41). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800132BC(s32 a0, s32 a1);
/* guess_DistSqXZToPoint: returns the squared horizontal (x, z) distance between object a0's position and point a1
 * Confidence high, code inference: a = (a0+6, 0, a0+E), b = (a1[0], 0, a1[2]); func_800132BC(a, b) = sum of Square0 of the differences
 * Names ledger: config/names.tsv guess_DistSqXZToPoint */
s32 guess_DistSqXZToPoint(s32 arg0, u16 * arg1)
{
    s16 a[3];
    s16 b[3];
    a[0] = *(u16 *)((u8 *)arg0 + 0x6);
    a[1] = 0;
    a[2] = *(u16 *)((u8 *)arg0 + 0xE);
    b[0] = *(u16 *)((u8 *)arg1 + 0x0);
    b[1] = 0;
    b[2] = *(u16 *)((u8 *)arg1 + 0x4);
    return func_800132BC((s32)a, (s32)b);
}
