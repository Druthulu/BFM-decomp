/* func_8016EDEC — shared body (overlay slot 0x80128158, h_exact 45ec89ce). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8016EE94(s32 a0, s32 a1);
extern s32 guess_g_PlayerActor;
void func_8016EDEC(s32 _arg0, s32 _arg1, s32 _arg2)
{
  unsigned short *new_var;
  if (1)
  {
    ((M2C_UNK (*)(void)) func_8016EE94)();
    new_var = &guess_g_PlayerActor;
    if (((u32) ((*new_var) - 0x19)) >= 2U)
    {
      ((M2C_UNK (*)(u16 *)) func_801599A4)(&guess_g_PlayerActor);
      ((M2C_UNK (*)(u16 *)) func_80159B3C)(&guess_g_PlayerActor);
    }
  }
}
