/* func_801432FC — shared body (overlay slot 0x80128158, h_exact 1286cbd4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80142DB8(s32 *a0);
extern s32 func_8012C044(s32 a0);
extern void func_80142BB4(s32 *a0, s32 a1, s32 a2);
extern void func_80142C9C(s32 *a0);
extern s32 func_8012BF10(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
void func_801432FC(s32 *a0) {
    if (func_80142DB8(a0) == 1) {
        func_80142BB4(a0, 1, 3);
        return;
    }
    if (*(s16 *)((u8 *)a0 + 0x100) != 0) {
        if (func_8012C044(a0) == 0) {
            return;
        }
        func_80142BB4(a0, 0, 3);
        return;
    }
    func_80142C9C(a0);
    if (func_8012BF10((s32)a0, 0x30) != 0) {
        func_8012AD44(a0, 2);
    }
}
