/* func_80145BF8 — shared body (overlay slot 0x80128158, h_exact a4cff956). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);
extern void guess_RequestSound(s32 a0, s32 a1);
void func_80145BF8(void) {
    guess_RequestSound(0x21, func_80028FBC() & 0xFFFF);
    guess_RequestSound(0x22, func_80029000() & 0xFFFF);
    guess_RequestSound(func_80028D9C() == 0 ? 0xC : 0xB, 0);
}
