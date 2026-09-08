/* func_80141B90 — shared body (overlay slot 0x80128158, h_exact a8e23f54). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013FAF8(s16, s16);
extern short D_800B9A02;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern u16 D_80115116;
extern u16 D_80115112;
extern u8 D_800B9A15;
void func_80141B90(void)
{
  volatile char pad;
  D_801151D0 = ((s32 *) D_801151C8)[*((u16 *) (&D_800B9A02))];
  ((void (*)(s32, s32))func_8013FAF8)(2, 3);
  if (D_80115116 == 0)
  {
    *((s8 *) (&D_800B9A15)) = 0;
    D_80115112 = D_80115112 + 1;
  }
}
