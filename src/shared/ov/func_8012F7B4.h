/* func_8012F7B4 — shared body (overlay slot 0x80128158, h_exact f2c10f62). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BEE8(s32);
extern s32 func_80131A34(s32, s32);
extern void func_80131CA8(int a0, int a1);
void func_8012F7B4(s32 a0) {
    if (*(s32 *)(a0 + 0xB4) & 4) {
        func_8012BEE8(a0);
        if (*(s32 *)(a0 + 0x1C) == 1) {
            if (func_80131A34(a0, 8) == 0) {
                func_80131A34(a0, 0x20);
            }
        }
    }
    func_80131CA8(a0, 7);
}
