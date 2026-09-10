short func_8016CBC0(void)
{

    extern Blk_8016CBC0 D_801EE1E0[];
  Poly_8016CBC0 p0;
  Poly_8016CBC0 p1;
  Mtx8_8016CBC0 mtx;
  Blk_8016CBC0 *blk;
  Rec_8016CBC0 *sub;
  Rec_8016CBC0 *pv;
  unsigned int uVar9;
  unsigned int w9;
  unsigned int uc;
  unsigned int a2;
  int col;
  int iVar3;
  int w3;
  unsigned int w3b;
  short count;
  short i;
  mtx = (*(Mtx8_8016CBC0 *)&D_800AE620);
  count = 0;
  p1.tag = 0x50000000;
  p0.tag = 0x50000000;
  p1.col[3].b = 0;
  p1.col[3].g = 0;
  p1.col[3].r = 0;
  p1.col[1].b = 0;
  p1.col[1].g = 0;
  p1.col[1].r = 0;
  p0.col[2].b = 0;
  p0.col[2].g = 0;
  p0.col[2].r = 0;
  p0.col[0].b = 0;
  p0.col[0].g = 0;
  p0.col[0].r = 0;
  for (i = 0; i < 8; i++)
  {
    blk = &D_801EE1E0[i];
    if (blk->f0 != 0)
    {
      sub = blk->ent;
      uVar9 = blk->f1;
      iVar3 = blk->f2;
      col = blk->f3;
      count = count + 1;
      w3 = iVar3 - 1;
      iVar3 = w3 + 0;
      if (w3 != (-1))
      {
        do
        {
          pv = &sub[(short) uVar9];
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[0].x = a;
            b = pv->h[3];
            p1.v[1].x = b;
            p0.v[1].x = (p1.v[0].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[0].y = a;
            b = pv->h[4];
            uc = ((unsigned) (col & 0xFF)) >> 3;
            p1.v[1].y = b;
            p0.v[1].y = (p1.v[0].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
            w9 = uVar9 - 1;
            uVar9 = w9 + 0;
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[0].z = a;
            b = pv->h[5];
            p1.col[0].g = col;
            p0.col[1].g = col;
            p1.col[0].b = uc;
            p0.col[1].b = uc;
            p1.col[0].r = uc;
            p0.col[1].r = uc;
            p1.v[1].z = b;
            p0.v[1].z = (p1.v[0].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          if (((int) (w9 << 16)) < 0)
          {
            uVar9 = 0xF;
          }
          pv = &sub[(short) uVar9];
          col = col - 0xF;
          a2 = (unsigned) (col & 0xFF);
          a2 = a2 >> 3;
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[2].x = a;
            b = pv->h[3];
            p1.v[3].x = b;
            p0.v[3].x = (p1.v[2].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[2].y = a;
            b = pv->h[4];
            p1.v[3].y = b;
            p0.v[3].y = (p1.v[2].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[2].z = a;
            b = pv->h[5];
            p1.col[2].g = col;
            p0.col[3].g = col;
            p1.col[2].b = a2;
            p0.col[3].b = a2;
            p1.col[2].r = a2;
            p0.col[3].r = a2;
            p1.v[3].z = b;
            p0.v[3].z = (p1.v[2].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          func_80017758(&p0, &mtx);
          func_80017758(&p1, &mtx);
          uc = iVar3 - 1;
          w3b = uc;
          iVar3 = w3b + 0;
        }
        while (((short) w3b) != (-1));
      }
    }
  }

  return count;
}
