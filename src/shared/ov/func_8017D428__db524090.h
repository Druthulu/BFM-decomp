/* func_8017D428 — shared body (overlay slot 0x80128158, h_exact db524090). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017D428(int param_1)
{
  s32 v0;
  s32 *s1;
  u16 *ptr;
  v0 = *(s32 *)((char *)param_1 + 0x1C);
  s1 = (s32 *)*(s32 *)((char *)param_1 + 0x34);
  *(s32 *)((char *)param_1 + 0x1C) = v0 + 1;
  if (v0 < 0x20) {
    ptr = (u16 *)((char *)param_1 + 0x2A);
    *ptr = *ptr - 0x10;
  } else {
    u16 val = *(u16 *)((char *)param_1 + 0x2C);
    func_80147324((s32)val);
    func_80147084(s1);
    func_801472B4((void *)s1);
    *(s32 *)((char *)param_1 + 0x1C) = 0;
    ptr = (u16 *)((char *)param_1 + 2);
    *ptr = *ptr + 1;
  }
  func_8017D030(param_1);
}
