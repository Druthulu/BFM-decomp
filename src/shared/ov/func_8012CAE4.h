/* func_8012CAE4 — shared body (overlay slot 0x80128158, h_exact 2820a65d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
extern u16 D_801274E4[];
void func_8012CAE4(void *a0) {
    u16 *d;
    void *p;
    s32 t;
    s32 a1;
    d = D_801274E4;
    *d |= 1;
    p = *(void **)((s32)a0 + 0x20);
    if (p != 0) {
        t = *(u16 *)p;
        if (t != 1) {
            if (t != 2) {
                goto done;
            }
            a1 = 0x38;
        } else {
            a1 = 0x84;
        }
        func_80016714(p, a1);
    done:;
    }
    func_80016714(a0, 0x10C);
}
