/* func_80149884 — shared body (overlay slot 0x80128158, h_exact e871b50e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 currentLocationId;
extern s32 func_8016F1AC(void);
s32 func_80149884(void) {
    s32 ret;
    if (currentLocationId == 0x308F) {
        ret = 0;
    } else {
        ret = func_8016F1AC() == 0;
    }
    return ret;
}
