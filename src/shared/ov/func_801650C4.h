/* func_801650C4 — shared body (overlay slot 0x80128158, h_exact 94097607). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80162CCC();
extern void func_80165124(void *a0);
extern void func_801651B8(void *a0);
void func_801650C4(s32 *a0) {
    s16 v = *(u16 *)((s32)a0 + 0x62) - 0x10;
    *(u16 *)((s32)a0 + 0x62) = v;
    if (v < 0) {
        func_80162CCC();
    } else {
        func_80165124(a0);
        func_801651B8(a0);
    }
}
