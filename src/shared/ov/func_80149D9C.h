/* func_80149D9C — shared body (overlay slot 0x80128158, h_exact 970fb761). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80149E94(s32 a0);
extern s32 func_80149DD8(s32 a0);
s32 func_80149D9C(s32 a0) {
    s32 v0;
    if (func_80149E94(a0) != 0) {
        v0 = 1;
    } else {
        v0 = func_80149DD8(a0) != 0;
    }
    return v0;
}
