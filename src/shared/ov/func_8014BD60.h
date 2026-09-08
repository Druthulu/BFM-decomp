/* func_8014BD60 — shared body (overlay slot 0x80128158, h_exact 12f02725). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80078EB8;
void func_8014BD60(s32 param_1, s32 param_2)
{
  int new_var;
  int v1;
  v1 = (int) ((unsigned short) D_80078EB8);
  if (v1 < param_2)
  {
    D_80078EB8 = 0;
  }
  else
  {
    D_80078EB8 = (unsigned short) ((new_var = v1) - param_2);
  }
  return;
}
