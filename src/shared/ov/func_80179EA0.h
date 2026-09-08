/* func_80179EA0 — shared body (overlay slot 0x80128158, h_exact af16be00). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80179B74(u16 *p);
void func_80179EA0(u16 *a0) {
    s16 buf[4];
    buf[0] = 5;
    buf[1] = a0[0];
    buf[2] = a0[1];
    buf[3] = a0[2];
    func_80179B74(buf);
}
