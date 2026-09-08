/* func_80175308 — shared body (overlay slot 0x80128158, h_exact c722f77f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8  D_8011F7A8;
extern u8  D_8011F7A9;
extern u8  D_8011F7AE;
extern u16 D_8011F7B4;
extern u16 D_8011F7B6;
extern s16 D_8011F7B8;
extern s16 D_8011F7BA;
extern s16 D_8011F7BC;
extern s16 D_8011F7BE;
extern u8 D_80078E78[];
extern s16 D_800B9A02;
extern void func_80016714(void *, s32);
extern void func_801757A0(s32);
extern void func_800596F4(s32);
void func_80175308(void) {
    u8 *p = (u8 *)&D_8011F7A8;
    p[0] = 1;
    D_8011F7A9 = 2;
    D_8011F7AE = 0x37;
    D_8011F7B8 = -0x37;
    (*(s16 *)&D_8011F7B4) = -0x37;
    D_8011F7BE = 0x37;
    D_8011F7BA = 0x37;
    (*(s16 *)&D_8011F7B6) = 0x37;
    D_8011F7BC = 0x37;
    *(Blk152 *)(p + 0x48) = (*(Blk152 *)D_80078E78);
    func_80016714(p + 0xE0, 0x98);
    {
        s16 *q = &D_800B9A02;
        func_801757A0(*q);
        func_800596F4(0);
        func_801757A0((s16)(*(u16 *)q ^ 1));
    }
}
