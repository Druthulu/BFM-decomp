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
        __asm__ __volatile__(
            "swc2 $25, 0(%0)\n"
            "swc2 $26, 4(%0)\n"
            "swc2 $27, 8(%0)\n"
            : : "r"(pout) : "memory");
    }
    return 0xfffff < out[0] + out[1] + out[2];
}
