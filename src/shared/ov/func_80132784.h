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
__asm__ __volatile__(
                    "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
                    "ctc2 $12, $0\n" "ctc2 $13, $1\n"
                    "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
                    "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
                    : : "r"((s32 *)(buf + 0x50)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_SetRotMatrix_m) beyond Sony's (P36 T5 gte1)
__asm__ __volatile__(
                    "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
                    "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
                    "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
                    : : "r"((s16 *)(buf + 0x70)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldclmv+gte_rtir_m) beyond Sony's (P36 T5 gte1)
gte_stclmv((s16 *)(buf + 0x90));
__asm__ __volatile__(
                    "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
                    "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
                    "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
                    : : "r"((s16 *)(buf + 0x72)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldclmv+gte_rtir_m) beyond Sony's (P36 T5 gte1)
gte_stclmv((s16 *)(buf + 0x92));
__asm__ __volatile__(
                    "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
                    "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
                    "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
                    : : "r"((s16 *)(buf + 0x74)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldclmv+gte_rtir_m) beyond Sony's (P36 T5 gte1)
gte_stclmv((s16 *)(buf + 0x94));
__asm__ __volatile__(
                    "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
                    "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
                    "ctc2 $13, $6\n" "ctc2 $14, $7\n"
                    : : "r"((s32 *)(buf + 0x50)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_SetTransMatrix_m) beyond Sony's (P36 T5 gte1)
__asm__ __volatile__(
                    "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n"
                    "sll $13, $13, 16\n" "or $12, $12, $13\n"
                    "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n"
                    "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n"
                    : : "r"((s16 *)(buf + 0x84)) : "$12", "$13", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldlv0+gte_rtv0tr_m) beyond Sony's (P36 T5 gte1)
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
__asm__ __volatile__(
                    "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
                    "ctc2 $12, $0\n" "ctc2 $13, $1\n"
                    "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
                    "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
                    : : "r"((s32 *)(buf + 0x90)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_SetRotMatrix_m) beyond Sony's (P36 T5 gte1)
__asm__ __volatile__(
                    "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
                    "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
                    "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
                    : : "r"((s16 *)(buf + 0x70)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldclmv+gte_rtir_m) beyond Sony's (P36 T5 gte1)
gte_stclmv((s16 *)(buf + 0x50));
__asm__ __volatile__(
                    "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
                    "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
                    "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
                    : : "r"((s16 *)(buf + 0x72)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldclmv+gte_rtir_m) beyond Sony's (P36 T5 gte1)
gte_stclmv((s16 *)(buf + 0x52));
__asm__ __volatile__(
                    "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
                    "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
                    "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
                    : : "r"((s16 *)(buf + 0x74)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldclmv+gte_rtir_m) beyond Sony's (P36 T5 gte1)
gte_stclmv((s16 *)(buf + 0x54));
__asm__ __volatile__(
                    "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
                    "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
                    "ctc2 $13, $6\n" "ctc2 $14, $7\n"
                    : : "r"((s32 *)(buf + 0x90)) : "$12", "$13", "$14", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_SetTransMatrix_m) beyond Sony's (P36 T5 gte1)
__asm__ __volatile__(
                    "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n"
                    "sll $13, $13, 16\n" "or $12, $12, $13\n"
                    "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n"
                    "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n"
                    : : "r"((s16 *)(buf + 0x84)) : "$12", "$13", "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldlv0+gte_rtv0tr_m) beyond Sony's (P36 T5 gte1)
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
