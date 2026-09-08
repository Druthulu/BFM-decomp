/* func_80130650 — shared body (overlay slot 0x80128158, h_exact 3767c011). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801319E0(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012CBF4(s32);
extern s32 func_80131D68(s32 a0, s32 a1);
extern void func_80131C78(s32 a0);
extern void func_80131CA8(int a0, int a1);
void func_80130650(s32 a0) {
    s32 s1;
    if (*(s32 *)(a0 + 0xB4) & 0x1000) {
        if (*(s16 *)(a0 + 0xA) >= 0x10) {
            func_801319E0(a0);
            return;
        }
        if (func_8012BEE8(a0) != 0) {
            func_801319E0(a0);
            return;
        }
        if (*(s32 *)(a0 + 0xC4) & 0x4) {
            s32 v1 = *(s32 *)(a0 + 0x20);
            *(s16 *)(v1 + 0x10) = *(u16 *)(v1 + 0x10) - 0x100;
        }
        s1 = ((s32 (*)(s32))func_8012CBF4)(a0);
        if (func_80131D68(a0, s1) == 1) {
            return;
        }
        if (s1 & 0x2000) {
            func_80131C78(a0);
        }
    }
    func_80131CA8(a0, 0x23);
}
