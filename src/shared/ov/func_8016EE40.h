/* func_8016EE40 — shared body (overlay slot 0x80128158, h_exact 5f6b9cf5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8016EF78(s32 a0);
extern s32 D_80126B58;
void func_8016EE40(s32 _arg0, s32 _arg1, s32 _arg2)
{
  s32 *new_var;
  void (*new_var2)(void *a0);
  unsigned short new_var3;
  new_var = &D_80126B58;
  ((M2C_UNK (*)(void)) func_8016EF78)();
  new_var3 = *new_var;
  if (((u32) (new_var3 - 0x19)) >= 2U)
  {
    ((M2C_UNK (*)(u16 *)) func_801599A4)(&D_80126B58);
    new_var2 = func_80159B3C;
    ((M2C_UNK (*)(u16 *)) new_var2)(&D_80126B58);
  }
}
