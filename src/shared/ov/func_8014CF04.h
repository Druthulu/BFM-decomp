/* func_8014CF04 — shared body (overlay slot 0x80128158, h_exact 22579236). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014DD8C(s32 arg0, void *arg1, void *arg2);
extern s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_8014C918(s32 a0, s32 a1);
s32 func_8014CF04(s32 a0, s32 a1, void *a2) {
    extern u8 D_801202A0[];
    extern u8 D_80126720[];
    u8 *p;
    u8 *q;
    s32 t;
    p = D_801202A0;
    if (p < p + 0x6480) {
        q = p + 0x75;
    loop:
        if (*(u16 *)p != 0) {
            if ((*(u16 *)(q - 0x19) & 0x400) != 0) {
                t = *(s32 *)(q - 0x1D);
                if (t != 0) {
                    if (p != *(u8 **)(a0 + 0x178)) {
                        if (p != *(u8 **)(a0 + 0x174)) {
                            if (*(s16 *)(q - 0x6B) >= *(s16 *)(a0 + 0xA)) {
                                if (func_80135A4C(*(s32 *)(q - 0x55), t, (s32 *)a1, (s32)a2) != 0) {
                                    *(u8 **)(a0 + 0x174) = p;
                                    q[-1] = 1;
                                    *(u16 *)(a0 + 6) = *(u16 *)a2;
                                    *(u16 *)(a0 + 0xA) = *(u16 *)((u8 *)a2 + 2);
                                    *(u16 *)(a0 + 0xE) = *(u16 *)((u8 *)a2 + 4);
                                    *(u16 *)(a0 + 0x16E) = func_8014C918(a0, q[0]) & 0xFF;
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        p += 0x10C;
        q += 0x10C;
        if ((u32)p < (u32)D_80126720) {
            goto loop;
        }
    }
    return 0;
}
