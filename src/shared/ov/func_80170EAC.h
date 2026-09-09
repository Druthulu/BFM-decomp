/* func_80170EAC — shared body (overlay slot 0x80128158, h_exact 6ac99ae3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *D_8011F738;
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern int func_800D0F8C(int a0);
extern void func_801718AC(void *a0);
void func_80170EAC(u8 * _arg0)
{
  s32 arg;
  if (((int (*)(char))func_800D0F8C)(D_8011F738) != 0)
  {
    arg = D_8011F73C;
  }
  else
  {
    arg = D_8011F740;
  }
  ((void (*)(s32)) func_801718AC)(arg);
}
