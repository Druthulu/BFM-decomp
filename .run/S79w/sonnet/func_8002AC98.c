extern s32 func_800291B4(s32);
extern u16 D_800A6588[];
extern u8 D_8010F46C[];
extern u8 D_80078EBA;
void func_8002AC98(void)
{
register u16 *base __asm__("$20");
  s16 i;
  s16 val;
  s32 t;
  s32 r;
  s32 idx;
  s16 rc;
  s32 b;
  base = D_800A6588;
  if (D_80078EBA == 0)
  {
    for (i = 0; i < 0x40; i++)
    {
      t = func_800291B4(((s16) i) + 0x63) & 0xF;
      if (t != 0)
      {
        r = rand() & 0x1F;
        switch (t)
        {
          case 1:
            rc = r;
            if ((rc != 0) && (rc != 0xB))
          {
            b = base[i] - 0xB;
            { s32 xt = r + b; val = xt; }
          }
          else
          {
            val = ((s16) base[i]) >> 1;
          }
            break;

          case 2:
            if (r != 0)
          {
            b = base[i] - 0xB;
            { s32 xt = r + b; val = xt; }
          }
            break;

          case 3:
            rc = r;
            if ((rc != 0) && (rc != 0xB))
          {
            b = base[i] - 0xB;
            { s32 xt = r + b; val = xt; }
          }
          else
          {
            val = base[i] * 2;
          }
            break;

        }

        idx = i + 1;
        if (val < (*((s16 *) (&D_8010F46C[idx * 8]))))
        {
          base[i] = *((s16 *) (&D_8010F46C[idx * 8]));
        }
        else
          if (((*((s16 *) (&D_8010F46C[idx * 8]))) * 4) < val)
        {
          rc = 4;
          base[i] = (*((s16 *) (&D_8010F46C[idx * 8]))) * rc;
        }
        else
        {
          base[i] = val;
        }
      }
    }

  }
}
