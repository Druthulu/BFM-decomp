/* func_80142BB4 — shared body (overlay slot 0x80128158, h_exact dd5bb9d1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801439C0(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012C218(void *a0);
extern void func_8012C098(void);
void func_80142BB4(s32 * param_1, s32 param_2, s32 param_3)
{
  void *new_var;
  new_var = param_1;
  if ((*((s16 *) (new_var + 0xfc))) == 1)
  {
    if ((param_2 != ((char) 0)) || ((*((s16 *) (new_var + 0x100))) == 0))
    {
      *((u16 *) (new_var + 0x5c)) = (*((u16 *) (new_var + 0x5c))) & 0xfefe;
      *((u32 *) ((*((s32 *) (new_var + 0x20))) + 4)) = (*((u32 *) ((*((s32 *) (new_var + 0x20))) + 4))) | 0x80000000;
      func_801439C0(*((u8 **) (new_var + 0xcc)));
      func_8012AD44((s32 *) new_var, param_3);
    }
  }
  else
    if ((param_2 != 0) || ((*((s16 *) (new_var + 0x100))) == 0))
  {
 do { func_8012C218(new_var = (void *) new_var); } while (0);
  }
  else
  {
    ((void (*)(void *)) func_8012C098)((void *) new_var);
  }
}
