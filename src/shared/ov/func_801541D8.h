/* guess_SetAnimFromIndex — shared body (overlay slot 0x80128158, h_exact cc56f5c9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154218(u8 *a0, s32 a1, s32 a2);
/* guess_SetAnimFromIndex: starts animation list a1 of a0's table (+0xB0) at entry index a2, unless that list is already running (+0xB4)
 * Confidence medium, xref chain: +0xB4 != (+0xB0)[a1] -> func_80154218: +0xB4 = list, +0xBC/+0xBD = a2, +0xDC = func_801549F8(..); guess_SetAnim is the same from index 0
 * Names ledger: config/names.tsv guess_SetAnimFromIndex */
void guess_SetAnimFromIndex(u8 *a0, s32 a1, s32 a2) {
    if (*(s32 *)(a0 + 0xB4) != ((s32 *)*(s32 **)(a0 + 0xB0))[a1]) {
        func_80154218(a0, a1, a2);
    }
}
