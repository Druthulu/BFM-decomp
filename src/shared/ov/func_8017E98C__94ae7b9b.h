/* func_8017E98C — shared body (overlay slot 0x80128158, h_exact 94ae7b9b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017E98C(void *a0)
{
  char *new_var;
  s32 v0;
register void *s0 __asm__("$16");
 do { } while (0);
  s0 = a0;
  ((void (*)(void *))func_8017EE68)(a0);
  new_var = (char *) s0;
  v0 = 0x8;
  *((s32 *) (((char *) s0) + 0x200)) = v0;
  v0 = 0x100000;
  *((s32 *) (new_var + 0x204)) = v0;
  func_80171990((u8 *) s0);
}
