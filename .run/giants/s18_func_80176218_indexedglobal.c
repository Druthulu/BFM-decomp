
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef float f32;
typedef unsigned long long u64;
typedef long long s64;
typedef double f64;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
extern u16 D_80078EB2;
extern u16 D_8011F82A;
extern u16 D_8011F82C;
extern u16 D_80078EB4;
extern u16 D_8011F8C4;
extern u8 D_8011F7A8;
extern u8 D_80078E78;
extern u8 D_8018A2B8[];
extern u8 *D_8018A23C[];
extern void func_80176FF4(s32);
extern void func_80177340(s32);
extern u32 func_801783D0(s32, s32);
extern void func_80177F84(s32, s32);
extern void func_80177DA8(s32, s32, s32);
extern void func_80177AD4(s32, s32);
extern s32 func_80024054(u8 *, u8 *);
extern u32 *func_80178298(u32 *, u8 *, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);
void func_80176218(s32 param_1)
{
  s32 st = (s32) (&D_8011F7A8);
  s32 cach = st + 0x48;
  s32 flag = st + 0xE0;
  s32 cur = (s32) (&D_80078E78);
  u8 buf[24];
register s32 ne __asm__("$2");
  u16 sA;
  sA = D_80078EB2;
  ne = sA != D_8011F82A;
  if (D_8011F82C == D_80078EB4)
  {
    if ((ne == 0) && (D_8011F8C4 == 0))
    {
      goto L340;
    }
  }
  else
  {
    s32 d = (s16) (D_8011F82C - D_80078EB4);
    if (d < 0)
    {
      if (d < (-10))
      {
        D_8011F82C = D_8011F82C + 2;
      }
      else
      {
        D_8011F82C = D_8011F82C + 1;
      }
    }
    else
      if (d > 10)
    {
      D_8011F82C = D_8011F82C - 2;
    }
    else
    {
      D_8011F82C = D_8011F82C - 1;
    }
    *((u16 *) (flag + 0x3C)) = 1;
    *((u16 *) (cach + 0x3A)) = *((u16 *) (cur + 0x3A));
    goto L328;
  }
  if (ne)
  {
    *((u16 *) (st + 0x82)) = sA;
    *((u16 *) (st + 0x11C)) = 1;
  }
  else
  {
    *((u16 *) (st + 0x11C)) = 0;
  }
  L328:
  func_80176FF4(*((s32 *) ((((param_1 << 16) >> 14) + st) + 0x18)));

  L340:
  ne = (*((u16 *) (cur + 0x3E))) != (*((u16 *) (cach + 0x3E)));

  if ((*((u16 *) (cach + 0x40))) == (*((u16 *) (cur + 0x40))))
  {
    if ((ne == 0) && ((*((u16 *) (flag + 0x40))) == 0))
    {
      goto L444;
    }
  }
  else
  {
    s32 d;
    u16 nc;
    d = (s16) ((*((u16 *) (cach + 0x40))) - (*((u16 *) (cur + 0x40))));
    if (d < 0)
    {
      nc = (*((u16 *) (cach + 0x40))) + 2;
      if ((-11) < d)
      {
        nc = (*((u16 *) (cach + 0x40))) + 1;
      }
    }
    else
    {
      nc = (*((u16 *) (cach + 0x40))) - 1;
      if (10 < d)
      {
        nc = (*((u16 *) (cach + 0x40))) - 2;
      }
    }
    *((u16 *) (cach + 0x40)) = nc;
    *((u16 *) (flag + 0x40)) = 1;
    *((u16 *) (cach + 0x3E)) = *((u16 *) (cur + 0x3E));
    goto L3E8;
  }
  if (ne)
  {
    *((u16 *) (cach + 0x3E)) = *((u16 *) (cur + 0x3E));
    *((u16 *) (flag + 0x40)) = 1;
  }
  else
  {
    *((u16 *) (flag + 0x40)) = 0;
  }
  L3E8:
  {
    s32 s0b = ((param_1 << 16) >> 14) + st;
    u16 cc;
    s32 pp;
    func_80177340((*((s32 *) (s0b + 0x18))) + 0x104);
    cc = *((u16 *) (cach + 0x40));
    pp = *((s32 *) (s0b + 0x28));
    if (cc < 100)
    {
      *((u8 *) (pp + 0x5D)) = D_8018A2B8[cc / 5];
    }
    else
    {
      *((u8 *) (pp + 0x5D)) = 0;
    }
  }

  L444:
  if ((*((s32 *) (cach + 0x14))) == (*((s32 *) (cur + 0x14))))
  {
    if ((*((s32 *) (flag + 0x14))) == 0)
    {
      goto L4D0;
    }
    *((s32 *) (flag + 0x14)) = 0;
    goto L4A8;
  }
  else
  {
    s32 d = (*((s32 *) (cur + 0x14))) - (*((s32 *) (cach + 0x14)));
    s32 nd;
    if (d > 0)
    {
      nd = (*((s32 *) (cach + 0x14))) + 1;
      if (9 < d)
      {
        nd = (*((s32 *) (cach + 0x14))) + 10;
      }
    }
    else
    {
      nd = (*((s32 *) (cach + 0x14))) - 10;
      if ((-10) < d)
      {
        nd = (*((s32 *) (cach + 0x14))) - 1;
      }
    }
    *((s32 *) (cach + 0x14)) = nd;
    *((s32 *) (flag + 0x14)) = 1;
  }

  L4A8:
  {
    u32 r = func_801783D0(*((s32 *) (cach + 0x14)), 0);
    func_80177F84((*((s32 *) ((((param_1 << 16) >> 14) + st) + 0x18))) + 0x208, r);
  }

  L4D0:
  if ((*((u16 *) (cur + 0x34))) != (*((u16 *) (cach + 0x34))))
  {
    *((u16 *) (cach + 0x34)) = *((u16 *) (cur + 0x34));
    *((u16 *) (flag + 0x34)) = 1;
    *((u8 *) (cach + 0x42)) = *((u8 *) (cur + 0x42));
  }
  else
  {
    if ((*((u16 *) (flag + 0x34))) == 0)
    {
      goto L558;
    }
    *((u16 *) (flag + 0x34)) = 0;
  }

  {
    u16 e = 999;
    s16 r;
    if ((*((u16 *) (cach + 0x34))) < 1000)
    {
      e = *((u16 *) (cach + 0x34));
    }
    r = (s16) func_801783D0((s16) e, 4);
    func_80177DA8((*((s32 *) ((((param_1 << 16) >> 14) + st) + 0x18))) + 0x294, (s32) r, *((u8 *) (cach + 0x42)));
  }
  L558:
  if ((*((s16 *) (cach + 0x1A))) != (*((s16 *) (cur + 0x1A))))
  {
    *((s16 *) (cach + 0x1A)) = *((s16 *) (cur + 0x1A));
    *((s16 *) (flag + 0x1A)) = 1;
  }
  else
  {
    if ((*((s16 *) (flag + 0x1A))) == 0)
    {
      goto L63C;
    }
    *((s16 *) (flag + 0x1A)) = 0;
  }

  {
    u16 f = *((u16 *) (cach + 0x1A));
    s32 e = *((s32 *) ((((param_1 << 16) >> 14) + st) + 0x18));
    s16 sv = 0x200;
    s32 i6;
    s32 i4;
    if ((f & 1) == 0)
    {
      sv = (*((u16 *) (st + 0x16))) + 0x65;
    }
    *((s16 *) (e + 0x32A)) = sv;
    {
      s32 t = ((((s16) f) / 15) & 3) * 15;
      i6 = func_801783D0(((((s16) f) / 15) * 0x10000) >> 0x12, 8);
      i4 = func_801783D0((t * 0x10000) >> 16, 0);
    }
    {
      s32 p2 = param_1;
__asm__("" : "=r"(p2) : "0"(p2));
      func_80177AD4((*((s32 *) ((((p2 << 16) >> 14) + st) + 0x18))) + 800, ((i6 + i4) * 0x10000) >> 0x10);
    }
  }
  L63C:
  if ((*((u8 *) (cur + 0x4A))) != (*((u8 *) (cach + 0x4A))))
  {
    *((u8 *) (cach + 0x4A)) = (*((u8 *) (cur + 0x4A))) & 0x7F;
    *((u8 *) (flag + 0x4A)) = 1;
  }
  else
  {
    if ((*((u8 *) (flag + 0x4A))) == 0)
    {
      return;
    }
    *((u8 *) (flag + 0x4A)) = 0;
  }

  {
    s32 s0b = ((param_1 << 16) >> 14) + st;
    u8 *arg = D_8018A23C[*((u8 *) (cach + 0x4A))];
    u32 *p = (u32 *) ((*((s32 *) (s0b + 0x18))) + 900);
    func_80024054(arg, buf);
    p = func_80178298(p, buf, (s16) ((*((u16 *) (st + 0x14))) + 0x39), (s16) ((*((u16 *) (st + 0x16))) + 0x5B));
    func_8005A600((s32) p, 0, 0, 0x15, 0);
    *p = (((u32) (((u8 *) p) - 0x14)) & 0xffffff) | 0x2000000;
    *((u32 **) (s0b + 0x20)) = p;
  }
}
