/* func_80131AC8 — shared body (overlay slot 0x80128158, h_exact a82785b8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80131CF4();  // K&R: 1 of 2 args (P37 unalias t4_ua6)
extern void func_8002D4C8(s32 a0, s32 a1);
s32 func_80131AC8(void *a0) {
    s32 s0 = func_80131CF4(*(s32 *)((u8 *)a0 + 0xBC)) & 0xFFFF;
    if (s0 != 0) {
        func_8002D4C8(s0, 0);
        return s0;
    }
    return 0;
}
