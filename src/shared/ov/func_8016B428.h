/* guess_RespawnSmallObjectType1E — shared body (overlay slot 0x80128158, h_exact 5722d205). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8016B448(s32, s32);
/* guess_RespawnSmallObjectType1E: frees the live small object of kind 0x1E, if any, and spawns a new one at a0's +0x7C/+0x7E/+0x80 with argument 0
 * Confidence medium, code inference: func_8016B448(a0, 0): func_8014C050 finds kind 0x1E in guess_g_SmallObjectPool, func_8016B984 frees it; guess_SpawnSmallObject(0x1E, a0, ..)
 * Names ledger: config/names.tsv guess_RespawnSmallObjectType1E */
s32 guess_RespawnSmallObjectType1E(s32 a0) {
    return func_8016B448(a0, 0);
}
