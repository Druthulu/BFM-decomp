/* func_8012BCCC — shared body (overlay slot 0x80128158, h_exact 2f5797b1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80013478(s32 a0, s32 a1);
extern s16 D_80126CBA;
extern s32 D_80126B58;
s32 func_8012BCCC(s32 a0) {
    s32 *p = &D_80126B58;
    if (D_80126CBA != 0) {
        return 0x7FFFFFFF;
    }
    return func_80013478(a0 + 4, (s32)p + 0x15C);
}
