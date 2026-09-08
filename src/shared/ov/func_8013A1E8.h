/* func_8013A1E8 — shared body (overlay slot 0x80128158, h_exact 3c78e328). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80127524;
extern s16 func_80138DB8(s32 a0, u8 a1, s32 a2);
extern void func_80138B88(s32 a0);
void func_8013A1E8(s32 a0) {
    s32 v = D_80127524;
    if (v == a0) {
        if (func_80138DB8(v, 0, 0x70) != 0 || (*(s32 *)(v + 8) & 0x800)) {
            func_80138B88(v);
        }
    }
}
