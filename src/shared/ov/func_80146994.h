/* guess_SpawnSmallObjectAtOrigin — shared body (overlay slot 0x80128158, h_exact f19dbbb7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
/* guess_SpawnSmallObjectAtOrigin: starts a small object of kind a0 with parameter a1 and words a2, a3 at position (0, 0, 0)
 * Confidence medium, xref chain: func_80146A6C(a0 & 0xFFFF, a1, 0, 0, 0, a2, a3): packs the record for func_80146AFC, the 0x58-byte D_8011D030 allocator
 * Names ledger: config/names.tsv guess_SpawnSmallObjectAtOrigin */
s32 guess_SpawnSmallObjectAtOrigin(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    func_80146A6C(arg0 & 0xFFFF, (void *)arg1, 0, 0, 0, arg2, arg3);
}
