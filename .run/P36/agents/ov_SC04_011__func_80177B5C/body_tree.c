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
register u32 cl __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)
register u32 cs __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)
u32 ca;
  s16 i;
  u32 mk1;
  u32 cc1;
  u32 flag;
register u32 nn __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
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
register u32 yr __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B t3_tus1)
register u32 yt __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
register u32 tr __asm__("$21");  // !FAKE: pin $21 — NEEDED DIFFERS (P36 rung B t3_tus1)
register u32 xr __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B t3_tus1)
u32 c3;
s32 ff;
s32 two;
  yt = y;
  tr = tbli;
__asm__("" : "=r"(tr) : "0"(tr));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
  xr = x;
__asm__("" : "=r"(xr) : "0"(xr));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
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
__asm__("" : "=r"(yr) : "0"(yr));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
  yt = (s16) yt;
  cs = (yt + 1) << 16;
  w = cs | x1;
__asm__("" : "=r"(w) : "0"(w));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
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
__asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t3_tus1)
  cs = yr << 16;
  p[0] = g;
  w3 = cs | ((xr + 0x2A) & 0xFFFF);
__asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t3_tus1)
  cl = ((v << 6) | 0x4016) << 16;
  uv = ((s16) tr) << 4;
  p[2] = w3;
  tt = uv | 0x1000;
  p[1] = col;
  p[3] = cl | tt;
  p += 5;
  p[0] = (((u32) (p - 5)) & 0xFFFFFF) | 0x3000000;
__asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t3_tus1)
  cs = cs | ((xr + 0x32) & 0xFFFF);
  uv = uv | 0x1008;
  cl = cl | uv;
  p[1] = col;
  p[2] = cs;
  p[3] = cl;
  p += 5;
__asm__("" :: "r"(tr), "r"(xr));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B t3_tus1)
  return p;
}
