/* func_8012F91C — shared body (overlay slot 0x80128158, h_exact fdb55867). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131340(s32 a0);
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_8012F91C(s32 a0) {
    if (*(s32 *)(a0 + 0xB4) & 0x80) {
        func_80131340(a0);
    }
    func_80131CA8(a0, 0x17);
}
