/* func_80165694 — shared body (overlay slot 0x80128158, h_exact af889943). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80078EC8;
void func_80165694(s32 arg0) {
    if (*(s32 *)((s32)arg0 + 0x1F8) & 0x80FFFFFF) {
        return;
    }
    if (D_80078EC8 != 0) {
        D_80078EC8 = D_80078EC8 - 1;
    }
}
