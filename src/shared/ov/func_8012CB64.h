/* func_8012CB64 — shared body (overlay slot 0x80128158, h_exact 00da3978). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8012CB64(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1)
    s32 v1;
    v0 = 0;
    v1 = *(s16*)arg0;
    if (((arg1 <= v1) && (v1 < arg2)) && (arg3 <= *(s16*)(arg0 + 4))) {
        v0 = *(s16*)(arg0 + 4) < arg4;
    }
    return v0;
}
