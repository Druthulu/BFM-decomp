/* func_80184374 — shared body (overlay slot 0x80128158, h_exact f6605f79). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80184CB8(s32*, s32);
void func_80184374(void * arg0) {
    extern short D_8019224C;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 6;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_8019224C);
    }
}
