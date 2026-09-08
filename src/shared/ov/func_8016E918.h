/* func_8016E918 — shared body (overlay slot 0x80128158, h_exact 0c243aad). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80115218;
void func_8016E918(short param_1, short param_2) {
    char *p;
    if (param_2 < 10) {
        p = (char *)&D_80115218 + ((s32)param_1 << 5);
        p[0] = param_1 + 1;
        p[3] = param_2;
        p[1] = 0;
    }
}
