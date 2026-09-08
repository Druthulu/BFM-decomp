/* func_8016E26C — shared body (overlay slot 0x80128158, h_exact 46617185). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016E3CC(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_8016E26C(s32 *a0) {
    func_8016E3CC((s32)a0);
    if (--a0[0x1C / 4] != 0) {
        func_80146A6C(0x48, a0, 0, 0, 0, 0x8000, 0);
    } else {
        a0[0x1C / 4] = 0x10;
        *(u16 *)((char *)a0 + 2) += 1;
    }
}
