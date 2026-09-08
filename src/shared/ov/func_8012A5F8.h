/* func_8012A5F8 — shared body (overlay slot 0x80128158, h_exact 06251e23). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012A62C(s32);
void func_8012A5F8(void (*a0)(void), s32 a1) {
    func_8012A62C(a1 & 0xFF);
    a0();
}
