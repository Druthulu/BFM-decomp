/* func_80171A88 — shared body (overlay slot 0x80128158, h_exact 157c01fe). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80171A88(s32 a0) {
    s32 v0;
    v0 = *(s32*)(a0 + 0x200);
    if (!v0) goto ret1;
    *(s32*)(a0 + 0x200) = v0 - 1;
    return (u32)(v0 - 1) < 1;
ret1:
    return 1;
}
