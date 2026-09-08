/* func_80180710 — shared body (overlay slot 0x80128158, h_exact d000df43). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 func_8017DA9C(void);
int func_80180710(void)
{
  int new_var;
  new_var = 0x1;
  new_var--;
  return (((unsigned int) ((int (*)(void))func_8017DA9C)()) << 16) == new_var;
  new_var++;
}
