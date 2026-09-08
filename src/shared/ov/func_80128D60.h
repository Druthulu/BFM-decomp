/* func_80128D60 — shared body (overlay slot 0x80128158, h_exact e08b51c3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
void func_80128D60(s32 a0, s32 *a1, s32 *a2) {
    a1[0] = (s32)a2;
    *(s16 *)((u8 *)a1 + 4) = 0;
    *(s16 *)((u8 *)a1 + 6) = a2[1] & 0x3F;
    if (a0 != 0) {
        func_80018450(a0, a2[0]);
    } else {
        func_800183E0(a2[0]);
    }
}
