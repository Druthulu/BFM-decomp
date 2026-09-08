/* func_8012F214 — shared body (overlay slot 0x80128158, h_exact 0400cb37). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
void func_8012F214(s32 a0, s32 a1, s32 a2) {
    s32 *p = (s32 *)(*(s32 *)(a0 + 0x20) + 0x34);
    s32 buf[2];
    func_8004914C(p);
    func_800491AC(p);
    RotTransSV(a1, a2, buf);
}
