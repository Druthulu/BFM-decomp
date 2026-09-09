/* func_80139D04 — shared body (overlay slot 0x80128158, h_exact 38fb7f4a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80139D04(s32 a0, s32 a1) {
    u8 *p;   /* $t0 */
    u32 div;   /* $t1 */
    u32 acc;  /* $t2 */
    u32 cnt;   /* $a2 */
    register u32 flag __asm__("$7");   /* $a3 */  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B headers1)
    register u32 param_2 __asm__("$5"); /* $a1 */  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B headers1)
    u32 q;
    register u32 rem __asm__("$4");  /* $a0 */  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
    u32 hi;  /* $v0 */
    register u32 pm __asm__("$3");  /* $v1 */  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
    u32 dm;  /* $v0 */
    p = (u8 *)a0;
    param_2 = (u32)a1;
    div = 10000;
    acc = 0;
    flag = 0;
    cnt = 5;
    do {
        q = (param_2 & 0xffff) / (div & 0xffff);
        hi = acc << 4;
        acc = q | hi;
        if ((flag & 0xffff) == 0) {
            if ((acc & 0xffff) != 0) {
                flag = cnt;
            }
            if ((flag & 0xffff) != 0) goto store;
        } else {
        store:
            *p = (u8)q;
            p = p + 1;
        }
        pm = param_2 & 0xffff;
        __asm__ __volatile__("" : : "r"(pm));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
        dm = div & 0xffff;
        rem = pm % dm;
        div = dm / 10;
        cnt = cnt - 1;
        param_2 = rem;
        if ((s32)cnt < 1) {
            if ((flag & 0xffff) == 0) {
                *p = 0;
                flag = flag + 1;
            }
            return flag & 0xffff;
        }
    } while (1);
}
