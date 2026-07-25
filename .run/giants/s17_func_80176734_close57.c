
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
extern u8 D_8011F7A8[];
extern u8 D_80078E78[];
extern s16 D_801152BA;
extern u8 D_8011F7B0;
extern u8 D_80115214;
extern u8 D_800B9A13;
extern u8 D_8018A2D8[];
extern u16 D_8018A22A[];
extern s32 D_8018A2E4[];
extern u16 D_8018A238;
extern u8 D_8018A2CC[];
extern u8 D_800D45D4;
extern u8 D_800D43D4;
extern u8 D_800D4414;
extern s32 D_80126B58;
extern s16 D_80126D20;
extern s16 D_80126CE0;
extern void func_800183E0(s32 a0);
extern s32 func_801619D0(void *a0);
extern s32 func_80161A00(s32 a0);
extern s32 func_80161A30(s32 a0);
extern s32 func_80161A60(s32 a0);
extern void func_801775E0(s32 a0, s32 a1);
void func_80176734(s32 param_1)
{
  int new_var;
register u8 *b __asm__("$19");
register u8 *p __asm__("$17");
register u8 *q __asm__("$18");
register u8 *r __asm__("$20");
register s32 f1 __asm__("$21");
register s32 arg __asm__("$22");
  s32 res;
register s32 v __asm__("$2");
  s32 f2;
register s32 e __asm__("$5");
  u8 *e2;
  s32 t;
  u8 c;
  u16 uv;
  u8 n;
  s32 z;
  b = D_8011F7A8;
  arg = param_1;
  p = b + 0x48;
  q = b + 0xE0;
  r = D_80078E78;
  e = *((s32 *) ((b + (((s16) param_1) * 4)) + 0x28));
  e2 = (u8 *) (e + 0x3C);
  if (D_801152BA != 0)
  {
    u8 d;
    c = D_8011F7B0;
    if (c < 0x80)
    {
      d = c + 0x80;
    }
    else
    {
      d = (~c) + 0x80;
    }
    e2[4] = d;
    *((u8 *) (e + 4)) = d;
    b[8] += D_80115214;
  }
  else
  {
    *((u8 *) (e + 0x40)) = 0x80;
    *((u8 *) (e + 4)) = 0x80;
  }
  if (q[0x48] != 0)
  {
    e = *((s32 *) ((b + (((s16) arg) * 4)) + 0x28));
    *((u8 *) (e + 0xD)) = D_8018A2D8[q[0x48]];
    if (q[0x48] >= 4)
    {
      u8 s = p[0x48];
      e = *((s32 *) ((b + (((s16) arg) * 4)) + 0x28));
      if (s & 0x80)
      {
        *((s16 *) (e + 0x20)) = D_8018A238;
        func_800183E0((s32) (&D_800D45D4));
      }
      else
        if (s != 0)
      {
        *((s16 *) (e + 0x20)) = D_8018A22A[s];
        func_800183E0(D_8018A2E4[p[0x48]]);
      }
      n = q[0x48];
      if (n == 5)
      {
        if (p[0x48] == 0)
        {
          q[0x48] = 0;
        }
        else
        {
          q[0x48] = n + 1;
        }
      }
      else
        if (n == 10)
      {
        q[0x48] = 0;
      }
      else
      {
        q[0x48] = n + 1;
      }
    }
    else
    {
      q[0x48] = q[0x48] + 1;
    }
  }
  else
    if (p[0x48] != r[0x48])
  {
    if ((p[0x48] == 0) && (r[0x48] != 0))
    {
      q[0x48] = 5;
    }
    else
    {
      q[0x48] = 0;
    }
    p[0x48] = r[0x48];
    {
      u8 m;
      e = *((s32 *) ((b + (((s16) arg) * 4)) + 0x28));
      m = q[0x48];
      q[0x48] = m + 1;
      *((u8 *) (e + 0xD)) = D_8018A2D8[m];
    }
  }
  if ((*((s16 *) (p + 0x2E))) == (*((s16 *) (r + 0x2E))))
  {
    if ((*((s16 *) (q + 0x2E))) == 0)
    {
      goto L9C0;
    }
    *((s16 *) (q + 0x2E)) = 0;
  }
  else
  {
    *((s16 *) (p + 0x2E)) = *((s16 *) (r + 0x2E));
    *((s16 *) (q + 0x2E)) = 1;
  }
  L984:
  {
    s32 e5;
    s32 tt;
    e5 = *((s32 *) ((b + (((s16) arg) * 4)) + 0x28));
    tt = (*((u16 *) (p + 0x2E))) << 16;
    if (tt != 0)
    {
      *((u8 *) (e5 + 0x49)) = D_8018A2CC[tt >> 20];
    }
    else
    {
      *((u8 *) (e5 + 0x49)) = 0xA0;
    }
  }

  L9C0:
  if (((*((s16 *) (p + 0x1E))) & 0x8000) != ((*((s16 *) (r + 0x1E))) & 0x8000))
  {
    if (((*((s16 *) (p + 0x1E))) & 0x8000) != 0)
    {
      *((s16 *) (p + 0x1E)) = 0;
      func_800183E0((s32) (&D_800D43D4));
    }
    else
    {
      *((s16 *) (p + 0x1E)) = -0x8000;
      func_800183E0((s32) (&D_800D4414));
    }
  }

  {
    u8 g = D_800B9A13;
    if (g != 3)
    {
      s32 t2 = b[7] != g;
      f1 = t2;
      if (t2 != 0)
      {
        b[7] = g;
      }
    }
    else
    {
      f1 = 0;
    }
  }
  res = 0;
  switch (r[0x48])
  {
    case 3:
      if (func_801619D0(&D_80126B58) != 0)
    {
      res = 0xFF;
    }
      break;

    case 4:
      if (func_80161A00((s32) (&D_80126B58)) != 0)
    {
      res = 0xFF;
    }
      break;

    case 5:
      if (func_80161A30((s32) (&D_80126B58)) != 0)
    {
      res = 0xFF;
    }
      break;

    case 6:
      if (func_80161A60((s32) (&D_80126B58)) != 0)
    {
      res = 0xBA;
    }
      break;

  }

  v = res;
  if (v != 0)
  {
register s32 num __asm__("$4");
register s32 one __asm__("$3");
    u8 rt;
    one = 1;
    num = (D_80126D20 << 7) / v;
    rt = r[0x48];
    q[0x47] = one;
    p[0x4B] = rt | 0xF0;
    p[0x47] = num;
    goto L88;
  }
  if (p[0x4B] >= 0xF0)
  {
    p[0x4B] = 0;
  }
  if (D_80126CE0 != 0)
  {
    uv = (u16) D_80126CE0;
    p[0x4B] = uv;
    f2 = p[0x47] != ((u8) uv);
  }
  else
  {
    uv = r[0x47];
    f2 = 0;
    if ((p[0x47] != uv) || (p[0x47] == 0x80))
    {
      f2 = 1;
    }
    if ((r[0x47] != 0) && (p[0x4B] != 0))
    {
      p[0x4B] = 0;
      p[0x47] = r[0x47];
    }
  }
  if (f2 != 0)
  {
    goto BIG;
  }
  new_var = f1 != 0;
  if (new_var)
  {
    goto BIG;
  }
  if (q[0x47] == 0)
  {
    goto L8C;
  }
  if (f1 == 0)
  {
    goto CLR;
  }
  BIG:
  if (((s32) p[0x47]) < ((s16) uv))
  {
    goto SET;
  }
  else
  {
    p[0x47] += (((s16) uv) != 0) ? (-3) : (-8);
    if ((p[0x47] == 0) || (p[0x47] > 0x80))
    {
      p[0x47] = 0;
      p[0x4B] = 0;
    }
    else
      if (((s32) p[0x47]) < ((s16) uv))
    {
      SET:
      p[0x47] = uv;

    }
  }

  q[0x47] = 1;
  goto L88;
  CLR:
  q[0x47] = 0;

  L88:
  L8C:
  z = (b[7] != 0) << 8;


  *((s16 *) ((*((s32 *) ((b + (((s16) arg) * 4)) + 0x28))) + 0x32)) = ((*((u16 *) (b + 0x12))) + z) + 5;
  func_801775E0((*((s32 *) ((b + (((s16) arg) * 4)) + 0x28))) + 0x64, (s16) (((*((u16 *) (b + 0x12))) + z) + 9));
}
