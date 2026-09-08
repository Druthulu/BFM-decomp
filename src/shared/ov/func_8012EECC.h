/* func_8012EECC — shared body (overlay slot 0x80128158, h_exact 6bab7bd4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8002A4FC(s32 a0);
s32 func_8012EECC(s32 a0) {
    s32 n = a0 * func_8002A4FC(a0);
    return a0 - (n * 100) / 7680;
}
