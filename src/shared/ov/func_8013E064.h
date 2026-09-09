/* func_8013E064 — shared body (overlay slot 0x80128158, h_exact 827cf706). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int SquareRoot12(int a0);
int func_8013E064(s16 *a0, s16 *a1) {
    s32 d[3];
    s32 sq[3];
    d[0] = a0[1] - a1[1];
    d[1] = a0[3] - a1[3];
    d[2] = a0[5] - a1[5];
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
        gte_stlvnl(pq);
    }
    return SquareRoot12(sq[0] + sq[1] + sq[2]);
}
