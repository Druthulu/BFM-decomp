/* func_8012C218 — shared body (overlay slot 0x80128158, h_exact ce41e186). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
void func_8012C218(void *a0) {
    u16 *p = ((u16 **)a0)[8];   /* 0x20/4 */
    if (p) {
        s32 a1;
        switch (*p) {
        case 2:  a1 = 0x38; break;
        case 1:  a1 = 0x84; break;
        default: goto skip;
        }
        func_80016714(p, a1);
    }
skip:
    func_80016714(a0, 0x10C);
}
