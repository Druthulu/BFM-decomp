/* func_8013ED6C — shared body (overlay slot 0x80128158, h_exact cba4af60). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80141C50(void);
extern s32 func_8013F350(void); /* §30#2 widened (discarding caller) */
extern void func_8013FAF8(s16 a0, s16 a1);
extern void func_8013E958(void);
extern short D_800B9A02;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern u16 D_8011511A;
extern u16 D_8011511E;
extern u16 D_80115112;
void func_8013ED6C(void) {
    s32 sp10[2];
    if ((s16)func_80141C50() == 0) {
        D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
        func_8013F350();
        func_8013FAF8(7, 8);
        if (D_8011511A == 7) {
            if ((D_8011511E & 0x810) == 0) {
                return;
            }
        }
        func_8013E958();
        D_80115112 = 4;
    }
    (void)sp10;
}
