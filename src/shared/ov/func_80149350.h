/* guess_ObjRotTransSV — shared body (overlay slot 0x80128158, h_exact 5aa2bbd6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);
/* guess_ObjRotTransSV: RotTransSV of a1 into a2 with object a0's model matrix: tail-calls guess_RotTransSVWithMatrix(*(a0 + 0x20) + 0x34) keeping a1, a2
 * Confidence medium, xref chain: K&R call guess_RotTransSVWithMatrix(*(a0 + 0x20) + 0x34) with the caller's a1/a2 left in place; guess_UpdateAttachedPos calls it (obj, buf, buf)
 * Names ledger: config/names.tsv guess_ObjRotTransSV */
void guess_ObjRotTransSV(s32 arg0) {
    ((void (*)())guess_RotTransSVWithMatrix)(*(s32 *)(arg0 + 0x20) + 0x34);
}
