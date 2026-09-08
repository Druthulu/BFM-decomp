/* func_80149BAC — shared body (overlay slot 0x80128158, h_exact 0e5161ea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8015DE24(s32 *a0);
extern void func_80157510(s32 *a0);
void func_80149BAC(s32 *a0) {
    if (*(s32 *)((s32)a0 + 0x178) != 0) {
        func_8015DE24(a0);
    } else {
        *(s8 *)((s32)a0 + 0x1AA) = 1;
        func_80157510(a0);
    }
}
