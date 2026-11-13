/* func_801508F8 — shared body (overlay slot 0x80128158, h_exact 3974efd4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8015094C(s32 a0);
/* $v0 at exit: result of func_8015094C or lbu $v0, 0x1BF($s0) at ov_MAIN_012:0x80150908 or addiu $v0, $zero, 0x1A at ov_MAIN_012:0x8015091C; no caller reads $v0 (census unused); void moved `li v0,26` at +0x1C in func_801508F8, ov_MAIN_012 objdump */
short func_801508F8(s32 a0)
{
  if ((*((u8 *) (a0 + 0x1BF))) != 0)
  {
    if ((*((u16 *) a0)) != 0x1A)
    {
      while (func_8015094C(a0) != 0)
      {
        ;
      }
    }
  }
}
