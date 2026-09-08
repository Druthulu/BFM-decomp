/* func_8016004C — shared body (overlay slot 0x80128158, h_exact a48dcd47). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800B9A17;
void func_8016004C(s32 a0) {
    *(s32 *)((s32)a0 + 0x184) = 0;
    *(s16 *)((s32)a0 + 0x18A) = 0;
    *(s16 *)((s32)a0 + 0x188) = 0;
    *(s32 *)((s32)a0 + 0x44) &= ~0x10;
    D_800B9A17 = 1;
}
