/* func_8013E194 — shared body (overlay slot 0x80128158, h_exact 87b707bc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int SquareRoot12(int a0);
int func_8013E194(s16 *a0, s16 *a1) {
    s32 d[3];
    s32 sq[3];
    d[0] = a0[0] - a1[0];
    d[1] = a0[1] - a1[1];
    d[2] = a0[2] - a1[2];
    {
        s32 *pd = &d[0];
        __asm__ __volatile__(
            "lwc2 $9, 0(%0)\n"
            "lwc2 $10, 4(%0)\n"
            "lwc2 $11, 8(%0)\n"
            "nop\n"
            "nop\n"
            "sqr 1\n"
            : : "r"(pd) : "$9", "$10", "$11", "memory");
    }
    {
        s32 *pq = &sq[0];
        __asm__ __volatile__(
            "swc2 $25, 0(%0)\n"
            "swc2 $26, 4(%0)\n"
            "swc2 $27, 8(%0)\n"
            : : "r"(pq) : "memory");
    }
    return SquareRoot12(sq[0] + sq[1] + sq[2]);
}
