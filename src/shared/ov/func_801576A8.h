/* func_801576A8 — shared body (overlay slot 0x80128158, h_exact cb63f983). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80155FF8(int arg, int a1);
void func_801576A8(void *arg0) {
    extern int func_80155FF8(int arg, int a1);
    extern void func_801599A4(void *a0);
    extern void func_80159B3C(void *a0);
    extern s32 func_80161208(void);
    s32 spill[4];  /* forces the 0x28 frame the target reserves */
    *(s32 *)((u8 *)arg0 + 0x44) |= 2;
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        func_801599A4(arg0);
        func_80159B3C(arg0);
    } else if (((s32 (*)(void *))func_80161208)(arg0) == 0) {
        func_80155FF8((int)arg0, *(u8 *)((u8 *)arg0 + 0x1AA));
    }
}
