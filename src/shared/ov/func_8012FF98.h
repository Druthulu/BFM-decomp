/* func_8012FF98 — shared body (overlay slot 0x80128158, h_exact bcfabc23). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BEE8(s32 a0);
extern void func_80130D48(s32 a0);
extern void func_801319E0(s32 a0);
extern void func_80131CA8(int a0, int a1);
void func_8012FF98(u8 *a0) {
    if (*(s32 *)(a0 + 0xB4) & 0x20) {
        s32 p = *(s32 *)(a0 + 0x20);
        if (p != 0) {
            *(u32 *)(p + 4) ^= 0x80000000;
        }
        if (func_8012BEE8((s32)a0)) {
            func_80130D48((s32)a0);
            func_801319E0((s32)a0);
        }
    }
    func_80131CA8((int)a0, 0x10);
}
