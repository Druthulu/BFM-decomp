/* guess_RotTransSVWithObjMatrix — shared body (overlay slot 0x80128158, h_exact 0400cb37). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void SetRotMatrix(void *a0);
extern void SetTransMatrix(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
/* guess_RotTransSVWithObjMatrix: loads the matrix of object a0 (at +0x34 of the struct its +0x20 points to) into the GTE, then RotTransSV a1 into a2
 * Confidence medium, xref chain: the same three library calls as guess_RotTransSVWithMatrix, with the matrix at +0x34 of the struct a0+0x20 points to
 * Names ledger: config/names.tsv guess_RotTransSVWithObjMatrix */
void guess_RotTransSVWithObjMatrix(s32 a0, s32 a1, s32 a2) {
    s32 *p = (s32 *)(*(s32 *)(a0 + 0x20) + 0x34);
    s32 buf[2];
    SetRotMatrix(p);
    SetTransMatrix(p);
    RotTransSV(a1, a2, buf);
}
