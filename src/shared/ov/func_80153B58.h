/* func_80153B58 — shared body (overlay slot 0x80128158, h_exact 596dbad8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 guess_g_FrameCounter; // Names ledger: config/names.tsv guess_g_FrameCounter
extern s32 func_8016DA04(s32 a0);
extern s32 guess_SpawnSmallObject(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80153B58(s32 *a0) {
    if ((guess_g_FrameCounter & 0x3) == 0) {
        func_8016DA04((s32)a0);
    }
    if ((guess_g_FrameCounter & 0x1) == 0) {
        guess_SpawnSmallObject(3, a0,
                      *(s16 *)((u8 *)a0 + 6),
                      *(s16 *)((u8 *)a0 + 0xA),
                      *(s16 *)((u8 *)a0 + 0xE),
                      0x8880000, 0x18009000);
    }
}
