/* func_801493D0 — shared body (overlay slot 0x80128158, h_exact 34e1bcfb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80015954(s32 a0, s32 a1);
void func_801493D0(s32 param_1, s32 param_2, s32 param_3)
{
  u8 buf1[8];
  u8 *new_var;
  u8 buf2[8];
  ((void (*)(s32, u8 *)) func_80015978)(param_2, buf1);
  new_var = buf2;
  ((void (*)(s32, u8 *, u8 *)) func_8012F14C)((*((s32 *) (param_1 + 0x20))) + 0x34, buf1, new_var);
  new_var++;
  new_var--;
  ((void (*)(u8 *, s32)) func_80015954)(buf2, param_3);
}
