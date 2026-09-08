/* func_8017C628 — shared body (overlay slot 0x80128158, h_exact af037f84). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80147060(u8 *a0);
extern void func_8017BEE8(void);
extern void func_80171A04(s32*);
void func_8017C628(u8 *a0) {
    func_8002D4C8(0x1B, 0);
    func_80147060(a0);
    func_8017BEE8();
    ((void (*)(u8 *))func_80171A04)(a0);
}
