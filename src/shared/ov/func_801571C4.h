/* func_801571C4 — shared body (overlay slot 0x80128158, h_exact b04b8b2c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
extern s32 func_8014C918(s32 a0, s32 a1);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
extern u8 D_801202A0[];
extern u8 D_801152A8[];
extern u8 D_80126720[];
u32 func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12)
{
  s16 sp18[4];
  u16 local_40;
  u16 local_38;
  u32 local_30;
  u32 ret;
  u32 counter;
  u32 s4val;
  s32 off;
  s32 r;
  ret = 0;
  ;
  local_38 = a10;
  r = ((s32 (*)(s32, s32, s32))func_80135004)(1, a3, a4);
  if (r != 0)
  {
    *((u8 *) a11) = (*((u16 *) (a4 + 6))) >> 13;
    *((u8 *) a12) = *((u16 *) (a4 + 6));
    ret = 2;
    __builtin_memcpy((void *) a6, D_801152A8, 8);
  }
  counter = 0;
  s4val = a1;
  local_30 = a2 & 0x8000;
  off = 0;
  do
  {
    u8 *e = &D_801202A0[off];
    s32 a1v;
    if (((((((*((u16 *) e)) != 0) && ((a1v = *((s32 *) (e + 0x58))) != 0)) && (((*((u32 *) (e + 0x5c))) & 0x8100) == 0x8000)) && ((*((u16 *) (e + 0x5e))) != 10)) && (((a9 & 0x80) != 0) || ((*((u16 *) (e + 0x5e))) != s4val))) && ((s4val != 0xd) || (((*((u16 *) (e + 0x5c))) & 0x2000) != 0)))
    {
      if (func_80135260(*((s32 *) (e + 0x20)), a1v, a3, a4) != 0)
      {
        if ((((*((u16 *) (e + 0x5c))) & 0x4000) != 0) || (((*((s16 *) (e + 0xae))) & local_38) != 0))
        {
          *((u8 *) a11) = func_8014C918(a0, *((u8 *) (e + 0x75)));
          *((u8 *) a12) = 0;
          __builtin_memcpy((void *) a6, D_801152A8, 8);
          ret |= 4;
          *((s32 *) a7) = (s32) e;
        }
        else
        {
          __builtin_memcpy(sp18, (void *) a4, 8);
          if (local_30 != 0)
          {
            sp18[3] = 1;
          }
          else
          {
            sp18[3] = 0;
          }
          func_8014C4AC((s32) e, a1, a2 & 0x7fff, sp18, *((s16 *) ((*((s32 *) (a0 + 0x20))) + 0x12)));
          __builtin_memcpy((void *) a5, D_801152A8, 8);
          *((s32 *) a7) = (s32) e;
          __builtin_memcpy((void *) a8, D_80126720, 8);
          ret |= 1;
          if ((a9 & 0x7f) != 0)
          {
            return ret;
          }
        }
      }
    }
    counter += 1;
    off += 0x10c;
  }
  while (counter < 0x60);
  return ret;
}
