/* func_80141B90 — shared body (overlay slot 0x80128158, h_exact a8e23f54). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013FAF8(s16, s16);
extern short guess_g_DoubleBufferIndex; // Names ledger: config/names.tsv guess_g_DoubleBufferIndex
extern u8 guess_g_MenuPacketBases[]; // Names ledger: config/names.tsv guess_g_MenuPacketBases
extern s32 guess_g_MenuPacketPtr; // Names ledger: config/names.tsv guess_g_MenuPacketPtr
extern u16 guess_g_MenuFrameCounter; // Names ledger: config/names.tsv guess_g_MenuFrameCounter
extern u16 guess_g_MenuStep; // Names ledger: config/names.tsv guess_g_MenuStep
extern u8 D_800B9A15;
void func_80141B90(void)
{
  volatile char pad;
  guess_g_MenuPacketPtr = ((s32 *) guess_g_MenuPacketBases)[*((u16 *) (&guess_g_DoubleBufferIndex))];
  ((void (*)(s32, s32))func_8013FAF8)(2, 3);
  if (guess_g_MenuFrameCounter == 0)
  {
    *((s8 *) (&D_800B9A15)) = 0;
    guess_g_MenuStep = guess_g_MenuStep + 1;
  }
}
