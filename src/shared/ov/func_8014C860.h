/* func_8014C860 — shared body (overlay slot 0x80128158, h_exact 2750c2a2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8014C860(s32 a0, s32 a1) {
    s32 r = 1;
    *(struct S8 *)(a0 + 0x154) = *(struct S8 *)a1;
    *(s16*)(a0 + 0x15A) = r;
    return r;
}
