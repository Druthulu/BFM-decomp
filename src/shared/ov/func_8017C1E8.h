/* func_8017C1E8 — shared body (overlay slot 0x80128158, h_exact 72bf44a0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147060(u8 *a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
void func_8017C1E8(void *a0) {
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        func_80147060((u8 *)a0);
        func_80171A1C((u8 *)a0);
        func_80174650((s32)a0);
    }
}
