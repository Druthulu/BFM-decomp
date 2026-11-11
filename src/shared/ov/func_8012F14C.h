/* guess_RotTransSVWithMatrix — shared body (overlay slot 0x80128158, h_exact 9a2982b6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
/* guess_RotTransSVWithMatrix: loads matrix a0 as the GTE rotation and translation, then rotate-translates SVECTOR a1 into a2 (RotTransSV)
 * Confidence high, xref chain: calls SetRotMatrix(a0) and SetTransMatrix(a0) (libgte, per the SLUS map), then RotTransSV(a1, a2, &flag)
 * Names ledger: config/names.tsv guess_RotTransSVWithMatrix */
void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2)
{
    s32 buf[2];
    func_8004914C((void *)a0);
    func_800491AC((void *)a0);
    RotTransSV(a1, a2, buf);
}
