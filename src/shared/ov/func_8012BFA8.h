/* func_8012BFA8 — shared body (overlay slot 0x80128158, h_exact 96500dd9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126CAC;
extern short D_80126CAE;
extern s16 D_80126CB0;
int func_8012BFA8(short *a0) {
    int in[3];
    int out[3];
    in[0] = D_80126CAC - a0[3];
    in[1] = D_80126CAE - a0[5];
    in[2] = D_80126CB0 - a0[7];
    gte_lwc2x3_sqr_e416(&in[0]);
    {
        int *pout = &out[0];
        gte_stlvnl(pout);
    }
    return 0xfffff < out[0] + out[1] + out[2];
}
