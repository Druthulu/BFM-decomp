/* guess_MoveImageList — shared body (overlay slot 0x80128158, h_exact 7eb4113a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void MoveImage(void *a0, s32 a1, s32 a2);
/* guess_MoveImageList: runs MoveImage over a zero-terminated list of {RECT, dst x, dst y} entries
 * Confidence high, xref chain: calls MoveImage(entry, entry[2], entry[3]) over 16-byte {RECT, x, y} entries until entry[3] == 0
 * Names ledger: config/names.tsv guess_MoveImageList */
void guess_MoveImageList(s32 a0) {
    s32 *r = (s32 *)a0;
    if (r[3] == 0) {
        return;
    }
    do {
        MoveImage(r, r[2], r[3]);
        r += 4;
    } while (r[3] != 0);
}
