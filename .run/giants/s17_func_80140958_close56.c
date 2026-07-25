
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
  u32 addr : 24;
  u32 len : 8;
} P_TAG;
typedef struct 
{
  u32 tag;
  u32 rgbc;
  s16 x0;
  s16 y0;
  u8 u0;
  u8 v0;
  u16 clut;
  s16 w;
  s16 h;
} Sprt;
extern u16 D_80115110[];
extern u8 D_80115140[];
extern u8 D_80115143;
extern u8 D_8011514E;
extern u8 D_80115158[];
extern u8 D_8011516A[];
extern void *D_80187A80[];
extern s16 D_80187E9C[];
extern s16 D_80187EAC[];
extern u8 D_8018793C[];
extern u8 D_8018798C[];
extern u16 D_801879BC;
extern u16 D_801879BE;
extern u16 D_800B9A02;
extern u8 D_800AE7BC[];
extern s32 func_8014168C(s32 a0);
extern u32 *func_80140D68(u32 *a0, void *a1, s32 a2, s32 a3, s32 a4);
u32 *func_80140958(u32 *ot, short idx, short n)
{
  int new_var4;
  int new_var5;
  unsigned short new_var2;
  int new_var;
  u16 new_var3;
  if (idx < n)
  {
    u16 *py = &D_801879BE;
    do
    {
      new_var = 3;
      if (((D_80115110[0] == 0) && (D_80115110[1] != 3)) && (D_80115110[1] < 6))
      {
        if (idx == D_80115110[5])
        {
          ot = func_80140D68(ot, &D_8018793C[idx * 4], idx, D_80187E9C[D_80115110[new_var] & 7], 0);
        }
      }
      else
      {
        void *pk = D_80187A80[idx];
        new_var5 = new_var;
        if (((pk != 0) && (idx == D_80115110[5])) && (idx != 6))
        {
          s32 v;
          if ((idx == 2) && (((s16 *) D_80115110)[12] != 0))
          {
            pk = D_8018798C;
          }
          if (idx == new_var5)
          {
            v = (D_8011514E - D_80115143) * 2;
          }
          else
          {
            v = func_8014168C(idx) * 2;
          }
          new_var3 = D_80115110[new_var5];
          ot = func_80140D68(ot, pk, idx, D_80187EAC[new_var3 & 7], (s16) v);
          if (((idx == 2) && (((s16 *) D_80115110)[12] == 1)) && (((s16 *) D_80115110)[15] != 0))
          {
            ot = func_80140D68(ot, pk, 2, 8, (((s16 *) D_80115110)[15] & 0xF) * 2);
          }
        }
      }
      new_var4 = new_var;
      if (idx == new_var4)
      {
        u16 k = D_80115110[5];
        if ((k == new_var4) && ((D_80115110[3] & 8) != 0))
        {
          short i;
          u16 *pn;
          unsigned short k2 = k * 2;
          s32 k4;
          ((Sprt *) ot)->v0 = 0x30;
          k4 = k * 4;
          pn = &D_800B9A02;
          for (i = 0; i < 2; i++)
          {
            Sprt *p;
            s32 nn;
            u32 *q;
            if (i == 0)
            {
              if (D_80115140[k] == 0)
              {
                continue;
              }
              ((Sprt *) ot)->y0 = (*py) - 4;
              if (1)
              {
              }
            }
            else
            {
              if ((((s8) D_80115158[k2]) - ((s8) D_80115140[k])) < 2)
              {
                continue;
              }
              ((Sprt *) ot)->v0 = 0x38;
              k2 = 3;
              ((Sprt *) ot)->y0 = (*py) + k2;
            }
            ((Sprt *) ot)->tag = 0x4000000;
            new_var2 = (D_801879BC + (*((u16 *) (&D_8011516A[k4])))) + 0x4A;
            ((Sprt *) ot)->rgbc = 0x64808080;
            ((Sprt *) ot)->u0 = 0x78;
            ((Sprt *) ot)->clut = 0x4056;
            (*((Sprt *) ot)).x0 = new_var2;
            ((Sprt *) ot)->h = 8;
            ((Sprt *) ot)->w = 8;
            nn = 4 * (((u32) (*pn)) * 5);
            q = (u32 *) ((*((s32 *) (&D_800AE7BC[nn]))) + 8);
            ((P_TAG *) ot)->addr = (u32) ((u32) ((P_TAG *) q)->addr);
            nn = ((u32) (*pn)) * 0x14;
            q = (u32 *) ((*((s32 *) (&D_800AE7BC[nn]))) + 8);
            ((P_TAG *) q)->addr = (u32) ot;
            ot += 5;
          }

        }
      }
      idx++;
    }
    while (idx < n);
  }
  return ot;
}
