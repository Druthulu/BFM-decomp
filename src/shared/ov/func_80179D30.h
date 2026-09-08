/* func_80179D30 — shared body (overlay slot 0x80128158, h_exact d8c69912). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80179B74(u16 *p);
void func_80179D30(u16 *a0) {
    s16 buf[4];
    buf[0] = 1;
    buf[1] = a0[0];
    buf[2] = a0[1];
    buf[3] = a0[2];
    func_80179B74(buf);
}
