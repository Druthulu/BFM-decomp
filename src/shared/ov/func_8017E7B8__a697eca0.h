/* func_8017E7B8 — shared body (overlay slot 0x80128158, h_exact a697eca0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017E7B8(a0)
s32 *a0;
{
  s32 v1;
  s32 a1;
  v1 = *((s32 *) (((u8 *) a0) + 0x20));
  *((s16 *) (((u8 *) v1) + 0x10)) = 0xC00;
  v1 = (s32) a0;
  func_8014706C((void *) v1);
  a1 = 0x27;
  func_80154150(v1, a1);
  *((s32 *) (((u8 *) a0) + 0x200)) = 0x80;
  func_80171990((u8 *) a0);
}
