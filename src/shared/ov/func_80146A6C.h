/* guess_SpawnSmallObject — shared body (overlay slot 0x80128158, h_exact 9e73259d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_SpawnSmallObject: starts a small object of kind a0 at x/y/z a2/a3/a4 with parameter words a1, a5, a6 in the 0x58-byte array guess_g_SmallObjectPool
 * Confidence medium, xref chain: packs {a0, a2, a3, a4, a1, a5, a6} and calls func_80146AFC: first free 0x58-byte record of guess_g_SmallObjectPool; kinds run through D_80126728
 * Names ledger: config/names.tsv guess_SpawnSmallObject */
void aF80146A6C(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6) __asm__("guess_SpawnSmallObject");
void aF80146A6C(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6)
{
    u8 sp[0x18];
    *(s16 *)(sp + 0x0) = a0;
    *(s32 *)(sp + 0x8) = a1;
    *(s16 *)(sp + 0x2) = a2;
    *(s16 *)(sp + 0x4) = a3;
    *(s16 *)(sp + 0x6) = a4;
    *(s32 *)(sp + 0xC) = a5;
    *(s32 *)(sp + 0x10) = a6;
    ((s32 (*)(void *))func_80146AFC)(sp);
}
