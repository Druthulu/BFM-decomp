/* func_80132784 — shared body (overlay slot 0x80128158, h_exact 040f7b51). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_80020F34(s32 a0, s32 a1);
extern void func_80054514(s32 a0, s32 a1);
void func_80132784(s32 a0, s32 a1, u32 a2)
{
  s32 s7 = a0;
  s32 s0p = a1;
  u32 s2v = a2;
  s32 s6;
  s32 s1m;
  s16 sVar1;
  u8 buf[0xC0];
  if (((*((s32 *) (s7 + 0x20))) != 0) || ((*((s32 *) (s0p + 0x20))) != 0))
  {
    s6 = *((s32 *) (s0p + 0x20));
    s1m = *((s32 *) (s6 + 0x20));
    if (s1m != 0)
    {
      *((s32 *) (buf + 0x48)) = *((s32 *) (s6 + 0x78));
      *((s32 *) (buf + 0x00)) = 0;
      if (((*((u16 *) (s6 + 0x2C))) & 1) != 0)
      {
        *((Blk16 *) (buf + 0x04)) = *((Blk16 *) (s6 + 0x34));
        *((Blk16 *) (buf + 0x14)) = *((Blk16 *) (s6 + 0x44));
      }
      else
      {
        func_80049CAC(s6 + 0x10, (s32) (buf + 0x04));
        sVar1 = (*((s16 *) (s0p + 6))) + (*((s16 *) (s0p + 0x50)));
        *((s16 *) (s6 + 8)) = sVar1;
        *((s32 *) (buf + 0x18)) = (s32) sVar1;
        sVar1 = (*((s16 *) (s0p + 0xA))) + (*((s16 *) (s0p + 0x52)));
        *((s16 *) (s6 + 0xA)) = sVar1;
        *((s32 *) (buf + 0x1C)) = (s32) sVar1;
        sVar1 = (*((s16 *) (s0p + 0xE))) + (*((s16 *) (s0p + 0x54)));
        *((s16 *) (s6 + 0xC)) = sVar1;
        *((s32 *) (buf + 0x20)) = (s32) sVar1;
        *((Blk16 *) (s6 + 0x34)) = *((Blk16 *) (buf + 0x04));
        *((Blk16 *) (s6 + 0x44)) = *((Blk16 *) (buf + 0x14));
        *((u16 *) (s6 + 0x2C)) = (*((u16 *) (s6 + 0x2C))) | 1;
      }
      if (((*((u16 *) (s6 + 0x2C))) & 0x10) != 0)
      {
        func_80020F34((s32) (buf + 0x04), s6 + 0x18);
      }
      func_80054514((s32) (buf + 0x00), (s32) (buf + 0x50));
      if (((s1m & 0x1000000) == 0) && (((*((u16 *) (s6 + 0x2C))) & 0x40) == 0))
      {
        s1m = s1m + ((s2v & 0xFFFF) * 0xC);
        func_80049CAC(s1m + 6, (s32) (buf + 0x70));
        *((s32 *) (buf + 0x84)) = (s32) (*((s16 *) (s1m + 0)));
        *((s32 *) (buf + 0x88)) = (s32) (*((s16 *) (s1m + 2)));
        *((s32 *) (buf + 0x8C)) = (s32) (*((s16 *) (s1m + 4)));
      }
      else
      {
        u32 *pu = (u32 *) ((s1m & 0xFEFFFFFF) + ((s2v & 0xFFFF) * 8));
        u32 w;
        *((u16 *) (buf + 0xB0)) = *((u16 *) (((s32) pu) + 6));
        w = *pu;
        *((u16 *) (buf + 0xB2)) = ((u16) (*((u8 *) (((s32) pu) + 1)))) | ((u16) ((w & 0xF) << 8));
        *((u16 *) (buf + 0xB4)) = ((u16) (w >> 0x10)) & 0xFF;
        *((u16 *) (buf + 0xB4)) = (*((u16 *) (buf + 0xB4))) | ((u16) ((w & 0xF0) << 4));
        func_80049CAC((s32) (buf + 0xB0), (s32) (buf + 0x70));
        *((s32 *) (buf + 0x84)) = (s32) (*((s8 *) (((s32) pu) + 3)));
        *((s32 *) (buf + 0x88)) = (s32) ((s8) pu[1]);
        *((s32 *) (buf + 0x8C)) = (s32) (*((s8 *) (((s32) pu) + 5)));
      }
      {
gte_SetRotMatrix((s32 *)(buf + 0x50));
gte_ldclmv((s16 *)(buf + 0x70)); gte_rtir();
gte_stclmv((s16 *)(buf + 0x90));
gte_ldclmv((s16 *)(buf + 0x72)); gte_rtir();
gte_stclmv((s16 *)(buf + 0x92));
gte_ldclmv((s16 *)(buf + 0x74)); gte_rtir();
gte_stclmv((s16 *)(buf + 0x94));
gte_SetTransMatrix((s32 *)(buf + 0x50));
gte_ldlv0((s16 *)(buf + 0x84)); gte_rtv0tr();
gte_stlvnl((s32 *)(buf + 0xA4));
      }
      s6 = *((s32 *) (s7 + 0x20));
      func_80049CAC(s6 + 0x10, (s32) (buf + 0x70));
      sVar1 = (*((s16 *) (s7 + 6))) + (*((s16 *) (s7 + 0x50)));
      *((s16 *) (s6 + 8)) = sVar1;
      *((s32 *) (buf + 0x84)) = (s32) sVar1;
      sVar1 = (*((s16 *) (s7 + 0xA))) + (*((s16 *) (s7 + 0x52)));
      *((s16 *) (s6 + 0xA)) = sVar1;
      *((s32 *) (buf + 0x88)) = (s32) sVar1;
      sVar1 = (*((s16 *) (s7 + 0xE))) + (*((s16 *) (s7 + 0x54)));
      *((s16 *) (s6 + 0xC)) = sVar1;
      *((s32 *) (buf + 0x8C)) = (s32) sVar1;
      {
gte_SetRotMatrix((s32 *)(buf + 0x90));
gte_ldclmv((s16 *)(buf + 0x70)); gte_rtir();
gte_stclmv((s16 *)(buf + 0x50));
gte_ldclmv((s16 *)(buf + 0x72)); gte_rtir();
gte_stclmv((s16 *)(buf + 0x52));
gte_ldclmv((s16 *)(buf + 0x74)); gte_rtir();
gte_stclmv((s16 *)(buf + 0x54));
gte_SetTransMatrix((s32 *)(buf + 0x90));
gte_ldlv0((s16 *)(buf + 0x84)); gte_rtv0tr();
gte_stlvnl((s32 *)(buf + 0x64));
      }
      *((Blk16 *) (s6 + 0x34)) = *((Blk16 *) (buf + 0x50));
      *((Blk16 *) (s6 + 0x44)) = *((Blk16 *) (buf + 0x60));
      s0p = 0x30;
      *((Blk16 *) (s6 + 0x54)) = *((Blk16 *) (buf + 0x50));
      *((Blk16 *) (s6 + 0x64)) = *((Blk16 *) (buf + 0x60));
      *((s32 *) (s6 + s0p)) = 1;
      *((u16 *) (s6 + 0x2C)) = (*((u16 *) (s6 + 0x2C))) | 1;
    }
  }
  return;
}
