s32 func_80021174(s32 a0, s32 a1)
{
  s32 sp[4];
  s32 lim;
s32 *p_a3;
register s32 ret __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
  if (a0 == 0x7FFF7FFF)
  {
    return 1;
  }
  p_a3 = D_800AE688;
__asm__ volatile ( "lw $12, 0( %0 );" "lw $13, 4( %0 );" "ctc2 $12, $0;" "ctc2 $13, $1;" "lw $12, 8( %0 );" "lw $13, 12( %0 );" "lw $14, 16( %0 );" "ctc2 $12, $2;" "ctc2 $13, $3;" "ctc2 $14, $4;" "lw $12, 20( %0 );" "lw $13, 24( %0 );" "ctc2 $12, $5;" "lw $14, 28( %0 );" "ctc2 $13, $6;" "ctc2 $14, $7" : : "r"( p_a3 ) : "$12", "$13", "$14", "memory" );  // !FAKE: gte direct — clobbers ['memory'] (gte_SetRotTransMatrix_m) beyond Sony's (P36 T5 gte1)
__asm__ volatile ( "lhu $13, 4( %0 );" "lhu $12, 0( %0 );" "sll $13, $13, 16;" "or $12, $12, $13;" "mtc2 $12, $0;" "lwc2 $1, 8( %0 )" : : "r"( (SV_80021174 *)a1 ) : "$12", "$13", "memory" );  // !FAKE: gte direct — clobbers ['memory'] (gte_ldlv0_m) beyond Sony's (P36 T5 gte1)
__asm__ volatile ( "nop;" "nop;" "rtps" : : : "memory" );  // !FAKE: gte direct — clobbers ['memory'] (gte_rtps_m) beyond Sony's (P36 T5 gte1)
gte_stsxy(sp);
gte_stflg(&sp[1]);
gte_stszotz(&sp[2]);
  if (sp[1] < 0)
  {
    return 0;
  }
  ret = 0;
  lim = (s16) a0;
  ;
  if ((*((s16 *) sp)) <= (-lim))
  {
    return ret;
  }
  if (lim < (*((s16 *) sp)))
  {
    return ret;
  }
  a0 = a0 >> 16;
  a1 = *((s16 *) (((char *) sp) + 2));
  if (a1 <= (-a0))
  {
    return ret;
  }
  ret = !(a0 < a1);
  return ret;
}
