/* func_80172ACC — shared body (overlay slot 0x80128158, h_exact f865f9dd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
void func_80172ACC(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    u16 v = *(u16 *)(a0 + 0x132);
    *(s16 *)(a0 + 0x136) = 0;
    *(u16 *)(p + 0x12) = v;
    func_80171A1C(a0);
    func_80174650((s32)a0);
}
