/* func_801303A0 — shared body (overlay slot 0x80128158, h_exact 2699b517). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012E364();
extern void func_80131CA8(int a0, int a1);
void func_801303A0(s32 a0) {
    if (*(s32 *)(a0 + 0xB4) & 0x2) {
        ((void (*)(s32))func_8012E364)(a0);
    }
    func_80131CA8(a0, 2);
}
