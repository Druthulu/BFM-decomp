/* func_801325B8 — shared body (overlay slot 0x80128158, h_exact 8fd22bf4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *memcpy(void *, const void *, u32);
extern void gteMIMefunc();
void func_801325B8(int dst, int src, int m0, int mm, int arg5)
{
    register int p __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
    int m;
    int n;
    register int dv __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B headers1)
    int sv;
    int ofs;
    int c;
    m = m0;
    p = src;
    if (*(int *)(p + 4) == 1) {
        sv = *(int *)(p + 0xC);
    } else {
        ofs = (int)((*(unsigned int *)(p + 0xC) >> 2) << 2) + 0xC;
        sv = p + ofs;
    }
    p = dst;
    sv += *(int *)(m + 8) * 8;
    if (*(int *)(p + 4) == 1) {
        dv = *(int *)(p + 0xC);
    } else {
        ofs = (int)((*(unsigned int *)(p + 0xC) >> 2) << 2) + 0xC;
        dv = p + ofs;
    }
    c = *(int *)(m + 8);
    dv += c * 8;
    n = *(int *)(m + 0xC);
    m += 0x10;
    memcpy(dv, sv, n * 8);
    gteMIMefunc(dv, m, n, arg5);
    if (mm != 0) {
        m = mm;
        p = src;
        if (*(int *)(p + 4) == 1) {
            sv = *(int *)(p + 0x14);
        } else {
            ofs = (int)((*(unsigned int *)(p + 0x14) >> 2) << 2) + 0xC;
            sv = p + ofs;
        }
        p = dst;
        sv += *(int *)(m + 8) * 8;
        if (*(int *)(p + 4) == 1) {
            dv = *(int *)(p + 0x14);
        } else {
            ofs = (int)((*(unsigned int *)(p + 0x14) >> 2) << 2) + 0xC;
            dv = p + ofs;
        }
        c = *(int *)(m + 8);
        dv += c * 8;
        n = *(int *)(m + 0xC);
        m += 0x10;
        memcpy(dv, sv, n * 8);
        gteMIMefunc(dv, m, n, arg5);
    }
}
