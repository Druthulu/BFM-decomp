/* func_8017CBD4 — shared body (overlay slot 0x80128158, h_exact 6f36e213). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800291A0(s32, s32);
extern int func_80178970(void);
extern void func_80178D18(void);
void func_8017CBD4(s32 a0) {
    extern void func_8002955C(void);
    extern s32 func_8002953C(void);
    extern void func_8002AC00(s32 arg0);
    u8 *p = *(u8 **)(a0 + 0xDC);
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        func_800291A0(*p + 0x3A, 1);
        func_8002955C();
        if ((u32)func_8002953C() >= 0x23U) {
            func_8002AC00(0x25);
        }
        *(u16 *)(a0 + 2) += 1;
    }
}
