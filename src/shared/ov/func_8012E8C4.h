/* func_8012E8C4 — shared body (overlay slot 0x80128158, h_exact 9ff619a4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8012E8C4(u8 *a0) {
    s32 *p = *(s32 **)(a0 + 0x20);
    p[1] = p[1] ^ 0x80000000;
}
