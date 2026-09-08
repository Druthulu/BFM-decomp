/* func_80132E6C — shared body (overlay slot 0x80128158, h_exact 1a7a7a1c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void Square0(s32 *a0, s32 *a1);
extern s16 D_80126CAC;
extern s16 D_80126CB0;
s32 func_80132E6C(s16 *a0) {
    s32 in[3];
    s32 out[3];
    in[0] = a0[3] - D_80126CAC;
    in[1] = 0;
    in[2] = a0[7] - D_80126CB0;
    Square0(in, out);
    return out[0] + out[2];
}
