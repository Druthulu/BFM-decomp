/* func_8014AA04 — shared body (overlay slot 0x80128158, h_exact c25c9d44). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EC0;
void func_8014AA04(s32 a0) {
    D_80078EC0 = a0 | (D_80078EC0 & 0x80);
}
