/* func_8014AD30 — shared body (overlay slot 0x80128158, h_exact a1e0a452). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146AFC(void *a0);
void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3) {
    struct S_8014AD30 sp;
    s16 b = a1[0];
    s16 c = a1[1];
    s16 d = a1[2];
    sp.h0 = 0x1D;
    sp.w0 = a0;
    sp.w1 = a2;
    sp.w2 = a3;
    sp.h1 = b;
    sp.h2 = c;
    sp.h3 = d;
    func_80146AFC(&sp);
}
