/* func_80151184 — shared body (overlay slot 0x80128158, h_exact 718e4df4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80151184(s32 arg0, s32 arg1, s32 arg2)
{
  u16 *new_var;
  int new_var2;
  *((s16 *) (((s8 *) arg0) + 0x3E)) = arg1;
  *((s16 *) (((s8 *) arg0) + 0x40)) = arg2;
  new_var = (u16 *) (((s8 *) arg0) + 0x42);
  new_var2 = (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x20)))) + 0x12)));
  *((u16 *) (((s8 *) arg0) + 0x3C)) = (u16) ((*((u16 *) (((s8 *) arg0) + 0x3C))) | 1);
  *new_var = new_var2;
}
