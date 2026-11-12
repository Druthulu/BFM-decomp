/* guess_ReturnPlayerToStandingState — shared body (overlay slot 0x80128158, h_exact 5f6b9cf5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8016EF78(s32 a0);
extern s32 guess_g_PlayerActor;
/* guess_ReturnPlayerToStandingState: calls func_8016EF78, then, unless the player's state is 0x19 or 0x1A, leaves its state and enters state 0 (standing)
 * Confidence low, xref chain: func_8016EF78(); state not 0x19/0x1A -> func_801599A4(player) (state exit table), func_80159B3C(player) (guess_SetState 0)
 * Names ledger: config/names.tsv guess_ReturnPlayerToStandingState */
void guess_ReturnPlayerToStandingState(s32 _arg0, s32 _arg1, s32 _arg2)
{
  s32 *new_var;
  void (*new_var2)(void *a0);
  unsigned short new_var3;
  new_var = &guess_g_PlayerActor;
  ((M2C_UNK (*)(void)) func_8016EF78)();
  new_var3 = *new_var;
  if (((u32) (new_var3 - 0x19)) >= 2U)
  {
    ((M2C_UNK (*)(u16 *)) func_801599A4)(&guess_g_PlayerActor);
    new_var2 = func_80159B3C;
    ((M2C_UNK (*)(u16 *)) new_var2)(&guess_g_PlayerActor);
  }
}
