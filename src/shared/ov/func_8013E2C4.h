/* func_8013E2C4 — shared body (overlay slot 0x80128158, h_exact c25f1351). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126CAC;
extern short D_80126CAE;
extern s16 D_80126CB0;
int func_8013E2C4(short *a0) {
    int in[3];
    int out[3];
    in[0] = D_80126CAC - a0[0];
    in[1] = D_80126CAE - a0[1];
    in[2] = D_80126CB0 - a0[2];
    __asm__ __volatile__(
        "lwc2 $9, 0(%0)\n"
        "lwc2 $10, 4(%0)\n"
        "lwc2 $11, 8(%0)\n"
        "nop\n"
        "nop\n"
        "sqr 0\n"
        : : "r"(&in[0]) : "$9", "$10", "$11", "memory");
    {
        int *pout = &out[0];
        gte_stlvnl(pout);
    }
    return (out[0] + out[1] + out[2]) - 0x90001U < 0x18FFF;
}
