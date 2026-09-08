/* func_8016EDEC — shared body (overlay slot 0x80128158, h_exact 45ec89ce). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8016EE94();
extern s32 D_80126B58;
void func_8016EDEC(s32 _arg0, s32 _arg1, s32 _arg2)
{
  unsigned short *new_var;
  if (1)
  {
    ((M2C_UNK (*)(void)) func_8016EE94)();
    new_var = &D_80126B58;
    if (((u32) ((*new_var) - 0x19)) >= 2U)
    {
      ((M2C_UNK (*)(u16 *)) func_801599A4)(&D_80126B58);
      ((M2C_UNK (*)(u16 *)) func_80159B3C)(&D_80126B58);
    }
  }
}
