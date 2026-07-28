















typedef struct 
{
  s16 x;
  s16 y;
} Hw4;
typedef struct 
{
  u16 f0;
  s16 f2;
} Prim4;
extern s16 func_8014168C(s16);
extern short D_800B9A02;
extern u16 D_80115110;
extern u8 D_80115140[];
extern s16 D_8011514E;
extern u8 D_80115158[];
extern Hw4 D_8011516A[];
extern Prim4 D_8018798C[];
extern Prim4 *D_80187A80[];
extern u8 D_80115143;
extern Prim4 D_8018793C[];
extern s16 D_80187E9C[];
extern s16 D_80187EAC[];
extern u16 D_801879BC;
extern u16 D_801879BE;
extern s32 *func_80140D68(s32 *, Prim4 *, s32, s32, s32);
s32 *func_80140958(ot, i, n)
s32 *ot;
s16 i;
s16 n;
{
  typedef struct 
  {
    u32 *ot;
    u32 pad[4];
  } Env_80140958;
  extern Env_80140958 D_800AE7BC[];
  Prim4 *p;
  s16 t;
  s32 c3;
register u16 *a __asm__("$20");
register u16 *b __asm__("$21");
register u16 *c __asm__("$23");
register u16 *e __asm__("$22");
register u16 *pb __asm__("$10");
register u32 m24 __asm__("$8");
register u32 mhi __asm__("$9");
register s32 eight __asm__("$2");
  if (i < n)
  {
    c3 = 3;
    a = &D_80115110;
    b = a + 5;
    c = a + 3;
    e = &D_801879BE;
    do
    {
      if (((a[0] == 0) && (a[1] != c3)) && (a[1] < 6))
      {
        if (i == a[5])
        {
          ot = func_80140D68(ot, &D_8018793C[i], i, D_80187E9C[a[3] & 7], 0);
        }
      }
      else
      {
        p = D_80187A80[i];
        if (((p != 0) && (i == b[0])) && (i != 6))
        {
          if ((i == 2) && ((*((s16 *) (b + 7))) != 0))
          {
            p = D_8018798C;
          }
          if (i != c3)
          {
            t = ((s32 (*)(s16)) func_8014168C)(i) * 2;
          }
          else
          {
            t = ((*((u8 *) (&D_8011514E))) - D_80115143) * 2;
          }
          ot = func_80140D68(ot, p, i, D_80187EAC[c[0] & 7], t);
          if (((i == 2) && ((*((s16 *) (c + 9))) == 1)) && ((*((s16 *) (c + 12))) != 0))
          {
            ot = func_80140D68(ot, p, 2, 8, ((*((s16 *) (c + 12))) & 0xF) * 2);
          }
        }
      }
      if (i == c3)
      {
        s32 m = b[0];
        if ((m == 3) && ((b[-2] & 8) != 0))
        {
          s32 k;
          u8 *q = ((u8 *) ot) + 0x14;
          s16 j;
          s16 y;
          j = 0;
          k = m;
          mhi = 0xFF000000;
          pb = (u16 *) (&D_800B9A02);
          m24 = 0xFFFFFF;
          for (; j < 2; j++)
          {
            if (j == 0)
            {
              if (D_80115140[k] == 0)
              {
                continue;
              }
              q[-7] = 0x30;
              y = (*e) - 4;
            }
            else
            {
              s32 k2 = k * 2;
              if ((((s8 *) D_80115158)[k2] - ((s8 *) D_80115140)[k]) < 2)
              {
                continue;
              }
              q[-7] = 0x38;
              y = (*e) + 3;
            }
            *((s16 *) (q - 10)) = y;
__asm__("" ::: "memory");
            *((u32 *) ot) = 0x4000000;
            q[-8] = 0x78;
            *((u32 *) (q - 0x10)) = 0x64808080;
            *((s16 *) (q - 6)) = 0x4056;
            *((s16 *) (q - 0xC)) = (D_801879BC + ((u16) D_8011516A[m].x)) + 0x4A;
            eight = 8;
            *((s16 *) (q - 2)) = eight;
            *((s16 *) (q - 4)) = eight;
            *((u32 *) ot) = ((*((u32 *) ot)) & mhi) | (D_800AE7BC[*pb].ot[2] & m24);
            {
register u32 *op __asm__("$4");
              op = D_800AE7BC[*pb].ot;
              op[2] = (op[2] & mhi) | (((u32) ot) & m24);
            }
            q += 0x14;
            ot += 5;
          }

        }
      }
      i = i + 1;
    }
    while (i < n);
  }
  return ot;
}