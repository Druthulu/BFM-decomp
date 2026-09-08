/* func_801655E4 — shared body (overlay slot 0x80128158, h_exact 57c0fed7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EC1;
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_8014BD60(s32 a0, s32 a1);
void func_801655E4(s32 a0) {
    func_8014BD60(a0, func_80165658(a0, D_80078EC1 & 0x7F) & 0x7F);
}
