/* func_801490F8 — shared body (overlay slot 0x80128158, h_exact 661924c3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
void func_801490F8(s32 a0, s32 a1) {
    s32 s0 = a0;
    s32 s1 = (s16)a1;
    *(s16 *)(s0 + 0x100) =
        *(u16 *)(s0 + 0x100) +
        func_80012B04(*(s16 *)(s0 + 0x100), *(s16 *)(s0 + 0x108), s1);
    *(s16 *)(s0 + 0x102) =
        *(u16 *)(s0 + 0x102) +
        func_80012B04(*(s16 *)(s0 + 0x102), *(s16 *)(s0 + 0x10A), s1);
    *(s16 *)(s0 + 0x104) =
        *(u16 *)(s0 + 0x104) +
        func_80012B04(*(s16 *)(s0 + 0x104), *(s16 *)(s0 + 0x10C), s1);
}
