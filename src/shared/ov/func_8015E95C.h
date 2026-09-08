/* func_8015E95C — shared body (overlay slot 0x80128158, h_exact 50852150). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8015E9B8(s32 *a0);
extern u8 D_80078EC0;
void func_8015E95C(s32 a0) {
    if ((D_80078EC0 & 0x80) == 0) {
        func_80146A6C(0x14, (void *)a0, 0, 0, 0, 0, 0);
    }
    func_8015E9B8(a0);
}
