/* func_8018BDA4 — shared body (overlay slot 0x80128158, h_exact 42c9d75c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012E57C(s32 a0, s32 a1);
void func_8018BDA4(s32 a0) {
    *(s16 *)(a0 + 0x2) = 1;
    *(s32 *)(a0 + 0xCC) = func_8012E57C(0x61, 0xA);
}
