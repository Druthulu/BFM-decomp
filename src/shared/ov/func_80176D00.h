/* func_80176D00 — shared body (overlay slot 0x80128158, h_exact 259aeb44). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80178004();
extern u8 D_8011F7B1;
extern u8 D_8011F7A8;
extern u16 D_80078EA6;
extern u16 D_8011F7B4;
extern u16 D_8011F7B6;
extern s16 D_8011F81E;
void func_80176D00(s32 a0) {
    u8 *arr = (u8 *)&D_8011F7A8;
    u8 *base;
    s32 tmp;
    s32 a1v, a2v;
    if (D_8011F7B1 != 0) {
        return;
    }
    base = arr + (s16)a0 * 4;
    tmp = *(s32 *)(base + 0x20) + 0x14;
    *(s32 *)(base + 0x38) = tmp;
    a1v = (s16)(D_8011F7B4 - 0x17);
    a2v = (s16)(D_8011F7B6 + 0x65);
    D_8011F81E = D_80078EA6;
    *(s32 *)(base + 0x40) = func_80178004(tmp, a1v, a2v) - 0x14;
}
