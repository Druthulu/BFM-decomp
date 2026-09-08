/* func_801303EC — shared body (overlay slot 0x80128158, h_exact bb3308c0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801319E0(s32 a0);
extern void func_80131CA8(int a0, int a1);
void func_801303EC(void *a0) {
    if (*(s32 *)((u8 *)a0 + 0xB4) & 0x10) {
        func_801319E0((s32)a0);
    }
    func_80131CA8((int)a0, 0xC);
}
