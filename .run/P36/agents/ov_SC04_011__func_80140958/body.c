s32 *func_80140958(ot, i, n)
s32 *ot;
s16 i;
s16 n;
{

    extern s16 D_8011514E;
    extern u8 D_80115158[];
    extern Hw4 D_8011516A[];
    extern Prim4 D_8019129C[];
    extern Prim4 *D_80191390[];
    extern u8 D_80115143;
    extern Prim4 D_8019124C[];
    extern s16 D_801917AC[];
    extern s16 D_801917BC[];
    extern u16 D_801912CC;
    extern u16 D_801912CE;
  extern Env_80140958 D_800AE7BC[];
  Prim4 *p;
  s16 t;
  s32 c3;
u16 *a;
u16 *b;
u16 *c;
u16 *e;
u16 *pb;
u32 m24;
u32 mhi;
  if (i < n)
  {
    c3 = 3;
    a = &D_80115110;
    b = a + 5;
    c = a + 3;
    e = &D_801912CE;
    do
    {
      if (((a[0] == 0) && (a[1] != c3)) && (a[1] < 6))
      {
        if (i == a[5])
        {
          ot = func_80140D68(ot, &D_8019124C[i], i, D_801917AC[a[3] & 7], 0);
        }
      }
      else
      {
        p = D_80191390[i];
        if (((p != 0) && (i == b[0])) && (i != 6))
        {
          if ((i == 2) && ((*((s16 *) (b + 7))) != 0))
          {
            p = D_8019129C;
          }
          if (i != c3)
          {
            t = ((s32 (*)(s16)) func_8014168C)(i) * 2;
          }
          else
          {
            t = ((*((u8 *) (&D_8011514E))) - D_80115143) * 2;
          }
          ot = func_80140D68(ot, p, i, D_801917BC[c[0] & 7], t);
          if (((i == 2) && ((*((s16 *) (c + 9))) == 1)) && ((*((s16 *) (c + 12))) != 0))
          {
            ot = func_80140D68(ot, p, 2, 8, ((*((s16 *) (c + 12))) & 0xF) * 2);
          }
        }
      }
      if (i == c3)
      {
        s32 m = b[0];
        /* [L1] compare against `i`, NOT against the literal 3. */
        if ((m == i) && ((b[-2] & 8) != 0))
        {
          s16 j;
          s32 k;
          s32 t3v;
          u8 *q = ((u8 *) ot) + 0x14;
          register s16 size __asm__("$2");  // !FAKE: pin $2 size — a hard-reg set is may_not_optimize, so loop.c (scan_loop, loop.c:649) keeps the in-loop li 8 (P36 S103 c48 minimum-lever)
          j = 0;
          k = m;
          t3v = m * 4;
          pb = (u16 *) (&D_800B9A02);
          m24 = 0xFFFFFF;
          mhi = 0xFF000000;
          for (; j < 2; j++)
          {
            if (j == 0)
            {
              if (D_80115140[k] == 0)
              {
                continue;
              }
              q[-7] = 0x30;
              *((s16 *) (q - 10)) = (*e) - 4;
            }
            else
            {
              s32 k2 = k * 2;
              if ((((s8 *) D_80115158)[k2] - ((s8 *) D_80115140)[k]) < 2)
              {
                continue;
              }
              q[-7] = 0x38;
              *((s16 *) (q - 10)) = (*e) + 3;
            }
            *((u32 *) ot) = 0x4000000;
            q[-8] = 0x78;
            *((u32 *) (q - 0x10)) = 0x64808080;
            *((s16 *) (q - 6)) = 0x4056;
            *((s16 *) (q - 0xC)) = (D_801912CC + ((u16) *((u16 *) (((u8 *) D_8011516A) + t3v)))) + 0x4A;
            size = 8;
            *((s16 *) (q - 2)) = size;
            *((s16 *) (q - 4)) = size;
            *((u32 *) ot) = ((*((u32 *) ot)) & mhi) | (D_800AE7BC[*pb].ot[2] & m24);
            {
u32 *op;
u32 w;
              op = D_800AE7BC[*pb].ot;
              w = op[2];
              w &= mhi;
              w |= ((u32) ot) & m24;
              op[2] = w;
            }
            q += 0x14;
            ot += 5;
            __asm__ __volatile__("" :: "r"(j));  // !FAKE: keepalive j — +3 depth-3 refs so allocno_compare (global.c:604) ranks j above k and j takes $a2 (P36 S103 c48 minimum-lever)
          }

        }
      }
      i = i + 1;
    }
    while (i < n);
  }
  return ot;
}
