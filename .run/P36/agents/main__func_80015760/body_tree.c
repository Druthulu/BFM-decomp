void func_80015760(Obj_80015760 *obj, s32 *ot)
{
  s32 x0;
u32 tx;
  s32 y0;
  s32 flags;
  u32 value;
  u32 digits;
s32 count;
  u8 digitCount;
  u8 width;
  u32 tagHi;
  u32 color;
  u32 yWord;
register u32 tagCode __asm__("$21");  // !FAKE: pin $21 — NEEDED DIFFERS (P36 rung B tus9)
  s32 *pkt;
  tx = obj->x;
  x0 = ((s32) tx) - (D_800AF7BC >> 1);
  flags = obj->flags;
  y0 = ((s32) obj->y) - (D_800AF7BE >> 1);
  value = (u32) obj->value;
  count = flags & 0xF;
  digitCount = count;
  if (count == 0)
  {
    digitCount = 8;
  }
  if (flags & 0x40)
  {
    digits = func_80015A74(value);
  }
  else
  {
    digits = value;
  }
  width = 8;
  if (flags & 0x80)
  {
    y0++;
    y0--;
    width = 0x10;
  }
  tagHi = width;
  if (tagHi == 8)
  {
    tagHi = 0x74000000;
  }
  else
  {
    tagHi = 0x7C000000;
  }
  tagCode = 0x03000000;
  pkt = (s32 *) D_800A5E60;
  if (digitCount != 0)
  {
    color = tagHi | 0x00808080;
    yWord = (u32) (y0 << 16);
    do
    {
      u32 xLow;
      u32 idx;
      s32 tile;
      u16 *uvPtr;
      u32 uvc;
register u32 mask __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
      xLow = (u16) x0;
      x0 = width + x0;
      idx = (digits >> ((digitCount - 1) << 2)) & 0xF;
      tile = D_80062B78[idx];
      pkt[1] = (s32) color;
      digitCount--;
      pkt[2] = (s32) (xLow | yWord);
      uvPtr = func_80015908(tile, (u16) flags);   /* the caller's original prototype took u16: the target masks (andi) before the call */
      uvc = 0x40560000;
      pkt[3] = (s32) ((*uvPtr) | uvc);
      mask = 0x00FFFFFF;
      pkt[0] = (s32) (((*ot) & mask) | tagCode);
      *ot = (s32) (((u32) pkt) & mask);
      pkt += 4;
    }
    while (digitCount != 0);
  }
  D_800A5E60 = (u8 *) pkt;
}
