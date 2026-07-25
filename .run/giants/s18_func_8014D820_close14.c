
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
typedef struct 
{
  u16 x;
  u16 y;
  u16 z;
  u16 w;
} V4;
typedef struct 
{
  u16 x;
  u16 y;
  u16 z;
  u16 w;
  s32 pad[4];
  s32 f18;
  s32 f1C;
  s32 f20;
} Desc;
typedef struct Ent
{
  u16 f0;
  u16 f2;
  u16 f4;
  u16 x;
  u16 f8;
  u16 y;
  u16 fC;
  u16 z;
  u8 p10[0x10];
  s32 f20;
  u8 p24[0x34];
  s32 f58;
  u16 f5C;
  u16 f5E;
  u8 p60[0x10C - 0x60];
} Ent;
extern s16 currentLocationId;
extern Ent D_801202A0[];
extern u8 D_8018876C[];
extern u16 D_801152A8;
extern u16 D_801152AC;
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014DCE0(s32 a0, s32 a1, s32 a2);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
s32 func_8014D820(s32 a0, u16 *a1, u16 *a2x)
{
  int new_var2;
  s32 new_var;
register u16 *a2 __asm__("$7");
  V4 out[3];
  V4 pos;
  Desc desc;
  Ent *ent;
  Ent *p;
  s32 dx;
  s32 dz;
  s32 ex;
  s32 ez;
  s32 r1;
  s32 r2;
  s32 r3;
  s32 ang;
  s32 x0;
  s32 y0;
  s32 z0;
  s32 tx;
  s32 tz;
  s32 r;
  s32 t;
register s32 u __asm__("$2");
  s32 a0v;
__asm__ __volatile__("" : "=r"(a2) : "0"(a2x));
  t = a2[0];
  u = a1[0];
  dx = t - u;
  a1 = a1;
__asm__ __volatile__("" : "=r"(a0v) : "0"(a0));
  t = a2[2];
  u = a1[2];
  dz = t - u;
  if (((s16) (dx | dz)) == 0)
  {
    goto fail;
  }
  desc.x = dx;
  desc.y = a2[1] - a1[1];
  desc.z = a2[2] - a1[2];
  ent = *((Ent **) (a0v + 0x170));
  if (ent->f0 == 0)
  {
    goto fail;
  }
  if ((ent->f5C & 0x1000) == 0)
  {
    goto fail;
  }
  if (ent->f58 == 0)
  {
    goto fail;
  }
  if (((s32 (*)(s32, s32, s32)) func_80135A4C)(ent->f20, ent->f58, (s32) a1) == 0)
  {
    goto fail;
  }
  ex = ent->x - (*((u16 *) (a0v + 6)));
  new_var = dz;
  ez = ent->z - (*((u16 *) (a0v + 0xE)));
  r1 = (s16) ratan2((s16) new_var, (s16) dx);
  r2 = (s16) ratan2((s16) ez, (s16) ex);
  r3 = (s16) func_80012A60(r1, r2);
  if (r3 >= 0x400)
  {
    goto fail;
  }
  desc.f20 = 0;
  desc.f1C = 0;
  desc.f18 = 0;
  pos.x = (x0 = ent->x);
  z0 = ent->z;
  tx = x0 + desc.x;
  y0 = ent->y;
  pos.y = y0;
  desc.y = (y0 + desc.y) + 8;
  tz = z0 + desc.z;
  pos.z = z0;
  desc.x = tx;
  desc.z = tz;
  if (currentLocationId != 0x3008)
  {
    for (p = D_801202A0; p < (D_801202A0 + 96); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->f0 == 0)
      {
        continue;
      }
      if (p->f5C == 0)
      {
        continue;
      }
      if (p->f58 == 0)
      {
        continue;
      }
      func_80135888(p->f20, p->f58, (s32) (&pos), (s32) (&desc));
    }

  }
  else
  {
    ang = ratan2(((s16) x0) - ((s16) tx), ((s16) z0) - ((s16) tz)) & 0xFFF;
    func_800139C8(ang, D_8018876C, &out[0]);
    func_800139C8((s16) (ang - 0x155), D_8018876C, &out[1]);
    func_800139C8((s16) (ang + 0x155), D_8018876C, &out[2]);
    out[0].x += pos.x;
    out[0].y = pos.y;
    out[0].z += pos.z;
    out[1].x += pos.x;
    out[1].y = pos.y;
    out[1].z += pos.z;
    out[2].x += pos.x;
    out[2].y = pos.y;
    out[2].z += pos.z;
    for (p = D_801202A0; p < (D_801202A0 + 96); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->f0 == 0)
      {
        continue;
      }
      if (p->f5C == 0)
      {
        continue;
      }
      if (p->f58 == 0)
      {
        continue;
      }
      if (func_8014DCE0((s32) p, (s32) (&pos), (s32) (&out[0])) != 0)
      {
        __builtin_memcpy((void *) ((s32) (&desc)), (void *) ((s32) (&pos)), 8);
      }
    }

  }
  r = func_80133784(0, &pos, (s32) (&desc));
  if ((r == 0) || ((r == 0x2000) && ((D_801152A8 | D_801152AC) == 0)))
  {
    ent->x = desc.x - desc.f18;
    ent->y = desc.y;
    ent->z = desc.z - desc.f20;
    desc.x -= pos.x;
    desc.y -= pos.y;
    desc.z -= pos.z;
    *((u16 *) (a0v + 6)) = a1[0] + desc.x;
    new_var2 = desc.y + 0x10;
    *((u16 *) (a0v + 0xA)) = a1[1] + new_var2;
    *((u16 *) (a0v + 0xE)) = a1[2] + desc.z;
  }
  else
  {
    *((u16 *) (a0v + 6)) = a1[0];
    if (1)
    {
      *((u16 *) (a0v + 0xA)) = a1[1] + 0x10;
    }
    *((u16 *) (a0v + 0xE)) = a1[2];
  }
  return 1;
  fail:
  *((s32 *) (a0v + 0x170)) = 0;

  return 0;
}
