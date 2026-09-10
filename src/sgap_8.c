#include "common.h"

extern s32 D_800C73D8[];
extern s16 D_800B9B36;
extern u8 D_800AE614;
extern s16 D_80079590[];
extern u8 D_80079592[];
extern s16 D_80079596[][26];
extern s16 D_80079598[];
extern s16 D_8007959A[];
extern s16 D_8007959C[];
extern s16 D_8007959E[];
extern u8 *D_800A6578;
extern u8 *D_800A6580;
extern s32 D_800A6584;
extern s16 D_800A6434;
extern s16 D_800B9B58[];
extern u8 D_800A4620[];
s32 func_80040DE8(s32 param_1, u16 param_2, u16 param_3, s16 param_4)
{
  s32 base;
  s32 vab;
  s16 id;
  s16 i;
  u8 k;
  u8 *p;
  s32 new_var;
  s32 q1;
  s32 qt;
  u32 a;
  u32 b;
  u16 vl;
  u16 vr;
  u8 pan;
  s32 o1;
  s32 o2;
  s32 o3;
  base = D_800C73D8[param_1 & 0xFF];
  id = param_1;
  D_800B9B36 = id;
  vab = (param_1 & 0xFF00) >> 8;
  base += vab * 0xB0;
  vl = param_2;
  new_var = base;
  vr = param_3;
  if (vl == 0)
  {
    vl = 1;
  }
  if (vr == 0)
  {
    vr = 1;
  }
  *((u16 *) (new_var + 0x58)) = vl;
  *((u16 *) (new_var + 0x5A)) = vr;
  if ((*((u16 *) (new_var + 0x58))) > 0x7F)
  {
    *((u16 *) (new_var + 0x58)) = 0x7F;
  }
  if ((*((u16 *) (new_var + 0x5A))) > 0x7F)
  {
    *((u16 *) (new_var + 0x5A)) = 0x7F;
  }
  if (param_4 == 1)
  {
    for (i = 0; i < D_800AE614; i++)
    {
      o1 = i * 52;
      if ((*((s16 *) (((s32) D_80079596) + o1))) == id)
      {
        k = *((u8 *) (new_var + 0x17));
        if ((*((s16 *) (((s32) D_8007959A) + o1))) == (*((u8 *) ((new_var + k) + 0x37))))
        {
          if ((*((s16 *) (((s32) D_8007959E) + o1))) == (*((u8 *) (new_var + 0x26))))
          {
            q1 = ((*((s16 *) (((s32) D_80079590) + o1))) * (*((s16 *) ((new_var + 0x60) + (k * 2))))) / 0x7F;
            qt = q1 * 0x3FFF;
            b = (D_800A6580[0x18] * qt) / 0x3F01;
            p = (u8 *) (((((*((s16 *) (((s32) D_80079598) + o1))) * 0x10) + (*((s16 *) (((s32) D_8007959C) + o1)))) * 0x20) + D_800A6584);
            a = ((b * D_800A6578[((*((s16 *) (((s32) D_8007959A) + o1))) * 0x10) + 1]) * p[2]) / 0x3F01;
            b = (a * (*((u16 *) (new_var + 0x58)))) / 0x7F;
            a = (a * (*((u16 *) (new_var + 0x5A)))) / 0x7F;
            pan = p[3];
            if (pan < 0x40)
            {
              vr = (a * pan) / 0x3F;
              vl = b;
            }
            else
            {
              vl = (b * (0x7F - pan)) / 0x3F;
              vr = a;
            }
            o2 = i * 52;
            pan = D_800A6578[((*((s16 *) (((s32) D_8007959A) + o2))) * 0x10) + 4];
            if (pan < 0x40)
            {
              vr = (vr * pan) / 0x3F;
            }
            else
            {
              vl = (vl * (0x7F - pan)) / 0x3F;
            }
            o3 = i * 52;
            pan = *((u8 *) (((s32) D_80079592) + o3));
            if (pan < 0x40)
            {
              vr = (vr * pan) / 0x3F;
            }
            else
            {
              vl = (vl * (0x7F - pan)) / 0x3F;
            }
            if (D_800A6434 == 1)
            {
              if (vl < vr)
              {
                vl = vr;
              }
              else
              {
                vr = vl;
              }
            }
            vl = (vl * vl) / 0x3FFF;
            vr = (vr * vr) / 0x3FFF;
            D_800B9B58[i * 8] = vl;
            D_800B9B58[(i * 8) + 1] = vr;
            D_800A4620[i] |= 3;
          }
        }
      }
    }

  }
  return D_800B9B36;
}

extern s32 D_800C73D8[];
extern s16 D_800B9B36;

s32 func_80041354(s32 param_1, u16 *param_2, u16 *param_3)
{
    s32 base;
    s16 *attr;
    s32 vab;

    base = D_800C73D8[param_1 & 0xFF];
    attr = &D_800B9B36;
    *attr = param_1;
    vab = (param_1 & 0xFF00) >> 8;
    base += vab * 0xB0;
    *param_2 = *(u16 *)(base + 0x58);
    *param_3 = *(u16 *)(base + 0x5A);
    return *attr;
}

extern s32 D_800C73D8[];
extern s16 D_800B9B36;

s32 func_800413B8(s32 param_1)
{
    s32 base;
    s32 vab;

    do { base = D_800C73D8[param_1 & 0xFF]; } while (0);
    D_800B9B36 = param_1;
    vab = (param_1 & 0xFF00) >> 8;
    base += vab * 0xB0;
    return *(s16 *)(base + 0x58);
}


extern s32 D_800C73D8[];
extern s16 D_800B9B36;

s32 func_80041400(s32 param_1)
{
    s32 base;
    s32 vab;

    do { base = D_800C73D8[param_1 & 0xFF]; } while (0);
    D_800B9B36 = param_1;
    vab = (param_1 & 0xFF00) >> 8;
    base += vab * 0xB0;
    return *(s16 *)(base + 0x5A);
}


extern u8   D_800AE614;
extern s16  D_80079596[][26];
extern u16  D_800B9B3A;
extern void func_80040868(s32);

void func_80041448(s16 param_1)
{
    u8 i;

    for (i = 0; i < D_800AE614; i++) {
        if (D_80079596[i][0] == param_1) {
            D_800B9B3A = i;
            func_80040868(0);
        }
    }
}
