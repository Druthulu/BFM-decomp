/* func_8014964C — shared body (overlay slot 0x80128158, h_exact fffcefd2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);
extern s32 guess_WorldToScreenFlag(void *param_1, void *param_2);
void func_8014964C(s32 param_1, s32 param_2) {
    SVECTOR in;
    SVECTOR out;
    s32 mid[2];
    s32 p2;
    SVECTOR *pin;
    s32 *m1;
    s32 *m2;
    s32 mtx;
    p2 = param_2;
    in.vx = *(s16 *)(p2 + 2);
    in.vy = *(s16 *)(p2 + 6);
    in.vz = *(s16 *)(p2 + 0xA);
    pin = &in;
    mtx = *(s32 *)(param_1 + 0x20);
    m1 = mid;
    ((void (*)(s32, SVECTOR *, s32 *))guess_RotTransSVWithMatrix)(mtx + 0x34, pin, m1);
    m1 = 0;
    m2 = mid;
    ((void (*)(s32 *, SVECTOR *))guess_WorldToScreenFlag)(m2, &out);
    *(s16 *)(p2 + 2) = out.vx;
    *(s16 *)(p2 + 6) = out.vy;
    *(s16 *)(p2 + 0xA) = out.vz;
}
