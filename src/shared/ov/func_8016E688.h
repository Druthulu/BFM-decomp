/* func_8016E688 — shared body (overlay slot 0x80128158, h_exact d643470d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016E778();
void func_8016E688(void *a0) {
    u16 *p = (u16 *)a0;
    s16 v;
    p[0x10/2] += 0x200;
    v = p[0x12/2] + p[0x10/2];
    p[0x12/2] = v;
    if (v >= 0x3000) {
        *(s32 *)((u8 *)a0 + 0x1C) = 4;
        *(s16 *)((u8 *)a0 + 0x2) += 1;
    }
    func_8016E778();
}
