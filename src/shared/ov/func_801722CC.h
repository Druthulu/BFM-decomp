/* func_801722CC — shared body (overlay slot 0x80128158, h_exact a86bc9a1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80172664(s32 *a0);
void func_801722CC(s32 *a0) {
    if (func_80172664(a0) == 0) {
        *(s16 *)((u8 *)a0 + 0xAC) = 0x40;
        *(s16 *)((u8 *)a0 + 0xAA) = 0x40;
    }
}
