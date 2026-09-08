/* func_8015ED6C — shared body (overlay slot 0x80128158, h_exact fd7de987). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EBF;
extern void func_80149048(s32 *a0);
void func_8015ED6C(s32 *a0) {
    D_80078EBF = 0;
    *(s32 *)((s32)a0 + 0x44) &= -2;
    func_80149048(a0);
}
