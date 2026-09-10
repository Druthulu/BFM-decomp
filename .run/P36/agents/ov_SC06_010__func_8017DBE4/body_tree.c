void func_8017DBE4(s32 *param_1)
{

    extern s8 D_801B2028;
  int new_var;
register s32 p __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus7)
s32 r;
  p = (s32) (&D_801B2028);
  r = param_1[0x2c / 4];
  new_var = r;
  p += new_var;
  *((s8 *) p) = 0;
  ((void (*)(void)) func_80146C3C)();
}
