/* func_8014C308 — shared body (overlay slot 0x80128158, h_exact a78b069d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1)
    s32 v1;
    if (*(u16 *)((u8 *)arg1 + 0x0) == 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg1 + 0x58) == 0) {
        return 0;
    }
    if (*(u16 *)((u8 *)arg1 + 0x5E) != arg2) {
        if ((*(s32 *)((u8 *)arg1 + 0x5C) & 0xC100) != 0x8000) {
            return 0;
        }
        if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
            v0 = 1;
            v1 = 9;
            if (arg2 == v1) return v0;
            v1 = 0x11;
            if (arg2 == v1) return v0;
            v1 = 0x29;
            if (arg2 == v1) return v0;
            v1 = 0xA;
            if (arg2 == v1) return v0;
            return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
        }
    }
    return 0;
}
