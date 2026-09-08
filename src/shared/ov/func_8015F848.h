/* func_8015F848 — shared body (overlay slot 0x80128158, h_exact b2b08ed8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_8011F730;
extern void func_801553A8(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
void func_8015F848(s32 *a0) {
    func_801553A8(a0);
    func_80154150((s32)a0, 0x1F);
    D_8011F730 |= 0x5;
    func_80146CA0(a0);
}
