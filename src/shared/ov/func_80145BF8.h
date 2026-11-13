/* func_80145BF8 — shared body (overlay slot 0x80128158, h_exact a4cff956). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 func_80028FBC(void);
extern u8 func_80029000(void);
extern u8 func_80028D9C(void);
extern void guess_RequestSound(s32 a0, s32 a1);
void func_80145BF8(void) {
    guess_RequestSound(0x21, RET_AS(s32, func_80028FBC, (void))() & 0xFFFF);
    guess_RequestSound(0x22, RET_AS(s32, func_80029000, (void))() & 0xFFFF);
    guess_RequestSound(RET_AS(s32, func_80028D9C, (void))() == 0 ? 0xC : 0xB, 0);
}
