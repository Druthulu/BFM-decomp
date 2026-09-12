/* func_80131E7C — shared body (overlay slot 0x80128158, h_exact 288abbc9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012E470(s32 a0);
extern void func_8012E4C8(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_80131E7C(s32 a0) {
    if (*(s32 *)(a0 + 0xB4) & 0x40000) {
        if (func_8012E470(a0)) {
            func_8012E4C8(a0);
            func_80131E00((struct S80131E00 *)a0, 1);
        }
    }
    func_80131CA8(a0, 0x3A);
}
