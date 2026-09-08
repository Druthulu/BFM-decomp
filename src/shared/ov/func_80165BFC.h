/* func_80165BFC — shared body (overlay slot 0x80128158, h_exact a7c4f31c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80161208();
extern void func_80165C58(s32 arg0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
void func_80165BFC(void *a0) {
    if (func_80161208() == 0) {
        if (*(u16 *)((u8 *)a0 + 0xB8) & 0x8000) {
            func_80165C58((s32)a0);
            func_801599A4(a0);
            func_80159B3C(a0);
        }
    }
}
