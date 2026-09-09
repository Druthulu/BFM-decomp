/* func_8013CA14 — shared body (overlay slot 0x80128158, h_exact 83788c45). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013CA14(void)
{
  int *base = &D_8018E760;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_8018E765;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_8018E764)) * 2) + D_8018E760);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_8018E765 = (unsigned char) p[1];
      D_8018E764 = D_8018E764 + 1;
      if (D_8018E765 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_8018E764 = 0;
        *base = 0;
      }
    }
    else
    {
      D_8018E765 = c - 1;
    }
  }
  return;
}
