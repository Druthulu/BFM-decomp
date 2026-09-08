/* func_8018625C — shared body (overlay slot 0x80128158, h_exact 3b484751). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8018625C(void *a0) {
    a0 = *(void **)((char *)a0 + 0xCC);
    if (a0 == 0) {
        return 0;
    }
    if (*(u16 *)a0 != 0x61) {
        return 0;
    }
    return func_801862A8(a0);
}
