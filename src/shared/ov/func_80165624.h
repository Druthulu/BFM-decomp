/* func_80165624 — shared body (overlay slot 0x80128158, h_exact 38098ef9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 func_80165658(s32 a0, s32 a1);
extern u8 D_80078EC1;
extern s16 D_80078EB8;
s32 func_80165624(s32 a0) {
    return (u32)(u16)D_80078EB8 < (u32)(func_80165658(a0, D_80078EC1 & 0x7F) & 0x7F);
}
