/* func_80150BC8 — shared body (overlay slot 0x80128158, h_exact b516ff15). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_800B99DA;
extern s32 func_801619D0(void *a0);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 func_8014BF6C(void);
extern s32 func_80151184(s32 a0, s32 a1, s32 a2);
void func_80150BC8(s32 *a0) {
    if (func_801619D0(a0) != 0) {
        if (D_800B99DA & 0x7) {
            func_80146994(0x34, (s32)a0, 0, 0);
        }
    } else {
        if ((func_8014BF6C() & 0xFF) == 0) {
            func_80151184((s32)a0, 0xC003, 0x10);
        }
    }
}
