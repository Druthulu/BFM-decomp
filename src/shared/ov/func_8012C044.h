/* func_8012C044 — shared body (overlay slot 0x80128158, h_exact d88e5bf5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801274D4;
extern s16 D_80126CAC;
extern s32 D_801274E0;
extern s32 func_80013478(s32 a0, s32 a1);
s32 func_8012C044(s32 a0) {
    s32 (*fp)(void) = (s32 (*)(void))D_801274D4;
    if (fp != 0) {
        return fp();
    }
    return func_80013478(a0 + 4, (s32)&D_80126CAC) >= D_801274E0;
}
