/* func_80182A7C — shared body (overlay slot 0x80128158, h_exact 9673e258). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80184CB8(s32*, s32);
void func_80182A7C(void * arg0) {
    extern short D_80191C08;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 5;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_80191C08);
    }
}
