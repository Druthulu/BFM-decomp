/* func_80177940 — shared body (overlay slot 0x80128158, h_exact 1bed0717). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80029504(void);
void func_80177940(u32 *p, u32 a_, u32 b_, u32 c_)
{
  int new_var;
register u32 a __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B headers1)
register u32 b __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers1)
register u32 c __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B headers1)
register u32 v __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1)
  u32 *q;
  u32 *r;
  u32 flag;
register u32 n __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B headers1)
  u32 nn;
  u32 t;
  u32 cl;
  u32 cs;
  u32 col;
  s16 i;
  new_var = a_;
  b = b_;
  c = c_;
  a = new_var;
  v = (u32) func_80029504();
  v = v - 10;
  v = v < 0x4b0;
  v = -v;
  v = v & 0xb4;
  c++;
  c--;
  cs = c << 16;
  p[0] = (((u32) (p - 5)) & 0xffffff) | 0x3000000;
  p[2] = cs | ((b + 0xf) & 0xffff);
  p[1] = 0x74808080;
  p[3] = (((v << 6) | 0x4016) << 16) | 0x3850;
  p += 5;
  q = p;
__asm__("" : "=r"(v) : "0"(v));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers1)
  cl = ((v << 6) | 0x4016) << 16;
  flag = 0x1000000;
  for (i = 0; i < 4; i++)
  {
    nn = (a << 16) >> 28;
    n = nn;
    if (((nn != 0) || (i == 3)) || (i == 1))
    {
      flag = 0;
    }
    q[0] = (((u32) (q - 5)) & 0xffffff) | 0x3000000;
    q[2] = (cs | (b & 0xffff)) | flag;
    col = 0x74808080;
    new_var = n * 8;
    q[1] = col;
    t = (new_var + 8) | 0x4000;
    q[3] = cl | t;
    q += 5;
    b += 8;
    a <<= 4;
    col = 0;
  }
  p = q;
  r = p;
__asm__("" : "=r"(r) : "0"(r));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers1)
  *((u16 *) (r - 8)) += 6;
  *((u16 *) (r - 3)) += 6;
}
