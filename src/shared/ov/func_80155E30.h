/* func_80155E30 — shared body (overlay slot 0x80128158, h_exact 10692cc0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80155E30(void *a0) {
    extern int func_80155FF8(int arg, int a1);
    extern void func_801599A4(void *a0);
    extern void func_80159B3C(void *a0);
    extern s32 func_80161208(void);
    volatile s32 spill[4];
    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
        return;
    }
    if (((s32 (*)(s32 *))func_80161208)(a0) != 0) {
        return;
    }
    func_80155FF8((int)a0, *(u8 *)((u8 *)a0 + 0x1AA));
}
