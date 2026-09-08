/* func_8012BEE8 — shared body (overlay slot 0x80128158, h_exact 2c8a6ecc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8012BEE8(s32 a0) {
    s32 v0;
    v0 = *(s32*)(a0 + 0x1C);
    if (!v0) goto ret1;
    *(s32*)(a0 + 0x1C) = v0 - 1;
    return (u32)(v0 - 1) < 1;
ret1:
    return 1;
}
