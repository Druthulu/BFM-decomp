/* func_801585AC — shared body (overlay slot 0x80128158, h_exact 8e35c115). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 func_80148800(s32 *a0);
s32 func_801585AC(s32 *a0) {
    u16 r = func_80148800(a0);
    u16 v = *(u16 *)((u8 *)a0 + 0x244) | r;
    s32 m;
    *(u16 *)((u8 *)a0 + 0x244) = v;
    m = v & 0x10;
    return m != 0;
}
