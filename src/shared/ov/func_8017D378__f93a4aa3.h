/* func_8017D378 — shared body (overlay slot 0x80128158, h_exact f93a4aa3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147324(s32 arg0);
void func_8017D378(void *param_1)
{
  unsigned short temp_0x2E;
  unsigned short *ptr_0x2;
  temp_0x2E = *(unsigned short *)((unsigned char *)param_1 + 0x2E);
  func_80147324((s32)temp_0x2E);
  ptr_0x2 = (unsigned short *)((unsigned char *)param_1 + 0x2);
  *ptr_0x2 = *ptr_0x2 + 1;
}
