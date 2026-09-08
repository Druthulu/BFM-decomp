/* func_80132DC4 — shared body (overlay slot 0x80128158, h_exact 06db85cd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 VectorNormalSS(void *a0, void *a1);
void func_80132DC4(s32 a0, s32 a1, s32 a2) {
    s16 in[3];
    s16 out[4];
    in[0] = (u16)*(u16 *)(a1 + 0x0) - *(u16 *)(a0 + 0x6);
    in[1] = (u16)*(u16 *)(a1 + 0x2) - *(u16 *)(a0 + 0xA);
    in[2] = (u16)*(u16 *)(a1 + 0x4) - *(u16 *)(a0 + 0xE);
    VectorNormalSS(&in[0], &out[0]);
    *(s32 *)(a0 + 0x10) = out[0] * a2;
    *(s32 *)(a0 + 0x14) = out[1] * a2;
    *(s32 *)(a0 + 0x18) = out[2] * a2;
}
