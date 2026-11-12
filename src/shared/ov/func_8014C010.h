/* guess_SpawnSmallObjectType2 — shared body (overlay slot 0x80128158, h_exact a8c18c00). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146AFC(void *arg0);
/* guess_SpawnSmallObjectType2: starts a small object of kind 2 at (0, 0, 0) with a0 as its first parameter word (+0x34) and a1 as its second (+0x2C)
 * Confidence medium, xref chain: func_80146AFC({kind 2, pos 0, +8 a0, +0xC a1, +0x10 0}); the jump launch passes 2, the standing step passes 1 every 4th frame
 * Names ledger: config/names.tsv guess_SpawnSmallObjectType2 */
void guess_SpawnSmallObjectType2(s32 a0, s32 a1) {
    struct S8014C010 sp;
    sp.w8 = a0;
    sp.h0 = 2;
    sp.h1 = 0;
    sp.h2 = 0;
    sp.h3 = 0;
    sp.wC = a1;
    sp.w10 = 0;
    func_80146AFC(&sp);
}
