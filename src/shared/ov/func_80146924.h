/* func_80146924 — shared body (overlay slot 0x80128158, h_exact e116ed6b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_g_SmallObjectPool; // Names ledger: config/names.tsv guess_g_SmallObjectPool
extern s32 guess_SpawnSmallObjectAtOrigin(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_80146924(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5) {
    s32 count = 0;
    u8 *v1 = (u8 *)&guess_g_SmallObjectPool;
    u8 *end = v1 + 0xA50;
    while (v1 < end) {
        if (*(u16 *)v1 == (a0 & 0xFFFF)) count++;
        v1 += 0x58;
    }
    if ((u32)count < (u32)arg5) {
        return guess_SpawnSmallObjectAtOrigin(a0 & 0xFFFF, a1, a2, a3);
    }
    return 0;
}
