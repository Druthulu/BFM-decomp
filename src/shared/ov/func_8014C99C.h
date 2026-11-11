/* func_8014C99C — shared body (overlay slot 0x80128158, h_exact 72a917ed). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_TestGameFlag(s32 arg);
extern s32 func_8016F1AC(void);
extern void func_80139914(s32 a0);
extern void guess_SetGameFlag(s32, s32);
void func_8014C99C(u8 *a0) {
    if ((guess_TestGameFlag(0x119) & 0xFF) != 0) {
        if (func_8016F1AC() != 0) {
            func_80139914(*(s32 *)(a0 + 0x198));
            *(s32 *)(a0 + 0x198) = 0;
            guess_SetGameFlag(0x119, 0);
        }
    }
}
