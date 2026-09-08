/* func_80170B90 — shared body (overlay slot 0x80128158, h_exact ef71fb01). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147060(u8 *a0);
extern void func_80171928(void *a0);
void func_80170B90(u8 *a0) {
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        func_80147060(a0);
        func_80171928(a0);
    }
}
