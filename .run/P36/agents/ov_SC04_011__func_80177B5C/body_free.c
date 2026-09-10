u32 *func_80177B5C(p, bits, tbli, x, y)
u32 *p;
u32 bits;
s32 tbli;
s32 x;
s32 y;
{

    extern u8 D_80193C10[];
u32 bb;
  u32 *q;
u32 v;
u32 cl;
u32 cs;
u32 ca;
  s16 i;
  u32 mk1;
  u32 cc1;
  u32 flag;
u32 nn;
  u32 n;
u32 t;
  u32 col;
  u32 uv;
  u32 tt;
  u32 nv;
  u32 x1;
  u32 x2;
  u32 w;
  u32 g;
  u32 gg;
  u32 w3;
u32 yr;
u32 yt;
u32 tr;
u32 xr;
u32 c3;
s32 ff;
s32 two;
  yt = y;
  tr = tbli;
  xr = x;
  mk1 = 0xFFFFFF;
  cc1 = 0x74808080;
  bb = bits;
  t = x + 0xE;
  flag = 0x1000000;
  i = 0;
  two = 2;
  ff = 255;
  ;
  v = D_80193C10[(s16) tbli];
  gg = ((u32) (p - 5)) & mk1;
  ca = 0x3000000;
  p[0] = gg | ca;
  x1 = (x - 3) & 0xFFFF;
  x2 = (x + 5) & 0xFFFF;
  p[1] = cc1;
  yr = yt;
  yt = (s16) yt;
  cs = (yt + 1) << 16;
  w = cs | x1;
  cl = ((v << 6) | 0x4016) << 16;
  p[2] = w;
  p[3] = cl | 0x1800;
  p += 5;
  p[0] = (((u32) (p - 5)) & mk1) | ca;
  p[1] = cc1;
  p[2] = cs | x2;
  p[3] = cl | 0x1808;
  p += 5;
  q = p;
  yt = yt << 16;
  {
    for (; i < 3; i++)
    {
      nn = ((bb << 16) >> 18) >> 10;
      n = nn;
      if (((nn != 0) || (i == two)) || (i == ff))
      {
        flag = 0;
      }
      q[0] = (((u32) (q - 5)) & 0xFFFFFF) | 0x3000000;
      q[2] = (yt | (t & 0xFFFF)) | flag;
      col = 0x74808080;
      q[1] = col;
      nv = ((n * 8) + 8) | 0x4000;
      q[3] = cl | nv;
      q += 5;
      t += 8;
      bb <<= 4;
    }

  }
  p = q;
  g = (((u32) (p - 5)) & 0xFFFFFF) | 0x3000000;
  cs = yr << 16;
  p[0] = g;
  w3 = cs | ((xr + 0x2A) & 0xFFFF);
  cl = ((v << 6) | 0x4016) << 16;
  uv = ((s16) tr) << 4;
  p[2] = w3;
  tt = uv | 0x1000;
  p[1] = col;
  p[3] = cl | tt;
  p += 5;
  p[0] = (((u32) (p - 5)) & 0xFFFFFF) | 0x3000000;
  cs = cs | ((xr + 0x32) & 0xFFFF);
  uv = uv | 0x1008;
  cl = cl | uv;
  p[1] = col;
  p[2] = cs;
  p[3] = cl;
  p += 5;
  return p;
}
