/* func_8012CEB0 — shared body (overlay slot 0x80128158, h_exact 72940661). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
s32 func_8012CEB0(s32 a0, s32 a1, s32 a2) {
    s32 sp10[2];
    s32 r;
    s32 v;
    s32 t;
    if ((a2 & 1) != 0) {
        s32 u;
        r = func_80133784((s16)a2, (void *)a0, a1);
        u = *(u8 *)(a1 + 6);
        r |= u;
        if (u == 2 || u == 0x1B) {
            r |= 0x1000;
        }
        return r;
    } else {
        r = func_80133784(0, (void *)a0, a1);
        if (r == 0) {
            return 0;
        }
        v = func_80133784(2, (void *)a1, (s32)sp10);
        if ((v & 0x6000) == 0) {
            return 0;
        }
        v &= 0xFFFF7FFF;
        v |= (r & 0x8000);
        t = *(u8 *)(a1 + 6);
        *(s16 *)(a1 + 2) = *(u16 *)((s32)sp10 + 2);
        v |= t;
        if (t == 2 || t == 0x1B) {
            v |= 0x1000;
        }
        return v;
    }
}
