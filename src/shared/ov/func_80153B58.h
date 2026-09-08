/* func_80153B58 — shared body (overlay slot 0x80128158, h_exact 596dbad8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_800B99DA;
extern s32 func_8016DA04(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80153B58(s32 *a0) {
    if ((D_800B99DA & 0x3) == 0) {
        func_8016DA04((s32)a0);
    }
    if ((D_800B99DA & 0x1) == 0) {
        func_80146A6C(3, a0,
                      *(s16 *)((u8 *)a0 + 6),
                      *(s16 *)((u8 *)a0 + 0xA),
                      *(s16 *)((u8 *)a0 + 0xE),
                      0x8880000, 0x18009000);
    }
}
