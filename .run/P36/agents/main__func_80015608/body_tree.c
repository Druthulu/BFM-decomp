void func_80015608(s32 arg0, s32 arg1)
{
  int new_var2;
  u8 *icon;
  int new_var;
  s32 x0;
  s32 flags;
register s32 blockSize __asm__("$22");  // !FAKE: pin $22 — NEEDED DIFFERS (P36 rung B tus9)
register u32 code __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
s32 htmp;
  u8 *cur;
  u32 rgbc;
  s32 y0;
  u32 y0hi;
  u16 *tex;
  u32 *otp;
register u32 tagconst __asm__("$20");  // !FAKE: pin $20 — NEEDED DIFFERS (P36 rung B tus9)
register u32 mask __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
  otp = (u32 *) arg1;
  icon = *((u8 **) (((u8 *) arg0) + 8));
  htmp = *((u16 *) (((u8 *) arg0) + 2));
  x0 = htmp - (D_800AF7BC >> 1);
  flags = *(((u8 *) arg0) + 0xC);
  htmp = *((u16 *) (((u8 *) arg0) + 4));
  y0 = htmp - (D_800AF7BE >> 1);
  new_var = 0x03000000;
  blockSize = (flags & 0x80) ? (0x10) : (8);
  code = blockSize & 0xFF;
  if (code == 8)
  {
    code = 0x74000000;
  }
  else
  {
    code = 0x7C000000;
  }
  cur = D_800A5E60;
  tagconst = new_var;
  if ((*icon) != 0)
  {
    rgbc = code | 0x808080;
    y0hi = y0 << 16;
    do
    {
      *((u32 *) (cur + 4)) = rgbc;
      *((u32 *) (cur + 8)) = ((u16) x0) | y0hi;
      {
        s32 xt = blockSize + x0;
        x0 = xt;
      }
      tex = func_80015908(*icon, (u16) flags);
      icon++;
      mask = 0x00FFFFFF;
      new_var2 = 0x40560000;
      new_var = 0x10;
      *((u32 *) (cur + 0xC)) = (*tex) | new_var2;
      *((u32 *) cur) = ((*otp) & mask) | tagconst;
      *otp = ((u32) cur) & mask;
      cur += new_var;
    }
    while ((*icon) != 0);
  }
  D_800A5E60 = cur;
}
