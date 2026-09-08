/* func_8012BB3C — shared body (overlay slot 0x80128158, h_exact d4f9dd59). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 a0, s32 a1);
s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3) {
    register s32 a __asm__("$17");   /* $s1 */
    register s32 div __asm__("$16"); /* $s0 */
    register s32 q __asm__("$3");    /* $v1 */
    register s32 d __asm__("$2");    /* $v0 */
    s32 ang;
    s32 diff;
    u32 cur;
    a = arg2;
    div = arg3;
    ang = ratan2(*(s16 *)(arg0 + 0xA) - *(s16 *)(arg1 + 0xA),
                 *(s16 *)(arg1 + 0x2) - *(s16 *)(arg0 + 0x2));
    ang = ang - 0x400;
    __asm__ __volatile__("" : : "r"(ang));
    div = (s16)div;
    a = a & 0xFFF;
    cur = ang & 0xFFF;
    if (a == cur) {
        d = 0;
    } else {
        s32 t;
        diff = cur - a;
        if (0x800 < diff) {
            t = a + 0x1000;
            diff = cur - t;
        }
        if (diff < -0x800) {
            t = a - 0x1000;
            diff = cur - t;
        }
        if (diff >= 0) {
            q = diff / div;
            if (q == 0) {
                q = 1;
            }
        } else {
            q = diff / div;
            if (q == 0) {
                q = -1;
            }
        }
        d = q;
    }
    return (s16)d;
}
