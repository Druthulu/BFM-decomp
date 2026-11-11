/* func_8013ED6C — shared body (overlay slot 0x80128158, h_exact cba4af60). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80141C50(void);
extern s32 func_8013F350(void); /* §30#2 widened (discarding caller) */
extern void func_8013FAF8(s16 a0, s16 a1);
extern void func_8013E958(void);
extern short guess_g_DoubleBufferIndex;
extern u8 guess_g_MenuPacketBases[];
extern s32 guess_g_MenuPacketPtr;
extern u16 guess_g_MenuPanel;
extern u16 guess_g_MenuPadPressed;
extern u16 guess_g_MenuStep;
void func_8013ED6C(void) {
    s32 sp10[2];
    if ((s16)func_80141C50() == 0) {
        guess_g_MenuPacketPtr = *(s32 *)&guess_g_MenuPacketBases[(u16)guess_g_DoubleBufferIndex * 4];
        func_8013F350();
        func_8013FAF8(7, 8);
        if (guess_g_MenuPanel == 7) {
            if ((guess_g_MenuPadPressed & 0x810) == 0) {
                return;
            }
        }
        func_8013E958();
        guess_g_MenuStep = 4;
    }
    (void)sp10;
}
